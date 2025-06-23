#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <RTClib.h>

#define SDA_PIN 22
#define SCL_PIN 23
#define RTC_INT_PIN 4
#define ADC_PIN 5

const int muxSelectPins[] = {1, 8, 11};  
const int relayPins[] = {10, 15, 20};

const char* ssid = "Vodafone-65E7";
const char* password = "ER7kdfrkdxs7b8pm";

const char* remote_ip = "172.19.41.178";  
const int remote_port = 4210;

RTC_DS3231 rtc;
WiFiUDP udp;

volatile bool rtcInterrupt = false;

void IRAM_ATTR rtcInterruptHandler() {
  rtcInterrupt = true;
}

void setup() {
  Serial.begin(115200);
  delay(3000);

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("WiFi connected.");

  for (int i = 0; i < 3; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH);  
  }

  for (int i = 0; i < 3; i++) 
    pinMode(muxSelectPins[i], OUTPUT);

  digitalWrite(muxSelectPins[0], 1);
  digitalWrite(muxSelectPins[1], 1);
  digitalWrite(muxSelectPins[2], 0);

  analogReadResolution(8);
  pinMode(ADC_PIN, INPUT);

  pinMode(RTC_INT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RTC_INT_PIN), rtcInterruptHandler, FALLING);

  Wire.begin(SDA_PIN, SCL_PIN);

  if (!rtc.begin()) {
    Serial.println("RTC not found!");
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
  udp.beginPacket(remote_ip, remote_port);
  udp.print("TX test ESP32");
  udp.endPacket();

  if (rtcInterrupt) {
    rtcInterrupt = false;
    rtc.clearAlarm(1);

    int analogVal = analogRead(ADC_PIN);
    Serial.print("[RTC] Interrupt: value = ");
    Serial.println(analogVal);

    DateTime now = rtc.now();
    int next_sec = ((now.second() / 10) + 1) * 10 % 60;
    DateTime alarmTime(now.year(), now.month(), now.day(), now.hour(), now.minute(), next_sec);
    rtc.setAlarm1(alarmTime, DS3231_A1_Second);
  }
}
