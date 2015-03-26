// nrf24_reliable_datagram_server.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple addressed, reliable messaging server
// with the RHReliableDatagram class, using the RH_NRF24 driver to control a NRF24 radio.
// It is designed to work with the other example nrf24_reliable_datagram_client
// Tested on Uno with Sparkfun WRL-00691 NRF24L01 module
// Tested on Teensy with Sparkfun WRL-00691 NRF24L01 module
// Tested on Anarduino Mini (http://www.anarduino.com/mini/) with RFM73 module
// Tested on Arduino Mega with Sparkfun WRL-00691 NRF25L01 module

#include <RHReliableDatagram.h>
#include <RH_NRF24.h>
#include <SPI.h>
#include <Wire.h>

#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2

// Singleton instance of the radio driver
RH_NRF24 driver(9, 10);
// RH_NRF24 driver(8, 7);   // For RFM73 on Anarduino Mini

// Class to manage message delivery and receipt, using the driver declared above
RHReliableDatagram manager(driver, SERVER_ADDRESS);

void setup() {
  Serial.begin(9600);
  if (!manager.init()) {
    Serial.println("init failed");
    // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  }
  Wire.begin();
}

float buf;
uint8_t buflen = sizeof(float);

void loop() {
  if (manager.available()) {
    uint8_t from;
    if (manager.recvfromAck((uint8_t*)&buf, &buflen, &from)) {
      Serial.print("got request from : 0x");
      Serial.print(from, HEX);
      Serial.print(": ");
      Serial.println(buf);

      switch (from) {
        case 0x1:
          Serial.println("SOVRUM");
          break;

        default:
          Serial.print("Received event from unknown source: ");
          Serial.print(from, HEX);
      }

      String result = String(buf);
      Serial.println(result);
      Serial.println(buf);

      String sendStr = result + ":SOVRUM";

      Wire.beginTransmission(4);
      Wire.write(sendStr.c_str());
      Wire.endTransmission();
    }
  }
}

