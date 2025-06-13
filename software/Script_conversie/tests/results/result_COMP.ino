// Arduino code generated from .st file

#include <counters.h>
#include <triggers.h>
#include <comparison.h>

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
GT<int> _TMP_GT28_OUT;
LT<bool> _TMP_LT31_OUT;

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

  _TMP_GT28_OUT.IN1 = CTU0.CV;
  _TMP_GT28_OUT.IN2 = CTU1.CV;
  _TMP_GT28_OUT.update();

  _TMP_LT31_OUT.IN1 = reset;
  _TMP_LT31_OUT.IN2 = load;
  _TMP_LT31_OUT.update();

  digitalWrite(OUTPUT1_GPIO, _TMP_GT28_OUT.OUT ? HIGH : LOW);
  digitalWrite(OUTPUT2_GPIO, _TMP_LT31_OUT.OUT ? HIGH : LOW);

  delay(100);
}