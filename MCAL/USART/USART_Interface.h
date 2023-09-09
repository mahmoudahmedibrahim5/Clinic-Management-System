/*
 * USART_Interface.h
 *
 *  Created on: Jun 17, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef USART_USART_INTERFACE_H_
#define USART_USART_INTERFACE_H_

#include "../../Utilities/STD_TYPES.h"
#include "../GPIO/GPIO_Interface.h"
#include "USART_Config.h"
#include "USART_Registers.h"

void USART_voidInit(st_USART_RegDef_t* USARTn, USART_Config_t* config);

void USART_voidSendData(st_USART_RegDef_t* USARTn, u8 data);
void USART_voidReceiveData(st_USART_RegDef_t* USARTn, u8* data);

#endif /* USART_USART_INTERFACE_H_ */
