#include "msp.h"
#include "delay_us.h"

/*
 * LCD.h
 *
 *  Created on: Apr 12, 2019
 *      Author: Daniel Gutmann
 */

#ifndef LCD_H_
#define LCD_H_

#define ENABLE  ((uint8_t)0x02) //enable pin
#define DISABLE ((uint8_t)0xFD)
#define RS      ((uint8_t)0x04) //RS pin
#define RW      ((uint8_t)0x01) //RW pin
#define DELAY   100

void init_LCD(uint8_t modeDispCTL); //mode_dispCTL: MSB(1,D,C,B,N,F,x,x)LSB (8bits)
void Clear_LCD();
void Home_LCD();
void Write_String_LCD(char* string, uint8_t startAddress);

#endif /* LCD_H_ */
