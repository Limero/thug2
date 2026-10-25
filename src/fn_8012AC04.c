// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012AC04-0x8012ADC4 (448B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8012A8F0(Unk_5B449B03 *, s32 *, s32 *);
s32 fn_80128B48(CStruct *, CStruct *);
s32 strlen(const char *);

typedef union {
    s32 i;
    f32 f;
} Value;

s32 fn_8012AC04(Unk_5B449B03 *arg0, Unk_5B449B03 *arg1) {
    Value value1;
    s32 type1;
    Value value0;
    s32 type0;
    u32 len0;

    fn_8012A8F0(arg0, &type0, (s32 *) &value0);
    fn_8012A8F0(arg1, &type1, (s32 *) &value1);
    switch (type0) {
    case 1:
        if (type1 != 2) {
            goto case1_integer;
        }
        return (f32) (f64) (s32) value0.i < value1.f;
    case1_integer:
        if (type1 != 1) {
            return 0;
        }
        return value0.i < value1.i;
    case 2:
        if (type1 != 1) {
            goto case2_float;
        }
        return value0.f < (f32) (f64) (s32) value1.i;
    case2_float:
        if (type1 != 2) {
            return 0;
        }
        return value0.f < value1.f;
    case 3:
        if (type1 != 3) {
            break;
        }
        len0 = strlen((const char *) value0.i);
        return len0 < strlen((const char *) value1.i);
    case 4:
        if (type1 != 4) {
            break;
        }
        len0 = strlen((const char *) value0.i);
        return len0 < strlen((const char *) value1.i);
    case 10:
    case 20:
        if ((type1 == 0xA) || (type1 == 0x14)) {
            return fn_80128B48((CStruct *) value0.i, (CStruct *) value1.i);
        }
        return 0;
    }
    return 0;
}
