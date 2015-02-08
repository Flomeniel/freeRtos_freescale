/**
 * @author 	Souyri Clement
 * @file	PID.c
 * @date	29 Janvier	2015
 * @brief	Fichier decrivant le fonctionement du PID
 * @version	1.4
 *
 *
 * @Note	ce fichier contient le code de la fonction PID celle ci permet d'asservir
 * le servo moteur pour que celui-ci induise un minimum d'erreur
 */
#include "PID.h"

int erreur;
int somme_erreur;
int var_erreur;
int previous_error;
float commande;

void init_PID()
{
	PID_Servo.Kd = VAL_KD;
	PID_Servo.Ki = VAL_KI;
	PID_Servo.Kp = VAL_KP;
}

float	Calcul_PID(PID_s *PID,float mesure, unsigned char consigne)
{
	/*
	 * @note consigne correspond a la valeur de l'angle du servomoteur;
	 * 		 mesure correspond à la possition de la ligne;
	 */

	erreur = (64-consigne); //-mesure;
	//somme_erreur += erreur;
	//var_erreur = erreur + previous_error;
	commande = ((PID->Kp * erreur)+(PID->Ki * somme_erreur)+(PID->Kd * var_erreur));
	//previous_error = erreur;
	return commande;
}


