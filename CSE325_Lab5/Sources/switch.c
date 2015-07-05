/*
 * switch.c
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 5
 * Peter Tueller (ptueller@asu.edu)
 */

#include "support_common.h"
#include "switch.h"
#include "pwm.h"
#include "stdint.h"

void switchInit() { //PTA0 and PTA1
	MCF_GPIO_PTAPAR &= ~15; //Clear bits 0-3 to set 2 pins to GPIO
	MCF_GPIO_DDRTA &= ~3; //Clear bits 0 and 1 to set 2 pins as inputs
	
	//Initialize PIT module
	MCF_PIT1_PCSR &=  ~0x0001; //Disable the module
	MCF_PIT1_PCSR |= 0x0004; //Clear pending interrupts
	MCF_PIT1_PCSR |= 0x001A; //Enable the interrupts and enable reload and overflow
	MCF_PIT1_PCSR |= 0x0200; //Set the prescaler to 2^2, so the tick rate is 20MHz
	MCF_PIT1_PMR = 20000; //Set the modulus to 1000 so that the interrupt happens every millisecond
	MCF_PIT1_PCSR |= 0x0001; //Enable the module
}

int getSwitchState(int sw) { //PTA0 or PTA1
	if(MCF_GPIO_SETTA & (sw+1)) {
		return 0; //Not pressed
	}
	else {
		return 1; //Pressed
	}
}

int debounce0() { //PTA0
	static uint16_t state = 0;  //holds present state
	state = (state << 1) | (!getSwitchState(0)) | 0xE000;
	if (state == 0xF000) return 1;
	return 0;
}

int debounce1() { //PTA1
	static uint16_t state = 0;  //holds present state
	state = (state << 1) | (!getSwitchState(1)) | 0xE000;
	if (state == 0xF000) return 1;
	return 0;
}