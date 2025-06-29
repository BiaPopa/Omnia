PROGRAM basic_ladder
  VAR
    input1 AT %IX0.0 : BOOL := FALSE;
    input2 AT %IX0.1 : BOOL := FALSE;
    output1 AT %QX0.0 : BOOL;
  END_VAR
  VAR
    CTU0 : CTU;
    CTU1 : CTU;
    R_TRIG1 : R_TRIG;
    R_TRIG2 : R_TRIG;
    _TMP_MUX36_OUT : INT;
    _TMP_LIMIT37_OUT : INT;
    _TMP_GT40_OUT : BOOL;
  END_VAR

  R_TRIG1(CLK := input1);
  CTU0(CU := R_TRIG1.Q, PV := 100);
  R_TRIG2(CLK := input2);
  CTU1(CU := R_TRIG2.Q, PV := 100);
  _TMP_MUX36_OUT := MUX(1, CTU0.CV, CTU1.CV);
  _TMP_LIMIT37_OUT := LIMIT(1, _TMP_MUX36_OUT, 4);
  _TMP_GT40_OUT := GT(_TMP_LIMIT37_OUT, 2);
  output1 := _TMP_GT40_OUT;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : basic_ladder;
  END_RESOURCE
END_CONFIGURATION

(*DBG:char md5[] = "de25704adfd53cca44990890686f0a16";*)
(*DBG:/**)
(*DBG: * This file is part of OpenPLC Runtime*)
(*DBG: **)
(*DBG: * Copyright (C) 2023 Autonomy, GP Orcullo*)
(*DBG: * Based on the work by GP Orcullo on Beremiz for uC*)
(*DBG: **)
(*DBG: * This program is free software; you can redistribute it and/or*)
(*DBG: * modify it under the terms of the GNU General Public License*)
(*DBG: * as published by the Free Software Foundation; either version 2*)
(*DBG: * of the License, or (at your option) any later version.*)
(*DBG: **)
(*DBG: * This program is distributed in the hope that it will be useful,*)
(*DBG: * but WITHOUT ANY WARRANTY; without even the implied warranty of*)
(*DBG: * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the*)
(*DBG: * GNU General Public License for more details.*)
(*DBG: **)
(*DBG: * You should have received a copy of the GNU General Public License*)
(*DBG: * along with this program; If not, see <http://www.gnu.org/licenses/>.*)
(*DBG: **)
(*DBG: */*)
(*DBG:*)
(*DBG:#include <stdbool.h>*)
(*DBG:*)
(*DBG:#include "iec_types_all.h"*)
(*DBG:#include "POUS.h"*)
(*DBG:*)
(*DBG:#define SAME_ENDIANNESS      0*)
(*DBG:#define REVERSE_ENDIANNESS   1*)
(*DBG:*)
(*DBG:uint8_t endianness;*)
(*DBG:*)
(*DBG:*)
(*DBG:extern BASIC_LADDER RES0__INSTANCE0;*)
(*DBG:*)
(*DBG:static const struct {*)
(*DBG:    void *ptr;*)
(*DBG:    __IEC_types_enum type;*)
(*DBG:} debug_vars[] = {*)
(*DBG:    {&(RES0__INSTANCE0.INPUT1), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.INPUT2), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.OUTPUT1), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU0.EN), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU0.ENO), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU0.CU), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU0.R), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU0.PV), INT_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU0.Q), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU0.CV), INT_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU0.CU_T.EN), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU0.CU_T.ENO), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU0.CU_T.CLK), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU0.CU_T.Q), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU0.CU_T.M), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU1.EN), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU1.ENO), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU1.CU), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU1.R), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU1.PV), INT_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU1.Q), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU1.CV), INT_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU1.CU_T.EN), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU1.CU_T.ENO), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU1.CU_T.CLK), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU1.CU_T.Q), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.CTU1.CU_T.M), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.R_TRIG1.EN), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.R_TRIG1.ENO), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.R_TRIG1.CLK), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.R_TRIG1.Q), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.R_TRIG1.M), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.R_TRIG2.EN), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.R_TRIG2.ENO), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.R_TRIG2.CLK), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.R_TRIG2.Q), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0.R_TRIG2.M), BOOL_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0._TMP_MUX36_OUT), INT_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0._TMP_LIMIT37_OUT), INT_ENUM},*)
(*DBG:    {&(RES0__INSTANCE0._TMP_GT40_OUT), BOOL_ENUM},*)
(*DBG:};*)
(*DBG:*)
(*DBG:#define VAR_COUNT               45*)
(*DBG:*)
(*DBG:uint16_t get_var_count(void)*)
(*DBG:{*)
(*DBG:    return VAR_COUNT;*)
(*DBG:}*)
(*DBG:*)
(*DBG:size_t get_var_size(size_t idx)*)
(*DBG:{*)
(*DBG:    if (idx >= VAR_COUNT)*)
(*DBG:    {*)
(*DBG:        return 0;*)
(*DBG:    }*)
(*DBG:    switch (debug_vars[idx].type) {*)
(*DBG:    case BOOL_ENUM:*)
(*DBG:        return sizeof(BOOL);*)
(*DBG:    case INT_ENUM:*)
(*DBG:        return sizeof(INT);*)
(*DBG:    default:*)
(*DBG:        return 0;*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)
(*DBG:void *get_var_addr(size_t idx)*)
(*DBG:{*)
(*DBG:    void *ptr = debug_vars[idx].ptr;*)
(*DBG:*)
(*DBG:    switch (debug_vars[idx].type) {*)
(*DBG:    case BOOL_ENUM:*)
(*DBG:        return (void *)&((__IEC_BOOL_t *) ptr)->value;*)
(*DBG:    case INT_ENUM:*)
(*DBG:        return (void *)&((__IEC_INT_t *) ptr)->value;*)
(*DBG:    default:*)
(*DBG:        return 0;*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)
(*DBG:void force_var(size_t idx, bool forced, void *val)*)
(*DBG:{*)
(*DBG:    void *ptr = debug_vars[idx].ptr;*)
(*DBG:*)
(*DBG:    if (forced) {*)
(*DBG:        size_t var_size = get_var_size(idx);*)
(*DBG:        switch (debug_vars[idx].type) {*)
(*DBG:        case BOOL_ENUM: {*)
(*DBG:            memcpy(&((__IEC_BOOL_t *) ptr)->value, val, var_size);*)
(*DBG:            //((__IEC_BOOL_t *) ptr)->value = *((BOOL *) val);*)
(*DBG:            ((__IEC_BOOL_t *) ptr)->flags |= __IEC_FORCE_FLAG;*)
(*DBG:            break;*)
(*DBG:        }*)
(*DBG:        case INT_ENUM: {*)
(*DBG:            memcpy(&((__IEC_INT_t *) ptr)->value, val, var_size);*)
(*DBG:            //((__IEC_INT_t *) ptr)->value = *((INT *) val);*)
(*DBG:            ((__IEC_INT_t *) ptr)->flags |= __IEC_FORCE_FLAG;*)
(*DBG:            break;*)
(*DBG:        }*)
(*DBG:        default:*)
(*DBG:            break;*)
(*DBG:        }*)
(*DBG:    } else {*)
(*DBG:        switch (debug_vars[idx].type) {*)
(*DBG:        case BOOL_ENUM:*)
(*DBG:            ((__IEC_BOOL_t *) ptr)->flags &= ~__IEC_FORCE_FLAG;*)
(*DBG:            break;*)
(*DBG:        case INT_ENUM:*)
(*DBG:            ((__IEC_INT_t *) ptr)->flags &= ~__IEC_FORCE_FLAG;*)
(*DBG:            break;*)
(*DBG:        default:*)
(*DBG:            break;*)
(*DBG:        }*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)
(*DBG:void swap_bytes(void *ptr, size_t size) *)
(*DBG:{*)
(*DBG:    uint8_t *bytePtr = (uint8_t *)ptr;*)
(*DBG:    size_t i;*)
(*DBG:    for (i = 0; i < size / 2; ++i) *)
(*DBG:    {*)
(*DBG:        uint8_t temp = bytePtr[i];*)
(*DBG:        bytePtr[i] = bytePtr[size - 1 - i];*)
(*DBG:        bytePtr[size - 1 - i] = temp;*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)
(*DBG:void trace_reset(void)*)
(*DBG:{*)
(*DBG:    for (size_t i=0; i < VAR_COUNT; i++) *)
(*DBG:    {*)
(*DBG:        force_var(i, false, 0);*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)
(*DBG:void set_trace(size_t idx, bool forced, void *val)*)
(*DBG:{*)
(*DBG:    if (idx >= 0 && idx < VAR_COUNT) *)
(*DBG:    {*)
(*DBG:        if (endianness == REVERSE_ENDIANNESS)*)
(*DBG:        {*)
(*DBG:            // Aaaaarghhhh... Stupid AVR is Big Endian.*)
(*DBG:            swap_bytes(val, get_var_size(idx));*)
(*DBG:        }*)
(*DBG:*)
(*DBG:        force_var(idx, forced, val);*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)
(*DBG:void set_endianness(uint8_t value)*)
(*DBG:{*)
(*DBG:    if (value == SAME_ENDIANNESS || value == REVERSE_ENDIANNESS)*)
(*DBG:    {*)
(*DBG:        endianness = value;*)
(*DBG:    }*)
(*DBG:}*)
(*DBG:*)