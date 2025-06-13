#include <Wire.h>

#define SENSOR_PIN A0

void logValue(int value) {
  Serial.print("Sensor: ");
  Serial.println(value);
}

void setup() {
  Serial.begin(115200);
  delay(3000);
}

void loop() {
  int val = analogRead(SENSOR_PIN);
  logValue(val);
}
