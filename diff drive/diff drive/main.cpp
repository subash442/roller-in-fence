/*
 * diff drive.cpp
 *
 * Created: 11/17/2017 5:55:45 PM
 * Author : Subash Timilsina
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "Motor.h"
//#include "Encoder.h"


#define MOTOR_RPM	450.0	
//Encoder e1(1);

int main(void)
{
	sei();
	uart3_init(UART_BAUD_SELECT(9600,F_CPU));
	
	Motor m1,m2;
	//e1.Initialise();
	m1.Initialise(1);
	m2.Initialise(2);
	char ch;
	int speed = 50;
    while (1) 
    {
	ch = '0';	
	ch = uart3_getc();
	uart3_putc(ch);
	switch(ch)
	{
		case 'F':
		{
			m1.SetOcrValue(speed);
			m1.SetForwardDirection();
			m2.SetOcrValue(speed);
			
			m2.SetForwardDirection();
			break;
		}
		case 'B':
		{
			m1.SetOcrValue(speed);
			m1.SetReverseDirection();

			m2.SetOcrValue(speed);
			m2.SetReverseDirection();
			break;
		}
		case 'L':
		{
			speed += 10;
		}
		case 'R':
		{
			speed -= 10;
		}
		case 'S':
		{
			m1.StopMotor();
			m2.StopMotor();
			break;
		}
	}

	//if (e1.Get_count()>32760) e1.ovfcntppr++;
	//if (e1.Get_count()>-32760) e1.ovfcntppr--;
	//uart3_putint(e1.Get_count());
	//uart3_putc('\t');
	//uart3_putint(e1.ovfcntppr);
	//uart3_puts("\n\r");
			
    }
}

//
//ISR(INT_VECT1)
//{
	//if(bit_is_set(ENCODER1_CHAPORTPIN,ENCODER1_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	//{
		//e1.incCount();
	//}
	//else
	//e1.dcrCount();
//
//}

