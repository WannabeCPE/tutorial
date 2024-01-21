//	Filename: led.c
//
//	Description: This file is used for LED Initialization..
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


//	This function initializes the LEDs.
void Init_LEDs(void) {
	//------------------------------------------------------------------------------
	// LED Configurations
	//------------------------------------------------------------------------------
	// Turns on both LEDs
	P1OUT &= ~RED_LED;
	P6OUT &= ~GRN_LED;
	//------------------------------------------------------------------------------
}