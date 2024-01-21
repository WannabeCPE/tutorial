//	Filename: macros.h
//
//	Description: This file contains all the macros 
//	that are used in other files.
//
//	Author: Cody Lane
//	Date: 08/30/20
// 
//	Compiler: Built with IAR Embedded Workbench 7.20.1


#define RESET_STATE             (0)
#define ALWAYS                  (1)
#define TRUE (1)
#define FALSE (0)
#define ORIGINAL             (0x00) //
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // 6 GREEN LED
#define SW2                  (0x08) // 2.3 SW2
#define SW1                  (0x02) // 4.1 SW1
#define Time_Sequence_Rate         (50)
#define S1250 (1250/Time_Sequence_Rate) //
#define S1000 (1000/Time_Sequence_Rate) //
#define S750   (750/Time_Sequence_Rate) //
#define S500   (500/Time_Sequence_Rate) //
#define S250   (250/Time_Sequence_Rate) //


// PWM 
#define WHEEL_PERIOD (65000)
#define WHEEL_OFF (0)

#define CRUISE_SPEED_RIGHT (12000)
#define CRUISE_SPEED_LEFT (6000)
#define RIGHT_FORWARD_WHEEL_ON  (10000)
#define LEFT_FORWARD_WHEEL_ON  (10000)
#define RIGHT_REVERSE_WHEEL_ON (10000)
#define LEFT_REVERSE_WHEEL_ON (25000)

#define RIGHT_FORWARD_SLOWER_WHEEL_ON  (7000)
#define LEFT_FORWARD_SLOWER_WHEEL_ON  (7000)
#define RIGHT_REVERSE_SLOWER_ON (10000)
#define LEFT_REVERSE_SLOWER_ON (10000)

#define RIGHT_FORWARD_SPEED (TB3CCR1)
#define LEFT_FORWARD_SPEED (TB3CCR2)
#define RIGHT_REVERSE_SPEED (TB3CCR3)
#define LEFT_REVERSE_SPEED (TB3CCR4)


// Timer B0 Intervals
#define TB0CCR0_INTERVAL (25000)
#define TB0CCR1_INTERVAL (25000)
#define TB0CCR2_INTERVAL (25000)

// Timer B1 Intervals
#define TB1CCR0_INTERVAL (5000)
#define TB1CCR1_INTERVAL (5000)
#define TB1CCR2_INTERVAL (25000)

// Ports 2 & 4 P4OUT clarification macro
#define P4PUD (P4OUT)
#define P2PUD (P2OUT)

// Switch Interrupt and debouncing macros
#define DEBOUNCE_COUNT_LIMIT (20)
#define DEBOUNCING (1)
#define SWITCH_PRESSED (0)

// Serial Communication auto transmit period
#define ONE_SECOND (20)
#define THREE_SECOND (60)

// Timer1 B2 intervals
#define TWO_HUNDRED_MSEC (4)
#define TWO_HUNDRED_MSEC_MAX (10)

// States
#define SPLASH ('S')
#define BAUD_1 ('X')
#define BAUD_2 ('Y')
#define BAUD_1_WAIT ('Z')
#define BAUD_2_WAIT ('z')
#define IOT_COMMAND_DISPLAY ('C')
#define TRANSMIT_MESSAGE ('T')
#define IP_SSID_DISPLAY ('I')
#define DISPLAY_WAIT_4_CHANGE ('W')
#define AT_COMMAND ('A')
#define AT_NSTCP_COMMAND ('P')
#define NONE ('N')
#define WAITING_FOR_INPUT ('w')
#define COURSE_COMMANDS_INACTIVE ('n')

// Drive State
#define WAIT ('W')

// Detector states
#define LEFT_SIDE ('l')
#define RIGHT_SIDE ('r')
#define WHITE_STATE ('w')
#define BLACK_LINE ('b')

// Update display interrupt 
#define UPDATE_DISPLAY_LIMIT (4)


// Display Length
#define DISPLAY_LENGTH (10)


// Serial Communications
#define BEGINNING (0)
#define SMALL_RING_SIZE (16)
#define LARGE_RING_SIZE (32)
#define BR_SPEED_0 ('0')
#define BR_SPEED_1 ('1')












// Port States
#define SELECT_LOW (0x00) // Select bit low state
#define SELECT_HIGH (0x01) // Select bit high state
#define DIRECT_IN (0x00) // Direction bit set to low  or in
#define DIRECT_OUT (0xFF) // Direction bit set to high or out
#define INITIAL_LOW (0x00) // Initial value set to zero
#define INITIAL_HIGH (0x01) // Initial value set to one


// Port 1 Pins
#define RED_LED (0x01) // 0 RED LED 0
#define A1_SEEED (0x02) // 1 A1_SEEED
#define V_DETECT_L (0x04) // 2 V_DETECT_L
#define V_DETECT_R (0x08) // 3 V_DETECT_R
#define A4_SEEED (0x10) // 4 A4_SEEED
#define V_THUMB (0x20) // 5 V_THUMB
#define UCA0RXD (0x40) // 6 Back Channel UCA0RXD
#define UCA0TXD (0x80) // 7 Back Channel UCA0TXD

// Port 2 Pins
#define P2_0 (0x01) // 0
#define IR_LED (0x02) // 1 IR LED ON/OFF signal
#define P2_2 (0x04) // 2
#define SW2 (0x08) // 3 SW2
#define P2_4 (0x10) // 4
#define P2_5 (0x20) // 5
#define LFXOUT (0x40) // XOUTR
#define LFXIN (0x80) // XINR

// Port 3 Pins
#define TEST_PROBE (0x01) // 0 TEST PROBE
#define CHECK_BAT (0x02) // 1 CHECK_BAT
#define OA2N (0x04) // 2 Photodiode Circuit
#define OA2P (0x08) // 3 Photodiode Circuit
#define SMCLK_OUT (0x10) // 4 SMCLK
#define DAC_CNTL (0x20) // 5 DAC signal from Processor
#define IOT_LINK (0x40) // 6 IOT_LINK
#define P3_7 (0x80) // 7 P3_7

// Port 4 Pins
#define RESET_LCD (0x01) // 0 LCD Reset
#define SW1 (0x02) // 1 SW1
#define UCA1RXD (0x04) // 2 Back Channel UCA1RXD
#define UCA1TXD (0x08) // 3 Back Channel UCA1TXD
#define UCB1_CS_LCD (0x10) // 4 Chip Select
#define UCB1CLK (0x20) // 5 SPI mode - clock output—UCB1CLK
#define UCB1SIMO (0x40) // 6 UCB1SIMO
#define UCB1SOMI (0x80) // 7 UCB1SOMI

// Port 5 Pins
#define IOT_RESET (0x01)  // 0 IOT RESET
#define V_BAT (0x02)  // 1 V_BAT
#define IOT_PROG_SEL (0x04) // 2 IOT_PROG_SEL
#define V_3_3 (0x10)  // 3 V_3_3
#define IOT_PROG_MODE (0x20)  // 4 IOT_PROG_MODE

// Port 6 Pins
#define R_FORWARD (0x01)  // 0 R_FORWARD
#define L_FORWARD (0x02)  // 1 L_FORWARD
#define R_REVERSE (0x04)  // 2 R_REVERSE
#define L_REVERSE (0x08)  // 3 L_REVERSE
#define LCD_BACKLITE (0x10)  // 4 LCD_BACKLITE
#define P6_5 (0x20)  // 5 P6_5 
#define GRN_LED (0x40)  // 6 GRN_LED 