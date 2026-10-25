// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80013238-0x80013254 (28B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
s32 fn_80013238(Unk_C7387A53 *self) {
    s32 flag = 1;
    if (self->unk0x38 <= 0)
        flag = 0;
    return flag;
}
