/*
 * APP.c
 *
 *  Created on: Sep 9, 2023
 *      Author: Mahmoud Ahmed
 */


#include "APP.h"

/******************* Hardware objects ******************/
KeyPad_t input = {PORTA, {0, 1, 2, 3, 4, 5, 6, 7}};
// LCD object
BT_t mobile = {USART1, 9600};	// Tx PA9, Rx PA10
/*******************************************************/


/********************* Time Slots **********************/
ST_Slot_t timeSlots[5];
/*******************************************************/

/****************** Constant Variables *****************/
const u8 Password[3] = {1, 2, 3};
/*******************************************************/

void APP_voidInit(void)
{
	RCC_voidInit();

	RCC_voidPeripheralEnable(GPIOA_EN);
	RCC_voidPeripheralEnable(GPIOB_EN);
	RCC_voidPeripheralEnable(USART1_EN);

	BT_voidInit(&mobile);
	// LCD initialize

	for(u8 i = 0; i < 5; i++){
		timeSlots[i].time = i;
		timeSlots[i].availability = AVAILABLE;
	}
}

void APP_voidStart(void)
{
	u8 mode;

	/* On the screen following should be printed
	 * choose the mode
	 * 1- Admin Mode 	2- User Mode
	 */
	LCD_voidDisplayString("Select Mode");
	LCD_voidDisplayStringRowColumn(1,0,"1-Admin mode   2-User mode");
	/* Read The input */
	while(KEYPAD_u8Read(&input)==NO_KEY_PRESSED);
	mode = KEYPAD_u8Read(&input);

	/* Check the mode */
	if(mode == 1)
		APP_voidAdminMode();
	else if(mode == 2)
		APP_voidUserMode();
}

void APP_voidAdminMode(void)
{
	u8 enteredPassword[3];
	u8 maxNumberOfTries = 3;

	while(maxNumberOfTries)
	{
		/* On the screen following should be printed
		 * Enter the Password:
		 */

		/* Read the entered Password */
		for(u8 i = 0; i < 3; i++)
		{
			while(KEYPAD_u8Read(&input)==NO_KEY_PRESSED);
			enteredPassword[i] = KEYPAD_u8Read(&input);
		}

		/* Check The Password */
		u8 right = 1;
		for(u8 i = 0; i < 3; i++)
		{
			if(enteredPassword[i] != Password[i])
			{
				right = 0;
				break;
			}
		}

		if(right)
		{
			u8 option;
			/* On the screen following should be printed
			 * Correct Password
			 * delay 3 seconds
			 * 1- Add Patient	2- Edit Patient data
			 * 3- Reserve Slot	4- Cancel Reservation
			 */
			while(KEYPAD_u8Read(&input)==NO_KEY_PRESSED);
			option = KEYPAD_u8Read(&input);

			switch(option)
			{
			case 1:
				APP_voidAddPatient();
				break;
			case 2:
				APP_voidEditPatient();
				break;
			case 3:
				APP_voidReserveSlot();
				break;
			case 4:
				APP_voidCancelReservation();
				break;
			default:
				// Invalid Input
			}

			break; // break from the while of number of tries
		}
		else
		{
			/* On the screen following should be printed
			* Wrong Password
			*/
		}
	}

	/* This point will be reached if admin enters the password 3 times wrong */

}

void APP_voidUserMode(void)
{
	u8 option;

	/* On the screen following should be printed
	 * 1- View Patient
	 * 2- View Reservation
	 */
	while(KEYPAD_u8Read(&input)==NO_KEY_PRESSED);
	option = KEYPAD_u8Read(&input);

	if(option == 1)
		APP_voidViewPatient();
	else if(option == 2)
		APP_voidViewReservation();
	else{
		//invalid input
	}
}

