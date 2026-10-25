// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F4040-0x800F40B8 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Ident: vtable dispatch wrapper (obj+0x50 = vtable). First call: vtable[0x3C]
// with (obj + vtable[0x38] s16 offset, arg1). Second: vtable[0x2C] with
// (obj + vtable[0x28] s16 offset, arg1, 0,0,0,0). Returns (result == 0) —
// want's subfic/adde (m2c rendered it as (0-X)+X+M2C_CARRY).
#include "types.h"
#include "structs.h"

s32 fn_800F4040(Unk_C7387A53 *arg0, s32 arg1) {
    Unk_3D886BE8 *vt;
    s32 r;

    vt = (void *)arg0->unk0x50;
    vt->unk0x3C((char *)arg0 + vt->unk0x38, arg1);
    vt = (void *)arg0->unk0x50;
    r = vt->unk0x2C((char *)arg0 + vt->unk0x28, arg1, 0, 0, 0, 0);
    return r == 0;
}