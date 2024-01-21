//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Cody Lane
//  Aug 2020
//  Built with IAR Embedded Workbench Version: V7.20.1 
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include  "macros.h"



// Global Variables
extern char pwm;
volatile char slow_input_down;
extern char display_line[4][11];
extern char *display[4];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned int update_display_count;
extern volatile unsigned char update_display;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
volatile unsigned int wheel_run;
extern unsigned int wheel_on_count;
extern char wheels_on;
extern unsigned int running;
extern char wheel_direction;
extern char number_of_runs;
extern char move_state;
extern char next_state;
extern char last_state;
extern volatile unsigned int update_display_count;
char display_adc;
extern char iot_start;

volatile char drive_state = NONE;

char iot_command_display[11] = "          ";
char BR_0[11] =  " 115,200  ";
char BR_1[11] =  " 460,800  " ;

char course_timer_ones_char[5];
char int_char[5];
extern volatile unsigned int course_timer_ones_count;
extern volatile unsigned int course_timer_decimal_count;
char course_timer_display[11] = "Time 000.0";
char marker_display[11] = "Arrived:  ";

extern char SSID[11];
extern char IP_address[SMALL_RING_SIZE + 1];
char display_0[11] = "          ";
char display_1[11] = "          ";
char display_2[11] = "          ";
char display_3[11] = "          ";
char display_out[11] =  "          " ;
volatile char display_state = NONE;
volatile char old_display_state = NONE;
char emitter_state = 0;
extern volatile char speed;

extern unsigned int marker_count;
extern volatile char marker_found;





void main(void) {
	//------------------------------------------------------------------------------
	// Main Program
	// This is the main routine for the program. Execution of code starts here.
	// The operating system is Back Ground Fore Ground.
	//
	//------------------------------------------------------------------------------

	PM5CTL0 &= ~LOCKLPM5;
	Init_Ports();                        // Initialize Ports
	// Disable the GPIO power-on default high-impedance mode to activate
	// previously configured port settings

	Init_Clocks();                       // Initialize Clock System
	Init_Conditions();                   // Initialize Variables and Initial Conditions
	Init_Timers();                       // Initialize Timers
	Init_ADC();
	Init_DAC();
	Init_LCD();                          // Initialize LCD
	Init_Serial(speed); // Initialize Serial Port for USB

	// Init_Switches();                     // Initialize Switches

	display_mode = ORIGINAL;

	strcpy(display_line[0], " ECE-306  ");
	update_string(display_line[0], 0);
	strcpy(display_line[1], " Voltages ");
	update_string(display_line[1], 1);
	strcpy(display_line[2], "BAT   CONV");
	update_string(display_line[2], 2);
	strcpy(display_line[3], "L    R    ");
	update_string(display_line[3], 3);


	TB0CCTL0 |= CCIE;
	//  move_state = STOP;

	  //------------------------------------------------------------------------------
	  // Begining of the "While" Operating System
	  //------------------------------------------------------------------------------

	while (ALWAYS) {    // Can the Operating system run
		menu();
		transmit_2_iot();
		carrot_command_buffer();
		iot_command_buffer();



		drive_state_machine();
		display_state_machine();
		Display();
		//------------------------------------------------------------------------------
	}
}

void INTtoBCD(int hex_value) {
	int value = RESET_STATE;
	int_char[0] = '0';
	int_char[1] = '0';
	int_char[2] = '0';
	int_char[3] = '0';
	while (hex_value > 999) {
		hex_value = hex_value - 1000;
		value = value + 1;
		int_char[0] = 0x30 + value;
	}
	value = RESET_STATE;
	while (hex_value > 99) {
		hex_value = hex_value - 100;
		value = value + 1;
		int_char[1] = 0x30 + value;
	}
	value = RESET_STATE;
	while (hex_value > 9) {
		hex_value = hex_value - 10;
		value = value + 1;
		int_char[2] = 0x30 + value;
	}
	int_char[3] = 0x30 + hex_value;

}
void get_course_timer_info(void) {


	INTtoBCD(course_timer_ones_count);
	for (int i = 5; i < 8; i++) {
		course_timer_display[i] = int_char[i - 4];
	}
	course_timer_display[9] = course_timer_decimal_count + 0x30;


}

