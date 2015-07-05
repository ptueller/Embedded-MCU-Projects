/*
 * pot.c
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 4
 * Peter Tueller (ptueller@asu.edu)
 */

#include "support_common.h"
#include "pot.h"
#include "pwm.h"

void potInit() {
	MCF_GPIO_PANPAR |= 0x08; //Set bit 3 to set pin AN3 to its primary function
	MCF_ADC_POWER &= ~0x0001; //Clear PD0 to power up Converter A
	while(MCF_ADC_POWER & 0x0400) {} //While the Converter is not yet powered up
	MCF_ADC_ADLST1 = 0x0003; //Read in pin 3
	MCF_ADC_ADLST2 = 0;
	MCF_ADC_ADSDIS = 0x00FE; //Disable all samples except the first one
	MCF_ADC_CTRL1 &= ~0x0007; //Clear the bottom three bits
	MCF_ADC_CTRL1 |= 0x0002; //Set the 2nd bit to set the mode to loop sequential
	MCF_ADC_CTRL1 |= 0x0800; //Enable interrupts
	MCF_ADC_CTRL2 = 20;
}

void startPot() {
	MCF_ADC_ADSTAT |= 0x0800; //Set bit 11 to clear the interrupt
	MCF_ADC_CTRL1 &= ~0x6000; //Clear START0 and STOP0
	MCF_ADC_CTRL1 |= 0x2000; //Set START0
}

void stopPot() {
	MCF_ADC_ADSTAT |= 0x0800; //Set bit 11 to clear the interrupt
	MCF_ADC_CTRL1 |= 0x4000; //Set STOP0
}
