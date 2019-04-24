#include "delay_us.h"

/*
 * delay_us.c
 *
 *  Created on: Apr 13, 2019
 *      Author: Daniel Gutmann
 */

void delay_us(int usec)
{

    SysTick -> LOAD = (((CS->CTL0 & CS_CTL0_DCORSEL_MASK)|CS_CTL0_DCORSEL_1)>>11)*(usec)/21;
    SysTick->CTRL = 1;
    while((SysTick->CTRL & 0x10000) != 0x10000);
}
