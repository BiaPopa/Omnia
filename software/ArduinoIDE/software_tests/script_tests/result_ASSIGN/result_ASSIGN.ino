// Arduino code generated from .st file

#define INPUT1_GPIO 17
#define INPUT2_GPIO 4
#define OUTPUT1_GPIO 2
#define OUTPUT2_GPIO 15

#include "esp_heap_caps.h" 

unsigned long activeTime = 0;
unsigned long lastSecond = millis();
unsigned long latency;

bool press = 0;
bool led_on = 0;

void setup() {
  pinMode(INPUT1_GPIO, INPUT_PULLUP);
  pinMode(INPUT2_GPIO, INPUT_PULLUP);
  pinMode(OUTPUT1_GPIO, OUTPUT);
  pinMode(OUTPUT2_GPIO, OUTPUT);

  Serial.begin(115200); 
}

void loop() {
  unsigned long loopStart = micros();
  unsigned long start;
  
  if (digitalRead(INPUT1_GPIO) == LOW && press == 0) {
    press = 1;
    start = micros();
  }

  bool input1 = (digitalRead(INPUT1_GPIO) == LOW);
  digitalWrite(OUTPUT1_GPIO, input1 ? HIGH : LOW);
  
  bool input2 = (digitalRead(INPUT2_GPIO) == LOW);
  digitalWrite(OUTPUT2_GPIO, input2 ? HIGH : LOW);
  
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
