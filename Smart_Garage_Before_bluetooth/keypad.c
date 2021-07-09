/*
 * keypad_driver.c
 *
 * Created: 2/24/2018 4:06:22 PM
 *  Author: Mohamed Zaghlol
 */ 
 #include "keypad.h"
 #include "common_macros.h"
 void keypad_init()
 {
	 SET_BIT(K_DIR,0);
	 SET_BIT(K_DIR,1);
	 SET_BIT(K_DIR,2);
	 SET_BIT(K_DIR,3);
	 CLEAR_BIT(K_DIR,4);
	 CLEAR_BIT(K_DIR,5);
	 CLEAR_BIT(K_DIR,6);
	 CLEAR_BIT(K_DIR,7);
	 SET_BIT(K_PORT,4);
	 SET_BIT(K_PORT,5);
	 SET_BIT(K_PORT,6);
	 SET_BIT(K_PORT,7);
	  
 }
 char keypad_check()
 {
	 char arr[4][4]={{'-','+','/','='},{'#','9','6','3'},{'0','8','5','2'},{'*','7','4','1'}};
	 unsigned char row,coloumn,x;
	 char returnval=NOTPRESSED;
h:	 for(row=0;row<4;row++)
	 {
		SET_BIT(K_PORT,0);
		SET_BIT(K_PORT,1);
		SET_BIT(K_PORT,2);
		SET_BIT(K_PORT,3);
		
		CLEAR_BIT(K_PORT,row);
	
		for(coloumn=0;coloumn<4;coloumn++)
		{
			x=READ_BIT(K_PIN,(coloumn+4));
			if(x==0)
			 {
				 returnval=arr[row][coloumn];
				 break;
			 }  
		}	
		if(x==0)
		{
			break;
		}
	}

	if(returnval == NOTPRESSED){
		goto h;
	}
	
	 return returnval ;	 
 }