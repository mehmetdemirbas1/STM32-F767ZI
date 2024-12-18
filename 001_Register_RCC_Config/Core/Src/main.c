
#include "main.h"
#include "string.h"



extern uint32_t SystemCoreClock;

uint32_t systemClock=0;

void RCC_Config()
{
	RCC->CR |= 0x00010000;			// HSE aktif et
	while(!(RCC->CR & 0x00020000));	// HSE bayragini bekle
	RCC->CR |= 0x00080000;			// CSS ON

	RCC->PLLCFGR = 0x00000000;	// PLL registerını clearla
	RCC->PLLCFGR |= (1 << 22);		// PLL HSE olarak ayarla
	RCC->PLLCFGR |= (4 << 0);		// PLL m değerini 4 olarak ayarla
	RCC->PLLCFGR |= (216 << 6);		// PLL n değerini 216 olarak ayarla

	RCC->CR |= (1 << 24);			// PLL'i aktif et
	while(!(RCC->CR & 0x02000000));	// PLL'in aktif olmasını bekle

	RCC->CFGR &= ~(1 << 0);
	RCC->CFGR |= ( 1 << 1);
	while(!(RCC->CFGR & (1 << 1)));
}


int main(void)
{
	systemClock = SystemCoreClock;

	RCC_Config();

	SystemCoreClockUpdate();

	systemClock = SystemCoreClock;



  while (1)
  {

  }

}
