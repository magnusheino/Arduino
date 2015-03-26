// nrf24_reliable_datagram_server.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple addressed, reliable messaging server
// with the RHReliableDatagram class, using the RH_NRF24 driver to control a NRF24 radio.
// It is designed to work with the other example nrf24_reliable_datagram_client
// Tested on Uno with Sparkfun WRL-00691 NRF24L01 module
// Tested on Teensy with Sparkfun WRL-00691 NRF24L01 module
// Tested on Anarduino Mini (http://www.anarduino.com/mini/) with RFM73 module
// Tested on Arduino Mega with Sparkfun WRL-00691 NRF25L01 module

#include <Ethernet.h>
#include <SPI.h>
#include <Wire.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
  Serial.begin(9600);

  Serial.println("Setup Wire communication");

  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event

  Serial.println("Wire communication setup");

  //  // start the Ethernet connection:
  //  if (Ethernet.begin(mac) == 0) {
  //    Serial.println("Failed to configure Ethernet using DHCP");
  //    // no point in carrying on, so do nothing forevermore:
  //    for (;;)
  //      ;
  //  }
  //  // print your local IP address:
  //  Serial.print("My IP address: ");
  //  for (byte thisByte = 0; thisByte < 4; thisByte++) {
  //    // print the value of each byte of the IP address:
  //    Serial.print(Ethernet.localIP()[thisByte], DEC);
  //    Serial.print(".");
  //  }
  //  Serial.println();
}

void receiveEvent(int howMany) {
  Serial.println("Received event");
  Serial.println(howMany);

  String result = String();
  while (Wire.available()) {
    char readStr = Wire.read();
    Serial.println("read");
    result = result + String(readStr);
  }
  Serial.println(result.c_str());
}

void loop() {
  delay(100);
}

