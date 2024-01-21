//------------------------------------------------------------------------------
//
//  Description: This file contains the configuation for the ADC as well as conversion functions
//
//
//  Cody Lane
//  Sep 2020
//  Built with IAR Embedded Workbench Version: V7.20.1 
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"

char adc_char[5];
extern char display_line[4][11];
extern volatile unsigned char update_display;
extern volatile unsigned char display_changed;
extern char emitter_state;
char emitter_state_on[11] = { "Emitter ON" };
char emitter_state_off[11] = { "EmitterOFF" };


void Init_ADC(void) {
	//------------------------------------------------------------------------------
	// V_DETECT_L (0x04) // Pin 2 A2
	// V_DETECT_R (0x08) // Pin 3 A3
	// V_THUMB (0x20) // Pin 5 A5
	//------------------------------------------------------------------------------
	// ADCCTL0 Register
	ADCCTL0 = RESET_STATE; // Reset
	ADCCTL0 |= ADCSHT_2; // 16 ADC clocks
	ADCCTL0 |= ADCMSC; // MSC
	ADCCTL0 |= ADCON; // ADC ON
	// ADCCTL1 Register
	ADCCTL1 = RESET_STATE; // Reset
	ADCCTL1 |= ADCSHS_0; // 00b = ADCSC bit
	ADCCTL1 |= ADCSHP; // ADC sample-and-hold SAMPCON signal from sampling timer.
	ADCCTL1 &= ~ADCISSH; // ADC invert signal sample-and-hold.
	ADCCTL1 |= ADCDIV_0; // ADC clock divider - 000b = Divide by 1
	ADCCTL1 |= ADCSSEL_0; // ADC clock MODCLK
	ADCCTL1 |= ADCCONSEQ_0; // ADC conversion sequence 00b = Single-channel single-conversion
	// ADCCTL1 & ADCBUSY identifies a conversion is in process
	// ADCCTL2 Register
	ADCCTL2 = RESET_STATE; // Reset
	ADCCTL2 |= ADCPDIV0; // ADC pre-divider 00b = Pre-divide by 1
	ADCCTL2 |= ADCRES_2; // ADC resolution 10b = 12 bit (14 clock cycle conversion time)
	ADCCTL2 &= ~ADCDF; // ADC data read-back format 0b = Binary unsigned.
	ADCCTL2 &= ~ADCSR; // ADC sampling rate 0b = ADC buffer supports up to 200 ksps
	// ADCMCTL0 Register
	ADCMCTL0 |= ADCSREF_0; // VREF - 000b = {VR+ = AVCC and VR– = AVSS }
	ADCMCTL0 |= ADCINCH_5; // V_THUMB (0x20) Pin 5 A5
	ADCIE |= ADCIE0; // Enable ADC conv complete interrupt
	ADCCTL0 |= ADCENC; // ADC enable conversion.
	ADCCTL0 |= ADCSC; // ADC start conversion.
}

//------------------------------------------------------------------------------
//******************************************************************************
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//------------------------------------------------------------------------------
void HEXtoBCD(int hex_value) {
	int value = RESET_STATE;
	adc_char[0] = '0';
	adc_char[1] = '0';
	adc_char[2] = '0';
	adc_char[3] = '0';
	while (hex_value > 999) {
		hex_value = hex_value - 1000;
		value = value + 1;
		adc_char[0] = 0x30 + value;
	}
	value = RESET_STATE;
	while (hex_value > 99) {
		hex_value = hex_value - 100;
		value = value + 1;
		adc_char[1] = 0x30 + value;
	}
	value = RESET_STATE;
	while (hex_value > 9) {
		hex_value = hex_value - 10;
		value = value + 1;
		adc_char[2] = 0x30 + value;
	}
	adc_char[3] = 0x30 + hex_value;

}



void adc_white_calibration(char location) {
	int i;
	char white_calibration_display[11] = { "           " };
	for (i = location; i < 10; i++) {
		white_calibration_display[i] = adc_char[i - location];
	}
	if (update_display) {
		update_display = RESET_STATE;
		if (display_changed) {
			display_changed = RESET_STATE;
			strcpy(display_line[0], "  WHITE    ");
			update_string(display_line[0], 0);
			strcpy(display_line[1], "CALIBRATE ");
			update_string(display_line[1], 1);
			strcpy(display_line[2], "  VALUE:  ");
			update_string(display_line[2], 2);
			strcpy(display_line[3], white_calibration_display);
			update_string(display_line[3], 3);
		};
	}
}

void adc_black_calibration(char location) {
	int i;
	char black_calibration_display[11] = { "           " };
	for (i = location; i < 10; i++) {
		black_calibration_display[i] = adc_char[i - location];
	}
	if (update_display) {
		update_display = RESET_STATE;
		if (display_changed) {
			display_changed = RESET_STATE;
			strcpy(display_line[0], "  BLACK    ");
			update_string(display_line[0], 0);
			strcpy(display_line[1], "CALIBRATE ");
			update_string(display_line[1], 1);
			strcpy(display_line[2], "  VALUE:  ");
			update_string(display_line[2], 2);
			strcpy(display_line[3], black_calibration_display);
			update_string(display_line[3], 3);
		};
	}
}

void adc_line2(char location) {
	int i;
	char V_Detect_Left_display[11] = { "V_DL:     " };
	
	for (i = location; i < 10; i++) {
		V_Detect_Left_display[i] = adc_char[i - location];
	}
	if (update_display) {
		update_display = RESET_STATE;
		if (display_changed) {
			display_changed = RESET_STATE;
			if (emitter_state) {
				strcpy(display_line[0], emitter_state_on);
				update_string(display_line[0], 0);
			}
			else {
				strcpy(display_line[0], emitter_state_off);
				update_string(display_line[0], 0);
			}
			strcpy(display_line[1], V_Detect_Left_display);
			update_string(display_line[1], 1);
		}
	}

}
void adc_line3(char location) {
	int i;
	char V_Detect_Right_display[11] = { "V_DR:     " };

	for (i = location; i < 10; i++) {
		V_Detect_Right_display[i] = adc_char[i - location];
	}
	if (update_display) {
		update_display = RESET_STATE;
		if (display_changed) {
			display_changed = RESET_STATE;
			if (emitter_state) {
				strcpy(display_line[0], emitter_state_on);
				update_string(display_line[0], 0);
			}
			else {
				strcpy(display_line[0], emitter_state_off);
				update_string(display_line[0], 0);
			}
			strcpy(display_line[2], V_Detect_Right_display);
			update_string(display_line[2], 2);
		}
	}
}
void adc_line4(char location) {
	int i;
	char V_Thumb_display[11] = { "V_TH:     " };

	for (i = location; i < 10; i++) {
		V_Thumb_display[i] = adc_char[i - location];
	}

	if (update_display) {
		update_display = RESET_STATE;
		if (display_changed) {
			display_changed = RESET_STATE;
			if (emitter_state) {
				strcpy(display_line[0], emitter_state_on);
				update_string(display_line[0], 0);
			}
			else {
				strcpy(display_line[0], emitter_state_off);
				update_string(display_line[0], 0);
			}
			strcpy(display_line[3], V_Thumb_display);
			update_string(display_line[3], 3);
		}
	}
}



//******************************************************************************
//------------------------------------------------------------------------------