#ifndef T2A_H_
#define T2A_H_
/*-------------------------------------------------------------------
 * File:        Timer2A.h
 * Author:      Ahmed Shehata
 * Date:        February, 2023
 * Description: Header file of the  Timer2 module.
 *------------------------------------------------------------------*/

// Included Header Files
// ----------------------
#include <stdint.h>
#include <stdbool.h>
/*********************************************************/
/*************Functions Prototypes************************/
/*********************************************************/
void Timer2_Init(uint32_t period);
void Timer2A_Start(void);
void Timer2A_Stop(void);
#endif
