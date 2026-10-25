// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009F27C-0x8009F310 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 CObject_AddRefLink(s32, s32);
void CObject_RemoveRefLink(s32, s32);
s32 Script_SpawnScript(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void *fn_8009F27C(CStruct *arg0, Unk_15EF4A35 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 spC;
    s32 sp8;
    void *temp_r29;
    s32 temp_r3;

    spC = arg4;
    sp8 = 0;
    temp_r3 = Script_SpawnScript(arg1, arg2, 0, 0, -1, arg3, 0, 0, sp8, spC);
    temp_r29 = (void *)(temp_r3 + 0xBC);
    if ((s32) ((Unk_FFAD6788 *)temp_r3)->unk0xBC != 0) {
        CObject_RemoveRefLink((s32)((Unk_FFAD6788 *)temp_r3)->unk0xBC, (s32)temp_r29);
        ((Unk_FFAD6788 *)temp_r3)->unk0xBC = 0;
    }
    ((Unk_FFAD6788 *)temp_r3)->unk0xBC = (s32)arg0;
    if (arg0 != 0) {
        CObject_AddRefLink((s32)arg0, (s32)temp_r29);
    }
    return (void *)temp_r3;
}
