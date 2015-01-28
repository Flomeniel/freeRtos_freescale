#ifndef CAMERA_H
#define	CAMERA_H

#include <stm32f4xx_conf.h>
#include <stm32f4xx.h>
#include "interruption.h"
#include "adc.h"
#include "servo.h"

#define INDEX_DONNEE_UTILE_DEBUT		30
#define RAPPORT_CYCLIQUE_MILIEU			90
#define ORDONNEE_ORIGINE				59
#define COEFF_DIRECTEUR					0.55

extern unsigned char ucCompteur;

extern void SIcamera(void * pvParameters);
void vClockCamera_Timer4_CH1_PB6();
void vSICameraGpio_PB7();
void vTraitementLigne();

#endif
