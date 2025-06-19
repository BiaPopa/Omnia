const int muxSelectPins[] = {1, 8, 11};  
const int muxInput = 5;

void setup() {
  Serial.begin(115200);
  delay(3000);

  for (int i = 0; i < 3; i++) 
    pinMode(muxSelectPins[i], OUTPUT);
  pinMode(muxInput, INPUT);

  Serial.println("MUX input test started");
}

void loop() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(muxSelectPins[0], bitRead(i, 0));
    digitalWrite(muxSelectPins[1], bitRead(i, 1));
    digitalWrite(muxSelectPins[2], bitRead(i, 2));
    delay(5); 

    Serial.print("MUX sel ");
    Serial.print(i);
    Serial.print(": ");

    if (i <= 2) {
      int val = digitalRead(muxInput);
      Serial.print("D");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(val ? "HIGH" : "LOW");
    } else {
      int val = analogRead(muxInput);
      Serial.print("A");
      Serial.print(i - 2);
      Serial.print(": ");
      Serial.println(val);
    }

    delay(500);
  }
}
