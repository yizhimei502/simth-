#ifndef __CONTROLER_H
#define __CONTROLER_H

#include "sys.h"

extern float a, b;
extern float rt;									//ÊäÈë
extern float Err1;											//Æ«²îerr1
extern float Yk, Yk_last;								//Ô¤¹ÀÆ÷²¹³¥
extern float Err2, Err2_last, Err2_pre;	//Æ«²îerr2
extern float Uk[];											//Êä³ö¿ØÖÆÁ¿
extern float Yt;												//Êä³ö
extern float K;

void Get_Err1(void);
void Get_Yk(void);
void Get_Err2(void);
float Get_Uk(void);

#endif
