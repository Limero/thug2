// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800872FC-0x80087358 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_802965F8[];
extern char lbl_802965FC[];
extern char lbl_803017D4[];
extern char lbl_803017D8[];
extern char lbl_803017D3[];
void fn_800872FC(f32 farg0) {
    *(f32 *)lbl_803017D4 = farg0;
    *(f32 *)lbl_803017D8 = (*(f32 *)lbl_802965F8 / (f32) (f64) *(u8 *)(s32)lbl_803017D3) * *(f32 *)lbl_802965FC;
}
