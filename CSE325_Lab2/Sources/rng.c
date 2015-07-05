/*
 * rng.c
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 2
 * Peter Tueller (ptueller@asu.edu)
 */

#include "support_common.h"
#include "rng.h"

void rngInit() {
            MCF_RNGA_RNGCR = 0; //Reset everything
            MCF_RNGA_RNGCR |= 5; //Set mask, high assurance, and GO
}
 
int getRandom() {
            return MCF_RNGA_RNGOUT & 3; //Return the values in the domain we care about: {0,1,2,3}
}