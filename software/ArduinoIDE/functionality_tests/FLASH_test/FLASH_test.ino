#include <SPIMemory.h>
#define FLASH_CS 21

SPIFlash flash(FLASH_CS);

struct SensorData {
  uint16_t id;
  float temperature;
  int32_t pressure;
  bool active;
};

void setup() {
  Serial.begin(115200);
  delay(3000);

  SPI.begin(6, 2, 7); 

  if (!flash.begin()) {
    Serial.println("Flash not detected");
    return;
  }

  Serial.println("Flash detected");

  // Test 1: BYTE
  uint8_t byteToWrite = 42;
  uint8_t byteRead = 0;
  flash.writeByte(0x0000, byteToWrite);
  byteRead = flash.readByte(0x0000);
  Serial.print("Byte test: "); Serial.println(byteRead == byteToWrite ? "PASS" : "FAIL");

  // Test 2: INT
  int16_t intToWrite = -32000;
  int16_t intRead = 0;
  flash.writeShort(0x0010, intToWrite);
  intRead = flash.readShort(0x0010);
  Serial.print("Int16 test: "); Serial.println(intRead == intToWrite ? "PASS" : "FAIL");

  // Test 3: FLOAT
  float floatToWrite = 3.1415;
  float floatRead = 0;
  flash.writeFloat(0x0020, floatToWrite);
  floatRead = flash.readFloat(0x0020);
  Serial.print("Float test: "); Serial.println(abs(floatRead - floatToWrite) < 0.0001 ? "PASS" : "FAIL");

  // Test 4: STRING
  String text = "ESP32-C6 FLASH OK";
  String textRead = "";
  flash.writeStr(0x0030, text);
  flash.readStr(0x0030, textRead);
  Serial.print("String test: "); Serial.println(textRead == text ? "PASS" : "FAIL");

  // Test 5: STRUCT
  SensorData s1 = {1001, 25.5, 101325, true};
  SensorData s2;
  flash.writeAnything(0x0100, s1);
  flash.readAnything(0x0100, s2);

  bool structPass = (s1.id == s2.id && abs(s1.temperature - s2.temperature) < 0.001 &&
                     s1.pressure == s2.pressure && s1.active == s2.active);

  Serial.print("Struct test: "); Serial.println(structPass ? "PASS" : "FAIL");
}

void loop() {}
