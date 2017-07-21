## Using internal clock source

The goal of this example is to demonstrate how the clock can be configured to run at various frequencies.

### Example 1
* Internal clock source: 8Mhz
* CKDIV8: 0 (programmed)
* Clock speed = 8Mhz / 8 = 1Mhz
* Every 1 million cycle is 1 second

Compile and upload:
```
```

### Example 2
* Internal clock source: 8Mhz
* CKDIV8: 1 (unprogrammed)
* Clock speed = 8Mhz
* Every 8 million cycle is 1 second

Compile and upload:
```
```

### Example 3
* Internal clock source: 8Mhz
* CKDIV8: 1 (unprogrammed)
* Clock speed = 8Mhz
* Every 8 million cycle is 1 second
* Overclock the AVR to 10Mhz

Compile and upload:
```
```

### Circuit
<img src="../../../images/circuit-int-clock-led.jpg">
