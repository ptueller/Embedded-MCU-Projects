/*
 * pwm.h
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 5
 * Peter Tueller (ptueller@asu.edu)
 */

#ifndef PWM_H_
#define PWM_H_

/*
typedef enum {
	RED=0,
	GREEN=1,
	BLUE=2
} pwm_color;
*/

void pwmInit();

void pwmWrite(int dutyCycle);

#endif /* PWM_H_ */
