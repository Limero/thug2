// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80003AE8-0x80003BE4 (252B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Unk_in {
    f32 f_0x00;
    f32 f_0x04;
    f32 f_0x08;
    f32 f_0x0C;
    f32 f_0x10;
    f32 f_0x14;
    f32 f_0x18;
    f32 f_0x1C;
    f32 f_0x20;
    f32 f_0x24;
    f32 f_0x28;
} Unk_in;

typedef struct Unk_out {
    f32 f_0x00;
    f32 f_0x04;
    f32 f_0x08;
    f32 f_0x0C;
} Unk_out;

extern f32 lbl_8028FC38;
extern f32 lbl_8028FC3C;
extern f32 lbl_8028FC40;
extern f32 lbl_8028FC44;

f32 fn_80003984(f32 y, f32 x);
f32 asinf(f32);
f32 cosf(f32);

/* Frame pad only — see STATUS note above. */
typedef struct {
    char x[24];
} Pad;

void fn_80003AE8(Unk_in *arg0, Unk_out *arg1) {
    f32 v;
    f32 pitch;
    f32 c;
    f32 yaw0;
    f32 yaw1;
    Pad _pad;

    v = arg0->f_0x08;
    if (v > lbl_8028FC38) {
        v = lbl_8028FC38;
    }
    if (v < lbl_8028FC3C) {
        v = lbl_8028FC3C;
    }
    pitch = -asinf(v);
    c = cosf(pitch);
    if (__builtin_fabsf(c) > lbl_8028FC40) {
        yaw0 = fn_80003984(-arg0->f_0x18 / c, arg0->f_0x28 / c);
        yaw1 = fn_80003984(-arg0->f_0x04 / c, arg0->f_0x00 / c);
    } else {
        yaw0 = lbl_8028FC44;
        yaw1 = fn_80003984(arg0->f_0x10, arg0->f_0x14);
    }
    arg1->f_0x00 = yaw0;
    arg1->f_0x04 = pitch;
    arg1->f_0x08 = yaw1;
    arg1->f_0x0C = lbl_8028FC38;
}
