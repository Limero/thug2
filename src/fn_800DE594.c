// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DE594-0x800DE604 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029A288[];
void fn_8000C5D8(Unk_A0A7249E *, s32, s32);
void fn_8009F558(Unk_C8FEE62D *, s32);
void fn_800DE594(CScript *arg0, s32 arg1) {
    s32 var_r31;

    arg0->unk0x18 = (s32)lbl_8029A288;
    if ((s32) arg0->unk0x38 != 0) {
        for (var_r31 = 1; var_r31 != -1; var_r31--) {
            fn_8000C5D8(arg0->unk0x38, var_r31, 0);
        }
    }
    fn_8009F558(arg0, arg1);
}
