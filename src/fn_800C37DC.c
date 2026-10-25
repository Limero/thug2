// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C37DC-0x800C3A24 (584B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern f32 lbl_80299078;
extern f32 lbl_8029907C;
extern f32 lbl_80299080;
extern f32 lbl_80299084;

f32 tanf(f32);
f32 atan2f(f32, f32);

/* File-local layouts: the shared Unk_* classes mis-type several of these
   slots, and the true widths decide the FPR/GPR counts. */
typedef struct Elem {
    char _p00[0x10];
    f32 f_10;
    f32 f_14;
    char _p18[0xA0];
    s32 i_B8;
    char _pBC[0x124];
} Elem;

typedef struct Obj {
    char _p000[0x158];
    f32 f_158;
    char _p15C[0x50];
    s32 n_1AC;
    char _p1B0[4];
    f32 f_1B4;
    f32 f_1B8;
    f32 f_1BC;
    char _p1C0[0x130];
    Elem *base_2F0;
    char _p2F4[0x30];
    f32 f_324;
    char _p328[0xFFC];
    f32 f_1324;
} Obj;

void fn_800C37DC(Obj *arg0) {
    f32 v324;
    f32 v1324;
    f32 k84;
    f32 qa;
    f32 qb;
    f32 r_28;
    f32 r_27;
    f32 r_29;
    f32 r_1;
    register s32 i __asm__("r11");
    s32 off;
    Elem *e;
    s32 sel;
    s32 n;
    f32 out0;
    f32 out1;

    volatile double _dummy0;
    volatile double _dummy1;
    volatile double _dummy2;
    volatile double _dummy3;
    volatile double _dummy4;

    v1324 = arg0->f_1324;
    v324 = arg0->f_324;
    arg0->f_1324 = ((v324 - v1324) * (arg0->f_158 * lbl_80299078)) + v1324;
    if (__builtin_fabsf(v324) > lbl_80299080) {
        qa = tanf(v324 * arg0->f_1B4);
        qa = arg0->f_1B8 / qa;
        if (qa > lbl_8029907C) {
            k84 = lbl_80299084;
            r_28 = -atan2f(arg0->f_1B8, qa - (arg0->f_1BC * k84));
            r_27 = -atan2f(arg0->f_1B8, (arg0->f_1BC * k84) + qa);
        } else {
            qa = -qa;
            k84 = lbl_80299084;
            r_28 = atan2f(arg0->f_1B8, (arg0->f_1BC * k84) + qa);
            r_27 = atan2f(arg0->f_1B8, qa - (arg0->f_1BC * k84));
        }
    } else {
        r_28 = lbl_8029907C;
        r_27 = r_28;
    }

    if (__builtin_fabsf(arg0->f_1324) > lbl_80299080) {
        qb = tanf(arg0->f_1324 * arg0->f_1B4);
        qb = arg0->f_1B8 / qb;
        if (qb > lbl_8029907C) {
            k84 = lbl_80299084;
            r_29 = -atan2f(arg0->f_1B8, qb - (arg0->f_1BC * k84));
            r_1 = -atan2f(arg0->f_1B8, (arg0->f_1BC * k84) + qb);
        } else {
            qb = -qb;
            k84 = lbl_80299084;
            r_29 = atan2f(arg0->f_1B8, (arg0->f_1BC * k84) + qb);
            r_1 = atan2f(arg0->f_1B8, qb - (arg0->f_1BC * k84));
        }
    } else {
        r_29 = lbl_8029907C;
        r_1 = r_29;
    }

    n = arg0->n_1AC;
    i = n - 1;
    if (n != 0) {
        off = ((i * 0x10) - i) << 5;
        do {
            e = (Elem *)((char *)arg0->base_2F0 + off);
            sel = e->i_B8;
            if (sel != 0) {
                out0 = r_27;
                if (sel == 1) {
                    out0 = r_28;
                }
                e->f_10 = out0;
                out1 = r_1;
                if (sel == 1) {
                    out1 = r_29;
                }
                e->f_14 = out1;
            }
            off -= 0x1E0;
        } while (--i != -1);
    }
}
