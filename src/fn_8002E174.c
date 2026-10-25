// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002E174-0x8002E1CC (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

extern f32 lbl_80291960;
extern f32 lbl_80291964;
extern f32 lbl_80291968;
extern f32 lbl_8029196C;

typedef struct {
    char _pad[0x60];
    s32 v;
} S2E174;

void fn_8002FC8C(void *, u32, s32, s32, s32, f32, f32, f32, f32);

void fn_8002E174(void *arg0, s32 arg1) {
    ((S2E174 *)arg0)->v = arg1;
    fn_8002FC8C(arg0, QB_DEFAULT, 0, 0, 0,
                lbl_80291960, lbl_80291964, lbl_80291968, lbl_8029196C);
}
