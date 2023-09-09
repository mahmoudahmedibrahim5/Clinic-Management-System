/*
 * GPIO_Registers.h
 *
 *  Created on: Feb 8, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef GPIO_GPIO_REGISTERS_H_
#define GPIO_GPIO_REGISTERS_H_

#define GPIOA_BASE_ADDR					0x40020000U
#define GPIOB_BASE_ADDR					0x40020400U
#define GPIOC_BASE_ADDR					0x40020800U
#define GPIOD_BASE_ADDR					0x40020C00U
#define GPIOE_BASE_ADDR					0x40021000U
#define GPIOH_BASE_ADDR					0x40021C00U

typedef volatile struct{
	u32 MODER;		// GPIO port mode register
	u32 OTYPER;		// GPIO port output type register
	u32 OSPEEDR;	// GPIO port output speed register
	u32 PUPDR;		// GPIO port pull-up/pull-down register
	u32 IDR;		// GPIO port input data register
	u32 ODR;		// GPIO port output data register
	u32 BSRR;		// GPIO port bit set/reset register
	u32 LCKR;		// GPIO port configuration lock register
	u32 AFRL;		// GPIO alternate function low register
	u32 AFRH;		// GPIO alternate function high register
}st_GPIO_RegDef_t;

#define GPIOA		((st_GPIO_RegDef_t *)GPIOA_BASE_ADDR)
#define GPIOB		((st_GPIO_RegDef_t *)GPIOB_BASE_ADDR)
#define GPIOC		((st_GPIO_RegDef_t *)GPIOC_BASE_ADDR)
#define GPIOD		((st_GPIO_RegDef_t *)GPIOD_BASE_ADDR)
#define GPIOE		((st_GPIO_RegDef_t *)GPIOE_BASE_ADDR)
#define GPIOH		((st_GPIO_RegDef_t *)GPIOH_BASE_ADDR)

#endif /* GPIO_GPIO_REGISTERS_H_ */
