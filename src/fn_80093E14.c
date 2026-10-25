// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80093E14-0x80093E4C (56B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80024090(s32);
void fn_80093E14(Unk_C7387A53 *arg0) {
    Unk_F5317C5D *temp_r10;
    void *temp_r9;

    temp_r9 = arg0->unk0x54;
    temp_r10 = *(s32 *)(*(s32 *)((char *)((char *)temp_r9) + 0x1C) + 0x20);
    fn_80024090((*((u16 *)&temp_r10->unk0x8) + 1) * 0xC);
}
