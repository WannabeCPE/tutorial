//	Filename: ports.c
//
//	Description: This file contains initializes all ports 1 through 6
//	
//
//	Author: Cody Lane
//	Date: 08/30/2020
// 
//	Compiler: Built with IAR Embedded Workbench 7.20.1


#include "macros.h"
#include  "functions.h"
#include  "msp430.h"
#include <string.h>

//  This function configures Port 1 and initializes pins
//  0 through 7. Pins will be described by 4 properties,
//  those being two selector bits, input/output bit, and 
//  initial value bit (if needed).
void Init_Port_1(void) { 

	// Port 1 Pins
	// 0 RED LED 0
	// 1 A1_SEEED
	// 2 V_DETECT_L
	// 3 V_DETECT_R
	// 4 A4_SEEED
	// 5 V_THUMB
	// 6 Back Channel UCA0RXD
	// 7 Back Channel UCA0TXD


	P1OUT = INITIAL_LOW; // initial value set to 0
    P1DIR = DIRECT_OUT; // P1 direction = output
	

	P1SEL0 &= ~RED_LED;  // P1_0 GPIO operation
	P1SEL1 &= ~RED_LED;  // P1_0 GPIO operation
	P1OUT |= RED_LED;  // initial value set to low
	P1DIR |= RED_LED;  // Direction = output
	

	P1SEL0 |= A1_SEEED;  // P1_1 A1 Function
	P1SEL1 |= A1_SEEED;	 // P1_1 A1 Function
	// P1OUT &= 
	// P1DIR &= ~A1_SEEED;  // Direction = input
	

	P1SEL0 |= V_DETECT_L;  // P1_2 A2 Function
	P1SEL1 |= V_DETECT_L;  // P1_2 A2 Function
	// P1OUT &= 
	// P1DIR &= ~V_DETECT_L;  // Direction = input
	

	P1SEL0 |= V_DETECT_R;  // P1_3 A3 Function
	P1SEL1 |= V_DETECT_R;  // P1_3 A3 Function
	// P1OUT &= 
	// P1DIR &= ~V_DETECT_R;  // Direction = input
	

	P1SEL0 |= A4_SEEED;  // P1_4 A4 Function
	P1SEL1 |= A4_SEEED;  // P1_4 A4 Function
	// P1OUT &= 
	// P1DIR &= ~A4_SEEED;  // Direction = input
	

	P1SEL0 |= V_THUMB;  // P1_5 A5 Function
	P1SEL1 |= V_THUMB;  // P1_5 A5 Function
	// P1OUT &=
	P1DIR &= ~V_THUMB;  // Direction = input
	 

	P1SEL0 |= UCA0RXD;  // P1_6 UCA0RXD Function
	P1SEL1 &= ~UCA0RXD;  // P1_6 UCA0RXD Function
	// P1OUT &=
	// P1DIR &= ~UCA0RXD;  // Direction = input
	

	P1SEL0 |= UCA0TXD;  // P1_7 UCA0TXD Function
	P1SEL1 &= ~UCA0TXD;  // P1_7 UCA0TXD Function
	// P1OUT &=
	// P1DIR &= ~UCA0TXD;  // Direction = input
	


}

