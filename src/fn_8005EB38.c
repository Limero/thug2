// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005EB38-0x8005EB6C (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80293B70[];
void fn_8005EB38(Unk_31DE137E *arg0, s32 arg1) {
    arg0->unk0x1C = (s32)lbl_80293B70;
    if (arg1 & 1) {
        Mem_Free();
    }
}
