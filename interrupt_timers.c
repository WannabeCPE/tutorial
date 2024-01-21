//------------------------------------------------------------------------------
//
//  Description: This file contains the Interrupt_Timers Routine 
//
//
//  Cody Lane
//  Septermber 2020
//  Built with IAR Embedded Workbench Version: V7.20.1 
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"

extern unsigned int switch_one_debouncing;
extern unsigned int switch_one_debounce_count;
extern unsigned int switch_two_debouncing;
extern unsigned int switch_two_debounce_count;
extern volatile unsigned char update_display;
extern volatile unsigned char display_changed;
extern volatile unsigned int display_update_count = RESET_STATE;
volatile unsigned int timerB0_count = RESET_STATE;
extern volatile char display_state;
extern volatile char speed;
extern volatile unsigned int message_index;
extern volatile unsigned int pb_index;
extern volatile unsigned int transmit_flag;
extern volatile unsigned int change_baud;
volatile unsigned int transmit_pc_count = RESET_STATE;

extern volatile unsigned int IP_get;
extern volatile char main_menu_active;
extern volatile char main_menu_select;
extern volatile char old_display_state;

extern volatile char SSID_received;
extern volatile char send_nstcp;

extern volatile char drive_state;
extern volatile unsigned int drive_distance;
extern volatile char iot_command_active;

extern volatile unsigned int iot_char_received;
extern volatile unsigned int iot_2_pc_transmit;
extern volatile unsigned int pc_char_received;
extern volatile unsigned int pc_2_iot_transmit;

unsigned int timer1_B2_count = RESET_STATE;
extern volatile char course_timer_increment;
volatile unsigned int course_timer_decimal_count = RESET_STATE;
volatile unsigned int course_timer_ones_count = RESET_STATE;

unsigned int timerB0_interrupt_count = RESET_STATE;
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void) {
	//------------------------------------------------------------------------------
	// TimerB0 0 Interrupt handler
	//----------------------------------------------------------------------------
	// ...... Add What you need happen in the interrupt ......

	if (timerB0_count < 4) {
		timerB0_count++;
	}
	if (timerB0_count == 4) {
		P5OUT |= IOT_RESET;
		IP_get = TRUE;
		TB0CCTL0 &= ~CCIE;
	}
	


	
	TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0
		//----------------------------------------------------------------------------
}
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void) {
	//----------------------------------------------------------------------------
	// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
	//----------------------------------------------------------------------------
	switch (__even_in_range(TB0IV, 14)) {
	case 0:

		break; // No interrupt
	case 2: 
		if (switch_one_debouncing) {
			switch_one_debounce_count++;
			if (switch_one_debounce_count == DEBOUNCE_COUNT_LIMIT) {
				
				switch_one_debouncing = RESET_STATE;
				switch_one_debounce_count = RESET_STATE;
				P4IE |= SW1;



				if (!switch_two_debouncing) {
					TB0CCTL1 &= ~CCIE;
					if (main_menu_active) {
						display_state = old_display_state;
						main_menu_active = RESET_STATE;
					}
					else {
						main_menu_active = TRUE;
					}
				}

			}
		}

		if (switch_two_debouncing) {
			switch_two_debounce_count++;
			if (switch_two_debounce_count == DEBOUNCE_COUNT_LIMIT) {
				switch_two_debouncing = RESET_STATE;
				switch_two_debounce_count = RESET_STATE;
				P2IE |= SW2;


				if (!switch_one_debouncing) {
					TB0CCTL1 &= ~CCIE;
					if (main_menu_active) {
						main_menu_select = TRUE;
					}
					else {
						main_menu_select = FALSE;
					}
				}
			}
		}

		// ...... Add What you need happen in the interrupt ......
		TB0CCR1 += TB0CCR0_INTERVAL; // Add Offset to TBCCR1
		break;
	case 4: // CCR2 not used
		display_update_count++;
		if (display_update_count == UPDATE_DISPLAY_LIMIT) {
			display_update_count = RESET_STATE;
			if (display_changed) {
				display_changed = FALSE;
				update_display = TRUE;
			}
		}

		/*
		transmit_pc_count++;
		if (transmit_pc_count == ONE_SECOND) {
			transmit_pc_count = RESET_STATE;
			if (iot_char_received) {
				iot_2_pc_transmit = TRUE; // Enable RX interrupt
				iot_char_received = FALSE;
			}
			if (pc_char_received) {
				pc_2_iot_transmit = TRUE;
				pc_char_received = FALSE;
			}
		}
		*/
		// ...... Add What you need happen in the interrupt ......
		TB0CCR2 += TB0CCR2_INTERVAL; // Add Offset to TBCCR2
		break;
	case 14: // overflow
		// ...... Add What you need happen in the interrupt ......
			break;
	default: break;
	}
	//----------------------------------------------------------------------------
}

#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void) {
	//------------------------------------------------------------------------------
	// TimerB1 0 Interrupt handler
	//----------------------------------------------------------------------------
	// ...... Add What you need happen in the interrupt ......
	// 10 msec timer for ADC

	ADCCTL0 |= ADCSC;
	TB1CCR0 += TB1CCR0_INTERVAL;

		//----------------------------------------------------------------------------
}

#pragma vector = TIMER1_B1_VECTOR
__interrupt void TIMER1_B1_ISR(void) {
	//----------------------------------------------------------------------------
	// TimerB1 1-2, Overflow Interrupt Vector (TBIV) handler
	//----------------------------------------------------------------------------
	switch (__even_in_range(TB1IV, 14)) {
	case 0:

		break; // No interrupt
	case 2:
		if (drive_distance > 0) {
			drive_distance--;
		}
		else {
			if (drive_state == 'M') {
				display_state = IOT_COMMAND_DISPLAY;
				iot_command_active = RESET_STATE;
				TB1CCTL1 &= ~CCIE;
			}
			else {
				drive_state = NONE;
				display_state = COURSE_COMMANDS_INACTIVE;
				iot_command_active = RESET_STATE;
				TB1CCTL1 &= ~CCIE;
			}
		}
		TB1CCR1 += TB1CCR0_INTERVAL; // Add Offset to TBCCR1
		break;
	case 4: // CCR2 not used
		if (SSID_received) {
			if (timer1_B2_count < THREE_SECOND) {
				timer1_B2_count++;
			}
			else {
				timer1_B2_count = RESET_STATE;
				SSID_received = FALSE;
				send_nstcp = TRUE;
				TB1CCTL2 &= ~CCIE;
			}
		}

		if (course_timer_increment) {
			timer1_B2_count++;
			if (timer1_B2_count == TWO_HUNDRED_MSEC) {
				timer1_B2_count = RESET_STATE;
				course_timer_decimal_count = course_timer_decimal_count + 2;
				if (course_timer_decimal_count == TWO_HUNDRED_MSEC_MAX) {
					course_timer_decimal_count = RESET_STATE;
					course_timer_ones_count++;
				}
			}
			display_state = old_display_state;
		}
		
		TB1CCR2 += TB1CCR2_INTERVAL; // Add Offset to TBCCR2
		break;
	case 14: // overflow
		// ...... Add What you need happen in the interrupt ......
		break;
	default: break;
	}
}


