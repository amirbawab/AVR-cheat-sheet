## Using internal clock source

The goal of this example is to demonstrate how the clock can be configured to run at various frequencies.  

*Note: The commands used to compile and upload to the chip are common for different AVR, however the switch values and flags in this example are specific for the ATmega328p. Please refer to the cheat sheet for further details.*

### Example 1
* Internal clock source: 8Mhz
* CKDIV8: 0 (programmed)
* Clock speed = 8Mhz / 8 = 1Mhz
* Every 1 million cycle is 1 second

Compile and upload:
```
# Compile
avr-gcc -std=c11 -mmcu=atmega328 -O -o example1.o example1.c

# Generate hex
avr-objcopy -O ihex example1.o example1.hex

# Upload hex and configure fuse bits to default for the ATmega328p (don't use the values below if you have another chip)
# The fuse bits don't need to be configured everytime, therefore the next time the following avrdude command is executed, all the -Ulfuse, -Uhfuse and -Uefuse can be omitted unless you want to make new changes.
# To learn how to generate the fuse byte values check to the cheat sheet.
avrdude -c usbasp -p m328p -U flash:w:example1.hex -Ulfuse:w:0x62:m -Uhfuse:w:0xd9:m -Uefuse:w:0xff:m
```

### Example 2
* Internal clock source: 8Mhz
* CKDIV8: 1 (unprogrammed)
* Clock speed = 8Mhz
* Every 8 million cycle is 1 second

Compile and upload:
```
avr-gcc -std=c11 -mmcu=atmega328 -O -o example2.o example2.c
avr-objcopy -O ihex example2.o example2.hex
avrdude -c usbasp -p m328p -U flash:w:example2.hex -Ulfuse:w:0xe2:m -Uhfuse:w:0xd9:m -Uefuse:w:0xff:m
```
### Example 3
* Internal clock source: 8Mhz
* CKDIV8: 1 (unprogrammed)
* Clock speed = 8Mhz
* Set the `F_CPU` to 16000000UL
* Every 1 second delay in the program becomes 2 seconds in reality
* Avoid doing this, the clock might lose its accuracy

Compile and upload:
```
avr-gcc -std=c11 -mmcu=atmega328 -O -o example3.o example3.c
avr-objcopy -O ihex example3.o example3.hex
avrdude -c usbasp -p m328p -U flash:w:example3.hex -Ulfuse:w:0xe2:m -Uhfuse:w:0xd9:m -Uefuse:w:0xff:m
```

### Circuit

#### Components
* 1x LED
* 1x Resistor 330 ohm for the LED
* 1x Resistor 10K for the ATmega328p
* 1x AVR microcontroller
* 1x AVR programmer

<img src="../../../images/circuit-int-clock-led.jpg">
