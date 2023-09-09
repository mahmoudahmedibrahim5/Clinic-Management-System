/*
 * GPIO_Interface.h
 *
 *  Created on: Feb 8, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef GPIO_GPIO_INTERFACE_H_
#define GPIO_GPIO_INTERFACE_H_

#include "../../Utilities/STD_TYPES.h"
#include "GPIO_Registers.h"
#include "GPIO_Config.h"

#define GPIO_LOW  0
#define GPIO_HIGH 1

typedef enum{
	PORTA,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTH=7
}EN_Port_t;

void GPIO_voidInitPort(EN_Port_t port, GPIO_Config_t* mode);
void GPIO_voidInitPin(EN_Port_t port, u8 pinNum, GPIO_Config_t* mode);

void GPIO_voidSetPinValue(EN_Port_t port, u8 pinNum, u8 val);
void GPIO_voidSetPortValue(EN_Port_t port, u16 val);
void GPIO_voidTogglePin(EN_Port_t port, u8 pinNum);
void GPIO_voidTogglePort(EN_Port_t port);

u8 GPIO_u8ReadPin(EN_Port_t port, u8 pinNum);
u16 GPIO_u8ReadPort(EN_Port_t port);

#endif /* GPIO_GPIO_INTERFACE_H_ */
