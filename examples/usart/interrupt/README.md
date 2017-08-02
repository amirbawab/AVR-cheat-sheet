## USART - Interrupt driven

### Example 1
Toggle LED everytime time the key `b` is pressed.

#### Steps
* Connect FTDI Basic into your machine
* Write the FTDI Basic into the ATmega328p (RX and TX pins)
* Connect to the FTDI from your machine using the `screen` command.
* Press `b`

### Example 2
Send a letter `a` to the console and toggle LED everytime a transmit is complete.

#### Steps
* Connect FTDI Basic into your machine
* Write the FTDI Basic into the ATmega328p (RX and TX pins)
* Connect to the FTDI from your machine using the `screen` command.
* You should see the letter `a` printed every 1 second on your screen.
