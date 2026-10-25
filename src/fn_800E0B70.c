// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E0B70-0x800E0BE0 (112B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80303150[];
extern char lbl_8029A6D0[];
void *fn_800E0B70(Unk_C8FEE62D *arg0) {
    fn_8009F53C();
    arg0->unk0x18 = (s32)lbl_8029A6D0;
    arg0->unk0x4 = QB_PARTICLE;
    arg0->unk0x1C = 0;
    arg0->unk0x20 = 0;
    arg0->unk0x28 = 0;
    arg0->unk0x30 = 0;
    arg0->unk0x2C = (s32) (*(s32 *)&lbl_80303150 + Tmr_GetTime());
    return arg0;
}
