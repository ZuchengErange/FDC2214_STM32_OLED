#include "stm32f10x.h"
#include "delay.h"
#include <stdio.h>
#include "OLED.h"
#include "sys.h"
#include "usart.h"
#include "led.h"
#include "fdc2214.h"
#include "stm32f10x.h"
#include "key.h"
char gesture_1[]="the signal is 1"; //手势1
char gesture_2[]="the signal is 2"; //手势2，手势剪刀
char gesture_3[]="the signal is 3";//手势3
char gesture_4[]="the signal is 4";//手势4
char gesture_5[]="the signal is 5";//手势5，手势布
char gesture_stone[]="the signal is stone";//手势石头
char gesture_dao[]="the signal is scissor";//手势剪刀
char gesture_bu[]="the signal is cloth";//手势布

char gesture_start[]="welcome to the system";
char gesture_start1[]="press 1 to de1";
char gesture_start2[]="press 2 to de2";
char gesture_start3[]="press 3 to tr1";
char gesture_start4[]="press 4 to tr2";
char gesture_prepare1[]="put the hand on test area";
char gesture_prepare2[]="press 1 to start train!";
char gesture_prepare3[]="press 1 to start decide!";
char gesture_prepare4[]="press any key to continue!";
char gesture_succes[]="the train is ok!";
char gesture_end[]="press 1 to continue";
char gesture_error[]="error!";

char gesture_zero[]="Please reset this";
 
 
float temp0[6];  //计划设置六块板，读取六块板的电容值，用该变量，测量六块板电容值
float temp1[6];  //计划设置六块板，读取六块板的电容值，用该变量，测量六块板电容值  需要与temp1作比较
float temp2[6];    //用来存偏差值，已输入
float temp3[6];    //用来计算现在偏差值，未输入
float tem0[12];   //初始输入当时环境下六块板的初始版的电容值范围，未覆盖，每两个数为一组，编号从1-6
float tem1[12];   //初始输入当时环境下六块板的初始版的电容值范围，全覆盖，每两个数为一组，编号从1-6
u8 key_bod;
u8 flag_tr=0;   //判断是否训练成功了（三次）
u8 flag_tr1=0;    //用于一二模块的判断
u8 flag_set=0;   //测量标志量 
u8 flag_set1=0;  //测量待定表示量
void System_de1(void);   //函数声明
void	System_de2(void);
void	System_tr11(void);
void	System_tr22(void);
void System_Start(void);
void System_Test(void);

void SetRemap(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//AFIO时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	//改变指定管脚的映射GPIO_Remap_SWJ_JTAGDisable JTAG-DP禁用+SW-DP使能
}


void Cal_Dat_start()    //设置读取数据，测量当时环境下六块板的初始版的电容值
{
	temp0[0] = Cap_Calculate(0);//读取初始值（第一块）  0-5对应1-6
	temp0[1] = Cap_Calculate(1);
	temp0[2] = Cap_Calculate(2);
	temp0[3] = Cap_Calculate(3);	
	temp0[4] = Cap_Calculate1(0);	  //读取初始值（第二块）
	temp0[5] = Cap_Calculate1(1);	
}

void Cal_Dat_start1()    //设置读取数据，测量当时环境下六块板的初始版的电容值
{
	temp1[0] = Cap_Calculate(0);//读取初始值（第一块）  0-5对应1-6
	temp1[1] = Cap_Calculate(1);
	temp1[2] = Cap_Calculate(2);
	temp1[3] = Cap_Calculate(3);	
	temp1[4] = Cap_Calculate1(0);	  //读取初始值（第二块）
	temp1[5] = Cap_Calculate1(1);	
}


