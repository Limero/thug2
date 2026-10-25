// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80009818-0x800098F4 (220B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
s32 fn_80009818(s8 *arg0, void **arg1) {
    s32 var_r8 = 1;
    s32 var_r7 = 0;
    s8 *var_r3 = arg0;
    do {
        void *p;
        void *q;
        register s32 cuw __asm__("r9");
        s8 cs;
        p = *arg1;
        __asm__("mr %0,%1" : "=r"(q) : "r"(p));
        cuw = *(u8 *)*arg1;
        cs = (s8)cuw;
        switch (cs) {
        case 0x20:
            *(u8 *)var_r3 = (u8)cuw;
            var_r8 = 0;
            var_r3 += 1;
            *arg1 += 1;
            break;
        case 0x5C:
            *arg1 = q + 1;
            if (*(s8 *)(q + 1) == 0x5F) {
                *(u8 *)var_r3 = 0x20;
                var_r3 += 1;
                *arg1 += 1;
                break;
            }
            if (*(s8 *)(q + 1) == 0x6E) {
                void *q1;
                q1 = q + 1;
                var_r7 = 1;
                *arg1 = q1 + 1;
                var_r8 = 0;
                break;
            }
            *(s8 *)var_r3 = cs;
            *(u8 *)(var_r3 + 1) = *(u8 *)*arg1;
            var_r3 += 1;
            var_r3 += 1;
            *arg1 += 1;
            break;
        case 0x00:
            var_r7 = 2;
            var_r8 = 0;
            break;
        default:
            *(u8 *)var_r3 = *(u8 *)q;
            var_r3 += 1;
            *arg1 += 1;
            break;
        }
    } while (var_r8 != 0);
    *(u8 *)var_r3 = (u8)var_r8;
    return var_r7;
}
