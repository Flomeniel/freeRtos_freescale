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

	RCC_AHB1PeriphClockCmd(ADXL345_SPI_SCK_GPIO_CLK | ADXL345_SPI_NSS_GPIO_CLK | ADXL345_SPI_INT1_GPIO_CLK | ADXL345_SPI_INT2_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(ADXL345_SPI_MISO_GPIO_CLK | ADXL345_SPI_MOSI_GPIO_CLK, ENABLE);

	GPIO_PinAFConfig(ADXL345_SPI_SCK_GPIO_PORT, ADXL345_SPI_SCK_SOURCE, ADXL345_SPI_SCK_AF);
	GPIO_PinAFConfig(ADXL345_SPI_MISO_GPIO_PORT, ADXL345_SPI_MISO_SOURCE, ADXL345_SPI_MISO_AF);
	GPIO_PinAFConfig(ADXL345_SPI_MOSI_GPIO_PORT, ADXL345_SPI_MOSI_SOURCE, ADXL345_SPI_MOSI_AF);

	/**
	* @noteSCK
	*/

	GPIO_InitTypeDef  GPIO_SCK_InitStructure;

	GPIO_SCK_InitStructure.GPIO_Pin   = ADXL345_SPI_SCK_PIN;
	GPIO_SCK_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_SCK_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_SCK_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_SCK_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(ADXL345_SPI_SCK_GPIO_PORT, &GPIO_SCK_InitStructure);

	/**
	 * @note MISO
	 */

	GPIO_InitTypeDef  GPIO_MISO_InitStructure;

	GPIO_MISO_InitStructure.GPIO_Pin   = ADXL345_SPI_MISO_PIN;
	GPIO_MISO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_MISO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_MISO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_MISO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(ADXL345_SPI_MISO_GPIO_PORT, &GPIO_MISO_InitStructure);

	/**
	 * @note MOSI
	 */

	GPIO_InitTypeDef  GPIO_MOSI_InitStructure;

	GPIO_MOSI_InitStructure.GPIO_Pin   = ADXL345_SPI_MOSI_PIN;
	GPIO_MOSI_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_MOSI_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_MOSI_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_MOSI_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(ADXL345_SPI_MOSI_GPIO_PORT, &GPIO_MOSI_InitStructure);

	/*
	 * @note NSS
	 */
	GPIO_InitTypeDef  GPIO_NSS_InitStructure;

	GPIO_NSS_InitStructure.GPIO_Pin   = ADXL345_SPI_NSS_PIN;
	GPIO_NSS_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_NSS_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_NSS_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(ADXL345_SPI_NSS_GPIO_PORT, &GPIO_NSS_InitStructure);

	/*
	 * 	@note	INT1
	 */

	GPIO_InitTypeDef	GPIO_INT1_InitStructure;

	GPIO_INT1_InitStructure.GPIO_Pin	= ADXL345_SPI_INT1_PIN;
	GPIO_INT1_InitStructure.GPIO_Mode	= GPIO_Mode_IN;
	GPIO_INT1_InitStructure.GPIO_OType	= GPIO_OType_PP;
	GPIO_INT1_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;
	GPIO_INT1_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;

	GPIO_Init(ADXL345_SPI_INT1_GPIO_PORT, &GPIO_INT1_InitStructure);

	/*
	 * 	@note	INT2
	 */

	GPIO_InitTypeDef	GPIO_INT2_InitStructure;

	GPIO_INT2_InitStructure.GPIO_Pin	= ADXL345_SPI_INT2_PIN;
	GPIO_INT2_InitStructure.GPIO_Mode	= GPIO_Mode_IN;
	GPIO_INT2_InitStructure.GPIO_OType	= GPIO_OType_PP;
	GPIO_INT2_InitStructure.GPIO_Speed	= GPIO_Speed_100MHz;
	GPIO_INT2_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;

	GPIO_Init(ADXL345_SPI_INT2_GPIO_PORT, &GPIO_INT2_InitStructure);

}

void vAccelerometre_SPI(void)
{
	RCC_APB2PeriphClockCmd(ADXL345_SPI_CLK, ENABLE);

	SPI_InitTypeDef	SPI_Accelerometre_InitStructure;

	SPI_Accelerometre_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_Accelerometre_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_Accelerometre_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_Accelerometre_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_Accelerometre_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_Accelerometre_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_Accelerometre_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;  // Il faut faire  le calcul exat pour 5MHZ
	SPI_Accelerometre_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;

	SPI_Init(ADXL345_SPI, &SPI_Accelerometre_InitStructure);

	SPI_Cmd(ADXL345_SPI, ENABLE);
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

char vAccDataSend(unsigned char data)
{

	while (SPI_GetFlagStatus(ADXL345_SPI, SPI_FLAG_TXE) == RESET)
	{

	}

	SPI_SendData(ADXL345_SPI, data);

	while (SPI_GetFlagStatus(ADXL345_SPI, SPI_FLAG_RXNE) == RESET)
	{

	}

	return	(char)SPI_I2S_ReceiveData(ADXL345_SPI);
}

void vAccDataDoubleSend(unsigned char data1, unsigned data2)
{
	while (SPI_GetFlagStatus(ADXL345_SPI, SPI_FLAG_TXE) == RESET)
	{

	}

	SPI_SendData(ADXL345_SPI, data1);

	while (SPI_GetFlagStatus(ADXL345_SPI, SPI_FLAG_TXE) == RESET)
	{

	}

	SPI_SendData(ADXL345_SPI, data2);
}

void vAccelerometre_Init_ALL(void)
{
	vAccelerometre_GPIO_SPI2_PC3_PC2();
	vAccelerometre_SPI();
	//vAccelerometre_DMA();
	//vAccDataDoubleSend(ADXL345_INT_MAP_REG,ADXL345_INT_DATAREADY);

}
