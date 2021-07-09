/*
 * Bluetooth_test.c
 *
 * Created: 5/28/2021 4:12:51 PM
 *  Author: dalia
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART.h"
#include "std_macros.h"
#include "DIO.h"
# define  F_CPU 8000000UL
#include <util/delay.h>
#define LED_1   9    // put the value of led 1 pin number in port A (0-7)
#define LED_2   10   // put the value of led 2 pin number in port A (0-7)
#define LED_3   14  

volatile char First_time =0;
volatile char First_time_data  ;

char Recieved_data  ;
char operation =0;
const char * Operation_ptr = &operation ;

int total_cars ;
int total_revenue ;
int empty_places;
int user_ID;
int Fees;
char enter_state;


int main(void)
{
	DDRB = 0b00000110;
	
	__asm__("SEI");                                //enable global interrupt

	UART_vInit(9600);
	while (1)
	{
	
    while(First_time==1)
    {
		
	//DIO_WritePinVal(LED_1,1);
	
		operation = First_time_data;
		
		if (atoi(Operation_ptr) == 1)          // ADMIN_USER Operation
		
		{
			Recieved_data= UART_Receive();
			
			if  (Recieved_data == 1)           // Admin Mode
			{
				PORTB = 0b00000010;
				
				total_cars = 7;                    // get the total cars of the day variable   *****
				UART_Transmit(total_cars);
				
				Recieved_data = UART_Receive();
				if (Recieved_data == 1)
				{
					total_revenue = 235;               // add all of the fees of the day   ****
					UART_Sendint(total_revenue,3);
				}
				
				
				
			}
			
			else if (Recieved_data == 0)        // User Mode
			{
				//DIO_WritePinVal(LED_1,1);
				PORTB = 0b00000010;
				
				enter_state = 0;                // get the state variable ****
				UART_Transmit(enter_state);     // send if he if entering or leaving 
				
			}
			operation= UART_Receive();
		}
		if(operation == 2)                    // GUEST_SUBSCRIBER Operation
		{
			PORTB = 0b00000000;
			
			Recieved_data= UART_Receive();       
			
			if (Recieved_data== 1)            // Guest Mode
			{
				if(enter_state== 1)            
				{
					empty_places = 3;               // get the empty places ****
					UART_Transmit(empty_places);
					Recieved_data= UART_Receive();     
					if (Recieved_data ==1)             //we have empty places
					{
						user_ID =255  ;                //overflow for any number above 255???
						UART_Sendint(user_ID,4);       // Use the ID generation function ****
						//open_motor_timer();
					}
					else                             //we have no empty places
					{
						First_time = 0;
						SET_BIT(UCSRB,RXCIE) ;
						break;
					}
					
					
				}
				
				
			}
			else             // Subscriber Mode
			{
				Recieved_data=UART_Receive();
				if (Recieved_data == 1)         // Password correct
				{
						//open_motor_timer();
				}
				
			}
			operation= UART_Receive();
		}
		if(operation == 3)                        // leaving Guest Operation
		{
			//DIO_WritePinVal(LED_1,1);
			user_ID = UART_Receive();             // Receive id code(1-4)
			/*
			check if correct id then get its fees
			*/
			Fees = 203;
			UART_Sendint(Fees,3);
			Recieved_data =UART_Receive() ;
			if(Recieved_data == 1)                //Money is paid
			{
				//DIO_WritePinVal(LED_1,0);
				//open_motor_timer();
			}
			operation= UART_Receive();
		}
		if (operation == 4)
		{
			//Light control
			
			//DIO_WritePinVal(LED_1,1);
			Recieved_data=UART_Receive();
			if (Recieved_data == 1)              //Turn ON LEDS
			{
				
				//DIO_WritePinVal(SMART_LED,1);
				PORTB = 0b00000100;
			}
			else if(Recieved_data == 0)         //Turn OFF LEDS
			{
				
				//DIO_WritePinVal(SMART_LED,0);
				PORTB = 0b00000000;
			}
			
		}
		First_time = 0;
		SET_BIT(UCSRB,RXCIE) ;
	}

	}
}

ISR(USART_RXC_vect)
{
	//PORTB = 0b00000010;
	First_time = 1;
	First_time_data = UDR;
	CLR_BIT(UCSRB,RXCIE) ;
	
}


