#include "main.h"
#include "string.h"

uint16_t count;

void RCC_Config(void)
{


	RCC->CR &=~(1 << 0);				// HSI' yı kapat
	RCC->CR |= (1 << 16);   			//HSE aktif et
	while( !(RCC->CR & (1 << 17)) );
	RCC->CR |= (1 << 19);
	RCC->CR |= 0x01000000;

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
	RCC->CFGR &=~(1 << 0);
	RCC->CFGR |= (1 << 1);
	RCC->CIR |= 0x00080000;
	RCC->CIR |= 0x00800000;

}

void Timer_Config(void)
{
	RCC->APB1ENR |=0x00000001;   	//Timer 2 clock aktif edildi

	TIM2->CR1 &= ~(1 << 4);
	TIM2->CR1 &= ~(1 << 5);
	TIM2->CR1 &= ~(1 << 8);
	TIM2->SMCR &= ~(1 << 0);
	TIM2->EGR |= (1 << 0);
	TIM2->PSC = 41999;
	TIM2->ARR = 4000;

	TIM2->CR1 |= (1 << 0);				// Timer 2 counter aktif


}

int main(void)
{
	RCC_Config();
	Timer_Config();
  while (1)
  {
	  count= TIM2->CNT;
  }

}