void Display(void) {
	if (update_display) {
		update_display = RESET_STATE;
		Display_Update(0, 0, 0, 0);
	}
}
void drive_state_machine(void) {
	switch (drive_state) {
	case NONE:
		motorsOff();
		drive_state = WAIT;
		break;
	case 'F':
		turnLeft(20000, 21000);
		drive_state = WAIT;
		break;
	case 'B':
		driveReverse();
		drive_state = WAIT;
		break;
	case 'L':
		turnLeft(29000, 11000);
		drive_state = WAIT;
		break;

	case 'l':
		spinLeft();
		drive_state = WAIT;
		break;

	case 'r':
		spinRight();
		drive_state = WAIT;
		break;

	case 'R':
		turnRight(31000, 11000);
		drive_state = WAIT;
		break;
	case 'S':
		motorsOff();
		drive_state = WAIT;
		break;
	case 'M':
		motorsOff();
		drive_state = WAIT;
		break;
	case WAIT:
		break;
	default: break;
	}
}

void display_state_machine(void) {
	switch (display_state) {
	case NONE:
		if (speed == BR_SPEED_0) {
			strcpy(display_line[0], " Waiting  ");
			strcpy(display_line[1], "   For    ");
			strcpy(display_line[2], "IP Address");
			strcpy(display_line[3], "          ");
			display_changed = TRUE;
		}
		else {

			strcpy(display_line[0], " Waiting  ");
			strcpy(display_line[1], "   For    ");
			strcpy(display_line[2], "IP Address");
			strcpy(display_line[3], "          ");
			display_changed = TRUE;

		}
		display_state = DISPLAY_WAIT_4_CHANGE;
		display_changed = TRUE;
		break;
	case IOT_COMMAND_DISPLAY:
		get_course_timer_info();
		if (marker_found) {
			marker_display[9] = marker_count + 0x30;
			lcd_4line();
			strcpy(display_line[0], marker_display);
			strcpy(display_line[1], display_2);
			strcpy(display_line[2], display_3);
			strcpy(display_line[3], course_timer_display);
			display_state = DISPLAY_WAIT_4_CHANGE;
			display_changed = TRUE;
		
		}
		else {
			lcd_BIG_mid();
			strcpy(display_line[0], " Command: ");
			strcpy(display_line[1], iot_command_display);
			strcpy(display_line[2], course_timer_display);
			strcpy(display_line[3], "          ");
			display_state = DISPLAY_WAIT_4_CHANGE;
			display_changed = TRUE;
		}
		old_display_state = IOT_COMMAND_DISPLAY;

		break;

	case COURSE_COMMANDS_INACTIVE:
		lcd_4line();
		get_course_timer_info();
		strcpy(display_line[0], " Waiting  ");
		strcpy(display_line[1], display_2);
		strcpy(display_line[2], display_3);
		strcpy(display_line[3], course_timer_display);
		display_state = DISPLAY_WAIT_4_CHANGE;
		old_display_state = COURSE_COMMANDS_INACTIVE;
		display_changed = TRUE;
		break;

	case WAITING_FOR_INPUT:
		lcd_4line();
		strcpy(display_line[0], " Waiting  ");
		strcpy(display_line[1], "   For    ");
		strcpy(display_line[2], "  Input   ");
		strcpy(display_line[3], "          ");
		display_state = DISPLAY_WAIT_4_CHANGE;
		display_changed = TRUE;

		break;
	
	case IP_SSID_DISPLAY:
		lcd_4line();
		for (int i = 0; i < DISPLAY_LENGTH; i++) {
			display_0[i] = SSID[i];
		}
		for (int i = 1; i < 8; i++) {
			display_2[i] = IP_address[i - 1];
		}
		for (int i = 2; i < 7; i++) {
			display_3[i] = IP_address[i + 6];
		}
		strcpy(display_line[0], display_0);
		strcpy(display_line[1], "IP address");
		strcpy(display_line[2], display_2);
		strcpy(display_line[3], display_3);
		display_changed = TRUE;
		old_display_state = IP_SSID_DISPLAY;
		display_state = DISPLAY_WAIT_4_CHANGE;
		break;
	case AT_COMMAND:
		strcpy(display_line[0], " COMMAND: ");
		strcpy(display_line[1], "    1/2   ");
		strcpy(display_line[2], "    AT    ");
		strcpy(display_line[3], "          ");
		display_changed = TRUE;
		display_state = DISPLAY_WAIT_4_CHANGE;
		break;

	case AT_NSTCP_COMMAND:
		strcpy(display_line[0], " COMMAND: ");
		strcpy(display_line[1], "    2/2   ");
		strcpy(display_line[2], "AT+NSTCP= ");
		strcpy(display_line[3], " 65001,1  ");
		display_changed = TRUE;
		display_state = DISPLAY_WAIT_4_CHANGE;
		break;

	case DISPLAY_WAIT_4_CHANGE:
		break;


	default:
		break;



	}
}





