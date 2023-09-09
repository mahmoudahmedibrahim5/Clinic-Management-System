/*
 * LED.c
 *
 *  Created on: Apr 24, 2023
 *      Author: Mahmoud Ahmed
 */

#include "LED_Interface.h"

void LED_voidInit(LED_t* led){
	GPIO_Config_t LED_config;
	LED_config.mode = GPIO_OUTPUT;
	LED_config.outType = GPIO_PUSH_PULL;
	LED_config.speed = GPIO_LOW_SPEED;
	LED_config.pupdState = GPIO_NO_PUPD;
	GPIO_voidInitPin(led->port, led->pin, &LED_config);
}

void LED_voidTurnON(LED_t* led){
	GPIO_voidSetPinValue(led->port, led->pin, GPIO_HIGH);
}

void LED_voidTurnOFF(LED_t* led){
	GPIO_voidSetPinValue(led->port, led->pin, GPIO_LOW);
}

void LED_voidToggle(LED_t* led){
	GPIO_voidTogglePin(led->port, led->pin);
}

u8 LED_u8Read(LED_t* led){
	return GPIO_u8ReadPin(led->port, led->pin);
}
