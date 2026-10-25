// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80222768-0x802227E0 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AFED4[];
extern char lbl_802AFED8[];
extern s32 lbl_80305F9C;
s32 fn_80128294(void *arg0, s32 arg1, void *arg2, s32 arg3);
s32 GetChecksum_4(void *arg0, s32 arg1, void *arg2, s32 arg3);
s32 fn_8022053C(s32 arg0, s8 arg1, s32 arg2);

bool ScriptToggleProSet(s32 arg0) {
    s32 sp8;
    s32 spC;
    s32 mgr;

    mgr = lbl_80305F9C;
    fn_80128294(arg0, lbl_802AFED4, &sp8, 1);
    GetChecksum_4(arg0, lbl_802AFED8, &spC, 1);
    fn_8022053C(mgr, ((Unk_12E59EE9 *)&sp8)->unk0x3, spC);
    return true;
}
