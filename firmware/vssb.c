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

void disableWatchdog();
void enableWatchdog();

uint8_t count=0;

int main()
{
	// Initialize pins
	MCUCR &= ~(1<<PUD); // disable pull-ups
	PORTB = 0;
	PINB = 0;
	DDRB = (1<<PB4)|(1<<PB3);

	// Set up INT0 pin interrupt on rising edge
	MCUCR |= (1<<ISC01)|(1<<ISC00);
	GIMSK |= (1<<INT0);

	sei();

	while (1) {
		//set_sleep_mode(SLEEP_MODE_PWR_DOWN);
		//sleep_mode();
	}
}

// Interrupts on rising edge of VSS
// So toggling PB3 at each rising edge gives /2
// Also, when counting, toggle PB4 to give /4
ISR(INT0_vect) {
	PINB |= (1<<PB3); // Toggle the output pin
	if (count++ & 0x01) {
		PINB |= (1<<PB4);
	}
}


inline void disableWatchdog()
{
	// disable watchdog reset mode and interrupt mode
	WDTCR |= _BV(WDE) | _BV(WDCE);
	WDTCR &= ~_BV(WDE);
}

inline void enableWatchdog()
{
	// Enable watchdog interrupt, set prescaling to 1 sec
	WDTCR |= _BV(WDIE) | _BV(WDP2) | _BV(WDP1);
}

// 8MHz / 64 = 125000
void slowClock()
{
	CLKPR = _BV(CLKPCE); // enable change to clock prescaler
	CLKPR = _BV(CLKPS2) | _BV(CLKPS1); // scale = /64
}