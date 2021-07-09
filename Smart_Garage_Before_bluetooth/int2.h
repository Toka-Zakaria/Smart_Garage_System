 /******************************************************************************
 *
 * Module: INT2 (external interrupt 2)
 *
 * File Name: int2.h
 *
 * Description: Header file for the INT2 driver
 *
 * Author: Abdelrahman El-Behairy
 *
 *******************************************************************************/

#ifndef INT2_H_
#define INT2_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"


/*******************************************************************************
 *                         Types Declarations                                  *
 *******************************************************************************/

typedef enum {
	FALLING=0,RISING=1
}EdgeType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Description : Function to initialize the INT2 pin */
void INT2_init(void);

/* Description : Function to set the INT2 trigger edge type */
void INT2_setEdgeType (EdgeType);

/* Description : Function to set the call back address of INT2 interrupt */
void INT2_setCallBack(void (*a_ptr)(void));

/* Description : Function to disable the INT2 pin */
void INT2_Deinit(void);

#endif /* INT2_H_ */
