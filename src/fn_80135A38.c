// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80135A38-0x80135AC8 (144B). Byte-identical.
#include "types.h"
// writeChannelData @ 0x80135A38
void writeChannelData(u16 *arg0, s32 arg1, void *arg2, s32 arg3, u32 arg4) {
    u16 *var_r3;
    u16 *var_r5;
    u16 *var_r8;
    u16 temp_r0;
    u32 var_r10;

    var_r3 = arg0;
    if (arg1 == 1) {
        u16 *src;
        register u16 *t9 __asm__("r9");
        var_r10 = 0U;
        t9 = *(u16 **)arg2;
        __asm__("" : "+r"(t9));
        src = t9 + arg3;
        if (var_r10 < arg4) {
            var_r5 = src;
            do {
                temp_r0 = *(u16 *)var_r5;
                var_r10 += 1;
                var_r5 += 1;
                *(u16 *)var_r3 = temp_r0;
                var_r3 += 1;
            } while (var_r10 < arg4);
        }
    } else {
        var_r5 = *(u16 **)arg2 + arg3;
        var_r8 = ((u16 **)arg2)[1] + arg3;
        var_r10 = 0U;
        while (var_r10 < arg4) {
            register u16 ta __asm__("r9");
            ta = *(u16 *)var_r5;
            var_r10 += 1;
            var_r5 += 1;
            *(u16 *)var_r3 = ta;
            *++var_r3 = *(u16 *)var_r8;
            var_r8 += 1;
            var_r3 += 1;
        }
    }
}
