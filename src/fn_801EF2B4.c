// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EF2B4-0x801EF2F8 (68B). Byte-identical.
#include "types.h"
#include "structs.h"

extern f32 fn_801EF3A8(Unk_C7387A53 * arg0, s32 * arg1);

s32 fn_801EF2B4(Unk_C7387A53 *arg0) {
    s32 sp8;

    return fn_801EF3A8(arg0, &sp8) <= *((f32 *)&arg0->unk0x2C);
}
