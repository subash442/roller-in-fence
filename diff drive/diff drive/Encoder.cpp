/* 
* Encoder.cpp
*
* Created: 10/15/2017 5:57:05 PM
* Author: Subash Timilsina
*/


#include "Encoder.h"

void Encoder::Initialise()
{	
	if(no==1)
	{
		INPUT(ENCODER1_CHANNELA);
		INPUT(ENCODER1_CHANNELB);
		SET(ENCODER1_CHANNELA);
		SET(ENCODER1_CHANNELB);
	}
	else if(no==2)
	{
		INPUT(ENCODER2_CHANNELA);
		INPUT(ENCODER2_CHANNELB);
		SET(ENCODER2_CHANNELA);
		SET(ENCODER2_CHANNELB);
	}
	else if (no==3)
	{
		INPUT(ENCODER3_CHANNELA);
		INPUT(ENCODER3_CHANNELB);
		SET(ENCODER3_CHANNELA);
		SET(ENCODER3_CHANNELB);
	}
	else if(no==4)
	{
		INPUT(ENCODER4_CHANNELA);
		INPUT(ENCODER4_CHANNELB);
		SET(ENCODER4_CHANNELA);
		SET(ENCODER4_CHANNELB);
	}
	Init_Interrupts();
	Init_Timers();
}

void Encoder::Init_Interrupts()
{
	sei();
	if(no==1)
	{
		EIMSK &= ~(1<<ENCODER1_INT);
		EICRA |= (1<<INT1_ISC1);	//falling edge
		EIMSK |= (1<<ENCODER1_INT);		//setting INT pin
		EIFR |= (1<<INT1_INTF);	    //clear int flag
	}
	else if (no==2)
	{
		EIMSK &= ~(1<<ENCODER2_INT);
		EICRA |= (1<<INT2_ISC1);	//falling edge
		EIMSK |= (1<<ENCODER2_INT);		//setting INT pin
		EIFR |= (1<<INT2_INTF);	    //clear int flag
	}
	else if (no==3)
	{
		EIMSK &= ~(1<<ENCODER3_INT);
		EICRA |= (1<<INT3_ISC1);	//falling edge
		EIMSK |= (1<<ENCODER3_INT);		//setting INT pin
		EIFR |= (1<<INT3_INTF);	    //clear int flag
	}
	else if (no==4)
	{
		EIMSK &= ~(1<<ENCODER4_INT);
		EICRA |= (1<<INT4_ISC1);	//falling edge
		EIMSK |= (1<<ENCODER4_INT);		//setting INT pin
		EIFR |= (1<<INT4_INTF);	    //clear int flag
	}	
}

void Encoder::Init_Timers()
{
	TCCR1B |= ((1<<WGM12)|(1<<CS30)|(1<<CS31)); //CTC mode and prescaler of 64
	TIMSK1 |= (1<<OCIE1A);
	OCR1A  = (F_CPU/1000)*(DELAYTIMEMS/64.0);
	TCNT1 = 0;
}


void Encoder::Calc_Speed()				//keep in timer compare match
{
	enc_valbuff[0]=enc_valbuff[1];
	enc_valbuff[1]=enc_valbuff[2];
	enc_valbuff[2]=enc_valbuff[3];
	enc_valbuff[3] = pprcount;
	speed = (enc_valbuff[0]+enc_valbuff[1]+enc_valbuff[2]+enc_valbuff[3])>>2	;
	pprcount = 0;
}