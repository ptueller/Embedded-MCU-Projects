/*
 * switch.h
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 5
 * Peter Tueller (ptueller@asu.edu)
 */

#ifndef SWITCH_H_
#define SWITCH_H_

void switchInit();

int getSwitchState(int sw);

int debounce0();

int debounce1();

#endif /* SWITCH_H_ */
