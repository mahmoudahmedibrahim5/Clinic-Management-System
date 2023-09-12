/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.c
 *
 * Description: Source file for the AVR LCD driver
 *
 * Author: Begad Elsamadesy
 *
 *******************************************************************************/

#include "HLCD.h"

GPIO_Config_t LCD_RS_PinConfig		=	{GPIO_OUTPUT,GPIO_PUSH_PULL,GPIO_MEDUIM_SPEED,GPIO_PULL_DOWN,GPIO_AF0};
GPIO_Config_t LCD_Enable_PinConfig	=	{GPIO_OUTPUT,GPIO_PUSH_PULL,GPIO_MEDUIM_SPEED,GPIO_PULL_DOWN,GPIO_AF0};
GPIO_Config_t LCD_DB_PORTConfig		=	{GPIO_OUTPUT,GPIO_PUSH_PULL,GPIO_MEDUIM_SPEED,GPIO_PULL_DOWN,GPIO_AF0};

GPIO_Config_t LCD_DB4_PinConfig		=	{GPIO_OUTPUT,GPIO_PUSH_PULL,GPIO_MEDUIM_SPEED,GPIO_PULL_DOWN,GPIO_AF0};
GPIO_Config_t LCD_DB5_PinConfig		=	{GPIO_OUTPUT,GPIO_PUSH_PULL,GPIO_MEDUIM_SPEED,GPIO_PULL_DOWN,GPIO_AF0};
GPIO_Config_t LCD_DB6_PinConfig		=	{GPIO_OUTPUT,GPIO_PUSH_PULL,GPIO_MEDUIM_SPEED,GPIO_PULL_DOWN,GPIO_AF0};
GPIO_Config_t LCD_DB7_PinConfig		=	{GPIO_OUTPUT,GPIO_PUSH_PULL,GPIO_MEDUIM_SPEED,GPIO_PULL_DOWN,GPIO_AF0};

void LCD_voidInit(void)
{
	GPIO_voidInitPin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,&LCD_RS_PinConfig);
	GPIO_voidInitPin(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID,&LCD_Enable_PinConfig);
#if((LCD_DATA_BITS_MODE==8))
	GPIO_voidInitPort(LCD_DB_PORT_ID,&LCD_DB_PORTConfig);
	SYSTICK_voidDelayMilliSec(20);
	LCD_voidSendCommand(LCD_BIT8_LINE2);
#elif ((LCD_DATA_BITS_MODE==4))
	GPIO_voidInitPin(LCD_DB_PORT_ID,LCD_DB4_PIN_ID,&LCD_DB4_PinConfig);
	GPIO_voidInitPin(LCD_DB_PORT_ID,LCD_DB5_PIN_ID,&LCD_DB5_PinConfig);
	GPIO_voidInitPin(LCD_DB_PORT_ID,LCD_DB6_PIN_ID,&LCD_DB6_PinConfig);
	GPIO_voidInitPin(LCD_DB_PORT_ID,LCD_DB7_PIN_ID,&LCD_DB7_PinConfig);
	LCD_voidSendCommand(LCD_BIT4_LINE2_INIT1);
	LCD_voidSendCommand(LCD_BIT4_LINE2_INIT2);
	LCD_voidSendCommand(LCD_BIT4_LINE2);
#endif

	LCD_voidSendCommand(LCD_CURSOR_OFF);
	LCD_voidSendCommand(LCD_CLEAR_SCREEN);
}

void LCD_voidSendCommand(u8 command)
{
	GPIO_voidSetPinValue(LCD_RS_PORT_ID,LCD_RS_PIN_ID,GPIO_LOW);
	SYSTICK_voidDelayMilliSec(1);
	GPIO_voidSetPinValue(LCD_ENABLE_PORT_ID,LCD_ENABLE_PIN_ID,GPIO_HIGH);
	SYSTICK_voidDelayMilliSec(1);
#if ((LCD_DATA_BITS_MODE==4))
	GPIO_voidSetPinValue(LCD_DB_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command,4));
	GPIO_voidSetPinValue(LCD_DB_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command,5));
	GPIO_voidSetPinValue(LCD_DB_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command,6));
	GPIO_voidSetPinValue(LCD_DB_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command,7));
	SYSTICK_voidDelayMilliSec(1);
	GPIO_voidSetPinValue(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, GPIO_LOW);
	SYSTICK_voidDelayMilliSec(1);
	GPIO_voidSetPinValue(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, GPIO_HIGH);
	SYSTICK_voidDelayMilliSec(1);
	GPIO_voidSetPinValue(LCD_DB_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command,0));
	GPIO_voidSetPinValue(LCD_DB_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command,1));
	GPIO_voidSetPinValue(LCD_DB_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command,2));
	GPIO_voidSetPinValue(LCD_DB_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command,3));
	SYSTICK_voidDelayMilliSec(1);
