// Arduino code generated from .st file

#include <counters.h>
#include <triggers.h>
#include <comparison.h>
#include <selection.h>
#include "esp_heap_caps.h" 

#define INPUT1_GPIO 17
#define INPUT2_GPIO 4
#define OUTPUT1_GPIO 2

CTU CTU0;
CTU CTU1;
R_TRIG R_TRIG1;
R_TRIG R_TRIG2;
MAX<int> _TMP_MAX36_OUT;
LIMIT<int> _TMP_LIMIT37_OUT;
GT<int> _TMP_GT40_OUT;

unsigned long activeTime = 0;
unsigned long lastSecond = millis();
unsigned long latency;
unsigned long start = 0;

volatile bool press = 0;
volatile bool led_on = 0;

volatile unsigned long counter0 = 0;
volatile unsigned long counter1 = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  pinMode(INPUT1_GPIO, INPUT_PULLUP);
  pinMode(INPUT2_GPIO, INPUT_PULLUP);
  pinMode(OUTPUT1_GPIO, OUTPUT);

  CTU0.PV = 100;
  CTU1.PV = 100;
}

void loop() {
  unsigned long loopStart = micros();

  bool input1 = (digitalRead(INPUT1_GPIO) == LOW);
  bool input2 = (digitalRead(INPUT2_GPIO) == LOW);

  if (input1 == 1) {
    counter0++;
  }

  if (input2 == 1) {
    counter1++;
  }

  if (input1 == 1 && press == 0 && (counter0 > counter1 ? counter0 : counter1) > 2) {
    press = 1;
    start = micros();
  }

  R_TRIG1.CLK = input1;
  R_TRIG1.update();

  CTU0.CU = R_TRIG1.Q;
  CTU0.update();

  R_TRIG2.CLK = input2;
  R_TRIG2.update();

  CTU1.CU = R_TRIG2.Q;
  CTU1.update();

  _TMP_MAX36_OUT.IN1 = CTU0.CV;
  _TMP_MAX36_OUT.IN2 = CTU1.CV;
  _TMP_MAX36_OUT.update();

  _TMP_LIMIT37_OUT.MN = 1;
  _TMP_LIMIT37_OUT.IN = _TMP_MAX36_OUT.OUT;
  _TMP_LIMIT37_OUT.MX = 4;
  _TMP_LIMIT37_OUT.update();

  _TMP_GT40_OUT.IN1 = _TMP_LIMIT37_OUT.OUT;
  _TMP_GT40_OUT.IN2 = 2;
  _TMP_GT40_OUT.update();

  digitalWrite(OUTPUT1_GPIO, _TMP_GT40_OUT.OUT ? HIGH : LOW);

  if (digitalRead(OUTPUT1_GPIO) == 1 && led_on == 0) {
    unsigned long end = micros();
    latency = end - start;
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