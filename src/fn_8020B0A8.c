// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020B0A8-0x8020B134 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AF3A0[];
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern void fn_80128294(CStruct *, void *, void *, s32);
extern s32 fn_80207184(Unk_90685748 *, s32, s32, s32);
s32 fn_8020B0A8(Unk_90685748 *arg0, CStruct *arg1) {
    s32 sp8;
    s32 spC;
    s32 var_r3;

    sp8 = 0;
    spC = 0xF;
    GetChecksum_2(arg1, 0, &sp8, 0);
    fn_80128294(arg1, lbl_802AF3A0, &spC, 0);
    if (sp8 != 0) {
        var_r3 = fn_80207184(arg0, sp8, spC, -1);
        goto L_end;
    }
    var_r3 = 0;
L_end:
    return var_r3;
}
