/*
 * Distance_Measuring.c
 *
 * Created: 10/4/2023 1:47:47 PM
 *  Author: mahmo
 */ 


#include <avr/io.h>
#include "DIO.h"
#include "LCD.h"
#define F_CPU 1000000UL
#include <avr/delay.h>

int main(void)
{
	unsigned long a,b,high;
	unsigned long distance;
	LCD_Init();
	DIO_setPINdir('d',7,1);

	
    while(1)
    {
	
		TCCR1A = 0;
	
		TIFR = (1<<ICF1);
		DIO_writePIN('d',7,1);
		_delay_us(50);
		DIO_writePIN('d',7,0);
	
		TCCR1B = 0xC1;
		while(TIFR&(1<<ICF1)==0);
		a = ICR1;
		TIFR = (1<<ICF1);
	
		TCCR1B = 0x81;
		while(TIFR&(1<<ICF1)==0);
		b = ICR1;
		TIFR = (1<<ICF1);
		TCNT1 = 0;
		TCCR1B = 0;
	
		high = b-a;
		distance = (34600*high)/(F_CPU*2ul);
	
		if (distance>=80)
		{
			LCD_clear_screen();
			LCD_send_string("Out of range");
			_delay_ms(500);
		}
		else
		{
			LCD_clear_screen();
			LCD_send_string("distance=");
			LCD_sendChar((distance/10)+48);
			LCD_sendChar((distance%10)+48);
			LCD_send_string("cm");
			_delay_ms(500);
		}		
	}
}