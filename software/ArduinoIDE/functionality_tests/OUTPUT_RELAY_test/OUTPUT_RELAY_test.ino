const int ledPins[] = {10, 15, 20};

void setup() {
  Serial.begin(115200);
  delay(3000);

  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  Serial.println("Relay output test started");
}

void loop() {
  for (int i = 0; i < 3; i++) {
    Serial.print("Relay/LED on pin ");
    Serial.print(ledPins[i]);
    Serial.println(" ON");

    digitalWrite(ledPins[i], HIGH);
    delay(1000);

    Serial.print("Relay/LED on pin ");
    Serial.print(ledPins[i]);
    Serial.println(" OFF");

    digitalWrite(ledPins[i], LOW);
    delay(1000);
  }
}
