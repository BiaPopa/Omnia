#define LED 18

void setup() {
  Serial.begin(115200);  
  delay(3000);

  pinMode(LED, OUTPUT);

  Serial.println("USB Test: connection successful");
  Serial.println("Type 'ON' or 'OFF' in the terminal");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim(); 
    
    if (command == "ON") {
      Serial.println("LED ON");
      digitalWrite(LED, HIGH);
    } else if (command == "OFF") {
      Serial.println("LED OFF");
      digitalWrite(LED, LOW);
    } else {
      Serial.println("Unknown command");
    }
  }
}
