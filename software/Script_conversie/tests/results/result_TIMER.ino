// Arduino code generated from .st file

#include <timers.h>

#define INPUT1_GPIO 17
#define INPUT2_GPIO 0
#define OUTPUT1_GPIO 10
#define OUTPUT2_GPIO 15

TON TON0;
TOF TOF0;

void setup() {
  pinMode(INPUT1_GPIO, INPUT_PULLUP);
  pinMode(INPUT2_GPIO, INPUT_PULLUP);
  pinMode(OUTPUT1_GPIO, OUTPUT);
  pinMode(OUTPUT2_GPIO, OUTPUT);

  TON0.PT = 500;
  TOF0.PT = 550;
}

void loop() {
  bool input1 = (digitalRead(INPUT1_GPIO) == LOW);
  bool input2 = (digitalRead(INPUT2_GPIO) == LOW);

  TON0.IN = input1;
  TON0.update();

  TOF0.IN = TON0.Q;
  TOF0.update();

  digitalWrite(OUTPUT1_GPIO, TOF0.Q ? HIGH : LOW);
  digitalWrite(OUTPUT2_GPIO, input2 ? HIGH : LOW);

  delay(100);
}