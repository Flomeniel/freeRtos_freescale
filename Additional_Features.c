/**
 * @file	Additional_Features.c
 * @brief	Ajout suplementaire systeme
 * @author	Souyri	Clement
 * @version v1.0
 * @date	28 janvier	2015
 *
 * @note	Ce fichier conttient tout les fonctionalitées
 * additionelle importante pour le fonctionement du systeme
 */

#include "Additional_Features.h"

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
