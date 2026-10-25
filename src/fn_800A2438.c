// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A2438-0x800A248C (84B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *fn_800A2430(void *);
bool fn_800A2438(CStruct *arg0, void *arg1) {
    u8 temp_r9;

    temp_r9 = *(u8 *)((char *)fn_800A2430(arg1) + (s32)0x8);
    if ((s32) (arg0->unk0x4 & 1) != (temp_r9 == 0)) {
        return true;
    }
    return false;
}
