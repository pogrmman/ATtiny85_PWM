##### Converting to Hex #####
pwm.hex: pwm.out
	avr-objcopy -R .eeprom -O ihex pwm.out pwm.hex
	avr-size pwm.out

##### Linking File #####
pwm.out: pwm.o
	avr-gcc -mmcu=attiny85 -o pwm.out -Wl,-Map,pwm.map pwm.o

##### Compiling #####
pwm.o: pwm.c
	avr-gcc -mmcu=attiny85 -Wall -Os -c pwm.c -std=c99

##### Installing #####
load: pwm.hex
	avrdude -p t85 -c usbtiny -e -U flash:w:pwm.hex -v
