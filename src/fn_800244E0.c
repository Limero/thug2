// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800244E0-0x80024564 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad0x0[0xB8];
    f32 fB8;
    f32 fBC;
    char pad0xC0[0xC];
    f32 fCC;
} Obj244E0;

extern f32 lbl_80291330;
extern f32 lbl_80291334;
extern f32 lbl_80291338;

f32 tanf(f32);
f32 atanf(f32);
f32 fn_8005E2D0(void);
void fn_80024564(Obj244E0 *arg0);

void fn_800244E0(Obj244E0 *arg0) {
    volatile double _dummy;
    f32 t;
    f32 r;
    t = tanf(arg0->fB8 * lbl_80291330 * lbl_80291334);
    r = atanf(t * fn_8005E2D0() / arg0->fCC);
    arg0->fBC = 2.0f * r * lbl_80291338;
    fn_80024564(arg0);
}
