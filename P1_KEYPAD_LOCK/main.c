#include "utils.h"
#include "msp.h"
#include <stdarg.h>
#include "lcd.h"
#include "keypad.h"

#define LED_PORT P2

void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    setDCO(freq3Mhz);
    setGPIO_even(LED_PORT, BIT2, OUTPUT);

    char keypadChar;
    TIMER_A0->CTL = 0x0000;                     //Clear TimerA0 Control register.
    TIMER_A0->CTL &= ~(TIMER_A_CTL_IFG);        //No interrupt pending.
    TIMER_A0->CTL |= TIMER_A_CTL_IE;
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP;          //Set timer A0 to count up mode.
    TIMER_A0->CTL |= TIMER_A_CTL_ID__8;             //Set timer to divide CLK by 8
    TIMER_A0->CTL |= TIMER_A_CTL_SSEL__ACLK;

    TIMER_A0->CCTL[0]

    lcd.init();
    lcd.backlight(HIGH);
    lcd.clear();
    lcd.putstr("You pressed the");
    lcd.line_2();

    keypad.init();

    while(1){
        keypadChar = keypad.poll();
        if(keypadChar){
            lcd.line_2();
            lcd.putchar(keypadChar);
            lcd.putstr(" key.");
        }
        LED_PORT->OUT ^= BIT2;                      //Blink LED when finished.
        delay_us(100000);
    }
}


