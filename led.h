#ifndef	LED_H
#define	LED_H

#include <stm32f4xx_conf.h>
#include <stm32f4xx.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>


void vLedCamera_Timer2_CH4_PB11();
void vLedBattery_GpioPD0134();
void DiodeDeTest();
void BarGraph();

#endif
