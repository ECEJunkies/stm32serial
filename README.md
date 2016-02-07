# stm32serial
USART2 support for serial debugging (STM32L476VG)

Using this code
---------------

Simple. Add serial.h and serial.c to your keil project and print to erial port like so:

	#include "serial.h"

	int main(void) {
	  serial_init();
	  sputs("This is a string for your serial port!\r\n");
	  //sputc("A"); // You can also print one character
	}

Information
-----------

This is for USART2, The pinout is as follows:
PA2 = TX. Connect your receieve wire here.
PA3 = RX. transmit wire of serial cable goes here

Settings? 9600 baud, 8 data bits, 1 stop bits. (9600 8N1)

TODO
----
Recieve doesn't work yet, and its' IRQ is disabled.
