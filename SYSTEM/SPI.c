#include "sys.h"
#include "SPI.h"

void SPI1_Init(unsigned short CPOL,unsigned short CPHA)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	
	RCC_APB2PeriphClockCmd(SPI1_GPIO_Init,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = SPI1_CLK_Init | SPI1_MISO_Init | SPI1_MOSI_Init;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI1_GPIO,&GPIO_InitStructure);
 	GPIO_SetBits(SPI1_GPIO,SPI1_CLK_Init | SPI1_MISO_Init | SPI1_MOSI_Init);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = CPOL;//ѡ���˴���ʱ�ӵ���̬:ʱ�����ո�
	SPI_InitStructure.SPI_CPHA = CPHA;//���ݲ����ڵڶ���ʱ����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//ָ�����ݴ����MSBλ2����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;//CRCֵ����Ķ���ʽ
	SPI_Init(SPI1, &SPI_InitStructure);//����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
	
	SPI_Cmd(SPI1, ENABLE); //ʹ��SPI����
}

void SPI2_Init(unsigned short CPOL,unsigned short CPHA)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	RCC_APB2PeriphClockCmd(SPI2_GPIO_Init,ENABLE);//��ӦGPIOʱ��ʹ��
	
	GPIO_InitStructure.GPIO_Pin = SPI2_CLK_Init | SPI2_MISO_Init | SPI2_MOSI_Init;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//PB13/14/15����������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI2_GPIO, &GPIO_InitStructure);//��ʼ��GPIOB
	GPIO_SetBits(SPI2_GPIO,SPI2_CLK_Init | SPI2_MISO_Init | SPI2_MOSI_Init);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = CPOL;//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA = CPHA;//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;//CRCֵ����Ķ���ʽ
	SPI_Init(SPI2, &SPI_InitStructure);//����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
	
	SPI_Cmd(SPI2, ENABLE); //ʹ��SPI����
}

void SPI_SetSpeed(SPI_TypeDef* SPIx,unsigned char SPI_BaudRatePrescaler)
{
  	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPIx->CR1&=0xFFC7;
	SPIx->CR1|=SPI_BaudRatePrescaler;//����SPI�ٶ�
	SPI_Cmd(SPIx,ENABLE);
}