//  This function configures Port 2 and initializes pins
//  0 through 7. Pins will be described by 4 properties,
//  those being two selector bits, input/output bit, and 
//  initial value bit (if needed).
void Init_Port_2(void) {

	// Port 2 Pins
	// 0 P2_0
	// 1 P2_1
	// 2 P2_2
	// 3 SW2
	// 4 P2_4
	// 5 P2_5
	// 6 XOUTR
	// 7 XINR

	P2OUT = INITIAL_HIGH; // P2 set Low
	P2DIR = DIRECT_IN; // Set P2 direction to output


	P2SEL0 &= ~P2_0; // P2_0 GPIO operation
	P2SEL1 &= ~P2_0; // P2_0 GPIO operation
	// P2OUT &=
	P2DIR &= ~P2_0; // Direction = input

	P2SEL0 &= ~IR_LED; // P2_1 GPIO operation
	P2SEL1 &= ~IR_LED; // P2_1 GPIO operation
	P2OUT |= IR_LED;
	P2DIR |= IR_LED; // Direction = output

	P2SEL0 &= ~P2_2; // P2_2 GPIO operation
	P2SEL1 &= ~P2_2; // P2_2 GPIO operation
	// P2OUT &=
	P2DIR &= ~P2_2; // Direction = input

	P2SEL0 &= ~SW2; // SW2 Operation
	P2SEL1 &= ~SW2; // SW2 Operation
	P2PUD |= SW2; // Configure pullup resistor
	P2DIR &= ~SW2; // Direction = input
	P2REN |= SW2; // Enable pullup resistor
	P2IES |= SW2; // P2.0 Hi/Lo edge interrupt
	P2IFG &= ~SW2; // Clear all P2.6 interrupt flags
	P2IE |= SW2; // P2.6 interrupt enabled

	P2SEL0 &= ~P2_4; // P2_4 GPIO operation
	P2SEL1 &= ~P2_4; // P2_4 GPIO operation
	// P2OUT &=
	P2DIR &= ~P2_4; // Direction = input

	P2SEL0 &= ~P2_5; // P2_5 GPIO operation
	P2SEL1 &= ~P2_5; // P2_5 GPIO operation
	// P2OUT &=
	P2DIR &= ~P2_5; // Direction = input

	P2SEL0 &= ~LFXOUT; // LFXOUT Clock operation
	P2SEL1 |= LFXOUT; // LFXOUT Clock operation
	// P2OUT &= 
	// P2DIR &=

	P2SEL0 &= ~LFXIN; // LFXIN Clock operation
	P2SEL1 |= LFXIN; // LFXIN Clock operation
	// P2OUT &=
	// P2DIR &=
}

//  This function configures Port 3 and initializes pins
//  0 through 7. Pins will be described by 4 properties,
//  those being two selector bits, input/output bit, and 
//  initial value bit (if needed).
void Init_Port_3(void) {

	// Port 3 Pins
	// 0 TEST PROBE
	// 1 CHECK_BAT
	// 2 Photodiode Circuit
	// 3 Photodiode Circuit
	// 4 SMCLK
	// 5 IR_LED
	// 6 IOT_LINK
	// 7 P3_7

	P3OUT = INITIAL_LOW;  // P3 set Low
	P3DIR = DIRECT_OUT;  // P3 direction = output
	
	
	P3SEL0 &= ~TEST_PROBE;  // P3_0 GPIO Function
	P3SEL1 &= ~TEST_PROBE;  // P3_0 GPIO Function
	// P3OUT
	P3DIR &= ~TEST_PROBE;  // Direction = input
	

	P3SEL0 |= CHECK_BAT;  // P3_1 OA2O Function
	P3SEL1 |= CHECK_BAT;  // P3_1 OA2O Function
	// P3OUT
	P3DIR &= ~CHECK_BAT;  // Direction = input
	

	P3SEL0 |= OA2N;  // P3_2 OA2- Function
	P3SEL1 |= OA2N;  // P3_2 OA2- Function
	// P3OUT
	P3DIR &= ~OA2N;  // Direction = input
	

	P3SEL0 |= OA2P;  // P3_3 OA2+ Function
	P3SEL1 |= OA2P;  // P3_3 OA2+ Function
	// P3OUT
	P3DIR &= ~OA2P;  // Direction = input
	

	P3SEL0 &= ~SMCLK_OUT;  // P3_4 SMCLK Function
	P3SEL1 &= ~SMCLK_OUT;  // P3_4 SMCLK Function
	// P3OUT
	P3DIR &= ~SMCLK_OUT;  // Direction = output
	

	P3SEL0 &= ~DAC_CNTL;  // P3_5 GPIO Function
	P3SEL1 &= ~DAC_CNTL;  // P3_5 GPIO Function
	// P3OUT
	P3DIR &= ~DAC_CNTL;  // Direction = input
	

	P3SEL0 &= ~IOT_LINK;  // P3_6 GPIO Function
	P3SEL1 &= ~IOT_LINK;  // P3_6 GPIO Function
	// P3OUT
	P3DIR &= ~IOT_LINK;  // Direction = input
	

	P3SEL0 &= ~P3_7;  // P3_7 GPIO Function
	P3SEL1 &= ~P3_7;  // P3_7 GPIO Function
	// P3OUT
	P3DIR &= ~P3_7;  // Direction = input
	
}

