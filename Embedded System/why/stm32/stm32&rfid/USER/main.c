#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "OLED_I2C.h"
#include "rfid.h"
#include "parser.h"
#include "distance.h"
 
 
/************************************************
程序说明
1.UART1采用数据队列解释器方式接收读卡器返回的24位数据
2.UART2用于向上位机发送数据，接收中断服务采用末尾回车判断＋BUF存储
3.
************************************************/


 int main(void)
 {		
 	u8 t=0,i,j,k,times,flag,param=1;  	
	u8 x=0,y=0,distance=0;
	u8 comm[]={0xBB,0x00,0x28,0x00,0x00,0x28,0x7E,0x0d,0x0a};
	u32 dis[20][3],temp[10];
 	data_parser  = parser_init(data_header, 1,data_back,1,24);
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
	uart2_init(115200);
 	LED_Init();			     //LED端口初始化
	KEY_Init();          //初始化与按键连接的硬件接口
	I2C_Configuration();
	OLED_Init();
	OLED_CLS();
	USART_GetFlagStatus(USART1,USART_FLAG_TC);
	USART_GetFlagStatus(USART2,USART_FLAG_TC);
	for(j=0;j<9;j++)
	{
		USART_SendData(USART1, comm[j]);//向串口1发送数据
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束,
	}
	OLED_ShowStr(0,0,"---detecting---",2);
	OLED_ShowStr(0,2,"I  D :",2);
	OLED_ShowStr(0,4,"RSSI :",2);
	OLED_ShowStr(0,6,"DIST :",2);
	
 	while(1)
	{
		if(USART_RX_STA==1)//收到rfid标签信息
		{
			for(j=0;j<10;j++)//查询缓冲区判断是否最近录入过
			{
				if(temp[j]==id)//在缓冲区中找到当前id
				{
					flag=1;
					break;
				}
			}
			
			if(flag!=1)//缓冲区中没有此id
			{
				temp[t]=id;//放入缓冲区
				t++; //缓冲区指针后移
				if(t>9) t=0;	//更新覆盖缓冲区
				dis[x][0]=id;		//向累加区添加当前标签
				dis[x][1]=1;	//rssi数量置1
				dis[x][2]=rssi;	//放入第一个rssi
				x++; //累加区指针加1
				
			}
			else//缓冲区中有这个id说明刚被扫过，那么就开始累加
			{	flag=0;
				for(j=0;j<20;j++)	//找到当前id在累加区中位置
				{
					if(dis[j][0]==id)	//找到id所在组
					{	
						dis[j][1]++;	//rssi计数加一
						dis[j][2]+=rssi;	//累加rssi
						if(dis[j][1]==10)//当前扫到的标签已经采集够了10次
						{
							distance=get_distance(param,dis[j][2]);
							send_distance(distance);
							dis[j][0]=0;
							x--;
						}
						break;
					}
				}
			}

			
			//显示ID、RSSI、距离
			OLED_ShowNum(60,2,id,2,2,0);
			OLED_ShowNum(60,4,rssi,3,2,0);
			OLED_ShowNum(60,6,distance,3,2,0);
			//清空标志位
			USART_RX_STA=0;
			
//			USART_SendData(USART2, 0xff);//向串口1发送数据
//			while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束,
//			USART_SendData(USART2, id);//发送id
//			while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束,
//			USART_SendData(USART2, distance);//发送距离
//			while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束,
		}
		
	
	}	 	
 }

