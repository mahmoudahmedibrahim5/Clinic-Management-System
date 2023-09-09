/*
 * RCC_Config.h
 *
 *  Created on: Feb 16, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef RCC_RCC_CONFIG_H_
#define RCC_RCC_CONFIG_H_


/* ********** System clock **********
 * Choose the system clock
 * HSI, HSE, PLL
 * */
#define SYS_CLK		HSI

/* ********** Buses clock prescaler **********
 * Choose the prescaler
 * for AHB choose from (1, 2, 4, 8, 16, 64, 128, 256, 512)
 * for APB1 choose from (2, 4, 8, 16)
 * for APB2 choose from (2, 4, 8, 16)
 * */
#define RCC_AHB_PRESCALER  1
#define RCC_APB1_PRESCALER 1
#define RCC_APB2_PRESCALER 1

/* ********** Clock Security system **********
 * Choose to enable or disable this feature
 * ENABLE
 * DISABLE
 */

#define RCC_CSS_ENABLE	RCC_ENABLE


/* ********** Peripheral Enable and Disable **********
 * Pass the required peripheral enable to functions
 * void RCC_peripheralEn(EN_peripheral_t per)
 * void RCC_peripheralDis(EN_peripheral_t per)
 * void RCC_peripheralLowPowerEn(EN_peripheral_t per)
 * void RCC_peripheralLowPowerDis(EN_peripheral_t per)
 *
 */

typedef enum {
	// AHB1
	GPIOA_EN,
	GPIOB_EN,
	GPIOC_EN,
	GPIOD_EN,
	GPIOE_EN,
	GPIOH_EN,
	CRC_EN,
	DMA1_EN,
	DMA2_EN,
	// AHB2
	OTGFS_EN,
	// APB1
	TIM2_EN,
	TIM3_EN,
	TIM4_EN,
	TIM5_EN,
	WWDG_EN,
	SPI2_EN,
	SPI3_EN,
	USART2_EN,
	I2C1_EN,
	I2C2_EN,
	I2C3_EN,
	PWR_EN,
	// APB2
	TIM1_EN,
	USART1_EN,
	USART6_EN,
	ADC1_EN,
	SDIO_EN,
	SPI1_EN,
	SPI4_EN,
	SYSCFG_EN,
	TIM9_EN,
	TIM10_EN,
	TIM11_EN
}EN_peripheral_t;

#endif /* RCC_RCC_CONFIG_H_ */
