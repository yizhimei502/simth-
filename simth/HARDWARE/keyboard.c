#include "keyboard.h"
#include "key.h"
#include "led.h"

float Px=0.02,Ix=0.001, In=1.00;			 //参数设置

void Key_board(float input,float P,float I)
{
		static int i=0,j=0;
		static int t1=0,t2=0,t3=0,t4=0;
		static int r1=0,r2=0,r3=0;
		char buf[3]={'R','P','I'}; 
		float buf1[4]={0.01,0.1,1,10};
		int  num1=0;
		char num;
		
	if(Key1==1)
	{
		Key1=0;
		num=buf[i];
		switch (num)
		{
			case 'R':  
					r1=1;
					r2=0;
					r3=0;
				break;
			case 'P':  
					r1=0;
					r2=1;
					r3=0;
				break;
			case 'I': 
					r1=0;
					r2=0;
					r3=1;
				break;
			default:
				break;
		}
		i++;
		if(i==3)
			i=0;
	}
	if(Key2==1)
	{
		Key2=0;
		num1=(int)(buf1[j]*100);
		switch(num1)
		{
			case 1: 
			  	t1=1;
					t2=0;
					t3=0;
					t4=0;
					break;
			case 10: 
			  	t1=0;
					t2=1;
					t3=0;
					t4=0;
					break;
			case 100: 
				  t1=0;
					t2=0;
					t3=1;
					t4=0;
					break;
			case 1000: 
			 	  t1=0;
					t2=0;
					t3=0;
					t4=1;
					break;
			default:
					break;
		}
		j++;
		if(j==4)
			j=0;
	}
	if(Key3==1)
	{
		Key5=1;
		Key3=0;
		 if(r1==1 && t1==1)
					input=input+0.01;        
		else if(r1==1 && t2==1)
					input=input+0.1;
		else if(r1==1 && t3==1)
					input=input+1;
		else if(r1==1 && t4==1)
					input=input+10;
		
		else if(r2==1 && t1==1)
					P=P+0.01;        
		else if(r2==1 && t2==1)
					P=P+0.1;
		else if(r2==1 && t3==1)
					P=P+1;
		else if(r2==1 && t4==1)
					P=P+10;
		
		else if(r3==1 && t1==1)
					I=I+0.01;
		else if(r3==1 && t2==1)
					I=I+0.1;
		else if(r3==1 && t3==1)
					I=I+1;
		else if(r3==1 && t4==1)
					I=I+10;
	}
	
	if(Key4==1)
	{
		Key5=1;
		Key4=0;
		 if(r1==1 && t1==1)
					input=input-0.01;
		else if(r1==1 && t2==1)
					input=input-0.1;
		else if(r1==1 && t3==1)
					input=input-1;
		else if(r1==1 && t4==1)
					input=input-10;
		
		else if(r2==1 && t1==1)
					P=P-0.01;
		else if(r2==1 && t2==1)
					P=P-0.1;
		else if(r2==1 && t3==1)
					P=P-1;
		else if(r2==1 && t4==1)
					P=P-10;
		
		else if(r3==1 && t1==1)
					I=I-0.01;
		else if(r3==1 && t2==1)
					I=I-0.1;
		else if(r3==1 && t3==1)
					I=I-1;
		else if(r3==1 && t4==1)
					I=I-10;
	}
	Px=P,Ix=I,In=input;  //赋值给全局变量,方便实现OLED显示与串口显示
}

