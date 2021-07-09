/*
 * keypad_driver.h
 *
 * Created: 2/24/2018 4:06:38 PM
 *  Author: Mohamed Zaghlol
 */ 


#ifndef KEYPAD_DRIVER_H_
#define KEYPAD_DRIVER_H_
#include <avr/io.h>

#define NOTPRESSED 0xff
#define K_DIR DDRA
#define K_PORT PORTA
#define K_PIN PINA



void keypad_init();
char keypad_check();



#endif /* KEYPAD_DRIVER_H_ */