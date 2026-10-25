// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80009B80-0x80009C00 (128B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_80009C00(CStruct *);
extern char lbl_8028FF00[];
void fn_80009B80(Unk_C8FEE62D *arg0, s32 arg1) {
    void *temp_r11;
    Unk_F5317C5D *temp_r9;

    arg0->unk0x18 = (s32)lbl_8028FF00;
    if ((s32) arg0->unk0xC != 0) {
        fn_80009C00(arg0);
    }
    temp_r11 = arg0->unk0x8;
    if (temp_r11 != NULL) {
        temp_r9 = ((Unk_C8FEE62D *)temp_r11)->unk0x14;
        ((s32 (*)(void *, s32))temp_r9->unk0xC)(temp_r11 + temp_r9->unk0x8, 3);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}