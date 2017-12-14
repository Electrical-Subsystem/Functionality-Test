/*
 * Final_OBC.c
 *
 * Created: 11/4/2017 7:25:55 PM
 * Author : mr_natarwarlal
 */ 

#include <avr/io.h>
#include "avr/interrupt.h"
#include "TWI_Master.h"
#include "common.h"
#include "uart.h"
//-------------master receiver-------------------------//

/*int main(void)
{
	sei();
	unsigned char HM_data[7];	
	unsigned char msg_buf[8];
	unsigned char SLA=0x20;
	
	TWI_Master_Initialise();
	init_UART0();
	
    while (1) 
    {
		
		msg_buf[0]=SLA+0x01;
		TWI_Start_Transceiver_With_Data(msg_buf,2);
		unsigned char z = TWI_Get_Data_From_Transceiver(msg_buf,2);
		_delay_ms(100);
		transmit_UART0(msg_buf[1]);
		
    }
}
*/
