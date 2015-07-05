/*
 * main.c
 * CSE325 Embedded Microprocessor Systems Spring 2015 - Project 5
 * Peter Tueller (ptueller@asu.edu)
 */

#include "support_common.h" /* include peripheral declarations and more */
#include "int.h"
#include "i2c.h" // For enumerated type i2c_mod
#include "oct_nunchuk.h"
#include "pit.h"
#include "pwm.h" //For Speaker module
#include "oct_ledm.h"
#include "timer.h"
#include "variables.h"

#define forever while (1)

static void hw_init();
static void sw_init();
static void level_init();
static int animate_scorpion(int scorpion_move);
static void near_spray();
static void lose();
static void win();
static void clear_screen();

int g_accel_x, g_accel_y, g_accel_z, g_button_c, g_button_z, g_pos_x, g_pos_y;
int pit1Flag, levelNumber, z_press, scorpion_move, goal;
int cat[2], scorpion1[2], scorpion2[2], spray[2], bubble[3][2];
enum oct_ledm_color world[8][16];
enum oct_ledm_color level[3][8][16] = { //3 total levels
		{
				{black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black},
				{black,black,green,black,black,black,black,black,red,black,black,black,black,black,black,black},
				{black,black,black,yellow,yellow,yellow,yellow,yellow,yellow,yellow,yellow,yellow,black,yellow,yellow,black},
				{black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black},
				{black,black,red,black,black,black,black,black,black,black,black,green,black,black,black,black},
				{yellow,yellow,yellow,yellow,yellow,yellow,yellow,yellow,yellow,yellow,yellow,yellow,black,black,black,black},
				{black,black,black,black,black,black,black,green,black,black,black,black,black,black,black,black},
				{black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,magenta}
		},
		{
				{black,black,black,black,black,black,black,black,black,green,black,black,black,black,black,black},
				{black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black},
				{red,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black},
				{yellow,yellow,yellow,yellow,black,black,black,black,yellow,yellow,black,black,black,magenta,black,black},
				{black,black,black,black,black,black,yellow,black,black,black,yellow,black,black,black,black,black},
				{black,black,black,black,black,yellow,black,black,black,black,yellow,black,black,black,black,black},
				{black,black,black,black,black,yellow,green,black,black,black,black,black,black,black,green,black},
				{black,black,yellow,black,black,yellow,black,black,red,black,black,black,yellow,black,black,black}
		},
		{
				{black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black},
				{black,black,black,black,black,green,black,black,black,black,black,magenta,black,black,black,black},
				{black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black},
				{black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black},
				{black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black},
				{black,yellow,green,black,yellow,yellow,black,yellow,black,yellow,black,black,yellow,black,yellow,green},
				{black,black,yellow,black,black,black,black,black,black,black,black,black,black,black,black,black},
				{black,black,yellow,red,black,black,black,black,black,black,black,black,red,black,black,black}
		}
};

enum oct_ledm_color win_lose[2][8][16] = {
		{ //Win!
				{black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black},
				{black,white,black,black,black,white,black,white,black,black,black,black,black,white,black,black},
				{black,white,black,white,black,white,black,black,black,white,white,black,black,white,black,black},
				{black,white,black,white,black,white,black,white,black,white,black,white,black,white,black,black},
				{black,white,black,white,black,white,black,white,black,white,black,white,black,black,black,black},
				{black,black,white,black,white,black,black,white,black,white,black,white,black,white,black,black},
				{black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black},
				{black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black}
		},
		{ //Lose
				{black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black},
				{black,white,black,black,black,black,black,black,black,black,black,black,black,white,white,white},
				{black,white,black,black,black,black,black,black,black,black,white,white,black,white,black,black},
				{black,white,black,black,black,white,white,white,black,white,black,black,black,white,white,black},
				{black,white,black,black,black,white,black,white,black,black,white,black,black,white,black,black},
				{black,white,white,white,black,white,white,white,black,black,black,white,black,white,white,white},
				{black,black,black,black,black,black,black,black,black,white,white,black,black,black,black,black},
				{black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black}
		},
};

__declspec(interrupt) octNunchukRead() {
	MCF_PIT1_PCSR |= 0x0004; //Clear the interrupt
	pit1Flag=1;
}

void hw_init()
{
	int_inhibit_all();
	timerInit();
	pwmInit();
	i2cInit(8);
	octNunchukInit();
	pit1Init(15, 2441/OCT_NUNCHUK_REFRESH_FREQ_HZ); //Set up the PIT1 module for 1Hz*refresh rate
	int_config(56,2,7,(void*)octNunchukRead); //Configure the ISR for the PIT1 module
	int_uninhibit_all();
	oct_ledm_init();
}

