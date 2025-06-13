PROGRAM basic_ladder
  VAR
    input1 AT %IX0.0 : BOOL := FALSE;
    input2 AT %IX0.1 : BOOL := TRUE;
    output1 AT %QX0.0 : BOOL;
    output2 AT %QX0.1 : BOOL;
    output3 AT %QX0.3 : BOOL;
    output4 AT %QX0.4 : BOOL;
    reset AT %IX0.2 : BOOL := FALSE;
    load AT %IX0.3 : BOOL := FALSE;
  END_VAR
  VAR
    CTU0 : CTU;
    CTU1 : CTU;
    R_TRIG1 : R_TRIG;
    R_TRIG2 : R_TRIG;
    _TMP_GT28_OUT : BOOL;
    _TMP_LT31_OUT : BOOL;
  END_VAR

  R_TRIG1(CLK := input1);
  CTU0(CU := R_TRIG1.Q, PV := 100);
  R_TRIG2(CLK := input2);
  CTU1(CU := R_TRIG2.Q, PV := 100);
  _TMP_GT28_OUT := GT(CTU0.CV, CTU1.CV);
  output1 := _TMP_GT28_OUT;
  _TMP_LT31_OUT := LT(reset, load);
  output2 := _TMP_LT31_OUT;
END_PROGRAM
