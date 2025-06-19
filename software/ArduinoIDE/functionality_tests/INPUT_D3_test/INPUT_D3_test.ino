const int muxSelectPins[] = {1, 8, 11};  
const int muxInputPin = 5;  

void setup() {
  Serial.begin(115200);
  delay(3000);

  for (int i = 0; i < 3; i++) 
    pinMode(muxSelectPins[i], OUTPUT);
  pinMode(muxInputPin, INPUT); 
  
  digitalWrite(muxSelectPins[0], 0);
  digitalWrite(muxSelectPins[1], 1);
  digitalWrite(muxSelectPins[2], 0);

  Serial.println("Test D3 started");
}

void loop() {
  int val = digitalRead(muxInputPin);

  Serial.print("D3: ");
  Serial.println(val ? "HIGH" : "LOW");

  delay(500);
}
