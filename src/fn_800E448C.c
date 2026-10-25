// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E448C-0x800E4558 (204B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80064494(void *, void *, void *, void *);
void fn_800643E8(void *, void *, void *, void *);
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(s32, s32, s32, s32);
s32 GetStructure_2(CStruct *, void *, s32 *, void *);
bool fn_800E448C(Unk_31DE137E *arg0, s32 arg1, CStruct *arg2) {
    s32 sp10;
    s32 spC;
    s32 sp8;

    sp8 = 0;
    GetStructure_2(arg2, QB_PARAMS, &sp8, 0);
    if ((s32) arg0->unk0x1C != 0) {
        spC = 0;
        if (GetChecksum_2(arg2, QB_EMITSCRIPT, &spC, 0) != 0) {
            fn_800643E8(arg0->unk0x1C, spC, sp8, arg0->unk0xC);
        }
        sp10 = 0;
        if (GetChecksum_2(arg2, QB_UPDATESCRIPT, &sp10, 0) != 0) {
            fn_80064494(arg0->unk0x1C, sp10, sp8, arg0->unk0xC);
        }
    }
    return true;
}
