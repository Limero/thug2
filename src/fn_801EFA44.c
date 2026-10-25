// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EFA44-0x801EFA84 (64B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8009F010(s32, s32, s32);
void fn_801EFA44(Unk_31DE137E *arg0) {
    arg0->unk0x1C &= ~0x10;
    fn_8009F010(arg0->unk0xC, QB_GOALHASENDED, 0);
}
