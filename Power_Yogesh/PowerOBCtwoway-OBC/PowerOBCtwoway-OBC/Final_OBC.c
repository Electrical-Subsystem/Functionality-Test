/*
 * Final_OBC.c
 *
 * Created: 11/4/2017 7:25:55 PM
 * Author : sagar_chu
 */ 

#include <avr/io.h>
#include "avr/interrupt.h"
#include "TWI_Master.h"
#include "common.h"
#include "uart.h"

int main(void)
{
	sei();
	uint8_t HM_data[7];	
	unsigned char msg_buf[8];
	unsigned char SLA=0x20;
	
	HM_data[0]=SLA+0x00;
	msg_buf[0]=SLA+0x01;
	TWI_Master_Initialise();
	init_UART0();
	
    while (1) 
    {
		//-------------master transmitter----------------------//
		 
		//HM_data[1]=receive_UART0();
		HM_data[1]=0xB8;
		
		TWI_Start_Transceiver_With_Data(HM_data,2);//HM_data[0]=address,HM_data[1]=data
		//transmit_UART0('1');
		//_delay_ms(1000);
		//--------------------master receiver-------------------//
	
// 		TWI_Start_Transceiver_With_Data(msg_buf,2);//mr//twi buff =address, len should be >=1, could be anything more than that
// 		//transmit_UART0('2');
// 		unsigned char z = TWI_Get_Data_From_Transceiver(msg_buf,2);//msg_buf[0]=address, because in isr we defined that,msg_buf[1]=data 
// 		//transmit_UART0('3');
// 		
// 		//transmit_UART0(msg_buf[0]);//this prints address
// 		transmit_UART0(msg_buf[1]);//this prints data received
// 		//transmit_UART0('a');
		_delay_ms(1000);
    }
}

