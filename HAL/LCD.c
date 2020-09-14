/*
 * lcd_prog.c
 *
 *  Created on: Jan 20, 2019
 *      LCD_ControlPORTuthor: Nmr
 */


#include "LCD.h"


void LCD_VidInit(void)
{
	LCD_DDR_DATA |= 0xf0;
	LCD_DDR_Control |=(1<<LCD_ENABLE_PIN)|(1<<LCD_RS_PIN);


	LCD_PORT_DATA &=~(0xf0);
	LCD_PORT_Control &=~((1<<LCD_ENABLE_PIN)|(1<<LCD_RS_PIN));

	_delay_ms(2);

	LCD_vidSendCommand(0x33);
	LCD_vidSendCommand(0x32);
	LCD_vidSendCommand(0x28);    /* initalization commands*/

	LCD_vidSendCommand(0x0e);
	LCD_vidSendCommand(0x01);
	_delay_ms(2);

	LCD_vidSendCommand(0x06);

}

void LCD_vidSendCommand(unsigned char command)
{


	LCD_PORT_Control &=~(1<<LCD_RS_PIN);   //RS zero send command


	LCD_PORT_DATA = (LCD_PORT_DATA & 0x0F) | (command & 0xF0); /* sending upper nibble */

	LCD_PORT_Control |=(1<<LCD_ENABLE_PIN);         /* Enable pulse */
	_delay_ms(2);
	LCD_PORT_Control &=~(1<<LCD_ENABLE_PIN);

	_delay_us(1);

	LCD_PORT_DATA = (LCD_PORT_DATA & 0x0F) | (command << 4);  /* sending lower nibble */
	LCD_PORT_Control |=(1<<LCD_ENABLE_PIN);         /* Enable pulse */
	_delay_ms(2);
	LCD_PORT_Control &=~(1<<LCD_ENABLE_PIN);

	_delay_ms(2);


}


void LCD_vidsendData(unsigned char character)
{

	LCD_PORT_Control |=(1<<LCD_RS_PIN);    //RS 1 send Data

	LCD_PORT_DATA = (LCD_PORT_DATA & 0x0F) | (character & 0xF0); /* sending upper nibble */

	LCD_PORT_Control |=(1<<LCD_ENABLE_PIN);         /* Enable pulse */
	_delay_ms(2);
	LCD_PORT_Control &=~(1<<LCD_ENABLE_PIN);

	_delay_us(1);

	LCD_PORT_DATA = (LCD_PORT_DATA & 0x0F) | (character << 4);  /* sending lower nibble */
	LCD_PORT_Control |=(1<<LCD_ENABLE_PIN);         /* Enable pulse */
	_delay_ms(2);
	LCD_PORT_Control &=~(1<<LCD_ENABLE_PIN);

	_delay_ms(2);


}

void LCD_vidsendword(char * word)
{
	while(*word!='\0')
	{
		LCD_vidsendData(*word);
		word++;

	}


}

void LCD_vidsendword_with_clear(char * word)
{
	LCD_vidClear();
	while(*word!='\0')
	{
		LCD_vidsendData(*word);
		word++;

	}


}


void LCD_vidClear(void)
{
	LCD_vidSendCommand(0x01);
}


void LCD_vid_Save_in_CGRAM(void)
{
	LCD_vidSendCommand(0b01000000);  //0x40   0b 0100 0000

	//   save Person
	LCD_vidsendData(0b01110);
	LCD_vidsendData(0b01110);
	LCD_vidsendData(0b00100);
	LCD_vidsendData(0b01110);
	LCD_vidsendData(0b10101);
	LCD_vidsendData(0b00100);
	LCD_vidsendData(0b01010);
	LCD_vidsendData(0b01010);

	//   save smile
	LCD_vidsendData(0b00000);
	LCD_vidsendData(0b00000);
	LCD_vidsendData(0b01010);
	LCD_vidsendData(0b00000);
	LCD_vidsendData(0b00000);
	LCD_vidsendData(0b10001);
	LCD_vidsendData(0b01110);
	LCD_vidsendData(0b00000);

	//   save LOCK
	LCD_vidsendData(0b01110);
	LCD_vidsendData(0b10001);
	LCD_vidsendData(0b10001);
	LCD_vidsendData(0b11111);
	LCD_vidsendData(0b11011);
	LCD_vidsendData(0b11011);
	LCD_vidsendData(0b11111);
	LCD_vidsendData(0b00000);


	//   save Heart
	LCD_vidsendData(0b00000);
	LCD_vidsendData(0b00000);
	LCD_vidsendData(0b01010);
	LCD_vidsendData(0b10101);
	LCD_vidsendData(0b10001);
	LCD_vidsendData(0b01110);
	LCD_vidsendData(0b00100);
	LCD_vidsendData(0b00000);


	///  SAVE Ï
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00001);
	LCD_vidsendData(0B00001);
	LCD_vidsendData(0B00001);
	LCD_vidsendData(0B11111);
	LCD_vidsendData(0B00000);

	///  SAVE ã
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B01110);
	LCD_vidsendData(0B10001);
	LCD_vidsendData(0B01110);

	///  SAVE  Í
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B01110);
	LCD_vidsendData(0B00001);
	LCD_vidsendData(0B11111);
	LCD_vidsendData(0B00000);


	///  SAVE Ã
	LCD_vidsendData(0b00110);
	LCD_vidsendData(0B00100);
	LCD_vidsendData(0B01110);
	LCD_vidsendData(0B00000);
	LCD_vidsendData(0B00100);
	LCD_vidsendData(0B00100);
	LCD_vidsendData(0B00100);
	LCD_vidsendData(0B00100);






}


void LCD_vidGoTo(unsigned char col,unsigned char Row)
{
	if(col==0)
	{
		LCD_vidSendCommand(0b10000000|Row);
	}

	else if(col==1)
	{
		LCD_vidSendCommand(0b11000000|Row);

	}


}
