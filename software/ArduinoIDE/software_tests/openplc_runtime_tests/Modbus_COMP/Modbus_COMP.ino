#include <WiFi.h>
#include <ModbusIP_ESP8266.h>
#include "esp_heap_caps.h"
#include <Arduino.h>

#define INPUT1_GPIO 17
#define INPUT2_GPIO 4
#define RESET_GPIO 21
#define LOAD_GPIO 22
#define OUTPUT1_GPIO 2
#define OUTPUT2_GPIO 15

const char* ssid = "Vodafone-65E7";
const char* password = "ER7kdfrkdxs7b8pm";

WiFiClient client;
ModbusIP mb;

unsigned long activeTime = 0;
unsigned long lastSecond = millis();
unsigned long latency = 0;

bool press = 0;
bool led_on = 0;

unsigned long counter0 = 0;
unsigned long counter1 = 0;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());

  mb.server();
  Serial.println("Modbus TCP Server started");

  mb.addCoil(0);
  mb.addCoil(1);

  mb.addIsts(0);
  mb.addIsts(1);
  mb.addIsts(2);
  mb.addIsts(3);

  pinMode(INPUT1_GPIO, INPUT_PULLUP);
  pinMode(INPUT2_GPIO, INPUT_PULLUP);
  pinMode(RESET_GPIO, INPUT_PULLUP);
  pinMode(LOAD_GPIO, INPUT_PULLUP);
  pinMode(OUTPUT1_GPIO, OUTPUT);
  pinMode(OUTPUT2_GPIO, OUTPUT);
}

void loop() {
  unsigned long loopStart = micros();
  unsigned long start;

  mb.task();

  if (digitalRead(INPUT1_GPIO) == LOW) {
    counter0++;
  }

  if (digitalRead(INPUT2_GPIO) == LOW) {
    counter1++;
  }

  if (digitalRead(INPUT1_GPIO) == LOW && press == 0 && counter0 > counter1) {
    press = 1;
    start = millis();
  } 
  
  bool input1 = (digitalRead(INPUT1_GPIO) == LOW);
  bool input2 = (digitalRead(INPUT2_GPIO) == LOW);
  bool reset = (digitalRead(RESET_GPIO) == LOW);
  bool load = (digitalRead(LOAD_GPIO) == LOW);

  mb.Ists(0, input1);
  mb.Ists(1, input2);
  mb.Ists(2, reset);
  mb.Ists(3, load);

  if (mb.Coil(0) == 1 && led_on == 0) {
    unsigned long latency = millis() - start;
    led_on = 1;

    Serial.print("Latenta OUTPUT: ");
    Serial.print(latency);
    Serial.println(" ms");
  }

  digitalWrite(OUTPUT1_GPIO, mb.Coil(0));
  digitalWrite(OUTPUT2_GPIO, mb.Coil(1));

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
