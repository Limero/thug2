// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006FB1C-0x8006FB50 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80294C50[];
void fn_8006FB1C(CScript *arg0, s32 arg1) {
    arg0->unk0x214 = (s32)lbl_80294C50;
    if (arg1 & 1) {
        fn_8006FBCC();
    }
}
