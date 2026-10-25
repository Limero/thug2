// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80240744-0x8024077C (56B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_802406DC(void *);
void fn_80240744(CStruct *arg0) {
    s32 temp_r0;
    s32 temp_r9;

    temp_r0 = arg0->unk0x8;
    if (!(temp_r0 & 0x100)) {
        temp_r9 = temp_r0 & 4;
        if (temp_r9 != 0) {
            fn_802406DC(arg0->unk0x34);
        }
    }
}
