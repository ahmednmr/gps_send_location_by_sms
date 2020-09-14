/*
 * gsm.c
 *
 *  Created on: Sep 14, 2020
 *      Author: embeddedfab
 */

#include "gsm.h"

char Rec_Data[DEFAULT_BUFFER_SIZE];
char Counter=0;

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

