// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800703D8-0x80070470 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
typedef struct {
    char _00[0x28];
    s16 off;
    char _pad32[2];
    void *fn;
} Fn800706ACDisp;
bool fn_800703D8(Unk_C7387A53 *arg0, CStruct *arg1) {
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
    ((s32 (*)(void *, s32, s32))temp_r9->fn)((char *)arg0 + temp_r9->off, sp8, spC);
    return true;
}
