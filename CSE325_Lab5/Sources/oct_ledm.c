/*
 * oct_ledm.c
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 5
 * Peter Tueller (ptueller@asu.edu)
 */

#include "oct_ledm.h"
#include "qspi.h"
#include "pit.h"
#include "int.h"
#include "variables.h"

uint8 g_ledm1_blue[8];
uint8 g_ledm2_blue[8];
uint8 g_ledm1_green[8];
uint8 g_ledm2_green[8];
uint8 g_ledm1_red[8];
uint8 g_ledm2_red[8];
uint8 g_row;

void oct_ledm_display_pattern(enum oct_ledm_color (*pattern)[8][16]) {
	int row, col;
	MCF_PIT0_PCSR &=  ~0x0001; //Disable PIT0
	for(row=0;row<8;row++) {
		g_ledm1_red[row]=0;
		g_ledm2_red[row]=0;
		g_ledm1_green[row]=0;
		g_ledm2_green[row]=0;
		g_ledm1_blue[row]=0;
		g_ledm2_blue[row]=0;
		for(col=0;col<8;col++) { //Determine how to place the data into it's respective locations and colors
			if((*pattern)[row][col] & red) g_ledm2_red[row] |= 1 << col;
			if((*pattern)[row][col] & green) g_ledm2_green[row] |= 1 << col;
			if((*pattern)[row][col] & blue) g_ledm2_blue[row] |= 1 << col;
			if((*pattern)[row][col+8] & red) g_ledm1_red[row] |= 1 << col;
			if((*pattern)[row][col+8] & green) g_ledm1_green[row] |= 1 << col;
			if((*pattern)[row][col+8] & blue) g_ledm1_blue[row] |= 1 << col;
		}
	}
	g_row=0;
	MCF_PIT0_PCSR |=  0x0001; //Enable PIT0
}

void oct_ledm_init() {
	MCF_GPIO_PTIPAR &= ~0x28; //Set pins 3 and 5 to be GPIO
	MCF_GPIO_DDRTI |= 0x28; //Set pins 3 and 5 as outputs
	MCF_GPIO_PORTTI &= ~0x20; //Set pin 5 low
	MCF_GPIO_PORTTI |= 0x08; //Set pin 3 high
	qspi_init(8,8); //8 bit blocks, baud divider of 8
	pit0Init(13,19); //Configure PIT0 to tick at ~500Hz
	int_config(55,1,7,(void*)oct_ledm_refresh); //Configure the ISR for the PIT0 module
}

__declspec(interrupt) oct_ledm_refresh() { //Called at 500Hz by PIT0 to refresh the screen
	oct_ledm_refresh_row();
	g_row = (g_row+1) % 8;
	if(g_row==0) oct_ledm_display_pattern(&world);
}

void oct_ledm_refresh_row() { //Send the data out to the specific row
	uint8 sdout[8];
	sdout[0]=g_ledm2_green[g_row];
	sdout[1]=g_ledm2_red[g_row];
	sdout[2]=g_ledm2_blue[g_row];
	sdout[3]=~(1<<g_row);
	sdout[4]=g_ledm1_green[g_row];
	sdout[5]=g_ledm1_red[g_row];
	sdout[6]=g_ledm1_blue[g_row];
	sdout[7]=sdout[3];
	MCF_GPIO_PORTTI &= ~0x20; //Set pin 5 low
	MCF_GPIO_PORTTI |= 0x08; //Set pin 3 high
	qspi_tx(8,sdout);
	MCF_GPIO_PORTTI |= 0x20; //Set pin 5 high
	MCF_GPIO_PORTTI &= ~0x08; //Set pin 3 low
}