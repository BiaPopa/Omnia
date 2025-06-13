// Arduino code generated from .st file

#include <counters.h>

#define INPUT_UP_GPIO 17
#define INPUT_DOWN_GPIO 0
#define RESET_GPIO 21
#define LOAD_GPIO 22
#define OUTPUT_UP_GPIO 10
#define OUTPUT_DOWN_GPIO 15

CTUD CTUD0;

void setup() {
  pinMode(INPUT_UP_GPIO, INPUT_PULLUP);
  pinMode(INPUT_DOWN_GPIO, INPUT_PULLUP);
  pinMode(RESET_GPIO, INPUT_PULLUP);
  pinMode(LOAD_GPIO, INPUT_PULLUP);
  pinMode(OUTPUT_UP_GPIO, OUTPUT);
  pinMode(OUTPUT_DOWN_GPIO, OUTPUT);

  CTUD0.PV = 5;
}

void loop() {
  bool input_up = (digitalRead(INPUT_UP_GPIO) == LOW);
  bool input_down = (digitalRead(INPUT_DOWN_GPIO) == LOW);
  bool reset = (digitalRead(RESET_GPIO) == LOW);
  bool load = (digitalRead(LOAD_GPIO) == LOW);

  CTUD0.CU = input_up;
  CTUD0.CD = input_down;
  CTUD0.R = reset;
  CTUD0.LD = load;
  CTUD0.update();

  digitalWrite(OUTPUT_UP_GPIO, CTUD0.QU ? HIGH : LOW);
  digitalWrite(OUTPUT_DOWN_GPIO, CTUD0.QD ? HIGH : LOW);

  delay(100);
}