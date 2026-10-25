// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80240ED8-0x80240F28 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
s32 fn_800546A0(s32);
void fn_80057E7C(Unk_C8FEE62D *, void *);
void fn_80240ED8(s32 *arg0, __ps_t *arg1, s32 arg2) {
    ((Unk_18AF37A6 *)arg0)->unk0x18 = arg1[0];
    ((Unk_18AF37A6 *)arg0)->unk0x20 = arg1[1];
    if (arg2 == 1) {
        fn_80057E7C(fn_800546A0((s32)*arg0), arg1);
    }
}
