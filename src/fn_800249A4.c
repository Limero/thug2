// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800249A4-0x80024A40 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

extern char lbl_802913F8[];
void fn_800550D4(s32, s32);
void fn_80024740(CStruct *, s32);

void fn_800249A4(CStruct *arg0, s32 arg1) {
    void *temp_r11;
    CStruct *temp_r9;
    CStruct *temp_r9_2;
    s32 v;

    v = arg0->unk0x10;
    arg0->unk0x8 = (s32)lbl_802913F8;
    fn_800550D4(v, arg1);
    temp_r11 = arg0->unk0x10;
    if (temp_r11 != NULL) {
        temp_r9 = ((Unk_9994C3F5 *)temp_r11)->unk0x8;
        ((s32 (*)(void *, s32))temp_r9->unk0xC)((char *)temp_r11 + *(s16 *)((char *)temp_r9 + 0x8), 3);
    }
    temp_r11 = arg0->unk0xC;
    if (temp_r11 != NULL) {
        temp_r9_2 = ((Unk_9994C3F5 *)temp_r11)->unk0x8;
        ((s32 (*)(void *, s32))temp_r9_2->unk0xC)((char *)temp_r11 + *(s16 *)((char *)temp_r9_2 + 0x8), 3);
    }
    fn_80024740(arg0, arg1);
}
