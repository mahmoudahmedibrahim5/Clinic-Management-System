/*
 * RCC_Interface.h
 *
 *  Created on: Feb 8, 2023
 *      Author: MAhmoud Ahmed Ibrahim
 */

#ifndef RCC_RCC_INTERFACE_H_
#define RCC_RCC_INTERFACE_H_

#include "../../Utilities/STD_TYPES.h"
#include "RCC_Registers.h"
#include "RCC_Private.h"
#include "RCC_Config.h"

void RCC_voidInit();

void RCC_voidPeripheralEnable(EN_peripheral_t per);
void RCC_voidPeripheralDisable(EN_peripheral_t per);

void RCC_voidPeripheralLowPowerEnable(EN_peripheral_t per);
void RCC_voidPeripheralLowPowerDisable(EN_peripheral_t per);

void RCC_voidPeripheralReset(EN_peripheral_t per);

#endif /* RCC_RCC_INTERFACE_H_ */
