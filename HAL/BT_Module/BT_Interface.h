/*
 * BT.h
 *
 *  Created on: Jun 17, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef BT_MODULE_BT_H_
#define BT_MODULE_BT_H_

#include "../../MCAL/USART/USART_Interface.h"

typedef struct{
	st_USART_RegDef_t* USARTn;
	u32 baudrate;
}BT_t;

void BT_voidInit(BT_t* bt);
void BT_voidSendData(BT_t* bt, u8* buffer, u32 len);
void BT_voidReceiveData(BT_t* bt, u8* buffer, u32 len);

#endif /* BT_MODULE_BT_H_ */
