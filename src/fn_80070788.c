// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80070788-0x800707F4 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetInteger(CStruct *, s32, s32 *, s32);
bool fn_80070788(Unk_C7387A53 *arg0, CStruct *arg1) {
    arg0->unk0x34 = 0xFE;
    GetInteger(arg1, 0, (char *)arg0 + 0x34, 0);
    if ((s32) arg0->unk0x34 < 0) {
        arg0->unk0x34 = 0;
    }
    if ((s32) arg0->unk0x34 > 0xFE) {
        arg0->unk0x34 = 0xFE;
    }
    return true;
}
