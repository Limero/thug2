// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801907E0-0x80190840 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void Script_RunScript(s32, s32, s32, s32, s32);

s32 fn_801907E0(Unk_C7387A53 *arg0, s32 arg1) {
    s32 sp8;
    s32 v;

    if (GetChecksum_2((CStruct *)arg0->unk0x20, arg1, &sp8, 0) == 0) {
        v = 0;
    } else {
        Script_RunScript(sp8, arg0->unk0x20, 0, 0, 0);
        v = 1;
    }
    return v;
}
