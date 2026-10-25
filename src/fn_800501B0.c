// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800501B0-0x800503BC (524B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_80292E74;   /* 1.0f                */
extern f64 lbl_80292E78;   /* 2^52                */
extern f64 lbl_80292E80;   /* 2^52 + 2^31         */
extern f32 lbl_80292E88;   /* 0.0625f             */
s32 fn_800145AC(void);
typedef struct { s32 w[6]; } S24;              /* 0x18-byte snap block */
typedef struct {                                /* 0x48-byte history record */
    f32 f0;
    char _4[0x14];
    f32 f18, f1c;
    char _20[0xC];
    f32 f2c, f30;
    char _34[0x14];
} Rec;
typedef struct {                                /* 0x4B8-byte CBlurEffect */
    Rec rec[16];
    f32 s480, s484, s488, s48c, s490, s494;     /* morph target block */
    f32 c498, c49c, c4a0, c4a4, c4a8, c4ac;     /* live (interpolated) values */
    u32 t0;                                     /* 0x4B0 last timestamp */
    u32 rem;                                    /* 0x4B4 remaining time */
} S501;
void fn_800501B0(S501 *arg0) {
    f32 var_f2;
    u32 now;
    u32 rem;
    u32 diff;
    s32 i;

    now = (u32)fn_800145AC();
    rem = arg0->rem;
    var_f2 = lbl_80292E74;
    if (rem != 0) {
        var_f2 = (f32)(now - arg0->t0) / (f32)rem;
    }
    diff = now - arg0->t0;
    arg0->rem = (diff < rem) ? (rem - diff) : 0;
    arg0->t0 = now;
    if (arg0->rem != 0) {
        arg0->c498 = (arg0->s480 - arg0->c498) * var_f2 + arg0->c498;
        arg0->c49c = (arg0->s484 - arg0->c49c) * var_f2 + arg0->c49c;
        arg0->c4a0 = (arg0->s488 - arg0->c4a0) * var_f2 + arg0->c4a0;
        arg0->c4a4 = (arg0->s48c - arg0->c4a4) * var_f2 + arg0->c4a4;
        arg0->c4a8 = (arg0->s490 - arg0->c4a8) * var_f2 + arg0->c4a8;
        arg0->c4ac = (arg0->s494 - arg0->c4ac) * var_f2 + arg0->c4ac;
    } else {
        *(S24 *)((char *)arg0 + 0x498) = *(S24 *)((char *)arg0 + 0x480);
    }
    for (i = 0; i < 16; i++) {
        f32 t, a, b, c, d;
        Rec *p = &arg0->rec[i];
        t = (f32)i * lbl_80292E88;
        a = arg0->c4a8 * t;
        b = arg0->c4ac * t;
        p->f18 = a;
        p->f1c = b;
        c = (arg0->c4a0 - lbl_80292E74) * t + lbl_80292E74;
        d = (arg0->c4a4 - lbl_80292E74) * t + lbl_80292E74;
        p->f2c = c;
        p->f30 = d;
        p->f0 = ((arg0->c49c - arg0->c498) * t + arg0->c498) * lbl_80292E88;
    }
}
