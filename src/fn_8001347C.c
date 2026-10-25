// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001347C-0x800134AC (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Matching key: the field is re-read after its own decrement (want has a
// second `lwz r0, 0x38(r3)` feeding both the ==0 test and the 0x14 store).
// ngccc forwards the value from the preceding store — even from a
// `*((volatile s32 *)&...)` load — unless the STORE is volatile too. Writing
// both the store and the reload through `*((volatile s32 *)&arg0->unk0x38)`
// reproduces the pair verbatim (plain store + volatile load = `mr r0, r10`).
#include "types.h"
#include "structs.h"

extern s32 lbl_802FFF10;

void fn_8001347C(Unk_C8FEE62D *arg0) {
    s32 v;
    lbl_802FFF10 -= 1;
    *((volatile s32 *)&arg0->unk0x38) = *((volatile s32 *)&arg0->unk0x38) - 1;
    v = *((volatile s32 *)&arg0->unk0x38);
    if (v == 0) {
        arg0->unk0x14 = v;
    }
}
