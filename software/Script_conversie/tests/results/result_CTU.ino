// Arduino code generated from .st file

#include <timers.h>
#include <counters.h>
#include <triggers.h>

#define INPUT1_GPIO 17
#define INPUT2_GPIO 0
#define RESET_GPIO 21
#define OUTPUT1_GPIO 10
#define OUTPUT2_GPIO 15

TON TON0;
TOF TOF0;
CTU CTU0;
TP TP0;
R_TRIG R_TRIG1;

void setup() {
  pinMode(INPUT1_GPIO, INPUT_PULLUP);
  pinMode(INPUT2_GPIO, INPUT_PULLUP);
  pinMode(RESET_GPIO, INPUT_PULLUP);
  pinMode(OUTPUT1_GPIO, OUTPUT);
  pinMode(OUTPUT2_GPIO, OUTPUT);

  TON0.PT = 500;
  TOF0.PT = 500;
  TP0.PT = 100;
  CTU0.PV = 7;
}

void loop() {
  bool input1 = (digitalRead(INPUT1_GPIO) == LOW);
  bool input2 = (digitalRead(INPUT2_GPIO) == LOW);
  bool reset = (digitalRead(RESET_GPIO) == LOW);

  TON0.IN = input1;
  TON0.update();

  TOF0.IN = TON0.Q;
  TOF0.update();

  TP0.IN = input2;
  TP0.update();

  R_TRIG1.CLK = TP0.Q;
  R_TRIG1.update();

  CTU0.CU = R_TRIG1.Q;
  CTU0.R = reset;
  CTU0.update();

  digitalWrite(OUTPUT1_GPIO, TOF0.Q ? HIGH : LOW);
  digitalWrite(OUTPUT2_GPIO, CTU0.Q ? HIGH : LOW);

  delay(100);
}