/**
 * 	@file Propultion.c
 * 	@brief	Programme de gestion moteurs arriere
 * 	@author Souyri clement
 * 	@version v1.2
 * 	@date 19 janvier 2015
 *
 * 	@note
 * 	Ce fichier decrit le fonctionement des moteur arrière gauche et
 * 	droite qui propulse le véhicule.
 *
 */

#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_tim.h>
#include <stm32f4xx_adc.h>
#include <stm32f4xx_syscfg.h>
#include <stm32f4xx.h>

#include "Propultion.h"


void vStartButton_GpioE3()
{
	  GPIO_InitTypeDef  GPIO_InitStructure;
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);				//CHANGE
		// Configure PC6-PC9 pins as AF, Pull-Down

		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3 ;						//CHANGE
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	/*	InitGpioxTimer(&GPIO_InitStrutureGpioxTimer, &GPIO_InitStructure, ENABLE);*/
		GPIO_Init(GPIOE, &GPIO_InitStructure);								//CHANGE
}


/**
 * 	@fn unsigned char Calcul_Vitesse_Propultion(void)
 * 	@brief fonction de calcul de la vitesse moteur
 *
 * 	@return retour un char qui fixera la vitesse à envoyer à la partie commande
 *
 *	@note
 * 	Le calcul de la vitesse doit étre lier à l'aquisition video afin d'avoir
 * 	un systeme entièrement linéaire
 *
 */
unsigned char Calcul_Vitesse_Propultion(unsigned char rapport_cyclique_servo)
{
	unsigned char speed;
	/**
	 * @brief Calcul à déterminer
	 */

	/**
	 * @note
	 * version de test			//132----174
	 */
	if( ( (rapport_cyclique_servo > 120) && (rapport_cyclique_servo < 145) ) || ((rapport_cyclique_servo > 155) && (rapport_cyclique_servo < 185)))
	{
		speed = 10;
	}
	else
	{
		speed = 30;
	}
	return speed;
}

/**
 * 	@fn	void Changer_vitesse_moteur(unsigned char delta)
 * 	@brief	Commande de la vittesse moteur
 *
 * 	@param delta : variable vitesse qui fixe la valeur du rapport cyclyque.
 *
 *	@note
 * 	On fixe un rapport cyclique qui fait varier la vittesse des moteur cette fonction
 * 	prend en compte la diférence entre les deux moteur(problématique de construction).
 */
void Changer_vitesse_moteur(unsigned char delta)
{
	/**
	 *  @brief la structure decrite ci-dessous peut etre modifier par
	 *  	   l'ajout d'un offset de corection si un moteur à un décalage.
	 */

	TIM_OCInitTypeDef       TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = delta;								//100 correspond

	//changer le numéro de TIM_OCxInite pour le chanel que tu veux
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);

//	TIM_OCInitTypeDef       TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = delta;								//100 correspond

	//changer le numéro de TIM_OCxInite pour le chanel que tu veux
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
}

/**
 * 	@fn void propultion_Gauche(unsigned char delta)
 * 	@brief Fonction de modification vitesse du moteur gauche.
 *
 * 	@param delta : variable vitesse qui fixe la valeur du rapport cyclyque.
 *
 *	@note
 * 	Cette fonction permet de modifier la vitesse du moteur gauche independament
 * 	du moteur droit.
 */
void propultion_Gauche(unsigned char delta)
{
	TIM_OCInitTypeDef       TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = delta;								//100 correspond

	//changer le numéro de TIM_OCxInite pour le chanel que tu veux
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
}

/**
 * 	@fn void propultion_Droit(unsigned char delta)
 * 	@brief Fonction de modification vitesse du moteur droit.
 *
 * 	@param delta : variable vitesse qui fixe la valeur du rapport cyclyque.
 *
 *	@note
 * 	Cette fonction permet de modifier la vitesse du moteur droit independament
 * 	du moteur gauche.
 */
