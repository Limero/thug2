// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80193130-0x801931EC (188B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 ContainsFlag(CStruct * arg0, s32 arg1);
extern s32 AddChecksum(CStruct * arg0, s32 arg1, s32 arg2);
extern s32 fn_8012720C(CStruct * arg0, s32 arg1);
extern s32 fn_8018C580(Unk_C8FEE62D * arg0);
s32 fn_80193130(Unk_C8FEE62D *arg0) {
    s32 temp_r30;
    Unk_0E2E8431 *temp_r9;

    temp_r30 = ContainsFlag(arg0->unk0x20, QB_TESTING_GOAL);
    AddChecksum(arg0->unk0x20, 0, QB_JUST_WON_GOAL);
    temp_r9 = *((void * *)&arg0->unk0x14);
    ((s32 (*)(void *, s32, s32))temp_r9->unk0x74)((char *)arg0 + temp_r9->unk0x70, 0, 1);
    fn_8012720C(arg0->unk0x20, QB_JUST_WON_GOAL);
    if (temp_r30 != 0) {
        AddChecksum(arg0->unk0x20, 0, QB_TESTING_GOAL);
    }
    temp_r30 = fn_8018C580(arg0);
    fn_8012720C(arg0->unk0x20, QB_TESTING_GOAL);
    return temp_r30;
}
