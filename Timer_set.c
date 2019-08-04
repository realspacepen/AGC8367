#include "sys.h"
#include "Timer_set.h"
void Timer4_Init(u16 arr, u16 ccr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM14????    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//??PORTF??	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM4); //B9,tim4ch4
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM4);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//??100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //??????
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //??
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //???PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //?????
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
	TIM_TimeBaseStructure.TIM_Period=arr;   //??????

	TIM4->CCR3 =ccr;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//??????14
	

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //???????:TIM????????2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //??????
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //????:TIM???????
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //??T??????????TIM1 4OC1

	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //??TIM14?CCR1????????
 
  TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPE?? 
	
	TIM_Cmd(TIM4, ENABLE);  //??TIM14
}
void Timer3_Init(u16 arr, u16 ccr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM14????    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//??PORTF??	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3); //GPIOF9??????14
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//??100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //??????
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //??
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //???PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=83;  //?????
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
//	TIM_TimeBaseStructure.TIM_Period=arr;   //??????
//	//TIM_SetCompare1(TIM4,ccr);
//	TIM3->CCR3 =ccr;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//??????14
	
	//???TIM14 Channel1 PWM??	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //???????:TIM????????2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //??????
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //????:TIM???????
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //??T??????????TIM1 4OC1

	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //??TIM14?CCR1????????
 
  TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPE?? 
	
	TIM_Cmd(TIM3, ENABLE);  //??TIM14
}

void TIM3_PWM_Set(u16 arr,u16 ccr,u16 psc)
{
		TIM3->PSC=psc;  //?????
	 //??????
	TIM3->ARR=arr;   //??????
	//TIM_SetCompare1(TIM4,ccr);
	TIM3->CCR3 =ccr;
}

void TIM4_PWM_Set(u16 arr,u16 ccr,u16 psc)
{
		TIM4->PSC=psc;  //?????
	 //??????
	TIM4->ARR=arr;   //??????
	//TIM_SetCompare1(TIM4,ccr);
	TIM4->CCR4 =ccr;
}