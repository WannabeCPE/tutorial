//------------------------------------------------------------------------------
//
//  Description: This file contains serial communication functions for the Main Routine - "While" Operating System
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

volatile unsigned int change_baud = RESET_STATE;
volatile char speed = BR_SPEED_0;

volatile char usb_process_buff[LARGE_RING_SIZE];
volatile char iot_process_buff[LARGE_RING_SIZE];

volatile unsigned int usb_pb_index = RESET_STATE;
volatile unsigned int iot_pb_index = RESET_STATE;

extern volatile unsigned int usb_rx_ring_rd;
extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int iot_rx_ring_rd;
extern volatile unsigned int iot_rx_ring_wr;

extern volatile unsigned int iot_2_pc_transmit;
extern volatile unsigned int pc_2_iot_transmit;

extern volatile unsigned int iot_fram_command_received;
extern volatile unsigned int pc_fram_command_received;

unsigned int iot_pb_updated = RESET_STATE;
unsigned int usb_pb_updated = RESET_STATE;

char iot_fram_command_message[LARGE_RING_SIZE] = { "IOT FRAM"};
char pc_fram_command_message[LARGE_RING_SIZE] = { "PC FRAM" };

char forward[11] = " FORWARD  ";
char turn_left[11] = "TURN LEFT ";
char turn_right[11] = "TURN RIGHT";
char reverse[11] = " REVERSE  ";
char spin_left[11] = "SPIN LEFT ";
char spin_right[11] = "SPIN RIGHT";
char stop[11] = "   STOP   ";

unsigned int carrot_rd;
volatile unsigned int fram_2_iot_ready = RESET_STATE;
char at[3] = { "T\r" };
char at_nstat[11] = { "T+NSTAT=?\r" };
char at_nstcp[18] = { "T+NSTCP=65001,1\r" };
volatile unsigned int get_ok = RESET_STATE;
extern volatile unsigned int IP_received;
extern volatile unsigned int ok_received;
volatile unsigned int send_at = RESET_STATE;
volatile unsigned int get_SSID = RESET_STATE;
extern volatile char SSID_received;

volatile char send_nstcp = RESET_STATE;

extern volatile char IOT_COMMAND[5][10];
unsigned int iot_command_rd = RESET_STATE;
extern volatile char iot_command_received;
volatile char iot_command_active = RESET_STATE;
extern volatile unsigned int iot_command_direct;
extern char iot_command_display[11];
extern volatile char display_state;

unsigned int iot_first_command = RESET_STATE;
volatile char course_timer_increment = RESET_STATE;

extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char IOT_Char_Rx[SMALL_RING_SIZE];

extern volatile char CARROT_COMMAND[SMALL_RING_SIZE];
extern volatile char FRAM_2_IOT[LARGE_RING_SIZE];

volatile unsigned int drive_distance = RESET_STATE;
extern volatile char drive_state;

unsigned int marker_count = RESET_STATE;
volatile char marker_found = RESET_STATE;


void baud(void) {
	if (change_baud) {
		change_baud = RESET_STATE;
		Init_Serial_UCA0(speed);
	}
}



void transmit_2_iot(void) {
	if (send_at) {
		send_at = FALSE;
		pc_fram_command_received = TRUE;
		CARROT_COMMAND[carrot_rd] = 'A';
	}

	if (ok_received) {
		pc_fram_command_received = TRUE;
		ok_received = FALSE;
		CARROT_COMMAND[carrot_rd] = 'N';
	}

	if (send_nstcp) {
		pc_fram_command_received = TRUE;
		send_nstcp = FALSE;
		CARROT_COMMAND[carrot_rd] = 'P';
	}

	if (SSID_received) {
		TB1CCTL2 |= CCIE;
	}


}

void carrot_command_buffer(void) {
	if (pc_fram_command_received) {
		switch (CARROT_COMMAND[carrot_rd]) {
		case 'A':
			for (int i = 0; i < sizeof(at); i++) {
				FRAM_2_IOT[i] = at[i];
			}
			pc_fram_command_received = FALSE;
			fram_2_iot_ready = TRUE;
			get_ok = TRUE;
			UCA0TXBUF = 'A';
			UCA0IE |= UCTXIE;

			CARROT_COMMAND[carrot_rd++] = NULL;
			if (carrot_rd >= sizeof(CARROT_COMMAND)) {
				carrot_rd = BEGINNING;
			}
			break;
		case 'N':
			for (int i = 0; i < sizeof(at_nstat); i++) {
				FRAM_2_IOT[i] = at_nstat[i];
			}
			pc_fram_command_received = FALSE;
			fram_2_iot_ready = TRUE;
			get_SSID = TRUE;
			UCA0TXBUF = 'A';
			UCA0IE |= UCTXIE;

			CARROT_COMMAND[carrot_rd++] = NULL;
			if (carrot_rd >= sizeof(CARROT_COMMAND)) {
				carrot_rd = BEGINNING;
			}
			break;

		case 'P':
			for (int i = 0; i < sizeof(at_nstcp); i++) {
				FRAM_2_IOT[i] = at_nstcp[i];
			}
			pc_fram_command_received = FALSE;
			fram_2_iot_ready = TRUE;
			display_state = WAITING_FOR_INPUT;
			UCA0TXBUF = 'A';
			UCA0IE |= UCTXIE;

			CARROT_COMMAND[carrot_rd++] = NULL;
			if (carrot_rd >= sizeof(CARROT_COMMAND)) {
				carrot_rd = BEGINNING;
			}
			break;
		case 'F':
			change_baud = TRUE;
			speed = BR_SPEED_0;
			baud();
			pc_fram_command_received = FALSE;
			CARROT_COMMAND[carrot_rd++] = NULL;
			if (carrot_rd >= sizeof(CARROT_COMMAND)) {
				carrot_rd = BEGINNING;
			}
			break;
			
		case 'S':
			change_baud = TRUE;
			speed = BR_SPEED_1;
			baud();
			pc_fram_command_received = FALSE;
			CARROT_COMMAND[carrot_rd++] = NULL;
			if (carrot_rd >= sizeof(CARROT_COMMAND)) {
				carrot_rd = BEGINNING;
			}
			break;
		default: break;
		}
	}
}

