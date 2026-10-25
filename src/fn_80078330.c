// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80078330-0x800784E0 (432B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-rerun-cse-after-loop
#include "types.h"
void fn_80078104(u8 *, s32, u32, u32, u8 *, u8 *, u8 *, u8 *);

void fn_80078330(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    s32 j;
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
    u8 *p;

    for (i = 0; i < (s32) (u16) (1 << *(u8 *) ((char *) arg0 + 7)); i++) {
        for (j = 0; j < (s32) (u16) (1 << *(u8 *) ((char *) arg0 + 6)); j++) {
            fn_80078104(arg1, (u16) (1 << *(volatile u8 *) ((char *) arg0 + 6)), j, i, &b0, &b1, &b2, &b3);
            p = (u8 *) arg2 + i * (u16) (1 << *(u8 *) ((char *) arg0 + 6)) * 4 + j * 4;
            if (arg3 & 0x200) {
                u8 t1, t2, t3;
                *p++ = b0;
                t1 = b1;
                t2 = b2;
                *p++ = t1;
                t3 = b3;
                *p++ = t2;
                *p++ = t3;
            } else {
                if (arg3 == 0) {
                    u8 u1, u2;
                    *p++ = b0;
                    u1 = b1;
                    u2 = b2;
                    *p++ = u1;
                    *p++ = u2;
                    *p++ = 0xFF;
                }
                if (arg3 & 4) {
                    p += 2;
                    *++p = b1;
                    p++;
                }
                if (arg3 & 8) {
                    p += 2;
                    *++p = b0;
                    p++;
                }
                if (arg3 & 0x10) {
                    p[3] = b2;
                }
            }
        }
    }
}
