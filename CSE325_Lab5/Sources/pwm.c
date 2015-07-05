/*
 * pwm.c
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 5
 * Peter Tueller (ptueller@asu.edu)
 */

#include "support_common.h"
#include "pwm.h"

void pwmInit() {
	MCF_PWM_PWME &= ~0x04; //Disable PWM2
	MCF_GPIO_PTCPAR |= 0x0C; //Set PWM2 to its tertiary function
	MCF_PWM_PWMPOL &= ~0x04; //Set PWM2 polarity low
	MCF_PWM_PWMCLK |= 0x04; //Set PWM2 clock source to the scaled clock
	MCF_PWM_PWMPRCLK = 0x33; //Set PCKA and PCKB to divide the bus clock by 8
	MCF_PWM_PWMSCLA = 5; //Set the scale variable to 5
	MCF_PWM_PWMSCLB = 5; //Set the scale variable to 5
	//If the system clock is 80MHz, each PWM clock should now be 1MHz
	MCF_PWM_PWMPER2 = 200; //Set the period to 200
	MCF_PWM_PWMDTY2 = 0; //Make the output a constant low
	MCF_PWM_PWMCNT2 = 0; //Clear the count register
	MCF_PWM_PWME |= 0x04; //Enable PWM2
	
}

void pwmWrite(int dutyCycle) { //dutyCycle must be between 0 and 200
	/*MCF_GPIO_PORTAN &= ~0xD0; //Disable each of the 3 LEDs
	switch(channel) {
		case 0:
		MCF_GPIO_PORTAN |= 0x10; //Set pin 4
		break;
		case 1:
		MCF_GPIO_PORTAN |= 0x40; //Set pin 6
		break;
		case 2:
		MCF_GPIO_PORTAN |= 0x80; //Set pin 7
		break;
	}*/
	MCF_PWM_PWMDTY2=dutyCycle;
	/*
	switch(color) {
	case RED:
		MCF_PWM_PWMDTY4=dutyCycle;
		break;
	case GREEN:
		MCF_PWM_PWMDTY5=dutyCycle;
		break;
	case BLUE:
		MCF_PWM_PWMDTY6=dutyCycle;
		break;
	}
	*/
	MCF_PWM_PWMCNT2 = 0; //Clear the count register
}
