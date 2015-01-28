#include "adc.h"

void vfiltrageNumerique(unsigned int *tab)
{
	unsigned char compteur;

		for(compteur=20; compteur<110; compteur++)
		{
			tab[compteur]=((tab[compteur-1]+tab[compteur]+tab[compteur+1])/3);
		}
}


void GPIO_Config_Camera_Adc1_PA1(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_StructInit(&GPIO_InitStructure);
  //for ADC1 on PC0 using IN10

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);				//
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  //for ADC1 on PC0 using IN10

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1 ;							//CHANGE
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void ADC1_CH1_Config_Camera(void)
{
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  ADC_InitTypeDef       ADC_InitStructure;

  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;

  ADC_CommonInit(&ADC_CommonInitStructure);

  ADC_InitStructure.ADC_Resolution = ADC_Resolution_6b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;


  ADC_StructInit(&ADC_InitStructure);

  ADC_Init(ADC1, &ADC_InitStructure);

  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_3Cycles);
  ADC_EOCOnEachRegularChannelCmd(ADC1, ENABLE);

  ADC_Cmd(ADC1, ENABLE);    //The ADC is powered on by setting the ADON bit in the ADC_CR2 register.
  //When the ADON bit is set for the first time, it wakes up the ADC from the Power-down mode.
}

void vBattery_GpioPA4_ADC2_CH4(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;

	  GPIO_StructInit(&GPIO_InitStructure);
	  //for ADC1 on PC0 using IN10

	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);

	  //for ADC1 on PC0 using IN10

		GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4 ;							//CHANGE
		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	  GPIO_Init(GPIOA, &GPIO_InitStructure);


	  ADC_CommonInitTypeDef ADC_CommonInitStructure;
	  ADC_InitTypeDef       ADC_InitStructure;

	  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;

	  ADC_CommonInit(&ADC_CommonInitStructure);

	  ADC_InitStructure.ADC_Resolution = ADC_Resolution_6b;
	  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	  ADC_InitStructure.ADC_NbrOfConversion = 1;


	  ADC_StructInit(&ADC_InitStructure);

	  ADC_Init(ADC1, &ADC_InitStructure);

	  ADC_RegularChannelConfig(ADC2, ADC_Channel_4, 1, ADC_SampleTime_3Cycles);
	  ADC_EOCOnEachRegularChannelCmd(ADC2, ENABLE);

	  ADC_Cmd(ADC2, ENABLE);    //The ADC is powered on by setting the ADON bit in the ADC_CR2 register.
	  //When the ADON bit is set for the first time, it wakes up the ADC from the Power-down mode.


}


