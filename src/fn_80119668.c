// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80119668-0x801196B8 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// fn_80119668: scales a 2- or 5-f32 run of a Script-pool object by farg0 * lbl_8029D4DC
// (run=5 when the s32 at +0x14 == 2). Suggested rename: fn_ScalePoolFloats.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029D4DC;
void fn_80119668(Unk_C8FEE62D *arg0, f32 farg0) {
    u32 i;
    u32 count = 2;
    if (arg0->unk0x14 == 2) {
        count = 5;
    }
    for (i = 0; i < count; i++) {
        ((f32 *)arg0)[i] = ((f32 *)arg0)[i] * farg0 * lbl_8029D4DC;
    }
}
