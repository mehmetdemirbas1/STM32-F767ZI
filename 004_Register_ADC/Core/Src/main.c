#include "main.h"
#include "string.h"

uint8_t adc_value; // adcmizi 8 bit olarak kullandığımız için 8 bitlik değer oluşturuyoruz
void RCC_Config()
{
	RCC->CR &=~(1 << 0);				// HSI' yı kapat
	RCC->CR |= (1 << 16);   			//HSE aktif et
	while( !(RCC->CR & (1 << 17)) );

	RCC->CR |=(1 << 19);

	RCC->PLLCFGR &= ~(32767 << 0);
	RCC->PLLCFGR |= (1 << 22);
	RCC->PLLCFGR |= (1 << 3);
	RCC->PLLCFGR |= (1 << 6);
	RCC->PLLCFGR |= (1 << 7);
	RCC->PLLCFGR &= ~(1 << 8);
	RCC->PLLCFGR |= (1 << 9);
	RCC->PLLCFGR |= (1 << 10);
	RCC->PLLCFGR &= ~(1 << 16);
	RCC->PLLCFGR &= ~(1 << 17);

	RCC->CR |= (1 << 24); 				// pll i aktif etmek için 1 yapıldı
	while( !(RCC->CR & (1 << 25)) );	// pll in aktif olması bekliyor

	RCC->CFGR &=~(1 << 0);
	RCC->CFGR |= (1 << 1);				// system clock olarak pll secildi
	while( !(RCC->CFGR & (1 << 1)) );
}
void GPIO_Config()
{
	RCC->AHB1ENR |= (1 << 0);			// GPIOA clock Aktif
	GPIOA->MODER |= 0x000000C0;			// GPIOA 3.pini analog mode olarak ayarladık
	GPIOA->OSPEEDR |=0x000000C0;		// GPIOA speed ayarını yaptık
}
void ADC_Config()
{
	RCC->APB2ENR |= (1 << 8);			// ADC1'in clock hattını aktif ettik

	ADC1->CR1 |= 0x02000000;			// Çözünürlüğü 8 bit olarak ayarladım
	ADC1->CR2 |= (1 << 0);				// ADC'yi aktif ettik
	ADC1->SMPR2 |= 0x00000600;			// Pinimize göre sample time registerını 56 cycle olarak ayarladık
	ADC->CCR |= 0x00010000;
}

uint8_t ADC_Read()
{
	uint8_t value=0;

	ADC1->CR2 |= 0x40000000;

	while(!(ADC1->SR & 0x00000002));
	value =ADC1->DR;

	return value;
}


int main(void)
{
 	RCC_Config();
	GPIO_Config();
	ADC_Config();
  while (1)
  {
	  adc_value = ADC_Read();
  }

}
