// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80016C70-0x80016D58 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

/* lbl_802FFF80 is a .data array of 16-byte (4 x s32) entries.  Byte-proven by
   the promoted siblings src/fn_80016D58.c / src/fn_80016E18.c and by the
   solved twin src/wip/fn_80016B50.c (0x80016B50-0x80016C70). */
typedef struct Ent {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
} Ent;

extern Ent lbl_802FFF80[];
extern f32 lbl_80290C10;
extern f32 lbl_80290C14;

/* GX_SetScissorBoxOffset = GXSetScissorBoxOffset, GX_SetScissor = GXSetScissor (both void),
   GX_SetViewport = GXSetViewport (six f32, no integer args). */
void GX_SetScissorBoxOffset(s32, s32);
void GX_SetScissor(s32, s32, s32, s32);
void GX_SetViewport(f32, f32, f32, f32, f32, f32);

void fn_80016C70(void) {
    Ent *e = &lbl_802FFF80[0];

    GX_SetScissorBoxOffset(0, 0);
    GX_SetScissor(e->f0, e->f4, e->f8, e->fC);
    GX_SetViewport((f32) (f64) e->f0, (f32) (f64) e->f4, (f32) (f64) e->f8,
                (f32) (f64) e->fC, lbl_80290C10, lbl_80290C14);
}
