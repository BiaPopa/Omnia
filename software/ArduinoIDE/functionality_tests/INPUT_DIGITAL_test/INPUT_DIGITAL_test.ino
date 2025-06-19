const int muxSelectPins[] = {1, 8, 11};  
const int muxInputPin = 5;        

void setup() {
  Serial.begin(115200);
  delay(3000);

  for (int i = 0; i < 3; i++) 
    pinMode(muxSelectPins[i], OUTPUT);
  pinMode(muxInputPin, INPUT);

  Serial.println("Digital input test started");
}

void loop() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(muxSelectPins[0], bitRead(i, 0));
    digitalWrite(muxSelectPins[1], bitRead(i, 1));
    digitalWrite(muxSelectPins[2], bitRead(i, 2));
    delay(5);  

    int val = digitalRead(muxInputPin);
    Serial.print("D");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(val ? "HIGH" : "LOW");

    delay(500);
  }
}
