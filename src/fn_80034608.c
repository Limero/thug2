// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80034608-0x80034684 (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

/* arg0 +0x14 is the vtable pointer, +0x18 starts a 0x400-byte f32 array
   (64 rows x 4 floats).  File-local, because the shared Unk_C8FEE62D class
   types +0x18 as s32 (corpus-wide majority vote) and the f32 stores need the
   real width (M6.89d-note). */
typedef struct {
    char pad0x14[0x14];
    s32 vt;
    f32 v[0x100];
} S_34608;

extern f32 lbl_80291C88;
extern char lbl_80291CE0[];
void fn_80033538(void *);

void *fn_80034608(void *arg0) {
    S_34608 *o = (S_34608 *)arg0;
    f32 *p;
    s32 i;
    f32 f0;
    f32 f13;

    fn_80033538(o);
    o->vt = (s32)lbl_80291CE0;
    f0 = 0.0f;
    f13 = lbl_80291C88;
    p = o->v;
    for (i = 0; i < 0x40; i++) {
        p[0] = f0; p[1] = f0; p[2] = f0; p[3] = f13;
        p += 4;
    }
    for (i = 0; i < 0x40; i++) { }
    return arg0;
}
