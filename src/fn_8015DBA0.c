// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015DBA0-0x8015DC0C (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void *fn_80125480(s32);
void AddChecksum(CStruct *, s32, s32);
bool ScriptGetCurrentPedProName(void *arg0, CScript *arg1) {
    u8 temp_r0;
    Unk_A5D07D11 *temp_r3;

    temp_r3 = fn_80125480(QB_UNKNOWN_0x09EEBCB8);
    temp_r0 = temp_r3->unk0x2;
    if (temp_r0 == 0xD) {
        return false;
    }
    if (temp_r0 != 0xA) {
        return false;
    }
    AddChecksum(arg1->unk0x18, QB_UNKNOWN_0xF054556D, temp_r3->unk0x4);
    return true;
}
