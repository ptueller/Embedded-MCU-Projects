/*
 * oct_nunchuk.h
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 4
 * Peter Tueller (ptueller@asu.edu)
 */

#ifndef OCT_NUNCHUK_H_
#define OCT_NUNCHUK_H_

#include "stdint.h"

#define OCT_NUNCHUK_BUTTON_C 			0x02
#define OCT_NUNCHUK_BUTTON_Z 			0x01

#define OCT_NUNCHUK_I2C_ADDR 			0x52
#define OCT_NUNCHUK_I2C_DELAY_US 		150
#define OCT_NUNCHUK_REFRESH_FREQ_HZ		4

#define OCT_NUNCHUK_REG_F0 				0xF0
#define OCT_NUNCHUK_REG_FB				0xFB
#define OCT_NUNCHUK_REG_NONE			0x00

void octNunchukInit();

void octNunchukTxCmd(uint8_t reg, uint8_t cmd);

#endif /* OCT_NUNCHUK_H_ */
