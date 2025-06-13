PROGRAM basic_ladder
  VAR
    input1 AT %IX0.0 : BOOL := FALSE;
    input2 AT %IX0.1 : BOOL := TRUE;
    output1 AT %QX0.0 : BOOL;
    output2 AT %QX0.1 : BOOL;
  END_VAR
  VAR
    TON0 : TON;
    TOF0 : TOF;
  END_VAR

  TON0(IN := input1, PT := T#500ms);
  TOF0(IN := TON0.Q, PT := T#550ms);
  output1 := TOF0.Q;
  output2 := input2;
END_PROGRAM
