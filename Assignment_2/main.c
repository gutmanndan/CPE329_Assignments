#include "msp.h"
#include "set_DCO.h"
#include "delay_us.h"

#define FREQ_1_5_MHZ 1
#define FREQ_3_MHZ 3
#define FREQ_6_MHZ 6
#define FREQ_12_MHZ 12
#define FREQ_24_MHZ 24
#define FREQ_48_MHZ 48

/**
 * main.c
 */

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	set_DCO(FREQ_3_MHZ);

	P4 -> SEL0 |= BIT3;
	P4 -> SEL1 &= ~BIT3;
	P4 -> DIR |= BIT3;
	P4 -> OUT |= BIT3;

	P2 -> SEL0 &= ~BIT7;
	P2 -> SEL1 &= ~BIT7;
    P2->DIR |= BIT7;
    P2->OUT |=BIT7;

    while (1)                               // continuous loop
    {
        P2->OUT ^= BIT7;
        delay_us(40000);       // Delay
    }
}
