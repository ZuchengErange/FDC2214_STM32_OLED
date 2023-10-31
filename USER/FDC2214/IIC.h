#ifndef __IIC_H__
#define __IIC_H__

#define IIC_PORT GPIOB
#define IIC_GPIO_Init RCC_APB2Periph_GPIOB

#define IIC_SCL PBout(8)
#define IIC_SCL_Init GPIO_Pin_8

#define IIC_SDA_Pin 9
#define IIC_SDA_In PBin(9)
#define IIC_SDA_Out PBout(9)
#define IIC_SDA_Init GPIO_Pin_9

#if IIC_SDA_Pin<8

#define IIC_SDA_MODE_IN() {\
	IIC_PORT->CRL&=~((unsigned int)0x0000000Fu<<(IIC_SDA_Pin*4));\
	IIC_PORT->CRL|=(unsigned int)8<<(IIC_SDA_Pin*4);}\

#define IIC_SDA_MODE_OUT() {\
	IIC_PORT->CRL&=~((unsigned int)0x0000000Fu<<(IIC_SDA_Pin*4));\
	IIC_PORT->CRL|=(unsigned int)3<<(IIC_SDA_Pin*4);}\

#else
	
#define IIC_SDA_MODE_IN() {\
	IIC_PORT->CRH&=~(((unsigned int)0x0000000Fu<<(IIC_SDA_Pin-8)*4));\
	IIC_PORT->CRH|=(unsigned int)8<<((IIC_SDA_Pin-8)*4);}\

#define IIC_SDA_MODE_OUT() {\
	IIC_PORT->CRH&=~(((unsigned int)0x0000000Fu<<(IIC_SDA_Pin-8)*4));\
	IIC_PORT->CRH|=(unsigned int)3<<((IIC_SDA_Pin-8)*4);}\

#endif

void IIC_Init(void);
void IIC_Start(void);//产生IIC开始信号
void IIC_Stop(void);//产生IIC停止信号
unsigned char IIC_Wait_Ack(void);//等待应答信号到来
void IIC_Ack(void);//产生ACK应答
void IIC_NAck(void);//不产生ACK应答
void IIC_Send_Byte(unsigned char dat);//发送一个字节
unsigned char IIC_Read_Byte(unsigned char ack);//读一个字节
unsigned char IIC_Check(unsigned char addr);

#endif
