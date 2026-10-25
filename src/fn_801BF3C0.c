// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BF3C0-0x801BF438 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

typedef struct {
    char pad0[4];
    s32 unk4;
    char pad8[0x10];
    s32 unk18;
    char pad1C[0x14];
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} CamBF3C0;

extern char lbl_802AC630[];
void fn_8009F53C(void *);

void *fn_801BF3C0(CamBF3C0 *arg0) {
    register char *pg0 __asm__("r11");
    register char *pg1 __asm__("r9");
    f32 f0;
    f32 f13;
    s32 i;
    f32 *p;

    fn_8009F53C(arg0);
    arg0->unk18 = (s32)lbl_802AC630;
    for (i = 4; i != 0; i--) {
        __asm__ volatile("");
    }
    __asm__ volatile("" ::: "memory");
    pg0 = (char *)0x802B0000;
    pg1 = (char *)0x802B0000;
    f0 = *(f32 *)(pg0 - 0x3A1C);
    f13 = *(f32 *)(pg1 - 0x3A18);
    arg0->unk4 = QB_WALKCAMERA;
    p = (f32 *)((char *)arg0 + 0x30);
    arg0->unk30 = f0;
    p[1] = f0;
    p[2] = f0;
    p[3] = f13;
    return arg0;
}
