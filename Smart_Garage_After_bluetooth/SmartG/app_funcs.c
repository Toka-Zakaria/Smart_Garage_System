/**********************************************************************************
 * [FILE NAME]:  application_functions.c
 *
 * [AUTHORS]: Toka Zakaria Mohamed Ramadan
 *           Abdelrahman El-Behairy
 *           Hatem Salah
 *
 * [DATE CREATED]: April 9, 2021
 *
 * [Description]: File to contain all functions of the application.
 ***********************************************************************************/

#include "app_funcs.h"
#include "timer.h"

uint8 g_feesCounter = 0;

/***************************************************************************************************
 * [Function Name]: open_motor_timer
 *
 * [Description]:  Function to hold the motor stopped for some time, indicate to the door
 *                 is open, after time has finished, it would call another function to force it
 *                 to move in opposite direction to indicate the door is closing
 *
 * [Args]:         NONE
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
void open_motor_timer(void)
{
	g_tickFlag++;

	if( g_tickFlag < MAXIMUM_SECONDS_OPENING)
	{

		motor_on_90();
		/*
		 * Open the lightning system
		 */
		SET_BIT(LED_DATA_PORT,LED_PIN);

	}/*End of if condition*/

	/*
	 * As long as g_tickFlag reaches the maximum value of seconds
	 * so the LCD will stop displaying the message
	 */
	else if(g_tickFlag == MAXIMUM_SECONDS_OPENING)
	{

		/*
		 * clear LCD screen after displaying the last message
		 */
		LCD_clearScreen();
		/*
		 *   1-display a message for the user to "Car passed"
		 *   2-force arrow of the LCD to go to the second line
		 *   3-display a message for the user "Door is closing now!"
		 */
		LCD_displayStringRowColumn(0,0,"Car passed");
		LCD_goToRowColumn(1,0);
		LCD_displayStringRowColumn(1,0,"Door is closing now!");
		motor_on_0();
		CLEAR_BIT(LED_DATA_PORT,LED_PIN);
		_delay_ms(3000);

		Timer_DeInit(Timer1);
		g_tickFlag= 0;
		
		g_holdSystem = RESUME_SYSTEM;
		LCD_clearScreen();
		

	}/*End of else if condition*/

	}/*End of open_motor_timer function*/

/***************************************************************************************************
 * [Function Name]: displayID
 *
 * [Description]:  Function to give Car parking its ID
 *
 *
 * [Args]:         NONE
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/

void displayID(void)
{

	motor_on_90();
	SET_BIT(LED_DATA_PORT,LED_PIN);
	
	Timer_setCallBack(open_motor_timer, Timer1);
	Timer_init(&g_timer);

}/*end of the displayID function*/






void startTime (void)
{
	/*Checking if it's the first car to enter the garage (no cars already parking in the garage)*/
	if(emptySpaces==3)
	{
		Timer_init(&g_feesTimer);   //start the Timer with the g_feesTimer configuration structure
		Timer_setCallBack(countTime, Timer0);
	}
	g_indicator[currentID]=1;
	g_feesCounter=0;
}





void countTime(void)
{
	if(g_feesCounter==32)
	{
		_delay_ms(500);
		/*looping on the indicators array to add the time passed for any car parked in the garage*/
		for(uint8 i=0;i<4;i++){
			if(g_indicator[i]==1)
			{
				g_count[i]+=1;
			}
		}
		g_feesCounter=0;
	}
	else
	{
		g_feesCounter++;
	}

}



void endTime (uint8 i)
{
	/*Calculating the fees (number of seconds * 5 dollars per second)*/
	fee=g_count[i]*5;

	/*reset the seconds counter for this ID*/
	g_count[i]=0;

	/*reset the indicator to zero as the place is now free*/
	g_indicator[i]=0;

	/*increase the empty spaces variable by 1*/
	emptySpaces++;

	/*let currentID tracker go to a free spot*/
	currentID++;
	
	LCD_displayString("FEES =");
	LCD_goToRowColumn(1,0);
	LCD_intgerToString(fee);
	LCD_displayCharacter('$');
	total_revenue = total_revenue + fee;

	/* Disable the timer if the garage has no cars*/
	if(emptySpaces==4)
		{
			//Timer_DeInit(Timer1);
		}
}

/***************************************************************************************************
 * [Function Name]: flameAlarm
 *
 * [Description]:  Function to be called when there is a fire to :
 * 					1- Open the gate
 * 					2- Display on the LCD that there is a fire
 * 					3- Start the buzzer and the red led
 *
 *
 * [Args]:         NONE
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/
// extern void flameAlarm(void)
// {
// 	/*
// 	 * Open the gate
// 	 */
// 	motor_on_90();
// 
// 	/*
// 	 * Open the lightning system
// 	 */
// 	SET_BIT(LED_DATA_PORT,LED_PIN);
// 
// 	/*
// 	 * Start the buzzer and the red led
// 	 */
// 	buzzer_on();
// 	SET_BIT(RED_LED_PORT,RED_LED_PIN);
// 
// 	/*
// 	 * Display a message to the user to inform him that there is a fire
// 	 * */
// 	LCD_clearScreen();
// 	LCD_displayString("FIRE WARNING!!!");
// 	LCD_goToRowColumn(1,0);
// 	LCD_displayString("EVACUATE NOW");
// 
// 	/*
// 	 * Wait until the flame sensor read 0 (the fire has been put out)
// 	 */
// 	while(BIT_IS_SET(INT2_INPUT_PORT,INT2_PIN));
// 
// 	/*
// 	 * call the function of motor_on_0
// 	 * to force the motor to return on its initial value
// 	 * in stopping state
// 	 */
// 	motor_on_0();
// 
// 	/*
// 	 * Stop the buzzer and the red led
// 	 */
// 	buzzer_off();
// 	CLEAR_BIT(RED_LED_PORT,RED_LED_PIN);
// }





