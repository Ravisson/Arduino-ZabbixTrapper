/*

Copyright 2017 Lubos Medovarsky

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software
   without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

/*

The application sends increasing counter value to Zabbix in the form of traps.
To use in a meaningful manner, fire up your Zabbix UI or API, and create a
hostname "arduino", add an item with key "counter" of type "Zabbix trapper",
with type "Numeric".

*/


#include <SPI.h>
#include <Ethernet.h>
#include "config.hpp"

int counter;

byte mac[] = { MAC1, MAC2, MAC3, MAC4, MAC5, MAC6 };
IPAddress zabbix(ZABBIX_IP1, ZABBIX_IP2, ZABBIX_IP3, ZABBIX_IP4);

void setup() {
    Serial.begin(9600);
    Serial.println("iBoard 1.1");
    Serial.println("Obtaining IP address using DHCP...");
    while (Ethernet.begin(mac) != 1) {
        delay(10);
    }
    counter = 1;
    Serial.println("setup done.");
}

void loop() {
    zabbix_send_trap();
    delay(60000);
    counter++;
}

const char PROGMEM content_header[] = "{\"request\":\"sender data\",\"data\":[";
const char PROGMEM content_item[] = "{\"host\":\"%s\",\"key\":\"%s\",\"value\":\"%d\"}";
const char PROGMEM content_footer[] = "]}";

char host[] = "arduino";     // hostname zabbix
char key[] = "counter";            // item  zabbix

unsigned int prepare_content(char *dst) {
    unsigned int len = 0;

    memcpy(&dst[len], content_header, sizeof(content_header));
    len += sizeof(content_header) - 1;
    len += sprintf_P(&dst[len], content_item, host, key, counter);
    memcpy(&dst[len], content_footer, sizeof(content_footer));
    len += sizeof(content_footer) - 1;
    return len;
}

EthernetClient zbx_client;
char packet_header[] = "ZBXD\1"; //followed by unsigned long long content_len
unsigned long long content_len;
unsigned int payload_len;
char packet_content[256];

void zabbix_send_trap() {
    content_len = prepare_content(packet_content);
    payload_len = sizeof(content_header) + content_len + sizeof(content_footer);
    if (zbx_client.connect(zabbix, 10051)) {
        Serial.println("connected to zabbix");
        Serial.println("sending data");
        zbx_client.write(packet_header, sizeof(packet_header) - 1);
	zbx_client.write((char *)&content_len, sizeof(content_len));
        zbx_client.write(packet_content, content_len);
        delay(1);
        zbx_client.stop();
        Serial.println("disconnected");
    }
}
