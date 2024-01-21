//------------------------------------------------------------------------------
//
//  Description: This file contains the Interrupt_Ports Routine 
//
//
//  Cody Lane
//  September 2020
//  Built with IAR Embedded Workbench Version: V7.20.1 
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"
//------------------------------------------------------------------------------
// Port 4 interrupt. For switches, they are disabled for the duration
// of the debounce timer. Flag is set that user space can check.

extern unsigned int switch_one_debouncing = RESET_STATE;
extern unsigned int switch_one_debounce_count = RESET_STATE;
unsigned int switch_one_press_count = RESET_STATE;

extern unsigned int switch_two_debouncing = RESET_STATE;
extern unsigned int switch_two_debounce_count = RESET_STATE;

extern volatile unsigned char display_state;
extern volatile unsigned char display_changed;

volatile unsigned int ADC_Channel = RESET_STATE;
volatile unsigned int ADC_Thumb = RESET_STATE;
volatile unsigned int ADC_Left_Detect = RESET_STATE;
volatile unsigned int ADC_Right_Detect = RESET_STATE;




#pragma vector=PORT4_VECTOR
__interrupt void switchP4_interrupt(void) {
	// Switch 1
	if (P4IFG & SW1) {
		P4IFG &= ~SW1; // IFG SW1 cleared
		TB0CCTL0 &= ~CCIE;
		TB0CCTL1 |= CCIE;
		// Set a variable to identify the switch has been pressed.
		// Set a variable to identify the switch is being debounced.
		switch_one_debouncing = DEBOUNCING;
		// Reset the count required of the debounce.
		switch_one_debounce_count = RESET_STATE;
		// Disable the Switch Interrupt.
		P4IE &= ~SW1;
		
		
		
		
		// Clear any current timer interrupt.
	
	}
	// Use a Timer Value to control the debounce
}

#pragma vector=PORT2_VECTOR
__interrupt void switchP2_interrupt(void) {
	// Switch 2
	if (P2IFG & SW2) {
		P2IFG &= ~SW2; // IFG SW2 cleared
		TB0CCTL0 &= ~CCIE;
		TB0CCTL1 |= CCIE;
		switch_two_debouncing = DEBOUNCING;
		switch_two_debounce_count = RESET_STATE;
		P2IE &= ~SW2;

	}
}

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void) {
	switch (__even_in_range(ADCIV, ADCIV_ADCIFG)) {
	case ADCIV_NONE:
		break;
	case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
	// before its previous conversion result was read.
		break;
	case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
		break;
	case ADCIV_ADCHIIFG: // Window comparator interrupt flags
		break;
	case ADCIV_ADCLOIFG: // Window comparator interrupt flag
		break;
	case ADCIV_ADCINIFG: // Window comparator interrupt flag
		break;
	case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
		ADCCTL0 &= ~ADCENC; // Disable ENC bit.
		switch (ADC_Channel++) {
		case 0x00:
			ADCMCTL0 &= ~ADCINCH_2;
			ADCMCTL0 |= ADCINCH_3;
			ADC_Left_Detect = ADCMEM0;
			ADC_Left_Detect = ADC_Left_Detect >> 2;
			ADCCTL0 |= ADCSC;
			// HEXtoBCD(ADC_Left_Detect);
			// adc_line2(6);
			break;
		case 0x01: // Channel A2 Interrupt
			ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A2
			ADCMCTL0 |= ADCINCH_5; // Enable Next channel A3
			ADC_Right_Detect = ADCMEM0; // Move result into Global
			ADC_Right_Detect = ADC_Right_Detect >> 2; // Divide the result by 4
			ADCCTL0 |= ADCSC;
			// HEXtoBCD(ADC_Right_Detect); // Convert result to String
			// adc_line3(6); // Place String in Display
			break;
		case 0x02:
			ADCMCTL0 &= ~ADCINCH_5;
			ADCMCTL0 |= ADCINCH_2;
			ADC_Thumb = ADCMEM0;
			ADC_Thumb = ADC_Thumb >> 2;
			ADC_Channel = RESET_STATE;
			// HEXtoBCD(ADC_Thumb);
			// adc_line4(6);
			break;
		default:
			break;
		}
		ADCCTL0 |= ADCENC;
		
	default:
		break;
	}
}

//------------------------------------------------------------------------------