void propultion_Droit(unsigned char delta)
{
	TIM_OCInitTypeDef       TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = delta;								//100 correspond

	//changer le numéro de TIM_OCxInite pour le chanel que tu veux
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
}

/**
 * 	@fn void vmoteur_G_Timer3_CH1_PC6(void)
 * 	@brief fonction d'initilaisation du moteur Gauche
 *
 *	@note
 * 	Cette fonction contient toute les initialisation lier au moteur Gauche:
 * 		- Initialisation des pericphérique et des horloges.
 * 		- Initialisation du timer 3 channel 1 qui vagénérer la PWM qui contrôle le moteur.
 * 		- Initialisation de la GPIO PC6.
 */
void vmoteur_G_Timer3_CH1_PC6()
{
	GPIO_InitTypeDef	GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);				//CHANGE
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;						//CHANGE
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;


	GPIO_Init(GPIOC, &GPIO_InitStructure);								//CHANGE

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);				//CHANGE


	/*	InitTimer(TIM3, 100, 100, 0);*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Prescaler =91;// psc
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 90;// arr
	TIM_TimeBaseStructure.TIM_ClockDivision =0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;// rcc

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);					//CHANGE

	/*	InitPwm(TIM3, TIM_OCMode_PWM1, 50);*/
	TIM_OCInitTypeDef       TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 35;

	//changer le numéro de TIM_OCxInite pour le chanel que tu veux
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);							//CHANGE
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);					//CHANGE

	TIM_ARRPreloadConfig(TIM3, ENABLE);									//CHANGE


		TIM_Cmd(TIM3, ENABLE);
}

/**
 * 	@fn void vmoteur_D_Timer3_CH2_PC7(void)
 * 	@brief fonction d'initilaisation du moteur Droit
 *
 *	@note
 * 	Cette fonction contient toute les initialisation lier au moteur Droit:
 * 		- Initialisation des pericphérique et des horloges.
 * 		- Initialisation du timer 3 channel 2 qui vagénérer la PWM qui contrôle le moteur.
 * 		- Initialisation de la GPIO PC7.
 */
void vmoteur_D_Timer3_CH2_PC7()
{
	GPIO_InitTypeDef	GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);				//CHANGE
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7;						//CHANGE
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;


	GPIO_Init(GPIOC, &GPIO_InitStructure);								//CHANGE

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);				//CHANGE


	/*	InitTimer(TIM3, 100, 100, 0);*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Prescaler =91;// psc
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 92;// arr
	TIM_TimeBaseStructure.TIM_ClockDivision =0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;// rcc

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);					//CHANGE

	/*	InitPwm(TIM3, TIM_OCMode_PWM1, 50);*/
	TIM_OCInitTypeDef       TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 35;

	//changer le numéro de TIM_OCxInite pour le chanel que tu veux
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);							//CHANGE
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);					//CHANGE

	TIM_ARRPreloadConfig(TIM3, ENABLE);									//CHANGE


	TIM_Cmd(TIM3, ENABLE);
}

/**
 * 	@fn void propultion_Droit(unsigned char delta)
 * 	@brief Fonction de modification vitesse du moteur droit.
 *
 * 	@param delta : variable vitesse qui fixe la valeur du rapport cyclyque.
 *
 *	@note
 * 	Cette fonction permet de modifier la vitesse du moteur droit independament
 * 	du moteur gauche.
 */
void vEnableMoteur_GPIO_PE2(unsigned char delta)
{
	  GPIO_InitTypeDef  GPIO_InitStructure;
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);				//CHANGE
		// Configure PC6-PC9 pins as AF, Pull-Down

		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2 ;						//CHANGE
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	/*	InitGpioxTimer(&GPIO_InitStrutureGpioxTimer, &GPIO_InitStructure, ENABLE);*/


		GPIO_Init(GPIOE, &GPIO_InitStructure);								//CHANGE
		GPIO_SetBits(GPIOE, GPIO_Pin_2);
}
