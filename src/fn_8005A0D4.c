// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005A0D4-0x8005A114 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80057970(s32, s32, s32);
s32 fn_8005A0D4(Unk_C7387A53 *arg0, s32 arg1) {
    s32 sp8;
    s32 v;

    v = arg0->unk0x20;
    sp8 = arg1;
    return (fn_80057970(v, &sp8, 1) != 0);
}
