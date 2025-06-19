#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;
volatile bool alarmTriggered = false;

void IRAM_ATTR onAlarmInterrupt() {
  alarmTriggered = true;
}

void setup() {
  Serial.begin(115200);
  delay(3000);

  Wire.begin(22, 23);  

  pinMode(4, INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(4), onAlarmInterrupt, FALLING);

  if (!rtc.begin()) {
    Serial.println("RTC not found");
    while (true);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting default time...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  rtc.writeSqwPinMode(DS3231_OFF);
  rtc.clearAlarm(1);
  rtc.clearAlarm(2);

  DateTime now = rtc.now();
  int next_sec = ((now.second() / 10) + 1) * 10 % 60;
  DateTime alarmTime(now.year(), now.month(), now.day(), now.hour(), now.minute(), next_sec);
  rtc.setAlarm1(alarmTime, DS3231_A1_Second);

  Serial.println("Alarm set every 10 seconds");
}

void loop() {
  if (alarmTriggered) {
    alarmTriggered = false;
    rtc.clearAlarm(1); 

    Serial.println("Alarm triggered");

    DateTime now = rtc.now();
    int next_sec = ((now.second() / 10) + 1) * 10 % 60;
    DateTime alarmTime(now.year(), now.month(), now.day(), now.hour(), now.minute(), next_sec);
    rtc.setAlarm1(alarmTime, DS3231_A1_Second);
  }
}
