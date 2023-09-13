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

	for(u8 i = 0; i < 5; i++)
		timeSlots[i].availability = AVAILABLE;
}

/**************** Start Function *****************/

void APP_voidStart(void)
{
	u8 mode;
	/* On the screen following should be printed
	 * choose the mode
	 * 1- Admin Mode 	2- User Mode
	 */
#if DEBUG
	u8 line1[14] = "\n\nSelect Mode\n";
	BT_voidSendData(&mobile, line1, 14);
	u8 line2[27] = "1-Admin Mode   2-User Mode\n";
	BT_voidSendData(&mobile, line2, 27);
	BT_voidReceiveData(&mobile, &mode, 1);
	mode -= '0';
#else
	LCD_voidDisplayString("Select Mode");
	LCD_voidDisplayStringRowColumn(1,0,"1-Admin mode   2-User mode");
	/* Read The input */
	while(KEYPAD_u8Read(&input)==NO_KEY_PRESSED);
	mode = KEYPAD_u8Read(&input);
#endif
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

	while(maxNumberOfTries--)
	{
		/* On the screen following should be printed
		 * Enter the Password:
		 */
#if DEBUG
		u8 msg [16] = "Enter Password: ";
		u8 buffer[3];
		BT_voidSendData(&mobile, msg, 16);
		BT_voidReceiveData(&mobile, buffer, 3);
		for(u8 i=0; i<3; i++)
			enteredPassword[i] = buffer[i] - '0';
#else
		LCD_voidClearScreen();
		LCD_voidDisplayString("Enter Password:");
		/* Read the entered Password */
		for(u8 i = 0; i < 3; i++)
		{
			while(KEYPAD_u8Read(&input)==NO_KEY_PRESSED);
			enteredPassword[i] = KEYPAD_u8Read(&input);
			LCD_voidDisplayCharacter('*');
		}
#endif
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
			u8 correct[] = "\nCorrect\n";
			BT_voidSendData(&mobile, correct, 9);
			/* On the screen following should be printed
			 * Correct Password
			 * delay 3 seconds
			 * 1- Add Patient	2- Edit Patient data
			 * 3- Reserve Slot	4- Cancel Reservation
			 */
#if DEBUG
			u8 choose [7] = "Choose\n";
			BT_voidSendData(&mobile, choose, 7);
			u8 line1[40] = "1- Add Patient     2- Edit Patient data\n";
			BT_voidSendData(&mobile, line1, 40);
			u8 line2[40] = "3- Reserve Slot   4- Cancel Reservation\n";
			BT_voidSendData(&mobile, line2, 40);
			BT_voidReceiveData(&mobile, buffer, 1);
			option = buffer[0] - '0';
#else

			LCD_voidClearScreen();
			LCD_voidDisplayString("Correct Password");
			SYSTICK_voidDelayMilliSec(3);
			LCD_voidDisplayString("1- Add Patient	2- Edit Patient data");
			LCD_voidDisplayStringRowColumn(1,0,"3- Reserve Slot	4- Cancel Reservation");
			while(KEYPAD_u8Read(&input)==NO_KEY_PRESSED);
			option = KEYPAD_u8Read(&input);
#endif
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
#if DEBUG
			u8 wrong[6] = "Wrong\n";
			BT_voidSendData(&mobile, wrong, 6);
#else
			LCD_voidClearScreen();
			LCD_voidDisplayString("Wrong Password");
#endif
		}
	}

	/* This point will be reached if admin enters the password 3 times wrong */
#if DEBUG
	if(maxNumberOfTries == 0){
		u8 lock[] = "Locked";
		BT_voidSendData(&mobile, lock, 6);
		while(1);
	}
#endif
}

