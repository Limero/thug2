// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020B190-0x8020B1DC (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
bool fn_8020B190(Unk_CEAF6E85 *arg0, CStruct *arg1) {
    s32 temp_r3;

    temp_r3 = GetChecksum_2(arg1, 0, (s32 *)((char *)arg0 + (s32)0x1C10), 0);
    if (temp_r3 == 0) {
        arg0->unk0x1C10 = temp_r3;
    }
    return true;
}
