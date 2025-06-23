// Arduino code generated from .st file

#include <counters.h>
#include "esp_heap_caps.h"
#include <Arduino.h>

#define INPUT_UP_GPIO 17
#define INPUT_DOWN_GPIO 4
#define RESET_GPIO 21
#define LOAD_GPIO 22
#define OUTPUT_UP_GPIO 2
#define OUTPUT_DOWN_GPIO 15

CTUD CTUD0;

unsigned long activeTime = 0;
unsigned long lastSecond = millis();
unsigned long latency;

bool press = 0;
bool led_on = 0;

unsigned long counter = 0;


void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(INPUT_UP_GPIO, INPUT_PULLUP);
  pinMode(INPUT_DOWN_GPIO, INPUT_PULLUP);
  pinMode(RESET_GPIO, INPUT_PULLUP);
  pinMode(LOAD_GPIO, INPUT_PULLUP);
  pinMode(OUTPUT_UP_GPIO, OUTPUT);
  pinMode(OUTPUT_DOWN_GPIO, OUTPUT);

  CTUD0.PV = 5;
}

void loop() {
  unsigned long loopStart = micros();
  unsigned long start;

  if (digitalRead(INPUT_UP_GPIO) == LOW) {
    counter++;
  }

  if (digitalRead(INPUT_DOWN_GPIO) == LOW) {
    counter--;
  }

  if (digitalRead(INPUT_UP_GPIO) == LOW && press == 0 && counter >= 5) {
    press = 1;
    start = micros();
  }

  bool input_up = (digitalRead(INPUT_UP_GPIO) == LOW);
  bool input_down = (digitalRead(INPUT_DOWN_GPIO) == LOW);
  bool reset = (digitalRead(RESET_GPIO) == LOW);
  bool load = (digitalRead(LOAD_GPIO) == LOW);

  CTUD0.CU = input_up;
  CTUD0.CD = input_down;
  CTUD0.R = reset;
  CTUD0.LD = load;
  CTUD0.update();

  digitalWrite(OUTPUT_UP_GPIO, CTUD0.QU ? HIGH : LOW);
  digitalWrite(OUTPUT_DOWN_GPIO, CTUD0.QD ? HIGH : LOW);

  if (digitalRead(OUTPUT_UP_GPIO) == 1 && led_on == 0 && press == 1) {
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
