/*
 * APP.h
 *
 *  Created on: Sep 9, 2023
 *      Author: Mahmoud Ahmed
 */

#ifndef APP_H_
#define APP_H_

#include "../MCAL/RCC/RCC_Interface.h"

#include "../HAL/BT_Module/BT_Interface.h"
#include "../HAL/KeyPad/KEYPAD_Interface.h"
#include "../HAL/LED/LED_Interface.h"

/*********************** Patient ***********************/
typedef enum{
	FEMALE,
	MALE
}EN_Gender_t;

typedef struct{
	u8 name[20];
	u8 age;
	u8 ID;
	EN_SlotTime_t slot;
	EN_Gender_t gender;
}ST_Patient_t;

/********************** Time Slots *********************/
typedef enum{
	FROM_12_TO_1,
	FROM_1_TO_2,
	FROM_2_TO_3,
	FROM_3_TO_4,
	FROM_4_TO_5
}EN_SlotTime_t;

typedef enum{
	NOT_AVAILABLE,
	AVAILABLE
}EN_SlotAvailability_t;

typedef struct{
	//I think this attribute is not needed since the array of slots is numberedEN_SlotTime_t time;
	EN_SlotAvailability_t availability;
	u8 ID;
}ST_Slot_t;

/*******************************************************/


/***************** Functions Prototypes ****************/
void APP_voidInit(void);

void APP_voidStart(void);
void APP_voidAdminMode(void);
void APP_voidUserMode(void);

// Administrator mode functions
void APP_voidAddPatient(void);
void APP_voidEditPatient(void);
void APP_voidReserveSlot(void);
void APP_voidCancelReservation(void);

// User mode functions
void APP_voidViewPatient(void);
void APP_voidViewReservation(void);

/*******************************************************/

#endif /* APP_H_ */
