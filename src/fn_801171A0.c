// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801171A0-0x80117220 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetString(CStruct *, s32, void *, s32);
s32 fn_8000A7F8(s32, s32);
void AddChecksum(CStruct *, s32, void *);

bool ScriptAppendSuffixToChecksum(CStruct *arg0, Unk_FFAD6788 *arg1) {
    s32 sp8;
    s32 spC;
    s32 combined;
    void *obj;

    GetChecksum_2(arg0, 0x3F4B019E, &sp8, 1);
    GetString(arg0, 0x94542EEA, &spC, 1);
    obj = *(void **)((char *)arg1 + 0x18);
    combined = fn_8000A7F8(sp8, spC);
    AddChecksum(obj, 0xAFB911C6, combined);
    return true;
}
