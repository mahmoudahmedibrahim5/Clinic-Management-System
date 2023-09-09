/*
 * GPIO_Program.c
 *
 *  Created on: Feb 8, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */


#include "GPIO_Interface.h"

void GPIO_voidInitPort(EN_Port_t port, GPIO_Config_t *mode)
{
	st_GPIO_RegDef_t *GPIOn;
	switch (port) {
	case PORTA:
		GPIOn = GPIOA;
		break;
	case PORTB:
		GPIOn = GPIOB;
		break;
	case PORTC:
		GPIOn = GPIOC;
		break;
	case PORTD:
		GPIOn = GPIOD;
		break;
	case PORTE:
		GPIOn = GPIOE;
		break;
	case PORTH:
		GPIOn = GPIOH;
		break;
	default:
		// error (will be edited later)
		break;
	}
	for (u8 i = 0; i < 16; i++) {
		// Configure the mode
		GPIOn->MODER &= ~(0x3 << ((2 * i)));
		GPIOn->MODER |= (mode->mode << (2 * i));

		// Configure GPIO_OUTPUTput type in case mode is GPIO_OUTPUTput
		if (mode->mode == GPIO_OUTPUT || mode->mode == GPIO_ALT_FN) {
			GPIOn->OTYPER &= ~(1 << (i));
			GPIOn->OTYPER |= (mode->outType << i);
		}

		// Configure speed
		GPIOn->OSPEEDR &= ~(0x3 << ((2 * i)));
		GPIOn->OSPEEDR |= (mode->speed << (2 * i));

		// Configure pull up and pull down resistors in case mode is input or open drain GPIO_OUTPUTput
		GPIOn->PUPDR &= ~(0x3 << ((2 * i)));
		GPIOn->PUPDR |= (mode->pupdState << (2 * i));

		// Configure Alternate function
		if (mode->mode == GPIO_ALT_FN) {
			if (mode->AltFuncMode < 8)
				GPIOn->AFRL |= (mode->AltFuncMode << (4 * i));
			else
				GPIOn->AFRH |= ((mode->AltFuncMode - 8) << (4 * i));
		}
	}
}

void GPIO_voidInitPin(EN_Port_t port, u8 pinNum, GPIO_Config_t *mode)
{
	st_GPIO_RegDef_t *GPIOn;
	switch (port) {
	case PORTA:
		GPIOn = GPIOA;
		break;
	case PORTB:
		GPIOn = GPIOB;
		break;
	case PORTC:
		GPIOn = GPIOC;
		break;
	case PORTD:
		GPIOn = GPIOD;
		break;
	case PORTE:
		GPIOn = GPIOE;
		break;
	case PORTH:
		GPIOn = GPIOH;
		break;
	default:
		// error (will be edited later)
		break;
	}

	// Configure the mode
	GPIOn->MODER &= ~(0x3 << ((2 * pinNum)));
	GPIOn->MODER |= (mode->mode << (2 * pinNum));

	// Configure GPIO_OUTPUTput type in case mode is output
	if (mode->mode == GPIO_OUTPUT || mode->mode == GPIO_ALT_FN) {
		GPIOn->OTYPER &= ~(1 << (pinNum));
		GPIOn->OTYPER |= (mode->outType << pinNum);
	}

	// Configure speed
	GPIOn->OSPEEDR &= ~(0x3 << ((2 * pinNum)));
	GPIOn->OSPEEDR |= (mode->speed << (2 * pinNum));

	// Configure pull up and pull down resistors in case mode is input or open drain output
	GPIOn->PUPDR &= ~(0x3 << ((2 * pinNum)));
	GPIOn->PUPDR |= (mode->pupdState << (2 * pinNum));

	// Configure Alternate function
	if (mode->mode == GPIO_ALT_FN) {
		if (pinNum < 8)
			GPIOn->AFRL |= (mode->AltFuncMode << (4 * pinNum));
		else
			GPIOn->AFRH |= ((mode->AltFuncMode) << (4 * (pinNum - 8)));
	}
}

