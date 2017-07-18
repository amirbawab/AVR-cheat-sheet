## AVR Programmer

### Microcontroller
#### ATmega328p
<img src="https://raw.githubusercontent.com/amirbawab/AVR/master/programmer/images/atmega328p.jpg"/>  

### Device
#### Sparkfun Pocket AVR Programmer
The device was tested on Ubuntu 16.04 and Arch linux  
<img src="https://raw.githubusercontent.com/amirbawab/AVR/master/programmer/images/programmer.jpg"/>  

#### Circuit
Components:
* 1x ATmega328p
* 1x Resistor 10K
* 1x Crystal 16Mhz
* 2x Capacitor 22pf
* 1x Pocket AVR Programmer
<img src="https://raw.githubusercontent.com/amirbawab/AVR/master/programmer/images/circuit.jpg"/>

#### Programmer connections
Wire the programmer to the ATmega328p as follow:
<img src="https://raw.githubusercontent.com/amirbawab/AVR/master/programmer/images/connections.jpg"/>  

#### Compile C program and upload hex
To compile your C program and upload the generated hex to the ATmega328p, use the `upload.sh` file as follow:
```
sudo ./upload.sh /path/to/program.c
```

### Links
* https://www.sparkfun.com/
