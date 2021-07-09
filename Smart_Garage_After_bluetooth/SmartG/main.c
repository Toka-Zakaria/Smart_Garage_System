/**********************************************************************************
 * [FILE NAME]:  application_functions.h
 *
 * [AUTHORS]: Toka Zakaria Mohamed Ramadan
 *            Abdelrahman El-Behairy
 *            Hatem Salah
 *            Dalia Ahmed
 *            Samar Elsayed
 *
 * [DATE CREATED]: April 9, 2021
 *
 * [Description]: File to contain all functions of the application.
 ***********************************************************************************/


#include "app_funcs.h"

uint8 g_tickFlag=0;
uint8 g_holdSystem = HOLD_SYSTEM;
uint8 slots = 8;
uint8 emptySpaces = 4;
const char *guestID[] = {"100", "200", "300", "400"};
const char *subsID [] = {"123", "321", "456", "654"};	
uint8 currentID = 4;

uint8 g_indicator[4];
uint8 g_count[4];

// Bluetooth Variables
volatile char First_time = 0;
volatile char First_time_data  ;

char Recieved_data  ;
char operation =0;
const char * Operation_ptr = &operation ;
char Transmitted_data  ;
char * TransData_ptr = &Transmitted_data ;

int total_cars = 0 ;
int user_ID;
int Fees;
char enter_state;


Timer_ConfigType g_timer = {START_VALUE, COMPARE_VALUE1, Timer1, F_CPU_1024, Compare, ChannelB};
Timer_ConfigType g_feesTimer = {START_VALUE, COMPARE_VALUE2, Timer0, F_CPU_1024, Compare, 0};

