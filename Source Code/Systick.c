/*-------------------------------------------------------------------
 * File:        Systick.c
 * Author:      Ahmed Shehata
 * Date:        February, 2023
 * Description: Source file of the SysTick timer module.
 *------------------------------------------------------------------*/

// Included Header Files
// ----------------------
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Systick.h"
#include "sprite.h"

// Global Variables
// -----------------
bool Flag = 0;

// Systick Timer Initialization
// -----------------------------
void SysTick_Init(uint32_t period){
	// Disable Systick timer and clear current value
	NVIC_ST_CTRL_R = 0x00;
	NVIC_ST_CURRENT_R = 0x00;

	// Set reload value and set priority to 2 (bits 29-31)
	NVIC_ST_RELOAD_R = period -1;
	NVIC_SYS_PRI3_R |= (0x2<<29);

	// Enable Systick timer with system clock as source and interrupts
	NVIC_ST_CTRL_R = 0x7;
}

// Delay 100ms at 80 MHz
// ----------------------
void Delay100ms(uint32_t count){uint32_t volatile time;
  while(count>0){
    time = 727240;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}

// Systick ISR
// ------------
void SysTick_Handler(void){  // runs at 30 Hz
	move_ship();
	check_missile();
	move_enemy();
  Flag = 1;		 // Set flag to indicate interrupt has occurred
}
