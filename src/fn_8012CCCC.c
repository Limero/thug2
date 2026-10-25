// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012CCCC-0x8012CD84 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 Mth_Rnd(s32);
typedef struct {
    char pad0[0xC];
    u16 count;
    char padE[8];
    u8 arr[0x200];
} S;
void fn_8012CCCC(S *arg0, s32 arg1) {
    u32 i = 0;
    u32 total;
    u8 last;
    u8 *p = (u8 *)arg0 + 0x16;
    total = arg0->count * 10U;
    last = arg0->arr[arg0->count - 1];
    if (i < total) {
        u8 *b = p;
        __asm__("" : "+r"(b));
        do {
            s32 a, c;
            u8 t0, t1;
            i++;
            a = Mth_Rnd(arg0->count);
            c = Mth_Rnd(arg0->count);
            t0 = b[c];
            t1 = b[a];
            b[a] = t0;
            b[c] = t1;
        } while (i < total);
    }
    if (arg1 != 0 && arg0->arr[0] == last) {
        s32 idx = Mth_Rnd(arg0->count - 1) + 1;
        u8 *q = (u8 *)arg0;
        u8 t0, t1;
        __asm__("" : "+r"(q));
        q += 0x16;
        t0 = q[0];
        t1 = q[idx];
        q[0] = t1;
        q[idx] = t0;
    }
}