void GPIO_voidSetPinValue(EN_Port_t port, u8 pinNum, u8 val)
{
	st_GPIO_RegDef_t *GPIOn;
	switch (port) {
	case PORTA:
		GPIOn = GPIOA;
		break;
	case PORTB:
		GPIOn = GPIOB;
		break;
	case PORTC:
		GPIOn = GPIOC;
		break;
	case PORTD:
		GPIOn = GPIOD;
		break;
	case PORTE:
		GPIOn = GPIOE;
		break;
	case PORTH:
		GPIOn = GPIOH;
		break;
	default:
		// error
		break;
	}
	if (val == GPIO_HIGH) {
		GPIOn->ODR |= (1 << pinNum);
	} else {
		GPIOn->ODR &= ~(1 << pinNum);
	}
}

void GPIO_voidSetPortValue(EN_Port_t port, u16 val)
{
	st_GPIO_RegDef_t *GPIOn;
	switch (port) {
	case PORTA:
		GPIOn = GPIOA;
		break;
	case PORTB:
		GPIOn = GPIOB;
		break;
	case PORTC:
		GPIOn = GPIOC;
		break;
	case PORTD:
		GPIOn = GPIOD;
		break;
	case PORTE:
		GPIOn = GPIOE;
		break;
	case PORTH:
		GPIOn = GPIOH;
		break;
	default:
		// error
		break;
	}

	GPIOn->ODR = val;
}

void GPIO_voidTogglePin(EN_Port_t port, u8 pinNum)
{
	st_GPIO_RegDef_t *GPIOn;
	switch (port) {
	case PORTA:
		GPIOn = GPIOA;
		break;
	case PORTB:
		GPIOn = GPIOB;
		break;
	case PORTC:
		GPIOn = GPIOC;
		break;
	case PORTD:
		GPIOn = GPIOD;
		break;
	case PORTE:
		GPIOn = GPIOE;
		break;
	case PORTH:
		GPIOn = GPIOH;
		break;
	default:
		// error
		break;
	}
	GPIOn->ODR ^= (1 << pinNum);
}

void GPIO_voidTogglePort(EN_Port_t port)
{
	st_GPIO_RegDef_t *GPIOn;
	switch (port) {
	case PORTA:
		GPIOn = GPIOA;
		break;
	case PORTB:
		GPIOn = GPIOB;
		break;
	case PORTC:
		GPIOn = GPIOC;
		break;
	case PORTD:
		GPIOn = GPIOD;
		break;
	case PORTE:
		GPIOn = GPIOE;
		break;
	case PORTH:
		GPIOn = GPIOH;
		break;
	default:
		// error
		break;
	}
	GPIOn->ODR ^= 0xFFFF;
}

u8 GPIO_voidReadPin(EN_Port_t port, u8 pinNum)
{
	st_GPIO_RegDef_t *GPIOn;
	switch (port) {
	case PORTA:
		GPIOn = GPIOA;
		break;
	case PORTB:
		GPIOn = GPIOB;
		break;
	case PORTC:
		GPIOn = GPIOC;
		break;
	case PORTD:
		GPIOn = GPIOD;
		break;
	case PORTE:
		GPIOn = GPIOE;
		break;
	case PORTH:
		GPIOn = GPIOH;
		break;
	default:
		// error
		break;
	}
	return (u8) ((GPIOn->IDR & (1 << pinNum)) >> pinNum);
}

u16 GPIO_voidReadPort(EN_Port_t port)
{
	st_GPIO_RegDef_t *GPIOn;
	switch (port) {
	case PORTA:
		GPIOn = GPIOA;
		break;
	case PORTB:
		GPIOn = GPIOB;
		break;
	case PORTC:
		GPIOn = GPIOC;
		break;
	case PORTD:
		GPIOn = GPIOD;
		break;
	case PORTE:
		GPIOn = GPIOE;
		break;
	case PORTH:
		GPIOn = GPIOH;
		break;
	default:
		// error
		break;
	}
	return (u16) (GPIOn->IDR);
}
