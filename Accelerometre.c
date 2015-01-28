/**
 * @file Accelerometre.c
 * @author
 * @brief fichier de description des fonction de commande de l'accelerometre
 * @version v0.1
 *
 * @note
 * Dans ce fichier seront decrit toute les fonctions concernant
 * l'accelereometre ainsi qu'une breve documentation
 */

#include "Accelerometre.h"

void vAccelerometre_GPIO_SPI2_PC3_PC2(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/**
	 * @note MISO
	 */

	GPIO_InitTypeDef  GPIO_MISO_InitStructure;

	GPIO_MISO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
	GPIO_MISO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_MISO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_MISO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_MISO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOC, &GPIO_MISO_InitStructure);

	/**
	 * @note MOSI
	 */

	GPIO_InitTypeDef  GPIO_MOSI_InitStructure;

	GPIO_MOSI_InitStructure.GPIO_Pin   = GPIO_Pin_3;
	GPIO_MOSI_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_MOSI_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_MOSI_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_MOSI_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOC, &GPIO_MOSI_InitStructure);

	/**
	 * @noteSCK
	 */

	GPIO_InitTypeDef  GPIO_SCK_InitStructure;

	GPIO_SCK_InitStructure.GPIO_Pin   = GPIO_Pin_10;
	GPIO_SCK_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_SCK_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_SCK_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_SCK_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_SCK_InitStructure);

	/*
	 * @note NSS
	 */
	GPIO_InitTypeDef  GPIO_NSS_InitStructure;

	GPIO_NSS_InitStructure.GPIO_Pin   = GPIO_Pin_12;
	GPIO_NSS_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_NSS_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_NSS_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_NSS_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_NSS_InitStructure);
}

void vAccelerometre_SPI(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	SPI_InitTypeDef	SPI_Accelerometre_InitStructure;

	SPI_Accelerometre_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_Accelerometre_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_Accelerometre_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_Accelerometre_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_Accelerometre_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_Accelerometre_InitStructure.SPI_NSS = SPI_NSS_Hard;
	SPI_Accelerometre_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;  // Il faut faire  le calcul exat pour 5MHZ
	SPI_Accelerometre_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Accelerometre_InitStructure.SPI_CRCPolynomial = 0xFFFF;

	SPI_Init(SPI2, &SPI_Accelerometre_InitStructure);
}

void vAccelerometre_IT_enable(void)
{
	SPI_ITConfig(SPI2, SPI_IT_RXNE, ENABLE);
}

void vAccelerometre_DMA(void)
{
	RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_DMA1, ENABLE);

	DMA_InitTypeDef	DMA_Acceleromtre_InitStructure;

	DMA_Acceleromtre_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_Acceleromtre_InitStructure.DMA_PeripheralBaseAddr = SPI_DR_DR;
	//DMA_Acceleromtre_InitStructure.DMA_Memory0BaseAddr = DMA1_Stream3;
	DMA_Acceleromtre_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_Acceleromtre_InitStructure.DMA_BufferSize = 8;
	DMA_Acceleromtre_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_Acceleromtre_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_Acceleromtre_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_Acceleromtre_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_Acceleromtre_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_Acceleromtre_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_Acceleromtre_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
	DMA_Acceleromtre_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_Acceleromtre_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_Acceleromtre_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	DMA_Init(DMA1_Stream3, &DMA_Acceleromtre_InitStructure);

}

double integration_simson_methods(double data_to_integrate,double interval)
{
//	double
}

void vAccDataProcess(void)
{

}

void vAccelerometre_Init_ALL(void)
{
	vAccelerometre_GPIO_SPI2_PC3_PC2();
	vAccelerometre_SPI();
	vAccelerometre_DMA();
}
