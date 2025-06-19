#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "Vodafone-65E7";
const char* password = "ER7kdfrkdxs7b8pm";

WiFiUDP udp;
const int localPort = 4210;

char incomingPacket[255];

void setup() {
  Serial.begin(115200);
  delay(3000);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  udp.begin(localPort);
  Serial.print("Listening for UDP packets on port ");
  Serial.println(localPort);
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = '\0';  
      Serial.print("Received UDP packet: ");
      Serial.println(incomingPacket);
    }
  }
}
