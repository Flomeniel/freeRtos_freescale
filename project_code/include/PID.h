/**
 * @author 	Souyri Clement
 * @file	PID.h
 * @date	29 Janvier	2015
 * @brief	Fichier d'inclusion du PID
 * @version	1.4
 *
 *
 * @Note	ce fichier contient le code de la fonction PID celle ci permet d'asservir
 * le servo moteur pour que celui-ci induise un minimum d'erreur
 */
#ifndef	PID_H
#define	PID_H

#include <math.h>
#include <stm32f4xx_conf.h>
#include <stm32f4xx.h>
#include "Project_conf.h"

void init_PID(void);
float Calcul_PID(PID_s *PID,float mesure, unsigned char consigne);

#endif
