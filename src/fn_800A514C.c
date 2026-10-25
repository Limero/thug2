// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A514C-0x800A51DC (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800A6910(CStruct *, s32 *);
s32 fn_800A6AC0(CStruct *, s32 *);
void fn_800A6AAC(CStruct *);
void fn_800A514C(Unk_C7387A53 *arg0, CScript *arg1) {
    s32 sp8;
    Unk_C8FEE62D *v;
loop_1:
    fn_800A6AAC(arg0->unk0xC);
    v = (Unk_C8FEE62D *)fn_800A6AC0(arg0->unk0xC, &sp8);
    goto loop_3;
loop_2:
    v = (Unk_C8FEE62D *)fn_800A6AC0(arg0->unk0xC, &sp8);
loop_3:
    if (v != NULL) {
        if ((s32)v->unk0x18 == (s32)arg1->unk0x18) {
            if (v->unk0x44 > 0) {
                v->unk0x44--;
            }
            fn_800A6910(arg0->unk0xC, &sp8);
            goto loop_1;
        }
        goto loop_2;
    }
}