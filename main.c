/*
 * main.c
 *
 *  Created on: 5 Oct 2015
 *      Author: EmbeddedFab
 */
#include "HAL/gsm.h"
#include "HAL/LCD.h"
#include "softuart.h"
#include"GPS_SKM55.h"
char RX_GPS_Search_buffer[DEFAULT_GPS_BUFFER_SIZE]={0};



int main()
{
	char c;
	GPS_info GPS_SKM55_information_original;
	GPS_info GPS_SKM55_information_modified;

	LCD_VidInit();
	LCD_vidsendword_with_clear("start");
	softuart_init();
	softuart_turn_rx_on(); /* redundant - on by default */
	sei();


	GSM_init();
	DDRD &=~(1<<PD2);

	UART_SEND_string("ATE1\r");
	_delay_ms(3000);
	LCD_vidsendword_with_clear("start program");
	while(1)
	{


		if ( softuart_kbhit() ) {
			c = softuart_getchar();
			RX_GPS_Search_buffer[counter++]=c;
			if(counter==DEFAULT_GPS_BUFFER_SIZE) 	Clear_GPS_REC_Buffer(RX_GPS_Search_buffer);

		}




		if(strstr(RX_GPS_Search_buffer,"GPGGA") )
		{
			Clear_GPS_REC_Buffer(RX_GPS_Search_buffer);
		}
		if(strstr(RX_GPS_Search_buffer,"GPGSA") )
		{

			GPS_Get_time_longitude_latitude_NMEA_format(RX_GPS_Search_buffer,&GPS_SKM55_information_original);

			GPS_change_time_zone(&GPS_SKM55_information_original,&GPS_SKM55_information_modified);
			GPS_Calculating_longitude_from_NMEA(&GPS_SKM55_information_original,&GPS_SKM55_information_modified);
			GPS_Calculating_latitude_from_NMEA(&GPS_SKM55_information_original,&GPS_SKM55_information_modified);

//			LCD_vidClear();
//			LCD_vidsendword("long :");
//			LCD_vidsendword(GPS_SKM55_information_modified.longitude);
//			LCD_vidGoTo(1,0);
//			LCD_vidsendword("lati :");
//			LCD_vidsendword(GPS_SKM55_information_modified.latitude);
//
//			_delay_ms(300);
//			GPS_SKM55_information_modified.longitude
//			GPS_SKM55_information_modified.latitude
//

			Clear_GPS_REC_Buffer(RX_GPS_Search_buffer);
		}





		if(PIND&(1<<PD2))
		{
			LCD_vidsendword_with_clear("button pressed");
			_delay_ms(300);

			UART_SEND_string("AT+CMGF=1\r");
			//		while(!Check_Respond("\r\nOK\r\n"))
			//		{
			//			_delay_ms(1);
			//		}
			_delay_ms(2000);

			UART_SEND_string("AT+CMGS=\"01115948824\"\r");
			//		while(!Check_Respond("\r\nOK\r\n"))
			//		{
			//			_delay_ms(1);
			//		}
			_delay_ms(2000);

			//						UART_SEND_string("Hello From GSM Module");   //https://www.google.com/maps/place/30.0110647,31.2067936
			//						UART_SendChar(0x1A);
			//			//			//		while(!Check_Respond("\r\nOK\r\n"))
			//		{
			//			_delay_ms(1);
			//		}

			UART_SEND_string("Hajj number A001 needs help at location ");
			UART_SEND_string("https://www.google.com/maps/place/");
			UART_SEND_string(GPS_SKM55_information_modified.longitude);
			UART_SEND_string(",");
			UART_SEND_string(GPS_SKM55_information_modified.latitude);
			UART_SendChar(0x1A);

			LCD_vidsendword_with_clear("done sending");
		}

	}


	return 0;
}



//