void iot_command_buffer(void) {
	if (iot_command_received) {
		if (++iot_first_command == 1) {
			course_timer_increment = TRUE;
			TB1CCTL2 |= CCIE;
		}
		if (IOT_COMMAND[iot_command_direct][iot_command_rd] != 'M') {
			marker_found = RESET_STATE;
		}
		switch (IOT_COMMAND[iot_command_direct][iot_command_rd]) {
		case 'F':
			display_command();
			get_drive_data();

			drive_state = 'F';
			display_state = IOT_COMMAND_DISPLAY;
			iot_command_active = TRUE;
			iot_command_received = FALSE;
			TB1CCTL1 |= CCIE;
			break;
		case 'L':
			display_command();
			get_drive_data();

			drive_state = 'L';
			display_state = IOT_COMMAND_DISPLAY;
			iot_command_active = TRUE;
			iot_command_received = FALSE;
			TB1CCTL1 |= CCIE;
			break;

		case 'R':
			display_command();
			get_drive_data();

			drive_state = 'R';
			display_state = IOT_COMMAND_DISPLAY;
			iot_command_received = FALSE;
			iot_command_active = TRUE;
			TB1CCTL1 |= CCIE;
			break;

		case 'B':
			display_command();
			get_drive_data();

			drive_state = 'B';
			display_state = IOT_COMMAND_DISPLAY;
			iot_command_received = FALSE;
			iot_command_active = TRUE;
			TB1CCTL1 |= CCIE;
			break;

		case 'l':
			display_command();
			get_drive_data();

			drive_state = 'l';
			display_state = IOT_COMMAND_DISPLAY;
			iot_command_received = FALSE;
			iot_command_active = TRUE;
			TB1CCTL1 |= CCIE;
			break;

		case 'r':
			display_command();
			get_drive_data();

			drive_state = 'r';
			display_state = IOT_COMMAND_DISPLAY;
			iot_command_received = FALSE;
			iot_command_active = TRUE;
			TB1CCTL1 |= CCIE;
			break;

		case 'S':
			display_command();
			get_drive_data();

			drive_state = 'S';
			display_state = IOT_COMMAND_DISPLAY;
			iot_command_received = FALSE;
			iot_command_active = TRUE;
			TB1CCTL1 |= CCIE;
			break;

		case 'M':
			get_drive_data();

			marker_found = TRUE;
			marker_count++;
			if (marker_count == 8) {
				course_timer_increment = FALSE;
				TB1CCTL2 &= ~CCIE;
			}

			drive_state = 'M';
			display_state = IOT_COMMAND_DISPLAY;
			iot_command_received = FALSE;
			iot_command_active = TRUE;
			TB1CCTL1 |= CCIE;
			break;

			
			
		default:break;
		
		}
	}
}




void display_command(void) {
	switch (IOT_COMMAND[iot_command_direct][iot_command_rd]) {
	case 'F':
		for (int i = 0; i < 10; i++) {
			iot_command_display[i] = forward[i];
		}
		break;
	case 'L':
		for (int i = 0; i < 10; i++) {
			iot_command_display[i] = turn_left[i];
		}
		break;

	case 'R':
		for (int i = 0; i < 10; i++) {
			iot_command_display[i] = turn_right[i];
		}
		break;

	case 'B':
		for (int i = 0; i < 10; i++) {
			iot_command_display[i] = reverse[i];
		}
		break;

	case 'l':
		for (int i = 0; i < 10; i++) {
			iot_command_display[i] = spin_left[i];
		}
		break;

	case 'r':
		for (int i = 0; i < 10; i++) {
			iot_command_display[i] = spin_right[i];
		}
		break;

	case 'S':
		for (int i = 0; i < 10; i++) {
			iot_command_display[i] = stop[i];
		}
		break;

	default:break;

	}
}

void get_drive_data(void) {
	if (iot_command_active) {
		drive_distance = RESET_STATE;
		TB1CCTL1 &= ~CCIE;
	}
	IOT_COMMAND[iot_command_direct][iot_command_rd++] = NULL;
	for (int i = 0; i < (IOT_COMMAND[iot_command_direct][iot_command_rd] - 0x30); i++) {
		drive_distance += 100;
	}
	IOT_COMMAND[iot_command_direct][iot_command_rd] = NULL;
	iot_command_rd++;
	for (int i = 0; i < (IOT_COMMAND[iot_command_direct][iot_command_rd] - 0x30); i++) {
		drive_distance += 10;
	}
	IOT_COMMAND[iot_command_direct][iot_command_rd] = NULL;
	iot_command_rd++;
	for (int i = 0; i < (IOT_COMMAND[iot_command_direct][iot_command_rd] - 0x30); i++) {
		drive_distance += 1;
	}
	IOT_COMMAND[iot_command_direct][iot_command_rd] = NULL;
	iot_command_direct++;
	if (iot_command_direct >= 5) {
		iot_command_direct = BEGINNING;
	}
	iot_command_rd = RESET_STATE;
}

