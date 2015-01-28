/* Includes ------------------------------------------------------------------*/
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_exti.h>
#include <stm32f4xx_tim.h>
#include <stm32f4xx_adc.h>
#include <stm32f4xx_syscfg.h>
#include <stm32f4xx.h>
#include <misc.h>

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

#include "interruption.h"
#include "camera.h"
#include "adc.h"
#include "servo.h"
#include "led.h"
#include "Propultion.h"

/********* Define******************/
#define BATTERY_TASK_PRIO	(tskIDLE_PRIORITY + 1)
#define ADC_TASK_PRIO		(tskIDLE_PRIORITY + 2)
#define SERVO_TASK_PRIO		(tskIDLE_PRIORITY + 3)


/*************Variable globale*************/
unsigned char ucCompteur=0;
unsigned int ADCResult1[128];

/*************Semaphore*************/
xSemaphoreHandle xSemaphoreADC   = NULL;
xSemaphoreHandle xSemaphoreSI    = NULL;
xSemaphoreHandle xSemaphoreNotSI = NULL;
xSemaphoreHandle xSemaphoreSERVO = NULL;

static signed portBASE_TYPE xHigherPriorityTaskWoken;


void vApplicationIdleHook(void){

	__WFI();
}


int main(void)
{
	vSemaphoreCreateBinary( xSemaphoreADC );
	vSemaphoreCreateBinary( xSemaphoreSI );
	vSemaphoreCreateBinary( xSemaphoreNotSI );
	vSemaphoreCreateBinary( xSemaphoreSERVO );

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

		while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)==0 );

		/*****************Enable des moteur**************/
		vEnableMoteur_GPIO_PE2();

	//	vmoteur_G_Timer3_CH1_PC6();
	//	vmoteur_D_Timer3_CH2_PC7();

//	DiodeDeTest();
		EXTILine6_Config_PB6();

	xTaskCreate( AoAdc,			(signed char*)"AO", 		configMINIMAL_STACK_SIZE, 	NULL, ADC_TASK_PRIO, 		NULL);
	xTaskCreate( ServoMoteur,	(signed char*)"SERVO", 		configMINIMAL_STACK_SIZE, 	NULL, SERVO_TASK_PRIO,		NULL);
	xTaskCreate( BarGraph,		(signed char*)"BATTERY",	configMINIMAL_STACK_SIZE,	NULL, BATTERY_TASK_PRIO,	NULL);

	vTaskStartScheduler();

	while(1)
	{
	}
}
/* Cette interruption se déclanche tous les fronts montants du PWM de la camera
 * A chaque front :
 * 					- On incrémente un compteur GLOBALE
 * 					- On lache un semaphore ADC pour déclencher une tache AoAdc qui effectue une conversion (NE MARCHE PAS!!!!!!)
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
		xSemaphoreGiveFromISR( xSemaphoreADC, xHigherPriorityTaskWoken );

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
}

void AoAdc(void * pvParameters)
{
	for(;;)
	{
		if( xSemaphoreTake( xSemaphoreADC, portMAX_DELAY ) == pdTRUE )
		{
	/*		ADC_SoftwareStartConv(ADC1);
			ADCResult1[ucCompteur]= ADC_GetConversionValue(ADC1);*/
		}
	}
}

/* Cette fonction ne tourne pas tant qu'elle n'a pas reçus le semaphores SERVO
 *
 *
*/
void ServoMoteur(void * pvParameters)
{
	unsigned char compteur=0;
	unsigned int	resultat=0;

	for(;;)
	{
		if( xSemaphoreTake( xSemaphoreSERVO, portMAX_DELAY ) == pdTRUE )
		{
			vTraitementLigne(&ADCResult1);

			for(compteur=0; compteur<128; compteur++)
			{
				resultat=ADCResult1[compteur]+resultat;
			}
			resultat=0;
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

