/**
 * Vehicle Speed Sensor Buffer firmware
 * ATtiny25
 *
 * I don't have any flip-flops handy for prototyping
 * so I'm using an ATtiny25 to implement /2 & /4. The
 * Jeep Grand Wagoneer uses an 8 pulse/mile VSS but
 * the GM TBI I've installed needs a 2 pulse/mile
 * signal.
 *
 * Michael Shimniok - http://www.bot-thoughts.com
 */

#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

int main()
{
	// Initialize pins
	MCUCR &= ~(1<<PUD); // disable pull-ups
	DDRB |= (1<<PB3)|(1<<PB4);
	PORTB |= (1<<PB3)|(1<<PB4);

	// Set up INT0 pin interrupt on rising edge
	MCUCR |= (1<<ISC01)|(1<<ISC00);
	GIMSK |= (1<<INT0);

	sei();

	while (1) {
	}
}

// Interrupts on rising edge of VSS
// So toggling PB3 at each rising edge gives /2
// Also, when counting, toggle PB4 to give /4
ISR(INT0_vect) {
	static uint8_t count=0;

	PINB |= (1<<PB3); // Toggle the output pin
	if (count++ & 0x01) {
		PINB |= (1<<PB4);
	}
}
