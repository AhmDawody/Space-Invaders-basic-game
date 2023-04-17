/*-------------------------------------------------------------------
 * File:        SpaceInvaders.c
 * Author:      Ahmed Shehata
 * Date:        February, 2023
 *
 * Description: This program is a game of Space Invaders, where the 
 *              player controls a ship and must defeat a fleet of 
 *              alien invaders. The game uses a Nokia 5110 LCD screen 
 *              to display the graphics and sound is generated using 
 *              a DAC.
 *
 *              This file contains the main game loop, as well as 
 *              initialization functions for the game components.
 *------------------------------------------------------------------*/

/* 
 * ******* Required Hardware I/O connections*******************
 * Slide pot pin 1 connected to ground
 * Slide pot pin 2 connected to PE2/AIN1
 * Slide pot pin 3 connected to +3.3V 
 * fire button connected to PE1
 * special weapon fire button connected to PE0
 * 8*R resistor DAC bit 0 on PB0 (least significant bit)
 * 4*R resistor DAC bit 1 on PB1
 * 2*R resistor DAC bit 2 on PB2
 * 1*R resistor DAC bit 3 on PB3 (most significant bit)
 *-----------------------------------------------------------------*/
/* Blue Nokia 5110
 * ---------------
 * Signal        (Nokia 5110) LaunchPad pin
 * Reset         (RST, pin 1) connected to PA7
 * SSI0Fss       (CE,  pin 2) connected to PA3
 * Data/Command  (DC,  pin 3) connected to PA6
 * SSI0Tx        (Din, pin 4) connected to PA5
 * SSI0Clk       (Clk, pin 5) connected to PA2
 * 3.3V          (Vcc, pin 6) power
 * back light    (BL,  pin 7) not connected, consists of 4 white LEDs which draw ~80mA total
 * Ground        (Gnd, pin 8) ground
 *-----------------------------------------------------------------*/
/* Red SparkFun Nokia 5110 (LCD-10168)
 * -----------------------------------
 * Signal        (Nokia 5110) LaunchPad pin
 * 3.3V          (VCC, pin 1) power
 * Ground        (GND, pin 2) ground
 * SSI0Fss       (SCE, pin 3) connected to PA3
 * Reset         (RST, pin 4) connected to PA7
 * Data/Command  (D/C, pin 5) connected to PA6
 * SSI0Tx        (DN,  pin 6) connected to PA5
 * SSI0Clk       (SCLK, pin 7) connected to PA2
 * back light    (LED, pin 8) not connected, consists of 4 white LEDs which draw ~80mA total
 *
 *-----------------------------------------------------------------*/ 
/* Included Header Files
 * ----------------------
 * This section includes the necessary header files that define various functions, 
 * macros, and types used in the program. These header files provide access to 
 * the standard libraries such as <stdint.h> and <stdbool.h> as well as 
 * custom libraries such as "Nokia5110.h", "Random.h", "Systick.h", "Timer2A.h", 
 * "sprite.h", "ADC.h", "DAC.h", and "PLL.h".
 * 
 * Each header file contains declarations for a specific set of functions or types. 
 * For example, "Nokia5110.h" defines functions for controlling the Nokia 5110 
 * LCD display, while "sprite.h" defines structures for storing and manipulating 
 * game sprites. By including these headers, the main program file gains access 
 * to the functions and types defined in the headers, making it easier to write 
 * and maintain the code.*/
#include <stdint.h>
#include <stdbool.h>  
#include "Nokia5110.h"
#include "Random.h"
#include "Systick.h"
#include "Timer2A.h"
#include "sprite.h"
#include "ADC.h"
#include "DAC.h"
#include "PLL.h"
#include "draw.h"

// Extern Variables
// -----------------
extern bool Flag;

/*********************************************************/
/************* Main Function *****************************/
/*********************************************************/
int main(void){
  __asm(" CPSID  I ");				// Disable Interrupts using assembly language
  PLL_Init();					// Initialize the PLL for 80 MHz clock frequency
  SysTick_Init(2666667);			// Initialize the SysTick timer with a frequency of 30 Hz
  Nokia5110_Init();				// Initialize the Nokia5110 LCD screen
  Timer2_Init(7256);				// Initialize Timer2 for sound generation
  DAC_Init();					// Initialize the digital-to-analog converter
  Sound_Init();					// Initialize sound generation module
  ADC0_Init();					// Initialize analog-to-digital converter for input control
  Random_Init(0); 				// Initialize a random seed for random number generation
  Draw_welcome();				// Draw the welcome screen
  Init();					// Initialize game sprites
  __asm(" CPSIE  I ");				// Enable Interrupts using assembly language
  Draw();					// Draw sprites on screen
  while(1){    								
	while(Flag==0){};    			// Wait for Flag to be set, indicating it's time to update the display
    	Draw();     				// Call the Draw function to update the game display
    	Flag = 0;   				// Clear the Flag to indicate that the display has been updated
    	if(ship_dead()){    			// If the player's ship is destroyed, execute the following code
		__asm(" CPSID  I ");  		// Disable interrupts to prevent the game from updating while the game over message is displayed
		Delay100ms(5);     		// Wait 
		Draw_score();         		// Call the Draw_score function to display the game over message and the final score
		Sound_Init();         		// Call the Sound_Init function to stop the sounds
		Init();               		// Call the Init function to reset the game and initialize the game sprites
		__asm(" CPSIE  I ");  		// Re-enable interrupts to allow the game to reset and start again
	}
	else{   				// If the player's ship is not destroyed, execute the following code
		if(victory()){  		// If all the aliens are destroyed, execute the following code
		__asm(" CPSID  I ");		// Disable interrupts to prevent the game from updating while the victory message is displayed
		Delay100ms(5);     		// Wait for 1 second
		Draw_victory();     		// Call the Draw_victory function to display the victory message
		Sound_Init();       		// Call the Sound_Init function to stop the sounds
		Init();             		// Call the Init function to reset the game and initialize the game sprites
		__asm(" CPSIE  I ");		// Re-enable interrupts to allow the game to reset and start again
		}
	}
}
}
