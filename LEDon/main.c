#include <avr/io.h>
#include <util/delay.h>

void ProcessPressedButton(int ButtonPressed);
void ProcessReleasedsButton(int ButtonReleased);

int Pressed_Confidence_Level[2];// equal to zero by default
int Released_Confidence_Level[2];
int Pressed[2];
int LEDNumber[2];

int main(void)
{
	//Initialization area. Setting up ports and data direction registors
	DDRB = 0b01111111;
	DDRD = 0b01111111;
	PORTB = 0b10000000;
	PORTD = 0b10000000;

	while (1)
	{
		if (bit_is_clear(PINB, 7))
		{
			//Lighting up LED on port B one at a time
			ProcessPressedButton(0);

		}
		else
		{
			//Making sure that the button on side 1 was released
			ProcessReleasedsButton(0);
		}
		if (bit_is_clear(PIND, 7))
		{
			//Lighting up LED on port D one at a time
			ProcessPressedButton(1);
		}
		else
		{
			//Making sure that the button on side 2 was released
			ProcessReleasedsButton(1);
		}
		//Process button clicks for side 1
		//Process button clicks for side 2		
	}
}

void ProcessPressedButton(int ButtonPressed)
{
	Pressed_Confidence_Level[ButtonPressed] ++;
	if (Pressed_Confidence_Level[ButtonPressed] > 500)
	{
		if (Pressed[ButtonPressed] == 0)
		{
			Pressed[ButtonPressed] = 1;
			
			if (ButtonPressed == 0)	PORTB |= 1<<LEDNumber[ButtonPressed];
			if (ButtonPressed == 1)	PORTD |= 1<<LEDNumber[ButtonPressed];
			LEDNumber[ButtonPressed] ++;
			if (LEDNumber[ButtonPressed] > 6)
			{
				//PORTB is winner and blink or do something else
				for(int i=0; i<10; i++)
				{
					if(ButtonPressed == 0) PORTB = 0b10000000;
					if(ButtonPressed == 1) PORTD = 0b10000000;
					_delay_ms(10);
					if(ButtonPressed == 0) PORTB = 0b11111111;
					if(ButtonPressed == 1) PORTD = 0b11111111;
					_delay_ms(10);
				}
				LEDNumber[0] = 0;
				LEDNumber[1] = 0;
				PORTB = 0b10000000;
				PORTD = 0b10000000;
			}
			
		}
		Pressed_Confidence_Level[ButtonPressed] = 0;
	}
}

void ProcessReleasedsButton(int ButtonReleased)
{
	Released_Confidence_Level[ButtonReleased] ++;
	if (Released_Confidence_Level[ButtonReleased] > 500)
	{
		Pressed[ButtonReleased] = 0;
		Released_Confidence_Level[ButtonReleased] = 0;
	}
}