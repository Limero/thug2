// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E2A18-0x800E2A70 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
void fn_80069C58(s32, s32, s32);
#include "structs.h"
s32 fn_80128D40(s32, s32, s32, s32);
bool fn_800E2A18(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp8[4];   /* the callee fills a 16-byte out buffer */

    fn_80128D40(arg1, 0, &sp8[0], 1);
    if ((s32) arg0->unk0x20 != 0) {
        fn_80069C58((s32) arg0->unk0x20, 0, &sp8[0]);
    }
    return true;
}
