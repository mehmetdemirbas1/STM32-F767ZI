#include "main.h"
#include "string.h"


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

	RCC->AHB1ENR |= (1 << 1);
	RCC->AHB1ENR |= (1 << 2);

	GPIOB->MODER = 0x10004001;			// pin 14,7 ve 0 output oılarak ayarlandı (ledlerinj bağlı olduğu pinler)
	GPIOC->MODER = 0x00000000;
	GPIOB->OSPEEDR = 0x3000C003;

}

void EXTI_Config(void)
{
	RCC->APB2ENR |= (1 << 14);

	SYSCFG->EXTICR[0] =0x00000006;

	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);


	NVIC_SetPriority(EXTI0_IRQn,1);
	NVIC_SetPriority(EXTI1_IRQn,2);




	EXTI->IMR |= (1 << 0);
	EXTI->IMR |= (1 << 1);

	EXTI->RTSR |= (1 << 0);
	EXTI->RTSR |= (1 << 1);

}

void EXTI0_IRQHandler()
{
	if(EXTI->PR & 0x00000001)
	{
		GPIOB->ODR = 0x00004000;
		delay(2160000);
		EXTI->PR =(0x00000001);

	}


}
void EXTI1_IRQHandler()
{
	if(EXTI->PR & 0x00000002)
	{
		GPIOB->ODR = 0x00000080;
		delay(2160000);
		EXTI->PR =(0x00000002);

	}

}



int main(void)
{
	RCC_Config();
	GPIO_Config();
	EXTI_Config();


  while (1)
  {
	  GPIOB->ODR |= (1 << 14);
	  GPIOB->ODR |= (1 << 7);
	  GPIOB->ODR |= (1 << 0);

  }

}
