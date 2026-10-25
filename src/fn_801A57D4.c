// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A57D4-0x801A5818 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern char lbl_802AB7DC[];
void GetString(s32, s32, s32 *, s32);
s32 fn_801A57D4(s32 arg0) {
    s32 sp8;

    sp8 = (s32)lbl_802AB7DC;
    GetString(arg0 + 0x6C, QB_CASFILENAME, &sp8, 0);
    return sp8;
}
