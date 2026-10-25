// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80016B50-0x80016C70 (288B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

/* lbl_802FFF80 is a .data array of 16-byte (4 x s32) entries; see the
   promoted siblings src/fn_80016D58.c and src/fn_80016E18.c for the same
   base.  The promoted twins 0x80016B50 / 0x80016C70 are the only difference. */
typedef struct Ent {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
} Ent;

extern Ent lbl_802FFF80[];
extern f32 lbl_80290C00;
extern f32 lbl_80290C04;

/* GX_SetScissorBoxOffset = GXSetScissorBoxOffset, GX_SetScissor = GXSetScissor (both
   void), GX_SetViewport = GXSetViewport (six f32, no integer args). */
void GX_SetScissorBoxOffset(s32, s32);
void GX_SetScissor(s32, s32, s32, s32);
void GX_SetViewport(f32, f32, f32, f32, f32, f32);

void fn_80016B50(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    /* The signed int->f32 conversions all share this one stack double; the
       `volatile` qualifier is WRONG here (it moves the slot to r1+0x18). */
    union { s32 w[2]; f64 d; } u;
    Ent *e = &lbl_802FFF80[arg0];

    if (arg1 != -1) {
        e->f0 = arg1;
    }
    if (arg2 != -1) {
        e->f4 = arg2;
    }
    if (arg3 != -1) {
        e->f8 = arg3;
    }
    if (arg4 != -1) {
        e->fC = arg4;
    }
    GX_SetScissorBoxOffset(0, 0);
    GX_SetScissor(e->f0, e->f4, e->f8, e->fC);
    GX_SetViewport((f32) (f64) e->f0, (f32) (f64) e->f4, (f32) (f64) e->f8,
                (f32) (f64) e->fC, lbl_80290C00, lbl_80290C04);
}
