// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D4C88-0x800D4D30 (168B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80299CB0[];
void fn_800A7324(void *, s32);
void fn_8009F558(Unk_C8FEE62D *, s32);
void fn_800D4C88(CScript *arg0, s32 arg1) {
    void *temp_r11;
    Unk_F5317C5D *temp_r9;

    temp_r11 = arg0->unk0x204;
    arg0->unk0x18 = (s32)lbl_80299CB0;
    if (temp_r11 != NULL) {
        temp_r9 = ((Unk_FFAD6788 *)temp_r11)->unk0xF4;
        ((s32 (*)(void *, s32))temp_r9->unk0xC)(temp_r11 + temp_r9->unk0x8, 3);
        arg0->unk0x204 = NULL;
    }
    if (arg0->unk0x1E4 != 0) {
        Mem_Free(arg0->unk0x1E4);
        arg0->unk0x1E4 = 0;
    }
    if (arg0->unk0x208 != 0) {
        fn_800A7324(arg0->unk0x208, 3);
        arg0->unk0x208 = 0;
    }
    fn_8009F558(arg0, arg1);
}
