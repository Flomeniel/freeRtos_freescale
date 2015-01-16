
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

#define INDEX_DONNEE_UTILE_DEBUT		30
#define RAPPORT_CYCLIQUE_MILIEU			90
#define ORDONNEE_ORIGINE				59
#define COEFF_DIRECTEUR					0.55
#define BATTERY_TASK_PRIO	(tskIDLE_PRIORITY + 1)
#define SI_TASK_PRIO		(tskIDLE_PRIORITY + 2)
#define ADC_TASK_PRIO		(tskIDLE_PRIORITY + 2)
#define SERVO_TASK_PRIO		(tskIDLE_PRIORITY + 3)

unsigned char ucCompteur=0;
unsigned char compteurtest=0;
unsigned int ADCResult1[128];

xSemaphoreHandle xSemaphoreADC = NULL;
xSemaphoreHandle xSemaphoreSI = NULL;
xSemaphoreHandle xSemaphoreNotSI = NULL;
xSemaphoreHandle xSemaphoreSERVO = NULL;

static signed portBASE_TYPE xHigherPriorityTaskWoken;




void vApplicationIdleHook(void){

	__WFI();
}

void ServoMoteur(void * pvParameters)
{
	for(;;)
	{
		if( xSemaphoreTake( xSemaphoreSERVO, portMAX_DELAY ) == pdTRUE )
		{
					servo_moteur_test(&ADCResult1);
		}
	}
}
void BarGraph(void * pvParameters)
{
	uint16_t	uiNiveauBattery;
	for(;;)
	{
		ADC_SoftwareStartConv(ADC2);
		uiNiveauBattery= ADC_GetConversionValue(ADC2);

		if(uiNiveauBattery<2000)
		{
			GPIO_SetBits(GPIOD,GPIO_Pin_0);
			GPIO_SetBits(GPIOD,GPIO_Pin_1);
			GPIO_SetBits(GPIOD,GPIO_Pin_3);
			GPIO_SetBits(GPIOD,GPIO_Pin_4);
		}

		if(uiNiveauBattery<1300);
		{
			GPIO_SetBits(GPIOD,GPIO_Pin_0);
			GPIO_SetBits(GPIOD,GPIO_Pin_1);
			GPIO_SetBits(GPIOD,GPIO_Pin_3);
			GPIO_ResetBits(GPIOD,GPIO_Pin_4);
		}
		if(uiNiveauBattery<800);
		{
			GPIO_SetBits(GPIOD,GPIO_Pin_0);
			GPIO_SetBits(GPIOD,GPIO_Pin_1);
			GPIO_ResetBits(GPIOD,GPIO_Pin_3);
			GPIO_ResetBits(GPIOD,GPIO_Pin_4);
		}
		if(uiNiveauBattery<300);
		{
			GPIO_SetBits(GPIOD,GPIO_Pin_0);
			GPIO_ResetBits(GPIOD,GPIO_Pin_1);
			GPIO_ResetBits(GPIOD,GPIO_Pin_3);
			GPIO_ResetBits(GPIOD,GPIO_Pin_4);
		}
	}
}
int main(void)
{
	vSemaphoreCreateBinary( xSemaphoreADC );
	vSemaphoreCreateBinary( xSemaphoreSI );
	vSemaphoreCreateBinary( xSemaphoreNotSI );
	vSemaphoreCreateBinary( xSemaphoreSERVO );

	SystemInit();
	SystemCoreClockUpdate();

	/*************Initialisation***************/
		GPIO_Config_Camera_Adc1_PA1();
		ADC1_CH1_Config_Camera();

		vLedCamera_Timer2_CH4_PB11();
		vClockCamera_Timer4_CH1_PB6();

		vBattery_GpioPA4_ADC2_CH4();
		vLedBattery_GpioPD0134();
		vSICameraGpio_PB7();
		vServo_Timer3_CH1_PC6();

	//	DiodeDeTest();

		EXTILine6_Config_PB6();


	xTaskCreate( SIcamera,		(signed char*)"SI",			configMINIMAL_STACK_SIZE, 	NULL, SI_TASK_PRIO, 		NULL);
	xTaskCreate( AoAdc,			(signed char*)"AO", 		configMINIMAL_STACK_SIZE, 	NULL, ADC_TASK_PRIO, 		NULL);
	xTaskCreate( ServoMoteur,	(signed char*)"SERVO", 		configMINIMAL_STACK_SIZE, 	NULL, SERVO_TASK_PRIO,		NULL);
	xTaskCreate( BarGraph,		(signed char*)"BATTERY",	configMINIMAL_STACK_SIZE,	NULL, BATTERY_TASK_PRIO,	NULL);

	vTaskStartScheduler();

	while(1)
	{
	}
}
void EXTI9_5_IRQHandler(void)
{

	if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	{
		ucCompteur++;
		xHigherPriorityTaskWoken = pdFALSE;

		xSemaphoreGiveFromISR( xSemaphoreADC, xHigherPriorityTaskWoken );

		if(ucCompteur == 127)
		{
			xSemaphoreGiveFromISR( xSemaphoreSI, xHigherPriorityTaskWoken );
		}

		if(ucCompteur == 128)
		{
			xSemaphoreGiveFromISR( xSemaphoreNotSI, xHigherPriorityTaskWoken );
		}

			ADC_SoftwareStartConv(ADC1);
			ADCResult1[ucCompteur]= ADC_GetConversionValue(ADC1);

		portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
}

void SIcamera(void * pvParameters)
{
	for(;;)
	{
		if( xSemaphoreTake( xSemaphoreSI, portMAX_DELAY ) == pdTRUE )
		{
				GPIO_SetBits(GPIOB, GPIO_Pin_7);
				xSemaphoreGive(xSemaphoreSERVO);
		}

		if( xSemaphoreTake( xSemaphoreNotSI, portMAX_DELAY ) == pdTRUE )
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			ucCompteur=0;
		}
	}
}


