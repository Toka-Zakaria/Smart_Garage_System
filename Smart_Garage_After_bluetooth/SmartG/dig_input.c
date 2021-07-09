/*
 * DIO.c
 *
 * Created: 4/22/2017 2:29:45 PM
 *  Author: A.Aboelmakarem
 */

#include "dig_input.h"

void DIO_WritePortVal(char Port_Num,char Val)
{
	switch(Port_Num)
	{
		case 0:
		PORTA=Val;
		break;
		
		case 1:
		PORTB=Val;
		break;
		
		case 2:
		PORTC=Val;
		break;
		
		case 3:
		PORTD=Val;
		break;
		
		default:
		break;
	}
}

char DIO_ReadPortVal(char Port_Num)
{
	char val;
	switch(Port_Num)
	{
		case 0:
		val=PINA;
		break;
		
		case 1:
		val=PINB;
		break;
		
		case 2: 
		val=PINC;
		break;
		
		case 3:
		val=PIND;
		break;
		
		default:
		val=0;
		break;
	}
	
	return val;
	
}


void DIO_WritePinVal(char Pin_Num, char Val)
{
	char Port_Num = Pin_Num/8;
	char Pin_Index = Pin_Num % 8;
	switch(Port_Num)
	{
		case 0:
		if(Val==0)
		CLR_BIT(PORTA,Pin_Index);
		else
		SET_BIT(PORTA,Pin_Index);
		break;
		
		case 1:
		if(Val==0)
		CLR_BIT(PORTB,Pin_Index);
		else
		SET_BIT(PORTB,Pin_Index);
		break;		

		case 2:
		if(Val==0)
		CLR_BIT(PORTC,Pin_Index);
		else
		SET_BIT(PORTC,Pin_Index);
		break;		

		case 3:
		if(Val==0)
		CLR_BIT(PORTD,Pin_Index);
		else
		SET_BIT(PORTD,Pin_Index);
		break;	
		
		default:
		break;
	}
} 

char DIO_ReadPinVal(char Pin_Num)
{
	char val;
	char Port_Num= Pin_Num /8 ;
	char Pin_Index= Pin_Num %8;
	
	switch (Port_Num)
	{
		case 0:		
		val=GET_BIT(PINA,Pin_Index);
		break;
		
		case 1:
		val=GET_BIT(PINB,Pin_Index);
		break;
		
		case 2:
		val=GET_BIT(PINC,Pin_Index);
		break;	
			
		case 3:
		val=GET_BIT(PIND,Pin_Index);
		break;
		
		default:
		val=0;
		break;
	}
	return val;
}

void DIO_Init()
{
	DDRA=DDRA_INIT;
	DDRB=DDRB_INIT;
	DDRC=DDRC_INIT;
	DDRD=DDRD_INIT;
	
	
	PORTA=PORTA_INIT;
	PORTB=PORTB_INIT;
	PORTC=PORTC_INIT;
	PORTD=PORTD_INIT;
	
}