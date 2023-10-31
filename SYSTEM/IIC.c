#include "stm32f10x.h"
#include "IIC.h"
#include "delay.h"
#include <stdio.h>

#define IIC_Delay() //delay_us(1)

void IIC_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(IIC_GPIO_Init,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = IIC_SCL_Init|IIC_SDA_Init;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(IIC_PORT,&GPIO_InitStructure);
	GPIO_SetBits(IIC_PORT,IIC_SCL_Init|IIC_SDA_Init);
}

void IIC_Start(void)//产生IIC开始信号
{
	IIC_SDA_MODE_OUT();//sda线输出
	IIC_SDA_Out = 1;	  	  
	IIC_SCL = 1;
	IIC_Delay();
	IIC_Delay();
 	IIC_SDA_Out = 0;//START:when CLK is high,DATA change form high to low
	IIC_Delay();
	IIC_Delay();
	IIC_SCL = 0;//钳住I2C总线，准备发送或接收数据 
}	  

void IIC_Stop(void)//产生IIC停止信号
{
	IIC_SDA_MODE_OUT();//sda线输出
	IIC_SCL = 0;
	IIC_SDA_Out = 0;//STOP:when CLK is high DATA change form low to high
	IIC_Delay();
	IIC_Delay();
	IIC_SCL = 1;
	IIC_SDA_Out = 1;//发送I2C总线结束信号
	IIC_Delay();
	IIC_Delay();
}

unsigned char IIC_Wait_Ack(void)//等待应答信号到来
{
	unsigned char ucErrTime=0;
	IIC_SDA_MODE_OUT();
	
	IIC_SDA_Out = 1;
	IIC_Delay();
	IIC_SCL = 1;
	IIC_Delay();
	
	IIC_SDA_MODE_IN();//SDA设置为输入
	
	while(IIC_SDA_In)
	{
		ucErrTime ++;
		if(ucErrTime > 250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL = 0;//时钟输出0 	   
	return 0;  
} 

void IIC_Ack(void)//产生ACK应答
{
	IIC_SCL = 0;
	IIC_SDA_MODE_OUT();
	IIC_SDA_Out = 0;
	IIC_Delay();
	IIC_SCL = 1;
	IIC_Delay();
	IIC_SCL = 0;
}

void IIC_NAck(void)//不产生ACK应答
{
	IIC_SCL = 0;
	IIC_SDA_MODE_OUT();
	IIC_SDA_Out = 1;
	IIC_Delay();
	IIC_SCL = 1;
	IIC_Delay();
	IIC_SCL = 0;
}

void IIC_Send_Byte(unsigned char dat)//IIC发送一个字节
{                        
	unsigned char i;
	IIC_SDA_MODE_OUT();
	IIC_SCL = 0;//拉低时钟开始数据传输
	for(i = 0;i < 8;i ++)
	{
		if(dat & 0x80)
			IIC_SDA_Out = 1;
		else
			IIC_SDA_Out = 0;
		
		dat <<= 1;
		IIC_Delay();
		IIC_SCL = 1;
		IIC_Delay();
		IIC_SCL = 0;
		IIC_Delay();
	}
}

unsigned char IIC_Read_Byte(unsigned char ack)//读1个字节
{
	unsigned char i,receive = 0;
	IIC_SDA_MODE_IN();//SDA设置为输入
	for(i = 0;i < 8;i ++)
	{
		IIC_SCL = 0; 
		IIC_Delay();
		IIC_SCL = 1;
		
		receive <<= 1;
		if(IIC_SDA_In)
			receive |= 0x01;
		IIC_Delay();
    }					 
    if(!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack();//发送ACK
	 
    return receive;
}