void APP_voidUserMode(void)
{
	u8 option;

	/* On the screen following should be printed
	 * 1- View Patient
	 * 2- View Reservation
	 */
#if DEBUG
	u8 choose [] = "Choose\n";
	u8 buffer;
	BT_voidSendData(&mobile, choose, 7);
	u8 line1[16] = "1- View Patient\n";
	BT_voidSendData(&mobile, line1, 16);
	u8 line2[20] = "2- View Reservation\n";
	BT_voidSendData(&mobile, line2, 20);
	BT_voidReceiveData(&mobile, &buffer, 1);
	option = buffer - '0';
#else

	LCD_voidClearScreen();
	LCD_voidDisplayStringRowColumn(0,0,"1- View Patient");
	LCD_voidDisplayStringRowColumn(1,0,"View Reservation");
	while(KEYPAD_u8Read(&input)==NO_KEY_PRESSED);
	option = KEYPAD_u8Read(&input);
#endif
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

#if DEBUG
	u8 name[21] = "Enter Patients name: ";
	BT_voidSendData(&mobile, name, 21);
	cntr = 0;
	while(tmp != '\n'){
		BT_voidReceiveData(&mobile, &tmp, 1);
		Patient[Global_PatientCounter].name[cntr] = tmp;
		cntr++;
	}
	Patient[Global_PatientCounter].name[cntr] = '\0';
	BT_voidSendData(&mobile, (u8 *)Patient[Global_PatientCounter].name, cntr);

	u8 age[20] = "Enter Patients age: ";
	BT_voidSendData(&mobile, age, 20);
	BT_voidReceiveData(&mobile, receivedAge, 2);
	Patient[Global_PatientCounter].age = ((receivedAge[0]-'0')*10) + (receivedAge[1]-'0');
	BT_voidSendData(&mobile, receivedAge, 2);

	u8 genderMsg[30] = "\nEnter Patients gender (M/F): ";
	BT_voidSendData(&mobile, genderMsg, 30);
	BT_voidReceiveData(&mobile, &gender, 1);
	BT_voidSendData(&mobile, &gender, 1);
	if(gender == 'M')	Patient[Global_PatientCounter].gender = MALE;
	else if(gender == 'F')	Patient[Global_PatientCounter].gender = FEMALE;
	Patient[Global_PatientCounter].ID = Global_PatientCounter + '0';

	u8 finalMsg[17] = "\nPatient ID is : ";
	u8 ID = Patient[Global_PatientCounter].ID;
	BT_voidSendData(&mobile, finalMsg, 17);
	BT_voidSendData(&mobile, &ID, 1);
#else

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
	Patient[Global_PatientCounter].age = ((receivedAge[0]-'0')*10) + (receivedAge[1]-'0');
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
#endif
	Global_PatientCounter++;
}

void APP_voidEditPatient(void)
{
	u8 PatientIDToEdit;
	u8 numbertoedit = 0;
	u8 gender;
	u8 msg[100];
	while(1)
	{
#if DEBUG
	strcpy((char*)msg, "Enter ID Of Patient To Edit: ");
	BT_voidSendData(&mobile, msg, strlen((char*)msg));
	BT_voidReceiveData(&mobile, &PatientIDToEdit, 1);
	PatientIDToEdit -= '0';
	if(PatientIDToEdit < Global_PatientCounter)
	{
		strcpy((char*)msg, "Choose\n");
		BT_voidSendData(&mobile, msg, strlen((char*)msg));
		strcpy((char*)msg, "1-Name\n");
		BT_voidSendData(&mobile, msg, strlen((char*)msg));
		strcpy((char*)msg, "2-Age\n");
		BT_voidSendData(&mobile, msg, strlen((char*)msg));
		strcpy((char*)msg, "3-Gender\n");
		BT_voidSendData(&mobile, msg, strlen((char*)msg));

		BT_voidReceiveData(&mobile, &numbertoedit, 1);
		numbertoedit -= '0';

		switch(numbertoedit)
		{
		case 1:
			strcpy((char*)msg, "Enter the new Name: ");
			BT_voidSendData(&mobile, msg, strlen((char*)msg));


			u8 cntr = 0;
			u8 tmp;
			while(tmp != '\n'){
				BT_voidReceiveData(&mobile, &tmp, 1);
				Patient[PatientIDToEdit].name[cntr] = tmp;
				cntr++;
			}
			Patient[PatientIDToEdit].name[cntr] = '\0';
			BT_voidSendData(&mobile, (u8 *)Patient[PatientIDToEdit].name, cntr);
			break;

		case 2:
			strcpy((char*)msg, "Enter the new Age: ");
			BT_voidSendData(&mobile, msg, strlen((char*)msg));
			u8 receivedAge[2];
			BT_voidReceiveData(&mobile, receivedAge, 2);
			Patient[PatientIDToEdit].age = ((receivedAge[0]-'0')*10) + (receivedAge[1]-'0');
			BT_voidSendData(&mobile, receivedAge, 2);
			break;

		case 3:
			strcpy((char*)msg, "Enter the new Gender: ");
			BT_voidSendData(&mobile, msg, strlen((char*)msg));
			BT_voidReceiveData(&mobile, &gender, 1);
			BT_voidSendData(&mobile, &gender, 1);
			if(gender == 'M')	Patient[PatientIDToEdit].gender = MALE;
			else if(gender == 'F')	Patient[PatientIDToEdit].gender = FEMALE;
			break;
		}
		break;
	}
	else
	{
		strcpy((char *)msg, "ID does not exist!");
		BT_voidSendData(&mobile, msg, strlen((char*)msg));
	}
#else
		LCD_voidDisplayString("Enter ID Of Patient To Edit, to exit press '*'");
		BT_voidReceiveData(&mobile, &PatientIDToEdit, 1);

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
				BT_voidReceiveData(&mobile, &numbertoedit, 1);
			}

			if(numbertoedit == '1')
			{
				LCD_voidDisplayString("Enter Patient's modified name");
				BT_voidReceiveData(&mobile,(u8 *)Patient[PatientIDToEdit].name,20);
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
#endif
	}
}

