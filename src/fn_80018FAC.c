// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80018FAC-0x8001908C (224B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern char lbl_80290D40[];
extern char lbl_80290D44[];
extern char lbl_80290D48[];
extern char lbl_80290D4C[];
extern u8 lbl_80300125[];

s32 fn_80128294(void *, char *, void *, s32);

bool ScriptNgc_BGColor(void *arg0) {
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;

    sp8 = lbl_80300125[0];
    spC = lbl_80300125[1];
    sp10 = lbl_80300125[2];
    sp14 = lbl_80300125[3];
    fn_80128294(arg0, lbl_80290D40, &sp8, 0);
    fn_80128294(arg0, lbl_80290D44, &spC, 0);
    fn_80128294(arg0, lbl_80290D48, &sp10, 0);
    fn_80128294(arg0, lbl_80290D4C, &sp14, 0);
    lbl_80300125[0] = sp8;
    lbl_80300125[1] = spC;
    lbl_80300125[2] = sp10;
    lbl_80300125[3] = sp14;
    return true;
}
