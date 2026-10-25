// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CDC64-0x801CDCD0 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_802AD2E8;
extern u32 fn_801CDB68(Unk_6EBFA797 *);
extern s32 fn_8012772C(CStruct *, s32, f32);

s32 fn_801CDC64(Unk_6EBFA797 *arg0, s32 arg1, CScript *arg2) {
    u32 v;

    v = fn_801CDB68(arg0);
    fn_8012772C(arg2->unk0x18, QB_AIRTIME, (f32)v * lbl_802AD2E8);
    return 1;
}
