// Arduino code generated from .st file

#include <timers.h>
#include <counters.h>
#include <triggers.h>

#define INPUT1_GPIO 17
#define INPUT2_GPIO 0
#define RESET_GPIO 21
#define LOAD_GPIO 22
#define OUTPUT1_GPIO 10
#define OUTPUT2_GPIO 15

CTU_DINT CTU_DINT0;
TP TP0;
R_TRIG R_TRIG0;
CTD_UDINT CTD_UDINT0;
R_TRIG R_TRIG1;
R_TRIG R_TRIG2;

void setup() {
  pinMode(INPUT1_GPIO, INPUT_PULLUP);
  pinMode(INPUT2_GPIO, INPUT_PULLUP);
  pinMode(RESET_GPIO, INPUT_PULLUP);
  pinMode(LOAD_GPIO, INPUT_PULLUP);
  pinMode(OUTPUT1_GPIO, OUTPUT);
  pinMode(OUTPUT2_GPIO, OUTPUT);

  CTD_UDINT0.PV = 2;
  TP0.PT = 100;
  CTU_DINT0.PV = 3;
}

void loop() {
  bool input1 = (digitalRead(INPUT1_GPIO) == LOW);
  bool input2 = (digitalRead(INPUT2_GPIO) == LOW);
  bool reset = (digitalRead(RESET_GPIO) == LOW);
  bool load = (digitalRead(LOAD_GPIO) == LOW);

  R_TRIG0.CLK = input1;
  R_TRIG0.update();

  R_TRIG1.CLK = R_TRIG0.Q;
  R_TRIG1.update();

  CTD_UDINT0.CD = R_TRIG1.Q;
  CTD_UDINT0.LD = load;
  CTD_UDINT0.update();

  TP0.IN = input2;
  TP0.update();

  R_TRIG2.CLK = TP0.Q;
  R_TRIG2.update();

  CTU_DINT0.CU = R_TRIG2.Q;
  CTU_DINT0.R = reset;
  CTU_DINT0.update();

  digitalWrite(OUTPUT1_GPIO, CTD_UDINT0.Q ? HIGH : LOW);
  digitalWrite(OUTPUT2_GPIO, CTU_DINT0.Q ? HIGH : LOW);

  delay(100);
}