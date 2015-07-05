/*
 * oct_nunchuk.c
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 4
 * Peter Tueller (ptueller@asu.edu)
 */

#include "support_common.h"
#include "oct_nunchuk.h"
#include "i2c.h"
#include "pit.h"
#include "int.h"
#include "timer.h"

void octNunchukInit() {
	octNunchukTxCmd(OCT_NUNCHUK_REG_F0,0x55); //Transmit command 0x55 to Nunchuk register 0xF0
	octNunchukTxCmd(OCT_NUNCHUK_REG_FB,0x00); //Transmit command 0x00 to Nunchuk register 0x00
}

void octNunchukTxCmd(uint8_t reg, uint8_t cmd) {
	uint8_t tx_data[2];
	int tx_count;
	if(reg != OCT_NUNCHUK_REG_NONE) { //If it is a legitimate register
		tx_data[0]=reg;
		tx_data[1]=cmd;
		tx_count=2;
	}
	else {
		tx_data[0]=cmd;
		tx_count=1;
	}
	i2cTx(OCT_NUNCHUK_I2C_ADDR,tx_count,OCT_NUNCHUK_I2C_DELAY_US,tx_data);
	timerDelay(2*OCT_NUNCHUK_I2C_DELAY_US);
}
