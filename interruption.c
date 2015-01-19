#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_exti.h>
#include <stm32f4xx_tim.h>
#include <stm32f4xx_adc.h>
#include <stm32f4xx_syscfg.h>
#include <stm32f4xx.h>
#include <misc.h>



#include "interruption.h"
#include "camera.h"
#include "adc.h"
#include "servo.h"

void EXTILine6_Config_PB6(void)
{

  NVIC_InitTypeDef   NVIC_InitStructure;
  EXTI_InitTypeDef   EXTI_InitStructure;

  /* Enable GPIOA clock */
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);				//CHANGE
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);				//CHANGE

//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE );


  /* Configure PA0 pin as input floating */
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
 // GPIO_Init(GPIOA, &GPIO_InitStructure);							//CHANGE


  /* Connect EXTI Line0 to PA0 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource6);		//CHANGE

  /* Configure EXTI Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line6;						//CHANGE
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

 // EXTI2_IRQn EXTI9_5_IRQn
  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;				//CHANGE
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0xF;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
