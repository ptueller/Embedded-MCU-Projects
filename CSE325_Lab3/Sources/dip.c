/*
 * dip.c
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 3
 * Peter Tueller (ptueller@asu.edu)
 */

#include "dip.h"
#include "support_common.h"

void dipInit() { //PDD 4
            MCF_GPIO_PDDPAR &= ~16; //Clear bit 4, to set to GPIO
            MCF_GPIO_DDRDD &= ~16; //Clear bit 4, set as input
}
 
int getDipState() { //PDD 4
            if(MCF_GPIO_SETDD & 16) { //If bit 4 is set
                        return 1;
            }
            else {
                        return 0;
            }
}
