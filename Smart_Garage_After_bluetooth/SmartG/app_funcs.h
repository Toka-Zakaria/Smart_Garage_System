/**********************************************************************************
 * [FILE NAME]:  application_functions.h
 *
 * [AUTHORS]: Toka Zakaria Mohamed Ramadan
 *           Abdelrahman El-Behairy
 *           Hatem Salah
 *
 * [DATE CREATED]: April 9, 2021
 *
 * [Description]: File to contain all functions of the application.
 ***********************************************************************************/


#ifndef APP_FUNCS_H_
#define APP_FUNCS_H_

#include <string.h>

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"
#include "std_macros.h"

#include "timer.h"
#include "motor.h"
#include "lcd.h"
#include "keypad.h"
#include "int2.h"

#include "USART.h"
#include "DIO.h"


/**************************************************************************
 *                        Preprocessor Macros                             *
 * ************************************************************************/

/*for timer*/
#define START_VALUE					  0
#define COMPARE_VALUE1				  8000
#define COMPARE_VALUE2				  250

#define MAXIMUM_SECONDS_OPENING       5

/*for system application*/
#define RESUME_SYSTEM                 0
#define HOLD_SYSTEM                   1

#define GUEST                        '1'
#define SUBSCRIBER                   '2'

#define ID_SELECTION                 '3'
#define ID_SIZE                       3

#define LED_PIN                      PB5
#define LED_DATA_PORT                PORTB
#define LED_DIRECTION_PORT           DDRB
#define LED_INPUT_PORT               PINB


#define RED_LED_PORT PORTC
#define RED_LED_PIN PC1
#define INT2_PIN PB2
#define INT2_INPUT_PORT PINB


// IR Entrance Sensor
#define IR_DIRECTION_PORT            DDRD
#define IR_PIN		                 PD3
#define IR_DATA_PORT                 PORTD
#define IR_INPUT_PORT                PIND

// IR Exit Sensor
#define IR2_DIRECTION_PORT            DDRD
#define IR2_PIN		                  PD2
#define IR2_DATA_PORT                 PORTD
#define IR2_INPUT_PORT                PIND

// Fees Button
#define FEES_PUSH_BUTTON_INPUT_PORT  PIND
#define FEES_PUSH_BUTTON_PIN		 PD1

// Smart Led For Bluetooth
#define SMART_LED   9  


extern uint8 g_tickFlag;
extern uint8 g_holdSystem;
extern uint8 g_feesCounter;
extern Timer_ConfigType g_timer;
extern Timer_ConfigType g_feesTimer;
extern uint8 currentID;
extern uint8 emptySpaces;
extern const char *guestID[];
extern uint8 g_indicator[4];
extern uint8 g_count[4];
uint16 fee;
uint16 total_revenue ;


void open_motor_timer(void);
void displayID(void);
void startTime (void);
void countTime(void);
void endTime (uint8 i);
void flameAlarm(void);

#endif /* APP_FUNCS_H_ */
