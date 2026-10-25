// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007BD70-0x8007BDC8 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8009A788(s16 *, u32, u32, s32, s32);
void fn_8007BD70(Unk_2BAD2BE8 *arg0) {
    fn_8009A788(*(s16 **) &arg0->unk0x18, arg0->unk0x2, arg0->unk0x6, (u16) ((*(volatile s32 *) &arg0->unk0x0 + *(volatile s32 *) &arg0->unk0x8) - 1), (u16) ((*(volatile s32 *) &arg0->unk0x4 + *(volatile s32 *) &arg0->unk0xC) - 1));
}
