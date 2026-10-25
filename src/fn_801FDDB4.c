// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FDDB4-0x801FDE1C (104B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AE7C4[];
extern char lbl_802AE7D8[];
void fn_8009F53C(void);
void *fn_801FDDB4(Unk_9AA07378 *arg0) {
    f32 temp_f0;
    fn_8009F53C();
    temp_f0 = *(f32 *)lbl_802AE7C4;
    arg0->unk0x18 = (s32)lbl_802AE7D8;
    arg0->unk0x4 = QB_PROJECTILECOLLISION;
    *((f32 *)&arg0->unk0x20) = temp_f0;
    *((f32 *)&arg0->unk0x24) = temp_f0;
    arg0->unk0x2C = 0;
    arg0->unk0x28 = 0;
    arg0->unk0x48 = 0;
    return arg0;
}
