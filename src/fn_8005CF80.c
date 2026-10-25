// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005CF80-0x8005CFC0 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8005D420(s32, void *, s32);
s32 fn_8005CF80(Unk_9994C3F5 *arg0, s32 arg1) {
    s32 sp8;
    sp8 = arg1;
    if ((s32) arg0->unk0x8 == 0) {
        return 0;
    }
    return fn_8005D420((s32) arg0->unk0x8, &sp8, 1);
}
