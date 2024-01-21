//------------------------------------------------------------------------------
//
//  Description: This file contains the Interrupt Service Routines for Serial Communications
//
//
//  Cody Lane
//  October 2020
//  Built with IAR Embedded Workbench Version: V7.20.1 
//------------------------------------------------------------------------------

#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"

volatile char CARROT_COMMAND[SMALL_RING_SIZE];
volatile char FRAM_2_IOT[LARGE_RING_SIZE];
unsigned int carrot_wr = RESET_STATE;
extern volatile unsigned int fram_2_iot_ready;
unsigned int fram_direct_iot = RESET_STATE;

volatile char IOT_COMMAND[5][10];
volatile unsigned int iot_command_direct = RESET_STATE;
unsigned int iot_command_wr = RESET_STATE;
volatile char iot_command_received = RESET_STATE;
char iot_command_capture = RESET_STATE;

extern volatile unsigned int send_at; 
extern volatile unsigned int get_ok;
volatile unsigned int ok_received = RESET_STATE;
unsigned int S_count = RESET_STATE;
unsigned int ok_find_end = RESET_STATE;


char IP_address[SMALL_RING_SIZE+1];
unsigned int ip_wr = RESET_STATE;
volatile unsigned int IP_get = RESET_STATE;
unsigned int IP_look = RESET_STATE;
unsigned int IP_capture = RESET_STATE;
volatile unsigned int IP_received = RESET_STATE;

char SSID[11];
unsigned int ssid_wr = RESET_STATE;
extern volatile unsigned int get_SSID;
unsigned int quote_count = RESET_STATE;

volatile char SSID_received = RESET_STATE;

unsigned int unique_id_count = RESET_STATE;


extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int usb_rx_ring_rd;
extern volatile unsigned int iot_rx_ring_wr;
extern volatile unsigned int iot_rx_ring_rd;
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char IOT_Char_Rx[SMALL_RING_SIZE];
extern volatile char usb_process_buff[LARGE_RING_SIZE];
extern volatile char iot_process_buff[LARGE_RING_SIZE];

extern volatile unsigned int usb_pb_index;
extern volatile unsigned int iot_pb_index;

volatile unsigned int iot_fram_command = RESET_STATE;
volatile unsigned int iot_fram_command_received = RESET_STATE;
volatile unsigned int pc_fram_command = RESET_STATE;
volatile unsigned int pc_fram_command_received = RESET_STATE;

extern volatile unsigned int iot_char_received;
extern volatile unsigned int pc_char_received;


volatile unsigned int iot_2_pc_transmit = RESET_STATE;
volatile unsigned int pc_2_iot_transmit = RESET_STATE;

extern volatile char speed;
extern volatile unsigned int change_baud;


extern volatile char display_state;

