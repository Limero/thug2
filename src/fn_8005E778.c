// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005E778-0x8005E898 (288B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct VT_s {
    char pad0[0x20];
    s16 off20; /* vtable method offset — lha */
    char pad22[2];
    void (*fn24)(void *);
} VT_s;

typedef struct S_s {
    void *unk0;  /* passed as arg0 to fn_8005C5BC / fn_8005C5F0 */
    char pad4[0xC];
    f32 f10;
    f32 f14;
    char pad18[0x34];
    VT_s *vt4C;
} S_s;

extern f32 lbl_80293B50; /* 1.0f    */
extern f32 lbl_80293B60; /* 0.0f    */
extern f32 lbl_80293B64; /* 1.25f   */
extern f32 lbl_80293B68; /* 1.1666f */

s32 fn_8005C5BC(void *);
s32 fn_8005C5F0(void *);

void fn_8005E778(S_s *arg0, f32 farg0, f32 farg1) {
    /* retail allocates a 0x28-byte locals region; only the 8-byte int->f64
       conversion slot at 0x28(r1) is live. this pad restores the frame. */
    char pad[32];
    f32 var_f12 = lbl_80293B50;
    f32 var_f28 = var_f12;
    /* hard-register pins (all three are load-bearing; ablating any one costs
       7-8 words): retail's FP allocation order is f28=scale0, f29=arg0,
       f30=arg1, f31=(f64)magic, then f11=scale1prod, f12=scale1, f13=scale0prod.
       Unpinned, ngccc rotates the three call-crossing values by one and swaps
       the two volatile products. */
    register f32 a0 __asm__("fr29");
    register f32 a1 __asm__("fr30");
    register f32 p1 __asm__("fr13");
    f32 p2;

    a0 = farg0;
    a1 = farg1;
    if (arg0->unk0 != NULL) {
        var_f28 = (f32)(f64)(u32)fn_8005C5BC(arg0->unk0);
        var_f12 = (f32)(f64)(u32)fn_8005C5F0(arg0->unk0);
    }
    p1 = var_f28 * a0;
    p2 = var_f12 * a1;
    if (a0 > lbl_80293B60) {
        if (p1 <= lbl_80293B64) {
            a0 = lbl_80293B64 / var_f28;
        }
    }
    if (a1 > lbl_80293B60) {
        if (p2 <= lbl_80293B68) {
            a1 = lbl_80293B68 / var_f12;
        }
    }
    arg0->f10 = a0;
    arg0->f14 = a1;
    ((void (*)(void *))arg0->vt4C->fn24)((char *)arg0 + arg0->vt4C->off20);
}
