#include "main.h"
#include "string.h"

int i=0;
void delay(uint32_t time)
{
	while(time--);
}
void RCC_Config(void)
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

	RCC->CR |= (1 << 24); 			// pll i aktif etmek için 1 yapıldı
	while( !(RCC->CR & (1 << 25)) );// pll in aktif olması bekliyor

	RCC->CFGR &=~(1 << 0);
	RCC->CFGR |= (1 << 1);		// system clock olarak pll secildi
	while( !(RCC->CFGR & (1 << 1)) );
}

void DAC1_Config()
{
	RCC->AHB1ENR |= 0x00000001;
	RCC->APB1ENR |= 0x20000000;

	DAC->CR |= 0x00000001;
	DAC->SWTRIGR |= 0x00000000;
	DAC->DHR12R1 |= 0x00000000;
}


int main(void)
{
	RCC_Config();
	DAC1_Config();
  while (1)
  {
	  for(;i<4096;i++)
	  {
		  DAC->DHR12R1 =i;
		  delay(10000);
	  }
	  for(;i>0;i--)
	  {
		  DAC->DHR12R1 =i;
		  delay(10000);
	  }
  }

}
