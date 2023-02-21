/*-------------------------------------------------------------------
 * File:        DAC.h
 * Author:      Ahmed Shehata
 * Date:        February, 2023
 * Description: Header file of the DAC module.
 *------------------------------------------------------------------*/
 
#ifndef DAC_H_
#define DAC_H_

// Included Header Files
// ----------------------
#include <stdint.h>
#include <stdbool.h>
/*********************************************************/
/*************Functions Prototypes************************/
/*********************************************************/
void DAC_Init(void);
void DAC_Out(uint32_t);
void Sound_Init(void);
void Sound_Play(const uint8_t *, uint32_t);
void Sound_Shoot(void);
void Sound_Killed(void);
void Sound_Explosion(void);

#endif