//  This function configures Port 4 and initializes pins
//  0 through 7. Pins will be described by 4 properties,
//  those being two selector bits, input/output bit, and 
//  initial value bit (if needed).
void Init_Port_4(void) {

	// Port 4 Pins
	// 0 LCD Reset
	// 1 SW1
	// 2 Back Channel UCA1RXD
	// 3 Back Channel UCA1TXD
	// 4 Chip Select
	// 5 SPI mode - clock output—UCB1CLK
	// 6 UCB1SIMO
	// 7 UCB1SOMI

	P4OUT = INITIAL_HIGH; // P1 set Low
	P4DIR = DIRECT_IN; // Set P1 direction to oitput

	
	P4SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
	P4SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
	P4OUT |= RESET_LCD; // Set RESET_LCD Off [High]
	P4DIR |= RESET_LCD; // Set RESET_LCD direction to output
	
	
	P4SEL0 &= ~SW1; // SW1 GPIO operation
	P4SEL1 &= ~SW1; // SW1 GPIO operation
	P4PUD |= SW1; // Configure pullup resistor
	P4DIR &= ~SW1; // Direction = input
	P4REN |= SW1; // Enable pullup resistor
	P4IES |= SW1; // P2.0 Hi/Lo edge interrupt
	P4IFG &= ~SW1; // Clear all P2.6 interrupt flags
	P4IE |= SW1; // P2.6 interrupt enabled
	
	P4SEL0 |= UCA1TXD; // USCI_A1 UART operation
	P4SEL1 &= ~UCA1TXD; // USCI_A1 UART operation
	// P4OUT &=
	// P4DIR &= 
	
	P4SEL0 |= UCA1RXD; // USCI_A1 UART operation
	P4SEL1 &= ~UCA1RXD; // USCI_A1 UART operation
	// P4OUT &=
	// P4DIR &= 

	P4SEL0 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
	P4SEL1 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
	P4OUT |= UCB1_CS_LCD; // Set SPI_CS_LCD Off [High]
	P4DIR |= UCB1_CS_LCD; // Set SPI_CS_LCD direction to output
	
	
	P4SEL0 |= UCB1CLK; // UCB1CLK SPI BUS operation
	P4SEL1 &= ~UCB1CLK; // UCB1CLK SPI BUS operation
	// P4OUT &=
	// P4DIR &= 
	
	P4SEL0 |= UCB1SIMO; // UCB1SIMO SPI BUS operation
	P4SEL1 &= ~UCB1SIMO; // UCB1SIMO SPI BUS operation
	// P4OUT &=
	// P4DIR &= 
	
	P4SEL0 |= UCB1SOMI; // UCB1SOMI SPI BUS operation
	P4SEL1 &= ~UCB1SOMI; // UCB1SOMI SPI BUS operation
	// P4OUT &=
	// P4DIR &= 
}

