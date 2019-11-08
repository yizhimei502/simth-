#include "dac_32.h"

void Dac1_Init(void)
{
  
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //使能PORTA通道时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  //使能DAC通道时钟 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 // 端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 		 //模拟输入
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);						//PA.4 输出高
					
	DAC_InitType.DAC_Trigger=DAC_Trigger_None;	//不使用触发功能 TEN1=0
	DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1输出缓存关闭 BOFF1=1
  DAC_Init(DAC_Channel_1,&DAC_InitType);	 //初始化DAC通道1

	DAC_Cmd(DAC_Channel_1, ENABLE);  //使能DAC1
	DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12位右对齐数据格式设置DAC值

}

//将电压转换后值送入DA器件
//输入：DA电压值
void VoltoDA(float Vol)
{
	unsigned int DaValue;
	
	DaValue = Vol * 4095 / 3.3;		//3.3V参考电压
	
	if (DaValue >= 3720)					//3.0V限幅
		DaValue = 3720;
	if (DaValue <= 0)
		DaValue = 0;							//0V限幅
	
	DAC_SetChannel1Data(DAC_Align_12b_R, (int)DaValue);//初始值为0	
}

//归一化Yt，1单位Yt对应0.01V,Yt设为（-150~~~150）
//输入：Yt
//返回：DA电压值
float RangeToDA(float send)
{
	float data;	
	
	if (send >= 10)
		send = 10;
	if (send <= -10)		//限幅
		send = -10;
	
	if (-10 <= send && send < 0)
		data = (10+send) * 0.15;
	else if (0 <= send && send <= 10)
		data = 1.5 + send * 0.15;
	return data;
}


