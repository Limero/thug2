// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F68D4-0x800F69BC (232B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80301B40;
s32 fn_80129528(CStruct *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void *fn_8009F498(s32);
s32 fn_800F1E1C(void *, s32);
s32 fn_8016A6E4(s32);
s32 fn_800F3708(Unk_C7387A53 *);

void fn_800F68D4(CStruct *arg0) {
    s32 sp8;
    u32 var_r30;
    Unk_9994C3F5 *temp_r3;
    Unk_C6B642AC *temp_r9;

    var_r30 = 0U;
    temp_r9 = *((void * *)&arg0->unk0x60);
    while (var_r30 < temp_r9->unk0x4) {
        GetChecksum_2(fn_80129528(arg0->unk0x60, var_r30), QB_NAME, &sp8, 0);
        temp_r3 = fn_8009F498(sp8);
        if (temp_r3 != NULL) {
            temp_r9 = *((void * *)&temp_r3->unk0x8);
            ((s32 (*)(void *))temp_r9->unk0x3C)(
                (char *)temp_r3 + temp_r9->unk0x38);
        }
        temp_r9 = *((void * *)&arg0->unk0x60);
        var_r30 += 1;
    }
    fn_800F1E1C(lbl_80301B40, arg0->unk0x5C);
    temp_r9 = *((void * *)&arg0->unk0x50);
    if (temp_r9->unk0x14(
            (char *)arg0 + temp_r9->unk0x10) != 0) {
        fn_8016A6E4(arg0->unk0x58);
    }
    temp_r9 = *((void * *)&arg0->unk0x50);
    ((s32 (*)(void *))temp_r9->unk0x84)(
        (char *)arg0 + temp_r9->unk0x80);
    fn_800F3708(arg0);
}
