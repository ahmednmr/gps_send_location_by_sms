/*
 * main.c
 *
 *  Created on: 5 Oct 2015
 *      Author: EmbeddedFab
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "MCAL/UART.h"
#include <avr/interrupt.h>

#include "stdlib.h"
#include "string.h"

#define TRUE 1
#define FALSE 0

#define SEND_SMS             1

#define DEFAULT_BUFFER_SIZE 100
char Rec_Data[DEFAULT_BUFFER_SIZE];
char Counter=0;

void GSM_init(void);
char Check_Respond(char * Expected_Respond);
char Check_Word_in_Respond(char * Word);
void Clear_REC_Buffer(void);


ISR (USART_RXC_vect)
{
	uint8_t oldsrg = SREG;
	cli();
	Rec_Data[Counter] = UDR;
	Counter++;
	if(Counter == DEFAULT_BUFFER_SIZE){
		Counter = 0; //pointer = 0;
	}
	SREG = oldsrg;
}


int main()
{
	GSM_init();
	DDRD |=(1<<PD2)|(1<<PD7);


	while(1)
	{

		PORTD &=~(1<<PD7);

		if(PIND&(1<<PD2))
		{
			PORTD |=(1<<PD7);
			_delay_ms(300);

			UART_SEND_string("AT+CMGF=1\r");
			//		while(!Check_Respond("\r\nOK\r\n"))
			//		{
			//			_delay_ms(1);
			//		}
			_delay_ms(1000);

			UART_SEND_string("AT+CMGS=\"01115948824\"\r");
			//		while(!Check_Respond("\r\nOK\r\n"))
			//		{
			//			_delay_ms(1);
			//		}
			_delay_ms(1000);

//			UART_SEND_string("Hello From GSM Module");   //https://www.google.com/maps/place/30.0110647,31.2067936
//			UART_SendChar(0x1A);
//			//		while(!Check_Respond("\r\nOK\r\n"))
			//		{
			//			_delay_ms(1);
			//		}

			UART_SEND_string("https://www.google.com/maps/place/");
			UART_SEND_string("30.0110647");
			UART_SEND_string(",");
			UART_SEND_string("31.2067936");
			UART_SendChar(0x1A);













			_delay_ms(3000);
		}

	}


	return 0;
}


char Check_Respond(char * Expected_Respond)
{
	char Respond_Length=0;

	Respond_Length=strlen(Expected_Respond);

	if(strncmp(Rec_Data,Expected_Respond, Respond_Length)==0)
	{
		Clear_REC_Buffer();
		return TRUE;
	}
	return FALSE;


}


char Check_Word_in_Respond(char * Word)
{


	if(strstr(Rec_Data,Word) != 0)
	{
		Clear_REC_Buffer();
		return TRUE;
	}

	return FALSE;
}

void Clear_REC_Buffer(void)
{
	Counter=0;
	memset(Rec_Data,0,DEFAULT_BUFFER_SIZE);
}


void GSM_init(void)
{
	init_UART();    //baudrate 9600
	sei();

	_delay_ms(1000);
	Clear_REC_Buffer();
	UART_SEND_string("ATE1\r");
	//	while(!((Check_Respond("\r\nOK\r\n"))||(Check_Respond("ATE0\r\r\n\r\nOK\r\n"))))
	//	{
	//		_delay_ms(1);
	//	}
	_delay_ms(3000);
}





//
