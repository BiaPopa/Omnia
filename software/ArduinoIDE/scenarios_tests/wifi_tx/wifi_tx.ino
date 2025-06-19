#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "Vodafone-65E7";
const char* password = "ER7kdfrkdxs7b8pm";

const char* remoteIP = "172.19.41.178"; 
const int remotePort = 4210;

WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  delay(3000);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("Connected!");
  udp.begin(4211);  
}

void loop() {
  udp.beginPacket(remoteIP, remotePort);
  udp.print("ESP32 TX active packet");
  udp.endPacket();

  Serial.println("Packet sent");
  delay(500); 
}
