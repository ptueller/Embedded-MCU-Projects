/*
 * main.c
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 2
 * Peter Tueller (ptueller@asu.edu)
 */


#include "support_common.h" /* include peripheral declarations and more */
#include "LED.h"
#include "dip.h"
#include "switch.h"
#include "rng.h"
#include "timer.h"
#if (CONSOLE_IO_SUPPORT || ENABLE_UART_SUPPORT)
/* Standard IO is only possible if Console or UART support is enabled. */
#include <stdio.h>
#endif


int main(void)
{
	int counter = 0;
	
	
	int delay=1000000; //Set the initial delay to 1 second
	int LEDIndex;
	int winVal;
	//Initialize all the modules
	LEDInit();
	dipInit();
	switchInit();
	rngInit();
	timerInit();
	
	for(;;) {
		clearAll();
		LEDIndex=0;
		winVal=getRandom(); //Get a random value to be the winning value for this round
		LEDPutVal(winVal,1); //Display that winning value
		timerDelay(delay);
		if(!getDipState()) { //Random Game
			while(!getSwitchState(0)) { //While the button is not pressed
				clearAll();
				LEDIndex=getRandom();
				LEDPutVal(LEDIndex,1);
				timerDelay(delay);
			}
		}
		else { //Sequence Game
			while(!getSwitchState(0)) { //While the button is not pressed
				clearAll();
				LEDPutVal(LEDIndex++,1); //Increment the LED index so that it displays sequentially
				LEDIndex %= 4; //Keep the LED index within our domain
				timerDelay(delay);
			}
			//The following conditional statement is needed to bring the index back to the value that was clicked
			//We need this to compare to the winning value to see if the game has been won
			if(LEDIndex==0) {
				LEDIndex=3;
			}
			else {
				LEDIndex--;
			}
		}
		//If the chosen value is equal to the winning value
		if(LEDIndex==winVal) {
			winAnimation(); //If so, display the winning animation
			delay *= 0.85; //Decrease the delay
		}
		else {
			loseAnimation(); //Else, display the losing animation
			delay=1000000; //Reset the delay
		}
	}

#if (CONSOLE_IO_SUPPORT || ENABLE_UART_SUPPORT)
	printf("Hello World in C++ from MCF52259 derivative on TWR-MCF5225X board\n\r");
#endif
	for(;;) {	   
	   	counter++;
	}
}
