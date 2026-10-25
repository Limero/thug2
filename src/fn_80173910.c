// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80173910-0x80173AA8 (408B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80301A38[];
extern s32 lbl_80305EB4;
extern s32 lbl_80305EB8;
void *fn_800A398C(s32 arg0, s32 arg1);
void *fn_800A3528(Unk_C7387A53 * arg0);
s32 CStruct_new(s32 arg0);
s32 CStruct_ctor(s32 arg0);
void AddChecksum(CStruct * arg0, s32 arg1, s32 arg2);
void Script_RunScript(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void CStruct_delete(CStruct * arg0, s32 arg1);
void fn_80145168(void *arg0, CStruct * arg1);
void fn_8014535C(Unk_7258DEBD * arg0, CStruct * arg1);
void *fn_80144CBC(void *arg0);

void fn_80173910(void *arg0, Unk_9D99273B *arg1) {
    s32 temp_r31;
    s32 temp_r31_2;
    s32 temp_r3_2;
    s32 temp_r3_3;
    void *temp_r3;
    CStruct *temp_r3_4;
    Unk_C6B642AC *temp_r9;
    Unk_F5317C5D *temp_r9_2;

    temp_r3 = fn_800A398C(*(s32 *)&lbl_80301A38, arg1->unk0x18 + QB_BAILBOARD);
    if (temp_r3 != NULL) {
        temp_r9 = ((Unk_9994C3F5 *)temp_r3)->unk0x8;
        ((s32 (*)(void *))temp_r9->unk0x3C)(temp_r3 + temp_r9->unk0x38);
        fn_800A3528(*(s32 *)&lbl_80301A38);
    }
    if ((s32) arg1->unk0xC8 == 0) {
        temp_r31 = CStruct_ctor(CStruct_new(8));
        AddChecksum(temp_r31, QB_SKATERID, arg1->unk0x18);
        Script_RunScript(QB_REMOVE_CAR_FROM_NON_LOCAL_SKATER, temp_r31, 0, 0, 0);
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
        if ((s32) arg1->unk0xC8 != 0) {
            goto block_6;
        }
    } else {
block_6:
        temp_r31_2 = arg1->unk0x2E8;
        if (temp_r31_2 == 0) {
            if (lbl_80305EB4 != 0) {
                CStruct_delete(lbl_80305EB4, 3);
                lbl_80305EB4 = temp_r31_2;
            }
            temp_r3_2 = CStruct_ctor(CStruct_new(8));
            lbl_80305EB4 = temp_r3_2;
            fn_80145168(arg1, temp_r3_2);
            if (lbl_80305EB8 != 0) {
                CStruct_delete(lbl_80305EB8, 3);
                lbl_80305EB8 = temp_r31_2;
            }
            temp_r3_3 = CStruct_ctor(CStruct_new(8));
            lbl_80305EB8 = temp_r3_3;
            fn_8014535C(arg1, temp_r3_3);
        }
    }
    temp_r3_4 = fn_80144CBC(arg1);
    *(s32 *)(*(s32 *)((char *)((char *)temp_r3_4) + 0x10) + 0xC) =  temp_r3_4->unk0xC;
    *(s32 *)(*(s32 *)((char *)((char *)temp_r3_4) + 0xC) + 0x10) =  temp_r3_4->unk0x10;
    temp_r3_4->unk0xC = temp_r3_4;
    temp_r3_4->unk0x10 = temp_r3_4;
    if (arg1 != NULL) {
        temp_r9_2 = arg1->unk0x8;
        ((s32 (*)(void *, s32))temp_r9_2->unk0xC)((char *)arg1 + temp_r9_2->unk0x8, 3);
    }
}
