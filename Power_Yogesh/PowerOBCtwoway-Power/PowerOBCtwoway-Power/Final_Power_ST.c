/*
 * Final_Power.c
 *
 * Created: 11/4/2017 7:22:58 PM
 * Author : mr_natwarlal
 */ 

#include <avr/io.h>
#include "avr/interrupt.h"
#include "TWI_slave.h"
#include "common.h"
#include "uart.h"
//-----------slave transmitter----------------------//

/*int main(void)
{
    sei();
	unsigned char HM_data[7];
	//unsigned char msg_buf[8];
	unsigned char SLA=0x20;		
	
	init_UART();
	TWI_Slave_Initialise(SLA);
	HM_data[0]=receive_UART();
	TWI_Start_Transceiver_With_Data(HM_data,1);
    while (1) 
    {
		transmit_UART('2');
		_delay_ms(100);
		transmit_UART('3');
	}
}
*/
