// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801347CC-0x80134844 (120B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_80134CD8(void *, s32 *, s32);
extern void fn_80134584(CScript *, Unk_C8FEE62D *);
extern void fn_801344E8(CScript *, Unk_C8FEE62D *);

void fn_801347CC(CScript *arg0, s32 arg1) {
    s32 sp8;
    Unk_C7387A53 *temp_r3;

    sp8 = arg1;
    temp_r3 = (void *)fn_80134CD8(arg0->unk0x18, &sp8, 1);
    if (temp_r3 != NULL) {
        if ((temp_r3->unk0xC -= 1) == 0) {
            if (arg0->unk0x24 != 0) {
                fn_80134584(arg0, temp_r3);
            } else {
                fn_801344E8(arg0, temp_r3);
            }
        }
    }
}
