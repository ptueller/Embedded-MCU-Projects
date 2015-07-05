/*
 * pwm.c
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 3
 * Peter Tueller (ptueller@asu.edu)
 */

#include "support_common.h"
#include "pwm.h"

void pwmInit() {
    MCF_GPIO_PANPAR &= ~0xD0; //Clear bits 4 6 and 7, to set 3 pins to GPIO mode
    MCF_GPIO_DDRAN |= 0xD0; //Set bits 4 6 and 7, to set 3 pins as outputs
    MCF_GPIO_PORTAN |= 0xD0; //Set bits 4 6 and 7, to set 3 pins to 1
    
	MCF_PWM_PWME &= ~0x70; //Disable PWM4-6
	MCF_GPIO_PTCPAR |= 0xF0; //Set PWM4 and PWM6 to their tertiary function
	MCF_GPIO_PTAPAR |= 0x30; //Set PWM5 to its tertiary function
	MCF_PWM_PWMPOL &= ~0x70; //Set PWM4-6 polarity low
	MCF_PWM_PWMCLK |= 0x70; //Set PWM4-6 clock source to the scaled clock
	MCF_PWM_PWMPRCLK = 0x33; //Set PCKA and PCKB to divide the bus clock by 8
	MCF_PWM_PWMSCLA = 5; //Set the scale variable to 5
	MCF_PWM_PWMSCLB = 5; //Set the scale variable to 5
	//If the system clock is 80MHz, each PWM clock should now be 1MHz
	MCF_PWM_PWMPER4 = 200; //Set the period to 200
	MCF_PWM_PWMPER5 = 200; //Set the period to 200
	MCF_PWM_PWMPER6 = 200; //Set the period to 200
	MCF_PWM_PWMDTY4 = 0; //Make the output a constant low
	MCF_PWM_PWMDTY5 = 0; //Make the output a constant low
	MCF_PWM_PWMDTY6 = 0; //Make the output a constant low
	MCF_PWM_PWMCNT4 = 0; //Clear the count register
	MCF_PWM_PWMCNT5 = 0; //Clear the count register
	MCF_PWM_PWMCNT6 = 0; //Clear the count register
	MCF_PWM_PWME |= 0x70; //Enable PWM4-6
	
	//Initialize the PIT module
	MCF_PIT0_PCSR &=  ~0x0001; //Disable the module
	MCF_PIT0_PCSR |= 0x0004; //Clear pending interrupts
	MCF_PIT0_PCSR |= 0x001A; //Enable the interrupts and enable reload and overflow
	MCF_PIT0_PCSR |= 0x0200; //Set the prescaler to 2^2, so the tick rate is 20MHz
	MCF_PIT0_PMR = 20000; //Set the modulus to 1000 so that the interrupt happens every millisecond
	MCF_PIT0_PCSR |= 0x0001; //Enable the module
	
}

void pwmWrite(int channel, pwm_color color, int dutyCycle) { //dutyCycle must be between 0 and 200
	MCF_GPIO_PORTAN &= ~0xD0; //Disable each of the 3 LEDs
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
	}
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
	MCF_PWM_PWMCNT4 = 0; //Clear the count register
	MCF_PWM_PWMCNT5 = 0; //Clear the count register
	MCF_PWM_PWMCNT6 = 0; //Clear the count register
}
