#include "msp.h"
#include "LCD.h"
#include <string.h>


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	init_LCD(0xFF); //MSB(1,D,C,B,N,F,x,x)LSB (8bits)

	char* asnmt3 = " Assignment 3";
	uint8_t startAddress = 0x00;
	Write_String_LCD(asnmt3, startAddress);

	char* helloWorld = "Hello World";
	startAddress = 0x40;
	Write_String_LCD(helloWorld, startAddress);

	Home_LCD();

	while(1);
}
