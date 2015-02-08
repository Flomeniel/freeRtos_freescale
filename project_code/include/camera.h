#ifndef	CAMERA_H
#define	CAMERA_H

#include <stm32f4xx_conf.h>
#include <stm32f4xx.h>
#include <math.h>

#include "Project_Conf.h"
#include "Propultion.h"
#include "PID.h"
#include "interruption.h"

extern unsigned char ucCompteur;


extern void SIcamera(void * pvParameters);
void vClockCamera_Timer4_CH1_PB6(void);
void vSICameraGpio_PB7(void);
void vTraitementLigne(unsigned int *ADCResult);
void vSICameraGpio_PE0(void);

#endif
