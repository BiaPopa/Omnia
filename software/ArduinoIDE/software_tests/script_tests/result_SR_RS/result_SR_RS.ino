// Arduino code generated from .st file

#include <triggers.h>
#include "esp_heap_caps.h" 

#define INPUT1_GPIO 17
#define INPUT2_GPIO 4
#define RESET_GPIO 21
#define LOAD_GPIO 22
#define OUTPUT1_GPIO 2
#define OUTPUT2_GPIO 15

SR SR0;
RS RS0;

unsigned long activeTime = 0;
unsigned long lastSecond = millis();
unsigned long latency;
unsigned long start = 0;

volatile bool press = 0;
volatile bool led_on = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  pinMode(INPUT1_GPIO, INPUT_PULLUP);
  pinMode(INPUT2_GPIO, INPUT_PULLUP);
  pinMode(RESET_GPIO, INPUT_PULLUP);
  pinMode(LOAD_GPIO, INPUT_PULLUP);
  pinMode(OUTPUT1_GPIO, OUTPUT);
  pinMode(OUTPUT2_GPIO, OUTPUT);

}

void loop() {
  unsigned long loopStart = micros();

  bool input1 = (digitalRead(INPUT1_GPIO) == LOW);
  bool input2 = (digitalRead(INPUT2_GPIO) == LOW);
  bool reset = (digitalRead(RESET_GPIO) == LOW);
  bool load = (digitalRead(LOAD_GPIO) == LOW);

  if (input1 == 1 && press == 0) {
    press = 1;
    start = micros();
  }

  SR0.S = input1;
  SR0.R = reset;
  SR0.update();

  RS0.S = input2;
  RS0.R = load;
  RS0.update();

  digitalWrite(OUTPUT1_GPIO, SR0.Q ? HIGH : LOW);
  digitalWrite(OUTPUT2_GPIO, RS0.Q ? HIGH : LOW);

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