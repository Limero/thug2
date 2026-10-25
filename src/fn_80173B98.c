// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80173B98-0x80173C10 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8019B834(s32);
void *fn_8017471C(Unk_C2F9BED0 *, s32);
void *GetChecksum_3(Unk_6A70655D *, s32);
void fn_801EF978(Unk_31DE137E *, s32);
s32 fn_80173B98(Unk_C2F9BED0 *arg0) {
    Unk_6A70655D *temp_r30;
    Unk_90685748 *temp_r3;

    temp_r30 = fn_8017471C(arg0, fn_8019B834(arg0->unk0x374));
    temp_r3 = GetChecksum_3(temp_r30, QB_TRICK);
    if ((s32) temp_r3->unk0x13F4 != 0) {
        fn_801EF978(GetChecksum_3(temp_r30, QB_SKATERENDRUN), 0);
    }
    return temp_r3->unk0x13F4;
}