void APP_voidReserveSlot(void)
{
	u8 slot;
	u8 id;

#if DEBUG
	u8 line1[26] = "\nPlease select slot time:\n";
	BT_voidSendData(&mobile, line1, 26);
	SYSTICK_voidDelayMilliSec(1000);
	u8 line2[31] = "1)12PM 2)1PM 3)2PM 4)3PM 5)4PM\n";
	BT_voidSendData(&mobile, line2, 31);
	BT_voidReceiveData(&mobile, &slot, 1);
	slot -= '0';
#else
	LCD_voidDisplayString("Please select slot time:");
	SYSTICK_voidDelayMilliSec(1000);
	LCD_voidMoveCursor(0,0);
	LCD_voidDisplayString("1)12PM 2)1PM 3)2PM");
	LCD_voidMoveCursor(1,0);
	LCD_voidDisplayString("4)3PM 5)4PM");
	BT_voidReceiveData(&mobile,slot, 1);
#endif

	if(timeSlots[(slot-1)].availability == AVAILABLE)
	{
#if DEBUG
		SYSTICK_voidDelayMilliSec(500);
		u8 line3[17] = "Please enter ID: ";
		BT_voidSendData(&mobile, line3, 17);
#else
		LCD_voidClearScreen();
		SYSTICK_voidDelayMilliSec(500);
		LCD_voidDisplayString("Please enter ID: ");
#endif
		BT_voidReceiveData(&mobile, &id, 1);
		timeSlots[(slot-1)].availability = NOT_AVAILABLE;
		timeSlots[(slot-1)].ID = id-'0';
	}

	else
	{
#if DEBUG
		SYSTICK_voidDelayMilliSec(500);
		u8 line4[18] = "Slot unavailable!\n";
		BT_voidSendData(&mobile, line4, 18);
#else
		LCD_voidClearScreen();
		SYSTICK_voidDelayMilliSec(500);
		LCD_voidDisplayString("Slot unavailable!");
#endif
	}
}

void APP_voidCancelReservation(void)
{
		u8 id;
#if DEBUG
		u8 line[45] = "\nEnter Patient ID to cancel reservation: \n";
		BT_voidSendData(&mobile, line, 44);
#else
		LCD_voidClearScreen();
	    LCD_voidDisplayString("Enter Patient ID to cancel reservation: ");
#endif
	    BT_voidReceiveData(&mobile, &id, 1);
	    id -= '0';
	    // Search for the reservation
	    for (u8 i = 0; i < 5; i++)
	    {
	        if (timeSlots[i].availability == NOT_AVAILABLE && timeSlots[i].ID == id)
	        {
	            // Found a reservation for the patient
	            timeSlots[i].availability = AVAILABLE;
#if DEBUG
		u8 line[45] = "Reservation canceled.\n";
		BT_voidSendData(&mobile, line, 23);
#else
        LCD_voidClearScreen();
        LCD_voidDisplayString("Reservation canceled.\n");
#endif
	            return;
	        }
	    }

	    // If the loop finishes without finding a reservation
#if DEBUG
		u8 line1[45] = "No reservation found for this patient.\n";
		BT_voidSendData(&mobile, line1, 40);
#else
	    LCD_voidClearScreen();
	    LCD_voidDisplayString("No reservation found for this patient.\n");
#endif

}


/**************** User Functions *****************/

