#include "msp.h"
/*
 * delay_us.h
 *
 *  Created on: Apr 9, 2019
 *      Author: Daniel Gutmann
 */

#ifndef DELAY_US_H_
#define DELAY_US_H_

void delay_us(usec)
{

    SysTick -> LOAD = (((CS->CTL0 & CS_CTL0_DCORSEL_MASK)|CS_CTL0_DCORSEL_1)>>11)*(usec)/21;
    SysTick->CTRL = 1;
    while((SysTick->CTRL & 0x10000) != 0x10000);
}



#endif /* DELAY_US_H_ */
