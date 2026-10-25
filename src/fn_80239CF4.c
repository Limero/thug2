// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80239CF4-0x80239D84 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-sched-interblock
#include "types.h"
void fn_80239CF4(void *arg0) {
    s32 flags = (s32)arg0 + 0x3538;
    s32 vals = (s32)arg0 + 0x3530;
    s32 bs = (s32)arg0 + 0x353C;
    s32 row, col;
    for (row = 0; row <= 0x39; row++) {
        s32 b = row * 0x3A0 + bs;
        s32 idx = row * 0x3A0;
        for (col = 0; col < 0x3A; col++) {
            if (*(s32 *)(idx + flags) != 0) {
                *(s32 *)(idx + flags) = 0;
                *(s32 *)(idx + vals) = *(s32 *)(idx + vals) - *(s32 *)b;
            }
            if (*(s32 *)(idx + vals) > 0xF) *(s32 *)(idx + vals) = 0xF;
            if (*(s32 *)(idx + vals) < -0x10) *(s32 *)(idx + vals) = -0x10;
            b += 0x10;
            idx += 0x10;
        }
    }
}
