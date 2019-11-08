#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "led.h"
#include "oled.h"
#include "DataScope_DP.h"
#include "simth.h"
#include "controler.h"
#include "math.h"
#include "adc_32.h"
#include "dac_32.h"
#include "key.h"
#include "oled_show.h"
#include "keyboard.h"


float T = 0.05;		  //采样周期
int ts = 10;			//纯滞后时间
float T0 = 0.01;		//被控对象的时间常数
float K	= 10;			//被控对象的放大系数

float a, b;

int main(void)
{
	unsigned char i;          	//计数变量
	unsigned char Send_Count; 	//串口需要发送的数据个数		
	float ut;	
	u16 ad_Data;
	float yt_ad;
	float da_yt;
	
	a = exp(-T/T0);
	b = K*(1-a);
	
	Key_Init();
	delay_init();
	uart_init(115200);
	
	LED_Init();
	Adc_Init();
	Dac1_Init();
  OLED_Init();
	
	while (1)
	{							
		ad_Data = Get_Adc_Average(ADC_Channel_1, 5);			//获取CPU2的反馈Yt
		yt_ad = AdcToYt(ad_Data);	
		Yt = yt_ad + 0.12;			//补偿
		 
	  Get_Err1();
		Get_Yk();
		Get_Err2();
		ut = Get_Uk();	
  	Yt = TransFunc_Out(ut);			//得到实际的Yt
		
		da_yt = RangeToDA(Yt);		  //将Yt转换为DA值，发生给CPU2
		VoltoDA(da_yt);								
		
		//将数据发送至上位机，显示波形
		DataScope_Get_Channel_Data(Yt, 1);	
		DataScope_Get_Channel_Data(ut, 2);		
		Send_Count = DataScope_Data_Generate(2);
		for( i = 0 ; i < Send_Count; i++) 
		{
			while((USART1->SR&0X40)==0);  
			USART1->DR = DataScope_OutPut_Buffer[i]; 
		}

		Key_board(In, Px, Ix);			//按键变参数
		OLED_show(In, Px, Ix);			//oled显示
		delay_ms(10);		
	}
}


