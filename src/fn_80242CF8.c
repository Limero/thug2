// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80242CF8-0x80242D60 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
// FIXED: protos + char-cast (was s32* x4) - EXACT, M5.47
void *fn_80241E38(void *, u32);
s32 fn_8022DC74(Unk_C7387A53 *, void *);
s32 fn_80242CF8(Unk_C7387A53 *arg0, u32 arg1) {
    s32 temp_r30;

    if ((arg1 >= (u32) *((u32 *)&arg0->unk0x30)) || ((s32) arg1 < 0)) {
        return 0;
    }
    temp_r30 = *((s32 *)fn_80238964());
    return fn_8022DC74(temp_r30, *(s32 *)((char *)fn_80241E38(arg0, arg1) + 8));
}

