/**
 * 	@file Propultion.h
 * 	@brief	Programme de gestion moteurs arriere
 * 	@author Souyri clement
 * 	@version v1.2
 * 	@date 19 janvier 2015
 *
 *	@note
 * 	Fichier d'entête de Propultion.c
 *
 */
#ifndef	PROPULTION_H
#define	PROPULTION_H

#include <stm32f4xx_conf.h>
#include <stm32f4xx.h>

#include "Project_conf.h"

extern unsigned char Calcul_Vitesse_Propultion(unsigned char rapport_cyclique_servo);
extern void Changer_vitesse_moteur(unsigned char delta);
void propultion_Gauche(unsigned char delta);
void propultion_Droit(unsigned char delta);
void vmoteur_G_Timer3_CH1_PC6(void);
void vmoteur_D_Timer3_CH2_PC7(void);
void vEnableMoteur_GPIO_PE2(void);
void recule_Gauche(unsigned char delta);
void recule_Droit(unsigned char delta);

#endif
