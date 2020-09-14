/*
 * gsm.h
 *
 *  Created on: Sep 14, 2020
 *      Author: embeddedfab
 */

#ifndef GSM_H_
#define GSM_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "../MCAL/UART.h"
#include <avr/interrupt.h>
#include "stdlib.h"
#include "string.h"

#define TRUE 1
#define FALSE 0



#define DEFAULT_BUFFER_SIZE 100


void GSM_init(void);
char Check_Respond(char * Expected_Respond);
char Check_Word_in_Respond(char * Word);
void Clear_REC_Buffer(void);


#endif /* GSM_H_ */