//------------------------------------------------------------------------------
#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void) {
	unsigned int temp;
	unsigned int temp_2;
	unsigned int temp_3;
	switch (__even_in_range(UCA0IV, 0x08)) {
	case 0: // Vector 0 - no interrupt
		break;
	case 2: // Vector 2 - RXIFG
		temp = iot_rx_ring_wr;
		IOT_Char_Rx[temp] = UCA0RXBUF;


		if (IP_get) {
			if (IOT_Char_Rx[temp] == 'y') {
				IP_look = TRUE;
			}
			if (IP_look) {
				if ((IOT_Char_Rx[temp] >= 0x30) && (IOT_Char_Rx[temp] <= 0x39)) {
					IP_capture = TRUE;
					IP_look = FALSE;
				}
			}
			if (IP_capture) {
				if (IOT_Char_Rx[temp] == ':') {
					IP_capture = FALSE;
					IP_received = TRUE;

				}
				else {
					IP_address[ip_wr++] = IOT_Char_Rx[temp];
				}
			}
			if (IP_received) {
				if (IOT_Char_Rx[temp] == 'S') {
					S_count++;
				}
				if ((S_count == 3) && (IOT_Char_Rx[temp] == '\n')) {
					IP_received = FALSE;
					IP_get = FALSE;
					S_count = RESET_STATE;
					send_at = TRUE;
				}
			}
		}
		if (get_ok) {
			if (IOT_Char_Rx[temp] == 'O') {
				ok_find_end = TRUE;
			}
			if (ok_find_end) {
				if (IOT_Char_Rx[temp] == '\n') {
					get_ok = FALSE;
					ok_find_end = FALSE;
					ok_received = TRUE;
				}
			}
		}

		if (get_SSID) {
			if (IOT_Char_Rx[temp] == '"') {
				quote_count++;
			}
			if (quote_count == 2) {
				quote_count = RESET_STATE;
				get_SSID = FALSE;
				SSID_received = TRUE;
				display_state = IP_SSID_DISPLAY;
			}
			else if ((quote_count == 1) && (IOT_Char_Rx[temp] != '"')) {
				SSID[ssid_wr++] = IOT_Char_Rx[temp];
			}
		}

		if (iot_command_capture) {
			if (IOT_Char_Rx[temp] == 0x0D) {
				iot_command_capture = FALSE;
				iot_command_wr = RESET_STATE;
				iot_command_received = TRUE;
			}
			else {
				temp_3 = iot_command_direct;
				IOT_COMMAND[temp_3][iot_command_wr++] = IOT_Char_Rx[temp];
			}
		}
		
		if (IOT_Char_Rx[temp] == 0x1B) {
			iot_fram_command = TRUE;
		}

		if (iot_fram_command) {
			switch (IOT_Char_Rx[temp]) {
			case 0x0D:
				iot_fram_command = FALSE;
				// message received variable needed 
				iot_fram_command_received = TRUE;
				break;
			case 'F':
				// do what needed for fast
				break;
			case 'S':
				if (unique_id_count == 1) {
					unique_id_count++;
				}
				break;
			case '0':
				if (unique_id_count == 2) {
					unique_id_count++;
				}
				break;
			case '1':
				if (unique_id_count == 2) {
					unique_id_count++;
				}
				break;
			case '5':
				if (unique_id_count == 3) {
					unique_id_count++;
				}
				break;
			case '2':
				if (unique_id_count == 4) {
					unique_id_count++;
				}
				break;
			case '6':
				if (unique_id_count == 5) {
					unique_id_count++;
				}
				break;
			case '3':
				if (unique_id_count == 6) {
					unique_id_count = RESET_STATE;
					iot_command_capture = TRUE;
				}
				break;
			case 0x1B:
				unique_id_count++;
				
				// do what needed for slow
				break;
			default: break;
			}
		}


		else {
			if (++iot_rx_ring_wr >= (sizeof(IOT_Char_Rx))) {
				iot_rx_ring_wr = BEGINNING;
			}
			UCA1IE |= UCTXIE;
		}

		break;
	case 4: // Vector 4 – TXIFG
		
		if (fram_2_iot_ready) {
			if (FRAM_2_IOT[fram_direct_iot] == NULL) {
				fram_direct_iot = RESET_STATE;
				fram_2_iot_ready = RESET_STATE;
				UCA0IE &= ~UCTXIE;
			}
			else {
				UCA0TXBUF = FRAM_2_IOT[fram_direct_iot];
				FRAM_2_IOT[fram_direct_iot] = NULL;
				fram_direct_iot++;
			}
		}
		else {
			UCA0TXBUF = USB_Char_Rx[usb_rx_ring_rd++];
			if (usb_rx_ring_rd >= SMALL_RING_SIZE) {
				usb_rx_ring_rd = BEGINNING;
			}
			temp_2 = iot_rx_ring_wr;
			if (iot_rx_ring_rd == temp_2) {
				UCA0IE &= ~UCTXIE;
			}
		}
		break;
	default: break;
	}
}


#pragma vector=EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void) {
	unsigned int temp;
	unsigned int temp_2;
	switch (__even_in_range(UCA1IV, 0x08)) {
	case 0: // Vector 0 - no interrupt
		break;
	case 2: // Vector 2 - RXIFG
		
		
		temp = usb_rx_ring_wr;
		USB_Char_Rx[temp] = UCA1RXBUF; // RX -> USB_Char_Rx character
	

		
		if (USB_Char_Rx[temp] == '^') {
			pc_fram_command = TRUE;
		}

		if (pc_fram_command) {
			switch (USB_Char_Rx[temp]) {
			case 0x0D:
				pc_fram_command = FALSE;
				// message received variable needed 
				pc_fram_command_received = TRUE;
				break;
			case 'A':
				CARROT_COMMAND[carrot_wr++] = USB_Char_Rx[temp];
				if (carrot_wr >= sizeof(CARROT_COMMAND)) {
					carrot_wr = RESET_STATE;
				}
			case 'F':
				CARROT_COMMAND[carrot_wr++] = USB_Char_Rx[temp];
				if (carrot_wr >= sizeof(CARROT_COMMAND)) {
					carrot_wr = RESET_STATE;
				}
				// do what needed for fast
				break;
			case 'S':
				CARROT_COMMAND[carrot_wr++] = USB_Char_Rx[temp];
				if (carrot_wr >= sizeof(CARROT_COMMAND)) {
					carrot_wr = RESET_STATE;
				}
				// do what needed for slow
				break;
			default: break;
			}
		}
		else {
			if (++usb_rx_ring_wr >= (sizeof(USB_Char_Rx))) {
				usb_rx_ring_wr = BEGINNING;
			}
			UCA0IE |= UCTXIE;
		}
		
		
		break;
	case 4: // Vector 4 – TXIFG
		
		UCA1TXBUF = IOT_Char_Rx[iot_rx_ring_rd++];
		if (iot_rx_ring_rd >= SMALL_RING_SIZE) {
			iot_rx_ring_rd = BEGINNING;
		}
		temp_2 = iot_rx_ring_wr;
		if (iot_rx_ring_rd == temp_2) {
			UCA1IE &= ~UCTXIE;
		}
		break;
	default: break;
	}
}

//------------------------------------------------------------------------------