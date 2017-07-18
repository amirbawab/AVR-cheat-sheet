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
<img src="https://raw.githubusercontent.com/amirbawab/AVR/master/programmer/images/programmer.jpg"/>  

### Circuit
Components:
* 1x ATmega328p
* 1x Resistor 10K
* 1x Crystal 16Mhz
* 2x Capacitor 22pf
* 1x Pocket AVR Programmer
<img src="https://raw.githubusercontent.com/amirbawab/AVR/master/programmer/images/circuit.jpg"/>
<img src="https://raw.githubusercontent.com/amirbawab/AVR/master/programmer/images/connections.jpg"/>  

### Compile and upload
To compile your C program and upload the generated hex to the ATmega328p, use the <a href="script/upload.sh">upload.sh</a> file as follow:
```
sudo ./script/upload.sh /path/to/program.c
```

### Links
* https://www.sparkfun.com/
