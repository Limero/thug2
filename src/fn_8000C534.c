// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000C534-0x8000C5A4 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80290290[];
void fn_8000C534(Unk_C5BAE83F *arg0, s32 arg1) {
    void *temp_r11;
    Unk_F5317C5D *temp_r9;

    temp_r11 = arg0->unk0x4;
    arg0->unk0xEC = (s32)lbl_80290290;
    if (temp_r11 != NULL) {
        temp_r9 = ((Unk_C8FEE62D *)temp_r11)->unk0x14;
        ((s32 (*)(void *, s32))temp_r9->unk0xC)(temp_r11 + temp_r9->unk0x8, 3);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
