# External interrupts using PCINTx

The following examples demonstrate how to use a switch on PCINT1. The goal of the examples is to toggle an LED on each button press. Changing to another PCINTx follows the same logic as described below. Refer to the cheat sheet for further details.

## Example 1
* Blink LED on each button press
* Bouncing problem 

### Compile and upload
```
avr-gcc -std=c11 -mmcu=atmega328 -O -o example1.o example1.c
avr-objcopy -O ihex example1.o example1.hex
avrdude -c usbasp -p m328p -U flash:w:example1.hex
```
## Example 2
* Blink LED on each button press
* A simple debouncing solution (not the best)

### Compile and upload
```
avr-gcc -std=c11 -mmcu=atmega328 -O -o example2.o example2.c
avr-objcopy -O ihex example2.o example2.hex
avrdude -c usbasp -p m328p -U flash:w:example2.hex
```

## Example 3
* Blink LED on each button press
* Bouncing problem 
* Check which pin triggered the interrupt (not very accurate)

### Compile and upload
```
avr-gcc -std=c11 -mmcu=atmega328 -O -o example3.o example3.c
avr-objcopy -O ihex example3.o example3.hex
avrdude -c usbasp -p m328p -U flash:w:example3.hex
```

### Circuit
<img src="../../../images/circuit-pcintx.jpg">