int main(){
	
	// To make led pin output
    DDRB  |= (1<<PB6);                //make Led Pin output
	SET_BIT(PORTB,PB1);               //make led pin initially  0
	
	
	//enable global interrupt
	__asm__("SEI");                                
	UART_vInit(9600);
	
	// To Disable JTAG
	MCUCSR |= (1<<JTD);
	MCUCSR |= (1<<JTD);
	
	// LCD initialization
	LCD_init();
	keypad_init();
	
	// INT2 initialization
// 	INT2_init();
// 	INT2_setEdgeType(RISING);
// 	INT2_setCallBack(flameAlarm);
	
	// OLD OR GUEST
	uint8 option;
	
	// Array to store ID of the user
	uint8 subID[ID_SIZE];
	
	// Correct ID Flag
	uint8 ID_flag = 0;
	
	// Loops Counter
	uint8 count;
	uint8 i;
	
	// Setting LED pin as output
	SET_BIT(LED_DIRECTION_PORT, LED_PIN);
	CLEAR_BIT(LED_DATA_PORT,LED_PIN); // LED is OFF
	
	// Enable General Interrupt BIT
	SREG |= (1<<7);

	// Initialize the IR by making the pin I/P.
	CLEAR_BIT(IR_DIRECTION_PORT,IR_PIN);
	CLEAR_BIT(IR2_DIRECTION_PORT,IR2_PIN);
	
	// initialize motor by making it o/p pin
	SET_BIT(MOTOR_DIRECTION_PORT, MOTOR_PIN);
	motor_on_0(); // motor is closed in the beginning	

	/******************************************************************************************
	 *                                      Application
	 *****************************************************************************************/
	LCD_displayString("SMART PARKING :D");
	while (1)
	{
		
		while (First_time == 0)
		{
				
	
		if (slots > 0){
			if( BIT_IS_CLEAR(IR_INPUT_PORT, IR_PIN ) ){
				
				
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Car is Found");
				LCD_goToRowColumn(1,0);
				LCD_displayStringRowColumn(1,0,"Welcome User!");

				
				// wait some seconds for these message to be
				// displayed on LCD, then clear the LCD message
				
				_delay_ms(3000);
				LCD_clearScreen();
				
				do
				{
					LCD_displayStringRowColumn(0,0,"Select option");
					LCD_goToRowColumn(1,0);
					LCD_displayStringRowColumn(1,0,"1:Guest 2:Sub");
					_delay_ms(200);

					
					// store the option selected in a variable
					option = keypad_check() ;

					// to force user to select 1 or 2
					if((option != GUEST) && (option != SUBSCRIBER)){
						LCD_clearScreen();
						LCD_displayStringRowColumn(0,0,"Wrong option");
						LCD_goToRowColumn(1,0);
						LCD_displayStringRowColumn(1,0,"Select 1 or 2");
						_delay_ms(2000);
					}
				}while ( (option != GUEST) && (option != SUBSCRIBER) );
				
				/******************************************************************************************
				 *                                     Guest Mode
				 *****************************************************************************************/
				if(option == GUEST)
				{	
					if(emptySpaces != 0){
						LCD_clearScreen();
						LCD_displayStringRowColumn(0,0,"Press 3, Please");
						LCD_goToRowColumn(1,0);
						LCD_displayStringRowColumn(1,0,"to get your ID");
						
						while( keypad_check() != ID_SELECTION);
						//access a valid element in the array
						currentID--;

						LCD_clearScreen();
						
						char sentence[32] = "Your ID is ";
						strncat( sentence, guestID[currentID], ID_SIZE);
						LCD_displayStringRowColumn(0,0, sentence);
						LCD_goToRowColumn(1,0);
						LCD_displayStringRowColumn(1,0,"Door is Open!");
						_delay_ms(2000);
						
						emptySpaces--;
						g_indicator[currentID]=1;
						displayID();
						total_cars = total_cars + 1;
						motor_on_0();
						startTime();							
					}
					else{
						// No more available space
						LCD_clearScreen();
						LCD_displayString("    Sorry !!");
						LCD_goToRowColumn(1,0);
						LCD_displayStringRowColumn(1,0,"No More Slots");
						_delay_ms(5000);
						LCD_clearScreen();
					}
				} // End of Guest MODE

				/******************************************************************************************
				 *                                    Subscriber Mode
				 *****************************************************************************************/
				else if(option == SUBSCRIBER)
				{

					
					// this delay to wait some seconds to
					// prevent the ID from storing '2'
					// and display it on LCD
					
					_delay_ms(1000);


					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Enter ID");
					LCD_goToRowColumn(1,0);
					LCD_displayStringRowColumn(1,0,"then press '='");
					
					_delay_ms(2000);
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Enter ID");
					LCD_goToRowColumn(1,0);
					
					// loop to store the ID user entered
ID_REQ:				for(count=0; count< ID_SIZE; count++){

						subID[count] = keypad_check();

						// Check if he entered a correct character
						// then print it and convert to a '*' 
						
						if ((subID[count]>= 0) && (subID[count]<= 9)){
							LCD_intgerToString(subID[count]);
						}
						else{
							LCD_displayCharacter(subID[count]);
						}

						// wait some seconds to display the ID then hide it
						_delay_ms(1000);

						// overwrite the number and put '*' to keep privacy
						LCD_goToRowColumn(1,count);
						LCD_displayCharacter('*');

						// Wait for a while to give time between presses
						_delay_ms(1000);

					} // End of for loop, now I have the ID given by the subscriber

					while( ( keypad_check() )!= '='){}

					// clear the screen after getting the ID !!!
					LCD_clearScreen();

					// Here we Compare the given ID and open the door
					// or ask the user to enter the correct ID
					
					for(i=0; i<4; i++){ 
						// to loop over subsID array
						for(count=0; count<ID_SIZE; count++){
							// to loop over my given ID
							if(subID[count] != subsID[i][count]){
								break;
							}
							if(count == 2){
								// Correct ID
								ID_flag = 1;
								LCD_displayString("Correct ID");
								LCD_goToRowColumn(1,0);
								LCD_displayStringRowColumn(1,0,"Door is Open");
								
								// Open the door for the Great Awesome Richie Richie Subscriber
								displayID();
								total_cars = total_cars + 1;
								Timer1_Fast_PWM_Init(200);	
								LCD_clearScreen();	
							}	
						}									
						if(ID_flag == 1){
							ID_flag = 0;
							break;
						}
						if(i == 3){
							// it's Surely a Wrong ID
							LCD_displayString("Wrong ID");
							LCD_goToRowColumn(1,0);
							LCD_displayStringRowColumn(1,0,"Type it Again !");
							_delay_ms(2000);
							LCD_clearScreen();
							LCD_displayStringRowColumn(0,0,"Enter ID");
							LCD_goToRowColumn(1,0);
							goto ID_REQ;
						}
					}		
				} // end of Subscriber MODE
				
				
				// to hold the whole program until the door opening
				// System Busy in opening door

				while((First_time == 0) && ((g_holdSystem != RESUME_SYSTEM) || (BIT_IS_CLEAR(IR_INPUT_PORT, IR_PIN))) ){}

				// return the state of the g_holdSystem to be hold again
				// after being RESUME to be ready for any required
				//  action to hold the system again
				 
				g_holdSystem = HOLD_SYSTEM;

				// clear LCD screen after displaying the last message
				LCD_clearScreen(); 
				
				// Someone is IN, slots are decreased
				slots--;
				
			}
			
			///////////////////////////////////////////////////////////////////////////////////////////////// SECOND IR
			// let's check the second IR
			
			else if(BIT_IS_CLEAR(IR2_INPUT_PORT,IR2_PIN)){
				
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,0,"Car is Found");
				LCD_goToRowColumn(1,0);
				LCD_displayStringRowColumn(1,0,"Welcome Back!");

				
				// wait some seconds for these message to be
				// displayed on LCD, then clear the LCD message
				
				_delay_ms(3000);
				LCD_clearScreen();
				
				do
				{
					LCD_displayStringRowColumn(0,0,"Select option");
					LCD_goToRowColumn(1,0);
					LCD_displayStringRowColumn(1,0,"1:Guest 2:Sub");
					_delay_ms(200);

					
					// store the option selected in a variable
					option = keypad_check() ;

					// to force user to select 1 or 2
					if((option != GUEST) && (option != SUBSCRIBER)){
						LCD_clearScreen();
						LCD_displayStringRowColumn(0,0,"Wrong option");
						LCD_goToRowColumn(1,0);
						LCD_displayStringRowColumn(1,0,"Select 1 or 2");
						_delay_ms(2000);
					}
				}while ( (option != GUEST) && (option != SUBSCRIBER) );
				
				
				/////////////////////////////////////////////////////////////////////////////////////////////////////
				///////////////////////////////////////////////GUEST MODE IN BACK////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////
				if(option == GUEST){
					
					// this delay to wait some seconds to
					// prevent the ID from storing '2'
					// and display it on LCD
					
					_delay_ms(1000);


					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Enter ID");
					LCD_goToRowColumn(1,0);
					LCD_displayStringRowColumn(1,0,"then press '='");
					
					_delay_ms(2000);
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Enter ID");
					LCD_goToRowColumn(1,0);
					
					// loop to store the ID user entered
ID_REQ_G2:			for(count=0; count< ID_SIZE; count++){

						subID[count] = keypad_check();

						// Check if he entered a correct character
						// then print it and convert to a '*'
						
						if ((subID[count]>= 0) && (subID[count]<= 9)){
							LCD_intgerToString(subID[count]);
						}
						else{
							LCD_displayCharacter(subID[count]);
						}

						// wait some seconds to display the ID then hide it
						_delay_ms(1000);

						// overwrite the number and put '*' to keep privacy
						LCD_goToRowColumn(1,count);
						LCD_displayCharacter('*');

						// Wait for a while to give time between presses
						_delay_ms(1000);

					} // End of for loop, now I have the ID given by the subscriber

					while( ( keypad_check() )!= '='){}

					// clear the screen after getting the ID !!!
					LCD_clearScreen();

					// Here we Compare the given ID and open the door
					// or ask the user to enter the correct ID
					
					for(i=0; i<4; i++){
						// to loop over subsID array
						for(count=0; count<ID_SIZE; count++){
							// to loop over my given ID
							if(subID[count] != guestID[i][count]){
								break;
							}
							if(count == 2){
								// Correct ID
								ID_flag = 1;
								if(g_indicator[i]==1){
										LCD_clearScreen();
										endTime(i);

										//Do nothing until the push button is pressed (fees are paid)
									
										while(keypad_check() != '='){};
										
										// Open the door for the Great Awesome Richie Richie Subscriber
										displayID();
										motor_on_0();
										LCD_clearScreen();
								}
								else{
									LCD_clearScreen();
									LCD_displayStringRowColumn(0,0,"Car is not");
									LCD_goToRowColumn(1,0);
									LCD_displayString("Here !");
									_delay_ms(2000);
									LCD_clearScreen();
								}							
							}
						}
						if(ID_flag == 1){
							ID_flag = 0;
							break;
						}
						if(i == 3){
							// it's Surely a Wrong ID
							LCD_displayString("Wrong ID");
							LCD_goToRowColumn(1,0);
							LCD_displayStringRowColumn(1,0,"Type it Again !");
							_delay_ms(2000);
							LCD_clearScreen();
							LCD_displayStringRowColumn(0,0,"Enter ID");
							LCD_goToRowColumn(1,0);
							goto ID_REQ_G2;
						}
					}
					
				}// GUEST MODE IS DONE
				
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////
				////////////////////////////////////////////////////SUBSCRIBER MODE////////////////////////////////////////////
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
				else if(option == SUBSCRIBER){
					
					// this delay to wait some seconds to
					// prevent the ID from storing '2'
					// and display it on LCD
					
					_delay_ms(1000);


					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Enter ID");
					LCD_goToRowColumn(1,0);
					LCD_displayStringRowColumn(1,0,"then press '='");
					
					_delay_ms(2000);
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Enter ID");
					LCD_goToRowColumn(1,0);
					
					// loop to store the ID user entered
ID_REQ_S3:			for(count=0; count< ID_SIZE; count++){

						subID[count] = keypad_check();

						// Check if he entered a correct character
						// then print it and convert to a '*'
						
						if ((subID[count]>= 0) && (subID[count]<= 9)){
							LCD_intgerToString(subID[count]);
						}
						else{
							LCD_displayCharacter(subID[count]);
						}

						// wait some seconds to display the ID then hide it
						_delay_ms(1000);

						// overwrite the number and put '*' to keep privacy
						LCD_goToRowColumn(1,count);
						LCD_displayCharacter('*');

						// Wait for a while to give time between presses
						_delay_ms(1000);

					} // End of for loop, now I have the ID given by the subscriber

					while( ( keypad_check() )!= '='){}

					// clear the screen after getting the ID !!!
					LCD_clearScreen();

					// Here we Compare the given ID and open the door
					// or ask the user to enter the correct ID
					
					for(i=0; i<4; i++){
						// to loop over subsID array
						for(count=0; count<ID_SIZE; count++){
							// to loop over my given ID
							if(subID[count] != subsID[i][count]){
								break;
							}
							if(count == 2){
								// Correct ID
								ID_flag = 1;
								LCD_displayString("Correct ID");
								LCD_goToRowColumn(1,0);
								LCD_displayStringRowColumn(1,0,"Door is Open");
								
								// Open the door for the Great Awesome Richie Richie Subscriber
								displayID();
								Timer1_Fast_PWM_Init(200);
								LCD_clearScreen();
							}
						}
						if(ID_flag == 1){
							ID_flag = 0;
							break;
						}
						if(i == 3){
							// it's Surely a Wrong ID
							LCD_displayString("Wrong ID");
							LCD_goToRowColumn(1,0);
							LCD_displayStringRowColumn(1,0,"Type it Again !");
							_delay_ms(2000);
							LCD_clearScreen();
							LCD_displayStringRowColumn(0,0,"Enter ID");
							LCD_goToRowColumn(1,0);
							goto ID_REQ_S3;
						}
					}
					
				} // End of exiting subscriber mode
			}
			// else for the IR Checking
			else{
				LCD_displayStringRowColumn(0,0,"SMART PARKING :D");
			}
		}
		// else for the SLOTS Checking
		else{
			if( BIT_IS_CLEAR(IR_INPUT_PORT, IR_PIN ) ){
				// A car is here
				LCD_clearScreen();
				LCD_displayString("    Sorry !!");
				LCD_goToRowColumn(1,0);
				LCD_displayStringRowColumn(1,0,"No More Slots");
				_delay_ms(5000);
				LCD_clearScreen();
			}
			else{
				LCD_displayStringRowColumn(0,0,"SMART PARKING :D");
			}
		}
	
	
	/******************************************************************************************
	 *                                  NO Car Found mode
	 *****************************************************************************************/

		while ( BIT_IS_SET(IR_INPUT_PORT , IR_PIN) && BIT_IS_SET(IR2_INPUT_PORT , IR2_PIN) && First_time == 0)
		{
			LCD_displayStringRowColumn(0,0,"SMART PARKING :D");
		}
    	}
		
	
	while(First_time ==1)
    {
		
	//	while(BIT_IS_SET(IR_INPUT_PORT , IR_PIN) ||BIT_IS_SET(IR2_INPUT_PORT , IR2_PIN) );     //wait until a car comes
		
			if (BIT_IS_CLEAR(IR_INPUT_PORT , IR_PIN) )         // Car At Entrance
			{
				enter_state = 1;
			}
			else                                    // Car At Exit
			{
				enter_state = 0;
			}
		
		operation = First_time_data;
		
		if (atoi(Operation_ptr) == 1)          // ADMIN_USER Operation
		
		{  
			Recieved_data= UART_Receive();
			
			if  (Recieved_data == 1)           // Admin Mode
			{
				
				UART_Transmit(total_cars);
				
				Recieved_data = UART_Receive();
				if (Recieved_data == 1)
				{
					     
					UART_Sendint(total_revenue,3);       //Check Max Value ***************
				}
			}
			
			else if (Recieved_data == 0)        // User Mode
			{
				
				UART_Transmit(enter_state);           // send if entering or leaving 
			}
			
			operation= UART_Receive();
		}
		if(operation == 2)                           // GUEST_SUBSCRIBER Operation
		{
			
			Recieved_data= UART_Receive();       
			
			if (Recieved_data== 1)                       // Guest Mode
			{
				if(enter_state== 1)            
				{
					
					UART_Transmit(emptySpaces);
					Recieved_data= UART_Receive();     
					if (Recieved_data ==1)                            //we have empty places
					{
						currentID--;
						UART_Sendint(atoi(guestID[currentID]),3);        // Use the ID generation function
						motor_on_90();
						_delay_ms(10000);                          //ckeck if we can do this
						motor_on_0();
					
					}
					else                                    //we have no empty places
					{
						First_time = 0;
						SET_BIT(UCSRB,RXCIE) ;
						break;
					}
					
				}
				
			}
			else                                    // Subscriber Mode
			{
				Recieved_data=UART_Receive();
				if (Recieved_data == 1)             // Password correct
				{  
					motor_on_90();
					_delay_ms(10000);                          //ckeck if we can do this
					motor_on_0();
				}
				First_time = 0;
				SET_BIT(UCSRB,RXCIE) ;
				break;
				
			}
			operation= UART_Receive();
		}
		if(operation == 3)                        // leaving Guest Operation
		{
			Recieved_data = UART_Receive();             // Receive id code(1-4)
			if (Recieved_data == 1)                     // Correct ID 
			{
				Fees = 203;
				UART_Sendint(Fees,3);
				Recieved_data =UART_Receive() ;
				if(Recieved_data == 1)                //Money is paid
				{
				motor_on_90();
				_delay_ms(10000);                          //ckeck if we can do this
				motor_on_0();
				}
				First_time = 0;
				SET_BIT(UCSRB,RXCIE) ;
				break;
			}
			
			
			operation= UART_Receive();
		}
		if (operation == 4)
		{
			//Light control
			
			Recieved_data=UART_Receive();
			if (Recieved_data == 1)              //Turn ON LEDS
			{
				clr_bit(PORTB,PB6);
				
			}
			else if(Recieved_data == 0)         //Turn OFF LEDS
			{
				set_bit(PORTB,PB6);
			}
			
		}
		First_time = 0;
		SET_BIT(UCSRB,RXCIE) ;
	}

				
				
	}
			
	return 0;
}


ISR(USART_RXC_vect)
{
	
	First_time = 1;
	First_time_data = UDR;
	CLEAR_BIT(UCSRB,RXCIE) ;    //disable interrupt
	
}
