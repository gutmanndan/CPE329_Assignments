#include "LCD.h"
#include <string.h>

/*
 * LCD.c
 *
 *  Created on: Apr 10, 2019
 *      Author: Daniel Gutmann
 */

//Functions only accessible in LCD.c
void Write_Byte(uint8_t data, uint8_t rsrw); //data: (8bits), rsrw: MSB(x,x,x,x,x,x,rs,rw)LSB (8bits)
void Set_Entry_Mode(uint8_t entryMode);
void Set_CGRAM(uint8_t address);
void Set_DDRAM(uint8_t address);
void wait_Busy_Flag();

void init_LCD(uint8_t modeDispCTL)  //MSB(1,D,C,B,N,F,x,x)LSB (8bits)
{
    P4-> SEL0 = 0;
    P4-> SEL1 = 0;
    P4-> DIR = 0xFF; //set ports to output
    P4-> OUT = 0x00; //Clear ports
    //delay_us(50000); //Power On delay

    //First initialization
    float shortDelay = 1;
    P4-> OUT |= 0x30;
    P4-> OUT |= ENABLE;
    shortDelay ++;
    P4-> OUT &= DISABLE;
    delay_us(100);

    //Set number of lines and font
    uint8_t dispMode = 0x20 | (modeDispCTL & 0x0F);
    Write_Byte(dispMode, 0); //mode must be 8 bit number the first 4 and last two bits don't matter
    delay_us(100);
    //wait_Busy_Flag();

    //Set number of lines and font
    Write_Byte(dispMode, 0); //mode must be 8 bit number the first 4 and last two bits don't matter
    delay_us(100);
    //wait_Busy_Flag();

    //Set display ON/OFF, cursor, cursor blink
    uint8_t dispOnOff = modeDispCTL>>4; //shift on/off control bits into lower nibble
    dispOnOff = 0x08 | (modeDispCTL & 0x0F);
    Write_Byte(dispOnOff,0);
    //wait_Busy_Flag();
    delay_us(100);

    Clear_LCD();
    P4-> OUT = 0x00; //clear ports
}

void Clear_LCD()
{
    Write_Byte(0x01,0);
    delay_us(2000);
    //wait_Busy_Flag();
}

void Home_LCD()
{
    Write_Byte(0x02,0);
    delay_us(2000);
}

void Write_String_LCD(char* string, uint8_t startAddress)
{
    Set_DDRAM(startAddress);
    int len = strlen(string);
    int i;
    for(i=0; i<len; i++)
    {
        Write_Byte(string[i], RS);
        delay_us(1000);
        Set_Entry_Mode(0x06);
    }
    delay_us(100);
}

void Write_Byte(uint8_t data, uint8_t rsrw)
{
    float shortDelay = 1;
    P4-> OUT = rsrw & (RS | RW);

    //UPPER NIBBLE
    P4-> OUT |= data & 0xF0;
    P4-> OUT |= ENABLE;
    shortDelay ++;
    P4-> OUT &= DISABLE;

    data = data<<4;
    P4-> OUT &= 0x0F;//Clear data

    //LOWER NIBBLE
    P4-> OUT |= data & 0xF0;
    P4-> OUT |= ENABLE;
    shortDelay ++;
    P4-> OUT &= DISABLE;
}

void Set_Entry_Mode(uint8_t entryMode)
{
    entryMode &= 0x07;
    entryMode |= 0x04;
    Write_Byte(entryMode,0);
    delay_us(100);
    //wait_Busy_Flag();
}

void Set_CGRAM(uint8_t address)
{
    address &= 0x7F;
    address |= 0x40;
    Write_Byte(address,0);
    delay_us(100);
    //wait_Busy_Flag();
}

void Set_DDRAM(uint8_t address)
{
    address |= 0x80;
    Write_Byte(address,0);
    delay_us(100);
    //wait_Busy_Flag();
}

void wait_Busy_Flag()
{
    float shortDelay = .1;
    P4-> DIR = ((0x00 | ENABLE) | RW); //Set Data bits to input
    P4-> OUT = RW;
    uint8_t busyFlag;

    do
    {
        P4 -> OUT |= ENABLE;
        busyFlag = P4-> IN;
        shortDelay *= .1;
        P4-> OUT &= DISABLE;
    }while((busyFlag & 0x80) == 0x00);
}
