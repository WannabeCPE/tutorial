//------------------------------------------------------------------------------
//
//  Description: This file contains the Initialization of Serial Ports
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

//----------------------------------------------------------------------------

volatile unsigned int usb_rx_ring_wr = RESET_STATE;
volatile unsigned int usb_rx_ring_rd = RESET_STATE;
volatile unsigned int iot_rx_ring_wr = RESET_STATE;
volatile unsigned int iot_rx_ring_rd = RESET_STATE;
volatile unsigned int usb_tx_ring_wr = RESET_STATE;
volatile unsigned int usb_tx_ring_rd = RESET_STATE;
volatile unsigned int iot_tx_ring_wr = RESET_STATE;
volatile unsigned int iot_tx_ring_rd = RESET_STATE;
volatile char USB_Char_Rx[SMALL_RING_SIZE];
volatile char USB_Char_Tx[SMALL_RING_SIZE] = {RESET_STATE};
volatile char IOT_Char_Rx[SMALL_RING_SIZE];
volatile char IOT_Char_Tx[SMALL_RING_SIZE];
volatile unsigned int pc_char_received = RESET_STATE;
volatile unsigned int iot_char_received = RESET_STATE;

void Init_Serial(char speed) {
	Init_Serial_UCA0(speed);
	Init_Serial_UCA1(speed);
}

void Init_Serial_UCA0(char speed) {
	int i;
	for (i = 0; i < SMALL_RING_SIZE; i++) {
		IOT_Char_Rx[i] = 0x00; // USB Rx Buffer
	}
	iot_rx_ring_wr = BEGINNING;
	iot_rx_ring_rd = BEGINNING;
	for (i = 0; i < SMALL_RING_SIZE; i++) { // May not use this
		IOT_Char_Tx[i] = 0x00; // USB Tx Buffer
	}
	iot_tx_ring_wr = BEGINNING;
	iot_tx_ring_rd = BEGINNING;

	iot_char_received = RESET_STATE;
	// Configure UART 0
	UCA0CTLW0 = 0; // Use word register
	UCA0CTLW0 |= UCSWRST; // Set Software reset enable
	UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
	UCA0CTLW0 &= ~UCMSB;
	UCA0CTLW0 &= ~UCSPB;
	UCA0CTLW0 &= ~UCPEN;
	UCA0CTLW0 &= ~UCSYNC;
	UCA0CTLW0 &= ~UC7BIT;
	UCA0CTLW0 |= UCMODE_0;
	

	if (speed == BR_SPEED_0) {
		UCA0BRW = 4;
		UCA0MCTLW = 0x5551;
		UCA0CTLW0 &= ~UCSWRST; // Set Software reset enable
		// UCA0TXBUF = 0x00; // prime the pump 
		UCA0IE |= UCRXIE; // Enable RX interrupt
		UCA0IE &= ~UCTXIE; // Enable RX interrupt

	}
	else {
		UCA0BRW = 52;
		UCA0MCTLW = 0x4911;
		UCA0CTLW0 &= ~UCSWRST; // Set Software reset enable
		// UCA0TXBUF = 0x00; // prime the pump 
		UCA0IE |= UCRXIE; // Enable RX interrupt
		UCA0IE &= ~UCTXIE; // Enable RX interrupt

	}

}

void Init_Serial_UCA1(char speed) {
	int i;
	for (i = 0; i < SMALL_RING_SIZE; i++) {
		USB_Char_Rx[i] = 0x00; // USB Rx Buffer
	}
	usb_rx_ring_wr = BEGINNING;
	usb_rx_ring_rd = BEGINNING;
	for (i = 0; i < SMALL_RING_SIZE; i++) { // May not use this
		USB_Char_Tx[i] = 0x00; // USB Tx Buffer
	}
	usb_tx_ring_wr = BEGINNING;
	usb_tx_ring_rd = BEGINNING;
	// transmit to pc off 
	pc_char_received = RESET_STATE;
	// Configure UART 0
	UCA1CTLW0 = 0; // Use word register
	UCA1CTLW0 |= UCSWRST; // Set Software reset enable
	UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
	UCA1CTLW0 &= ~UCMSB;
	UCA1CTLW0 &= ~UCSPB;
	UCA1CTLW0 &= ~UCPEN;
	UCA1CTLW0 &= ~UCSYNC;
	UCA1CTLW0 &= ~UC7BIT;
	UCA1CTLW0 |= UCMODE_0;


	if (speed == BR_SPEED_0) {
		UCA1BRW = 4;
		UCA1MCTLW = 0x5551;
		UCA1CTLW0 &= ~UCSWRST; // Set Software reset enable
		// UCA0TXBUF = 0x00; // prime the pump 
		UCA1IE |= UCRXIE; // Enable RX interrupt
		UCA1IE &= ~UCTXIE; // Enable RX interrupt

	}
	else {
		UCA1BRW = 17;
		UCA1MCTLW = 0x4A00;
		UCA1CTLW0 &= ~UCSWRST; // Set Software reset enable
		// UCA0TXBUF = 0x00; // prime the pump 
		UCA1IE |= UCRXIE; // Enable RX interrupt
		UCA1IE &= ~UCTXIE; // Enable RX interrupt

	}

}

