PROGRAM basic_ladder
  VAR
    input1 AT %IX0.0 : BOOL := FALSE;
    input2 AT %IX0.1 : BOOL := TRUE;
    output1 AT %QX0.0 : BOOL;
    output2 AT %QX0.1 : BOOL;
    reset AT %IX0.2 : BOOL := FALSE;
    load AT %IX0.3 : BOOL := FALSE;
  END_VAR
  VAR
    CTU_DINT0 : CTU_DINT;
    TP0 : TP;
    R_TRIG0 : R_TRIG;
    CTD_UDINT0 : CTD_UDINT;
    R_TRIG1 : R_TRIG;
    R_TRIG2 : R_TRIG;
  END_VAR

  R_TRIG0(CLK := input1);
  R_TRIG1(CLK := R_TRIG0.Q);
  CTD_UDINT0(CD := R_TRIG1.Q, LD := load, PV := 2);
  output1 := CTD_UDINT0.Q;
  TP0(IN := input2, PT := T#100ms);
  R_TRIG2(CLK := TP0.Q);
  CTU_DINT0(CU := R_TRIG2.Q, R := reset, PV := 3);
  output2 := CTU_DINT0.Q;
END_PROGRAM
