// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AF78C-0x800AF7EC (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: 64-bit accumulator update — samples the monotonic u64
// counter fn_800144B4() = lbl_802FFF40, adds the running delta
// (new - *(o+0x34A8)) into the 64-bit integrator at o+0x34A0, then parks the
// fresh sample at o+0x34A8. The subfc/subfe (u64 subtract) + addc/adde
// (u64 add) pairs are why this needed the o+0x34A0/0x34A8 u64 typing.
#include "types.h"
#include "structs.h"
u64 fn_800144B4(void);
void fn_800AF78C(Unk_6315E9F3 *o) {
    o->unk0x34A0 += fn_800144B4() - o->unk0x34A8;
    o->unk0x34A8 = fn_800144B4();
}