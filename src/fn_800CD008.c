// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CD008-0x800CD074 (108B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
void fn_800B0A08(s32, Unk_C7387A53 *, void *);
s32 fn_80024660(void *);
s32 fn_800CD008(Unk_EA529D06 *arg0, Unk_A2289594 *arg1, void *arg2) {
    s32 temp_r30;

    temp_r30 = arg1->unk0xC0;
    if ((temp_r30 != 0) && (arg2 != 0)) {
        fn_800B0A08(arg0, temp_r30, fn_80024660(arg2));
    } else {
        arg0->unk0x0 = arg1->unk0xA0;
        arg0->unk0x8 = arg1->unk0xA8;
    }
    return arg0;
}
