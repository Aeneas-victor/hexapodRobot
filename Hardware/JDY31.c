#include "JDY31.h"
#include "Delay.h"
#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

char Serial_RxPacket[100]; //USART1_IRQHandler那接受数据帧中的数据部分存储位置
uint8_t Serial_RxFlag;

void Serial_Init(void)
{
		//这两行代码用来使能USART1和GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//输入上拉
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//配置USART1的通信参数，要符合蓝牙连手机时的要求。即波特率为9600，无奇偶校验位，停止位为1，数据位长度为8位
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//使能USART1的接收中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置中断优先级分组。这里设置为2
	
	//来配置USART1的中断优先级。本代码中设置为抢占优先级为1，子优先级为1
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1, ENABLE);//用来使能USART1
	
}
//这个函数接受一个8位无符号整数(Byte)作为参数，将该字节数据发送到USART1串口
void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}
//通过串口发送一个字节数组的数据。做法是函数接收一个只想字节数组的指针array和数组的长度length作为参数，然后通过不断循环将数组中的每个字节逐个发送
void Serial_SendArray(uint8_t *Array,uint16_t Length)
{
	uint16_t i;
	for(i=0;i<Length;i++)
	{
		Serial_SendByte(Array[i]);
	}
}
//函数接受一个只想字符数组的指针string ，表示要发送的字符串数据
//用法是他使用循环遍历字符串中的每个字符，并调用serial_sendByte()函数将字符逐个发送，直到遇到字符串结束符‘0’
void Serial_SendString(char *String)
{
	uint8_t i=0;
	for(i=0;String[i]!='0';i++)
	{
		Serial_SendByte(String[i]);
	}
}
//一个算法，即底数X的Y次幂的值。接受两个正整数参数：X（底数）和Y（指数）。它使用一个while循环，将底数X连续乘以自身Y次，得到结果Result。初始时，结果Result被初始化为1
uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}
//Number表示要发送的数字，Length表示要发送的数字的位数。它使用一个循环，从最高位开始逐位地发送数值
void Serial_SendNumber(uint32_t Number,uint8_t Length)
{
	uint8_t i;
	for(i=0;i<Length;i++)
	{
		Serial_SendByte(Number/Serial_Pow(10,Length-i-1)%10+'0');//Serial_Pow(10, Length - i - 1)是用来获取当前位的除数，实现数字的右移操作
	}
}
//该函数的目的是将ch的值通过串口发送出去，并返回相同的值。即Serial_SendByte()被调用以将ch的值通过串口发送出去。最后，函数返回ch的值。
int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}
 
//通过串口打印格式化的字符串，实现类似printf()的功能
void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}
 
/**************************************以上跟江科大完全一样************************************/
 
 
void USART1_IRQHandler(void)//USART1串口中断服务函数
{
	static uint8_t flag = 0;
	static uint8_t pRxPacket = 0;
	
	
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)//先通过USART_GetITStatus()函数检查USART1接收中断标志位是否置位，如果RXNE置一了，就进if判断
	{
		uint8_t RxData = USART_ReceiveData(USART1);//调用USART_ReceiveData()函数读取接收寄存器中的数据到变量RxData中
		
		
		if (flag == 0)
		{
			if (RxData == '0' )//RxData为0，表示接收到了数据帧的起始符号
			{
				flag = 1;
				pRxPacket = 0;
			}
		}
		
		else if (flag == 1)
		{
			if (RxData == '1')//如果接收到字符’1'，表示接收到了数据帧的结束符号
			{
				flag = 0;
				Serial_RxPacket[pRxPacket] = '\0';//表示接收到了数据帧的终止符号，将状态切换为0，并在数据包末尾添加字符串结束符号’\0’
				Serial_RxFlag = 1;//表示接收到了完整的数据包
			}
			else//否则，将接收到的数据存储到Serial_RxPacket数组中
			{
				Serial_RxPacket[pRxPacket] = RxData;
				pRxPacket ++;
			}
		}
					USART_ClearITPendingBit(USART1, USART_IT_RXNE);//手动清除USART1接收中断标志位，以结束中断处理过程
	}
}
	//在蓝牙上写"0on1"即可实现打开灯，"0off1"关闭灯





