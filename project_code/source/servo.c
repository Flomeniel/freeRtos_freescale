#include "servo.h"

void servo_moteur(unsigned char delta)
{
	TIM_OCInitTypeDef       TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = delta;								//100 correspond

	//changer le numéro de TIM_OCxInite pour le chanel que tu veux
	TIM_OC1Init(TIM11, &TIM_OCInitStructure);							//CHANGE
}

void vServo_Timer11_CH1_PB9()
{
	// Configure PC6-PC9 pins as AF, Pull-Down
	GPIO_InitTypeDef        GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);				//CHANGE
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);				//CHANGE

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;						//CHANGE
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;


	GPIO_Init(GPIOB, &GPIO_InitStructure);								//CHANGE

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM11);				//CHANGE


/*	InitTimer(TIM3, 100, 100, 0);*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Prescaler =1799;// psc
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 1850;// arr
	TIM_TimeBaseStructure.TIM_ClockDivision =0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;// rcc

	TIM_TimeBaseInit(TIM11, &TIM_TimeBaseStructure);					//CHANGE

/*	InitPwm(TIM3, TIM_OCMode_PWM1, 50);*/
	TIM_OCInitTypeDef       TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = REGLAGE_VITESSE_ROTATION_SERVOMOTEUR;

	//changer le numéro de TIM_OCxInite pour le chanel que tu veux
	TIM_OC1Init(TIM11, &TIM_OCInitStructure);							//CHANGE
	TIM_OC1PreloadConfig(TIM11, TIM_OCPreload_Enable);					//CHANGE

	TIM_ARRPreloadConfig(TIM11, ENABLE);									//CHANGE


	TIM_Cmd(TIM11, ENABLE);												//CHANGE
}
