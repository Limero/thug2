// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021C7CC-0x8021C7EC (32B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8021C7CC(s32 arg0, CStruct *arg1) {
    CStruct *temp_r3;
    s32 t;

    temp_r3 = (void *)(arg0 + 0x130);
    t = temp_r3->unk0x10;
    arg1->unk0xC = (s32)temp_r3;
    arg1->unk0x10 = t;
    *(s32 *)(temp_r3->unk0x10 + 0xC) = (s32)arg1;
    temp_r3->unk0x10 = (s32)arg1;
}
