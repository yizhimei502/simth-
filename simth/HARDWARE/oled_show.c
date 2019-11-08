#include "oled_show.h"
#include "oled.h"
#include "keyboard.h"


void OLED_show(float input,float P,float I)
{
	int adcx1=0,adcx2=0;
	int P1=0,P2=0;
	int I1=0,I2=0;
//	int D1=0,D2=0;
//	int t1=0,t2=0;
//	int K1=0,K2=0;
//	int T01=0,T02=0;
//	
	adcx1=(int)(input*100)/100;
	adcx2=(int)(input*100)%100;
	P1=(int)(P*100)/100;
	P2=(int)(P*100)%100;
	I1=(int)(I*100)/100;
	I2=(int)(I*100)%100;
	
	OLED_ShowString(0,0,"Input:");
	OLED_ShowString(10,2,"KP:");
	OLED_ShowString(60,2,"KI:");
	
	OLED_ShowNum(50,0,adcx1,2,12);
	OLED_ShowChar(65,0,'.');
	OLED_ShowNum(70,0,adcx2,2,12);
	
	OLED_ShowNum(10,4,P1,2,12);
	OLED_ShowChar(25,4,'.');
	OLED_ShowNum(30,4,P2,2,12);
	
	OLED_ShowNum(60,4,I1,2,12);
	OLED_ShowChar(75,4,'.');
	OLED_ShowNum(80,4,I2,2,12);
	
}
