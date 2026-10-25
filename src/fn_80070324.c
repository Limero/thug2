// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80070324-0x80070394 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetInteger(CStruct *, s32, s32 *, s32);
bool fn_80070324(CStruct *arg0, CStruct *arg1) {
    arg0->unk0x4 = 0x28;
    GetInteger(arg1, 0, (char *)arg0 + 4, 0);
    if ((s32) arg0->unk0x4 < 0) {
        arg0->unk0x4 = 0;
    }
    if ((s32) arg0->unk0x4 > 0xFE) {
        arg0->unk0x4 = 0xFE;
    }
    return true;
}
