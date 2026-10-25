// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EDA40-0x801EDAA0 (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void fn_8009F53C(void);
extern char lbl_802ADB18[];
void *fn_801EDA40(Unk_DB0E2BAB *arg0) {
    fn_8009F53C();
    arg0->unk0x18 = (s32)lbl_802ADB18;
    arg0->unk0x4 = QB_SKATERADJUSTPHYSICS;
    arg0->unk0x24 = 0;
    arg0->unk0x28 = 0;
    arg0->unk0x2C = 0;
    arg0->unk0x30 = 0;
    arg0->unk0x20 = 0;
    return arg0;
}
