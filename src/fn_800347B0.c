// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800347B0-0x80034850 (160B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8005527C(void *);
void fn_80033560(Unk_C8FEE62D *, s32);
extern char lbl_80291CA0[];
void fn_800347B0(Unk_C8FEE62D *arg0, s32 arg1) {
    void *temp_r11;
    Unk_F5317C5D *temp_r9;

    arg0->unk0x14 = (s32)lbl_80291CA0;
    if ((s32) arg0->unk0x1C != 0) {
        fn_8005527C(arg0->unk0x1C);
        arg0->unk0x1C = 0;
    }
    temp_r11 = arg0->unk0x18;
    if (temp_r11 != NULL) {
        temp_r9 = ((Unk_C8FEE62D *)temp_r11)->unk0x14;
        ((s32 (*)(void *, s32))temp_r9->unk0xC)(temp_r11 + temp_r9->unk0x8, 3);
        arg0->unk0x18 = NULL;
    }
    if ((s32) arg0->unk0x20 != 0) {
        arg0->unk0x20 = 0;
    }
    fn_80033560(arg0, arg1);
}
