// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F99D8-0x801F9A24 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern void *fn_801F9820(Unk_C7387A53 *);

void fn_801F99D8(Unk_C7387A53 *arg0, Unk_C4654E77 *arg1) {
    Unk_C4654E77 *dst;

    dst = fn_801F9820(arg0);
    dst->unk0x8 = arg1->unk0x8;
    dst->unk0x10 = arg1->unk0x10;
    dst->unk0x18 = arg1->unk0x18;
    dst->unk0x20 = arg1->unk0x20;
}
