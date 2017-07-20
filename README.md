# AVR Cheat Sheet 

*The Following Cheat Sheet is built based on the ATmega328p, but other AVR microcontroller should follow similar steps.*

### Table of Contents
* [Datasheet](#datasheet)
* [Packages](#packages)
  * [Arch linux](#arch-linux)
* [Microcontroller](microcontroller)
  * [ATmega328p](#atmega328p)
* [Programmer](#programmer)
  * [Sparkfun Pocket AVR Programmer](#sparkfun-pocket-avr-programmer)
  * [USBASP USBISP AVR Programmer](#usbasp-usbisp-avr-programmer)
  * [Programmer circuit](#programmer-circuit)
* [Eclipse](#eclipse)
  * [Installation](#installation)
  * [Create a new project](#create-a-new-project)
  * [Configure project](#configure-project)
  * [Build and upload from Eclipse](#build-and-upload-from-eclipse)
  * [Build and upload manually](#build-and-upload-manually)
* [Input/Output](#inputoutput)
  * [Introduction](#introduction)
  * [DDRx](#ddrx)
  * [PORTx](#portx)
  * [PINx](#pinx)
* [Contributing](#contributing)
* [Resources](#resources)

### Datasheet
#### ATmega328p
PDF from <a href="http://www.atmel.com/Images/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf">Atmel</a>

### Packages
#### Arch linux
* avr-binutils
* avr-gcc
* avr-libc
* avrdude

### Microcontroller
#### ATmega328p
<img src="images/atmega328p.jpg"/>  

### Programmer
#### Sparkfun Pocket AVR Programmer
The device was tested on Ubuntu 16.04 and Arch linux  
<img width="300" src="images/usbtiny-programmer.jpg"/>  

#### USBASP USBISP AVR Programmer
The device was tested on Arch linux  
<img width="300" src="images/usbasp-programmer.jpg"/>

#### Programmer circuit
Components:
* 1x ATmega328p
* 1x Resistor 10K ohm
* 1x Crystal 16Mhz (needed for microcontrollers programs that use external oscillator. e.g Bootloader)
* 2x Capacitor 22pf
* 1x AVR Programmer
<img src="images/circuit.jpg"/>

For AVR Programming cable with 6 pins:  
<img width="300" src="images/connections-6.jpg"/>  

For AVR Programming cable with 10 pins:  
<img width="300" src="images/connections-10.jpg"/>  

### Eclipse
#### Installation
* Install Eclipse C/C++
* Install plugin:
  * From Eclipse, go to **Help** > **Eclipse Marketplace**
  * Search for and install **AVR Eclipse Plugin**

#### Create a new project
* Create a new C Project
  * Select **AVR Cross Target Application** > **Empty Project** as project type
  * Select **AVR-GCC Toolchain** in the Toolchains box
* Press **Finish**

#### Configure project
* In **Project Explorer** select the AVR project
* Go to **Project** > **Properties**
* Expand **C/C++ Build** then select **Settings**
  * Check the **Generate HEX file for Flash memory**
* Expand **AVR** then select **AVRDude**
  * From the **Programmer** tab
    * Create a new programmer configuration
    * Give this configuration a name (Sparkfun Pocket AVR Programmer, USBASP USBISP AVR Programmer, etc...)
    * From the **Programmer Hardware**:
      * Select **USBasp** if you have the "USBASP USBISP AVR Programmer"
      * Select **USBtiny** if you have the "SparkFun Pocket AVR Programmer"
      * If you have something else then select the corresponding value
      * The option selected will be the value for the `-c` flag in the `avrdude` command
  * From the **Flash/EEPROM** tab
    * Make sure **Upload Flash Memory Image** is **from build**
* From the expanded **AVR**, select **Target Hardware**
  * Select **ATmega328p** as **MCU type**. If you are programming another AVR micrcontroller, then select the corresponding one.
* Done! Click on **Apply and Close**

Note that we did not explicitly tell **avr-gcc** to include ATMega328p header files using the -I flag, nor to link the correct libraries using -l flag. However, we did mention in the configuration that the target hardware is an ATMega328p which will add the -mmcu=atmega328p to the avr-gcc command and use the corresponding files. 

For instance, consider some IO functionality is required in the C program written for the ATmega328p. To use those functionalities, the <avr/io.h> header file should be included. Using the -mmcu switch the compiler will directly know that the file meant to be loaded is in fact <avr/iom328p.h> by preprocessing the macros in <avr/io.h>. 

> #include <avr/io.h>  
> This header file includes the apropriate IO definitions for the device that has been specified by the -mmcu= compiler command-line switch. This is done by diverting to the appropriate file <avr/ioXXXX.h> which should never be included directly. Some register names common to all AVR devices are defined directly within <avr/common.h>, which is included in <avr/io.h>, but most of the details come from the respective include file.

From: http://www.atmel.com/webdoc/avrlibcreferencemanual/group__avr__io.html

#### Build and upload from Eclipse
* Write a small C program for your AVR microntroller
* Build the project
* Do the required wiring between the AVR microcontroller and the programmer (check the prgorammer section for more details)
* Plug the programmer into your machine
* Go to **AVR** > **Upload Project to Target Device**

#### Build and upload manually
* Write a small C program for your AVR microcontroller
* Generate object file: `avr-gcc -std=c11 -mmcu=atmega328 -O -o avr.o avr.c`
  * Select the correct `-mmcu` switch value for your AVR microcontroller
* Generate hex file: `avr-objcopy -O ihex avr.o avr.hex`
* Upload hex to the AVR microcontroller: `avrdude -c usbasp -p m328p -U flash:w:avr.hex`
  * Select the `-c` value depending on which AVR programmer device your are using.
    * Use `usbtiny` for the SparkFun Pocket AVR Programmer
    * Use `usbasp` for the USBASP USBISP AVR Programmer
    * Or if you have another AVR Programmer select the correct value
  * Select the `-p` value depending on which AVR microcontroller is used

Use <a href="script/ATmega328-upload.sh">ATmega328-upload.sh</a> script file to buid a C program and upload its hex to the ATmega328p (The script file uses the commands described above). 

### Input/Output
#### Introduction
Each Input/Output pin on the AVR microcontroller belong to a Port alphabet (e.g. Pin 28 on the ATmega328p belongs to Port C). Each of those pins has three register bits assigned to them: DDxn in DDRx, PORTxn in PORTx and PINxn in PINx.

Source: [Datasheet](#datasheet) § 18.2.1. Configuring the Pin

DDRx, PORTx and PINx registers consist of one byte each, allowing at most 8 physical pins to be configured per alphabet letter. 

#### DDRx
```
+------+------+------+------+------+------+------+------+
| DDx7 | DDx6 | DDx5 | DDx4 | DDx3 | DDx2 | DDx1 | DDx0 |
+------+------+------+------+------+------+------+------+
```
Data Direction Register x allows specifying the direction of the I/O pins belonging to the Port x.  
If the bit 1 was written to DDx0, then Px0 direction is "output". If the bit 0 was written, then Px0 direction is "input".

#### PORTx
```
+--------+--------+--------+--------+--------+--------+--------+--------+
| PORTx7 | PORTx6 | PORTx5 | PORTx4 | PORTx3 | PORTx2 | PORTx1 | PORTx0 |
+--------+--------+--------+--------+--------+--------+--------+--------+
```
Port x register has two functionalities depending on the Data Direction Register x bits values.  
If DDx0 is set to "input", then writing 1 at PORTx0 activates the pull-up resistor at Px0, and writing 0 deactivates it at Px0.  
If DDx0 is set to "output", then writing 1 at PORTx0 drives Px0 high, and writing 0 drives Px0 low. 

#### PINx
```
+-------+-------+-------+-------+-------+-------+-------+-------+
| PINx7 | PINx6 | PINx5 | PINx4 | PINx3 | PINx2 | PINx1 | PINx0 |
+-------+-------+-------+-------+-------+-------+-------+-------+
```
Pin x register allows reading the values on the pins with "input" direction. For instance, if DDx0 is set to "input", then PINx0 can be used to read the input value.

### Fuse Bits
#### Introduction
In an AVR, fuse bytes are composed of 8 fuse bits responsible for the behavior of the chip. The bits are programmable and nonvolatile (the fuse bits programmed dont change their values the next time the chip is active). Writing 1 into a fuse bit sets it to unprogrammed and 0 sets it to programmed.

Some AVR microcontrollers have 2 fuse bytes (low and high) and others like the ATmega328p have 3 fuse bytes (low, high and extended). 

Source: [datasheet](#datasheet) § 31.2. Fuse Bits.

#### Configure AVR clock
An AVR clock speed detemines how many instructions are executed per second (Hz or cycles/second). 

### Contributing
* Edit README.md
* Add your changes
* Write description of your changes in the `Commit changes` form
* Select the radio button "Create a new branch for this commit and start a pull request."
* Specify a name for your commit branch
* Click on "Propose file change" and then on "Create pull request"

### Resources
* https://www.sparkfun.com/
* https://aaroneiche.com/2016/11/06/programming-avrs-using-a-usbasp-on-a-mac/
* http://www.avr-tutorials.com/digital/about-avr-8-bit-microcontrollers-digital-io-ports
* http://www.ladyada.net/learn/avr/fuses.html
* http://treehouseprojects.ca/fusebits/
