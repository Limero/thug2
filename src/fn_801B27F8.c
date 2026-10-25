// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B27F8-0x801B2900 (264B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern f32 lbl_802ABF2C;
extern f32 lbl_802ABF30;
extern f32 lbl_802ABF34;
extern f32 lbl_802ABF38;
extern f32 fn_800144C8(void);
void fn_800086B0(Unk_C7387A53 * arg0, Unk_DB0E2BAB * arg1, f32 farg0);

typedef struct { f32 a, b, c, d; } tmp48_s;

register void *obj __asm__("r31");

bool fn_801B27F8(void *arg0) {
    __ps_t sp8[8];
    tmp48_s tmp;
    register char *p8 __asm__("r29");
    register char *p48 __asm__("r30");
    register void *cA __asm__("r10");
    void *cB;
    void *cC;
    __ps_t pr6;
    __ps_t pr7;
    f32 C;
    f32 D;
    f32 t;
    f32 v;
    f32 nv;
    s32 i4;

    obj = arg0;
    p8 = (char *)sp8;
    p48 = (char *)&tmp;
    for (i4 = 4; i4 != 0; i4--) {
        __asm__ volatile("");
    }

    t = fn_800144C8() * lbl_802ABF2C;
    v = *(f32 *)((char *)obj + (s32)0x1C) * lbl_802ABF30;
    nv = v * t + *(f32 *)((char *)obj + (s32)0xB8);
    *(f32 *)((char *)obj + (s32)0xB8) = nv;
    fn_800086B0((char *)obj + (s32)0x20, sp8, nv);

    cA = *(void **)((char *)obj + (s32)0xC);
    pr6 = sp8[6];
    C = lbl_802ABF34;
    *(__ps_t *)((char *)cA + (s32)0x58) = pr6;
    pr7 = sp8[7];
    D = lbl_802ABF38;
    *(__ps_t *)((char *)cA + (s32)0x60) = pr7;

    cB = *(void **)((char *)obj + (s32)0xC);
    *(__ps_t *)((char *)cB + (s32)0x78) = sp8[0];
    *(__ps_t *)((char *)cB + (s32)0x80) = ((__ps_t *)p8)[1];
    *(__ps_t *)((char *)cB + (s32)0x88) = sp8[2];
    {
        __ps_t pr3 = sp8[3];

        *(__ps_t *)((char *)cB + (s32)0x90) = pr3;
    }
    *(__ps_t *)((char *)cB + (s32)0x98) = sp8[4];
    *(__ps_t *)((char *)cB + (s32)0xA0) = sp8[5];
    *(__ps_t *)((char *)cB + (s32)0xA8) = sp8[6];
    *(__ps_t *)((char *)cB + (s32)0xB0) = sp8[7];

    cC = *(void **)((char *)obj + (s32)0xC);
    {
        tmp48_s *t48 = (tmp48_s *)p48;

        tmp.a = C;
        t48->b = C;
        t48->c = C;
        t48->d = D;
    }
    *(__ps_t *)((char *)cC + (s32)0xA8) = *(__ps_t *)&tmp.a;
    *(__ps_t *)((char *)cC + (s32)0xB0) = *(__ps_t *)&tmp.c;
    return true;
}