#elif((LCD_DATA_BITS_MODE==8))
	GPIO_voidSetPortValue(LCD_DB_PORT_ID,command);
	SYSTICK_voidDelayMilliSec(1);
#endif
	GPIO_voidSetPinValue(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, GPIO_LOW);
	SYSTICK_voidDelayMilliSec(1);
}

void LCD_voidDisplayu8acter(u8 u8acter)
{
	GPIO_voidSetPinValue(LCD_RS_PORT_ID, LCD_RS_PIN_ID, GPIO_HIGH);
	SYSTICK_voidDelayMilliSec(1);
	GPIO_voidSetPinValue(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, GPIO_HIGH);
	SYSTICK_voidDelayMilliSec(1);
	GPIO_voidSetPortValue(PORTC, u8acter);
	SYSTICK_voidDelayMilliSec(1);
#if ((LCD_DATA_BITS_MODE==4))
	GPIO_voidSetPinValue(LCD_DB_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(u8acter,4));
	GPIO_voidSetPinValue(LCD_DB_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(u8acter,5));
	GPIO_voidSetPinValue(LCD_DB_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(u8acter,6));
	GPIO_voidSetPinValue(LCD_DB_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(u8acter,7));
	SYSTICK_voidDelayMilliSec(1);
	GPIO_voidSetPinValue(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, GPIO_LOW);
	SYSTICK_voidDelayMilliSec(1);
	GPIO_voidSetPinValue(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, GPIO_HIGH);
	SYSTICK_voidDelayMilliSec(1);
	GPIO_voidSetPinValue(LCD_DB_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(u8acter,0));
	GPIO_voidSetPinValue(LCD_DB_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(u8acter,1));
	GPIO_voidSetPinValue(LCD_DB_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(u8acter,2));
	GPIO_voidSetPinValue(LCD_DB_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(u8acter,3));
	SYSTICK_voidDelayMilliSec(1);
#elif((LCD_DATA_BITS_MODE==8))
	GPIO_voidSetPortValue(LCD_DB_PORT_ID, u8acter);
	SYSTICK_voidDelayMilliSec(1);
#endif
	GPIO_voidSetPinValue(LCD_ENABLE_PORT_ID, LCD_ENABLE_PIN_ID, GPIO_LOW);
	SYSTICK_voidDelayMilliSec(1);
}

void LCD_voidDisplayString(u8 *Str)
{
	u8 i=0;
	while(Str[i]!='\0')
	{
		LCD_voidDisplayu8acter(Str[i]);
		i++;
	}
}

void LCD_voidMoveCursor(u8 row,u8 col)
{
	u8 lcd_meomry_address=0;
	switch (row)
	{
	case 0:
		lcd_meomry_address=col;
		break;
	case 1:
		lcd_meomry_address=col+0x40;
		break;
	case 2:
		lcd_meomry_address=col+0x10;
		break;
	case 3:
		lcd_meomry_address=col+0x50;
		break;
	}
	LCD_voidSendCommand(lcd_meomry_address|LCD_SET_CURSOR_LOCATION);
}

void LCD_voidDisplayStringRowColumn(u8 row,u8 col,u8 *Str)
{
	LCD_voidMoveCursor(row, col);
	LCD_voidDisplayString(Str);
}

void LCD_voidIntgerToString(u32 data)
{
	u8 buff[16];				/* String to hold the ascii result */
	itoa(data,buff,10);			/* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	LCD_voidDisplayString(buff);
}

void LCD_voidClearScreen(void)
{
	LCD_voidSendCommand(LCD_CLEAR_SCREEN);
}
