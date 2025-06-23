#include <WiFi.h>
#include <ModbusIP_ESP8266.h>
#include "esp_heap_caps.h"

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

unsigned long ist1_timer = 0;
unsigned long ist2_timer = 0;
unsigned long ist3_timer = 0;
unsigned long ist4_timer = 0;

unsigned long activeTime = 0;
unsigned long lastSecond = millis();
unsigned long latency;
unsigned long start = 0;

volatile bool press = 0;
volatile bool led_on = 0;

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

  pinMode(INPUT1_GPIO, INPUT_PULLUP);
  pinMode(INPUT2_GPIO, INPUT_PULLUP);
  pinMode(RESET_GPIO, INPUT_PULLUP);
  pinMode(LOAD_GPIO, INPUT_PULLUP);

  pinMode(OUTPUT1_GPIO, OUTPUT);
  pinMode(OUTPUT2_GPIO, OUTPUT);

  delay(100);
}

void loop() {
  unsigned long loopStart = micros();

  mb.task();

  bool input1 = (digitalRead(INPUT1_GPIO) == LOW);
  bool input2 = (digitalRead(INPUT2_GPIO) == LOW);
  bool reset  = (digitalRead(RESET_GPIO) == LOW);
  bool load   = (digitalRead(LOAD_GPIO) == LOW);

  if (input1) ist1_timer = millis();
  if (input2) ist2_timer = millis();
  if (reset)  ist3_timer = millis();
  if (load)   ist4_timer = millis();

  mb.Ists(0, millis() - ist1_timer < 500);
  mb.Ists(1, millis() - ist2_timer < 500);
  mb.Ists(2, millis() - ist3_timer < 500);
  mb.Ists(3, millis() - ist4_timer < 500);

  if (input1 == 0 && press == 0 && reset == 1) {
    press = 1;
    start = millis();
  }

  digitalWrite(OUTPUT1_GPIO, mb.Coil(0));
  digitalWrite(OUTPUT2_GPIO, mb.Coil(1));

  if (mb.Coil(1) == 1 && led_on == 0) {
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
    Serial.print("Estimare CPU usage: ");
    Serial.print(cpuUsage, 2);
    Serial.println(" %");

    activeTime = 0;
    lastSecond = millis();
  }

  delay(100);
}
