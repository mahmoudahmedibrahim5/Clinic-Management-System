/*
 * USART_Registers.h
 *
 *  Created on: Jun 17, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef USART_USART_REGISTERS_H_
#define USART_USART_REGISTERS_H_

#define USART1_BASE_ADDR				0x40011000U
#define USART2_BASE_ADDR				0x40004400U
#define USART6_BASE_ADDR				0x40011400U

typedef volatile struct{
	u32 SR;
	u32 DR;
	u32 BRR;
	u32 CR1;
	u32 CR2;
	u32 CR3;
	u32 GTPR;
}st_USART_RegDef_t;

#define USART1		((st_USART_RegDef_t*)USART1_BASE_ADDR)
#define USART2		((st_USART_RegDef_t*)USART2_BASE_ADDR)
#define USART6		((st_USART_RegDef_t*)USART6_BASE_ADDR)

#endif /* USART_USART_REGISTERS_H_ */
