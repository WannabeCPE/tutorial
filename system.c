//------------------------------------------------------------------------------
//
//  Description: This file contains the System Controls
//
//
//  Jim Carlson
//  Aug 2017
//  Built with IAR Embedded Workbench Version: V7.10.2 (8.0.6.4651)
//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
//------------------------------------------------------------------------------
// System Configurations

// Tells the compiler to provide the value in reg as an input to an 
// inline assembly block.  Even though the block contains no instructions,
// the compiler may not optimize it away, and is told that the value
// may change and should not be relied upon.

//inline void enable_interrupts(void) __attribute__((always_inline));
void enable_interrupts(void){
  __bis_SR_register(GIE);     // enable interrupts
//  asm volatile ("eint \n");
}


