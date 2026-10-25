// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CFFB0-0x801CFFF8 (72B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_80141988(Unk_C7387A53 *);
extern s32 GetChecksum_3(Unk_6A70655D *, u32);
extern void fn_801FF54C(Unk_31DE137E *, s32);
bool fn_801CFFB0(Unk_DFF20570 *arg0) {
    arg0->unk0x358 = 0;
    fn_801FF54C(GetChecksum_3(fn_80141988(arg0->unk0xC), QB_CAMERALOOKAROUND), 0);
    return true;
}
