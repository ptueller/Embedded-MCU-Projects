/*
 * main.c
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 3
 * Peter Tueller (ptueller@asu.edu)
 */


#include "support_common.h" /* include peripheral declarations and more */
//#include "LED.h"
#include "dip.h"
#include "pot.h"
#include "pwm.h"
#include "switch.h"
#include "rng.h"
#include "timer.h"
#include "int.h"
#include "variables.h"
#if (CONSOLE_IO_SUPPORT || ENABLE_UART_SUPPORT)
/* Standard IO is only possible if Console or UART support is enabled. */
#include <stdio.h>
#endif

int level, pitFlag, potFlag, switchFlag;

static void setLevel(int level) { //Set the LEDs according to what level of the game we are on
	unsigned int value;
	value = (unsigned int) getRandom(0xFFFFFFFF) % (level+2);
	duty[0][0]=(value*200)/(level+1);
	value = (unsigned int) getRandom(0xFFFFFFFF) % (level+2);
	duty[0][1]=(value*200)/(level+1);
	value = (unsigned int) getRandom(0xFFFFFFFF) % (level+2);
	duty[0][2]=(value*200)/(level+1);
}

static void win() { //Display the winning animation
	int count;
	MCF_PIT0_PCSR &=  ~0x0008; //Disable the PIT interrupt
	MCF_PIT1_PCSR &=  ~0x0008; //Disable the PIT interrupt
	stopPot();
	MCF_GPIO_PORTAN |= 0xD0; //Set bits 4 6 and 7, to enable all LEDs
	for(count=0;count<4;count++) {
		MCF_PWM_PWMDTY4 = 200; //Make the output a constant high
		MCF_PWM_PWMDTY5 = 200; //Make the output a constant high
		MCF_PWM_PWMDTY6 = 200; //Make the output a constant high
		MCF_PWM_PWMCNT4 = 0; //Clear the count register
		MCF_PWM_PWMCNT5 = 0; //Clear the count register
		MCF_PWM_PWMCNT6 = 0; //Clear the count register
		timerDelay(250000);
		MCF_PWM_PWMDTY4 = 0; //Make the output a constant low
		MCF_PWM_PWMDTY5 = 0; //Make the output a constant low
		MCF_PWM_PWMDTY6 = 0; //Make the output a constant low
		MCF_PWM_PWMCNT4 = 0; //Clear the count register
		MCF_PWM_PWMCNT5 = 0; //Clear the count register
		MCF_PWM_PWMCNT6 = 0; //Clear the count register
		timerDelay(250000);
	}
	setLevel(++level); //Go to the next level
	MCF_PIT0_PCSR |= 0x0008; //Enable the PIT interrupt
	MCF_PIT1_PCSR |= 0x0008; //Enable the PIT interrupt
	startPot();
}

static void lose() { //Display the losing animation
	int i;
	MCF_PIT0_PCSR &=  ~0x0008; //Disable the PIT interrupt
	MCF_PIT1_PCSR &=  ~0x0008; //Disable the PIT interrupt
	stopPot();
	MCF_GPIO_PORTAN |= 0xD0; //Set bits 4 6 and 7, to enable all LEDs
	MCF_PWM_PWMDTY4 = 200; //Make the output a constant high
	MCF_PWM_PWMDTY5 = 0; //Make the output a constant low
	MCF_PWM_PWMDTY6 = 0; //Make the output a constant low
	MCF_PWM_PWMCNT4 = 0; //Clear the count register
	MCF_PWM_PWMCNT5 = 0; //Clear the count register
	MCF_PWM_PWMCNT6 = 0; //Clear the count register
	for(i=(200-1);i>=0;i=i-2) {
		MCF_PWM_PWMDTY4 = i; //Make the output a constant high
		MCF_PWM_PWMCNT4 = 0; //Clear the count register
		timerDelay(40000);
	}
	level=0;
	setLevel(level); //Reset the game
	MCF_PIT0_PCSR |= 0x0008; //Enable the PIT interrupt
	MCF_PIT1_PCSR |= 0x0008; //Enable the PIT interrupt
	startPot();
}

