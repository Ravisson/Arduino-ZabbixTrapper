
# Arduino ZabbixTrapper Proof of Concept #

[Zabbix](http://zabbix.com/) [trap](https://www.zabbix.com/documentation/2.0/manual/config/items/itemtypes/trapper)
sender (TCP client) for Arduino and AVR MCUs and Wiznet 5100 Ethernet silicon, written using [Platformio](http://platformio.org/).

The code works with iTead Studio's [iBoard 1.1](https://www.itead.cc/iboard.html) Ethernet board.
It should also work with the original [Arduino EthernetShield](https://www.arduino.cc/en/Main/ArduinoEthernetShield).

## Prerequisites ##

The project expects Platformio framework installed. See [PlatformIO Core](http://docs.platformio.org/en/latest/installation.html) for details.

## Building ##

After checking out this repository:
* cd to the repository's root directory
* edit platformio init to suit your needs. It is preconfigured for iBoard/Ethernet board
and AVR Dragon with SPI attached to the iBoard.
* issue ```platformio init```. This will satisfy dependencies and set up the environment.
* edit src/config.hpp to suit your environment. The board is preconfigured to obtain the IPv4 address
using DHCP protocol. You can (and should) change the MAC address, as well as Zabbix server IP address
to suit your needs.
* execute ```platformio run``` to build the code,
* to build the code and program the board afterwards, execute ```platformio run --target=program```.


## Author ##

The code is copyright 2017, Lubos Medovarsky.
All rights reserved.

Licensed under BSD 3-clause license.
