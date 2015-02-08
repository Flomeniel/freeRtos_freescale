#ifndef	SERVO_H
#define	SERVO_H

#include <stm32f4xx_conf.h>
#include <stm32f4xx.h>

#include "Project_conf.h"
#include "interruption.h"
#include "camera.h"
#include "adc.h"

extern void servo_moteur(unsigned char delta);
void Timer3_CH1_PC6_servo(void);
void ServoMoteur(void * pvParameters);
void ServoMoteur2(void);
void vServo_Timer11_CH1_PB9(void);

#endif
