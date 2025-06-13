// Arduino code generated from .st file

#include <bitwise.h>

#define INPUT1_GPIO 17
#define INPUT2_GPIO 0
#define RESET_GPIO 21
#define LOAD_GPIO 22
#define OUTPUT1_GPIO 10
#define OUTPUT2_GPIO 15
#define OUTPUT3_GPIO 19
#define OUTPUT4_GPIO 18

AND _TMP_AND42_OUT;
XOR _TMP_XOR43_OUT;
OR _TMP_OR44_OUT;
NOT _TMP_NOT45_OUT;

void setup() {
  pinMode(INPUT1_GPIO, INPUT_PULLUP);
  pinMode(INPUT2_GPIO, INPUT_PULLUP);
  pinMode(RESET_GPIO, INPUT_PULLUP);
  pinMode(LOAD_GPIO, INPUT_PULLUP);
  pinMode(OUTPUT1_GPIO, OUTPUT);
  pinMode(OUTPUT2_GPIO, OUTPUT);
  pinMode(OUTPUT3_GPIO, OUTPUT);
  pinMode(OUTPUT4_GPIO, OUTPUT);

}

void loop() {
  bool input1 = (digitalRead(INPUT1_GPIO) == LOW);
  bool input2 = (digitalRead(INPUT2_GPIO) == LOW);
  bool reset = (digitalRead(RESET_GPIO) == LOW);
  bool load = (digitalRead(LOAD_GPIO) == LOW);

  _TMP_AND42_OUT.IN1 = input1;
  _TMP_AND42_OUT.IN2 = input2;
  _TMP_AND42_OUT.update();

  _TMP_XOR43_OUT.IN1 = reset;
  _TMP_XOR43_OUT.IN2 = load;
  _TMP_XOR43_OUT.update();

  _TMP_OR44_OUT.IN1 = _TMP_AND42_OUT.OUT;
  _TMP_OR44_OUT.IN2 = _TMP_XOR43_OUT.OUT;
  _TMP_OR44_OUT.update();

  _TMP_NOT45_OUT.IN = _TMP_OR44_OUT.OUT;
  _TMP_NOT45_OUT.update();

  digitalWrite(OUTPUT1_GPIO, _TMP_NOT45_OUT.OUT ? HIGH : LOW);

  delay(100);
}