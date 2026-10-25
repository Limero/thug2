// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C5A3C-0x801C5A94 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_80305F9C;
extern s32 fn_801754AC(s32 arg0);
extern s32 NextItem(s32 arg0);
extern void fn_801C5F4C(Unk_B9F059B9 * arg0);

void fn_801C5A3C(Unk_B9F059B9 *arg0) {
    if ((fn_801754AC(lbl_80305EAC) != 0) && (NextItem(lbl_80305F9C) != 0)) {
        fn_801C5F4C(arg0);
    }
}
