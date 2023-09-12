/*
 * App.c
 *
 *  Created on: Sep 11, 2023
 *      Author: dell
 */

#include "APP.h"

/******************* Hardware objects ******************/
KeyPad_t input = {PORTA, {0, 1, 2, 3, 4, 5, 6, 7}};
BT_t mobile = {USART1, 9600};	// Tx PA9, Rx PA10
/*******************************************************/

/********************* Time Slots **********************/
ST_Slot_t timeSlots[6];
/*******************************************************/

/********************* Patients ************************/
ST_Patient_t Patient[50];
/*******************************************************/

/****************** Constant Variables *****************/
const u8 Password[3] = {1, 2, 3};
/*******************************************************/

/****************** Patients Counter *******************/
static u8 Global_PatientCounter=0;
/*******************************************************/

/*----------------------------------------------------------------------------------------------*/

/**************** Initialize Function *****************/

void APP_voidInit(void)
{
	RCC_voidInit();

	RCC_voidPeripheralEnable(GPIOA_EN);
	RCC_voidPeripheralEnable(GPIOB_EN);
	RCC_voidPeripheralEnable(USART1_EN);

	BT_voidInit(&mobile);
	LCD_voidInit();

	for(u8 i = 0; i < 5; i++){
		timeSlots[i].time = i;
		timeSlots[i].availability = AVAILABLE;
	}
}

/**************** Start Function *****************/

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

/**************** Mode Functions *****************/


