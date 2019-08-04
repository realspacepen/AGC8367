
#include "sys.h" 
#define PA6_ADC ADC_Channel_6
#define PA7_ADC ADC_Channel_7
void Adc1_Init(void);  							   
void Adc2_Init(void); 				//ADC通道初始化
u16  Get_Adc_CH1(u8 ch); 				//获得某个通道值 
u16  Get_Adc_CH2(u8 ch); 	
u16 Get_Adc_Average1(u8 ch,u8 times);//得到某个通道给定次数采样的平均值  
u16 Get_Adc_Average2(u8 ch,u8 times);
float Get_Adc_PAx(u8 AdNo,u8 ch,u8 times,float Offset);














