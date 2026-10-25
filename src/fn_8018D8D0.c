// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018D8D0-0x8018D924 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8018D5D4(Unk_C7387A53 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_8018D8D0(Unk_C7387A53 *arg0, CStruct *arg1, s32 arg2) {
    s32 sp8;
    s32 h;

    h = fn_8018D5D4(arg0, arg2);
    GetInteger((CStruct *)h, arg1, &sp8, 1);
    return sp8 != 0;
}
