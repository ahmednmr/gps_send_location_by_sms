

#ifndef GPS_SKM55_H_
#define GPS_SKM55_H_

#include <avr/interrupt.h>
#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

#define DEFAULT_GPS_BUFFER_SIZE 100

typedef struct
{
	char time[9];
	char longitude[15];
	char latitude[15];


}GPS_info;


unsigned char counter;
void Clear_GPS_REC_Buffer(char * buffer);
bool GPS_Get_time_longitude_latitude_NMEA_format(char* buffer,GPS_info* GPS_information);

bool GPS_change_time_zone(GPS_info* GPS_information_orginal,GPS_info* GPS_information_modified );
bool GPS_Calculating_longitude_from_NMEA(GPS_info* GPS_information_orginal,GPS_info* GPS_information_modified );
bool GPS_Calculating_latitude_from_NMEA(GPS_info* GPS_information_orginal,GPS_info* GPS_information_modified );



#endif /* GPS_SKM55_H_ */
