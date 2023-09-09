/*
 * GPIO_Config.h
 *
 *  Created on: Jul 1, 2023
 *      Author: ADMIN
 */

#ifndef GPIO_GPIO_CONFIG_H_
#define GPIO_GPIO_CONFIG_H_

typedef struct{
	u8 mode;		// pin modes
	u8 outType;	// Output types
	u8 speed;		// speed levels
	u8 pupdState;	// Pull up pull down states
	u8 AltFuncMode;// Alternate functions modes
}GPIO_Config_t;

/* pin modes */
#define GPIO_INPUT	 			0
#define GPIO_OUTPUT	 			1
#define GPIO_ALT_FN 			2
#define GPIO_ANALOG 			3
/* Output types */
#define GPIO_PUSH_PULL			0
#define GPIO_OPEN_DRAIN			1
/* Speed levels */
#define GPIO_LOW_SPEED			0
#define GPIO_MEDUIM_SPEED		1
#define GPIO_HIGH_SPEED			2
#define GPIO_VERY_HIGH_SPEED	3
/* Pull up pull down states */
#define GPIO_NO_PUPD 			0
#define GPIO_PULL_UP 			1
#define GPIO_PULL_DOWN			2
/* Alternate functions modes */
typedef enum {
	GPIO_AF0,
	GPIO_AF1,
	GPIO_AF2,
	GPIO_AF3,
	GPIO_AF4,
	GPIO_AF5,
	GPIO_AF6,
	GPIO_AF7,
	GPIO_AF8,
	GPIO_AF9,
	GPIO_AF10,
	GPIO_AF11,
	GPIO_AF12,
	GPIO_AF13,
	GPIO_AF14,
	GPIO_AF15
} EN_AlternateFunctions_t;

#endif /* GPIO_GPIO_CONFIG_H_ */