int main()
{
	uint8 data[6]; //Array in which the nunchuk data will be stored
	int i, z_press_fall_count;
	hw_init();
	sw_init();
	z_press_fall_count=0;
	scorpion_move=0;
	forever {
		if(pit1Flag) { //If we want to receive data from the nunchuk (25Hz)
			octNunchukTxCmd(OCT_NUNCHUK_REG_NONE,0x00);
			i2cRead(OCT_NUNCHUK_I2C_ADDR,6,OCT_NUNCHUK_I2C_DELAY_US,data); //Read in the nunchuk's data
			g_pos_x = data[0];
			g_pos_y = data[1];
			g_accel_x = (data[2] << 2 | (data[5] & 0x0C) >> 2);
			g_accel_y = (data[3] << 2 | (data[5] & 0x30) >> 4);
			g_accel_z = (data[4] << 2 | (data[5] & 0xC0) >> 6);
			g_button_c = !!(data[5] & 0x2);
			g_button_z = !!(data[5] & 0x1);

			if(g_pos_x<60) { //If the nunchuk is pointing left
				if(cat[1]>0) { //If the cat isn't at the wall
					if(world[cat[0]][cat[1]-1]==red || world[cat[0]][cat[1]-1]==magenta) { //If you run into a scorpion or a spray bottle
						lose();
					}
					if(world[cat[0]][cat[1]-1]==green || world[cat[0]][cat[1]+1]==white) { //If you run into a bubble or the goal
						goal++;
					}
					if(world[cat[0]][cat[1]-1]!=yellow) { //If you aren't trying to run into an obstacle
						world[cat[0]][cat[1]]=black;
						cat[1]--; //Update the cat position
						world[cat[0]][cat[1]]=cyan;
					}
					if((cat[0]!=7) && (world[cat[0]+1][cat[1]]!=yellow)) { //If there isn't any solid ground beneath the cat
						z_press=-(7-cat[0])*5; //Induce gravity based on the cat's height
					}
				}
			}
			if(g_pos_x>200) { //If the nunchuk is pointing right
				if(cat[1]<15) { //If the cat isn't at the wall
					if(world[cat[0]][cat[1]+1]==red || world[cat[0]][cat[1]-1]==magenta) { //If you run into a scorpion or spray bottle
						lose();
					}
					if(world[cat[0]][cat[1]+1]==green || world[cat[0]][cat[1]+1]==white) { //If you run into a bubble or the goal
						goal++;
					}
					if(world[cat[0]][cat[1]+1]!=yellow) { //If you aren't trying to run into an obstacle
						world[cat[0]][cat[1]]=black;
						cat[1]++; //Update the cat position
						world[cat[0]][cat[1]]=cyan;
					}
					if((cat[0]!=7) && (world[cat[0]+1][cat[1]]!=yellow)) { //If there isn't any solid ground beneath the cat
						z_press=-(7-cat[0])*5; //Induce gravity based on the cat's height
					}
				}
			}
			if(!g_button_z) { //If we're holding down the z button
				if(z_press<39) { //Charge up the jump to a certain level (max height of the map)
					z_press++;
				}
			}
			else if(z_press>0) {
				//z_press holds the charge up
				for(i=cat[0];i>=cat[0]-z_press/5;i--) { //Scan up directly above the cat and see if there is...
					if(world[i][cat[1]]==yellow || world[i][cat[1]]==magenta) { //...an obstacle or spray bottle
						break;
					}
					else if(world[i][cat[1]]==green || world[i][cat[1]]==white) { //...a bubble or goal
						goal++;
						world[i][cat[1]]=black;
					}
					else if(cat[0]+i==0) { //The top of the map
						i=-1;
						break;
					}
				}
				world[cat[0]][cat[1]]=black;
				cat[0]=i+1; //Update the cat's position
				world[cat[0]][cat[1]]=cyan;
				z_press=-(7-cat[0])*5;; //Now we have a certain amount of gravity to deal with
				z_press_fall_count=0; //This variable translates the gravity to actual pixels
			}
			else if(z_press<0) { //Simulate Gravity
				if(world[cat[0]+1][cat[1]]==green || world[cat[0]+1][cat[1]]==white) { //If we fall into a bubble or goal
					goal++;
				}
				if(world[cat[0]+1][cat[1]]==red || world[cat[0]+1][cat[1]]==magenta) { //If you fall into a scorpion or spray bottle
					lose();
				}
				if((cat[0]==7) || (world[cat[0]+1][cat[1]]==yellow)) { //If we are on the ground or an obstacle
					z_press=0;
					z_press_fall_count=0;
				}
				else {
					if(z_press_fall_count!=7-z_press/5) { //Whenever gravity has decreased enough to allow us to move down another pixel
						z_press_fall_count=7-z_press/5;
						world[cat[0]][cat[1]]=black;
						cat[0]=cat[0]+1; //Update the cat's position
						world[cat[0]][cat[1]]=cyan;
					}
					z_press++;
				}
			}
			scorpion_move=animate_scorpion(scorpion_move); //Move the scorpions!
			near_spray(); //Check if we're near a spray bottle
			if(goal==3) { //Determine where to put the white goal once all the bubbles have been popped
				switch(levelNumber) {
				case 0:
					world[6][1]=white;
					break;
				case 1:
					world[1][14]=white;
					break;
				case 2:
					world[5][12]=white;
					break;
				}
			}
			if(goal==4) { //If we get the goal, win!
				win();
			}
			pit1Flag=0;
		}
	}
}

