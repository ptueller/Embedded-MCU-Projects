/*
 * LED.c
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 5
 * Peter Tueller (ptueller@asu.edu)
 */

#include "LED.h"
#include "timer.h"
#include "support_common.h"

void LEDInit() {
    MCF_GPIO_PTCPAR &= ~255; //Clear the lower 8 bits, to set 4 pins to GPIO mode
    MCF_GPIO_DDRTC |= 15; //Set the lower 4 bits, to set 4 pins as outputs
    MCF_GPIO_PORTTC &= ~15; //Clear the lower 4 bits, to set 4 pins to 0
}

void LEDPutVal(int LED, int state) { // LED={0,1,2,3}, state={0,1}
    MCF_GPIO_PORTTC = (MCF_GPIO_PORTTC & ~(1<<LED)) | (state<<LED); //Set the LED to the specified state
}

void clearAll() {
    MCF_GPIO_PORTTC &= ~15; //Clear the lower 4 bits, to set 4 pins to 0
}

void setAll() {
	MCF_GPIO_PORTTC |= 15; //Set the lower 4 bits, to set 4 pins to 1
}

void winAnimation() {
	int i;
	for(i=0;i<4;i++) { //Flash the LEDs four times
		clearAll();
		timerDelay(300000);
		setAll();
		timerDelay(300000);
	}
	clearAll();
}

void loseAnimation() {
	int i;
	setAll(); //Turn on all the LEDs
	timerDelay(300000);
	for(i=3;i>=0;i--) { //Turn off each of the LEDs one by one
		LEDPutVal(i,0);
		timerDelay(300000);
	}
}