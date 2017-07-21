## Erase bootloader

### Components
* 1x AVR microcontroller
* 1x Resistor 10K ohm
* 1x Crystal oscillator 16Mhz
* 2x Capacitors 22pf
* 1x AVR programmer

*Note: Some online tutorials show that the bootloader can be installed without using an external crystal oscillator. If that applies to your AVR, then the circuit can stay the same but the crystal oscillator with the capacitors will not be used during the erase process.*

#### Circuit
<img src="../../../images/erase-bootloader.jpg">

*Note: Check the cheat sheet to learn about the wiring between the AVR and the programmer.*

### AVRDUDE
Use the blink program in the <a href="../../basic/LED/">LED</a> directory to overwrite the software installed on the chip.

*Note: This example is for the ATmega328p. Check the cheat sheet for details about other AVR.*

*Info: This can be done using eclipse as well. More details in the cheat sheet.*

*Note: Fuse bits will be reset to default values. More details about the fuse bits in the cheat sheet.*

```
# Compile C program
avr-gcc -std=c11 -mmcu=atmega328 -O -o blink.o blink.c

# Generate hex file
avr-objcopy -O ihex blink.o blink.hex

# [Optional] Read fuse bytes to know if the external crystal oscillator is useful in the circuit
avrdude -c usbasp -p m328p -U lfuse:r:-:h -U hfuse:r:-:h -U efuse:r:-:h

# Upload hex file to the ATmega328p and reset fuse bits to default values
avrdude -pm328p -cusbasp -Uflash:w:blink.hex:a -Ulfuse:w:0x62:m -Uhfuse:w:0xd9:m -Uefuse:w:0xff:m

```
