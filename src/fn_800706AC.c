// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800706AC-0x80070744 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
typedef struct {
    char _00[0x30];
    s16 off;
    char _pad32[2];
    void *fn;
} Fn800706ACDisp;
bool fn_800706AC(Unk_C7387A53 *arg0, CStruct *arg1) {
    s32 spC;
    s32 sp8;
    Fn800706ACDisp *temp_r9;

    sp8 = 0;
    if (GetChecksum_2(arg1, 0, &sp8, 0) == 0) {
        return false;
    }
    spC = 0x20;
    GetInteger(arg1, 0, &spC, 0);
    temp_r9 = (Fn800706ACDisp *)arg0->unk0x5C;
    ((s32 (*)(void *, void *, void *))temp_r9->fn)((char *)arg0 + temp_r9->off, sp8, spC);
    return true;
}
