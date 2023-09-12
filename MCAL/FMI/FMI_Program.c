/*
 * FMI_Program.c
 *
 *  Created on: Sep 4, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */


#include "FMI_Interface.h"

void FMI_voidSectorErase(EN_FlashSectors_t sector)
{
	/* Check that no Flash memory operation is ongoing */
	while((FMI->SR>>16)&1);

	/* Unlock Control Register */
	if(FMI->CR>>31 & 1)
	{
		FMI->KEYR = FMI_KEY1;
		FMI->KEYR = FMI_KEY2;
	}

	/* Enable Sector Erase */
	FMI->CR |= (1<<1);

	/* Choose The sector */
	FMI->CR &= ~(0b111<<3);
	FMI->CR |= (sector<<3);

	/* Start the erase */
	FMI->CR |= (1<<16);

	/* Check that no Flash memory operation is ongoing */
	while((FMI->SR>>16)&1);
}

void FMI_voidMassErase(void)
{
	/* Check that no Flash memory operation is ongoing */
	while((FMI->SR>>16)&1);

	/* Unlock Control Register */
	if(FMI->CR>>31 & 1)
	{
		FMI->KEYR = FMI_KEY1;
		FMI->KEYR = FMI_KEY2;
	}

	/* Enable Mass Erase */
	FMI->CR |= (1<<2);

	/* Start the erase */
	FMI->CR |= (1<<16);

	/* Check that no Flash memory operation is ongoing */
	while((FMI->SR>>16)&1);
}

void FMI_voidFlashWrite(u32* flashAddress, u32* buffer, u32 len)
{
	/* Check that no Flash memory operation is ongoing */
	while((FMI->SR>>16)&1);

	/* Unlock Control Register */
	if(FMI->CR>>31 & 1)
	{
		FMI->KEYR = FMI_KEY1;
		FMI->KEYR = FMI_KEY2;
	}

	/* Choose Data Width */
	FMI->CR |= (FMI_PARALLELISM<<8);

	/* Enable Programming */
	FMI->CR |= (1<<0);

	/* Start the programming */
	FMI->CR |= (1<<16);

	/* Check that no Flash memory operation is ongoing */
	while((FMI->SR>>16)&1);
}