void APP_voidAdminMode(void)
{
	u8 enteredPassword[3];
	u8 maxNumberOfTries = 3;

	while(maxNumberOfTries)
	{
		/* On the screen following should be printed
		 * Enter the Password:
		 */
		LCD_voidClearScreen();
		LCD_voidDisplayString("Enter Password:");
		/* Read the entered Password */
		for(u8 i = 0; i < 3; i++)
		{
			while(KEYPAD_u8Read(&input)==NO_KEY_PRESSED);
			enteredPassword[i] = KEYPAD_u8Read(&input);
			LCD_voidDisplayCharacter('*');
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
			LCD_voidClearScreen();
			LCD_voidDisplayString("Correct Password");
			SYSTICK_voidDelayMilliSec(3);
			LCD_voidDisplayString("1- Add Patient	2- Edit Patient data");
			LCD_voidDisplayStringRowColumn(1,0,"3- Reserve Slot	4- Cancel Reservation");
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
				LCD_voidClearScreen();
				LCD_voidDisplayString("invalid input");
				break;
			}

			break; // break from the while of number of tries
		}
		else
		{
			/* On the screen following should be printed
			 * Wrong Password
			 */
			LCD_voidClearScreen();
			LCD_voidDisplayString("Wrong Password");
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
	LCD_voidClearScreen();
	LCD_voidDisplayStringRowColumn(0,0,"1- View Patient");
	LCD_voidDisplayStringRowColumn(1,0,"View Reservation");
	while(KEYPAD_u8Read(&input)==NO_KEY_PRESSED);
	option = KEYPAD_u8Read(&input);

	if(option == 1)
		APP_voidViewPatient();
	else if(option == 2)
		APP_voidViewReservation();
	else{
		//invalid input
		LCD_voidClearScreen();
		LCD_voidDisplayString("invalid input");
	}
}


/**************** Administrator Functions *****************/


void APP_voidAddPatient(void)
{
	u8 gender;
	u8 tmp, cntr;
	u8 receivedAge[2];

	LCD_voidDisplayString("Enter Patients name");

	cntr = 0;
	while(tmp != '\n'){
		BT_voidReceiveData(&mobile, &tmp, 1);
		Patient[Global_PatientCounter].name[cntr] = tmp;
		cntr++;
	}
	SYSTICK_voidDelayMilliSec(20);

	LCD_voidDisplayString("Enter Patients age");
	BT_voidReceiveData(&mobile, receivedAge, 2);
	Patient[PatientIDToEdit].age = ((receivedAge[0]-'0')*10) + (receivedAge[1]-'0');
	SYSTICK_voidDelayMilliSec(20);

	LCD_voidDisplayString("Enter Patients gender (M/F)");
	BT_voidReceiveData(&mobile, &gender, 1);
	SYSTICK_voidDelayMilliSec(20);
	if(gender == 'M')	Patient[Global_PatientCounter].gender = MALE;
	else if(gender == 'F')	Patient[Global_PatientCounter].gender = FEMALE;

	Patient[Global_PatientCounter].ID=Global_PatientCounter;
	LCD_voidDisplayString(Patient[Global_PatientCounter].name);
	LCD_voidDisplayStringRowColumn(1,0,"ID number ");
	LCD_voidMoveCursor(1,10);
	LCD_voidIntgerToString(Global_PatientCounter); //It shall display "(Patient's name) ID number (Patient's ID)"
	SYSTICK_voidDelayMilliSec(500);
	LCD_voidClearScreen();
	Global_PatientCounter++;
}

void APP_voidEditPatient(void)
{
	u8 PatientIDToEdit;
	u8 numbertoedit = 0;
	u8 receivedAge[2];

	while(1)
	{
		LCD_voidDisplayString("Enter ID Of Patient To Edit, to exit press '*'");
		BT_voidReceiveData(&mobile,PatientIDToEdit, 1);

		if(PatientIDToEdit == '*')
			return;

		PatientIDToEdit -= '0'; // Convert ascii to int
		if(PatientIDToEdit < Global_PatientCounter)//we could use ID
		{
			LCD_voidDisplayString("Patient's data:");
			SYSTICK_voidDelayMilliSec(1500);
			LCD_voidDisplayString("1-Name:");
			SYSTICK_voidDelayMilliSec(1500);
			LCD_voidDisplayString("2-Age:");
			SYSTICK_voidDelayMilliSec(1500);
			LCD_voidDisplayString("3-Gender:");
			SYSTICK_voidDelayMilliSec(1500);
			//if we can display them together would be better

			while(numbertoedit != '1' || numbertoedit != '2' || numbertoedit != '3')
			{
				LCD_voidDisplayString("Enter number of data to edit");
				BT_voidReceiveData(&mobile, numbertoedit, 1);
			}

			if(numbertoedit == '1')
			{
				LCD_voidDisplayString("Enter Patient's modified name");
				BT_voidReceiveData(&mobile,Patient[PatientIDToEdit].name,20);
				SYSTICK_voidDelayMilliSec(500);
				LCD_voidDisplayString("Modified name:");
				LCD_voidMoveCursor(0,15);
				LCD_voidDisplayString(Patient[PatientIDToEdit].name);
				SYSTICK_voidDelayMilliSec(1000);
			}
			else if(numbertoedit == '2')
			{
				LCD_voidDisplayString("Enter Patients modified age");
				BT_voidReceiveData(&mobile, receivedAge, 2);
				Patient[PatientIDToEdit].age = ((receivedAge[0]-'0')*10) + (receivedAge[1]-'0');
				SYSTICK_voidDelayMilliSec(500);
				LCD_voidDisplayString("Modified age:");
				LCD_voidMoveCursor(0,14);
				LCD_voidIntgerToString(Patient[PatientIDToEdit].age);
				SYSTICK_voidDelayMilliSec(1000);
			}
			else if(numbertoedit == '3')
			{
				LCD_voidDisplayString("Enter Patients modified gender (M/F)");
				BT_voidReceiveData(&mobile,&Patient[PatientIDToEdit].gender,1);
				SYSTICK_voidDelayMilliSec(500);
				LCD_voidDisplayString("Modified gender:");
				LCD_voidMoveCursor(0,17);
				if(Patient[PatientIDToEdit].gender == MALE) LCD_voidDisplayString("MALE");
				else	LCD_voidDisplayString("FEMALE");
				SYSTICK_voidDelayMilliSec(1000);
			}

			LCD_voidClearScreen();
			SYSTICK_voidDelayMilliSec(500);
			break;
		}
		else
		{
			LCD_voidDisplayString("ID does not exist!");
			SYSTICK_voidDelayMilliSec(500);
		}
	}
}

void APP_voidReserveSlot(void)
{
	u8 slot;
	u8 id;

	LCD_voidDisplayString("Please select slot time:");
	SYSTICK_voidDelayMilliSec(1000);
	LCD_voidMoveCursor(0,0);
	LCD_voidDisplayString("1)12PM 2)1PM 3)2PM");
	LCD_voidMoveCursor(1,0);
	LCD_voidDisplayString("4)3PM 5)4PM");
	BT_voidReceiveData(&mobile,slot, 1);

	if(timeSlots[(slot-1)].availability == AVAILABLE)
	{
		LCD_voidClearScreen();
		SYSTICK_voidDelayMilliSec(500);
		LCD_voidDisplayString("Please enter ID: ");
		BT_voidReceiveData(&mobile, id, 1);
		timeSlots[(slot-1)].availability = NOT_AVAILABLE;
		timeSlots[(slot-1)].ID = id;
	}
	else
	{
		LCD_voidClearScreen();
		SYSTICK_voidDelayMilliSec(500);
		LCD_voidDisplayString("Slot unavailable!");
	}


}

void APP_voidCancelReservation(void)
{

}


/**************** User Functions *****************/

void APP_voidViewPatient(void)
{
	u8 id = 100;

	while(id >= Global_PatientCounter)
	{
		LCD_voidDisplayString("Please enter your ID: ");
		BT_voidReceiveData(&mobile, id, 1);
		if (id >= Global_PatientCounter) LCD_voidDisplayString("ID does not exist! ");
	}

	LCD_voidClearScreen();
	SYSTICK_voidDelayMilliSec(500);

	LCD_voidDisplayString("Name: ");
	LCD_voidMoveCursor(0, 6);
	LCD_voidDisplayString(Patient[id].name);
	LCD_voidMoveCursor(1, 0);
	LCD_voidDisplayString("ID: ");
	LCD_voidMoveCursor(1, 3);
	LCD_voidDisplayString(Patient[id].ID);
	LCD_voidMoveCursor(1, 5);
	LCD_voidDisplayString("Age: ");
	LCD_voidMoveCursor(1, 9);
	LCD_voidDisplayString(Patient[id].age);
	LCD_voidMoveCursor(1, 12);
	LCD_voidDisplayString("G: ");
	LCD_voidMoveCursor(1, 14);
	if(Patient[id].gender == MALE)	LCD_voidDisplayString("Male");
	else	LCD_voidDisplayString("Female");

	SYSTICK_voidDelayMilliSec(5000);
}

void APP_voidViewReservation(void)
{


}


