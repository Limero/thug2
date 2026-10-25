// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022D8A4-0x8022D910 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8023FC44(void *);
s32 fn_8022D8A4(Unk_C7387A53 *arg0) {
    s32 sp8[27];
    s32 temp_r9;

    fn_8023FC44(sp8);
    temp_r9 = (arg0->unk0x20 - 1) * 0x94D00;
    sp8[2] += temp_r9;
    return (sp8[2] / 609536) + 1;
}
