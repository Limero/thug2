// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800580A0-0x8005812C (140B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8005F3D4(void *, s32);
void fn_800580A0(Unk_C8FEE62D *arg0, s32 arg1) {
    void *temp_r29;
    void *temp_r30;
    CStruct *temp_r30_2;
    void *temp_r9;

    temp_r9 = arg0->unk0x14;
    if (temp_r9 != NULL) {
        temp_r30 = ((Unk_C7387A53 *)temp_r9)->unk0xC;
        temp_r30_2 = temp_r30 + 0xC0;
        temp_r29 = temp_r9 + ((Unk_988430B4 *)temp_r30)->unk0xC0;
        ((s32 (*)(void *, void *, void *))temp_r30_2->unk0x4)(temp_r29, fn_80057EF4(), arg1);
        if ((s32) arg0->unk0x4 & 0x40) {
            arg0->unk0x4 |= 0x20;
        }
    }
    if ((s32) arg0->unk0x10 != 0) {
        fn_8005F3D4(*((void * *)&arg0->unk0x10), arg1);
    }
}
