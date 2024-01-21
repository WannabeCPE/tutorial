//------------------------------------------------------------------------------
//
//  Description: This file contains the Drive, Reverse, and Turn Functions 
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

extern volatile unsigned int ADC_Left_Detect;
extern volatile unsigned int ADC_Right_Detect;
extern volatile unsigned int line_follow_ready;
extern volatile char current_circle_state;
volatile char previous_circle_state = NONE;
volatile int previous_error = RESET_STATE;
extern unsigned int left_val, right_val;


void driveForward(void) {
	motorsOff();
	RIGHT_FORWARD_SPEED = 15000;
	LEFT_FORWARD_SPEED = 16000;
}

void driveReverse(void) {
	motorsOff();
	RIGHT_REVERSE_SPEED = 20000;
	LEFT_REVERSE_SPEED = 20000;
	


}

void motorsOff(void) {
	RIGHT_FORWARD_SPEED = WHEEL_OFF;
	LEFT_FORWARD_SPEED = WHEEL_OFF;
	RIGHT_REVERSE_SPEED = WHEEL_OFF;
	LEFT_REVERSE_SPEED = WHEEL_OFF;
}

void spinLeft(void) {
	motorsOff();
	RIGHT_FORWARD_SPEED = 20000 ;
	LEFT_REVERSE_SPEED = 21000;
}

void spinRight(void) {
	motorsOff();
	RIGHT_REVERSE_SPEED = 20000;
	LEFT_FORWARD_SPEED = 21000;

}

void turnLeft(int pwm_fast, int pwm_slow) {
	motorsOff();

	RIGHT_FORWARD_SPEED = pwm_fast;
	LEFT_FORWARD_SPEED = pwm_slow;
	
	
}
void turnRight(int pwm_fast, int pwm_slow) {
	motorsOff();

	RIGHT_FORWARD_SPEED = pwm_slow;
	LEFT_FORWARD_SPEED = pwm_fast;
	
	
}

void backRight(void) {
	motorsOff();
	LEFT_REVERSE_SPEED = LEFT_REVERSE_WHEEL_ON;
}


void followLine(void) {
	motorsOff();

	if (line_follow_ready) {
		line_follow_ready = RESET_STATE;
		if (current_circle_state == WHITE_STATE) {
			switch (previous_circle_state) {
			case LEFT_SIDE:
				turnLeft(12000, 8000);
				current_circle_state = LEFT_SIDE;
				break;
			case RIGHT_SIDE:
				turnLeft(14000, 6000);
				current_circle_state = RIGHT_SIDE;
				break;
			default:
				motorsOff();
				break;
			}

		}
		else if (current_circle_state == BLACK_LINE) {
			turnLeft(12000, 6000);
		}
		else {

			WheelControl();
		}
		previous_circle_state = current_circle_state;
	
	}
	
	line_follow_ready = TRUE;

	
}

void WheelControl(void) {
	int pwm_fast, pwm_slow;
	int total_error, delta_error, e;
	e = left_val - right_val;
	delta_error = e - previous_error;
	previous_error = e;
	
	total_error = (e + delta_error) * 100;
	if (total_error < 0) {
		pwm_fast = CRUISE_SPEED_LEFT - total_error;
		pwm_slow = CRUISE_SPEED_RIGHT + total_error;
		if (pwm_fast > 32000) {
			pwm_fast = 32000;
		}
		else if (pwm_fast < 0) {
			pwm_fast = 0;
		}
		if (pwm_slow > 32000) {
			pwm_slow = 32000;
		}
		else if (pwm_slow < 0) {
			pwm_slow = 0;
		}
		turnRight(pwm_fast, pwm_slow);
	}
	else if (total_error >= 0) {
		pwm_fast = CRUISE_SPEED_RIGHT + total_error;
		pwm_slow = CRUISE_SPEED_LEFT - total_error;
		if (pwm_fast > 32000) {
			pwm_fast = 32000;
		}
		else if (pwm_fast < 0) {
			pwm_fast = 0;
		}
		if (pwm_slow > 32000) {
			pwm_slow = 32000;
		}
		else if (pwm_slow < 0) {
			pwm_slow = 0;
		}
		turnLeft(pwm_fast, pwm_slow);
	}
	

}
