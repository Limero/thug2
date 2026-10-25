// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80134844-0x801348BC (120B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_80134CD8(void *, s32 *, s32);
extern void fn_80134584(CScript *, Unk_C8FEE62D *);
extern void fn_8013465C(CScript *, s32);

void fn_80134844(CScript *arg0, s32 arg1) {
    s32 sp8;
    s32 temp_r30;
    Unk_C7387A53 *temp_r3;

    sp8 = arg1;
    temp_r3 = (void *)fn_80134CD8(arg0->unk0x18, &sp8, 1);
    if (temp_r3 != NULL) {
        temp_r30 = temp_r3->unk0xC;
        fn_80134584(arg0, temp_r3);
        fn_8013465C(arg0, sp8);
        *(s32 *)((char *)fn_80134CD8(arg0->unk0x18, &sp8, 1) + (s32)0xC) = temp_r30;
    }
}
