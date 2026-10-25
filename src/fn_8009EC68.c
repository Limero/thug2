// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009EC68-0x8009ECE4 (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8009F204(Unk_C8FEE62D *, void *, Unk_C8FEE62D *);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
bool fn_8009EC68(Unk_C8FEE62D *arg0, CStruct *arg1) {
    s32 spC;
    s32 sp8;

    if (GetChecksum_2(arg1, 0, &sp8, 0) != 0) {
        spC = 0;
        GetStructure_2(arg1, QB_PARAMS, &spC, 0);
        fn_8009F204(arg0, sp8, spC);
    }
    return true;
}
