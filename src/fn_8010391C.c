// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010391C-0x801039D8 (188B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// ID: setup wrapper around worker fn_80103320 — stores dest-buffer ptr
// (arg3) to lbl_80301BC4, zeroes counter lbl_80302BC8, stores extra (arg4)
// to lbl_80302BCC, runs the worker on (arg0, arg0+0x34 field, arg1), then
// returns the count (or the static buffer lbl_80301BC8 on empty/negative).
// Likely a script-data fetch/unpack helper (QB-adjacent zone).
// Suggested rename: ScriptDataFetchSetup (verify against callers first).
#include "types.h"
#include "structs.h"
extern s32 lbl_80301BC4;
extern s32 lbl_80302BC8;
extern s32 lbl_80302BCC;
extern char lbl_80301BC8[];
void fn_80103320(void *, void *, s32);
s32 fn_8010391C(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4) {
    s32 temp_r0;
    s32 var_r3 = arg3;

    if ((s32) arg0->unk0x34 == 0) {
        *arg2 = *(u16 *)((char *)arg0 + 8);
        return (s32)lbl_80301BC8;
    } else {
        lbl_80302BC8 = 0;
        lbl_80301BC4 = var_r3;
        lbl_80302BCC = arg4;
        fn_80103320(arg0, (void *)(s32)arg0->unk0x34, arg1);
        temp_r0 = lbl_80302BC8;
        if (temp_r0 < 0) {
            var_r3 = (s32)lbl_80301BC8;
            *arg2 = *(u16 *)((char *)arg0 + 8);
        } else {
            *arg2 = temp_r0;
            var_r3 = lbl_80301BC4;
        }
        lbl_80301BC4 = 0;
        lbl_80302BCC = 0;
    }
    return var_r3;
}
