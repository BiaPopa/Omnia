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
    RS0 : RS;
    SEMA0 : SEMA;
  END_VAR

  SEMA0(CLAIM := input1, RELEASE := reset);
  output1 := SEMA0.BUSY;
  RS0(S := input2, R1 := load);
  output2 := RS0.Q1;
END_PROGRAM
