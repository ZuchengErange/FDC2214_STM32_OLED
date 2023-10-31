#ifndef __OLED_H__
#define __OLED_H__

/*ѡ��оƬ�ͺ�*/
#define SH1106//����ΪSH1106��������ΪSSD1306
/*ѡ���ֿ�*/
#define FONT_6_8 
#define FONT_8_16 
/*ѡ��ӿ�*/
#define CONNECTION 1 //1Ϊ���SPI,0ΪIIC,2ΪӲ��SPI

#define OLED_ADDR 0x78  //I2C��ַ

#define OLED_HW_SPI SPI1//ʹ��Ӳ��SPI��SPI���
#define OLED_SPI_Init() SPI1_Init(SPI_CPOL_Low,SPI_CPHA_1Edge)

//-----------------OLED�˿ڶ���----------------
#define OLED_PORT GPIOB
#define OLED_GPIO_Init RCC_APB2Periph_GPIOB

#if CONNECTION!=0
#define OLED_SCL PBout(1)//��OLEDģ���SCL
#define OLED_SCL_Init GPIO_Pin_1

#define OLED_SDA PBout(3)//��OLEDģ��SDA
#define OLED_SDA_Init GPIO_Pin_3

#define OLED_RST PBout(5)//��OLEDģ��RST
#define OLED_RST_Init GPIO_Pin_5

#define OLED_DC PBout(7)//��OLEDģ��D/C
#define OLED_DC_Init GPIO_Pin_7
#endif

//#define OLED_HAVE_FLASH
#define OLED_PRINTF_REMAP

#define OLED_X 128
#define OLED_Y 64/8
#define Font_Size 16
#define Font_Buff_Size Font_Size*Font_Size/8

void OLED_Init(void);//��ʼ��
void OLED_switch(unsigned char power);//OLED��ʾ����
void OLED_contrast(unsigned char contrast);//�趨�Աȶȣ�0-255
void OLED_clear(void);//����
void OLED_Shift(unsigned char y);
void OLED_bmp(unsigned char x0,unsigned char y0,unsigned char x_lenth,unsigned char y_lenth,const unsigned char *bmp_tab);//��ʾһ��ͼƬ�������귶ΧΪ0-127�������귶ΧΪ0-7ҳ

#ifdef FONT_6_8
void OLED_6_8_Char(unsigned char y,unsigned char x,char ch);
void OLED_6_8(unsigned char x,unsigned char y,char* string);//��ʾ6*8�ַ���
unsigned char OLED_6_8_Number(unsigned char y,unsigned char x,int number,unsigned char digits);
void OLED_putc(char ch);
#endif
#ifdef FONT_8_16
void OLED_8_16_Char(unsigned char y,unsigned char x,char ch);
void OLED_8_16(unsigned char x,unsigned char y,char* string);//��ʾ8*16�ַ���
unsigned char OLED_8_16_Number(unsigned char y,unsigned char x,int number,unsigned char digits);
#endif

#ifdef OLED_HAVE_FLASH
unsigned char OLED_OpenFont(char* FileName);
void OLED_DrawGBK16(unsigned char y,unsigned char x,char* Font);
unsigned char OLED_GBK16(unsigned char y,unsigned char x0,const char* str);
#endif

#endif