__declspec(interrupt) pitISR() {
	MCF_PIT0_PCSR |= 0x0004; //Clear the interrupt
	pitFlag=1;
}

__declspec(interrupt) potISR() {
	while(!(MCF_ADC_ADSTAT & 0x0800)) {} //Wait until the conversion is complete
	MCF_ADC_ADSTAT |= 0x0800; //Set bit 11 to clear the interrupt
	potFlag=1;
}

__declspec(interrupt) switchISR() {
	MCF_PIT1_PCSR |= 0x0004; //Clear the interrupt
	switchFlag=1;
}

int main(void)
{
	int counter = 0;
	int i,j;
	int result;
	//Initialize the modules
	//LEDInit();
	dipInit();
	switchInit();
	potInit();
	timerInit();
	pwmInit();
	rngInit();

	pitFlag=0;
	potFlag=0;
	switchFlag=0;

	//Initialize the duty cycles for each color of each LED
	for(i=0;i<3;i++) { //For each LED
		for(j=0;j<3;j++) { //For each color
			duty[i][j]=0;
		}
	}

	channelCount=0;

	editingColor=0;
	duty[1][editingColor]=200; //We will be editing the color Red first

	int_inhibit_all();
	int_config(55,1,7,(void*)pitISR); //Configure the ISR for the PIT0 module
	int_config(49,1,6,(void*)potISR); //Configure the ISR for the ADCA module
	int_config(56,2,7,(void*)switchISR); //Configure the ISR for the PIT1 module
	int_uninhibit_all();

	level=0;

	setLevel(level); //Start the game

	startPot(); //Begin sampling the ADC
	
	for(;;) {
		if(pitFlag) {
			//Update each color of the current channel
			pwmWrite(channelCount,RED,duty[channelCount][RED]);
			pwmWrite(channelCount,GREEN,duty[channelCount][GREEN]);
			pwmWrite(channelCount,BLUE,duty[channelCount][BLUE]);
			channelCount = (channelCount+1) % 3; //Increment the channel in the domain of 0,1,2
			pitFlag=0; //Reset the flag
		}
		if(potFlag) {
			result = MCF_ADC_ADRSLT0 >> 3; //Get the result (between 0 and 4096)
			result = result * 200;
			result = result / 4096; //Scale the result to the 0 to 200 bounds required by the duty cycle
			duty[2][editingColor]=result;
			potFlag=0; //Reset the flag
		}
		if(switchFlag) {
			if(debounce0()) { //SW1
				duty[1][editingColor]=0; //Turn off the old color
				editingColor=(editingColor+1)%3; //Switch the active channel
				duty[1][editingColor]=200; //Switch the new color
			}

			if(debounce1()) { //SW3
				int i,j;
				int correct=0;
				//Check each color of LED2 against LED0 to see if they are within 5% accuracy (5 down or 5 up, the total range is 200)
				for(i=0;i<3;i++) {
					for(j=((duty[2][i]-5)<0) ? 0 : duty[2][i]-5 ; j<(duty[2][i]+5) ; j++) { //Check to see if the values are within range
						if(j==duty[0][i]) {
							//If all channels pass, then the correct will increment to 3
							correct++;
						}
					}
				}
				if(correct>=3) {
					win(); //Display the winning animation
					correct=0;
				}
				else {
					lose(); //Display the losing animation
				}
			}
			switchFlag=0; //Reset the flag
		}
	}


#if (CONSOLE_IO_SUPPORT || ENABLE_UART_SUPPORT)
	//printf("Hello World in C++ from MCF52259 derivative on TWR-MCF5225X board\n\r");
#endif
	for(;;) {	   
		counter++;
	}
}
