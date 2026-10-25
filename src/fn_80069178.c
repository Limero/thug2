// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80069178-0x800691AC (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80294980[];
void fn_80069178(Unk_7A675EAB *arg0, s32 arg1) {
    arg0->unk0x1B8 = (s32)lbl_80294980;
    if (arg1 & 1) {
        Mem_Free();
    }
}
