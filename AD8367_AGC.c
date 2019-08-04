#include "stm32f4xx.h"
#include "ADC_stm32f4.h"
#include "math.h"
#include "dac.h"
#include "delay.h"
#include "AD8367_AGC.h"
#include "usart.h"
float AD8362_Vrms;
float AD8362_DC;
float AD8362_Vpp;
u16 DA_ctrl;

void GainControl(void)
{
	static u8 i;
	AD8362_DC=Get_Adc_PAx(1,PA6_ADC,2,0.05);
//	AD8362_Vrms=1000*pow(10,-0.4415*AD8362_DC*AD8362_DC+3.2743*AD8362_DC-6.3699);
//	AD8362_Vpp=2*1.414*AD8362_Vrms;
	if(AD8362_DC>3.10)
	{
//		Dac1_Set_Vol(50);
		for(i=0;i<20&&AD8362_DC>3.10;i++)
		{
			DA_ctrl-=10;if(DA_ctrl<0)DA_ctrl=10;
			Dac1_Set_Vol(DA_ctrl);
			AD8362_DC=Get_Adc_PAx(1,PA6_ADC,1,0.05);
			delay_ms(6);
		}
		
	}
	else {	
		for(i=0;i<20&&AD8362_DC<3.0;i++)
		{
			AD8362_DC=Get_Adc_PAx(1,PA6_ADC,5,0.05);
/*			AD8362_Vrms=1000*pow(10,-0.4415*AD8362_DC*AD8362_DC+3.2743*AD8362_DC-6.3699);
			if(AD8362_Vrms<350.0)
			{
				DA_ctrl+=10;
				Dac1_Set_Vol(DA_ctrl);
			}
			else if (AD8362_Vrms>400)
			{
				DA_ctrl-=10;
				if(DA_ctrl==0)DA_ctrl=10;
				Dac1_Set_Vol(DA_ctrl);
			}
			else		break;
			delay_ms(10);
		}
*/	
			if(AD8362_DC>3.0)break;
				DA_ctrl+=10;
			if(DA_ctrl>800)DA_ctrl=800;
				Dac1_Set_Vol(DA_ctrl);
			printf("DA=%d\n",DA_ctrl);
			delay_ms(10);
		}
			
			
	}
}
		
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
