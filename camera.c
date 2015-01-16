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

void vSICameraGpio_PB7()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);				//CHANGE
	// Configure PC6-PC9 pins as AF, Pull-Down

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7 ;						//CHANGE
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

/*	InitGpioxTimer(&GPIO_InitStrutureGpioxTimer, &GPIO_InitStructure, ENABLE);*/


	GPIO_Init(GPIOB, &GPIO_InitStructure);								//CHANGE
}
