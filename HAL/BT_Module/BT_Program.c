/*
 * BT.c
 *
 *  Created on: Jun 17, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#include "BT_Interface.h"

void BT_voidInit(BT_t* bt){
	USART_Config_t BM;
	BM.dataSize = USART_DATA_SIZE_8_BIT;
	BM.mode = USART_ASYNCHRONOUS;
	BM.overSampling = USART_OVERSAMPLING16;
	BM.transmission = USART_TX_AND_RX;
	BM.parityType = USART_NO_PARITY;
	BM.stopBits = USART_STOP_BIT_1_BIT;
	BM.baudrate = bt->baudrate;

	USART_voidInit(bt->USARTn, &BM);
}

void BT_voidSendData(BT_t* bt, u8* buffer, u32 len){
	for(u32 i=0; i<len; i++)
		USART_voidSendData(bt->USARTn, buffer[i]);
}

void BT_voidReceiveData(BT_t* bt, u8* buffer, u32 len){
	for(u32 i=0; i<len; i++)
		USART_voidReceiveData(bt->USARTn, &buffer[i]);
}
