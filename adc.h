#ifndef	ADC_H
#define	ADC_H

#include <stm32f4xx_conf.h>
#include <stm32f4xx.h>
#include "interruption.h"
#include "camera.h"
#include "servo.h"

//extern unsigned int ADCResult[128];

extern void AoAdc(void * pvParameters);
extern void GPIO_Config_Camera_Adc1_PA1();
extern void ADC1_CH1_Config_Camera(void);
extern void vfiltrageNumerique(unsigned int *tab);

#endif
