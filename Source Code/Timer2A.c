/*-------------------------------------------------------------------
 * File:        Timer2A.c
 * Author:      Ahmed Shehata
 * Date:        February, 2023
 * Description: Source file of the  Timer2 module.
 *------------------------------------------------------------------*/
// Included Header Files
// ----------------------
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "Timer2A.h"
#include "sprite.h"
#include "DAC.h"

// Global Variables
// -----------------
bool Semaphore;
extern uint32_t Count;
extern const uint8_t *Wave;
extern uint32_t Index;

// Timer Initialization
// ---------------------
void Timer2_Init(uint32_t period){ 
  uint32_t volatile delay;
  SYSCTL_RCGC1_R |= 0x40000;   // Timer2 using the legacy register
  delay = SYSCTL_RCGC1_R;
  TIMER2_CTL_R = 0x00000000;    // 1) disable timer2A during setup
  TIMER2_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = period-1;    // 4) reload value
  TIMER2_TAPR_R = 0;            // 5) bus clock resolution
  TIMER2_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
  TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x80000000; // 8) priority 4
	// interrupts enabled in the main program after all devices initialized
	// vector number 39, interrupt number 23
  NVIC_EN0_R = 1<<23;           // 9) enable IRQ 23 in NVIC
  TIMER2_CTL_R = 0x00000001;    // 10) enable timer2A
}

// Timer ISR
// ----------
void Timer2A_Handler(void){ 
  TIMER2_ICR_R = 0x00000001;  // acknowledge
  if(Count){
    DAC_Out(Wave[Index]>>4); 
    Index = Index + 1;
    Count = Count - 1;
  }else{
    Timer2A_Stop();
  }
}

void Timer2A_Stop(void){
  TIMER2_CTL_R &= ~0x00000001; // disable
}
void Timer2A_Start(void){
  TIMER2_CTL_R |= 0x00000001;   // enable
}
