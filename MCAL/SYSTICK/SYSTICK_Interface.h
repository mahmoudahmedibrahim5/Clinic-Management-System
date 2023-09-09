/*
 * SYSTICK_Interface.h
 *
 *  Created on: Aug 19, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef SYSTICK_SYSTICK_INTERFACE_H_
#define SYSTICK_SYSTICK_INTERFACE_H_

#include "../../Utilities/STD_TYPES.h"
#include "SYSTICK_Registers.h"
#include "SYSTICK_Config.h"

void SYSTICK_voidInit(void);

void SYSTICK_voidDelayMilliSec(u32 ms);
void SYSTICK_voidDelayMicroSec(u32 us);

u32 SYSTICK_u32GetElapsedTime(void);
u32 SYSTICK_u32GetRemainingTime(void);

void SYSTICK_voidEnableInterrupt(void);
void SYSTICK_voidStartCountMilliSeconds(u32 ms, void(*ptr)(void));
void SYSTICK_voidStartCountMicroSeconds(u32 us, void(*ptr)(void));

void SYSTICK_voidSetCallBackFunction( void(*ptr)(void) );

#endif /* SYSTICK_SYSTICK_INTERFACE_H_ */
