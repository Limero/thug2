// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A952C-0x800A95D4 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, s32);
s32 fn_800D68AC(void);
s32 Mth_Rnd(s32);
s32 fn_800F0610(void *, s32);
s32 fn_800A94C8(Unk_A9157FE7 *);
s32 fn_800F0598(s32);
bool fn_800A952C(Unk_1DD88053 *arg0) {
    s32 temp_r3;

    temp_r3 = fn_800F0598(arg0->unk0x64);
    if (temp_r3 == 0) {
        return false;
    }
    arg0->unk0x60 = (s32) arg0->unk0x64;
    GetChecksum_3(arg0->unk0x18, QB_MOTION);
    if (fn_800D68AC() != 0) {
        arg0->unk0x64 = fn_800F0610(arg0->unk0x64, Mth_Rnd(temp_r3));
    } else {
        arg0->unk0x64 = fn_800F0610(arg0->unk0x64, 0);
    }
    arg0->unk0x70 = arg0->unk0x80;
    arg0->unk0x78 = arg0->unk0x88;
    fn_800A94C8(arg0);
    return true;
}
