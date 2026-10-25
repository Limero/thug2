// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A1B2C-0x801A1B7C (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern const f32 lbl_802AB1C0;
extern const f32 lbl_802AB1C4;
extern s32 fn_8002DEAC(void *, s32, s32, f32, f32, f32, f32);
s32 fn_801A1B2C(void *arg0, f32 farg0) {
    register char *p __asm__("r9");
    f32 temp_f1;

    p = (char *)arg0;
    temp_f1 = lbl_802AB1C0;
    ((Unk_7469D341 *)p)->unk0x70 = 0;
    return fn_8002DEAC(p + (s32)0x74, 0, 0, temp_f1, farg0, temp_f1, lbl_802AB1C4);
}
