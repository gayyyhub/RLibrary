#include "distance.h"
#include "usart.h"

u8 get_distance(u8 parameter,u16 rssi)
{
	u8 distance;
	rssi/=10;//取rssi平均值
	distance = rssi;//计算距离
	return distance;
}


void send_distance(u8 distance)
{
	USART_SendData(USART2, 0xff);//向串口1发送数据
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束,
	USART_SendData(USART2, id);//发送id
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束,
	USART_SendData(USART2, distance);//发送距离
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束,
	
}