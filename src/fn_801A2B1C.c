// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A2B1C-0x801A2C10 (244B). Byte-identical.
#include "types.h"
#include "structs.h"

s32 CStruct_new(s32 arg0);
s32 CStruct_ctor(s32 arg0);
s32 fn_80126FF4(Unk_80577C09 * arg0, CStruct * arg1);
s32 fn_801A269C(Unk_31DE137E * arg0);
void fn_801A27CC(Unk_C7387A53 * arg0, Unk_C8FEE62D * arg1);
s32 Script_RunScript(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 CStruct_delete(CStruct * arg0, s32 arg1);

void fn_801A2B1C(Unk_31DE137E *arg0, Unk_C8FEE62D *arg1) {
    s32 temp_r28;
    s32 temp_r30;
    Unk_EFE13F4E *temp_r9;
    Unk_F5317C5D *temp_r9_2;

    temp_r28 = arg1->unk0x34;
    fn_80126FF4((temp_r30 = CStruct_ctor(CStruct_new(8))), arg1->unk0x38);
    if (fn_801A269C(arg0) == 1) {
        fn_801A27CC(arg0, arg1);
    }
    temp_r9 = arg1->unk0x14;
    ((s32 (*)(void *))temp_r9->unk0x4C)((char *)arg1 + temp_r9->unk0x48);
    *(s32 *)(arg1->unk0x10 + 0xC) = arg1->unk0xC;
    *(s32 *)(arg1->unk0xC + 0x10) = arg1->unk0x10;
    arg1->unk0xC = (s32)arg1;
    arg1->unk0x10 = (s32)arg1;
    if (arg1 != NULL) {
        temp_r9_2 = arg1->unk0x14;
        ((s32 (*)(void *, s32))temp_r9_2->unk0xC)((char *)arg1 + temp_r9_2->unk0x8, 3);
    }
    if (temp_r28 != 0) {
        Script_RunScript(temp_r28, temp_r30, 0, 0, 0);
    }
    if (temp_r30 != 0) {
        CStruct_delete(temp_r30, 3);
    }
}
