/*-------------------------------------------------------------------
 * File:        Systick.h
 * Author:      Ahmed Shehata
 * Date:        February, 2023
 * Description: Header file of the SysTick timer module.
 *------------------------------------------------------------------*/
#ifndef SYS_H_
#define SYS_H_

// Included Header Files
// ----------------------
#include "stdint.h"

// Function Prototypes
// --------------------
void SysTick_Init(uint32_t);
void Delay100ms(uint32_t); 

#endif
