/*
 * i2c.c
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 5
 * Peter Tueller (ptueller@asu.edu)
 */

#include "support_common.h"
#include "i2c.h"
#include "timer.h"
#include "int.h"

#define I2C_READ 1
#define I2C_WRITE 0

void i2cAcquireBus() {
	while(MCF_I2C1_I2SR & 0x20) {} //While the bus is busy
}

void i2cInit(uint8_t address) {
	int dummy;
	MCF_GPIO_PUBPAR = 0xA; //Set UB0 and UB1 to '10', the secondary mode
	MCF_I2C1_I2ADR = address << 1; //Set the address of the device
	MCF_I2C1_I2FDR |= 0x3A; //Set the frequency to just below 100kbps
	i2cReset(); //Set the module to be slave-receiver with interrupts disabled
	if(MCF_I2C1_I2SR & 0x20) { //If the bus is busy
		MCF_I2C1_I2CR = 0x00; //I2C module is disabled, act as slave-receiver
		MCF_I2C1_I2CR = 0xA0; //I2C module is enabled, act as master-receiver
		dummy = MCF_I2C1_I2DR; //Perform a dummy read
		MCF_I2C1_I2SR = 0x00; //Clear I2C arbitration lost flag, clear IRQ flag
		MCF_I2C1_I2CR = 0x00; //I2C module is disabled, act as slave-receiver, send stop bit
		MCF_I2C1_I2CR = 0x80; //Enable the module
	}
}

void i2cReset() { //Enable the module, disable interrupts, act as slave-receiver, auto ACK, no start bits
	MCF_I2C1_I2CR |= 0x80;
	MCF_I2C1_I2CR &= ~0x40;
	MCF_I2C1_I2CR &= ~0x20;
	MCF_I2C1_I2CR &= ~0x10;
	MCF_I2C1_I2CR &= ~0x08;
	MCF_I2C1_I2CR &= ~0x04;
}

void i2cRead(uint8_t address, int count, int delay_us, uint8_t* data) {
	int i;
	uint8_t dummy;
	i2cAcquireBus();
	i2cTxAddr(address,I2C_READ,delay_us); //Transmit start bit, slave address, and read bit
	MCF_I2C1_I2CR &= ~0x10; //Become a master-receiver
	MCF_I2C1_I2CR &= ~0x08; //Automatically ACK each byte
	dummy = i2cRxByte(delay_us); //Do a dummy read

	for(i=0;i<(count-1);i++) {
		data[i]=i2cRxByte(delay_us);
	}
	MCF_I2C1_I2CR |= 0x08; //NACK the second to last byte
	data[count-1]=i2cRxByte(delay_us);
	i2cReset();
}

uint8_t i2cRxByte(int delay_us) {
	uint8_t rx_byte;
	rx_byte=MCF_I2C1_I2DR;
	while(!i2cTxComplete()) {} //Wait until the transmission is finished
	MCF_I2C1_I2SR &= ~0x02; //Clear the IRQ flag
	if(delay_us>0) {
		timerDelay(delay_us);
	}
	return rx_byte;
}

void i2cSendStop() {
	MCF_I2C1_I2CR &= ~0x20; //Act as slave-receiver and send the stop bit
}

void i2cTx(uint8_t address, int count, int delay_us, uint8_t* data) {
	int i;
	i2cAcquireBus(); //Wait for the bus to become idle
	i2cTxAddr(address,I2C_WRITE,delay_us);
	for(i=0;i<count;i++) {
		i2cTxByte(data[i],delay_us); //Send each byte
	}
	i2cSendStop();
	i2cReset();
}

void i2cTxAddr(uint8_t address, uint8_t rw, int delay_us) {
	uint8_t tx_byte=0;
	MCF_I2C1_I2CR |= 0x10; //Act as master-transmitter
	MCF_I2C1_I2CR |= 0x20; //Send the start bit
	tx_byte |= address << 1;
	tx_byte |= rw;
	i2cTxByte(tx_byte,delay_us);
}

void i2cTxByte(uint8_t tx_byte, int delay_us) {
	int_inhibit_all(); //Disable interrupts
	MCF_I2C1_I2DR = tx_byte;
	while(!i2cTxComplete()) {} //Wait for the transfer to complete
	MCF_I2C1_I2SR &= ~0x02; //Clear the IRQ flag
	int_uninhibit_all(); //Enable interrupts
	timerDelay(delay_us);
}

int i2cTxComplete() {
	if(MCF_I2C1_I2SR & 0x02) { //If there has been an interrupt
		return 1;
	}
	else {
		return 0;
	}
}
