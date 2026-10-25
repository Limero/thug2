// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80033C1C-0x80033CF8 (220B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

/* arg0 + 0x24 is a float (lfs/lfs/lfs), and the guard reads it twice
   (as the fcmpu operand and as fn_8002AE34's f1). The corpus-merged
   CScript votes it s32, so declare the real layout file-locally. */
typedef struct {
    char _00[0x18];
    s32 unk18;
    s32 unk1C;
    char _20[4];
    f32 unk24;
} S_80033C1C;

/* fn_80033ED0() result: fields at +0x8 and +0xC. m2c wrote
   `*(s32 *)((s32 *)r + 0x8)` which ngccc scales to 0x20. */
typedef struct {
    char _00[8];
    s32 unk8;
    s32 unkC;
} S_80033ED0;

extern f32 lbl_80291C58;

/* 5th declared arg is the float, 6th the int — see the note above. */
void fn_8002AE34(s32, s32, s32, s32, f32, s32);
s32 fn_80033ED0(S_80033C1C *);
s32 fn_8006FB50(void *, s32);

s32 fn_80033C1C(S_80033C1C *arg0, s32 arg1) {
    register s32 ret __asm__("r3");
    s32 t;
    register s32 v __asm__("r9");
    register s32 w __asm__("r0");
    f32 f;
    f32 K;

    if (arg0->unk18 == 0) {
        return 0;
    }
    t = arg0->unk1C;
    if (t == 0) {
        return 0;
    }
    f = arg0->unk24;
    K = lbl_80291C58;
    ret = 0;
    if (!(f <= K)) {
        arg0->unk18 = fn_8006FB50((void *)t, 0);
        t = fn_80033ED0(arg0);
        v = ((S_80033ED0 *)t)->unk8;
        __asm__ volatile("cmpwi %1,0\n\tli %0,0\n\tbeq 8f\n\taddi %0,%1,0x408\n8:\n"
                         : "=&r"(w) : "r"(v) : "cr0");
        *(s32 *)((char *)arg0->unk1C + 0x20C) = w;
        t = fn_80033ED0(arg0);
        *(s32 *)((char *)arg0->unk1C + 0x210) = ((S_80033ED0 *)t)->unkC;
        fn_8002AE34(arg0->unk18, arg1, arg1 + 0x400, arg1 + 0x800, arg0->unk24, arg0->unk1C);
        fn_8006FB50((void *)arg0->unk1C, 1);
        ret = 1;
    }
    return ret;
}
