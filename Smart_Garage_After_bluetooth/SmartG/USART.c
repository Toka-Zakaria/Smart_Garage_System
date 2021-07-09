/*
 * USART.c
 *
 * Created: 10/6/2019 1:20:08 PM
 *  Author: Mohamed Zaghlol
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include "common_macros.h"

void UART_vInit(unsigned long baud)
{
	/*1 - Choose baud rate that will be used by sender and receiver by writing to UBRRL/UBRRH*/
	unsigned short UBRR ;
	UBRR=(F_CPU/(16*baud))-1 ;
	UBRRH=(unsigned char)(UBRR>>8);
	UBRRL=(unsigned char)UBRR;
	/*2 - Enable USART Sender & Receiver*/
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,RXCIE);
	/*3 - Choose number of data bits to be sent,parity and stop bits from UCSRC
	, We will work with 8 bits data,1 stop bit and no parity bits*/
	UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
}

void UART_Transmit(char data)
{
	char Transmitted_data  ;
	char * TransData_ptr = &Transmitted_data ;
	/*Wait for UDR transmit buffer to be empty*/
	while(READ_BIT(UCSRA,UDRE)==0);
	/*Put data to UDR transmit buffer transmit*/
	itoa(data,TransData_ptr,10);
	UDR =*TransData_ptr;
}

char UART_Receive(void)
{
	char Recieved_data  ;
	char * RecData_ptr = &Recieved_data ;
	/*Wait for UDR receive buffer to be filled with data*/
	while(READ_BIT(UCSRA,RXC)==0);
	/*Receive data from UDR receive buffer*/
	Recieved_data = UDR;
	Recieved_data = atoi(RecData_ptr);
	return Recieved_data ;
}
void UART_Sendint (int number ,int nofdigits)
{
	char stringtodisp[nofdigits];
	itoa(number,stringtodisp,10);
	for(int i=0;i<=nofdigits-1;i++)   //loop till we find null terminator
	{
		while (! (UCSRA & (1 << UDRE)) );
		UDR = stringtodisp[i];
	}
	
}

 