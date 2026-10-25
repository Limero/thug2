// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80107118-0x801071A8 (144B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80293260[];
extern void *Mem_NewZero(s32);
s32 fn_80107118(s32 unused, s32 arg1, Unk_C7387A53 *arg2, CStruct *arg3, s32 arg4) {
    Unk_C8FEE62D *temp_r3;

    if (arg4 < 0) {
        *((s32 *)((char *)arg2->unk0x2C + ((arg2->unk0x24 + arg4) * 4))) = arg1;
    } else {
        temp_r3 = Mem_NewZero(0x18);
        temp_r3->unk0xC = temp_r3;
        temp_r3->unk0x10 = temp_r3;
        temp_r3->unk0x14 = (s32)lbl_80293260;
        temp_r3->unk0x4 = arg1;
        temp_r3->unk0x8 = 0;
        temp_r3->unk0x10 =  arg3->unk0x10;
        temp_r3->unk0xC = arg3;
        *(s32 *)(*(s32 *)((char *)((char *)arg3) + 0x10) + 0xC) = temp_r3;
        arg3->unk0x10 = temp_r3;
    }
    return arg4 + 1;
}
