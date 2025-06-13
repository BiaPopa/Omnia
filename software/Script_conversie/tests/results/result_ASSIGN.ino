// Arduino code generated from .st file

#define INPUT1_GPIO 17
#define INPUT2_GPIO 0
#define OUTPUT1_GPIO 10
#define OUTPUT2_GPIO 15


void setup() {
  pinMode(INPUT1_GPIO, INPUT_PULLUP);
  pinMode(INPUT2_GPIO, INPUT_PULLUP);
  pinMode(OUTPUT1_GPIO, OUTPUT);
  pinMode(OUTPUT2_GPIO, OUTPUT);

}

void loop() {
  bool input1 = (digitalRead(INPUT1_GPIO) == LOW);
  bool input2 = (digitalRead(INPUT2_GPIO) == LOW);

  digitalWrite(OUTPUT1_GPIO, input1 ? HIGH : LOW);
  digitalWrite(OUTPUT2_GPIO, input2 ? HIGH : LOW);

  delay(100);
}