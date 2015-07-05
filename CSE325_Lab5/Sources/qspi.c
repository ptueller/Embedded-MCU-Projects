/*
 * qspi.c
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 5
 * Peter Tueller (ptueller@asu.edu)
 */

#include "qspi.h"

void qspi_init(uint8 block, uint16 baudrate) {
	int i;
	MCF_GPIO_PQSPAR |= 0x11;
	MCF_GPIO_PQSPAR &= ~0x22; //Set pins 0 and 2 to the primary function
	MCF_QSPI_QMR = baudrate & 0xFF; //Set baudrate
	MCF_QSPI_QMR &= ~0x0300; //Low clock polarity and data changed on rising edge
	MCF_QSPI_QMR |= 0x2000; //8 bits
	MCF_QSPI_QMR |= 0x8000; //Set master mode
	MCF_QSPI_QWR = ((block-1) & 0xF) << 8; //Lower 4 bits of block size
	MCF_QSPI_QIR = 0; //Clear interrupts and flags
	MCF_QSPI_QIR |= 0xD; //Clear flags
	MCF_QSPI_QAR=0x20; //Set to bottom of Command RAM
	for(i=0;i<block;i++) {
		MCF_QSPI_QDR = 0x4F00; //Continuous transmission, mask all chip selects
	}
}

void qspi_tx(int bits, uint8* data) {
	int i;
	MCF_QSPI_QAR=0x00; //Set to transmit section
	for(i=0;i<bits;i++) {
		MCF_QSPI_QDR = data[i];
	}
	MCF_QSPI_QWR &= ~0xF; //Reset the queue pointer
	MCF_QSPI_QIR |= 0x1; //Clear the SPIF flag
	MCF_QSPI_QDLYR |= 0x8000; //Initiate a transmit
	while(!(MCF_QSPI_QIR & 0x1)) {} //Wait until the transmission is complete
}