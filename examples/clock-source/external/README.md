## Using external clock source

### Why using external clock source
External clock source, such as an external crystal oscillator, is sometimes important because it provides a more accurate timing than the one offered by the internal RC oscillator integrated in the AVR. A more accurate clock is required when the program developed depends on a very accurate clock (e.g. Timer) or envolves USB related functionalities where timing is curicial. However, adding an external crystal oscillator consumes more power, resulting in quickly draining the batteries.



