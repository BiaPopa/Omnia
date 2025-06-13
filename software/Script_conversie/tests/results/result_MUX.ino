// Arduino code generated from .st file

#include <counters.h>
#include <triggers.h>
#include <comparison.h>
#include <selection.h>

#define INPUT1_GPIO 17
#define INPUT2_GPIO 0
#define RESET_GPIO 21
#define LOAD_GPIO 22
#define OUTPUT1_GPIO 10
#define OUTPUT2_GPIO 15
#define OUTPUT3_GPIO 19
#define OUTPUT4_GPIO 18

CTU CTU0;
CTU CTU1;
R_TRIG R_TRIG1;
R_TRIG R_TRIG2;
MUX<int> _TMP_MUX36_OUT;
LIMIT<int> _TMP_LIMIT37_OUT;
GT<int> _TMP_GT40_OUT;

void setup() {
  pinMode(INPUT1_GPIO, INPUT_PULLUP);
  pinMode(INPUT2_GPIO, INPUT_PULLUP);
  pinMode(RESET_GPIO, INPUT_PULLUP);
  pinMode(LOAD_GPIO, INPUT_PULLUP);
  pinMode(OUTPUT1_GPIO, OUTPUT);
  pinMode(OUTPUT2_GPIO, OUTPUT);
  pinMode(OUTPUT3_GPIO, OUTPUT);
  pinMode(OUTPUT4_GPIO, OUTPUT);

  CTU0.PV = 100;
  CTU1.PV = 100;
}

void loop() {
  bool input1 = (digitalRead(INPUT1_GPIO) == LOW);
  bool input2 = (digitalRead(INPUT2_GPIO) == LOW);
  bool reset = (digitalRead(RESET_GPIO) == LOW);
  bool load = (digitalRead(LOAD_GPIO) == LOW);

  R_TRIG1.CLK = input1;
  R_TRIG1.update();

  CTU0.CU = R_TRIG1.Q;
  CTU0.update();

  R_TRIG2.CLK = input2;
  R_TRIG2.update();

  CTU1.CU = R_TRIG2.Q;
  CTU1.update();

  _TMP_MUX36_OUT.K = 1;
  _TMP_MUX36_OUT.IN0 = CTU0.CV;
  _TMP_MUX36_OUT.IN1 = CTU1.CV;
  _TMP_MUX36_OUT.update();

  _TMP_LIMIT37_OUT.MN = 1;
  _TMP_LIMIT37_OUT.IN = _TMP_MUX36_OUT.OUT;
  _TMP_LIMIT37_OUT.MX = 4;
  _TMP_LIMIT37_OUT.update();

  _TMP_GT40_OUT.IN1 = _TMP_LIMIT37_OUT.OUT;
  _TMP_GT40_OUT.IN2 = 2;
  _TMP_GT40_OUT.update();

  digitalWrite(OUTPUT1_GPIO, _TMP_GT40_OUT.OUT ? HIGH : LOW);

  delay(100);
}