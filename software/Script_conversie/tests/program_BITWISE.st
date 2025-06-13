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
    _TMP_AND42_OUT : BOOL;
    _TMP_XOR43_OUT : BOOL;
    _TMP_OR44_OUT : BOOL;
    _TMP_NOT45_OUT : BOOL;
  END_VAR

  _TMP_AND42_OUT := AND(input1, input2);
  _TMP_XOR43_OUT := XOR(reset, load);
  _TMP_OR44_OUT := OR(_TMP_AND42_OUT, _TMP_XOR43_OUT);
  _TMP_NOT45_OUT := NOT(_TMP_OR44_OUT);
  output1 := _TMP_NOT45_OUT;
END_PROGRAM
