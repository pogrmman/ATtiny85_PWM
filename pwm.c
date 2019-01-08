#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
int main() {
  // Set pin 4 to output
  DDRB = (1<<DDB4);

  // Set up PWM
  OCR1A = 0;
  GTCCR = (1<<PWM1A);
  GTCCR |= ((1<<COM1A1)|(1<<COM1A0));


  while(1) {
    OCR1A = 255;
    _delay_ms(250);
    OCR1A = 128;
    _delay_ms(250);
    OCR1A = 64;
    _delay_ms(250);
    OCR1A = 0;
    _delay_ms(250);
  }

  return 0;
}
