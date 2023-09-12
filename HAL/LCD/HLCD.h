/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.h
 *
 * Description: header file for the AVR LCD driver
 *
 * Author: Begad Elsamadesy
 *
 *******************************************************************************/
#ifndef LCD_H_
#define LCD_H_

#include "../../Utilities/STD_TYPES.h"
#include "../../Utilities/BIT_Math.h"

#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "../../MCAL/SYSTICK/SYSTICK_Interface.h"

/**********************************************************************************************
 									 & Ports Configurations
 **********************************************************************************************/
#define LCD_DATA_BITS_MODE					4

#define LCD_RS_PORT_ID						PORTB
#define LCD_RS__ID						0
GPIO_Config_t LCD_RS_Config		=	{GPIO_OUTPUT,GPIO_PUSH_PULL,GPIO_MEDUIM_SPEED,GPIO_PULL_DOWN,GPIO_AF0};

#define LCD_ENABLE_PORT_ID					PORTB
#define LCD_ENABLE__ID					1
GPIO_Config_t LCD_Enable_Config	=	{GPIO_OUTPUT,GPIO_PUSH_PULL,GPIO_MEDUIM_SPEED,GPIO_PULL_DOWN,GPIO_AF0};

#define LCD_DB_PORT_ID						PORTA
GPIO_Config_t LCD_DB_PORTConfig		=	{GPIO_OUTPUT,GPIO_PUSH_PULL,GPIO_MEDUIM_SPEED,GPIO_PULL_DOWN,GPIO_AF0};


#if(LCD_DATA_BITS_MODE==4)
#define LCD_DB4__ID              	    3
#define LCD_DB5__ID						4
#define LCD_DB6__ID						5
#define LCD_DB7__ID                 		6
GPIO_Config_t LCD_DB4_Config		=	{GPIO_OUTPUT,GPIO_PUSH_PULL,GPIO_MEDUIM_SPEED,GPIO_PULL_DOWN,GPIO_AF0};
GPIO_Config_t LCD_DB5_Config		=	{GPIO_OUTPUT,GPIO_PUSH_PULL,GPIO_MEDUIM_SPEED,GPIO_PULL_DOWN,GPIO_AF0};
GPIO_Config_t LCD_DB6_Config		=	{GPIO_OUTPUT,GPIO_PUSH_PULL,GPIO_MEDUIM_SPEED,GPIO_PULL_DOWN,GPIO_AF0};
GPIO_Config_t LCD_DB7_Config		=	{GPIO_OUTPUT,GPIO_PUSH_PULL,GPIO_MEDUIM_SPEED,GPIO_PULL_DOWN,GPIO_AF0};
#endif

/**********************************************************************************************
 											Commands
 **********************************************************************************************/
#define LCD_CLEAR_SCREEN					0x01
#define LCD_SHIFT_CURSOR_LEFT				0x04
#define LCD_SHIFT_CURSOR_RIGHT				0x06
#define LCD_CURSOR_OFF						0x0C
#define LCD_CURSOR_ON						0x0E
#define LCD_BIT4_LINE2						0x28
#define LCD_BIT4_LINE2_INIT1 				0x33
#define LCD_BIT4_LINE2_INIT2  				0x32
#define LCD_BIT8_LINE2						0x38
#define LCD_SET_CURSOR_LOCATION        	    0x80

/*********************************************************************************************
									Function Prototypes
 *********************************************************************************************/
void LCD_voidInit(void);
void LCD_voidSendCommand(u8 command);
void LCD_voidDisplayCharacter(u8 character);
void LCD_voidDisplayString(char *Str);
void LCD_voidMoveCursor(u8 row,u8 col);
void LCD_voidDisplayStringRowColumn(u8 row,u8 col,char *Str);
void LCD_voidIntgerToString(u32 data);
void LCD_voidClearScreen(void);

#endif /* LCD_H_ */
