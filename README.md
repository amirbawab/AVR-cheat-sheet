# AVR Cheat Sheet 

*The Following Cheat Sheet is built based on the ATmega328p, but other AVR microcontroller should follow similar steps.*

### Table of Contents

* [Datasheet](#datasheet)
    * [ATmega328p](#atmega328p)
* [Packages](#packages)
    * [Arch linux](#arch-linux)
* [Microcontroller](#microcontroller)
    * [ATmega328p](#atmega328p-1)
* [Programmer](#programmer)
    * [Sparkfun Pocket AVR Programmer](#sparkfun-pocket-avr-programmer)
    * [USBASP USBISP AVR Programmer](#usbasp-usbisp-avr-programmer)
    * [Programmer circuit](#programmer-circuit)
* [Eclipse](#eclipse)
    * [Installation](#installation)
    * [Create a new project](#create-a-new-project)
    * [Configure project](#configure-project)
    * [Configure fuse bits](#configure-fuse-bits)
    * [Build and upload from Eclipse](#build-and-upload-from-eclipse)
* [Manually (no IDE)](#manually-no-ide)
    * [Build and upload manually](#build-and-upload-manually)
    * [Reset fuse bytes to default values manually](#reset-fuse-bytes-to-default-values-manually)
    * [Read fuse bytes manually](#read-fuse-bytes-manually)
* [Input/Output](#inputoutput)
    * [Introduction](#introduction)
    * [DDRx](#ddrx)
    * [PORTx](#portx)
    * [PINx](#pinx)
* [Fuse bits](#fuse-bits)
    * [Introduction](#introduction-1)
    * [Low fuse byte](#low-fuse-byte)
    * [High fuse byte](#high-fuse-byte)
    * [Extended fuse byte](#extended-fuse-byte)
* [Clock source](#clock-source)
    * [AVR Clock](#avr-clock)
    * [Why using external clock source](#why-using-external-clock-source)
* [Examples](#examples)
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
```
                          ATmega328p
                          +---------+
(PCINT14/RESET)      PC6 /|1  \_/ 28|\ PC5 (ADC5/SCL/PCINT13)
(PCINT16/RXD)        PD0 /|2      27|\ PC4 (ADC4/SDA/PCINT12)
(PCINT17/TXD)        PD1 /|3      26|\ PC3 (ADC3/PCINT11)
(PCINT18/INT0)       PD2 /|4      25|\ PC2 (ADC2/PCINT10)
(PCINT19/OC2B/INT1)  PD3 /|5      24|\ PC1 (ADC1/PCINT9)
(PCINT20/XCK/T0)     PD4 /|6      23|\ PC0 (ADC0/PCINT8)
VCC                      /|7      22|\     GND
GND                      /|8      21|\     AREF
(PCINT6/XTAL1/TOSC1) PB6 /|9      20|\     AVCC
(PCINT7/XTAL2/TOSC2) PB7 /|10     19|\ PB5 (SCK/PCINT5)
(PCINT21/OC0B/T1)    PD5 /|11     18|\ PB4 (MISO/PCINT4)
(PCINT22/OC0A/AIN0)  PD6 /|12     17|\ PB3 (MOSI/OC2A/PCINT3)
(PCINT23/AIN1)       PD7 /|13     16|\ PB2 (SS/OC1B/PCINT2)
(PCINT0/CLKO/ICP1)   PB0 /|14     15|\ PB1 (OC1A/PCINT1)
                          +---------+
```

### Programmer
#### Sparkfun Pocket AVR Programmer
The device was tested on Ubuntu 16.04 and Arch linux  
<img width="300" src="images/usbtiny-programmer.jpg"/>  

#### USBASP USBISP AVR Programmer
The device was tested on Arch linux  
<img width="300" src="images/usbasp-programmer.jpg"/>

#### Programmer circuit
Components for circuit (1) and (2):
* 1x ATmega328p
* 1x Resistor 10K ohm
* 1x AVR Programmer

Additional components for circuit (2):
* 1x Crystal oscillator 16Mhz
* 2x Capacitor 12-22pf

*Note: For details about the crystal oscillator and capacitors values, refer to the datasheet under the section "System Clock and Clock Options"*

Circuit (1): If the AVR fuse bits are configured to use the internal oscillator 
<img src="images/circuit-programmer-1.jpg"/>  

Circuit (2): If the AVR fuse bits are configured to use an external clock source
<img src="images/circuit-programmer-2.jpg"/>  

*Note: For more details about fuse bits please refer to the [Fuse bits](#fuse-bits) section*

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
  * Select **ATmega328p** as **MCU type** and select the **MCU Clock Frequency** value (default is 1Mhz).
* Done! Click on **Apply and Close**

Note that we did not explicitly tell **avr-gcc** to include ATMega328p header files using the -I flag, nor to link the correct libraries using -l flag. However, we did mention in the configuration that the target hardware is an ATMega328p which will add the -mmcu=atmega328p to the avr-gcc command and use the corresponding files. 

For instance, consider some IO functionality is required in the C program written for the ATmega328p. To use those functionalities, the <avr/io.h> header file should be included. Using the -mmcu switch the compiler will directly know that the file meant to be loaded is in fact <avr/iom328p.h> by preprocessing the macros in <avr/io.h>. 

> #include <avr/io.h>  
> This header file includes the apropriate IO definitions for the device that has been specified by the -mmcu= compiler command-line switch. This is done by diverting to the appropriate file <avr/ioXXXX.h> which should never be included directly. Some register names common to all AVR devices are defined directly within <avr/common.h>, which is included in <avr/io.h>, but most of the details come from the respective include file.

From: http://www.atmel.com/webdoc/avrlibcreferencemanual/group__avr__io.html

#### Configure fuse bits
* In **Project Explorer** select the AVR project
* Go to **Project** > **Properties**
* Expand **AVR** then select **AVRDude**
* In **Fuses** tab, **select direct hex values** then click on the **Select editor** icon to configure the fuses. Or if you know the hex values, just write them in the corresponding fields (fuse bytes).
* *Note: A wrong configuration can prevent you from reprogramming your AVR.*
* Done! Click **Apply and Close**

#### Build and upload from Eclipse
* Write a small C program for your AVR microntroller
* Build the project
* Do the required wiring between the AVR microcontroller and the programmer refer to the [Programmer](#programmer) section.
* Plug the programmer into your machine
* Go to **AVR** > **Upload Project to Target Device**

### Manually (no IDE)
#### Build and upload manually
* Write a small C program for your AVR microcontroller
* Generate object file: 
```
avr-gcc -std=c11 -mmcu=atmega328 -O -o avr.o avr.c
```
* Generate hex file:
```
avr-objcopy -O ihex avr.o avr.hex
```
* Upload hex to the AVR microcontroller: 
```
avrdude -c usbasp -p m328p -U flash:w:avr.hex
```
  * Select the `-c` value depending on which AVR programmer device your are using.
    * Use `usbtiny` for the SparkFun Pocket AVR Programmer
    * Use `usbasp` for the USBASP USBISP AVR Programmer
    * Or if you have another AVR Programmer select the correct value

Use <a href="script/ATmega328-upload.sh">ATmega328-upload.sh</a> script file to buid a C program and upload its hex to the ATmega328p (The script file uses the commands described above). 

#### Reset fuse bytes to default values manually
* From the [Fuse Bits](#fuse-bits) section, locate the **Fuse Low Byte** table
  * Write down the **Default value** top-down (Bits#: 7...0): 01100010 (binary) = 0x62 (hex)
* Locate the **Fuse High Byte** table
  * Write down the **Default value** top-down (Bits#: 7...0): 11011001 (binary) = 0xd9 (hex)
* Locate the **Extended Fuse Byte for ATmega328/P** table
  * Write down the **Default value** top-down (Bits#: 7...0): 11111111 (binary) = 0xff (hex)
* The final command looks like this:
```
avrdude -p m328p -c usbasp -Ulfuse:w:0x62:m -Uhfuse:w:0xd9:m -Uefuse:w:0xff:m 
```
  * Remeber to update the `-c` switches to match your programmer. For more details check [Build and upload manually](#build-and-upload-manually).

#### Read fuse bytes manually
* Reading fuse bits is done using `avrdude` command.
```
avrdude -c usbasp -p m328p -U lfuse:r:-:h -U hfuse:r:-:h -U efuse:r:-:h
```
  * Remeber to update the `-c` switches to match your programmer. For more details check [Build and upload manually](#build-and-upload-manually).
  * The `-` symbol in each of the `-U` switches values tells the command to print the results on the screen. To write the output on a file, just replace `-` by a file path (e.g. `/tmp/low_fuse.hex`). 

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

### Fuse bits
#### Introduction
ATmega328p has three fuse bytes composed of 8 fuse bits each, responsible for the behavior of the chip. The bits are programmable and nonvolatile (the fuse bits programmed dont change their values the next time the chip is active). Writing 1 into a fuse bit sets it to unprogrammed and 0 sets it to programmed.

#### Low fuse byte
The low fuse byte enables controlling the speed, start up time and the source of the clock. Furthermore, it allows exposing the system clock output on PORTB0. Refer to [datasheet](#datasheet) at section "Clock Output Buffer".
```
+---------------+---------+-------------------------+------------------+-------------------------------------+
| Low Fuse Byte | Bit No. | Description             | Default Value    | Comments                            |
+---------------+---------+-------------------------+------------------+-------------------------------------+
| CKDIV8        |    7    | Divide clock by 8       | 0 (programmed)   | By default the 8Mhz internal clock  |
|               |         |                         |                  | is divided by 8 (8Mhz/8 = 1Mhz)     |
+---------------+---------+-------------------------+------------------+-------------------------------------+
| CKOUT         |    6    | Clock output            | 1 (unprogrammed) | Expose the system clock output on   |
|               |         |                         |                  | PORTB0.
+---------------+---------+-------------------------+------------------+-------------------------------------+
| SUT1          |    5    | Select start-up time    | 1 (unprogrammed) | Set the clock start up time.        |
+---------------+---------+-------------------------+------------------+                                     |
| SUT0          |    4    | Select start-up time    | 0 (programmed)   |                                     |
+---------------+---------+-------------------------+------------------+-------------------------------------+
| CKSEL3        |    3    | Select Clock source     | 0 (programmed)   | By default the internal clock is    |
+---------------+---------+-------------------------+------------------+ used.                               |
| CKSEL2        |    2    | Select Clock source     | 0 (programmed)   |                                     |
+---------------+---------+-------------------------+------------------+                                     |
| CKSEL1        |    1    | Select Clock source     | 1 (unprogrammed) |                                     |
+---------------+---------+-------------------------+------------------+                                     |
| CKSEL0        |    0    | Select Clock source     | 0 (programmed)   |                                     |
+---------------+---------+-------------------------+------------------+-------------------------------------+
```

#### High fuse byte
The high fuse byte is responsible for various type of configuration.
```
+----------------+---------+----------------------------+------------------+-------------------------------------+
| High Fuse Byte | Bit No. | Description                | Default Value    | Comments                            |
+----------------+---------+----------------------------+------------------+-------------------------------------+
| RSTDISBL       |    7    | External Reset Disable     | 1 (unprogrammed) | Disable reset functionality.        |
|                |         |                            |                  | Modifying this can prevent you from |
|                |         |                            |                  | reprogramming your chip.            |
+----------------+---------+----------------------------+------------------+-------------------------------------+
| DWEN           |    6    | debugWIRE Enable           | 1 (unprogrammed) | Used for debugging.                 |
|                |         |                            |                  | Modifying this can prevent you from |
|                |         |                            |                  | reprogramming your chip.            |
+----------------+---------+----------------------------+------------------+-------------------------------------+
| SPIEN          |    5    | Enable Serial Program      | 0 (programmed)   | By default SPI is enabled.          |
|                |         | and Data Downloading       |                  | Modifying this can prevent you from |
|                |         |                            |                  | reprogramming your chip.            |
+----------------+---------+----------------------------+------------------+-------------------------------------+
| WDTON          |    4    | Watchdog Timer Always On   | 1 (unprogrammed) | Watchdog timer resets the chip      |
|                |         |                            |                  | if it was not responding.           |
+----------------+---------+----------------------------+------------------+-------------------------------------+
| EESAVE         |    3    | EEPROM memory is preserved | 1 (unprogrammed) | EEPROM is a non volatile memory     |
|                |         | through the Chip Erase     |                  | which can hold permanen data.       |
+----------------+---------+----------------------------+------------------+-------------------------------------+
| BOOTSZ1        |    2    | Select Boot Size           | 0 (programmed)   | Set the size of the bootloader      |
+----------------+---------+----------------------------+------------------+                                     |
| BOOTSZ0        |    1    | Select Boot Size           | 0 (programmed)   |                                     |
+----------------+---------+----------------------------+------------------+-------------------------------------+
| BOOTRST        |    0    | Select Reset Vector        | 1 (unprogrammed) | Enable or disbale the bootloader    |
+----------------+---------+----------------------------+------------------+-------------------------------------+
```

#### Extended fuse byte
If the ATmega chips is offered a poor voltage, it can become unstable and possibly misbehave. Therefore, the extended fuse byte allows setting a BOD (Brown-Out Detector) threshold voltage determining if the chip should stay active or should reset.
```
+--------------------+---------+----------------------------+------------------+-------------------------------------+
| Extended Fuse Byte | Bit No. | Description                | Default Value    | Comments                            |
+--------------------+---------+----------------------------+------------------+-------------------------------------+
|         -          |    7    |             -              |        1         |                  -                  |
+--------------------+---------+----------------------------+------------------+-------------------------------------+
|         -          |    6    |             -              |        1         |                  -                  |
+--------------------+---------+----------------------------+------------------+-------------------------------------+
|         -          |    5    |             -              |        1         |                  -                  |
+--------------------+---------+----------------------------+------------------+-------------------------------------+
|         -          |    4    |             -              |        1         |                  -                  |
+--------------------+---------+----------------------------+------------------+-------------------------------------+
|         -          |    3    |             -              |        1         |                  -                  |
+--------------------+---------+----------------------------+------------------+-------------------------------------+
| BODLEVEL2          |    2    | Brown-out Detector trigger | 1 (unprogrammed) | A threshold voltage determining     |
|                    |         |           level            |                  | if the chip should stay active or   |
+--------------------+---------+----------------------------+------------------+ should reset.                       +
| BODLEVEL1          |    1    | Brown-out Detector trigger | 1 (unprogrammed) |                                     |
|                    |         |           level            |                  |                                     |
+--------------------+---------+----------------------------+------------------+                                     +
| BODLEVEL0          |    0    | Brown-out Detector trigger | 1 (unprogrammed) |                                     |
|                    |         |           level            |                  |                                     |
+--------------------+---------+----------------------------+------------------+-------------------------------------+
```

### Clock source
#### AVR Clock
*Note: If you have an AVR microcontroller other than the ATmega328p, then you can check the values below in your datasheet under the section "Calibrated Internal RC Oscillator".*

By default the ATmega328p internal RC Oscillator provides an 8.0Mhz clock. Also the default fuse bit CKDIV8 is programmed which divides the internal frequency by 8 (8.0Mhz / 8 = 1.0Mhz). To make the chip work on an 8Mhz frequency (maximum clock speed), the CKDIV8 bit must be unprogrammed. If more than 8Mhz is needed then avoid overclocking your AVR (can misbehave), instead use an external clock source. 

*Note: For more details about fuse bits CKDIV8 configuration, check the [Fuse bits](#fuse-bits) section.*

#### Why using external clock source
External clock source, such as an external crystal oscillator, is sometimes important because it provides a more accurate timing than the one offered by the internal RC oscillator integrated in the AVR. A more accurate clock is required when the program developed depends on a very accurate clock (e.g. Timer) or envolves USB related functionalities where timing is curicial. However, adding an external crystal oscillator consumes more power, resulting in quickly draining the batteries.

#### Example of clock source
Example for using internal and external clock source can be found in the section [Examples](#examples)

### External interrupts
#### Difference between INTx and PCINTx
* There are only few INTx pins but there are a lot more PCINTx pins.
* Each INTx pin have its own interrupt vector making it simple for the developer to listen for an event on that specific pin. On the other hand, a PCINTx pin shares an interrupt vector with several others, so listening for an event on that specific pin requires additional steps in order to mask out the other PCINTx pins in the same vector. To know which PCINTx pins share the same interrupt vector, refer to you AVR datashete at section "EXINT - External Interrupts".
* INTx can report events under several situations (For ATmega328p: INT0:[low, any] and INT1:[falling, rising]). PCINTx report events on any change.
  * Note that as of revision B of the ATmega328p datasheet, there is a typo in the Interrupt Sense Control 0 and 1 tables. The fix is: ISC00 and ISC01 are for INT0, and ISC10 and ISC11 are for INT1.

#### Configure INTx
* In general, the Data Direction value (DDxn) for INTx is set to "input", and the port value (PORTxn) is set to high (enable pull-up resitor). However, setting the Data Direction for INTx to "output" will still trigger an event.
* As explained above, the INTx can report event on different degrees. To specify this degree level, refer to the datasheet at section "External Interrupt Control Register A" in order to set the value for `EICRA`.
* The ATmega328p has two INTx pins (INT0 and INT1). To specify the used one(s), set the value for `EIMSK` by checking the options in the datasheet at section "External Interrupt Mask Register".
* To activate interrupts use `sei()` and to deactivate them use `cli()`.
* To handle events from INTx, use the following function `ISR(INTx_vect){...}`

#### Configure PCINTx
* In general, the Data Direction value (DDxn) for PCINTx is set to "input", and the port value (PORTxn) is set to high (enable pull-up resitor). However, setting the Data Direction for PCINTx to "output" will still trigger an event.
* Set the range of pins that will cause an interrupt. This can be done by setting the value for the `PCICR` to the corresponding range(s). Details about setting this register can be found in the datasheet at section "Pin Change Interrupt Control Register".
* In the selected ranges, mask out the pins that will not provide any interrupts by setting the value for `PCMSKx` where `x` is the group index for the selected pin range. If more than one range is selected, then multiple `PCMSKx` should be defined. For more information about the values for that register refer to the datasheet at section "Pin Change Mask Register ...".
* To activate interrupts use `sei()` and to deactivate them use `cli()`.
* To handle events from PCINTx, use the following function `ISR(PCINTy_vect){...}` where `y` is the group index of the selected range pins.

#### Example of external interrputs
Example for using external interrupts can be found in the section [Examples](#examples)

### Timer
#### Introduction
The ATmega328p has two 8-bit timers and one 16-bit timer. The 8-bit timers counts up to 255, and the 16-bit 
timer counts up to 65,536.

#### Timer 0 (TC0 8-bit)
**Register**: TCCR0A  
**Name**: Timer/Counter 0 Control Register A  
**Datasheet**: 19.9.1. TC0 Control Register A  
**Description**: Set the timer mode.  
**Value**:   
```
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
| Mode | WGM02 | WGM01 | WGM00 |    Timer/Counter   | TOP  | Update of OCR0x at | TOV Flag Set on |
|      |       |       |       |  Mode of Operation |      |                    |                 |
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
|  0   |   0   |   0   |   0   |       Normal       | 0xFF |     Immediate      |      MAX        |
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
|  1   |   0   |   0   |   1   | PWM, Phase Correct | 0xFF |        TOP         |     BOTTOM      |
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
|  2   |   0   |   1   |   0   | CTC (Clear Timer   | OCRA |     Immediate      |      MAX        |
|      |       |       |       | on Compare Match)  |      |                    |                 |
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
|  3   |   0   |   1   |   1   |     Fast PWM       | 0xFF |      BOTTOM        |      MAX        |
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
|  4   |   1   |   0   |   0   |     Reserved       |  -   |         -          |       -         |
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
|  5   |   1   |   0   |   1   | PWM, Phase Correct | OCRA |        TOP         |     BOTTOM      |
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
|  6   |   1   |   1   |   0   |     Reserved       |  -   |         -          |       -         |
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
|  7   |   1   |   1   |   1   |     Fast PWM       | OCRA |      BOTTOM        |      TOP        |
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
```
##### Modes (19.7 Modes of Operation)
**Normal**: The counter simply overruns when it passes its 8-bit value and then restarts from the bottom.  
**CTC mode**: The counter is cleared (reset to 0)  when the counter value (TCNT0) matches the OCR0A.

---

**Register**: TCCR0B  
**Name**: Timer/Counter 0 Control Register B  
**Datasheet**: 19.9.2. TC0 Control Register B  
**Description**: Prescaler allows slowing down the timer by dividing the timer clock frequency by 1, 8, 64, etc...  
**Value**:  
```
+------+------+------+--------------------------------------------------------+
| CS02 | CS01 | CS00 | Description                                            |
+------+------+------+--------------------------------------------------------+
|   0  |   0  |   0  | No clock source (Timer/Counter stopped)                |
+------+------+------+--------------------------------------------------------+
|   0  |   0  |   1  | clk/1 (No prescaling)                                  |
+------+------+------+--------------------------------------------------------+
|   0  |   1  |   0  | clk/8 (From prescaler)                                 |
+------+------+------+--------------------------------------------------------+
|   0  |   1  |   1  | clk/64 (From prescaler)                                |
+------+------+------+--------------------------------------------------------+
|   1  |   0  |   0  | clk/256 (From prescaler)                               |
+------+------+------+--------------------------------------------------------+
|   1  |   0  |   1  | clk/1024 (From prescaler)                              |
+------+------+------+--------------------------------------------------------+
|   1  |   1  |   0  | External clock source on T0 pin. Clock on falling edge |
+------+------+------+--------------------------------------------------------+
|   1  |   1  |   1  | External clock source on T0 pin. Clock on rising edge  |
+------+------+------+--------------------------------------------------------+
```

---

**Register**: OCR0A  
**Name**: Timer/Counter 0 Output Compare Register A  
**Datasheet**: 19.9.6. TC0 Output Compare Register A  
**Description**: This register contains an 8-bit value that is continuously compared with the counter value, 
and when there is a match an Output Compare interrupt occures.  
**Value**: It is common to calculate this value using an online timer calculator like 
http://eleccelerator.com/avr-timer-calculator/.
For example, given an ATmega328p with a clock of 1Mhz. Assume the timer that will be active is of 8-bits. 
The prescale can be set to Clk/1024 to work with the time in a flexible way (check above for more details). 
Finally, consider that the timer should interrupt every 1 second. Put all those information in the calculator
in order to generate the total timer ticks required in order to get 1 second, that is the value for OCR0A. 
Please note that the value provided by the calculator might be greater than 255 (active timer is only 8-bit).
If that is the case, then try setting the desired time to something small (e.g. 0.1s, 0.01s, etc...), 
and from the C program keep a counter that will determine when 1 second has passed.

---

**Register**: OCR0B  
**Name**: Timer/Counter 0 Output Compare Register B  
**Datasheet**: 19.9.7. TC0 Output Compare Register B  
**Description**: Refer to OCR0A  
**Value**: Refer to OCR0A  

---

**Register**: TIMSK0  
**Name**: Timer/Counter 0 Interrupt Mask Register  
**Datasheet**: 19.9.3. TC0 Interrupt Mask Register  
**Description**: Enables the logic when an interrupt should occur.  
**Value**: 
```
+--------+--------------------------+-------------------------------------------------------+
| Value  | Name                     | Description                                           |
+--------+--------------------------+-------------------------------------------------------+
| OCIE0B | Output Compare B         | Execute interrupt if timer value matches OCIE0B value |
|        | Match Interrupt Enable   |                                                       |
+--------+--------------------------+-------------------------------------------------------+
| OCIE0A | Output Compare A         | Execute interrupt if timer value matches OCIE0A value |
|        | Match Interrupt Enable   |                                                       |
+--------+--------------------------+-------------------------------------------------------+
| TOIE0  | Timer/Counter0, Overflow | Execute interrupt if timer value overflows e.g. 255+1 |
|        | Interrupt Enable         |                                                       |
+--------+--------------------------+-------------------------------------------------------+
```

#### Timer 1 (TC1 16-bit)
**Register**: TCCR1A  
**Name**: Timer/Counter 1 Control Register A  
**Datasheet**: 20.14.1. TC1 Control Register A  
**Description**: Set the timer mode.  
**Value**:
```
+------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+
| Mode | WGM13 | WGM12 | WGM11 | WGM10 |   Timer/Counter   | TOP    | Update of | TOV1 Flag |
|      |       |       |       |       | Mode of Operation |        | OCR1x at  |  Set on   |
+------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+
|  0   |   0   |   0   |   0   |   0   |      Normal       | 0xFFFF | Immediate |    MAX    |
+------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+
|  1   |   0   |   0   |   0   |   1   | PWM,Phase Correct | 0X00FF |    TOP    |  BOTTOM   |
|      |       |       |       |       |       8-bit       |        |           |           |
+------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+
|  2   |   0   |   0   |   1   |   0   | PWM,Phase Correct | 0x01FF |    TOP    |  BOTTOM   |
|      |       |       |       |       |       9-bit       |        |           |           |
+------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+
|  3   |   0   |   0   |   1   |   1   | PWM,Phase Correct | 0x03FF |    TOP    |  BOTTOM   |
|      |       |       |       |       |       10-bit      |        |           |           |
+------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+
|  4   |   0   |   1   |   0   |   0   |        CTC        | CCR1A  | Immediate |    MAX    |
+------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+
|  5   |   0   |   1   |   0   |   1   | Fast PWM, 8-bit   | 0x00FF |  BOTTOM   |    TOP    |
+------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+
|  6   |   0   |   1   |   1   |   0   | Fast PWM, 9-bit   | 0x01FF |  BOTTOM   |    TOP    |
+------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+
|  7   |   0   |   1   |   1   |   1   | Fast PWM, 10-bit  | 0x03FF |  BOTTOM   |    TOP    |
+------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+
|  8   |   1   |   0   |   0   |   0   | PWM, Phase and    |  ICR1  |  BOTTOM   |  BOTTOM   |
|      |       |       |       |       | Frequency Correct |        |           |           |
+------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+
|  9   |   1   |   0   |   0   |   1   | PWM, Phase and    | OCR1A  |  BOTTOM   |  BOTTOM   |
|      |       |       |       |       | Frequency Correct |        |           |           |
+------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+
|  10  |   1   |   0   |   1   |   0   | PWM,Phase Correct |  ICR1  |    TOP    |  BOTTOM   |
+------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+
|  11  |   1   |   0   |   1   |   1   | PWM,Phase Correct | OCR1A  |    TOP    |  BOTTOM   |
+------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+
|  12  |   1   |   1   |   0   |   0   |        CTC        |  ICR1  | Immediate |    MAX    |
+------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+
|  13  |   1   |   1   |   0   |   1   |      Reserved     |   -    |     -     |     -     |
+------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+
|  14  |   1   |   1   |   1   |   0   |      Fast PWM     |  ICR1  |  BOTTOM   |    TOP    |
+------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+
|  15  |   1   |   1   |   1   |   1   |      Fast PWM     | OCR1A  |  BOTTOM   |    TOP    |
+------+-------+-------+-------+-------+-------------------+--------+-----------+-----------+
```

---

**Register**: TCCR1B  
**Name**: Timer/Counter 1 Control Register B  
**Datasheet**: 20.14.2. TC1 Control Register B  
**Description**: Set the timer mode.  
**Value**:
```
+------+------+------+--------------------------------------------------------+
| CS12 | CS11 | CS10 | Description                                            |
+------+------+------+--------------------------------------------------------+
|   0  |   0  |   0  | No clock source (Timer/Counter stopped)                |
+------+------+------+--------------------------------------------------------+
|   0  |   0  |   1  | clk/1 (No prescaling)                                  |
+------+------+------+--------------------------------------------------------+
|   0  |   1  |   0  | clk/8 (From prescaler)                                 |
+------+------+------+--------------------------------------------------------+
|   0  |   1  |   1  | clk/64 (From prescaler)                                |
+------+------+------+--------------------------------------------------------+
|   1  |   0  |   0  | clk/256 (From prescaler)                               |
+------+------+------+--------------------------------------------------------+
|   1  |   0  |   1  | clk/1024 (From prescaler)                              |
+------+------+------+--------------------------------------------------------+
|   1  |   1  |   0  | External clock source on T1 pin. Clock on falling edge |
+------+------+------+--------------------------------------------------------+
|   1  |   1  |   1  | External clock source on T1 pin. Clock on rising edge  |
+------+------+------+--------------------------------------------------------+
```

#### Timer 2 (TC0 8-bit)
**Register**: TCCR2A  
**Name**: Timer/Counter 2 Control Register A  
**Datasheet**: 22.11.1. TC2 Control Register A  
**Description**: Set the timer mode.  
**Value**:   
```
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
| Mode | WGM22 | WGM21 | WGM20 |    Timer/Counter   | TOP  | Update of OCR0x at | TOV Flag Set on |
|      |       |       |       |  Mode of Operation |      |                    |                 |
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
|  0   |   0   |   0   |   0   |       Normal       | 0xFF |     Immediate      |      MAX        |
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
|  1   |   0   |   0   |   1   | PWM, Phase Correct | 0xFF |        TOP         |     BOTTOM      |
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
|  2   |   0   |   1   |   0   | CTC (Clear Timer   | OCRA |     Immediate      |      MAX        |
|      |       |       |       | on Compare Match)  |      |                    |                 |
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
|  3   |   0   |   1   |   1   |     Fast PWM       | 0xFF |      BOTTOM        |      MAX        |
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
|  4   |   1   |   0   |   0   |     Reserved       |  -   |         -          |       -         |
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
|  5   |   1   |   0   |   1   | PWM, Phase Correct | OCRA |        TOP         |     BOTTOM      |
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
|  6   |   1   |   1   |   0   |     Reserved       |  -   |         -          |       -         |
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
|  7   |   1   |   1   |   1   |     Fast PWM       | OCRA |      BOTTOM        |      TOP        |
+------+-------+-------+-------+--------------------+------+--------------------+-----------------+
```
##### Modes (22.7 Modes of Operation)
Refer to this section under the Timer 0 (above)

---

**Register**: TCCR2B  
**Name**: Timer/Counter 2 Control Register B  
**Datasheet**: 22.11.2. TC2 Control Register B  
**Description**: Prescaler allows slowing down the timer by dividing the timer clock frequency by 1, 8, 32, etc...  
**Value**:  
```
+------+------+------+-------------------------------------------+
| CS22 | CS21 | CS20 | Description                               |
+------+------+------+-------------------------------------------+
|   0  |   0  |   0  | No clock source (Timer/Counter stopped)   |
+------+------+------+-------------------------------------------+
|   0  |   0  |   1  | clk/1 (No prescaling)                     |
+------+------+------+-------------------------------------------+
|   0  |   1  |   0  | clk/8 (From prescaler)                    |
+------+------+------+-------------------------------------------+
|   0  |   1  |   1  | clk/32 (From prescaler)                   |
+------+------+------+-------------------------------------------+
|   1  |   0  |   0  | clk/64 (From prescaler)                   |
+------+------+------+-------------------------------------------+
|   1  |   0  |   1  | clk/128 (From prescaler)                  |
+------+------+------+-------------------------------------------+
|   1  |   1  |   0  | clk/256 (From prescaler)                  |
+------+------+------+-------------------------------------------+
|   1  |   1  |   1  | clk/1024 (From prescaler)                 |
+------+------+------+-------------------------------------------+
```

---

**Register**: OCR2A  
**Name**: Timer/Counter 2 Output Compare Register A  
**Datasheet**: 22.11.4. TC2 Output Compare Register A  
**Description**: This register contains an 8-bit value that is continuously compared with the counter value, 
and when there is a match an Output Compare interrupt occures.  
**Value**: Refer to the register OCR0A in section [Timer 0](#timer-0)

---

**Register**: OCR2B  
**Name**: Timer/Counter 2 Output Compare Register B  
**Datasheet**: 22.11.5. TC2 Output Compare Register B  
**Description**: Refer to OCR2A  
**Value**: Refer to OCR2A 

---

**Register**: TIMSK2  
**Name**: Timer/Counter 2 Interrupt Mask Register  
**Datasheet**: 22.11.6. TC2 Interrupt Mask Register  
**Description**: Enables the logic when an interrupt should occur.  
**Value**: 
```
+--------+--------------------------+-------------------------------------------------------+
| Value  | Name                     | Description                                           |
+--------+--------------------------+-------------------------------------------------------+
| OCIE2B | Output Compare B         | Execute interrupt if timer value matches OCIE2B value |
|        | Match Interrupt Enable   |                                                       |
+--------+--------------------------+-------------------------------------------------------+
| OCIE2A | Output Compare A         | Execute interrupt if timer value matches OCIE2A value |
|        | Match Interrupt Enable   |                                                       |
+--------+--------------------------+-------------------------------------------------------+
| TOIE2  | Timer/Counter0, Overflow | Execute interrupt if timer value overflows e.g. 255+1 |
|        | Interrupt Enable         |                                                       |
+--------+--------------------------+-------------------------------------------------------+
```

### Examples
Some example files has been provided for further explanation
* <a href="examples">Example directory</a>

### Contributing
* Edit README.md
* Add your changes
* Write description of your changes in the `Commit changes` form
* Select the radio button "Create a new branch for this commit and start a pull request."
* Specify a name for your commit branch
* Click on "Propose file change" and then on "Create pull request"

### Resources
#### Websites
* https://www.sparkfun.com/
* https://aaroneiche.com/2016/11/06/programming-avrs-using-a-usbasp-on-a-mac/
* http://www.avr-tutorials.com/digital/about-avr-8-bit-microcontrollers-digital-io-ports
* http://www.ladyada.net/learn/avr/fuses.html
* http://treehouseprojects.ca/fusebits/
* http://www.instructables.com/id/How-to-change-fuse-bits-of-AVR-Atmega328p-8bit-mic/

#### YouTube
* NewbieHack - Microcontroller Tutorial - A Beginners, by Patrick Hood-Daniel
  * https://www.youtube.com/playlist?list=PLE72E4CFE73BD1DE1

* Learning AVR-C, by humanHardDrive
  * https://www.youtube.com/playlist?list=PLA6BB228B08B03EDD

* Atmel Programming Tutorial, by Chris Dahms
  * https://www.youtube.com/playlist?list=PLoLaqVexEviMZu55Y4JO66b4xIv5K-D1L
