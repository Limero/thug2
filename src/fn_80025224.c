// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80025224-0x800252C0 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80291538[];
void fn_80025E2C(CStruct *);
void fn_80025D84(void *);
void fn_80024740(CStruct *, s32);
void fn_80025224(CStruct *arg0, s32 arg1) {
    void *temp_r11;
    CStruct *temp_r9;
    Unk_9994C3F5 *temp_r9_2;

    temp_r11 = arg0->unk0xC;
    arg0->unk0x8 = (s32)lbl_80291538;
    if (temp_r11 != NULL) {
        temp_r9 = ((Unk_9994C3F5 *)temp_r11)->unk0x8;
        ((void (*)(void *, s32))temp_r9->unk0xC)((char *)temp_r11 + *(s16 *)((char *)temp_r9 + 0x8), 3);
    }
    temp_r9_2 = arg0->unk0x68;
    if (temp_r9_2 != NULL) {
        if ((s32) temp_r9_2->unk0x8 != 0) {
            fn_80025E2C(arg0);
            fn_80025D84(arg0->unk0x50);
        }
        arg0->unk0x68 = NULL;
    }
    fn_80024740(arg0, arg1);
}