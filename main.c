#include "sys.h"
#include "delay.h"
#include "math.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "usart.h"
#include <stdio.h>
#include <ctype.h>
#include <cstring>
#include "ADC_stm32f4.h"
#include "dac.h"
#include "Timer_set.h"
#include "AD_9226.h"
#include "AD8367_AGC.h"
//----------------------------AGC测试----------------------------------//
void Read_ctrl_init(void);
extern float AD8362_DC;
int main(void)
{ 
	u16 key_code,key;
	u16 DA_tmp=25,AD_tmp;
	float Volt,Vrms;
	float Volt1;
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		
	uart_init(115200);	//串口初始化波特率为115200
	LED_Init();		  		
	Read_ctrl_init();
	Adc1_Init();//A6
	EXTIX_Init();
	Dac1_Init();
 Timer4_Init(4999,2499,83);
 Timer3_Init(49,24,83);
	KEY_Init();
	PBout(13)=1;
	PBout(14)=0;
	TIM3_PWM_Set(49,24,83);
	TIM4_PWM_Set(9,5,5);
//	AD9226_GPIO_config();
	Dac1_Set_Vol(50);
	AD8362_DC=Get_Adc_PAx(1,PA6_ADC,6,0.005);
	while(1)
	{
		AD8362_DC=Get_Adc_PAx(1,PA6_ADC,6,0.005);
		printf("AD=%f\n",AD8362_DC);
		key=KEY_Scan(0);
		key_code=Key_coder();
		if(AD8362_DC<3.0||AD8362_DC>3.15)
		{
			GainControl();
		}
		if(key==KEY0_PRES)break;
		
		delay_ms(100);
	}
	while(1)
	{
		if(key==KEY0_PRES)
		{
			Volt=Get_Adc_PAx(1,PA6_ADC,6,0.005);
			Vrms=1000*pow(10,-0.4415*Volt*Volt+3.2743*Volt-6.3699);
			printf("Volt=%4f\n",Volt);
			printf("Vrms=%4f\n",Vrms);						
		}
		if(key==KEY1_PRES)
		{
			Volt1=Get_AD9226_value();
			delay_ms(50);
			printf("AD_value=%f\n",Volt1);
		}
		if(key_code==1){
				PBout(13)=!PBout(13);
			PBout(14)=!PBout(14);

			DA_tmp+=25;if(DA_tmp==0)DA_tmp=50;
			printf("DA=%d\n",DA_tmp);
			Dac1_Set_Vol(DA_tmp);
		}
		if(key==KEYG6_PRES)
		{			
			printf("OK");
		}
		if(key_code==2){
			PBout(13)=!PBout(13);
			PBout(14)=!PBout(14);
//			printf("2");
			DA_tmp-=25;
			Dac1_Set_Vol(DA_tmp);if(DA_tmp==0)DA_tmp=50;
			printf("DA=%d\n",DA_tmp);
		}
	}

}

void Read_ctrl_init()
{
	 GPIO_InitTypeDef GPIO_InitStructure;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); 
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0|GPIO_Pin_5|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //
	GPIO_Init(GPIOB,&GPIO_InitStructure); 
}

