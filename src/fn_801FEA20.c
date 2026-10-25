// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FEA20-0x801FEA78 (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
f32 fn_801417B8(CScript *, s32);
s32 fn_8012772C(CStruct *, s32, f32);

bool fn_801FEA20(Unk_C7387A53 *arg0, s32 arg1, CScript *arg2) {
    s32 temp_r29;

    temp_r29 = arg2->unk0x18;
    fn_8012772C(temp_r29, QB_FACTORCOMPLETE, *((f32 *)&arg0->unk0x20) / fn_801417B8(arg0->unk0xC, QB_PHYSICS_RUNTIMER_DURATION));
    return true;
}
