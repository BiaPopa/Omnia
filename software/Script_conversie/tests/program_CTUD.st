PROGRAM basic_ladder
  VAR
    input_up AT %IX0.0 : BOOL := FALSE;     
    input_down AT %IX0.1 : BOOL := FALSE;   
    reset AT %IX0.2 : BOOL := FALSE;       
    load AT %IX0.3 : BOOL := FALSE;        
    output_up AT %QX0.0 : BOOL;           
    output_down AT %QX0.1 : BOOL;          
  END_VAR

  VAR
    CTUD0 : CTUD;
  END_VAR

  CTUD0(CU := input_up, CD := input_down, R := reset, LD := load, PV := 5);
  output_up := CTUD0.QU;
  output_down := CTUD0.QD;
END_PROGRAM
