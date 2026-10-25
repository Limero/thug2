// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801064C8-0x80106560 (152B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029C210[];
bool fn_801064C8(Unk_C7387A53 *arg0, s32 arg1) {
    s32 i;
    s32 k;

    for (i = 0; i < arg0->unk0x24; i++) {
        if (((s32 *)arg0->unk0x2C)[i] == arg1) {
            for (k = i + 1; k < arg0->unk0x24; k++) {
                ((s32 *)arg0->unk0x2C)[k - 1] =
                    ((s32 *)arg0->unk0x2C)[k];
            }
            ((s32 *)arg0->unk0x2C)
                [arg0->unk0x24 - 1] = 0;
            return true;
        }
    }
    return false;
}
