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

/**
 * 	@brief Interface SPI ADXL345
 */

#define	ADXL345_SPI						SPI2
#define	ADXL345_SPI_CLK					RCC_APB1Periph_SPI2

#define	ADXL345_SPI_SCK_PIN				GPIO_Pin_10
#define	ADXL345_SPI_SCK_GPIO_PORT		GPIOD
#define	ADXL345_SPI_SCK_GPIO_CLK		RCC_AHB1Periph_GPIOD
#define	ADXL345_SPI_SCK_SOURCE			GPIO_PinSource10
#define	ADXL345_SPI_SCK_AF				GPIO_AF_SPI1

#define	ADXL345_SPI_MISO_PIN			GPIO_Pin_2
#define	ADXL345_SPI_MISO_GPIO_PORT		GPIOC
#define	ADXL345_SPI_MISO_GPIO_CLK		RCC_AHB1Periph_GPIOC
#define	ADXL345_SPI_MISO_SOURCE			GPIO_PinSource2
#define	ADXL345_SPI_MISO_AF				GPIO_AF_SPI1

#define	ADXL345_SPI_MOSI_PIN			GPIO_Pin_3
#define	ADXL345_SPI_MOSI_GPIO_PORT		GPIOC
#define	ADXL345_SPI_MOSI_GPIO_CLK		RCC_AHB1Periph_GPIOC
#define	ADXL345_SPI_MOSI_SOURCE			GPIO_PinSource3
#define	ADXL345_SPI_MOSI_AF				GPIO_AF_SPI1

#define	ADXL345_SPI_NSS_PIN				GPIO_Pin_12
#define	ADXL345_SPI_NSS_GPIO_PORT		GPIOD
#define	ADXL345_SPI_NSS_GPIO_CLK		RCC_AHB1Periph_GPIOD

#define ADXL345_SPI_INT1_PIN			GPIO_Pin_8
#define	ADXL345_SPI_INT1_GPIO_PORT		GPIOD
#define	ADXL345_SPI_INT1_GPIO_CLK		RCC_AHB1Periph_GPIOD
#define	ADXL345_SPI_INT1_LINE			EXTI_Line8
#define	ADXL345_SPI_INT1_PORT_SOURCE	EXTI_PortSourceGPIOD
#define	ADXL345_SPI_INT1_PIN_SOURCE		EXTI_PinSource8
#define	ADXL345_SPI_INT1_EXTI_IRQn		EXTI8_IRQn

#define ADXL345_SPI_INT2_PIN			GPIO_Pin_9
#define	ADXL345_SPI_INT2_GPIO_PORT		GPIOD
#define	ADXL345_SPI_INT2_GPIO_CLK		RCC_AHB1Periph_GPIOD
#define	ADXL345_SPI_INT2_LINE			EXTI_Line9
#define	ADXL345_SPI_INT2_PORT_SOURCE	EXTI_PortSourceGPIOD
#define	ADXL345_SPI_INT2_PIN_SOURCE		EXTI_PinSource9
#define	ADXL345_SPI_INT2_EXTI_IRQn		EXTI9_IRQn

/**
 * 	@brief Adresse des Registre de l'ADXL345
 */

#define ADXL345_DEVID_REG          0x00
#define ADXL345_THRESH_TAP_REG     0x1D
#define ADXL345_OFSX_REG           0x1E
#define ADXL345_OFSY_REG           0x1F
#define ADXL345_OFSZ_REG           0x20
#define ADXL345_DUR_REG            0x21
#define ADXL345_LATENT_REG         0x22
#define ADXL345_WINDOW_REG         0x23
#define ADXL345_THRESH_ACT_REG     0x24
#define ADXL345_THRESH_INACT_REG   0x25
#define ADXL345_TIME_INACT_REG     0x26
#define ADXL345_ACT_INACT_CTL_REG  0x27
#define ADXL345_THRESH_FF_REG      0x28
#define ADXL345_TIME_FF_REG        0x29
#define ADXL345_TAP_AXES_REG       0x2A
#define ADXL345_ACT_TAP_STATUS_REG 0x2B
#define ADXL345_BW_RATE_REG        0x2C
#define ADXL345_POWER_CTL_REG      0x2D
#define ADXL345_INT_ENABLE_REG     0x2E
#define ADXL345_INT_MAP_REG        0x2F
#define ADXL345_INT_SOURCE_REG     0x30
#define ADXL345_DATA_FORMAT_REG    0x31
#define ADXL345_DATAX0_REG         0x32
#define ADXL345_DATAX1_REG         0x33
#define ADXL345_DATAY0_REG         0x34
#define ADXL345_DATAY1_REG         0x35
#define ADXL345_DATAZ0_REG         0x36
#define ADXL345_DATAZ1_REG         0x37
#define ADXL345_FIFO_CTL           0x38
#define ADXL345_FIFO_STATUS        0x39


/**
 * 	@brief commande ADXL345
 */

#define ADXL345_SPI_READ    0x80
#define ADXL345_SPI_WRITE   0x00

/**
 * 	@brief	Interuption ADXL345
 */

#define ADXL345_INT_DISABLE 0X00 // used for disabling interrupts
#define ADXL345_INT_OVERRUN 0X01
#define ADXL345_INT_WATERMARK 0X02
#define ADXL345_INT_FREEFALL 0X04
#define ADXL345_INT_INACTIVITY 0X08
#define ADXL345_INT_ACTIVITY 0X10
#define ADXL345_INT_DOUBLETAP 0X20
#define ADXL345_INT_TAP 0X40
#define ADXL345_INT_DATAREADY 0X80

#define	LoadDataLenght	3

void Accelerometre(void * pvParameters);
void vAccelerometre_GPIO_SPI2_PC3_PC2(void);
void vAccelerometre_SPI(void);
void vAccelerometre_DMA(void);
void vAccelerometre_Init_ALL(void);
void vAccelerometre_IT_enable(void);
char vAccDataSend(unsigned char data);

#endif
