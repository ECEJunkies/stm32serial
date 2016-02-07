#include "stm32l476xx.h"
#include "lcd.h"
#include "serial.h"

/*
void System_Clock_Init(void);
void LCD_Initialization(void); // Mixing underscores and Camel / Title case is bad practice, btw.
void LCD_Clear(void);
void LCD_Display_NAme(char *name);
void LCD_PIN_Init(void);
*/

int main(void){
	LCD_Initialization();
	LCD_Clear();
	LCD_Display_Name();
	//LCD_DisplayString((uint8_t*)"ECE271");
	LCD_bar();
	
	//serial_init();
	//sputs("Testing\r\n");
	
	while(1);
}

void System_Clock_Init(void){
	
	// Enable High Speed Internal Clock (HSI = 16 MHz)
  RCC->CR |= ((uint32_t)RCC_CR_HSION);
	
  // wait until HSI is ready
  while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 );
	
  // Select HSI as system clock source 
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
  RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;  //01: HSI16 oscillator used as system clock

  // Wait till HSI is used as system clock source 
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 );
		
}
