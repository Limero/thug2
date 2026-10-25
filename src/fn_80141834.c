// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80141834-0x80141880 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
void fn_80141570(CScript *, CStruct *);
void fn_80141834(CScript *arg0, s32 arg1, CStruct *arg2) {
    s32 sp8;

    sp8 = 0;
    GetStructure_2(arg2, arg1, &sp8, 0);
    fn_80141570(arg0, sp8);
}
