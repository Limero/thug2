// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80010F70-0x80010FA4 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80290630[];
void fn_80010F70(Unk_9994C3F5 *arg0, s32 arg1) {
    arg0->unk0x8 = (s32)lbl_80290630;
    if (arg1 & 1) {
        Mem_Free();
    }
}
