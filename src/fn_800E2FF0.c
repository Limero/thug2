// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E2FF0-0x800E3058 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: QB-hash lookup helper. Runs `GetInteger(arg1, hash, &sp8,
// 0)` (hash 0 = a null/default lookup) and, if the object at arg0+0x20 is
// non-null, stores `(sp8 == 1)` into *(obj+0x180). Returns 1. The
// `xori;subfic;adde` fold is the `(sp8 ^ 1) == 0` == `sp8 == 1` bool.
#include "types.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
bool fn_800E2FF0(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 sp8;
    s32 temp_r0;
    Unk_C7387A53 *temp_r9;

    sp8 = 0;
    GetInteger(arg1, 0, &sp8, 0);
    temp_r9 = arg0->unk0x20;
    if (temp_r9 != NULL) {
        temp_r0 = sp8 ^ 1;
        temp_r9->unk0x180 = (s32) ((temp_r0 == 0));
    }
    return true;
}