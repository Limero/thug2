// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80192484-0x80192588 (260B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802A98F0[];
extern char lbl_802A98FC[];
extern char lbl_802A9908[];
extern char lbl_802A9910[];
extern char lbl_802A98D4[];
s32 fn_80128294(CStruct *, void *, void *, s32);
void fn_8018F514(Unk_9AA07378 *, CStruct *);
void fn_80192484(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;

    fn_80128294(arg1, (s32)lbl_802A98F0, &sp8, 0);
    if (sp8 != 0) {
        arg0->unk0x80 = 1;
    }
    fn_80128294(arg1, (s32)lbl_802A98FC, &spC, 0);
    if (spC != 0) {
        arg0->unk0x80 = 1;
    }
    fn_80128294(arg1, (s32)lbl_802A9908, &sp10, 0);
    if (sp10 != 0) {
        arg0->unk0x80 = 1;
    }
    fn_80128294(arg1, (s32)lbl_802A9910, &sp14, 0);
    arg0->unk0x84 = sp14;
    if (fn_80128294(arg1, (s32)lbl_802A98D4, &sp18, 0) != 0) {
        arg0->unk0x50 = sp18;
    }
    fn_8018F514(arg0, arg1);
}
