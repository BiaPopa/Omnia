const int muxSelectPins[] = {1, 8, 11};  
const int muxInputPin = 5;  

void setup() {
  Serial.begin(115200);
  delay(3000);

  for (int i = 0; i < 3; i++) 
    pinMode(muxSelectPins[i], OUTPUT);
  pinMode(muxInputPin, INPUT); 
  
  digitalWrite(muxSelectPins[0], 0);
  digitalWrite(muxSelectPins[1], 0);
  digitalWrite(muxSelectPins[2], 1);

  Serial.println("Test A2 started");
}

void loop() {
  int val = analogRead(muxInputPin);

  Serial.print("A2: ");
  Serial.println(val);

  delay(500);
}
