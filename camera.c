#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_exti.h>
#include <stm32f4xx_tim.h>
#include <stm32f4xx_adc.h>
#include <stm32f4xx_syscfg.h>
#include <stm32f4xx.h>
#include <math.h>

#include "interruption.h"
#include "camera.h"
#include "adc.h"
#include "servo.h"
#include "Propultion.h"

#define RAPPORT_CYCLIQUE_MILIEU			150
#define INDEX_DONNEE_UTILE_DEBUT		20	//30
#define ORDONNEE_ORIGINE				118.64		//59
#define COEFF_DIRECTEUR					0.568

void vTraitementLigne(unsigned int *ADCResult)
{
//	static float	a									= COEFF_DIRECTEUR;
//	static float	b									= ORDONNEE_ORIGINE;
	static unsigned char	ucRapportCycliquePrecedent	= RAPPORT_CYCLIQUE_MILIEU;

	unsigned char			uiIndexLigneNoir			= 0;
	unsigned char			index						= INDEX_DONNEE_UTILE_DEBUT;
	unsigned char			sucRapportCyclique			= RAPPORT_CYCLIQUE_MILIEU;


	do
	{
		if(ADCResult[index]<3500)
		{
			if( (ADCResult[index]+ADCResult[index+1]+ADCResult[index+2]+ ADCResult[index+3]+ADCResult[index+4]+ADCResult[index+5]+ADCResult[index+6] ) < (ADCResult[index+7]+ADCResult[index+8]+ADCResult[index+9]+ADCResult[index+10]+ADCResult[index+11]+ADCResult[index+12]+ADCResult[index+13] ))
			{
				uiIndexLigneNoir=index;
			}
		}

		index++;
	}while(uiIndexLigneNoir==0 && index <= 108);

	sucRapportCyclique=((unsigned char)(uiIndexLigneNoir*COEFF_DIRECTEUR)+ORDONNEE_ORIGINE);		//	130-180

	//Changer_vitesse_moteur(Calcul_Vitesse_Propultion(sucRapportCyclique));				//132----174

	if(sucRapportCyclique < ucRapportCycliquePrecedent-10 || sucRapportCyclique > ucRapportCycliquePrecedent+10)
	{

	}else
	{
		if(sucRapportCyclique > ucRapportCycliquePrecedent+3 || sucRapportCyclique < ucRapportCycliquePrecedent-3)
		{
			servo_moteur(sucRapportCyclique);
			ucRapportCycliquePrecedent=sucRapportCyclique;
		}
	}

}


void vClockCamera_Timer4_CH1_PB6()
{
	// Configure PC6-PC9 pins as AF, Pull-Down
	GPIO_InitTypeDef        GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;						//CHANGE
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

/*	InitGpioxTimer(&GPIO_InitStrutureGpioxTimer, &GPIO_InitStructure, ENABLE);*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);				//CHANGE
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);				//CHANGE

	GPIO_Init(GPIOB, &GPIO_InitStructure);								//CHANGE

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);				//CHANGE


/*	InitTimer(TIM3, 100, 100, 0);*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Prescaler =100;// psc
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 100;// arr
	TIM_TimeBaseStructure.TIM_ClockDivision =0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;// rcc

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);					//CHANGE

/*	InitPwm(TIM3, TIM_OCMode_PWM1, 50);*/
	TIM_OCInitTypeDef       TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 50;

	//changer le numéro de TIM_OCxInite pour le chanel que tu veux
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);							//CHANGE
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);					//CHANGE

	TIM_ARRPreloadConfig(TIM4, ENABLE);									//CHANGE


	TIM_Cmd(TIM4, ENABLE);												//CHANGE

}

void vSICameraGpio_PE0()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);				//CHANGE
	// Configure PC6-PC9 pins as AF, Pull-Down

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 ;						//CHANGE
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

/*	InitGpioxTimer(&GPIO_InitStrutureGpioxTimer, &GPIO_InitStructure, ENABLE);*/


	GPIO_Init(GPIOE, &GPIO_InitStructure);								//CHANGE
}

