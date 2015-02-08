/* Includes ------------------------------------------------------------------*/
#include <stm32f4xx_conf.h>
#include <stm32f4xx.h>

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

/**
 * @brief Fchier contenant tout les define du projet
 */
#include "Project_conf.h"


#include "interruption.h"
#include "camera.h"
#include "adc.h"
#include "servo.h"
#include "led.h"
#include "Propultion.h"
#include "Accelerometre.h"
#include "PID.h"
#include "Additional_Features.h"

/*************Variable globale*************/
unsigned char	ucCompteur=0;
unsigned int	ADCResult1[128];
unsigned char	cConmand = ADXL345_DATAX0_REG;
char			X_Value0 = 0;
char			Y_Value0 = 0;
char 			X_Value1 = 0;
char			Y_Value1 = 0;

/*************Semaphore*************/

xSemaphoreHandle xSemaphoreSERVO = NULL;
xSemaphoreHandle xSemaphoreACC	 = NULL;

static signed portBASE_TYPE xHigherPriorityTaskWoken;


void vApplicationIdleHook(void){

	__WFI();
}


int main(void)
{
	vSemaphoreCreateBinary( xSemaphoreSERVO );
	vSemaphoreCreateBinary( xSemaphoreACC);

	SystemInit();
	SystemCoreClockUpdate();


		/*************Initialisation de l'ADC camera ***************/
		GPIO_Config_Camera_Adc1_PA1();
		ADC1_CH1_Config_Camera();

		/*************Initialisation PWM Led eclairage ***************/
		vLedCamera_Timer2_CH4_PB11();

		/*************Initialisation PWM Clock Camera ***************/
		vClockCamera_Timer4_CH1_PB6();

		/*************Initialisation de l'adc Batterie ***************/
		vBattery_GpioPA4_ADC2_CH4();

		/*************Initialisation Gpio Led Batterie ***************/
		vLedBattery_GpioPD0134();

		/*************Initialisation Gpio Si Camera ***************/
		vSICameraGpio_PE0();

		/*************Initialisation PWM Servo Moteur ***************/
		vServo_Timer11_CH1_PB9();

		/**************Lancement course*************/
		vStartButton_GpioE3();

					//127----150----187
		while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)==0 );

		/*****************Enable des moteur**************/
		vEnableMoteur_GPIO_PE2();

		vmoteur_G_Timer3_CH1_PC6();
		vmoteur_D_Timer3_CH2_PC7();
		/*****************Accelerometre*****************/
		//vAccelerometre_Init_ALL();
		/*****************PID*****************/
		init_PID();

//	DiodeDeTest();
		EXTILine6_Config_PB6();

	xTaskCreate( ServoMoteur,	(signed char*)"SERVO", 		configMINIMAL_STACK_SIZE, 	NULL, PRIORITE_NIVEAU_3,	NULL);
	xTaskCreate( BarGraph,		(signed char*)"BATTERY",	configMINIMAL_STACK_SIZE,	NULL, PRIORITE_NIVEAU_1,	NULL);
	xTaskCreate( Accelerometre,	(signed char*)"ACCELERO",	configMINIMAL_STACK_SIZE,   NULL, PRIORITE_NIVEAU_2,	NULL);

	vTaskStartScheduler();

	while(1)
	{
	}
}
/* Cette interruption se d�clanche tous les fronts montants du PWM de la camera
 * A chaque front :
 * 					- On incr�mente un compteur GLOBALE
 * 					- On lache un semaphore ADC pour d�clencher une tache AoAdc qui effectue une conversion (NE MARCHE PAS!!!!!!)
 * (TEMPORAIRE!!!) = On effectue la conversion au lieu de la faire dans tache comme on devrait!! On la stocke dans un tableau globale
 * Tout les 127 front:
 * 					- On lache un semaphore SI pour activer la GPIO SI qui donne le top depart de la camera
 * Tout les 128 Front:
 * 					- On lache un semaphore NOT SI pour desactiver la GPIO SI
 *
 */
