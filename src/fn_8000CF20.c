// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000CF20-0x8000CFB0 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -Os
#include "types.h"
#include "types.h"
#include "structs.h"
void *memcpy(void *, const void *, s32);
u32 fn_8000CF20(CStruct *arg0, void *arg1, u32 arg2) {
    s32 *r9;
    u32 avail;

    r9 = *(s32 **)&arg0->unk0x10;
    avail = r9[4] - r9[3];
    if (arg2 > avail) {
        arg2 = avail;
    }
    if (r9[0] != 0) {
        memcpy(arg1, (void *)(r9[2] + r9[3]), arg2);
    } else {
        memcpy(arg1, (void *)(r9[1] + r9[3]), arg2);
    }
    r9 = *(s32 **)&arg0->unk0x10;
    r9[3] = r9[3] + arg2;
    return arg2;
}
