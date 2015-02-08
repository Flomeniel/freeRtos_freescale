#ifndef	PROJECT_CONF_H
#define	PROJECT_CONF_H

/**
 * @brief	Configuration des prioritee
 */

#define	PRIORITE_NIVEAU_1	(tskIDLE_PRIORITY + 1)
#define	PRIORITE_NIVEAU_2	(tskIDLE_PRIORITY + 2)
#define	PRIORITE_NIVEAU_3	(tskIDLE_PRIORITY + 3)

/**
 * @	brief	Configuration rapide pour les test
 */

#define	REGLAGE_VITESSE_PROPULTION				35
#define	REGLAGE_VITESSE_ROTATION_SERVOMOTEUR	150
#define	TAILLE_REGISTRE_CAMERA					108
#define RAPPORT_CYCLIQUE_MILIEU					150
#define INDEX_DONNEE_UTILE_DEBUT				20//30
#define ORDONNEE_ORIGINE						157			//Normale 113.206		//PID	157
#define COEFF_DIRECTEUR							0.69			//Normale 0.689		//PID	0.69
#define	VALEUR_MAX_SATURATION_CAMERA			3000
#define	VITESSE_PROPULTION						33
#define	ARRET_PROPULTION						0
#define	DETECTION_LIGNE_ARRIVEE_NIVEAU_HAUT		220000
#define	DETECTION_LIGNE_ARRIVEE_NIVEAU_BAS		200000

#define	VAL_KD	0
#define	VAL_KI	0
#define	VAL_KP	1


/**
 * @brief declaration de Typedef
 */

typedef	struct{

		float	Kp;
		float	Ki;
		float	Kd;

}PID_s;

/**
 * @brief	Declaration des structures
 */

PID_s PID_Servo;

#endif
