// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005B984-0x8005B9B4 (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// SetUpdateCallbacks: stores two callbacks into global slots (0x803009BC,
// 0x803009C0) then calls fn_8007DD50 for init (same family as fn_8005BA0C).
// Suggested rename: fn_8005B984_set_update_callbacks.
#include "types.h"
extern s32 lbl_803009BC;
extern s32 lbl_803009C0;
extern void fn_8007DD50(void);
void fn_8005B984(s32 arg0, s32 arg1) {
    lbl_803009BC = arg0;
    lbl_803009C0 = arg1;
    fn_8007DD50();
}