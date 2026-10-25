// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AEE08-0x801AEE7C (116B). Byte-identical.
#include "types.h"
#include "structs.h"

register s32 r31_guard __asm__("r31");

extern char lbl_802ABCD8[];
extern s32 fn_8003E7CC(s32);
extern s32 fn_80128F94(Unk_9D4ED6AF *);

void *fn_801AEE08(Unk_9AA07378 *arg0) {
    s32 zero;
    void *var_r3;

    zero = 0;
    arg0->unk0x4 = arg0;
    arg0->unk0x8 = zero;
    arg0->unk0xC = arg0;
    arg0->unk0x10 = arg0;
    arg0->unk0x24 = zero;
    arg0->unk0x28 = zero;
    arg0->unk0x34 = zero;
    arg0->unk0x38 = zero;
    arg0->unk0x14 = (s32)lbl_802ABCD8;
    arg0->unk0x68 = fn_80128F94(fn_8003E7CC(0xC));
    arg0->unk0x3C = zero;
    var_r3 = arg0;
    arg0->unk0x40 = zero;
    return var_r3;
}
