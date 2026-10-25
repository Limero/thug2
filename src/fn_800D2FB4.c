// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D2FB4-0x800D3018 (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80299A58[];
extern f32 lbl_80299A24;
extern void fn_8009F53C(Unk_C8FEE62D * arg0);

void *fn_800D2FB4(Unk_9AA07378 *arg0) {
    f32 temp_f0;

    fn_8009F53C(arg0);
    temp_f0 = lbl_80299A24;
    arg0->unk0x18 = (s32)lbl_80299A58;
    arg0->unk0x4 = QB_CARPHYSICS;
    *((f32 *)&arg0->unk0x1C) = temp_f0;
    *((f32 *)&arg0->unk0x20) = temp_f0;
    *((f32 *)&arg0->unk0x24) = temp_f0;
    arg0->unk0x48 = 1;
    return arg0;
}
