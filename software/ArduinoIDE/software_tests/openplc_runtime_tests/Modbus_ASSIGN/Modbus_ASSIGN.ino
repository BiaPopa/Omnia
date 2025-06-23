#include <WiFi.h>
#include <ModbusIP_ESP8266.h> 
#include "esp_heap_caps.h"

#define LED1_GPIO 2
#define LED2_GPIO 15

#define INPUT1_GPIO 17
#define INPUT2_GPIO 4

const char* ssid = "Vodafone-65E7";
const char* password = "ER7kdfrkdxs7b8pm";

WiFiClient client;
ModbusIP mb;

unsigned long activeTime = 0;
unsigned long lastSecond = millis();
unsigned long latency;

bool press = 0;
bool led_on = 0;

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

  pinMode(LED1_GPIO, OUTPUT);
  pinMode(LED2_GPIO, OUTPUT);

  pinMode(INPUT1_GPIO, INPUT_PULLUP);
  pinMode(INPUT2_GPIO, INPUT_PULLUP);
}

void loop() {
  unsigned long loopStart = micros(); 
  unsigned long start;
  
  mb.task();

  if (digitalRead(INPUT1_GPIO) == LOW && press == 0) {
    press = 1;
    start = millis();
  }
  
  bool in1 = (digitalRead(INPUT1_GPIO) == LOW);
  mb.Ists(0, in1);
  digitalWrite(LED1_GPIO, mb.Coil(0));
  
  bool in2 = (digitalRead(INPUT2_GPIO) == LOW);
  mb.Ists(1, in2);
  digitalWrite(LED2_GPIO, mb.Coil(1));

  if (mb.Coil(0) == 1 && led_on == 0) {
    unsigned long end = millis();
    latency = end - start;
    led_on = 1;

    Serial.print("Latenta OUTPUT: ");
    Serial.print(latency);
    Serial.println(" ms");
  } 

  unsigned long loopEnd = micros();
  activeTime += (loopEnd - loopStart);

  if (millis() - lastSecond >= 1000) {
    Serial.print("RAM libera: ");
    Serial.print(esp_get_free_heap_size());
    Serial.println(" bytes");

    float cpuUsage = (float)activeTime / 10000.0;
    Serial.print("CPU usage estimat: ");
    Serial.print(cpuUsage, 2);
    Serial.println(" %");

    activeTime = 0;
    lastSecond = millis();
  }

  delay(100);
}