void Decide_Init_shou()  //用于猜数字的判断
{
	int i;
		flag_set=0;
	flag_set1=0;
	for(i=0;i<5;i++)
	{
		if(temp1[i]>=(temp0[i]+0.8))
			flag_set++;
		else 
			flag_set1++;	
		temp3[i]=temp1[i]-temp0[i];
	}
	if (flag_set==0)
	     OLED_6_8(0,0,gesture_stone);
	else if(flag_set==1)
		 OLED_6_8(0,0,gesture_error);
	else if(flag_set==2)
		OLED_6_8(0,0,gesture_dao);
	else if(flag_set==3)
		OLED_6_8(0,0,gesture_error);
	else if(flag_set==4)
		OLED_6_8(0,0,gesture_error);
	else if(flag_set==5)
		OLED_6_8(0,0,gesture_bu);
	delay_ms(10);
	OLED_6_8_Number(1,0,flag_set1,0);
	OLED_6_8_Number(2,0,flag_set,0);
	if(flag_tr1==1)
	OLED_6_8(7,0,gesture_zero);
}

void Decide_Init_shu()  //用于猜手势的判断
{
	int i;
	flag_set=0;
	flag_set1=0;
	for(i=0;i<5;i++)
	{
		if(temp1[i]>=(temp0[i]+0.8))
			flag_set++;
		else 
			flag_set1++;	
		temp3[i]=temp1[i]-temp0[i];
	}
	if (flag_set==0)
	     OLED_6_8(0,0,gesture_stone);
	else if(flag_set==1)
		 OLED_6_8(0,0,gesture_1);
	else if(flag_set==2)
		OLED_6_8(0,0,gesture_2);
	else if(flag_set==3)
		OLED_6_8(0,0,gesture_3);
	else if(flag_set==4)
		OLED_6_8(0,0,gesture_4);
	else if(flag_set==5)
		OLED_6_8(0,0,gesture_5);
	delay_ms(10);
	OLED_6_8_Number(1,0,flag_set1,0);
	OLED_6_8_Number(2,0,flag_set,0);
	if(flag_tr1==1)
	OLED_6_8(7,0,gesture_zero);
}

void System_Init(void)
{
	flag_set=0;    //设置计数判断的标志位
	flag_set1=0;   //设置测试用标志位
	delay_init();  // 初始化延时
	SetRemap();   //初始化jlink
  FDC2214_Init();// 初始化fdc2214(第二块)
  FDC2214_Init1(); //初始化fdc2214(第一块）
	OLED_Init();//初始化OLED，用于显示
	KEY_Init();//初始化键盘key_board,用于输入信息
}

void System_Start(void)  //系统启动 
{
	OLED_6_8(0,0,gesture_start);     //显示指示性标语，内容见上面
	OLED_6_8(1,0,gesture_start1);
	OLED_6_8(2,0,gesture_start2);
	OLED_6_8(3,0,gesture_start3);
	OLED_6_8(4,0,gesture_start4);
	OLED_6_8(5,0,gesture_prepare1);
}
void	System_de1(void)   //猜测数字手势
{
	flag_tr1=1;
	 delay_ms(10);  //消除抖动
	 OLED_clear();
	delay_ms(10);
	  Cal_Dat_start1();
	  Decide_Init_shu();
		key_bod=KEY_Scan(0);
	OLED_6_8(4,0,gesture_prepare4);
    while(!KEY_Scan(0))
		{
		
		}
		OLED_clear();
		delay_ms(10);	 
}
void	System_de2(void)    //猜测剪刀、石头、布手势
{
	flag_tr1=1;
	 delay_ms(10);  //消除抖动
	 OLED_clear();
	delay_ms(10);
	  Cal_Dat_start1();
	  Decide_Init_shou();
		key_bod=KEY_Scan(0);
	OLED_6_8(4,0,gesture_prepare4);
    while(!KEY_Scan(0))
		{
		
		}
		OLED_clear();
		delay_ms(10);	 
}

