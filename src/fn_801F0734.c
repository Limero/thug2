// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F0734-0x801F0778 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
void CStruct_delete(CStruct *, s32);
void fn_801F0734(Unk_C7387A53 *arg0) {
    s32 temp;

    temp = arg0->unk0x24;
    if (temp != 0) {
        CStruct_delete(temp, 3);
        arg0->unk0x24 = 0;
    }
}
