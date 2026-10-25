// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F1E1C-0x800F1EF0 (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse
#include "types.h"

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
} E;

s32 fn_800F0374(s32);
void fn_800F1790(void *, s32);
void fn_800F18B0(void *, s32, s32);

s32 fn_800F1E1C(void *arg0, s32 arg1) {
    s32 i;
    s32 res;
    s32 *hp;
    E *p;
    s32 n;
    s32 *q9;
    s32 *q11;
    s32 v8;
    s32 v0;
    s32 v4;

    i = 0;
    fn_800F0374(arg1);
    res = 0;
    if ((u32)res < (u32)*(s32 *)((char *)arg0 + 0x10008)) {
        hp = (s32 *)((char *)arg0 + 0x10000);
        p = (E *)((char *)hp + 0xC);
        do {
            if (p->f0 == arg1) {
                fn_800F1790(arg0, i);
                n = hp[2] - 1;
                hp[2] = n;
                if (i != n) {
                    q9 = (s32 *)((char *)(n * 0xC + (s32)arg0) + 0x10000);
                    q11 = q9 + 3;
                    v0 = q9[3];
                    v4 = q11[1];
                    v8 = q11[2];
                    p->f0 = v0;
                    p->f4 = v4;
                    p->f8 = v8;
                    fn_800F18B0(arg0, hp[2], i);
                }
                res = 1;
                break;
            }
            i++;
            p = (E *)((char *)p + 0xC);
        } while ((u32)i < (u32)hp[2]);
    }
    return res;
}