static void sw_init()
{
	pit1Flag = 0;
	levelNumber = 0;
	cat[0]=0;
	cat[1]=0;
	level_init(level);
	z_press=0;
}

static void level_init() {
	int i,j;
	for(i=0;i<8;i++) {
		for(j=0;j<16;j++) {
			world[i][j]=level[levelNumber][i][j]; //Set each pixel by column and row
		}
	}
	switch(levelNumber) {
	case 0: //Tell the software where the scorpions, spray bottle, and bubbles are
		scorpion1[0]=4;
		scorpion1[1]=2;
		scorpion2[0]=1;
		scorpion2[1]=8;
		spray[0]=7;
		spray[1]=15;
		bubble[0][0]=6;
		bubble[0][1]=7;
		bubble[1][0]=1;
		bubble[1][1]=2;
		bubble[2][0]=4;
		bubble[2][1]=11;
		break;
	case 1:
		scorpion1[0]=7;
		scorpion1[1]=9;
		scorpion2[0]=2;
		scorpion2[1]=0;
		spray[0]=2;
		spray[1]=13;
		bubble[0][0]=0;
		bubble[0][1]=10;
		bubble[1][0]=6;
		bubble[1][1]=7;
		bubble[2][0]=6;
		bubble[2][1]=14;
		break;
	case 2:
		scorpion1[0]=7;
		scorpion1[1]=12;
		scorpion2[0]=7;
		scorpion2[1]=3;
		spray[0]=1;
		spray[1]=11;
		bubble[0][0]=5;
		bubble[0][1]=2;
		bubble[1][0]=1;
		bubble[1][1]=5;
		bubble[2][0]=5;
		bubble[2][1]=15;
		break;
	}
	world[7][0]=cyan; //Place the cat in the initial position
	cat[0]=7;
	cat[1]=0;
	levelNumber = (levelNumber+1) % 3; //Increase the level number
	scorpion_move=0;
	goal=0;
}

static void lose() { //Flash the Lose sign a few times, with beeps
	int i,j,z;
	for(z=0;z<4;z++) {
		for(i=0;i<8;i++) {
			for(j=0;j<16;j++) {
				world[i][j]=win_lose[1][i][j];
			}
		}
		pwmWrite(100);
		timerDelay(500000);
		pwmWrite(0);
		clear_screen();
		timerDelay(500000);
	}
	levelNumber=0;
	level_init();
}

static void win() { //Flash the Win! sign a few times, with beeps
	int i,j,z;
	for(z=0;z<4;z++) {
		for(i=0;i<8;i++) {
			for(j=0;j<16;j++) {
				world[i][j]=win_lose[0][i][j];
			}
		}
		pwmWrite(150);
		timerDelay(500000);
		pwmWrite(0);
		clear_screen();
		timerDelay(500000);
	}
	level_init();
}

static int animate_scorpion(int scorpion_move) { //Move each of the two scorpions forward or backward
	world[scorpion1[0]][scorpion1[1]]=black;
	world[scorpion2[0]][scorpion2[1]]=black;
	if(scorpion_move==10) {
		scorpion1[1]--;
		scorpion2[1]++;
	}
	if(scorpion_move==20) {
		scorpion1[1]--;
		scorpion2[1]++;
	}
	if(scorpion_move==30) {
		scorpion1[1]++;
		scorpion2[1]++;
	}
	if(scorpion_move==40) {
		scorpion1[1]++;
		scorpion2[1]--;
	}
	if(scorpion_move==50) {
		scorpion1[1]++;
		scorpion2[1]--;
	}
	if(scorpion_move==60) {
		scorpion1[1]--;
		scorpion2[1]--;
		world[scorpion1[0]][scorpion1[1]]=red;
		world[scorpion2[0]][scorpion2[1]]=red;
		if(world[scorpion1[0]][scorpion1[1]]==cyan || world[scorpion2[0]][scorpion2[1]]==cyan) { //If the scorpion runs into the cat
			lose();
			return 0;
		}
		return 0;
	}
	if(world[scorpion1[0]][scorpion1[1]]==cyan || world[scorpion2[0]][scorpion2[1]]==cyan) { //If the scorpion runs into the cat
		lose();
		return 0;
	}
	world[scorpion1[0]][scorpion1[1]]=red;
	world[scorpion2[0]][scorpion2[1]]=red;
	return scorpion_move+1;
}