void AoAdc(void * pvParameters)
{
	for(;;)
	{
		if( xSemaphoreTake( xSemaphoreADC, portMAX_DELAY ) == pdTRUE )
		{

		}
	}
}

void servo_moteur_test(unsigned int *ADCResult)
{
	static float			a							= COEFF_DIRECTEUR;
	static unsigned char	b							= ORDONNEE_ORIGINE;
	static unsigned char	ucRapportCycliquePrecedent	= RAPPORT_CYCLIQUE_MILIEU;

	unsigned char			uiIndexLigneNoir			= 0;
	unsigned char			index						= INDEX_DONNEE_UTILE_DEBUT;
	unsigned char			sucRapportCyclique			= RAPPORT_CYCLIQUE_MILIEU;

	vfiltrageNumerique(ADCResult);
	vfiltrageNumerique(ADCResult);
	vfiltrageNumerique(ADCResult);
	vfiltrageNumerique(ADCResult);
	do
	{
		if(ADCResult[index]<400)
		{
		//	if( (ADCResult[index]+ADCResult[index+1]+ADCResult[index+2]+ ADCResult[index+3]+ADCResult[index+4]+ADCResult[index+5]+ADCResult[index+6] ) < (ADCResult[index+7]+ADCResult[index+8]+ADCResult[index+9]+ADCResult[index+10]+ADCResult[index+11]+ADCResult[index+12]+ADCResult[index+13] ))
		//	{
				uiIndexLigneNoir=index;
		//	}
		}

		index++;
	}while(uiIndexLigneNoir==0 && index <= 110);

	sucRapportCyclique=((unsigned char)(uiIndexLigneNoir*a))+b;

	if(sucRapportCyclique < ucRapportCycliquePrecedent-10 || sucRapportCyclique > ucRapportCycliquePrecedent+10)
	{

	}else
	{
		servo_moteur(sucRapportCyclique);			//60-120
		ucRapportCycliquePrecedent=sucRapportCyclique;
	}
	/*if(sucRapportCyclique > ucRapportCycliquePrecedent-10 || sucRapportCyclique < ucRapportCycliquePrecedent+10)
		{
		servo_moteur(sucRapportCyclique);			//60-120
		ucRapportCycliquePrecedent=sucRapportCyclique;
		}else
		{

		}*/
}

