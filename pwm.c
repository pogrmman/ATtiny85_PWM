#define F_CPU 1000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>

volatile int delayTime = 50;

// Change delay for ramping on interrupt
ISR(INT0_vect) {
	if(delayTime == 50) {
		delayTime = 1;
	} else {
		delayTime = 50;
	}
	
}

int main() {
  // Set pin 5 to output
  DDRB = (1<<PB0);

  // Set up PWM
  OCR0A = 0; // Duty cycle
  // Run it in normal mode, not inverted
  TCCR0A = ((1<<COM0A1)|(0<<COM0A0));
  // Fast PWM mode
  TCCR0A |= ((1<<WGM01)|(1<<WGM00));
  TCCR0B = (0<<WGM02);
  // Clock has 1/8 prescaler
  TCCR0B |= (1<<CS01);

	// Interrupt on pin change
	MCUCR = ((0<<ISC01)|(1<<ISC00));
	// Enable interrupts
	GIMSK = (1<<INT0);
	sei();
	
  int i;
	int delayTime_Local;
	while(1) {
    // Ramp up brightness
    for (i=0; i<256; ++i) {
      OCR0A = i;
			ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
				delayTime_Local = delayTime;
				_delay_ms(delayTime_Local);
			}
    }
    // Ramp down brightness
    for (i=255; i>0; --i) {
      OCR0A = i;
			ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
				delayTime_Local = delayTime;
				_delay_ms(delayTime_Local);
			}
    }
  }

  return 0;
}
