// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020C54C-0x8020C58C (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_801A9A4C(s32);
void fn_8020C58C(Unk_BF3B6DA6 *, s32);
void fn_8020C54C(Unk_BF3B6DA6 *arg0, s32 arg1) {
    CScript *temp_r9;
    arg0->unk0x1400 = arg1;
    if (arg1 == 0) {
        fn_801A9A4C((s32)arg0 + 0x1404);
        return;
    }
    temp_r9 = (CScript *)arg0->unk0x2C;
    fn_8020C58C(arg0, temp_r9->unk0x1D0);
}
