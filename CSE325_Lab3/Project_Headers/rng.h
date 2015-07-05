/*
 * rng.h
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 3
 * Peter Tueller (ptueller@asu.edu)
 */

#ifndef RNG_H_
#define RNG_H_

void rngInit();

int getRandom(int domain);

#endif /* RNG_H_ */
