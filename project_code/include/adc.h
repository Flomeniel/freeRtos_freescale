#ifndef	ADC_H
#define ADC_H

#include <stm32f4xx_conf.h>
#include <stm32f4xx.h>

#include "interruption.h"
#include "camera.h"
#include "servo.h"

void GPIO_Config_Camera_Adc1_PA1(void);
void ADC1_CH1_Config_Camera(void);
void vfiltrageNumerique(unsigned int *tab);
void vBattery_GpioPA4_ADC2_CH4(void);

#endif
