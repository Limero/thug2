// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80015DE4-0x80015E34 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80015DE4(CScript *);
s32 CARDFreeBlocks(void *, void *, void *);
s32 fn_80015DE4(CScript *arg0) {
    s32 spC;
    s32 sp8;
    s32 var_r3;

    if (CARDFreeBlocks(arg0->unk0x18, &sp8, &spC) == 0) {
        var_r3 = sp8;
        if (var_r3 < 0) {
            var_r3 += 0x1FFF;
        }
        return var_r3 >> 0xD;
    }
    return 0;
}
