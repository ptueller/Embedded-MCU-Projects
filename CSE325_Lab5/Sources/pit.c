/*
 * pit.c
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 5
 * Peter Tueller (ptueller@asu.edu)
 */
#include "support_common.h"
#include "pit.h"
#include "int.h"

void pit0Init(int prescale, int modulus) {
	//Initialize the PIT module
	MCF_PIT0_PCSR &=  ~0x0001; //Disable the module
	MCF_PIT0_PCSR |= 0x0004; //Clear pending interrupts
	MCF_PIT0_PCSR |= 0x001A; //Enable the interrupts and enable reload and overflow
	MCF_PIT0_PCSR |= (prescale << 8); //Set the prescaler
	MCF_PIT0_PMR = modulus; //Set the modulus
	MCF_PIT0_PCSR |= 0x0001; //Enable the module
}

void pit1Init(int prescale, int modulus) {
	//Initialize the PIT module
	MCF_PIT1_PCSR &=  ~0x0001; //Disable the module
	MCF_PIT1_PCSR |= 0x0004; //Clear pending interrupts
	MCF_PIT1_PCSR |= 0x001A; //Enable the interrupts and enable reload and overflow
	MCF_PIT1_PCSR |= (prescale << 8); //Set the prescaler
	MCF_PIT1_PMR = modulus; //Set the modulus
	MCF_PIT1_PCSR |= 0x0001; //Enable the module
}