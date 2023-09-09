/*
 * USART_Program.c
 *
 *  Created on: Jun 17, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */
#include "USART_Interface.h"

static void USART_voidConfigurePins(st_USART_RegDef_t* USARTn, u8 mode);

void USART_voidInit(st_USART_RegDef_t* USARTn, USART_Config_t* config){
	// Configure the pins
	USART_voidConfigurePins(USARTn, config->mode);
	// Enable USART
	USARTn->CR1 |= (1<<13);

	if(config->mode == USART_SYNCHRONOUS){
		// Enable CK pin
		USARTn->CR2 |= (1<<11);
	}
	else if(config->mode == USART_HALF_DUPLEX){
		// Select Half-Duplex mode
		USARTn->CR3 |= (1<<3);
	}
	else{
		// Disable CK pin
		USARTn->CR2 &= ~(1<<11);
	}

	// Define word length
	switch(config->dataSize){
	case 0:
		USARTn->CR1 &= ~(1<<12);
		break;
	case 1:
		USARTn->CR1 |= (1<<12);
		break;
	}

	// Configure Parity bit
	switch(config->parityType){
		case 0:
			USARTn->CR1 |= (1<<10); // Enable Parity
			USARTn->CR1 &= ~(1<<9);	// Configure it to Even Parity
			break;
		case 1:
			USARTn->CR1 |= (1<<10); // Enable Parity
			USARTn->CR1 |= (1<<9);  // Configure it to Odd Parity
			break;
		case 2:
			USARTn->CR1 &= ~(1<<10);// Disable Parity
			break;
	}

	// Set the number of stop bits
	USARTn->CR2 &= ~(11<<12);
	USARTn->CR2 |= (config->stopBits<<12);

	if(config->overSampling == USART_OVERSAMPLING8){
		USARTn->CR1 |= (1<<15);
	}
	else{
		USARTn->CR1 &= ~(1<<15);
	}

	/*		Setting  the BaudRate
	 **************************************
	 * This part could have been calculated but this would take time and space
	 * So, I preferred to write manually only the famous used BaudRates instead of calculating
	 * If you want to add more BaudRates check the table in page 521 (Section 19.3.4 Fractional baud rate generation) in Reference Manual.
	 * Here is the equation for the calculation:
	 * float realValue = (F_CPU)/(8*(2-config->overSampling) * config->baudrate);
	 * */
	if(config->baudrate == 9600){
		if(config->overSampling == USART_OVERSAMPLING16)
			USARTn->BRR |= 0x683;
		else
			USARTn->BRR |= 0xD06;
	}
	else if(config->baudrate == 115200){
		if(config->overSampling == USART_OVERSAMPLING16)
			USARTn->BRR |= 0x8B;
		else
			USARTn->BRR |= 0x116;
	}

	// Send Idle frame to start transmission (Transmitter Enable)
	if(config->transmission == USART_TX_ONLY)
		USARTn->CR1 |= (1<<3);
	else if(config->transmission == USART_RX_ONLY)
		USARTn->CR1 |= (1<<2);
	else if(config->transmission == USART_TX_AND_RX){
		USARTn->CR1 |= (1<<3);
		USARTn->CR1 |= (1<<2);
	}
}

void USART_voidSendData(st_USART_RegDef_t* USARTn, u8 data){
	while(!(USARTn->SR & (1<<7)));
	USARTn->DR = data;
}

void USART_voidReceiveData(st_USART_RegDef_t* USARTn, u8* data){
	while(!(USARTn->SR & (1<<5)));
	*data = USARTn->DR;
}

static void USART_voidConfigurePins(st_USART_RegDef_t* USARTn, u8 mode){
	GPIO_Config_t USARTConfig;
	USARTConfig.mode = GPIO_ALT_FN;
	USARTConfig.outType = GPIO_PUSH_PULL;
	USARTConfig.pupdState = GPIO_NO_PUPD;
	USARTConfig.speed = GPIO_HIGH_SPEED;

	if(USARTn == USART1){
		USARTConfig.AltFuncMode = GPIO_AF7;
		GPIO_voidInitPin(PORTA, 9, &USARTConfig);	// TX
		GPIO_voidInitPin(PORTA, 10, &USARTConfig);	// RX
		if(mode == USART_SYNCHRONOUS)
			GPIO_voidInitPin(PORTA, 8, &USARTConfig); 	// CK
		if(mode == USART_HARDWARE_FLOW_CONTROL){
			GPIO_voidInitPin(PORTA, 11, &USARTConfig);	// CTS
			GPIO_voidInitPin(PORTA, 12, &USARTConfig);	// RTS
		}
	}
	else if(USARTn == USART2){
		USARTConfig.AltFuncMode = GPIO_AF7;
		GPIO_voidInitPin(PORTA, 2, &USARTConfig);	// TX
		GPIO_voidInitPin(PORTA, 3, &USARTConfig);	// RX
		if(mode == USART_SYNCHRONOUS)
			GPIO_voidInitPin(PORTA, 4, &USARTConfig);	// CK
		if(mode == USART_HARDWARE_FLOW_CONTROL){
			GPIO_voidInitPin(PORTA, 0, &USARTConfig); 	// CTS
			GPIO_voidInitPin(PORTA, 1, &USARTConfig);	// RTS
		}
	}
	else if(USARTn == USART6){
		USARTConfig.AltFuncMode = GPIO_AF8;
		GPIO_voidInitPin(PORTA, 11, &USARTConfig);	// TX
		GPIO_voidInitPin(PORTA, 12, &USARTConfig);	// RX
	}
}
