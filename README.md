
# Packet Hack Village Badge

## Hack in the Box 2021

<img width="1391" alt="badge" src="https://user-images.githubusercontent.com/164192/143951272-8e56367f-7359-47f5-b485-b351de2fadd6.png">

Badge designed by [@TweetsFromPanda](https://twitter.com/TweetsFromPanda).

**[More Badge Information on Hackster](https://www.hackster.io/433948/the-packet-hack-badge-fc54cc)**

## Setup

Install AVR compiler and build tools:

### Linux (debian/ubuntu)

```shell
sudo apt install make gcc-avr binutils-avr gdb-avr avr-libc avrdude
```

### OSX (brew)

```shell
brew tap osx-cross/avr
brew install make avr-gcc avr-binutils avrdude
```

## Building

`HANDLE="LANRAT"` is optional and is used to program your own handle/name onto the badge. Replace with your own handle/name.

```shell
make clean
make HANDLE="LANRAT"
make flash
```

## Flashing

`make flash` should be all thats required. By default the Makefile will use `avrdude` setup with the [Tigard](https://github.com/tigard-tools/tigard) programmer, but any AVR programmer will work. You may need to tweak the Makefile to specify another programmer type.

### Fuses

If you need to program the fuses you can use the correct values are in `conf/lfuse` and `conf/hfuse`
The Makefile has recipes for reading/writing the correct fuse bits.

## Image

You can use the following program to create custom header files for your own images & logos.
https://www.hobbytronics.co.uk/bmp-lcd-converter
