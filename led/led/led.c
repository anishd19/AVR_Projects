/*
 * led.c
 *
 * Created: 05-11-2013 12:10:54
 *  Author: anish
 */ 


#include <avr/io.h>
#include <util/delay.h>
//#include <anishlib/tools.h>
int main(void)
{
	
	DDRB |= 1<<PINB0;		//LED 1
	PORTB ^= 1<<PINB0;		// Toggle LED 1 pin
	DDRD |= 1<<PIND7;		// LED 2
	DDRB &= ~(1<<PINB1);	// Button
	PORTB |= 1<<PINB1;		// Button hign by default
	
	int Pressed = 0;
	
    while(1)
    {
    
		if (bit_is_clear(PINB, 1))
		{
			if (Pressed == 0)
			{
				PORTB ^= 1<<PINB0;
				PORTD ^= 1<<PIND7;
				Pressed = 1;
			}
		}
		else
		{
			Pressed = 0;
		}
	
	}
}