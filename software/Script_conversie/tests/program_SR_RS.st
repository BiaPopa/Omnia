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
    SR0 : SR;
    RS0 : RS;
  END_VAR

  SR0(S1 := input1, R := reset);
  output1 := SR0.Q1;
  RS0(S := input2, R1 := load);
  output2 := RS0.Q1;
END_PROGRAM