//  This function configures Port 5 and initializes pins
//  0 through 4. Pins will be described by 4 properties,
//  those being two selector bits, input/output bit, and 
//  initial value bit (if needed).
void Init_Port_5(void) {

	// Port 5 Pins
	// 0 IOT RESET
	// 1 V_BAT
	// 2 IOT_PROG_SEL
	// 3 V_3_3
	// 4 IOT_PROG_MODE

	P5OUT = INITIAL_LOW;  // P5 set low
	P5DIR = DIRECT_IN;  // P5 direction = output


	P5SEL0 &= ~IOT_RESET;  // P5_0 GPIO Function
	P5SEL1 &= ~IOT_RESET;  // P5_0 GPIO Function
	P5OUT &= ~IOT_RESET;
	P5DIR |= IOT_RESET;  // Direction = input
	

	P5SEL0 &= ~V_BAT;  // P5_1 GPIO Function
	P5SEL1 &= ~V_BAT;  // P5_1 GPIO Function
	// P5OUT
	P5DIR &= ~V_BAT;  // Direction = input
	

	P5SEL0 &= ~IOT_PROG_SEL;  // P5_2 GPIO Function
	P5SEL1 &= ~IOT_PROG_SEL;  // P5_2 GPIO Function
	// P5OUT
	P5DIR &= ~IOT_PROG_SEL;  // Direction = input
	

	P5SEL0 &= ~V_3_3;  // P5_3 GPIO Function
	P5SEL1 &= ~V_3_3;  // P5_3 GPIO Function
	// P5OUT
	P5DIR &= ~V_3_3;  // Direction = input
	

	P5SEL0 &= ~IOT_PROG_MODE;  // P5_4 GPIO Function
	P5SEL1 &= ~IOT_PROG_MODE;  // P5_4 GPIO Function
	// P5OUT
	P5DIR &= ~IOT_PROG_MODE;  // Direction = input
	
}

//  This function configures Port 6 and initializes pins
//  0 through 6. Pins will be described by 4 properties,
//  those being two selector bits, input/output bit, and 
//  initial value bit (if needed).
void Init_Port_6(void) {

	// Port 6 Pins
	// 0 R_FORWARD
	// 1 L_FORWARD
	// 2 R_REVERSE
	// 3 L_REVERSE
	// 4 LCD_BACKLITE
	// 5 P6_5 
	// 6 GRN_LED 
        
    P6OUT = INITIAL_LOW;  // P6 set to low
	P6DIR = DIRECT_OUT;  // P6 direction = output
	

	P6SEL0 |= R_FORWARD;  // P6_0 TB3.1 Function
	P6SEL1 &= ~R_FORWARD; // P6_0 TB3.1 Function
	// P6OUT &= ~R_FORWARD;
    P6DIR |= R_FORWARD;  // Direction = output
       
	

	P6SEL0 |= L_FORWARD;  // P6_1 TB3.2 Function
	P6SEL1 &= ~L_FORWARD;  // P6_1 TB3.2 Function
	// P6OUT &= ~L_FORWARD;
    P6DIR |= L_FORWARD;  // Direction = output
        
	

	P6SEL0 |= R_REVERSE;  // P6_2 TB3.3 Function
	P6SEL1 &= ~R_REVERSE;  // P6_2 TB3.3 Function
    // P6OUT &= ~R_REVERSE;
	P6DIR |= R_REVERSE;  // Direction = output
        
	

	P6SEL0 |= L_REVERSE;  // P6_3 TB3.4 Function
	P6SEL1 &= ~L_REVERSE;  // P6_3 TB3.4 Function
    // P6OUT &= ~L_REVERSE;
	P6DIR |= L_REVERSE;  // Direction = output
        
	

	P6SEL0 &= ~LCD_BACKLITE;  // P6_4 GPIO Function
	P6SEL1 &= ~LCD_BACKLITE;  // P6_4 GPIO Function
    P6OUT |= LCD_BACKLITE;
	P6DIR |= LCD_BACKLITE;  // Direction = output
	// P6OUT

	P6SEL0 &= ~P6_5;  // P6_5 GPIO Function
	P6SEL1 &= ~P6_5;  // P6_5 GPIO Function
	// P6OUT 
	P6DIR &= ~P6_5;  // Direction = input
	

	P6SEL0 &= ~GRN_LED;  // P6_6 GPIO Function
	P6SEL1 &= ~GRN_LED;  // P6_6 GPIO Function
	// P6OUT 
	P6DIR |= GRN_LED;  // Direction = output
	
}

// This function calls the rest of the initialization functions
void Init_Ports(void) {  
	Init_Port_1();
	Init_Port_2();
	Init_Port_3();
	Init_Port_4();
	Init_Port_5();
	Init_Port_6();

}