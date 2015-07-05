/*
 * LED.h
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 2
 * Peter Tueller (ptueller@asu.edu)
 */

#ifndef LED_H_
#define LED_H_

void LEDInit();

void LEDPutVal(int LED, int state);

void clearAll();

void setAll();

void winAnimation();

void loseAnimation();

#endif /* LED_H_ */
