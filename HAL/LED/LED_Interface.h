/*
 * LED.h
 *
 *  Created on: Apr 24, 2023
 *      Author: Mahmoud Ahmed
 *
 *      since I am usually use the same configuration for LEDs
 *      I decided to write this driver so I don't need to write this
 *      configuration every time I use LED and it also make the main code more readable
 *
 */

#ifndef LED_LED_H_
#define LED_LED_H_

#include "../../MCAL/GPIO/GPIO_Interface.h"

typedef struct LED{
	u8 port;
	u8 pin;
}LED_t;

void LED_voidInit(LED_t* led);
void LED_voidTurnON(LED_t* led);
void LED_voidTurnOFF(LED_t* led);
void LED_voidToggle(LED_t* led);
u8 LED_u8Read(LED_t* led);

#endif /* LED_LED_H_ */
