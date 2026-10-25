// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003AB44-0x8003ABA0 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8003D50C(s32, s32, s32);
s32 fn_8003A430(CStruct *);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 fn_8003AB44(s32 arg0, s32 arg1) {
    s32 sp8;
    if (GetStructure_2(arg0 + 0x58, arg1, &sp8, 0) != 0) {
        return fn_8003D50C(arg1, fn_8003A430(sp8), 0);
    }
    return 0;
}