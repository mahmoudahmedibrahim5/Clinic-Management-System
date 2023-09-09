/*
 * USART_Config.h
 *
 *  Created on: Jun 17, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef USART_USART_CONFIG_H_
#define USART_USART_USART_CONFIG_H_

#define USART_F_CPU	16000000

typedef struct{
	u8 mode;
	u8 transmission;
	u8 overSampling;
	u8 dataSize;
	u8 stopBits;
	u8 parityType;
	u32 baudrate;
}USART_Config_t;

/* Modes */
#define USART_ASYNCHRONOUS				0
#define USART_HARDWARE_FLOW_CONTROL		1
#define USART_MULTIBUFFER				2
#define USART_MULTIPROCESSOR			3
#define USART_SYNCHRONOUS				4
#define USART_SMARTCARD					5
#define USART_HALF_DUPLEX				6
#define USART_IRDA						7
#define USART_LIN						8
/* Transmission and Reception */
#define USART_TX_ONLY					0
#define	USART_RX_ONLY					1
#define USART_TX_AND_RX					2
/* OverSampling */
#define USART_OVERSAMPLING16			0
#define USART_OVERSAMPLING8				1
/* Data size */
#define USART_DATA_SIZE_8_BIT			0
#define USART_DATA_SIZE_9_BIT			1
/* Stop Bits */
#define USART_STOP_BIT_1_BIT			0
#define USART_STOP_BIT_0_5_BIT			1
#define	USART_STOP_BIT_2_BIT			2
#define USART_STOP_BIT_1_5_BIT			3
/* Parity Type */
#define USART_EVEN_PARITY				0
#define USART_ODD_PARITY				1
#define USART_NO_PARITY					2
/* BaudRate */

#endif /* USART_USART_CONFIG_H_ */
