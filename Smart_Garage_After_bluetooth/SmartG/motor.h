/**********************************************************************************
 * [FILE NAME]: motor.h
 *
 * [AUTHOR]: Toka Zakaria Mohamed Ramadan
 *
 * [DATE CREATED]: Nov 5, 2020
 *
 * [Description]:File of All types Declaration and Functions prototypes of DC Motor.
 ***********************************************************************************/

#ifndef MOTOR_H_
#define MOTOR_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

#define MOTOR_DIRECTION_PORT                  DDRD
#define MOTOR_PIN                             PD4
#define MOTOR_DATA_PORT                      PORTD

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
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
void Timer1_Fast_PWM_Init(unsigned short duty_cycle);
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
void motor_on_90(void);
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
void motor_on_0(void);



#endif /* MOTOR_H_ */
