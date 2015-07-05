/*
 * qspi.h
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 5
 * Peter Tueller (ptueller@asu.edu)
 */

#ifndef QSPI_H_
#define QSPI_H_

#include "support_common.h"

void qspi_init(uint8 block, uint16 baudrate);

void qspi_tx(int bits, uint8* data);

#endif /* QSPI_H_ */
