// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D4D30-0x800D4D94 (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 *arg2, s32 arg3);
void fn_800D8908(Unk_C7387A53 * arg0, CStruct * arg1);
void fn_800D4D30(CScript *arg0, CStruct *arg1) {
    s32 sp8;

    sp8 = 0;
    GetChecksum_2((void *)arg1, QB_NAME, &sp8, 0);
    arg0->unk0x200 = sp8;
    arg0->unk0x1FC = sp8;
    fn_800D8908(arg0, arg1);
}
