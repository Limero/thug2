// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021F89C-0x8021F8E8 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8019880C(s32);
extern char lbl_80305EC0[];
void fn_8021F89C(Unk_C7387A53 *arg0) {
    s32 var_r9;

    fn_8019880C(*(s32 *)&lbl_80305EC0);
    var_r9 = 1;
    if ((s32) arg0->unk0x4C == 1) {
        var_r9 = 0;
    }
    arg0->unk0x4C = var_r9;
}