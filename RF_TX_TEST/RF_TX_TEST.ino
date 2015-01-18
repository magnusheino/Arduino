#include <RCSwitch.h>

RCSwitch everFlourishSwitch = RCSwitch();
int led = 13;

void setup() {
  pinMode(led, OUTPUT); 
  everFlourishSwitch.enableTransmit(10);  // Using Pin #10
}

void loop() {
  digitalWrite(led, HIGH);;      
  everFlourishSwitch.send(0x451557, 24);
  delay(1000);
  digitalWrite(led, LOW);
  everFlourishSwitch.send(0x451554, 24);
  delay(1000);
}
