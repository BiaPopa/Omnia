// Arduino code generated from .st file

#include <timers.h>
#include <counters.h>
#include <triggers.h>
#include "esp_heap_caps.h" 
#include <Arduino.h>

#define INPUT1_GPIO 17
#define INPUT2_GPIO 4
#define RESET_GPIO 21
#define OUTPUT1_GPIO 2
#define OUTPUT2_GPIO 15

unsigned long activeTime = 0;
unsigned long lastSecond = millis();
unsigned long latency;
unsigned long start;

bool press = 0;
bool led_on = 0;

unsigned long counter = 0;

TON TON0;
TOF TOF0;
CTU CTU0;
TP TP0;
R_TRIG R_TRIG1;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  pinMode(INPUT1_GPIO, INPUT_PULLUP);
  pinMode(INPUT2_GPIO, INPUT_PULLUP);
  pinMode(RESET_GPIO, INPUT_PULLUP);
  pinMode(OUTPUT1_GPIO, OUTPUT);
  pinMode(OUTPUT2_GPIO, OUTPUT);

  TON0.PT = 500;
  TOF0.PT = 500;
  TP0.PT = 100;
  CTU0.PV = 3;
}

void loop() {
  unsigned long loopStart = micros();

  if (digitalRead(INPUT2_GPIO) == LOW) {
    counter++;
  }

  if (digitalRead(INPUT2_GPIO) == LOW && press == 0 && counter >= 3) {
    press = 1;
    start = micros();
  }

  bool input1 = (digitalRead(INPUT1_GPIO) == LOW);
  bool input2 = (digitalRead(INPUT2_GPIO) == LOW);
  bool reset = (digitalRead(RESET_GPIO) == LOW);

  TON0.IN = input1;
  TON0.update();

  TOF0.IN = TON0.Q;
  TOF0.update();

  TP0.IN = input2;
  TP0.update();

  R_TRIG1.CLK = TP0.Q;
  R_TRIG1.update();

  CTU0.CU = R_TRIG1.Q;
  CTU0.R = reset;
  CTU0.update();

  digitalWrite(OUTPUT1_GPIO, TOF0.Q ? HIGH : LOW);
  digitalWrite(OUTPUT2_GPIO, CTU0.Q ? HIGH : LOW);

  if (digitalRead(OUTPUT2_GPIO) == HIGH && led_on == 0) {
    latency = micros() - start;
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