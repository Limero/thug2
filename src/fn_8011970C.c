// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011970C-0x8011976C (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// fn_8011970C: default-state predicate — 1 when arg0's leading f32s equal lbl_8029D4E0
// and (type at +0x14 != 2 or f2..f4 also equal it); else 0. Suggested rename: fn_IsDefaultState.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029D4E0;
bool fn_8011970C(Unk_DB0E2BAB *arg0) {
    f32 c = lbl_8029D4E0;
    if ((*((f32 *)&arg0->unk0x0) != c) ||
        (*((f32 *)&arg0->unk0x4) != c)) {
ret0:
        return false;
    }
    if (arg0->unk0x14 == 2) {
        if (*((f32 *)&arg0->unk0x8) != c) goto ret0;
        if (*((f32 *)&arg0->unk0xC) != c) goto ret0;
        if (*((f32 *)&arg0->unk0x10) != c) goto ret0;
    }
    return true;
}
