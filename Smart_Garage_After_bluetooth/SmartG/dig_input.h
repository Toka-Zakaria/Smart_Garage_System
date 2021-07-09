/*
 * DIO.h
 *
 * Created: 4/22/2017 2:30:13 PM
 *  Author: A.Aboelmakarem
 */ 

#include <avr/io.h>
#include "common.h"

void DIO_WritePortVal(char Port_Num,char Val);
char DIO_ReadPortVal(char Port_Num);
void DIO_WritePinVal(char Pin_Num, char Val);
char DIO_ReadPinVal(char Pin_Num);
void DIO_Init();

/**********************Configuration****************/
#define DDRA_INIT    0b00000000
#define DDRB_INIT    0b11000000
#define DDRC_INIT    0b11111111
#define DDRD_INIT    0b11111111

#define PORTA_INIT   0b00000000
#define PORTB_INIT   0b00000000
#define PORTC_INIT   0b00000000
#define PORTD_INIT   0b00000000



