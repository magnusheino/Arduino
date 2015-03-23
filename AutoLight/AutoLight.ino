#include <RemoteSwitch.h>

#include <Wire.h>
#include "RTClib.h"

int ledPin = 13;
int everPin = 10;

int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the analog resistor divider

boolean lighted = false;

EverFlourishSwitch everswitch(everPin);

RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600);

  pinMode(everPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  Wire.begin();
  rtc.begin();

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  Serial.println("Init complete");
}

void loop() {
  if (lighted) {
    handleLighted();
  } else {
    handleNotLighted();
  }
  delay(1000 * 5);
}

boolean isWeekDay(DateTime& datetime) {
  return datetime.dayOfWeek() > 0 && datetime.dayOfWeek() < 6;
}

boolean isMorning(DateTime& datetime) {
  return datetime.hour() > 5 && datetime.hour() < 9 && isWeekDay(datetime);
}

boolean isEvening(DateTime& datetime) {
  return datetime.hour() > 14 && datetime.hour() < 23;
}

void handleLighted() {
  Serial.println("Light is on");
  DateTime now = getTime();

  if (!isEvening(now) && !isMorning(now)) {
    Serial.println("Time is evening and not morning");
    turnLightOff();
  } else {
    turnLightOn();
  }
}

DateTime getTime() {
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  
  return now;
}

void handleNotLighted() {
  Serial.println("Light is off");

  photocellReading = analogRead(photocellPin);

  if (photocellReading < 500) {
    Serial.println("It's dark");
    DateTime now = getTime();

    if (isMorning(now) || isEvening(now)) {
      Serial.println("Time is morning or evening");
      turnLightOn();
    } else {
      Serial.println("But time is not there");
      turnLightOff();
    }
  } else {
    Serial.println("It's not dark");
    turnLightOff();
  }
}

void turnLightOn() {
  Serial.println("Turn light on");
  digitalWrite(ledPin, HIGH);
  everswitch.sendSignal('B', 1, true);
  lighted = true;
}

void turnLightOff() {
  Serial.println("Turn light off");
  digitalWrite(ledPin, LOW);
  everswitch.sendSignal('B', 1, false);
  lighted = false;
}