void APP_voidViewPatient(void)
{
	u8 id = 100;
	u8 tmp;
	while(id >= Global_PatientCounter)
	{
#if DEBUG
		u8 line[30] = "\nPlease enter your ID: \n";
		BT_voidSendData(&mobile, line, 24);
		BT_voidReceiveData(&mobile, &tmp, 1);
		id = tmp - '0';
		if (id >= Global_PatientCounter)
			{
			u8 error[20] = "ID does not exist! \n";
			BT_voidSendData(&mobile, error, 20);
			}
#else
		LCD_voidDisplayString("Please enter your ID: ");
		BT_voidReceiveData(&mobile, id, 1);
		if (id >= Global_PatientCounter) LCD_voidDisplayString("ID does not exist! ");
#endif
	}

#if DEBUG
	u8 nameMsg[7] = "\nName: ";
	BT_voidSendData(&mobile, nameMsg, 7);
	BT_voidSendData(&mobile, (u8 *)Patient[id].name, strlen(Patient[id].name));

	u8 idMsg[5] = "\nID: ";
	BT_voidSendData(&mobile, idMsg, 5);
	BT_voidSendData(&mobile, &Patient[id].ID, 1);

	u8 ageMsg[6] = "\nAge: ";
	BT_voidSendData(&mobile, ageMsg, 6);
	u8 agePrint[2];
	agePrint[0] = (Patient[id].age/10) + '0';
	agePrint[1] = (Patient[id].age%10) + '0';
	BT_voidSendData(&mobile, agePrint, 2);

	u8 genderMsg[9] = "\nGender: ";
	BT_voidSendData(&mobile, genderMsg, 9);
	if(Patient[id].gender == MALE){
		u8 line[5] ="MALE\n";
		BT_voidSendData(&mobile, line, 5);
	}
	else{
		u8 line[7] = "FEMALE\n";
		BT_voidSendData(&mobile, line, 7);
	}

#else

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

	if(Patient[id].gender == MALE)	LCD_voidDisplayString("M");
	else	LCD_voidDisplayString("F");

#endif
	SYSTICK_voidDelayMilliSec(5000);
}

void APP_voidViewReservation(void)
{
    u8 id;
    u8 found = 0;
#if DEBUG
		u8 line[50] = "\nEnter Patient ID to view reservation: \n";
		BT_voidSendData(&mobile, line, 41);
#else
	    LCD_voidClearScreen();
	    LCD_voidDisplayString("Enter Patient ID to view reservation: ");
#endif

    BT_voidReceiveData(&mobile, &id, 1);
    id -= '0';
    // Search for the reservation
    for (u8 i = 0; i < 5; i++)
    {
        if (timeSlots[i].availability == NOT_AVAILABLE && timeSlots[i].ID == id)
        {
        	found = 1;
#if DEBUG
        	switch (i)
			{
				case FROM_12_TO_1:
					strcpy((char *)line, "Reservation is at : 12PM - 1PM");
					break;
				case FROM_1_TO_2:
					strcpy((char *)line, "Reservation is at : 1PM - 2PM");
					break;
				case FROM_2_TO_3:
					strcpy((char *)line, "Reservation is at : 2PM - 3PM");
					break;
				case FROM_3_TO_4:
					strcpy((char *)line, "Reservation is at : 3PM - 4PM");
					break;
				case FROM_4_TO_5:
					strcpy((char *)line, "Reservation is at : 4PM - 5PM");
					break;
			}

        	BT_voidSendData(&mobile, line, strlen((char *)line));
        	break;
#else
            // Found a reservation for the patient
            LCD_voidClearScreen();
            LCD_voidDisplayString("Reservation for ID ");
            LCD_voidDisplayCharacter(id + '0'); // Display the patient's ID "convert from int to char adding the asci of zero"
            LCD_voidDisplayString(" at ");

            // Display the time slot based on the enum value
            switch (i)
            {
                case FROM_12_TO_1:
                    LCD_voidDisplayString("12PM - 1PM");
                    break;
                case FROM_1_TO_2:
                    LCD_voidDisplayString("1PM - 2PM");
                    break;
                case FROM_2_TO_3:
                    LCD_voidDisplayString("2PM - 3PM");
                    break;
                case FROM_3_TO_4:
                    LCD_voidDisplayString("3PM - 4PM");
                    break;
                case FROM_4_TO_5:
                    LCD_voidDisplayString("4PM - 5PM");
                    break;
            }
#endif
            //return;

        }
    }

    // If the loop finishes without finding a reservation
#if DEBUG
    if(found == 0){
    strcpy((char *)line, "No reservation found for this patient!");
    BT_voidSendData(&mobile, line, 38);
    }
#else
    LCD_voidClearScreen();
    LCD_voidDisplayString("No reservation found for this patient!");
#endif
}
