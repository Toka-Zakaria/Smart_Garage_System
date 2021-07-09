/*
 * common.h
 *
 * Created: 2/3/2021 9:50:56 PM
 *  Author: A.yaser
 */ 


#ifndef COMMON_H_
#define COMMON_H_


#define SET_BIT(reg,pos)         reg|=(1<<pos)
#define CLR_BIT(reg,pos)         reg&=~(1<<pos)
#define TOGGLE_BIT(reg,pos)      reg^=(1<<pos)
#define GET_BIT(reg,pos)         (reg &(1<<pos))>>pos


#endif /* COMMON_H_ */