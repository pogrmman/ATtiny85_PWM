#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
int main() {
  // Set pin 5 to output
  DDRB = (1<<PB0);

  // Set up PWM
  OCR0A = 20; // Duty cycle
  // Run it in normal mode, not inverted
  TCCR0A = ((1<<COM0A1)|(0<<COM0A0));
  // Fast PWM mode
  TCCR0A |= ((1<<WGM01)|(1<<WGM00));
  TCCR0B = (0<<WGM02);
  // Clock has 1/8 prescaler
  TCCR0B |= (1<<CS01);
  
  while(1) {
    ;
  }

  return 0;
}
