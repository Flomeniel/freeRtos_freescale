/**
 * @file Accelerometre.h
 * @author
 * @brief fichier d'entete de l'accelerometre
 * @version v0.1
 *
 * @note
 * Dans ce fichier seront decrit toute les fonctions concernant
 * l'accelereometre ainsi qu'une breve documentation
 */
#ifndef	ACCELEROMETRE_H
#define	ACCELEROmetre_H

#include <stm32f4xx_conf.h>
#include <stm32f4xx.h>


#define	LoadDataLenght	3

void vAccelerometre_GPIO_SPI2_PC3_PC2(void);
void vAccelerometre_SPI(void);
void vAccelerometre_DMA(void);
void vAccelerometre_Init_ALL(void);
void vAccelerometre_IT_enable(void);

#endif
