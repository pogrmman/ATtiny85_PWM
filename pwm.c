#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
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

  int i;
  while(1) {
    // Ramp up brightness
    for (i=0; i<256; ++i) {
      OCR0A = i;
      _delay_ms(20);
    }
    // Ramp down brightness
    for (i=255; i>0; --i) {
      OCR0A = i;
      _delay_ms(20);
    }
  }

  return 0;
}
