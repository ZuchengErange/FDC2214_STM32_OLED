#ifndef __OLED_H__
#define __OLED_H__

/*选择芯片型号*/
#define SH1106//定义为SH1106，不定义为SSD1306
/*选择字库*/
#define FONT_6_8 
#define FONT_8_16 
/*选择接口*/
#define CONNECTION 1 //1为软件SPI,0为IIC,2为硬件SPI

#define OLED_ADDR 0x78  //I2C地址

#define OLED_HW_SPI SPI1//使用硬件SPI的SPI编号
#define OLED_SPI_Init() SPI1_Init(SPI_CPOL_Low,SPI_CPHA_1Edge)

//-----------------OLED端口定义----------------
#define OLED_PORT GPIOB
#define OLED_GPIO_Init RCC_APB2Periph_GPIOB

#if CONNECTION!=0
#define OLED_SCL PBout(1)//接OLED模块的SCL
#define OLED_SCL_Init GPIO_Pin_1

#define OLED_SDA PBout(3)//接OLED模块SDA
#define OLED_SDA_Init GPIO_Pin_3

#define OLED_RST PBout(5)//接OLED模块RST
#define OLED_RST_Init GPIO_Pin_5

#define OLED_DC PBout(7)//接OLED模块D/C
#define OLED_DC_Init GPIO_Pin_7
#endif

//#define OLED_HAVE_FLASH
#define OLED_PRINTF_REMAP

#define OLED_X 128
#define OLED_Y 64/8
#define Font_Size 16
#define Font_Buff_Size Font_Size*Font_Size/8

void OLED_Init(void);//初始化
void OLED_switch(unsigned char power);//OLED显示开关
void OLED_contrast(unsigned char contrast);//设定对比度，0-255
void OLED_clear(void);//清屏
void OLED_Shift(unsigned char y);
void OLED_bmp(unsigned char x0,unsigned char y0,unsigned char x_lenth,unsigned char y_lenth,const unsigned char *bmp_tab);//显示一幅图片，横坐标范围为0-127，纵坐标范围为0-7页

#ifdef FONT_6_8
void OLED_6_8_Char(unsigned char y,unsigned char x,char ch);
void OLED_6_8(unsigned char x,unsigned char y,char* string);//显示6*8字符串
unsigned char OLED_6_8_Number(unsigned char y,unsigned char x,int number,unsigned char digits);
void OLED_putc(char ch);
#endif
#ifdef FONT_8_16
void OLED_8_16_Char(unsigned char y,unsigned char x,char ch);
void OLED_8_16(unsigned char x,unsigned char y,char* string);//显示8*16字符串
unsigned char OLED_8_16_Number(unsigned char y,unsigned char x,int number,unsigned char digits);
#endif

#ifdef OLED_HAVE_FLASH
unsigned char OLED_OpenFont(char* FileName);
void OLED_DrawGBK16(unsigned char y,unsigned char x,char* Font);
unsigned char OLED_GBK16(unsigned char y,unsigned char x0,const char* str);
#endif

#endif
