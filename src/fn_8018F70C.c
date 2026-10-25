// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018F70C-0x8018F89C (400B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void AddChecksum(void *, s32, s32);
s32 ContainsFlag(void *, s32);
s32 fn_8012729C(void *);
s32 fn_8018E6F4(void *);
void fn_80127C14(void *, void *, void *);
s32 fn_8018D0EC(void *o);
void AddInteger(void *, void *, void *);
s32 fn_80128978(s32 arg0, s32 arg1);
#include "qb_constants.h"
#include "structs.h"
s32 fn_8018D924(s32);
s32 GetChecksum_2(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3);
void fn_8018F70C(Unk_9AA07378 *arg0, CStruct *arg1) {
    s32 sp8;
    s32 var_r29;
    Unk_C7387A53 *temp_r9;
    var_r29 = 0;
    AddInteger(arg1, QB_LEVELNUM, fn_8018E6F4(arg0));
    AddInteger(arg1, QB_ISLOCKED, fn_8018D924(arg0));
    AddInteger(arg1, QB_HASSEEN, fn_8018D0EC(arg0));
    temp_r9 = arg0->unk0x14;
    AddInteger(arg1, QB_HASBEATEN, ((s32 (*)(void *))temp_r9->unk0xAC)((char *)arg0 + *(s16 *)((char *)temp_r9 + 0xA8)));
    if (GetChecksum_2(arg0->unk0x20, QB_RECORD_TYPE, &sp8, 0) != 0) {
        if (sp8 == QB_TIME) {
            var_r29 = arg0->unk0x4C;
        } else if (sp8 == -QB_UNKNOWN_0x32993752) {
            var_r29 = arg0->unk0x50;
        }
    }
    AddInteger(arg1, QB_WIN_RECORD, var_r29);
    if (fn_80128978(arg0->unk0x20, QB_CLASSIC_MODE_GOAL) != 0) {
        AddChecksum(arg1, 0, QB_CLASSIC);
    } else {
        AddChecksum(arg1, 0, QB_CAREER);
    }
    if ((ContainsFlag(arg0->unk0x20, QB_PRESERVE_FLAGS) != 0) && (fn_8012729C(arg0->unk0x24) == 0)) {
        fn_80127C14(arg1, QB_GOAL_FLAGS, arg0->unk0x24);
    }
}
