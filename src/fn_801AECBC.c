// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AECBC-0x801AED20 (100B). Byte-identical.
#include "types.h"
#include "structs.h"

register s32 r31_guard __asm__("r31");

extern char lbl_802ABD20[];
extern void fn_800091F4(CStruct *);

void *fn_801AECBC(Unk_C8FEE62D *arg0) {
    s32 zero;
    char *p;
    void *var_r3;

    zero = 0;
    arg0->unk0x4 = arg0;
    arg0->unk0x8 = zero;
    arg0->unk0xC = arg0;
    p = (char *)arg0 + (s32)0x48;
    arg0->unk0x10 = arg0;
    arg0->unk0x14 = (s32)lbl_802ABD20;
    fn_800091F4(p);
    arg0->unk0x3C = zero;
    arg0->unk0x38 = zero;
    arg0->unk0x44 = 1;
    var_r3 = arg0;
    return var_r3;
}