void EXTI9_5_IRQHandler(void)
{

	if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	{
		/*Compteur GLOBALE*/
		ucCompteur++;

		xHigherPriorityTaskWoken = pdFALSE;

		/*Semapore de la fonction Conversion ADC de la camera NE MARCHE PAS!!! MAIS ON FAIT COMME SI.....*/
		//xSemaphoreGiveFromISR( xSemaphoreADC, xHigherPriorityTaskWoken );

		/*Si le compteur est a 127 on lache le semaphore Si qui declenche la tache SIcamera*/
		if(ucCompteur == 127)
		{
		//	xSemaphoreGiveFromISR( xSemaphoreSI, xHigherPriorityTaskWoken );
			GPIO_SetBits(GPIOE, GPIO_Pin_0);
			xSemaphoreGiveFromISR( xSemaphoreSERVO, xHigherPriorityTaskWoken );
		}

		/*Si le compteur est a 128 on lache le semaphore NOT Si qui declenche la tache SIcamera*/
		if(ucCompteur == 128)
		{
		//	xSemaphoreGiveFromISR( xSemaphoreNotSI, xHigherPriorityTaskWoken );
			GPIO_ResetBits(GPIOE, GPIO_Pin_0);
			ucCompteur=0;
		}

		ADC_SoftwareStartConv(ADC1);
		ADCResult1[ucCompteur]= ADC_GetConversionValue(ADC1);

		portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
	else if(EXTI_GetITStatus(EXTI_Line8) != RESET)
	{
		xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR( xSemaphoreACC, xHigherPriorityTaskWoken );
		portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
}

void Accelerometre(void * pvParameters)
{
	for(;;)
	{
		if ( xSemaphoreTake( xSemaphoreACC, portMAX_DELAY) == pdTRUE)
		{
			X_Value0 = vAccDataSend(ADXL345_DATAX0_REG);
			Y_Value0 = vAccDataSend(ADXL345_DATAY0_REG);
			X_Value1 = vAccDataSend(ADXL345_DATAX1_REG);
			Y_Value1 = vAccDataSend(ADXL345_DATAY1_REG);
		}
	}
}

/* Cette fonction ne tourne pas tant qu'elle n'a pas re�us le semaphores SERVO
 *
 *
*/
void ServoMoteur(void * pvParameters)
{
	//unsigned char compteur=0;
	//unsigned int	resultat=0;

	for(;;)
	{
		if( xSemaphoreTake( xSemaphoreSERVO, portMAX_DELAY ) == pdTRUE )
		{
			vTraitementLigne(&ADCResult1);

		/*	for(compteur=0; compteur<128; compteur++)
			{
				resultat=ADCResult1[compteur]+resultat;
			}
			resultat=0;*/
		}
	}
}


void BarGraph(void * pvParameters)
{
	uint16_t	uiNiveauBattery;
	for(;;)
	{
		ADC_SoftwareStartConv(ADC2);
		while(ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC) == RESET);
		uiNiveauBattery= ADC_GetConversionValue(ADC2);

		if(uiNiveauBattery>1500 && uiNiveauBattery<1600 )
		{
			GPIO_SetBits(GPIOD,GPIO_Pin_0);
			GPIO_SetBits(GPIOD,GPIO_Pin_1);
			GPIO_SetBits(GPIOD,GPIO_Pin_3);
			GPIO_SetBits(GPIOD,GPIO_Pin_4);
		}

		if(uiNiveauBattery>1400 && uiNiveauBattery<1500 )
		{
			GPIO_SetBits(GPIOD,GPIO_Pin_0);
			GPIO_SetBits(GPIOD,GPIO_Pin_1);
			GPIO_SetBits(GPIOD,GPIO_Pin_3);
			GPIO_ResetBits(GPIOD,GPIO_Pin_4);
		}
		if(uiNiveauBattery>1300 && uiNiveauBattery<1400 )
		{
			GPIO_SetBits(GPIOD,GPIO_Pin_0);
			GPIO_SetBits(GPIOD,GPIO_Pin_1);
			GPIO_ResetBits(GPIOD,GPIO_Pin_3);
			GPIO_ResetBits(GPIOD,GPIO_Pin_4);
		}
		if(uiNiveauBattery >1200 && uiNiveauBattery<1300 )
		{
			GPIO_SetBits(GPIOD,GPIO_Pin_0);
			GPIO_ResetBits(GPIOD,GPIO_Pin_1);
			GPIO_ResetBits(GPIOD,GPIO_Pin_3);
			GPIO_ResetBits(GPIOD,GPIO_Pin_4);
		}
	}
}
