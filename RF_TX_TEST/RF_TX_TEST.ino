#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
int led = 13;

#define ON 1

void setup() {
  pinMode(led, OUTPUT); 
  mySwitch.enableTransmit(10);  // Using Pin #10
}

void loop() {
//  digitalWrite(led, HIGH);;      
//  mySwitch.send(4527447, 24);
//  delay(1000);
//  digitalWrite(led, LOW);
//  mySwitch.send(4527444, 24);
//  delay(1000);
  digitalWrite(led, HIGH);;      
  mySwitch.send(0x451557, 24);
  delay(1000);
  digitalWrite(led, LOW);
  mySwitch.send(0x451554, 24);
  delay(1000);
}
