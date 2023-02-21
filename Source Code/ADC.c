/*-------------------------------------------------------------------
 * File:        ADC.c
 * Author:      Ahmed Shehata
 * Date:        February, 2023
 * Description: Source file of the ADC module.
 *------------------------------------------------------------------*/
 
// Included Header Files
// ----------------------
#include <stdint.h>
#include "ADC.h"
#include "tm4c123gh6pm.h"
/*********************************************************/
/*************ADC & PortE Initialization******************/
/*********************************************************/
void ADC0_Init(void){volatile uint32_t delay;
		SYSCTL_RCGCADC_R |= (1<<0);                 									//enable clock for adc0
    while((SYSCTL_RCGCADC_R&0x1)==0);           									//wait
    SYSCTL_RCGC2_R |= 0x10;			               										//enable port e clock
		delay  =SYSCTL_RCGC2_R;																				//wait
    GPIO_PORTE_DIR_R &= ~0x07;                  									//PE0-2 Input
    GPIO_PORTE_AFSEL_R |= (1<<2) | (0<<1) | (0<<0);               //PE2 is alternate function, PE0,1 GPIO
    GPIO_PORTE_DEN_R |= (0<<2) | (1<<1) | (1<<0);                 //PE2 den is disabled, PE0,1 Enabled
    GPIO_PORTE_AMSEL_R |= 0x04;               										//Enable analog function
    ADC0_SSPRI_R|=(0<<12)|(0x1<<8)|(0x2<<4)|(0x3<<0);   					//SS3 Highest, SS0 Lowest
    ADC0_ACTSS_R &= ~(1<<3);                    									//SS3 is disabled during initialization
    ADC0_EMUX_R &= ~(0xF<<12);                  									//SS3 is processor triggered
    ADC0_SSMUX3_R = (0x1);                     										//channel Ain1 (PE2)
    ADC0_SSCTL3_R = 0x6;                       										//no TS0 D0, yes IE0 END0
    ADC0_ACTSS_R |= (1<<3);                     									//Enable SS3
}
/*********************************************************/
/*************Take input from ADC*************************/
/*********************************************************/
uint16_t ADC0_In(void){  
		uint16_t r;
    ADC0_PSSI_R |= (1<<3);                  //Initialize SS3
    while((ADC0_RIS_R&(1<<3))==0);          //wait for 1
    r = ADC0_SSFIFO3_R&0xFFF;                //result in r
    ADC0_ISC_R |= (1<<3);                    //clear ss3 by writing 1 to ISC
    return r;
}
/********************************************************************************/
/*************convert 12-bit number form adc to 0:66 number *********************/
/********************************************************************************/
uint32_t convert(uint16_t in){
		float x;
		x = ((float)in / 4095) * 66;
		return (uint32_t) x;
}
