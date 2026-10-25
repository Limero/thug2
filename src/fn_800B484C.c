// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B484C-0x800B4880 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

void fn_800B484C(Unk_9D191493 *arg0, s32 arg1, f32 farg0) {
    s32 n;
    s32 i;
    f32 *base;

    if ((s32)arg0->unk0x210 == 0) {
        return;
    }
    n = (s32)arg0->unk0x230;
    if (arg1 <= 0) {
        return;
    }
    if (arg1 > n) {
        return;
    }
    i = arg1 - 1;
    base = (f32 *)((char *)arg0 + 0x220);
    base[i] = farg0;
}
