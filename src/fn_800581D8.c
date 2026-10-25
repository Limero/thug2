// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800581D8-0x80058234 (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void fn_800FF914(Unk_9994C3F5 *);
void fn_800581D8(Unk_C8FEE62D *arg0, s32 arg1) {
    u16 temp_r0;
    Unk_897A0ACF *temp_r9;

    temp_r9 = arg0->unk0x14;
    if (temp_r9 != NULL) {
        if (arg1 == 0) {
            s32 t = temp_r9->unk0x4;
            t &= QB_UNKNOWN_0xFFFFFF7F;
            temp_r9->unk0x4 = (u16)t;
            return;
        }
        temp_r0 = temp_r9->unk0x4;
        if (!(temp_r0 & 0x80)) {
            temp_r9->unk0x4 = (u16)(temp_r0 | 0x80);
            fn_800FF914(arg0->unk0x14);
        }
    }
}
