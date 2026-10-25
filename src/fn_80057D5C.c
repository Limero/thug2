// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80057D5C-0x80057D90 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// ID: null-guarded forwarding wrapper — returns 0 if arg0+0x10 is NULL,
// else returns fn_8005F1BC(field). Likely a Script*/object query helper.
// Suggested rename: GuardedGet_8005F1BC (verify against callers first).
#include "types.h"
#include "structs.h"
extern s32 fn_8005F1BC(s32);
s32 fn_80057D5C(CStruct *arg0) {
    s32 temp_r0;
    s32 var_r3;

    temp_r0 = arg0->unk0x10;
    var_r3 = 0;
    if (temp_r0 == 0) {
        return var_r3;
    }
    return fn_8005F1BC(temp_r0);
}
