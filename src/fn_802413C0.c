// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802413C0-0x8024144C (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 fn_800546A0(s32);
extern void fn_800580A0(Unk_C8FEE62D *, void *);
extern f32 lbl_802B1124;
void fn_802413C0(Unk_C7387A53 *arg0, f32 farg0) {
    volatile struct { f32 _f0; f32 _f1; f32 _f2; } fr;
    volatile double _dummy;
    register void *p11 __asm__("r11");
    register void *r4v __asm__("r4");
    s32 t;

    t = fn_800546A0(*(s32 *)arg0);
    if (arg0->unk0x28 & 1) {
        p11 = &fr;
        {
            f32 *q = (f32 *)p11;
            fr._f0 = lbl_802B1124;
            q[2] = farg0;
        }
        r4v = p11;
    } else {
        p11 = &fr;
        {
            f32 *q = (f32 *)p11;
            fr._f0 = farg0;
            q[2] = lbl_802B1124;
        }
        r4v = p11;
    }
    fr._f1 = lbl_802B1124;
    fn_800580A0(t, r4v);
}
