/*
 * timer.c
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 4
 * Peter Tueller (ptueller@asu.edu)
 */

#include "support_common.h"
#include "timer.h"

void timerInit() { //Set the timer to count in microseconds
            MCF_DTIM0_DTMR |= 0x0001; // Reset Timer
            MCF_DTIM0_DTMR &= 0xFFFE;
            MCF_DTIM0_DTMR = 0x4F02; // Set PS = 79, Clk Div = 1
            MCF_DTIM0_DTXMR = 0x40; // Set HALTED.
}
 
void timerDelay(long u) { //Set delay in microseconds
            MCF_DTIM0_DTER = 0x03; // Clear Events
            MCF_DTIM0_DTCN = 0x00000000; // Clear Timer Counter
            MCF_DTIM0_DTRR = u-1;
            MCF_DTIM0_DTMR |= 0x0001;
            while ( !(MCF_DTIM0_DTER & 0x02)) {} //Wait until the time has elapsed
}