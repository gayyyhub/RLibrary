#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "includes.h"
#include "lcd.h"
#include "key.h"  
#include "24cxx.h" 
#include "myiic.h"
#include "touch.h" 
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h" 

//任务优先级
#define START_TASK_PRIO		3
//任务堆栈大小	
#define START_STK_SIZE 		512
//任务控制块
OS_TCB StartTaskTCB;
//任务堆栈	
CPU_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *p_arg);

//任务优先级
#define MOUSE_TASK_PRIO		7
//任务堆栈大小
#define MOUSE_STK_SIZE		2048
//任务控制块
OS_TCB	MouseTaskTCB;
//任务堆栈
__align(8) CPU_STK	MOUSE_TASK_STK[MOUSE_STK_SIZE];
//任务函数
void mouse_task(void *p_arg);


//装载画图界面						
void Load_Draw_Dialog(void)
{
	LCD_Clear(WHITE);//清屏   
 	POINT_COLOR=BLUE;//设置字体为蓝色 
	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//显示清屏区域
  	POINT_COLOR=RED;//设置画笔蓝色 
}	  
//计算x1,x2的绝对值
u32 usb_abs(u32 x1,u32 x2)
{
	if(x1>x2)return x1-x2;
	else return x2-x1;
}



int main(void)
{

	OS_ERR err;
	CPU_SR_ALLOC();
	
	

	
	delay_init();       //延时初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //中断分组配置
	uart_init(115200);    //串口波特率设置
	LED_Init();         //LED初始化
	LCD_Init();		//初始化LCD 	
	KEY_Init();		//按键初始化		 	
	TP_Init();		//初始化触摸屏  
	POINT_COLOR=RED;  
	
	
	
	OSInit(&err);		//初始化UCOSIII
	OS_CRITICAL_ENTER();//进入临界区
	//创建开始任务
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//任务控制块
				 (CPU_CHAR	* )"start task", 		//任务名字
                 (OS_TASK_PTR )start_task, 			//任务函数
                 (void		* )0,					//传递给任务函数的参数
                 (OS_PRIO	  )START_TASK_PRIO,     //任务优先级
                 (CPU_STK   * )&START_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//任务堆栈深度限位
                 (CPU_STK_SIZE)START_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,					//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* )&err);				//存放该函数错误时的返回值
	OS_CRITICAL_EXIT();	//退出临界区	 
	OSStart(&err);  //开启UCOSIII
	while(1);
}

//开始任务函数
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//统计任务                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();	
#endif
	
#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	 //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	
	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
	LCD_ShowString(60,70,200,16,16,"USB Mouse TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2014/3/15");	
	LCD_ShowString(60,130,200,16,16,"KEY_UP:SCROLL +");		 
	LCD_ShowString(60,150,200,16,16,"KEY1:RIGHT BTN");	
	LCD_ShowString(60,170,200,16,16,"KEY0:LEFT BTN");	
  	delay_ms(1800);
 	USB_Port_Set(0); 	//USB先断开
	delay_ms(300);
   	USB_Port_Set(1);	//USB再次连接
	//USB配置
 	USB_Interrupts_Config();    
 	Set_USBClock();   
 	USB_Init();	        
	Load_Draw_Dialog();    
	
	OS_CRITICAL_ENTER();	//进入临界区

//创建LED1任务
	OSTaskCreate((OS_TCB 	* )&MouseTaskTCB,		
				 (CPU_CHAR	* )"mouse task", 		
                 (OS_TASK_PTR )mouse_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )MOUSE_TASK_PRIO,     	
                 (CPU_STK   * )&MOUSE_TASK_STK[0],	
                 (CPU_STK_SIZE)MOUSE_STK_SIZE/10,	
                 (CPU_STK_SIZE)MOUSE_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);	
				 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//挂起开始任务			 
	OS_CRITICAL_EXIT();	//进入临界区
}



void mouse_task(void *parg)
{

}

