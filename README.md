
# Arduino-ZabbixTrapper #

Zabbix trap sender for Arduino and AVR ATmega328P MCU, written using Platformio.

The code works with iBoard 1.1 Ethernet board clone. It should also work with the original Ethernet board.

## Prerequisites ##

The project expects Platformio framework installed. See (PlatformIO Core) [http://docs.platformio.org/en/latest/installation.html] for details.

## Building ##

After checking out this repository, cd to its root directory and issue ```platformio init```.
This will satisfy dependencies and set up the envirnment.

Edit platformio init to suit your needs. It is preconfigured for iBoard/Ethernet board
and AVR Dragon with SPI attached to the iBoard.

Edit src/config.hpp to suit your environment. The board is preconfigured to obtain the IPv4 address
using DHCP protocol. You can (and should) change the MAC address, as well as Zabbix server IP address
to suit your needs.

Execute ```platformio run``` to build the code. To both build the code and program the board,
execute ```platformio run --target=program```.


## Author ##

The code is copyright 2017, Lubos Medovarsky.
All rights reserved.

Licensed under BSD 3-clause license.
