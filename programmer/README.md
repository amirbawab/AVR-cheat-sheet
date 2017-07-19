## AVR Programmer

### Table of Contents
  * [Packages](#packages)
  * [Microcontroller](#microcontroller)
  * [Programmer](#programmer)
  * [Circuit](#circuit)
  * [Compile and upload](#compile-and-upload)
### Packages
#### Arch linux
* avr-binutils
* avr-gcc
* avr-libc
* avrdude

### Microcontroller
#### ATmega328p
<img src="https://raw.githubusercontent.com/amirbawab/AVR/master/programmer/images/atmega328p.jpg"/>  

### Programmer
#### Sparkfun Pocket AVR Programmer
The device was tested on Ubuntu 16.04 and Arch linux  
<img src="https://raw.githubusercontent.com/amirbawab/AVR/master/programmer/images/usbtiny-programmer.jpg"/>  

### Circuit
Components:
* 1x ATmega328p
* 1x Resistor 10K
* 1x Crystal 16Mhz
* 2x Capacitor 22pf
* 1x AVR Programmer
<img src="https://raw.githubusercontent.com/amirbawab/AVR/master/programmer/images/circuit.jpg"/>

For AVR Programming cable with 6 pins:
<img src="https://raw.githubusercontent.com/amirbawab/AVR/master/programmer/images/connections-6.jpg"/>  

For AVR Programming cable with 10 pins:
<img src="https://raw.githubusercontent.com/amirbawab/AVR/master/programmer/images/connections-10.jpg"/>  

### Compile and upload
To compile your C program and upload the generated hex to the ATmega328p, use the <a href="script/ATmega328-upload.sh">ATmega328-upload.sh</a> file as follow:
```
DEVICE="usbtiny" # For Pocket AVR Programer
DEVICE="usbasp"  # For USBASP USBISP AVR Programmer
sudo ./script/upload.sh ${DEVICE} /path/to/program.c
```

### Resources
* https://www.sparkfun.com/
* https://aaroneiche.com/2016/11/06/programming-avrs-using-a-usbasp-on-a-mac/
