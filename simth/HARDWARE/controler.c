#include "controler.h"
#include "usart.h"
#include "keyboard.h"

#define N   201			//滞后10s，N = ts/T(滞后时间/采样时间 + 1)

float Kp;
float Ki;
float Kd;				//初始的PID参数在keyboard中设置，后续可以通过按键改变

float rt = 1.0;														  //输入
float Err1 = 0;																//偏差err1
float Yk = 0, Yk_last = 0;										//预估器补偿
float Err2 = 0, Err2_last = 0, Err2_pre = 0;	//偏差err2
float Uk[N] = {0};														//输出控制量
float Yt = 0;																	//输出

void Get_Err1(void)		
{
	rt = In;
	Err1 = rt - Yt;
}

void Get_Yk(void)			//预估器补偿
{
	Yk_last = Yk;
	Yk = a*Yk_last + b*(Uk[0] - Uk[N - 1]);
}

void Get_Err2(void)
{
	Err2_pre = Err2_last;
	Err2_last = Err2;
	Err2 = Err1 - Yk;
}

float Get_Uk(void)		//得到控制量
{
	int i = 0;
	
	for (i = 0; i < N - 1; i++)
	{
		Uk[N-1-i] = Uk[N-2-i];
	}
	
	Ki = Px;
	Kp = Ix;
	
	Uk[0] = Uk[1] + Kp*(Err2 - Err2_last) + Ki*Err2 + Kd*(Err2 - 2*Err2_last + Err2_pre);
	
	if (Uk[0] >= 10)				//控制器输出限幅
		Uk[0] = 10;
	if (Uk[0] <= -10)  		
		Uk[0] = -10;
	
//	Uk[0] = rt/K;				//最优控制量
	
	return Uk[0];
}

