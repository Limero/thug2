// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005BA0C-0x8005BA3C (48B). Byte-identical.
// SetUpdateCallbacks: stores two function pointers into global callback
// slots (0x803009C4, 0x803009C8), then calls fn_8007DD50 for init.
#include "types.h"
extern s32 lbl_803009C4;
extern s32 lbl_803009C8;
extern void fn_8007DD50(void);
void fn_8005BA0C(s32 arg0, s32 arg1) {
    lbl_803009C4 = arg0;
    lbl_803009C8 = arg1;
    fn_8007DD50();
}
