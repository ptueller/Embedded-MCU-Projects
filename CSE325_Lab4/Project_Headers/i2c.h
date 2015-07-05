/*
 * i2c.h
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 4
 * Peter Tueller (ptueller@asu.edu)
 */

#ifndef I2C_H_
#define I2C_H_

#include "stdint.h"

void i2cAcquireBus();

void i2cInit(uint8_t address);

void i2cReset();

void i2cRead(uint8_t address, int count, int delay_us, uint8_t* data);

uint8_t i2cRxByte(int delay_us);

void i2cSendStop();

void i2cTx(uint8_t address, int count, int delay_us, uint8_t* data);

void i2cTxAddr(uint8_t address, uint8_t rw, int delay_us);

void i2cTxByte(uint8_t tx_byte, int delay_us);

int i2cTxComplete();

#endif /* I2C_H_ */
