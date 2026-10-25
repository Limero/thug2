// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001076C-0x800107A0 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80290610[];
void fn_8001076C(CScript *arg0, s32 arg1) {
    arg0->unk0x18 = (s32)lbl_80290610;
    if (arg1 & 1) {
        Mem_Free();
    }
}
