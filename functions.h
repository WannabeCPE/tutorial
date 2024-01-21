//******************************************************************************
//
//  Description: This file contains the Function prototypes
//
//  Jim Carlson
//  Aug 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************
// Functions

// Initialization
void Init_Conditions(void);

// Interrupts
void enable_interrupts(void);
__interrupt void Timer1_A0_ISR(void);
__interrupt void TIMER0_A1_ISR(void);
__interrupt void Timer0_B0_ISR(void);
__interrupt void TIMER0_B1_ISR(void);
__interrupt void switch_interrupt(void);
__interrupt void eUSCI_B0_ISR(void);
__interrupt void eUSCI_A0_ISR(void);
__interrupt void eUSCI_A3_ISR(void);
__interrupt void Timer1_B0_ISR(void);
__interrupt void TIMER1_B1_ISR(void);

// State machines for main
void display_state_machine(void);
void drive_state_machine(void);

// Analog to Digital Converter
void Init_ADC(void);
void ADC_Process(void);
void HEXtoBCD(int hex_value);
void INTtoBCD(int hex_value);
void add_decimal(void);
void adc_line2(char location);
void adc_line3(char location);
void adc_line4(char location);
void adc_white_calibration(char location);
void adc_black_calibration(char location);
unsigned int convert_to_mA( unsigned int volts, unsigned int calc);

//------------------------------------------------------------------------------
// Clocks
void Init_Clocks(void);

//------------------------------------------------------------------------------
// DAC
void Init_DAC(void);

//------------------------------------------------------------------------------
// IOT
void IOT_Process(void);             // Process IOT messages
void check_iot_rec(void);
void determine_iot(void);
void iot_system_init(void);
void iot_meassage_type(void);
void iot_process(void);
void iot_process_simple(void);
void iot_clean_buffer(void);
void iot_test(void);
void iot_wakeup(void);
void query_iot(void);
void iot_config(void);
void get_set_iot(char getset, char feature);
void iot_config_dump(void);
void set_network_iot(void);
void set_ssid_iot(char location);
void get_iot(void);
void set_iot(void);
void AT_iot(void);
void AT_factory(void);    // AT+F
void STS_iot(void);
void process_iot(void);
void iot_message(void);
void iot_message_ipaddr(char message_type);
void iot_message_ssid(unsigned int offset);
void iot_car_cntl(void);
void iot_write_data(void);
void set_iot_baudrate(char baud);
void iot_reset(void);
void change_comm(void);
void iot_factory_default(void);
void iot_hardware_reset(void);
void set_location_iot(char location);
void iot_class(void);
void iot_message_macaddr(void);
void send_ssid(void);
void iot_ping(void);
void iot_message_scanning(void);
void ip_addr(void);
void grab_char(void);

//------------------------------------------------------------------------------
// LED Configurations
void Init_LEDs(void);
void IR_LED_control(char selection);
void Backlite_control(char selection);

//------------------------------------------------------------------------------
  // LCD
void Display_Process(void);
void Display_Update(char p_L1,char p_L2,char p_L3,char p_L4);
void enable_display_update(void);
void update_string(char *string_data, int string);
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);

void lcd_power_on(void);
void lcd_write_line1(void);
void lcd_write_line2(void);
//void lcd_draw_time_page(void);
//void lcd_power_off(void);
void lcd_enter_sleep(void);
void lcd_exit_sleep(void);
//void lcd_write(unsigned char c);
//void out_lcd(unsigned char c);

void Write_LCD_Ins(char instruction);
void Write_LCD_Data(char data);
void ClrDisplay(void);
void ClrDisplay_Buffer_0(void);
void ClrDisplay_Buffer_1(void);
void ClrDisplay_Buffer_2(void);
void ClrDisplay_Buffer_3(void);

void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_4line(void);
void lcd_out(char *s, char line, char position);
void lcd_rotate(char view);
void Display(void);
void get_course_timer_info(void);
void display_command(void);

//void lcd_write(char data, char command);
void lcd_write(unsigned char c);
void lcd_write_line1(void);
void lcd_write_line2(void);
void lcd_write_line3(void);


void lcd_command( char data);
void LCD_test(void);
void LCD_iot_meassage_print(int nema_index);
void display_ADC (void);

// Menu
void Menu_Process(void);


// Ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
//void Init_Port3(char pin_type);
void Init_Port3(void);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);
void Init_Port7(void);
void Init_Port8(void);
void Init_PortJ(void);

// Serial
void Init_Serial(char speed);
void Init_Serial_UCA0(char speed);
void Init_Serial_UCA1(char speed);
void Init_Serial_UCA3(char speed);
void Transmit_U(void);
void alphabet(void);
void outchar(char character);
void print_CR(void);
void menu(void);
void grab_a_character(void);
int wait_for_character(void);
void increment_usb_rx_ring(void);
void increment_iot_rx_ring(void);
void menu_program(void);
void outhex (unsigned int hexvalue);
void outshorthex (unsigned int hexvalue);
void serialtest_line1(void);
void out_wifi(char character);
void usb_process_buffer(void);
void iot_process_buffer(void);
void transmit_2_pc(void);
void transmit_2_iot(void);
void baud(void);
void carrot_command_buffer(void);
void iot_command_buffer(void);
void get_drive_data(void);

// SPI
void Init_SPI_B0(void);
void SPI_B0_write(char byte);
void Init_SPI_B1(void);
void SPI_B1_write(char byte);
void spi_rs_data(void);
void spi_rs_command(void);
void spi_LCD_idle(void);
void spi_LCD_active(void);
void SPI_test(void);
void WriteIns(char instruction);
void WriteData(char data);
void SPI_test(void);


//void LCD_PRINT(char *d, char line);
//void LCD_COMMAND( char cData);
//void LCD_INIT();
void delay_ms( int duration_time);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);
void Init_Switch(void);
void Switch_Process(void);
void Switch1_Process(void);
void Switch2_Process(void);
void menu_act(void);
void menu_select(void);
void menu(void);
void main_menu_sel(void);




// Timers
void Init_Timers(void);
void Init_Timer_A0(void);
void Init_Timer_A1(void);
void Init_Timer_A2(void);
void Init_Timer_A3(void);
void Init_Timer_B0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);

void usleep(unsigned int usec);
void usleep10(unsigned int usec);
void five_msec_sleep(unsigned int msec);
void measure_delay(void);
void out_control_words(void);

// Wheels
void all_wheels_off(void);
void left_wheel_forward_on(void);
void left_wheel_reverse_on(void);
void left_wheels_off(void);
void right_wheel_forward_on(void);
void right_wheel_reverse_on(void);
void right_wheels_off(void);
void wheels(void);
void WheelControl(void);


// my drive functions
void motorsOff(void);
void driveForward(void);
void driveReverse(void);
void spinLeft(void);
void spinRight(void);
void turnLeft(int p1, int p2);
void turnRight(int p1, int p2);
void backRight(void);
void followLine(void);










