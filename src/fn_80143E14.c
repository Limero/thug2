// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80143E14-0x80143F5C (328B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddChecksum(CStruct *, s32, s32);
void fn_80144C34(Unk_C8FEE62D *, s32, Unk_C8FEE62D *);
void CStruct_delete(CStruct *, s32);
void fn_80132140(Unk_C7387A53 *);
void fn_801D0C74(Unk_C2F9BED0 *);
s32 fn_80141988(Unk_C7387A53 *);
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_801BE7F4(Unk_C7387A53 *);
void fn_801EFAEC(Unk_31DE137E *);
void fn_80143AF4(Unk_3DDEEB97 *);
void fn_80143E14(Unk_46563DCA *arg0, s32 arg1, s32 arg2) {
    Unk_BC571107 *temp_r9;
    s32 temp_r31;
    s32 var_r11 = 0;

    temp_r9 = ((Unk_C7387A53 *)arg0->unk0x2B0)->unk0x38;
    if ((s32)temp_r9->unk0x188 == 0) {
        var_r11 = (temp_r9->unk0x20 ^ 1) == 0;
    }
    if (var_r11 != 0) {
        temp_r31 = CStruct_ctor(CStruct_new(8));
        AddChecksum(temp_r31, QB_NEWSCRIPT, QB_ONGROUNDAI);
        fn_80144C34(arg0, QB_SWITCH_ONGROUNDAI, temp_r31);
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
    }
    if ((s32)arg0->unk0x14 != 0) {
        fn_80132140(arg0->unk0x14);
    }
    fn_801D0C74(arg0->unk0x2AC);
    fn_801BE7F4(GetChecksum_3(fn_80141988(arg0), QB_SKATERCAMERA));
    temp_r9 = arg0->unk0x8;
    temp_r9->unk0x94((char *)arg0 + temp_r9->unk0x90);
    fn_80143AF4(arg0);
    temp_r9 = arg0->unk0x8;
    temp_r9->unk0x9C((char *)arg0 + temp_r9->unk0x98);
    temp_r9 = arg0->unk0x8;
    temp_r9->unk0xA4((char *)arg0 + temp_r9->unk0xA0, arg1, arg2);
    fn_801EFAEC(GetChecksum_3((s32)arg0, QB_SKATERENDRUN));
}
