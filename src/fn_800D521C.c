// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D521C-0x800D5304 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern s32 lbl_80303150;
extern f32 lbl_80299B38;
s32 Tmr_GetTime(void);
f32 sinf(f32);
void fn_800D521C(Unk_FCBBC883 *arg0) {
    volatile __ps_t t[2];
    __ps_t *tp;
    Unk_DF2324A8 *p;
    s32 tick;
    s32 n;
    u32 m;
    f32 sum;
    f32 f;

    tick = Tmr_GetTime();
    n = arg0->unk0x1F4;
    m = (u32)(lbl_80303150 + tick) % (u32)n;
    sum = arg0->unk0x1F0 * sinf((f32)(m * 2) * lbl_80299B38 / (f32)n);
    tp = (__ps_t *)t;
    __asm__("" : "+r"(tp));
    p = *((u32 * *)&arg0->unk0xC);
    arg0->unk0x1EC = sum;
    t[0] = p->unk0x58;
    tp[1] = p->unk0x60;
    f = *(f32 *)((char *)&t[0] + 4);
    *((f32 *)&arg0->unk0x1E8) = f;
    { f32 s2 = f + sum; *(f32 *)((char *)&t[0] + 4) = s2; }
    p->unk0x58 = t[0];
    p->unk0x60 = tp[1];
}
