// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009FB7C-0x8009FC60 (228B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80301A38[];
void CStruct_new(s32 arg0);
void fn_8009FB20(Unk_6A70655D *, Unk_C7387A53 *);
s32 fn_800A1BB4(Unk_C7387A53 *arg0, s32 arg1);
s32 GetChecksum_2(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3);
s32 CStruct_ctor();
void fn_80126F88(s32, s32);
void CStruct_delete(s32, s32);

void fn_8009FB7C(Unk_6A70655D *arg0, CStruct *arg1, CStruct *arg2) {
    s32 sp8;
    s32 temp_r30;
    void *temp_r3;
    CScript *temp_r9;
    CScript *temp_r9_2;

    GetChecksum_2(arg1, QB_COMPONENT, &sp8, 1);
    temp_r3 = fn_800A1BB4(*(s32 *)&lbl_80301A38, sp8);
    fn_8009FB20(arg0, temp_r3);
    if (arg2 != 0) {
        CStruct_new(8);
        temp_r30 = CStruct_ctor();
        fn_80126F88(temp_r30, arg1);
        fn_80126F88(temp_r30, arg2);
        temp_r9 = ((CScript *)temp_r3)->unk0x18;
        ((s32 (*)(void *, void *))temp_r9->unk0x1C)((char *)temp_r3 + *(s16 *)&temp_r9->unk0x18, temp_r30);
        if (temp_r30 != 0) {
            CStruct_delete(temp_r30, 3);
        }
    } else {
        temp_r9_2 = ((CScript *)temp_r3)->unk0x18;
        ((s32 (*)(void *, void *))temp_r9_2->unk0x1C)((char *)temp_r3 + *(s16 *)&temp_r9_2->unk0x18, arg1);
    }
}