void	System_tr11(void)    //训练并猜测数字手势
{
	int i;
	 delay_ms(10);  //消除抖动
	 OLED_clear();
	 delay_ms(10);
  	if (flag_tr==1)
	{	
		OLED_clear();
		for(i=0;i<5;i++)
		{
			OLED_6_8(0,0,gesture_prepare1);
			OLED_6_8(1,0,gesture_prepare4);
			 while(!KEY_Scan(0))
		    {		
		    }
		OLED_clear();		
		Cal_Dat_start1();
	  Decide_Init_shu();
		OLED_6_8(1,0,gesture_prepare4);
			while(!KEY_Scan(0))
		    {		
		    }
		 }
	}
	else
	{
    for(i=0;i<=2;i++)
	{
    OLED_clear();
		Cal_Dat_start1();
	  Decide_Init_shu();
		OLED_6_8(2,0,gesture_succes);
		OLED_6_8_Number(3,0,i+1,0);
		if(i==2)
		flag_tr=1;
		key_bod=KEY_Scan(0);
		OLED_6_8(4,0,gesture_prepare4);
    while(!KEY_Scan(0))
		{		
		}
	}
	OLED_clear();
	OLED_6_8(4,0,gesture_start4);	 
  }
}

void	System_tr22(void)   //训练并猜测剪刀石头布手势
{
	int i;
	 delay_ms(10);  //消除抖动
	 OLED_clear();
	 delay_ms(10);
	if (flag_tr==1)
	{	
		OLED_clear();
		for(i=0;i<5;i++)
		{
			OLED_6_8(0,0,gesture_prepare1);
			OLED_6_8(1,0,gesture_prepare4);
			 while(!KEY_Scan(0))
		    {		
		    }
		OLED_clear();		
		Cal_Dat_start1();
	  Decide_Init_shou();
		OLED_6_8(1,0,gesture_prepare4);
			while(!KEY_Scan(0))
		    {		
		    }
		 }
	}
		else
		{
    for(i=0;i<=2;i++)
	{
    OLED_clear();
		Cal_Dat_start1();
	  Decide_Init_shou();
		OLED_6_8(2,0,gesture_succes);
		OLED_6_8_Number(3,0,i+1,0);
		if(i==2)
		flag_tr=1;
		key_bod=KEY_Scan(0);
		OLED_6_8(4,0,gesture_prepare4);
				
    while(!KEY_Scan(0))
		{				}  		
	}
	  OLED_clear();
    OLED_6_8(4,0,gesture_start3);	
    }
}
void System_test(void)  //系统开始测试
{
	key_bod=0;
	while(1)
	{
		delay_ms(10);
	key_bod=KEY_Scan(0);
switch(key_bod){
			case KEY1_PRES:	System_de2();		break;
			case KEY2_PRES:	System_de1();		break;
	    case KEY3_PRES:	System_tr22();		break;
	    case KEY4_PRES:	System_tr11();		break;
			default:		delay_ms(10);	
		}
	}
}

	int s1=1;
int main(void)
{
  tem0[0]=56.9669685 ;
	tem0[1]=57.11726;
	tem0[2]=59.6409378; 
  tem0[3]=59.6832542;
  tem0[4]=54.865818;
  tem0[5]=55.1457558;
	tem0[6]=59.6996422;
	tem0[7]=59.7704773;
	tem0[8]=58.0599136;
	tem0[9]=58.3522148;
	tem0[10]=56.0469933;
	tem0[11]=56.3269958;
	
	tem1[0]=59.1051331;
	tem1[1]=60.365097;
	tem1[2]=61.9395256;
	tem1[3]=63.1645775;
	tem1[4]=56.6305008;
	tem1[5]=58.6025162;
	tem1[6]=61.3317947;
	tem1[7]=63.147892;
	tem1[8]=60.3067894;
	tem1[9]=62.2066345;
	tem1[10]=56.2894669;
	tem1[11]=56.5089607;
	
	temp2[0]=1.6;
 temp2[1]=0.56;
 temp2[2]=1.024745;
 temp2[3]=0;
 temp2[4]=1.9545746;
 temp2[5]=0;
   flag_tr=0;

  System_Init();//初始化整个系统
		OLED_clear();
 Cal_Dat_start(); //设置读取数据，测量当时环境下六块板的初始版的电容值
  	System_Start();  //让系统启动
		  System_test();

	//OLED_6_8_Number(0,0,-12344885,0);
	//OLED_8_16_Number(1,0,-12231545,0);
//	 OLED_clear();
// Cal_Dat_start1(); //设置读取数据，测量当时环境下六块板的初始版的电容值
//  Decide_Init_shu();
		while(1)
	{
		
	}
}


