/*
 * Final_Power.c
 *
 * Created: 11/4/2017 7:22:58 PM
 * Author : mr_natawarlal
 */ 

#include <avr/io.h>
#include "avr/interrupt.h"
#include "TWI_slave.h"
#include "common.h"
#include "uart.h"
uint8_t command;
uint8_t jam=5;
uint8_t HM_data[8];
ISR(INT0_vect)
{
	for (int i=0;i<60;i++)
	{
		_delay_ms(1000);
		transmit_UART(i);
	}
	GICR&=~(1<<INT0);
}
//-----------------slave receiver----------------------------//
//unsigned char msg_buf[8]={'9','9','9','9','9','9','9','9'};
//msg_buf[0]='9';
uint8_t ADC_Convert(uint8_t i)// ADC Initialization and Conversion combined in one function
{	switch(i)
	{case 1: ADMUX = 0x61; // v1- Battery Voltage by 3
		ADCSRA = 0xC5;
		_delay_ms(10);
		while (ADCSRA & (1<<ADSC));
		return ADCH;
		break;
		
		case 2:	ADMUX = 0x63;//v3 - OBC Voltage by 2
		ADCSRA = 0xC5;
		_delay_ms(10);
		while (ADCSRA & (1<<ADSC));
		return ADCH;
		break;
		
		case 3: ADMUX = 0x64;//v2 - Downlink voltage by 2
		ADCSRA = 0xC5;
		_delay_ms(10);
		while (ADCSRA & (1<<ADSC));
		return ADCH;
		break;
		
		case 4: ADMUX = 0x60;//i1 - Panel current
		ADCSRA = 0xC5;
		_delay_ms(10);
		while (ADCSRA & (1<<ADSC));
		return ADCH;
		break;
		
		case 5: ADMUX = 0x62;//i2 - Consumption Current
		ADCSRA = 0xC5;
		_delay_ms(10);
		while (ADCSRA & (1<<ADSC));
		return ADCH;
		transmit_UART('1');
		break;
	default: break;}
}
void Startup_all(){

	PORTA|=0b00000000;
	PORTB|=0b00001110;
	PORTC|=0b11000100;
	PORTD|=0b00010000;
	HM_data[0]|=0xFE;
}
void Stop_all()
{
	PORTA|=0b11000000;
	PORTB|=0b00001110;
	PORTC|=0b11000100;
	PORTD|=0b11010000;
	HM_data[0]|=0x00;
}
void Startup(uint8_t command)
{
	if((command & 0x80) == 0x80)
	{PORTB |= (1<<PINB0);//Beacon
	HM_data[0] |= 0x80;}
	else {PORTB &= (0<<PINB0);//Beacon
		HM_data[0] &= 0x7E;
	}
	if((command & 0x40) == 0x40)
	{PORTB |= (1<<PINB2);//Downlink
	HM_data[0] |= 0x40;}
	else{PORTB &= (0<<PINB2);//Downlink
	HM_data[0] &=0xBE;}
	if((command & 0x20)== 0x20)
	{PORTD &= (0<<PIND7);//Torquer
	HM_data[0] |= 0x20;}
	else{
			PORTD |= (1<<PIND7);//Torquer
			HM_data[0] &= 0xDE;
	}
	if((command & 0x10) == 0x10)
	{PORTA &= (0<<PINA7);//OBC
	HM_data[0] |= 0x10;}
	else {PORTA |= (1<<PINA7);//OBC
		HM_data[0] &= 0xEE;}
	if((command & 0x08) == 0x08)
	{PORTA &= (0<<PINA6);//GPS
	HM_data[0] |= 0x08;}
	else {PORTA |= (1<<PINA6);//GPS
		HM_data[0] &= 0xF6;}
	if((command & 0x04) == 0x04)
	{PORTB |= (1<<PINB3);//Magmeter
	HM_data[0] |= 0x04;}
	else {PORTB &= (0<<PINB3); //Magmeter
		HM_data[0] &= 0xFA;}
	if((command & 0x02) == 0x02)
	{PORTC &= (0<<PINC6); //REG 5v
	HM_data[0] |= 0x02;}
	else {PORTC |= (1<<PINC6); //REG 5v
		HM_data[0] &= 0xFC;}
	if(command == 0xFE)
Startup_all();
	else if((~command) == 0xFE)
	Stop_all();
}

