// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C5800-0x801C5860 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void fn_8012772C(CStruct * arg0, s32 arg1, f32 arg2);
extern f32 lbl_802ACBE0;

bool fn_801C5800(Unk_C7387A53 *arg0, s32 arg1, CScript *arg2) {
    fn_8012772C(arg2->unk0x18, QB_PREVIOUSPHYSICSSTATEDURATION,
                (f32)((f64)(u32)arg0->unk0x24) * lbl_802ACBE0);
    return true;
}
