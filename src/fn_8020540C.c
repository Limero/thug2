// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020540C-0x80205460 (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AF170[];
void *fn_8020540C(Unk_DB0E2BAB *arg0) {
    fn_8009F53C();
    arg0->unk0x18 = (s32)lbl_802AF170;
    arg0->unk0x4 = QB_TAGGINGCONTROL;
    arg0->unk0x20 = 0;
    arg0->unk0x24 = 0;
    return arg0;
}
