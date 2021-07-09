 /******************************************************************************
 *
 * Module: INT2 (external interrupt 2)
 *
 * File Name: int2.c
 *
 * Description: Source file for the INT2 driver
 *
 * Author: Abdelrahman El-Behairy
 *
 *******************************************************************************/

#include "int2.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variable to hold the address of the call back functions for the application */
static volatile void (*g_int2CallBackPtr)(void) = NULL_PTR;

/*******************************************************************************
*                          ISR's Definitions                                  *
*******************************************************************************/

ISR (INT2_vect)
{
	if(g_int2CallBackPtr != NULL_PTR)
		{
			/* Call the Call Back function after the external interrupt pin triggered an interrupt */
			(g_int2CallBackPtr)();
		}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/* Description : Function to initialize the INT2 pin */
void INT2_init(void)
{
	CLEAR_BIT(DDRD,PB2);	/*Set the PB2 (INT2) pin as input pin*/
	SET_BIT(GICR,INT2);		/*Enable the INT2 interrupt*/
	SET_BIT(SREG,7);		/*Enable the I-bit (Global Interrupt Enable)*/
}

/* Description : Function to set the INT2 trigger edge type */
void INT2_setEdgeType (EdgeType a_edge)
{
	/*MCUCSR ==> ISC2 =0 for falling edge
	 *MCUCSR ==> ISC2 =1 for rising edge */
	MCUCR = (MCUCR & 0xBF) | (a_edge << 6);
}

/* Description : Function to set the call back address of INT2 interrupt */
void INT2_setCallBack(void (*a_ptr)(void))
{
	/* put the given address in the global pointer to function to hold it and therefore you can call back its function */
	g_int2CallBackPtr=a_ptr;
}

/* Description : Function to disable the INT2 pin */
void INT2_Deinit(void)
{
	CLEAR_BIT(GICR,INT2);		/*Disable the INT2 interrupt*/
}
