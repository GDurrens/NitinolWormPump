//
//
// NitinolDriver.c
//
// Dual Nitinol driver 
//
// Gregoire Durrens
// 05/03/2016
//
// based on the hello.RGB.45.c board of
// Neil Gershenfeld
// 11/10/10
//
// (c) Massachusetts Institute of Technology 2010
// This work may be reproduced, modified, distributed,
// performed, and displayed for any purpose. Copyright is
// retained and must be preserved. The work is provided
// as is; no warranty is provided, and users accept all 
// liability.
//

#include <avr/io.h>
#include <util/delay.h>

#define output(directions,pin) (directions |= pin) // set port direction for output
#define input(directions,pin) (directions &= (~pin)) // set port direction for input
#define set(port,pin) (port |= pin) // set port pin
#define clear(port,pin) (port &= (~pin)) // clear port pin
#define pin_test(pins,pin) (pins & pin) // test for port pin
#define bit_test(byte,bit) (byte & (1 << bit)) // test for bit set
#define PWM_delay() _delay_us(77) // PWM delay
#define delay_ms(time_ms) _delay_ms(time_ms) // delay


#define output_port PORTB
#define output_direction DDRB
#define Nitinol1 (1 << PB3)
#define Nitinol2 (1 << PB4)

#define input_port PORTB
#define input_direction DDRB
#define input_pins PINB
#define button (1 << PB2)

int main(void) {
   //
   // main
   //
   
	// variables that won't change
	unsigned char count, pwm, intensity = 255;


   //
   // set clock divider to /1
   //
   CLKPR = (1 << CLKPCE);
   CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);

   //
   // initialize LED pins
   //
   clear(output_port, Nitinol1);
   output(output_direction, Nitinol1);
   clear(output_port, Nitinol2);
   output(output_direction, Nitinol2);   
   input(input_direction, button);

   //
   // main loop
   //
   while (1) {	
      //
      // NITINOL1 ON  
      //
		for (count = 0; count<255 ;++count) {
			clear(output_port,Nitinol1);
			for (pwm = intensity; pwm < 255; ++pwm)      	
            PWM_delay();
         set(output_port,Nitinol1);
			for (pwm = 0; pwm < intensity; ++pwm)      	
            PWM_delay();
		}

		//
      // NITINOL1 COOLING OFF for 5s
      //

		clear(output_port,Nitinol1);
		delay_ms(5000);

		//
      // NITINOL2 ON  
      //
		for (count = 0; count<255 ;++count) {
			clear(output_port,Nitinol2);
			for (pwm = intensity; pwm < 255; ++pwm)      	
            PWM_delay();
         set(output_port,Nitinol2);
			for (pwm = 0; pwm < intensity; ++pwm)      	
            PWM_delay();
		}

		//
      // NITINOL2 COOLING OFF for 5s
      //

		clear(output_port,Nitinol2);
		delay_ms(5000);
	}
}
