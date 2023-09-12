/*
 * FMI_Registers.h
 *
 *  Created on: Sep 4, 2023
 *      Author: Mahmoud Ahmed Ibrahim
 */

#ifndef FMI_FMI_REGISTERS_H_
#define FMI_FMI_REGISTERS_H_

#define FLASH_INTERFACE_BASE_ADDR		0x40023C00U

typedef volatile struct{
	u32 ACR;
	u32 KEYR;
	u32 OPTKEYR;
	u32 SR;
	u32 CR;
	u32 OPTCR;
}st_FMI_RegDef_t;

#define FMI ((st_FMI_RegDef_t *) FLASH_INTERFACE_BASE_ADDR)

#endif /* FMI_FMI_REGISTERS_H_ */
