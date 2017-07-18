#!/bin/bash
# Author: Matthew Davis
# Modified by: Amir Bawab

# Used to flash a C program to the Atmega328p
function flash() {

    if [[ -z "$1" ]]
    then
        cat<<EOF
Compile C program and upload generated hex to connected Atmega328p

Usage: 
    ./upload.sh program.c
EOF
    else
        # remove extension from arg
        filename=$(echo "$1" | cut -d '.' -f 1)

        # create object and hex files
        avr-gcc -std=c11 -mmcu=atmega328 -O -o "${filename}.o" "$1"
        avr-objcopy -O ihex "${filename}.o" "${filename}.hex"

        # flash hex file to atmega
        sudo avrdude -c usbtiny -p m328p -U "flash:w:${filename}.hex"

        # remove object and hex files to keep dir clean
        rm "${filename}.o" "${filename}.hex"
    fi
}

flash "$1"
