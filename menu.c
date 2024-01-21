//------------------------------------------------------------------------------
//
//  Description: This file contains functions for the Menu System
//
//
//  Cody Lane
//  Nov 2020
//  Built with IAR Embedded Workbench Version: V7.20.1 
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"

volatile char main_menu_active = RESET_STATE;
volatile char main_menu_select = RESET_STATE;
extern volatile char send_nstcp;
extern volatile unsigned int ADC_Thumb;
extern volatile char display_state;
extern volatile char old_display_state;


void menu(void) {
	if (main_menu_active) {
		switch (ADC_Thumb>>9) {
		case 0:
			display_state = AT_COMMAND;
			break;
		case 1:
			display_state = AT_NSTCP_COMMAND;
			break;
		default: break;
		
		}
		if (main_menu_select) {
			main_menu_sel();
			main_menu_select = RESET_STATE;
			display_state = old_display_state;
			main_menu_active = FALSE;
		}
	}
	
}

void main_menu_sel(void) {
	switch (ADC_Thumb >> 9) {
	case 0:
		break;
	case 1:
		send_nstcp = TRUE;
		break;
	default: break;
	}

}