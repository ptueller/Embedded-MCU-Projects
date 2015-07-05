/*
 * switch.c
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 2
 * Peter Tueller (ptueller@asu.edu)
 */

#include "support_common.h"
#include "switch.h"

void switchInit() { //PTA0 and PTA1
            MCF_GPIO_PTAPAR &= ~15; //Clear bits 0-3 to set 2 pins to GPIO
            MCF_GPIO_DDRTA &= ~3; //Clear bits 0 and 1 to set 2 pins as inputs
}
 
int getSwitchState(int sw) { //PTA0 or PTA1
            if(MCF_GPIO_SETTA & (sw+1)) {
                        return 0; //Not pressed
            }
            else {
                        return 1; //Pressed
            }
}