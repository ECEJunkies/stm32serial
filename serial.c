#include "stm32l476xx.h"
#include "serial.h"

// This code works only for USART2

void _gpio_init(void) {
	
	GPIOA->MODER  &= 0xFFFFFF0F;
	GPIOA->MODER  |= 0x000000A0;
	GPIOA->PUPDR  &= 0xFFFFFF0F;
	GPIOA->OTYPER &= 0xFFFFFFF0;
	GPIOA->OTYPER |= 0x00000008;
	GPIOA->AFR[0] &= 0xFFFF00FF;
	GPIOA->AFR[0] |= 0x00007700;
}

void _rcc_init(void) {
	
	RCC->CR |= RCC_CR_HSION;
	while( (RCC->CR & RCC_CR_HSIRDY) == 0);
	RCC->CFGR &= ~RCC_CFGR_SW_HSI;
	RCC->CFGR |= RCC_CFGR_SW_HSI;
	while ( (RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI );
	
	RCC->AHB2ENR  |= RCC_AHB2ENR_GPIOAEN;
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN; // Enable USART2 clock
}

void serial_init(void) {
	_rcc_init();
	_gpio_init();
	
		USART2->CR1 &= ~USART_CR1_M;     // 1 start bit, 8 data bits
	USART2->CR1 &= ~USART_CR1_OVER8; // oversampling is 16
	USART2->CR2 &= ~USART_CR2_STOP;  //  1 stop bit
	USART2->BRR  = 0x683;            // 9600 baud
	USART2->CR1 |= (USART_CR1_RE | USART_CR1_TE);
	
	USART2->CR1 |= USART_CR1_UE;     // Enable USART2
	//USART2->CR1 |= USART_CR1_RXNEIE; // Enable USART2 RX Interrupts 
}

void sputc(const char chr) {

	while ( !(USART2->ISR & USART_ISR_TXE ));
	USART2->TDR = (chr & 0x1FF); // Bits 31-9 must remain reserved!
	while ( !(USART2->ISR & USART_ISR_TC  ));
	//USART2->ISR &= ~USART_ISR_TC; // Datasheet hints this may not be necessary..
}

void sputs(const char *str) {
	while (*str != '\0') {
		sputc(*str);
		str++;
	}
}
