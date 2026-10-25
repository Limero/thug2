// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80139B54-0x80139B88 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029F350[];
void fn_80139B54(Unk_9994C3F5 *arg0, s32 arg1) {
    arg0->unk0x8 = (s32)lbl_8029F350;
    if (arg1 & 1) {
        Mem_Free();
    }
}
