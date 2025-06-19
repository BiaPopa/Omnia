const int muxSelectPins[] = {1, 8, 11};  
const int muxInputPin = 5;             

void setup() {
  Serial.begin(115200);
  delay(3000);

  for (int i = 0; i < 3; i++) 
    pinMode(muxSelectPins[i], OUTPUT);
  pinMode(muxInputPin, INPUT);  
  
  Serial.println("Analog input test started");
}

void loop() {
  for (int i = 3; i <= 5; i++) {
    digitalWrite(muxSelectPins[0], bitRead(i, 0));
    digitalWrite(muxSelectPins[1], bitRead(i, 1));
    digitalWrite(muxSelectPins[2], bitRead(i, 2));
    delay(5);  

    int val = analogRead(muxInputPin);
    Serial.print("A");
    Serial.print(i - 2);
    Serial.print(": ");
    Serial.println(val);

    delay(500);
  }
}
