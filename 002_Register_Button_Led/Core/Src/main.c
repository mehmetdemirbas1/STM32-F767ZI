#include "main.h"
#include "string.h"



int count = 0;

void delay(uint32_t time)
{
	while(time--);
}

void RCC_Config(void)
{
	//RCC->CR &=0x00000083;			//Registerı Sıfırladık

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

void GPIO_Config(void)
{

	RCC->AHB1ENR |= (1 << 1);					// GPIOB aktif
	RCC->AHB1ENR |= (1 << 2);					// GPIOC aktif

	// Pin 13 için (BUTTON)

	// Pin 14 için (LED)
	GPIOB->MODER &= ~(3 << 28); 			    // Pin 14 temizle
	GPIOB->MODER |= (1 << 28);   				// Pin 14 output

	// Pin 7 için (LED)
	GPIOB->MODER &= ~(3 << 14);  				// Pin 7 temizle
	GPIOB->MODER |= (1 << 14);   				// Pin 7 output

	// Pin 0 için (LED)
	GPIOB->MODER &= ~(3 << 0);   				// Pin 0 temizle
	GPIOB->MODER |= (1 << 0);    				// Pin 0 output
	GPIOB->OSPEEDR |= 0xFFFFFFFF;


}


int main(void)
{
	RCC_Config();
	SystemCoreClockUpdate();
	GPIO_Config();
  while (1)
  {
	  if(GPIOC->IDR & 0x00002000)
	  {

		  delay(2160000);
		  count++;
	  }
	  if(count%2==0){
		    GPIOB->ODR |= (1 << 14);  				// Pin 14 toggle
		    GPIOB->ODR |= (1 << 7);   				// Pin 7 toggle
		    GPIOB->ODR |= (1 << 0);   				// Pin 0 toggle
	  }
	  else{
		    GPIOB->ODR &= ~(1 << 14);  				// Pin 14 toggle
		    GPIOB->ODR &= ~(1 << 7);   				// Pin 7 toggle
		    GPIOB->ODR &= ~(1 << 0);   				// Pin 0 toggle
	  }


  }

}