/*	void Stop(uint8_t command)
{	if(((~command) & 0x80) == 0x80)
	{PORTB &= (0<<PINB0);//Beacon
		HM_data[0] &= 0x7E;
	}
	if(((~command) & 0x40) == 0x40)
	{PORTB &= (0<<PINB2);//Downlink
		HM_data[0] &=0xBE;
		transmit_UART(jam);
	}
	if(((~command) & 0x20) == 0x20){
		PORTD |= (1<<PIND7);//Torquer
		HM_data[0] &= 0xDE;
	}
	if(((~command) & 0x10) == 0x10)
	{	PORTA |= (1<<PINA7);//OBC
		HM_data[0] &= 0xEE;
		transmit_UART(jam);}
	if(((~command) & 0x08) == 0x08)
	{PORTA |= (1<<PINA6);//GPS
		HM_data[0] &= 0xF6;
	}
	if(((~command) & 0x04) == 0x04)
	{PORTB &= (0<<PINB3); //Magmeter
		HM_data[0] &= 0xFA;
		transmit_UART(jam);
	}
	if(((~command) & 0x02) == 0x02)
	{
		PORTC |= (1<<PINC6); //REG 5v
		HM_data[0] &= 0xFC;
		transmit_UART(jam);
	}
	if((~command) == 0xFE)
	Stop_all();
}*/

void Safe_Mode_on() {
	PORTB |= (1<<PINB0);//Beacon
	PORTC &= (0<<PINC6); //REG 5v
	HM_data[0]=0x82;
}
void Emergency_Mode_off() {
	PORTB &= (0<<PINB2);	//Downlink
	PORTD &= (0<<PIND7);	//Torquer
	PORTB &= (0<<PINB3);	//MagMeter
	PORTA &= (0<<PINA6);	//GPS
	PORTA &= (0<<PINA7);	//OBC
	HM_data[0]=0x82;
}
void Safe_Mode_off() {
	PORTB &= (0<<PINB0);	//Beacon
	PORTC |= (1<<PINC6); //REG 5v
	HM_data[0]=0x00;
}
int main(void)
{	DDRA=0b11000000;
	DDRB=0b00001110;
	DDRC=0b11000100;
	DDRD=0b11010000;
	init_UART();
	GICR = (1<<INT0);
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	MCUCR = 0xA0;//Power down mode of sleep
	
	sei();
	
	sleep_enable();
	sleep_mode();
	sleep_disable();
	_delay_ms(100);
	GICR&=~(1<<INT0);
    Startup_all();
	//msg_buf[0] ='9';
	//unsigned char HM_data[7];
	uint8_t msg_buf[8];
	unsigned char SLA=0x20;

	TWI_Slave_Initialise(SLA);
	
	TWI_Start_Transceiver_With_Data(msg_buf,1);
    while (1) 
    {
		
		uint8_t z = TWI_Get_Data_From_Transceiver(msg_buf , 1);//sr
		transmit_UART(msg_buf[0]);//sr
		//TWI_Start_Transceiver_With_Data(HM_data,1);
		_delay_ms(500);//sr
		for (uint8_t i=1;i<6;i++)
		{
			HM_data[i]=ADC_Convert(i);
		}
		if(1){HM_data[6]=0x00;
		HM_data[6]|=(PINB1<<7)|(PIND3<<6)|(PIND5<<5)|(PINC3<<4)|((~PINC4)<<3);}
		for (int i=0;i<8;i++)
		{transmit_UART(HM_data[i]);
		 transmit_UART(i);}
		command=msg_buf[0];
		transmit_UART(HM_data[0]);
		Startup(command);
		transmit_UART(HM_data[0]);
		_delay_ms(500);
		}
}

