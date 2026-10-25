// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80159BEC-0x80159C68 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_80305EAC[];

s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 fn_801A6E64(s32);

s32 ScriptGoalsGreaterThan(CStruct *arg0) {
    f32 sp8;
    s32 res;
    f32 fv;

    if (GetFloat(arg0, 0, &sp8, 0) == 0) {
        return 0;
    }
    fv = (f32)fn_801A6E64(*(s32 *)((char *)*(void **)lbl_80305EAC + 0x24));
    res = 1;
    __asm__("" : "+r"(res));
    if (fv > sp8) {
        return res;
    }
    return 0;
}
