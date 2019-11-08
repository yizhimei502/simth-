#ifndef __ADC_32_H
#define __ADC_32_H

#include "sys.h"

void Adc_Init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times); 
 
float AdcToYt(u16 ad_date); 
 
#endif
