// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A38DC-0x801A3910 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AB790[];
void fn_801A38DC(Unk_FFAD6788 *arg0, s32 arg1) {
    arg0->unk0x68 = (s32)lbl_802AB790;
    if (arg1 & 1) {
        Mem_Free();
    }
}
