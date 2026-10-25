// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80057FFC-0x800580A0 (164B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void fn_8005F3A0(s32, s32);
s32 fn_80057EF4(Unk_C8FEE62D *);
void fn_80057FFC(Unk_C8FEE62D *arg0, s32 arg1) {
    s32 temp_r28;
    s32 temp_r4;
    s32 var_r0;
    s32 field;
    void *temp_r29;
    void *temp_r30;
    CStruct *temp_r30_2;
    void *temp_r9;

    field = arg0->unk0xC - 4;
    temp_r4 = arg1 - field;
    var_r0 = temp_r4;
    if (temp_r4 < 0) {
        var_r0 = temp_r4 + 3;
    }
    temp_r9 = arg0->unk0x14;
    temp_r28 = temp_r4 - (var_r0 & QB_UNKNOWN_0xFFFFFFFC);
    if (temp_r9 != NULL) {
        temp_r30 = ((Unk_C7387A53 *)temp_r9)->unk0xC;
        temp_r30_2 = temp_r30 + 0xB8;
        temp_r29 = temp_r9 + ((Unk_8415B424 *)temp_r30)->unk0xB8;
        ((s32 (*)(void *, void *, void *))temp_r30_2->unk0x4)(temp_r29, fn_80057EF4(arg0), temp_r28);
    }
    if ((s32) arg0->unk0x10 != 0) {
        fn_8005F3A0(arg0->unk0x10, temp_r28);
    }
    arg0->unk0xC = arg1;
}
