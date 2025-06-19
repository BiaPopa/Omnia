const int ledPins[] = {9, 18, 19};

void setup() {
  Serial.begin(115200);
  delay(3000);

  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  Serial.println("LED output test started");
}

void loop() {
  for (int i = 0; i < 3; i++) {
    Serial.print("LED on pin ");
    Serial.print(ledPins[i]);
    Serial.println(" ON");

    digitalWrite(ledPins[i], HIGH);
    delay(1000);

    Serial.print("LED on pin ");
    Serial.print(ledPins[i]);
    Serial.println(" OFF");

    digitalWrite(ledPins[i], LOW);
    delay(1000);
  }
}
