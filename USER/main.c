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
char gesture_1[]="the signal is 1"; //����1
char gesture_2[]="the signal is 2"; //����2�����Ƽ���
char gesture_3[]="the signal is 3";//����3
char gesture_4[]="the signal is 4";//����4
char gesture_5[]="the signal is 5";//����5�����Ʋ�
char gesture_stone[]="the signal is stone";//����ʯͷ
char gesture_dao[]="the signal is scissor";//���Ƽ���
char gesture_bu[]="the signal is cloth";//���Ʋ�

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
 
 
float temp0[6];  //�ƻ���������壬��ȡ�����ĵ���ֵ���øñ�����������������ֵ
float temp1[6];  //�ƻ���������壬��ȡ�����ĵ���ֵ���øñ�����������������ֵ  ��Ҫ��temp1���Ƚ�
float temp2[6];    //������ƫ��ֵ��������
float temp3[6];    //������������ƫ��ֵ��δ����
float tem0[12];   //��ʼ���뵱ʱ�����������ĳ�ʼ��ĵ���ֵ��Χ��δ���ǣ�ÿ������Ϊһ�飬��Ŵ�1-6
float tem1[12];   //��ʼ���뵱ʱ�����������ĳ�ʼ��ĵ���ֵ��Χ��ȫ���ǣ�ÿ������Ϊһ�飬��Ŵ�1-6
u8 key_bod;
u8 flag_tr=0;   //�ж��Ƿ�ѵ���ɹ��ˣ����Σ�
u8 flag_tr1=0;    //����һ��ģ����ж�
u8 flag_set=0;   //������־�� 
u8 flag_set1=0;  //����������ʾ��
void System_de1(void);   //��������
void	System_de2(void);
void	System_tr11(void);
void	System_tr22(void);
void System_Start(void);
void System_Test(void);

void SetRemap(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//AFIOʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	//�ı�ָ���ܽŵ�ӳ��GPIO_Remap_SWJ_JTAGDisable JTAG-DP����+SW-DPʹ��
}


void Cal_Dat_start()    //���ö�ȡ���ݣ�������ʱ�����������ĳ�ʼ��ĵ���ֵ
{
	temp0[0] = Cap_Calculate(0);//��ȡ��ʼֵ����һ�飩  0-5��Ӧ1-6
	temp0[1] = Cap_Calculate(1);
	temp0[2] = Cap_Calculate(2);
	temp0[3] = Cap_Calculate(3);	
	temp0[4] = Cap_Calculate1(0);	  //��ȡ��ʼֵ���ڶ��飩
	temp0[5] = Cap_Calculate1(1);	
}

void Cal_Dat_start1()    //���ö�ȡ���ݣ�������ʱ�����������ĳ�ʼ��ĵ���ֵ
{
	temp1[0] = Cap_Calculate(0);//��ȡ��ʼֵ����һ�飩  0-5��Ӧ1-6
	temp1[1] = Cap_Calculate(1);
	temp1[2] = Cap_Calculate(2);
	temp1[3] = Cap_Calculate(3);	
	temp1[4] = Cap_Calculate1(0);	  //��ȡ��ʼֵ���ڶ��飩
	temp1[5] = Cap_Calculate1(1);	
}


void Decide_Init_shou()  //���ڲ����ֵ��ж�
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

void Decide_Init_shu()  //���ڲ����Ƶ��ж�
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
	flag_set=0;    //���ü����жϵı�־λ
	flag_set1=0;   //���ò����ñ�־λ
	delay_init();  // ��ʼ����ʱ
	SetRemap();   //��ʼ��jlink
  FDC2214_Init();// ��ʼ��fdc2214(�ڶ���)
  FDC2214_Init1(); //��ʼ��fdc2214(��һ�飩
	OLED_Init();//��ʼ��OLED��������ʾ
	KEY_Init();//��ʼ������key_board,����������Ϣ
}

void System_Start(void)  //ϵͳ���� 
{
	OLED_6_8(0,0,gesture_start);     //��ʾָʾ�Ա�����ݼ�����
	OLED_6_8(1,0,gesture_start1);
	OLED_6_8(2,0,gesture_start2);
	OLED_6_8(3,0,gesture_start3);
	OLED_6_8(4,0,gesture_start4);
	OLED_6_8(5,0,gesture_prepare1);
}
void	System_de1(void)   //�²���������
{
	flag_tr1=1;
	 delay_ms(10);  //��������
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
void	System_de2(void)    //�²������ʯͷ��������
{
	flag_tr1=1;
	 delay_ms(10);  //��������
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

void	System_tr11(void)    //ѵ�����²���������
{
	int i;
	 delay_ms(10);  //��������
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

void	System_tr22(void)   //ѵ�����²����ʯͷ������
{
	int i;
	 delay_ms(10);  //��������
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
void System_test(void)  //ϵͳ��ʼ����
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

  System_Init();//��ʼ������ϵͳ
		OLED_clear();
 Cal_Dat_start(); //���ö�ȡ���ݣ�������ʱ�����������ĳ�ʼ��ĵ���ֵ
  	System_Start();  //��ϵͳ����
		  System_test();

	//OLED_6_8_Number(0,0,-12344885,0);
	//OLED_8_16_Number(1,0,-12231545,0);
//	 OLED_clear();
// Cal_Dat_start1(); //���ö�ȡ���ݣ�������ʱ�����������ĳ�ʼ��ĵ���ֵ
//  Decide_Init_shu();
		while(1)
	{
		
	}
}


