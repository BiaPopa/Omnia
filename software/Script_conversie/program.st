PROGRAM blinky
  VAR
    input1 AT %IX0.0 : BOOL := TRUE;
    input2 AT %IX0.1 : BOOL := FALSE;
    input3 AT %IX0.2 : BOOL := TRUE;
    input4 AT %IW0 : INT := 2000;
    input5 AT %IX0.3 : BOOL := TRUE;
    input6 AT %IX0.4 : BOOL := FALSE;
    output1 AT %QX0.0 : BOOL;
    output2 AT %QX0.1 : BOOL;
    output3 AT %QX0.2 : BOOL;
    output4 AT %QX0.3 : BOOL;
    output5 AT %QX0.4 : BOOL;
    output6 AT %QX0.5 : BOOL;
  END_VAR
  VAR
    R_TRIG0 : R_TRIG;
    toggle1 : BOOL := FALSE;
    counterVal : INT := 0;
    R_TRIG1 : R_TRIG;
    CTU0 : CTU;
    TON0 : TON;
    TON1 : TON;
    TOF0 : TOF;
    TOF1 : TOF;
    _TMP_EQ10_OUT : BOOL;
    _TMP_SEL62_OUT : BOOL;
    _TMP_XOR40_OUT : BOOL;
    _TMP_EQ3_OUT : BOOL;
    _TMP_SEL63_OUT : BOOL;
    R_TRIG2 : R_TRIG;
    _TMP_GT58_OUT : BOOL;
    _TMP_EQ6_OUT : BOOL;
    _TMP_LT64_OUT : BOOL;
    _TMP_SEL77_OUT : BOOL;
    _TMP_GE14_OUT : BOOL;
    _TMP_LT20_OUT : BOOL;
    _TMP_AND70_OUT : BOOL;
    _TMP_GE71_OUT : BOOL;
  END_VAR

  _TMP_EQ10_OUT := EQ(counterVal, 1);
  _TMP_SEL62_OUT := SEL(input6, toggle1, _TMP_EQ10_OUT);
  output1 := _TMP_SEL62_OUT;
  R_TRIG0(CLK := NOT(input1));
  _TMP_XOR40_OUT := XOR(R_TRIG0.Q, toggle1);
  toggle1 := _TMP_XOR40_OUT;
  _TMP_EQ3_OUT := EQ(counterVal, 2);
  _TMP_SEL63_OUT := SEL(input6, NOT(input2), _TMP_EQ3_OUT);
  output2 := _TMP_SEL63_OUT;
  R_TRIG1(CLK := NOT(input3));
  R_TRIG2(CLK := R_TRIG1.Q);
  _TMP_GT58_OUT := GT(counterVal, 3);
  CTU0(CU := R_TRIG2.Q, R := _TMP_GT58_OUT, PV := 4);
  counterVal := CTU0.CV;
  _TMP_EQ6_OUT := EQ(counterVal, 3);
  output3 := _TMP_EQ6_OUT;
  _TMP_LT64_OUT := LT(input4, 1000);
  TON0(EN := _TMP_LT64_OUT, IN := NOT(output4), PT := T#200ms);
  TOF0(EN := TON0.ENO, IN := TON0.Q, PT := T#200ms);
  _TMP_SEL77_OUT := SEL(NOT(input6), TOF0.Q, NOT(input3) AND NOT(input5));
  output4 := _TMP_SEL77_OUT;
  _TMP_GE14_OUT := GE(input4, 1000);
  _TMP_LT20_OUT := LT(input4, 3000);
  _TMP_AND70_OUT := AND(_TMP_GE14_OUT, _TMP_LT20_OUT);
  TON1(EN := _TMP_AND70_OUT, IN := NOT(output5), PT := T#1s);
  TOF1(EN := TON1.ENO, IN := TON1.Q, PT := T#1s);
  output5 := TOF1.Q;
  _TMP_GE71_OUT := GE(input4, 3000);
  output6 := _TMP_GE71_OUT;
END_PROGRAM
