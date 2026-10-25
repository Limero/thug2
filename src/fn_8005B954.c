// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005B954-0x8005B984 (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// SetUpdateCallbacks: stores two callbacks into global slots (0x803009B4,
// 0x803009B8) then calls fn_8007DD50 for init (same family as fn_8005BA0C).
// Suggested rename: fn_8005B954_set_update_callbacks.
#include "types.h"
extern s32 lbl_803009B4;
extern s32 lbl_803009B8;
extern void fn_8007DD50(void);
void fn_8005B954(s32 arg0, s32 arg1) {
    lbl_803009B4 = arg0;
    lbl_803009B8 = arg1;
    fn_8007DD50();
}