/*
 * oct_ledm.h
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 5
 * Peter Tueller (ptueller@asu.edu)
 */

#ifndef OCT_LEDM_H_
#define OCT_LEDM_H_

#include "support_common.h"

typedef enum oct_ledm_color {
	black=0x00,
	blue=0x01,
	green=0x02,
	magenta=0x05,
	cyan=0x03,
	red=0x04,
	white=0x07,
	yellow=0x06
} color;

void oct_ledm_display_pattern(enum oct_ledm_color (*pattern)[8][16]);

void oct_ledm_init();

__declspec(interrupt) oct_ledm_refresh();

void oct_ledm_refresh_row();

#endif /* OCT_LEDM_H_ */
