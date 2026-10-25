// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80087284-0x800872FC (120B). Byte-identical.
// (range corrected 2026-09-01: m2c boundary cut at 0xD0; real symbol ends 0xFC)
// IDENTIFIED (2026-09-01): unpacks a u32 into the 3-byte .data global
// lbl_803017D0 (bytes >>24, >>16, >>8, low) and stores a computed scale to
// lbl_803017D8 = (lbl_802965E8 / (f32)(u8)value) * lbl_802965EC. Shares the
// lbl_803017CC/D0/D4/D8 state with siblings fn_80087240/fn_80087358
// (color-ish/scale state, 0x80087xxx). Suggested rename: SetColorScale /
// UnpackColorAndScale. Match notes: u32 temp masks (b0..b3) are required to
// force WANT's extrwi byte-extract form (inline casts let GCC fold to srwi).
#include "types.h"
extern f64 lbl_802965E0;
extern f32 lbl_802965E8;
extern f32 lbl_802965EC;
extern char lbl_803017D0[];
extern f32 lbl_803017D8;
void fn_80087284(u32 *arg0) {
    u32 temp_r8;
    u32 b0;
    u32 b1;
    u32 b2;
    u32 b3;
    temp_r8 = *arg0;
    b0 = (temp_r8 >> 0x18U) & 0xFFU;
    b1 = (temp_r8 >> 0x10U) & 0xFFU;
    b2 = (temp_r8 >> 8U) & 0xFFU;
    b3 = temp_r8 & 0xFFU;
    lbl_803017D0[0] = (s8) b0;
    lbl_803017D0[1] = (u8) b1;
    lbl_803017D0[2] = (u8) b2;
    lbl_803017D0[3] = (u8) b3;
    lbl_803017D8 = (lbl_802965E8 / (f32) (f64) (u8) temp_r8) * lbl_802965EC;
}
