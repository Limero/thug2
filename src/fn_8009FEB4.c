// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009FEB4-0x8009FF18 (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetChecksum_3(Unk_6A70655D *, s32);
s32 fn_8009FEB4(Unk_6A70655D *arg0, CStruct *arg1) {
    s32 sp8;

    sp8 = 0;
    GetChecksum_2(arg1, QB_NAME, &sp8, 1);
    return GetChecksum_3(arg0, sp8) != 0;
}
