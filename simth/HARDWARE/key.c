#include "key.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "keyboard.h"
#include "controler.h"


int Key1=0, Key2=0, Key3=0, Key4=0,Key5=0;

void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	
	/**********中断线初始化*****************/
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6);
  EXTI_InitStructure.EXTI_Line=EXTI_Line6;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_Init(&EXTI_InitStructure);	 

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource7);
  EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_Init(&EXTI_InitStructure);	 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource8);
  EXTI_InitStructure.EXTI_Line=EXTI_Line8;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_Init(&EXTI_InitStructure);	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource9);
  EXTI_InitStructure.EXTI_Line=EXTI_Line9;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_Init(&EXTI_InitStructure);	 
	/*******优先级初始化**************************/
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级0 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line6)!=RESET)
	{
		delay_ms(15);//消抖
		if(KEY1==0)	 //按键KEY1
		{
			LED1=!LED1;
			Key1=1;
		}
		EXTI_ClearITPendingBit(EXTI_Line6);  //清除LINE6上的中断标志位
	}		
	
	else if(EXTI_GetITStatus(EXTI_Line7)!=RESET)
	{ 
		delay_ms(15);//消抖
		if(KEY2==0)	 //按键KEY2
		{
			LED2=!LED2;
			Key2=1;
		}	
		EXTI_ClearITPendingBit(EXTI_Line7);  //清除LINE7上的中断标志位
	}		
	 
	else if(EXTI_GetITStatus(EXTI_Line8)!=RESET)
	{ 
		delay_ms(15);//消抖
		if(KEY3==0)	 //按键KEY3
		{
			LED1=!LED1;
			Key3=1;
		}
		EXTI_ClearITPendingBit(EXTI_Line8);  //清除LINE8上的中断标志位
	}		
	 
	 else if(EXTI_GetITStatus(EXTI_Line9)!=RESET)
	{ 
		delay_ms(15);//消抖
		if(KEY4==0)	 //按键KEY4
		{
			LED2=!LED2;
			Key4=1;
		}	
		EXTI_ClearITPendingBit(EXTI_Line9);  //清除LINE9上的中断标志位
	}
}
 



