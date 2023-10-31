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

void IIC_Start(void)//����IIC��ʼ�ź�
{
	IIC_SDA_MODE_OUT();//sda�����
	IIC_SDA_Out = 1;	  	  
	IIC_SCL = 1;
	IIC_Delay();
	IIC_Delay();
 	IIC_SDA_Out = 0;//START:when CLK is high,DATA change form high to low
	IIC_Delay();
	IIC_Delay();
	IIC_SCL = 0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  

void IIC_Stop(void)//����IICֹͣ�ź�
{
	IIC_SDA_MODE_OUT();//sda�����
	IIC_SCL = 0;
	IIC_SDA_Out = 0;//STOP:when CLK is high DATA change form low to high
	IIC_Delay();
	IIC_Delay();
	IIC_SCL = 1;
	IIC_SDA_Out = 1;//����I2C���߽����ź�
	IIC_Delay();
	IIC_Delay();
}

unsigned char IIC_Wait_Ack(void)//�ȴ�Ӧ���źŵ���
{
	unsigned char ucErrTime=0;
	IIC_SDA_MODE_OUT();
	
	IIC_SDA_Out = 1;
	IIC_Delay();
	IIC_SCL = 1;
	IIC_Delay();
	
	IIC_SDA_MODE_IN();//SDA����Ϊ����
	
	while(IIC_SDA_In)
	{
		ucErrTime ++;
		if(ucErrTime > 250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL = 0;//ʱ�����0 	   
	return 0;  
} 

void IIC_Ack(void)//����ACKӦ��
{
	IIC_SCL = 0;
	IIC_SDA_MODE_OUT();
	IIC_SDA_Out = 0;
	IIC_Delay();
	IIC_SCL = 1;
	IIC_Delay();
	IIC_SCL = 0;
}

void IIC_NAck(void)//������ACKӦ��
{
	IIC_SCL = 0;
	IIC_SDA_MODE_OUT();
	IIC_SDA_Out = 1;
	IIC_Delay();
	IIC_SCL = 1;
	IIC_Delay();
	IIC_SCL = 0;
}

void IIC_Send_Byte(unsigned char dat)//IIC����һ���ֽ�
{                        
	unsigned char i;
	IIC_SDA_MODE_OUT();
	IIC_SCL = 0;//����ʱ�ӿ�ʼ���ݴ���
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

unsigned char IIC_Read_Byte(unsigned char ack)//��1���ֽ�
{
	unsigned char i,receive = 0;
	IIC_SDA_MODE_IN();//SDA����Ϊ����
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
        IIC_NAck();//����nACK
    else
        IIC_Ack();//����ACK
	 
    return receive;
}
