// Arduino code generated from .st file

#include <bitwise.h>
#include "esp_heap_caps.h" 
#include <Arduino.h>

#define INPUT1_GPIO 17
#define INPUT2_GPIO 4
#define RESET_GPIO 21
#define LOAD_GPIO 22

#define OUTPUT1_GPIO 2

AND _TMP_AND42_OUT;
XOR _TMP_XOR43_OUT;
OR  _TMP_OR44_OUT;
NOT _TMP_NOT45_OUT;

unsigned long activeTime = 0;
unsigned long lastSecond = millis();
unsigned long latency = 0;

bool press = 0;
bool led_on = 0;

void setup() {
  pinMode(INPUT1_GPIO, INPUT_PULLUP);
  pinMode(INPUT2_GPIO, INPUT_PULLUP);
  pinMode(RESET_GPIO, INPUT_PULLUP);
  pinMode(LOAD_GPIO, INPUT_PULLUP);

  pinMode(OUTPUT1_GPIO, OUTPUT);

  Serial.begin(115200);
  delay(1000); 
}

void loop() {
  unsigned long loopStart = micros(); 
  unsigned long start; 

  bool input1 = (digitalRead(INPUT1_GPIO) == LOW);
  bool input2 = (digitalRead(INPUT2_GPIO) == LOW);
  bool reset  = (digitalRead(RESET_GPIO) == LOW);
  bool load   = (digitalRead(LOAD_GPIO) == LOW);

  if (((input1 && input2) || (reset ^ load)) && press == 0) {
    press = 1;
    start = micros();
  }

  _TMP_AND42_OUT.IN1 = input1;
  _TMP_AND42_OUT.IN2 = input2;
  _TMP_AND42_OUT.update();

  _TMP_XOR43_OUT.IN1 = reset;
  _TMP_XOR43_OUT.IN2 = load;
  _TMP_XOR43_OUT.update();

  _TMP_OR44_OUT.IN1 = _TMP_AND42_OUT.OUT;
  _TMP_OR44_OUT.IN2 = _TMP_XOR43_OUT.OUT;
  _TMP_OR44_OUT.update();

  _TMP_NOT45_OUT.IN = _TMP_OR44_OUT.OUT;
  _TMP_NOT45_OUT.update();

  digitalWrite(OUTPUT1_GPIO, _TMP_NOT45_OUT.OUT ? HIGH : LOW);

  if (digitalRead(OUTPUT1_GPIO) == LOW && led_on == 0 && press == 1) {
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