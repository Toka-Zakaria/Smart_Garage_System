/**********************************************************************************
 * [FILE NAME]: motor.c
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Nov 5, 2020
 *
 * [Description]: Functions will be used to work with Servo motor.
 *
 ***********************************************************************************/

#include"motor.h"
/***************************************************************************************************
 * [Function Name]: Timer1_Fast_PWM_Init
 *
 * [Description]:  Function to generate pulse duration to enable Servo motor to work
 *
 * [Args]:         unsigned short duty_cycle
 *
 * [In]            duty cycle
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/

void Timer1_Fast_PWM_Init(unsigned short duty_cycle)
{
	TCNT1 = 0;		/* Set timer1 initial count to zero */
	ICR1 = 2499;	/* Set TOP count for timer1 in ICR1 register */

	OCR1A = duty_cycle+1; /* Set the compare value */
	OCR1B = duty_cycle; /* Set the compare value */
	TCCR1A = (1<<WGM11) | (1<<COM1B1);
	TCCR1B = (1<<WGM12) | (1<<WGM13) | (1<<CS10) | (1<<CS11);
}

/***************************************************************************************************
 * [Function Name]: motor_on_90
 *
 * [Description]:  Function to make the motor move with angle 90 degree
 *
 * [Args]:         NONE
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/

void motor_on_90(void)
{
	Timer1_Fast_PWM_Init(80);	/* Set Servo shaft at 90° position by 1.5 ms pulse */
	_delay_ms(1000);

}/*End of motor_onClockWise*/

/***************************************************************************************************
 * [Function Name]: motor_on_0
 *
 * [Description]:  Function to make the motor move to the equilibrium position 0 degree
 *
 * [Args]:         NONE
 *
 * [In]            NONE
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/

void motor_on_0(void)
{
	Timer1_Fast_PWM_Init(200);	/* Set Servo shaft at 0° position by 1 ms pulse */
	_delay_ms(1000);


}/*End of motor_onClockWise*/


