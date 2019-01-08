#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
int main() {
  // Set pip 6 to output
  DDRB = (1<<DDB1);

  // Set up PWM
  // Run it in normal mode, not inverted
  TCCR0A = ((1<<COM0A1)|(0<<COM0A0));
  // Fast PWM mode
  TCCR0A |= ((1<<WGM01)|(1<<WGM00));
  TCCR0B = (0<<WGM02);

  while(1) {
    OCR0A = 255;
  }

  return 0;
}
