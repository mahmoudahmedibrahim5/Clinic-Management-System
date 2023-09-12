/*
 * FMI_Interfave.h
 *
 *  Created on: Sep 4, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef FMI_FMI_INTERFAVE_H_
#define FMI_FMI_INTERFAVE_H_

#include "../../Utilities/STD_TYPES.h"

#include "FMI_Private.h"
#include "FMI_Registers.h"
#include "FMI_Config.h"

typedef enum{
	FLASH_SECTOR0,
	FLASH_SECTOR1,
	FLASH_SECTOR2,
	FLASH_SECTOR3,
	FLASH_SECTOR4,
	FLASH_SECTOR5,
	FLASH_SECTOR6
}EN_FlashSectors_t;

void FMI_voidSectorErase(EN_FlashSectors_t sector);
void FMI_voidMassErase(void);
void FMI_voidFlashWrite(u32* flashAddress, u32* buffer, u32 len);

#endif /* FMI_FMI_INTERFAVE_H_ */
