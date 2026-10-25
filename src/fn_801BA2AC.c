// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BA2AC-0x801BA348 (156B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetInteger(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 GetChecksum_3(Unk_6A70655D * arg0, u32 arg1);
extern f32 fn_8012570C(s32 arg0, s32 arg1);
bool fn_801BA2AC(void *arg0, CStruct *arg1) {
    s32 sp8;
    GetInteger(arg1, 0, &sp8, 1);
    if (sp8 == 0) {
        ((Unk_C8FEE62D *)arg0)->unk0x1C = sp8;
    } else {
        ((Unk_C8FEE62D *)arg0)->unk0x1C = 2;
        arg0 = (void *)GetChecksum_3(((Unk_C8FEE62D *)arg0)->unk0xC, QB_MOTION);
        if (arg0 != NULL) {
            *((f32 *)&((Unk_C8FEE62D *)arg0)->unk0x28) = fn_8012570C(QB_PED_SKATER_DELTAV, 0);
            *((f32 *)&((Unk_C8FEE62D *)arg0)->unk0x2C) = fn_8012570C(QB_PED_SKATER_DELTAV, 0);
        }
    }
    return true;
}
