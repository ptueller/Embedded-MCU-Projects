/*
 * main.c
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 4
 * Peter Tueller (ptueller@asu.edu)
 */

#include "support_common.h" /* include peripheral declarations and more */
#include <stdio.h> // For printf()
#include "int.h"
#include "i2c.h" // For enumerated type i2c_mod
#include "oct_nunchuk.h"
#include "pit.h"
#include "timer.h"
//==================================================================================================================================
// Private Preprocessor Macros
//==================================================================================================================================
#define forever while (1)
//==================================================================================================================================
// Static Function Definitions
//==================================================================================================================================
static void hw_init();
static void console_update();
static void sw_init();
//==================================================================================================================================
// Private Global Variables
//==================================================================================================================================
int g_console_update;
int g_accel_x, g_accel_y, g_accel_z, g_button_c, g_button_z, g_pos_x, g_pos_y;
int pit1Flag;
//==================================================================================================================================
// Function Definitions
//==================================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: pitISR()
//
// DESCRIPTION
// Called by PIT 0 ISR at 1 Hz to update the console with the Wii Nunchuk state information.
//----------------------------------------------------------------------------------------------------------------------------------
__declspec(interrupt) pitISR() {
	MCF_PIT0_PCSR |= 0x0004; //Clear the interrupt
	g_console_update = 1;
}


__declspec(interrupt) octNunchukRead() {
	MCF_PIT1_PCSR |= 0x0004; //Clear the interrupt
	pit1Flag=1;
}

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: hw_init()
//
// DESCRIPTION
// Initializes the MCF52259 hardware peripherals.
//----------------------------------------------------------------------------------------------------------------------------------
void hw_init()
{
	int_inhibit_all();
	timerInit();
	i2cInit(8);
	octNunchukInit();
	pit0Init(15, 2441); //Setup the PIT0 module for 1Hz
	pit1Init(15, 2441/OCT_NUNCHUK_REFRESH_FREQ_HZ); //Set up the PIT1 module for 1Hz*refresh rate
	int_config(55,1,7,(void*)pitISR); //Configure the ISR for the PIT0 module
	int_config(56,2,7,(void*)octNunchukRead); //Configure the ISR for the PIT1 module
	int_uninhibit_all();
}
//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: main()
//----------------------------------------------------------------------------------------------------------------------------------
int main()
{
	uint8_t data[6];
	hw_init();
	sw_init();
	forever {
		if(g_console_update) {
			//MCF_PIT0_PCSR &=  ~0x0008; //Disable the PIT interrupt
			//MCF_PIT1_PCSR &=  ~0x0008; //Disable the PIT interrupt
			printf("%d %d %d %d %d %d %d\n",
					g_pos_x,
					g_pos_y,
					g_accel_x,
					g_accel_y,
					g_accel_z,
					g_button_c,
					g_button_z
			);
			//MCF_PIT0_PCSR |= 0x0008; //Enable the PIT interrupt
			//MCF_PIT1_PCSR |= 0x0008; //Enable the PIT interrupt
			g_console_update = 0;
		}
		if(pit1Flag) {
			//MCF_PIT0_PCSR &=  ~0x0008; //Disable the PIT interrupt
			//MCF_PIT1_PCSR &=  ~0x0008; //Disable the PIT interrupt
			octNunchukTxCmd(OCT_NUNCHUK_REG_NONE,0x00);
			i2cRead(OCT_NUNCHUK_I2C_ADDR,6,OCT_NUNCHUK_I2C_DELAY_US,data); //Read in the nunchuk's data
			g_pos_x = data[0];
			g_pos_y = data[1];
			g_accel_x = (data[2] << 2 | (data[5] & 0x0C) >> 2);
			g_accel_y = (data[3] << 2 | (data[5] & 0x30) >> 4);
			g_accel_z = (data[4] << 2 | (data[5] & 0xC0) >> 6);
			g_button_c = !!(data[5] & 0x2);
			g_button_z = !!(data[5] & 0x1);
			
			//MCF_PIT0_PCSR |= 0x0008; //Enable the PIT interrupt
			//MCF_PIT1_PCSR |= 0x0008; //Enable the PIT interrupt
			pit1Flag=0;
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: sw_init()
//
// DESCRIPTION
// Software initialization.
//----------------------------------------------------------------------------------------------------------------------------------
static void sw_init()
{
	g_console_update = 0;
	pit1Flag = 0;
}
