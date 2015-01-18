#include <RemoteSwitch.h>

int ledPin = 13;
int everPin = 10;

int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the analog resistor divider

EverFlourishSwitch everswitch(everPin);

void setup() {
  pinMode(everPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  photocellReading = analogRead(photocellPin);

  Serial.print("Analog reading = ");
  Serial.print(photocellReading);     // the raw analog reading
  Serial.println();

  // We'll have a few threshholds, qualitatively determined
  if (photocellReading < 700) {
    digitalWrite(ledPin, HIGH);
    everswitch.sendSignal('B', 1, true);
  } else {
    digitalWrite(ledPin, LOW);
    everswitch.sendSignal('B', 1, false);
  }
  delay(1000);
}
