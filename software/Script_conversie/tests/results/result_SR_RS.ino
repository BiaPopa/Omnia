// Arduino code generated from .st file

#include <triggers.h>

#define INPUT1_GPIO 17
#define INPUT2_GPIO 0
#define RESET_GPIO 21
#define LOAD_GPIO 22
#define OUTPUT1_GPIO 10
#define OUTPUT2_GPIO 15

SR SR0;
RS RS0;

void setup() {
  pinMode(INPUT1_GPIO, INPUT_PULLUP);
  pinMode(INPUT2_GPIO, INPUT_PULLUP);
  pinMode(RESET_GPIO, INPUT_PULLUP);
  pinMode(LOAD_GPIO, INPUT_PULLUP);
  pinMode(OUTPUT1_GPIO, OUTPUT);
  pinMode(OUTPUT2_GPIO, OUTPUT);

}

void loop() {
  bool input1 = (digitalRead(INPUT1_GPIO) == LOW);
  bool input2 = (digitalRead(INPUT2_GPIO) == LOW);
  bool reset = (digitalRead(RESET_GPIO) == LOW);
  bool load = (digitalRead(LOAD_GPIO) == LOW);

  SR0.S1 = input1;
  SR0.R = reset;
  SR0.update();

  RS0.S = input2;
  RS0.R1 = load;
  RS0.update();

  digitalWrite(OUTPUT1_GPIO, SR0.Q1 ? HIGH : LOW);
  digitalWrite(OUTPUT2_GPIO, RS0.Q1 ? HIGH : LOW);

  delay(100);
}