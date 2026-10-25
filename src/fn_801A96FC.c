// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A96FC-0x801A977C (128B). Byte-identical.
#include "types.h"
#include "structs.h"

extern u8 fn_801A9670(s32, s32);

void fn_801A96FC(Unk_C8FEE62D *arg0, CStruct *arg1) {
    char *q;
    char *p2;
    u8 ret;

    if ((arg0->unk0x44 != 0) &&
        (arg0->unk0x40 == arg1->unk0x0)) {
        ret = fn_801A9670(arg1->unk0xC,
                          arg0->unk0x18);
        q = (char *)(arg1->unk0x8) + 8;
        q[arg1->unk0x4] = ret;
        (arg1->unk0x4) += 1;
        p2 = (char *)(arg1->unk0x8);
        p2[arg1->unk0x0] += 1;
    }
}
