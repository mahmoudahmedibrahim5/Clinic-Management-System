/*
 * RCC_Registers.h
 *
 *  Created on: Feb 8, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef RCC_RCC_REGISTERS_H_
#define RCC_RCC_REGISTERS_H_

#define RCC_BASE_ADDR					0x40023800U

typedef volatile struct{
	u32 CR;
	u32 PLLCFGR;
	u32 CFGR;
	u32 CIR;
	u32 AHB1RSTR;
	u32 AHB2RSTR;
	u32 reserved1[2];
	u32 APB1RSTR;
	u32 APB2RSTR;
	u32 reserved2[2];
	u32 AHB1ENR;
	u32 AHB2ENR;
	u32 reserved3[2];
	u32 APB1ENR;
	u32 APB2ENR;
	u32 reserved4[2];
	u32 AHB1LPENR;
	u32 AHB2LPENR;
	u32 reserved[2];
	u32 APB1LPENR;
	u32 APB2LPENR;
	u32 reserved6[2];
	u32 BDCR;
	u32 CSR;
	u32 reserved7[2];
	u32 SSCGR;
	u32 PLLI2SCFGR;
	u32 reserved8;
	u32 DCKCFGR;
}st_RCC_RegDef_t;

#define RCC		((st_RCC_RegDef_t *)RCC_BASE_ADDR)

/* CR Register Bits */
#define RCC_CR_HSI_ON	0
#define RCC_CR_HSE_ON	16
#define RCC_CR_PLL_ON	24

/* CFGR Register Bits */
#define RCC_CFGR_HSI	0
#define RCC_CFGR_HSE	1
#define RCC_CFGR_PLL	2

#endif /* RCC_RCC_REGISTERS_H_ */
