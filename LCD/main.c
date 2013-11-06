#include <avr/io.h>
#include <util/delay.h>

#define MrLCDsCrib 				PORTB		//Data Pins
#define DataDir_MrLCDsCrib		DDRB
#define MrLCDsControl 			PORTD		//Control Ports	//Always op
#define DataDir_MrLCDsControl	DDRD

#define LightSwitch 	5			//Enable		
#define ReadWrite 		7			//R/W			
#define BiPolarMood		2			//RS

void Check_if_MRLCD_isBusy(void);
void Peek_A_Boo(void);
void Send_A_Command(unsigned char command);
void Send_A_Character(unsigned char character);

int main(void)
{
	DataDir_MrLCDsControl |= 1<<LightSwitch | 1<<ReadWrite | 1<<BiPolarMood;
	_delay_ms(15);				//wait for LCD to get fully ON
	
	
	Send_A_Command(0x01);		//Clear Screen
	_delay_ms(2);				//time taken to clear
	Send_A_Command(0b00000010);	//Cursor Return
	_delay_ms(2);				//time taken to clear
	Send_A_Command(0x38);		//8 bit mode
	_delay_us(50);
	Send_A_Command(0b00001111);	//control cursor, display on/off
	//Send_A_Command(0b
	
	Send_A_Character(0x41); 	//A
	Send_A_Character(0x4E);		//N
	Send_A_Character(0x49);		//I
	Send_A_Character(0x53);		//S
	Send_A_Character(0x48);		//H
	Send_A_Character(0x20);		//space
	Send_A_Character(0x41);		//A
	Send_A_Character(0x56);		//V
	Send_A_Character(0x41);		//A
	Send_A_Character(0x4E);		//N
	Send_A_Character(0x41);		//A
	Send_A_Character(0x20);		//space
	Send_A_Character(0x21);
	Send_A_Character(0x21);
	/*
	Send_A_Character(0x41); 	//A
	Send_A_Character(0x4E);		//N
	Send_A_Character(0x49);		//I
	Send_A_Character(0x53);		//S
	Send_A_Character(0x48);		//H
	Send_A_Character(0x20);		//space
	Send_A_Character(0x41);		//A
	Send_A_Character(0x56);		//V
	Send_A_Character(0x41);		//A
	Send_A_Character(0x4E);		//N
	Send_A_Character(0x41);		//A
	Send_A_Character(0x20);		//space
	*/
	
	while(1)
	{
	}
}

void Check_if_MRLCD_isBusy()
{
	DataDir_MrLCDsCrib = 0;		//ip DDRB
	MrLCDsControl |= 1<<ReadWrite;
	MrLCDsControl &= ~1<<BiPolarMood;	//command mode
	
	while(MrLCDsCrib >= 0x80) //D7 on PORTB Pin7 will be 1 when busy else 0
	{
		Peek_A_Boo();	// Every time MrLCD populates the crib with busy info, when in read mode
	}
	
	
	DataDir_MrLCDsCrib = 0xFF; // op
}

void Peek_A_Boo()
{
	MrLCDsControl |= 1<<LightSwitch; // Enable on
	asm volatile("nop");		// volatile means a dynamic statement, compiler will not optimize it out
	asm volatile("nop");
	MrLCDsControl &= ~1<<LightSwitch;
}

void Send_A_Command(unsigned char command)
{
	Check_if_MRLCD_isBusy();
	MrLCDsCrib = command;	//PORTB
	MrLCDsControl &= ~(1<<ReadWrite | 1<<BiPolarMood);	//RW off, RS cleared
	Peek_A_Boo();
	MrLCDsCrib = 0;
	
}

void Send_A_Character(unsigned char character)
{
	Check_if_MRLCD_isBusy(); 
	MrLCDsCrib = character;	//PORTB
	MrLCDsControl &= ~(1<<ReadWrite);	//RW off, RS cleared
	MrLCDsControl |= (1<<BiPolarMood);	//RS
	Peek_A_Boo();		//Enable Process
	MrLCDsCrib = 0;
}