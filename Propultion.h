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

unsigned char Calcul_Vitesse_Propultion();
void Changer_vitesse_moteur(unsigned char delta);
void propultion_Gauche(unsigned char delta);
void propultion_Droit(unsigned char delta);
void vmoteur_G_Timer3_CH1_PC6(void);
void vmoteur_D_Timer3_CH2_PC7(void);
