#include <RemoteSwitch.h>

int led = 13;

EverFlourishSwitch everswitch(10);

void setup() {
  pinMode(10, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);;
  everswitch.sendSignal('B', 1, true);
  //wait 2 seconds
  delay(2000);
  digitalWrite(led, LOW);;
  everswitch.sendSignal('B', 1, false);
  delay(2000);
}
