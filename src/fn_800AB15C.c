// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AB15C-0x800AB224 (200B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
s32 fn_8005DFD8(Unk_C8FEE62D *);
void CStruct_delete(CStruct *, s32);
extern char lbl_80298448[];
extern char lbl_802984C8[];
void fn_800AB15C(Unk_C8FEE62D *arg0, s32 arg1) {
    void *temp_r11;
    Unk_F5317C5D *temp_r9;
    s32 temp_r3;

    arg0->unk0x14 = (s32)lbl_80298448;
    temp_r3 = arg0->unk0x38;
    if (temp_r3 != 0) {
        CStruct_delete(temp_r3, 3);
    }
    temp_r3 = arg0->unk0x18;
    if (temp_r3 != 0 && fn_8005DFD8((void *)temp_r3) == 0) {
        temp_r11 = arg0->unk0x18;
        if (temp_r11 != 0) {
            temp_r9 = ((Unk_9994C3F5 *)temp_r11)->unk0x8;
            ((s32 (*)(void *, s32))temp_r9->unk0xC)(temp_r11 + temp_r9->unk0x8, 3);
        }
    }
    arg0->unk0x14 = (s32)lbl_802984C8;
    *(s32 *)(arg0->unk0x10 + 0xC) = arg0->unk0xC;
    *(s32 *)(arg0->unk0xC + 0x10) = arg0->unk0x10;
    arg0->unk0xC = (s32)arg0;
    arg0->unk0x10 = (s32)arg0;
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
