## Using external clock source

The goal of this example is to demonstrate how the clock can be configured to run at various frequencies.  

*Note: The commands used to compile and upload to the chip are common for different AVR, however the switch values and flags in this example are specific for the ATmega328p. Please refer to the cheat sheet for further details.*

### Find the fuse byte values for the external crystal 16Mhz
*Note: For the ATmega328p, changing the clock source require only changing the low fuse byte. For other AVR microcontrollers, follow the idea explained below but refer to your datasheet for the exact information.*

*Note: Generating the fuse byte values can be done automatically from Eclipse. Check the cheat sheet for details.*

* The high fuse byte and the extended fuse byte will have their default values. Refer to the cheat sheet for more details.
* Open the datasheet at section "Fuse Bits"
  * Locate the "Fuse low byte" table
  * Write down on a paper the fuse bits names top-down (bit# 7...0)
    * CKDIV8 (both values 1 and 0 will be demonstrated in the following examples)
    * CKOUT = 1 (default value)
    * SUT1
    * SUT0
    * CKSEL3
    * CKSEL2
    * CKSEL1
    * CKSEL0
* Open the datasheet at section "Clock Sources"
  * Locate the "Device Clocking Options Selec" table
  * In this example, we will be using the "Full Swing Crystal Oscillator"
  * This option has a CKSEL3/2/1/0 fuse bits within the range of `0111-0110`
  * To know exactly which binary sequence to chose exaclty, we need to check the selected option section.
* Open the datasheet at section "Full Swing Crystal Oscillator"
  * Locate the "Full Swing Crystal Oscillator operating modes" table
    * This table has one option which tells us the crystal frequency range accepted and the values of the 2 capacitors attached to each end of the crystal. 
    * Write down the values:
      * CKSEL3 = 0
      * CKSEL2 = 1
      * CKSEL1 = 1
  * Locate the "Start-Up Times for the Full Swing Crystal Oscillator Clock Selection" table
    * This table has all the remaining fuse bits information needed
    * In this table the option "Crystal Oscillator, slowly rising power" is selected (let it take its time).
    *  Write down the values:
      * CKSEL0 = 1
      * SUT1 = 1
      * SUT0 = 1
* So the final fuse bits sequence is:
    * CKDIV8 = 1 / 0
    * CKOUT = 1 (default value)
    * SUT1 = 1
    * SUT0 = 1
    * CKSEL3 = 0
    * CKSEL2 = 1
    * CKSEL1 = 1
    * CKSEL0 = 1
  * With CKDIV8 programmed:
    * 01110111 = 0x77
  * With CKDIV9 unprogrammed:
    * 11110111 = 0xf7

### Example 1
* External clock source: 16Mhz
* CKDIV8: 0 (programmed)
* Clock speed = 16Mhz / 8 = 2Mhz
* Every 2 million cycle is 1 second

Compile and upload:
```
# Compile
avr-gcc -std=c11 -mmcu=atmega328 -O -o example1.o example1.c

# Generate hex
avr-objcopy -O ihex example1.o example1.hex

# Upload hex and configure fuse bits to use the external 16Mhz crystal oscillator (don't use the values below if you have another chip)
# The fuse bits don't need to be configured everytime, therefore the next time the following avrdude command is executed, all the -Ulfuse, -Uhfuse and -Uefuse can be omitted unless you want to make new changes.
# To learn how to generate the fuse byte values check to the cheat sheet.
avrdude -c usbasp -p m328p -U flash:w:example1.hex -Ulfuse:w:0x77:m -Uhfuse:w:0xd9:m -Uefuse:w:0xff:m
```

### Example 2
* Internal clock source: 16Mhz
* CKDIV8: 1 (unprogrammed)
* Clock speed = 16Mhz
* Every 16 million cycle is 1 second

Compile and upload:
```
avr-gcc -std=c11 -mmcu=atmega328 -O -o example2.o example2.c
avr-objcopy -O ihex example2.o example2.hex
avrdude -c usbasp -p m328p -U flash:w:example2.hex -Ulfuse:w:0xf7:m -Uhfuse:w:0xd9:m -Uefuse:w:0xff:m
```
### Example 3
* Internal clock source: 16Mhz
* CKDIV8: 1 (unprogrammed)
* Clock speed = 16Mhz
* Set the `F_CPU` to 32000000UL
* Every 1 second delay in the program becomes 2 seconds in reality
* Not recommened

Compile and upload:
```
avr-gcc -std=c11 -mmcu=atmega328 -O -o example3.o example3.c
avr-objcopy -O ihex example3.o example3.hex
avrdude -c usbasp -p m328p -U flash:w:example3.hex -Ulfuse:w:0xf7:m -Uhfuse:w:0xd9:m -Uefuse:w:0xff:m
```

### Circuit

#### Components
* 1x LED
* 1x Resistor 330 ohm for the LED
* 1x Resistor 10K for the ATmega328p
* 1x AVR microcontroller
* 1x AVR programmer
* 1x Crystal oscillator 16Mhz
* 2x Capacitors 22pf

<img src="../../../images/circuit-ext-clock-led.jpg">
