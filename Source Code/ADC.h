#ifndef ADC_H_
#define ADC_H_
/*-------------------------------------------------------------------
 * File:        ADC.h
 * Author:      Ahmed Shehata
 * Date:        February, 2023
 * Description: Header file of the ADC module.
 *------------------------------------------------------------------*/

// Included Header Files
// ----------------------
#include <stdint.h>

// Function Prototypes
// --------------------
void ADC0_Init(void);
uint16_t ADC0_In(void);
uint32_t convert(uint16_t in);

#endif