static void near_spray() { //Check all around the cat (2 pixels wide scan) for the spray bottle. 
	//If it's, found animate the spray bottle expanding to the cat and making beeps
	if(world[cat[0]+1][cat[1]]==magenta) {
		if(cat[0]+1<8) {
			pwmWrite(30);
			timerDelay(500000);
			world[cat[0]][cat[1]]=magenta;
			pwmWrite(60);
			timerDelay(500000);
			lose();
		}
	}
	else if(world[cat[0]+2][cat[1]]==magenta) {
		if(cat[0]+2<8) {
			pwmWrite(30);
			timerDelay(500000);
			world[cat[0]+1][cat[1]]=magenta;
			pwmWrite(60);
			timerDelay(500000);
			world[cat[0]][cat[1]]=magenta;
			pwmWrite(90);
			timerDelay(500000);
			lose();
		}
	}
	else if(world[cat[0]-1][cat[1]]==magenta) {
		if(cat[0]-1>=0) {
			pwmWrite(30);
			timerDelay(500000);
			world[cat[0]][cat[1]]=magenta;
			pwmWrite(60);
			timerDelay(500000);
			lose();
		}
	}
	else if(world[cat[0]-2][cat[1]]==magenta) {
		if(cat[0]-2>=0) {
			pwmWrite(30);
			timerDelay(500000);
			world[cat[0]-1][cat[1]]=magenta;
			pwmWrite(60);
			timerDelay(500000);
			world[cat[0]][cat[1]]=magenta;
			pwmWrite(90);
			timerDelay(500000);
			lose();
		}
	}
	else if(world[cat[0]][cat[1]+1]==magenta) {
		if(cat[1]+1<16) {
			pwmWrite(30);
			timerDelay(500000);
			world[cat[0]][cat[1]]=magenta;
			pwmWrite(60);
			timerDelay(500000);
			lose();
		}
	}
	else if(world[cat[0]][cat[1]+2]==magenta) {
		if(cat[1]+2<16) {
			pwmWrite(30);
			timerDelay(500000);
			world[cat[0]][cat[1]+1]=magenta;
			pwmWrite(60);
			timerDelay(500000);
			world[cat[0]][cat[1]]=magenta;
			pwmWrite(90);
			timerDelay(500000);
			lose();
		}
	}
	else if(world[cat[0]][cat[1]-1]==magenta) {
		if(cat[1]-1>=0) {
			pwmWrite(30);
			timerDelay(500000);
			world[cat[0]][cat[1]]=magenta;
			pwmWrite(60);
			timerDelay(500000);
			lose();
		}
	}
	else if(world[cat[0]][cat[1]-2]==magenta) {
		if(cat[1]-2>=0) {
			pwmWrite(30);
			timerDelay(500000);
			world[cat[0]][cat[1]-1]=magenta;
			pwmWrite(60);
			timerDelay(500000);
			world[cat[0]][cat[1]]=magenta;
			pwmWrite(90);
			timerDelay(500000);
			lose();
		}
	}
	else if(world[cat[0]-1][cat[1]-1]==magenta) {
		if(cat[1]-1>=0 && cat[0]-1>=0) {
			pwmWrite(30);
			timerDelay(500000);
			world[cat[0]][cat[1]]=magenta;
			pwmWrite(60);
			timerDelay(500000);
			lose();
		}
	}
	else if(world[cat[0]+1][cat[1]-1]==magenta) {
		if(cat[1]-1>=0 && cat[0]+1<8) {
			pwmWrite(30);
			timerDelay(500000);
			world[cat[0]][cat[1]]=magenta;
			pwmWrite(60);
			timerDelay(500000);
			lose();
		}
	}
	else if(world[cat[0]-1][cat[1]+1]==magenta) {
		if(cat[1]+1<16 && cat[0]-1>=0) {
			pwmWrite(30);
			timerDelay(500000);
			world[cat[0]][cat[1]]=magenta;
			pwmWrite(60);
			timerDelay(500000);
			lose();
		}
	}
	else if(world[cat[0]+1][cat[1]+1]==magenta) {
		if(cat[1]+1<16 && cat[0]+1<8) {
			pwmWrite(30);
			timerDelay(500000);
			world[cat[0]][cat[1]]=magenta;
			pwmWrite(60);
			timerDelay(500000);
			lose();
		}
	}
}

static void clear_screen() { //Turn the screen black
	int i,j;
	for(i=0;i<8;i++) {
		for(j=0;j<16;j++) {
			world[i][j]=black;
		}
	}
}
