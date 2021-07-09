/*
 * USART.h
 *
 * Created: 10/6/2019 1:19:54 PM
 *  Author: Mohamed Zaghlol
 */ 


#ifndef USART_H_
#define USART_H_
void UART_vInit(unsigned long baud);
void UART_Transmit(char data);
char UART_Receive(void);
void UART_Sendint (int number ,int nofdigits);
#endif /* USART_H_ */
