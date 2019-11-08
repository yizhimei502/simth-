#include "simth.h"

#define LAG 201			//滞后10s，LAG = ts/T(滞后时间/采样时间 + 1)

//static double Num[2] = {0, 6.3212};
//static double Den[2] = {1, 0.3679};

float Input[LAG] = {0};
float Now_Out = 0, Last_Out = 0;

/****************************
//描述：传递函数模拟（滞后系统）
//输入：indata：控制器输出u(t)
//返回：系统输出
****************************/
float TransFunc_Out(float indata)
{
	int i;
	
	Input[0] = indata;
	
	for (i = 0; i < LAG - 1; i++)
	{
		Input[LAG-1-i] = Input[LAG-2-i];
	}
	
	Now_Out = a*Last_Out + b*Input[LAG-1];
	Last_Out = Now_Out;
	
	return Now_Out;
}

