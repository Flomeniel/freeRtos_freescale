#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_exti.h>
#include <stm32f4xx_tim.h>
#include <stm32f4xx_adc.h>
#include <stm32f4xx_syscfg.h>
#include <stm32f4xx.h>

#include "interruption.h"
#include "camera.h"
#include "adc.h"
#include "servo.h"




void servo_moteur(unsigned char delta)
{
	TIM_OCInitTypeDef       TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = delta;								//100 correspond

	//changer le numéro de TIM_OCxInite pour le chanel que tu veux
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);							//CHANGE
}

void vServo_Timer3_CH1_PC6()
{
	// Configure PC6-PC9 pins as AF, Pull-Down
	GPIO_InitTypeDef        GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);				//CHANGE
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);				//CHANGE

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;						//CHANGE
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;


	GPIO_Init(GPIOC, &GPIO_InitStructure);								//CHANGE

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);				//CHANGE


/*	InitTimer(TIM3, 100, 100, 0);*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Prescaler =1285;// psc
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 1281;// arr
	TIM_TimeBaseStructure.TIM_ClockDivision =0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;// rcc

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);					//CHANGE

/*	InitPwm(TIM3, TIM_OCMode_PWM1, 50);*/
	TIM_OCInitTypeDef       TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 90;

	//changer le numéro de TIM_OCxInite pour le chanel que tu veux
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);							//CHANGE
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);					//CHANGE

	TIM_ARRPreloadConfig(TIM3, ENABLE);									//CHANGE


	TIM_Cmd(TIM3, ENABLE);												//CHANGE
}
