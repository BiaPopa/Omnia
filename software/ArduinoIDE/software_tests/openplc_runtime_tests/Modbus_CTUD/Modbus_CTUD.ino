// Arduino code generated from .st file

#include "esp_heap_caps.h"
#include <Arduino.h>
#include <WiFi.h>
#include <ModbusIP_ESP8266.h>

#define INPUT_UP_GPIO 17
#define INPUT_DOWN_GPIO 4
#define RESET_GPIO 21
#define LOAD_GPIO 22
#define OUTPUT_UP_GPIO 2
#define OUTPUT_DOWN_GPIO 15

const char* ssid = "Vodafone-65E7";
const char* password = "ER7kdfrkdxs7b8pm";

WiFiClient client;
ModbusIP mb;

unsigned long activeTime = 0;
unsigned long lastSecond = millis();
unsigned long latency;
unsigned long start;

bool press = 0;
bool led_on = 0;
unsigned long counter = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);

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

  pinMode(INPUT_UP_GPIO, INPUT_PULLUP);
  pinMode(INPUT_DOWN_GPIO, INPUT_PULLUP);
  pinMode(RESET_GPIO, INPUT_PULLUP);
  pinMode(LOAD_GPIO, INPUT_PULLUP);
  pinMode(OUTPUT_UP_GPIO, OUTPUT);
  pinMode(OUTPUT_DOWN_GPIO, OUTPUT);
}

void loop() {
  unsigned long loopStart = micros();
  mb.task();

  if (digitalRead(INPUT_UP_GPIO) == LOW) {
    counter++;
  }

  if (digitalRead(INPUT_DOWN_GPIO) == LOW) {
    counter--;
  }

  if (digitalRead(INPUT_UP_GPIO) == LOW && press == 0 && counter >= 5) {
    press = 1;
    start = millis();
  }

  bool input_up = (digitalRead(INPUT_UP_GPIO) == LOW);
  bool input_down = (digitalRead(INPUT_DOWN_GPIO) == LOW);
  bool reset = (digitalRead(RESET_GPIO) == LOW);
  bool load = (digitalRead(LOAD_GPIO) == LOW);

  mb.Ists(0, input_up);
  mb.Ists(1, input_down);
  mb.Ists(2, reset);
  mb.Ists(3, load);

  digitalWrite(OUTPUT_UP_GPIO, mb.Coil(0));
  digitalWrite(OUTPUT_DOWN_GPIO, mb.Coil(1));

  if (mb.Coil(0) == 1 && led_on == 0 && press == 1) {
    latency = millis() - start;
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
