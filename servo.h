#ifndef	SERVO_H
#define	SERVO_H

#include <stm32f4xx_conf.h>
#include <stm32f4xx.h>
#include "interruption.h"
#include "camera.h"
#include "adc.h"

extern void servo_moteur(unsigned char delta);
void Timer3_CH1_PC6_servo();
void ServoMoteur();

#endif
