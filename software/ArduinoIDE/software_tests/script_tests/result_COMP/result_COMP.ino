// Arduino code generated from .st file

#include <counters.h>
#include <triggers.h>
#include <comparison.h>
#include "esp_heap_caps.h"
#include <Arduino.h>

#define INPUT1_GPIO 17
#define INPUT2_GPIO 4
#define RESET_GPIO 21
#define LOAD_GPIO 22
#define OUTPUT1_GPIO 2
#define OUTPUT2_GPIO 15

CTU CTU0;
CTU CTU1;
R_TRIG R_TRIG1;
R_TRIG R_TRIG2;
GT<int> _TMP_GT28_OUT;
LT<bool> _TMP_LT31_OUT;

unsigned long activeTime = 0;
unsigned long lastSecond = millis();
unsigned long latency = 0;

bool press = 0;
bool led_on = 0;

unsigned long counter0 = 0;
unsigned long counter1 = 0;


void setup() {
  pinMode(INPUT1_GPIO, INPUT_PULLUP);
  pinMode(INPUT2_GPIO, INPUT_PULLUP);
  pinMode(RESET_GPIO, INPUT_PULLUP);
  pinMode(LOAD_GPIO, INPUT_PULLUP);
  pinMode(OUTPUT1_GPIO, OUTPUT);
  pinMode(OUTPUT2_GPIO, OUTPUT);

  CTU0.PV = 100;
  CTU1.PV = 100;

  Serial.begin(115200);
  delay(1000);
}

void loop() {
  unsigned long loopStart = micros();
  unsigned long start;

  if (digitalRead(INPUT1_GPIO) == LOW) {
    counter0++;
  }

  if (digitalRead(INPUT2_GPIO) == LOW) {
    counter1++;
  }

  if (digitalRead(INPUT1_GPIO) == LOW && press == 0 && counter0 > counter1) {
    press = 1;
    start = micros();
  }

  bool input1 = (digitalRead(INPUT1_GPIO) == LOW);
  bool input2 = (digitalRead(INPUT2_GPIO) == LOW);
  bool reset = (digitalRead(RESET_GPIO) == LOW);
  bool load = (digitalRead(LOAD_GPIO) == LOW);

  R_TRIG1.CLK = input1;
  R_TRIG1.update();

  CTU0.CU = R_TRIG1.Q;
  CTU0.update();

  R_TRIG2.CLK = input2;
  R_TRIG2.update();

  CTU1.CU = R_TRIG2.Q;
  CTU1.update();

  _TMP_GT28_OUT.IN1 = CTU0.CV;
  _TMP_GT28_OUT.IN2 = CTU1.CV;
  _TMP_GT28_OUT.update();

  _TMP_LT31_OUT.IN1 = reset;
  _TMP_LT31_OUT.IN2 = load;
  _TMP_LT31_OUT.update();

  digitalWrite(OUTPUT1_GPIO, _TMP_GT28_OUT.OUT ? HIGH : LOW);
  digitalWrite(OUTPUT2_GPIO, _TMP_LT31_OUT.OUT ? HIGH : LOW);

  if (digitalRead(OUTPUT1_GPIO) == HIGH && led_on == 0) {
    unsigned long latency = micros() - start;
    led_on = 1;

    Serial.print("Latenta OUTPUT: ");
    Serial.print(latency);
    Serial.println(" us");
  } 

  unsigned long loopEnd = micros();
  activeTime += (loopEnd - loopStart);

  if (millis() - lastSecond >= 1000) {
    Serial.print("RAM libera: ");
    Serial.print(esp_get_free_heap_size());
    Serial.println(" bytes");

    float cpuUsage = (float)activeTime / 10000.0;
    Serial.print("Estimare CPU usage: ");
    Serial.print(cpuUsage, 2);
    Serial.println(" %");

    activeTime = 0;
    lastSecond = millis();
  }

  delay(100);
}
