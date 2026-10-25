// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801833F4-0x801834C4 (208B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8018B324(s32, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
extern char lbl_802A95A8[];
void *fn_801833F4(Unk_526DA6F2 *arg0) {
    s32 *var_r9;
    s32 var_ctr;
    Unk_C8FEE62D *temp_r9;

    fn_8018B324((char *)arg0 + 4, 0);
    temp_r9 = (char *)arg0 + 0x20;
    temp_r9->unk0x14 = (s32)lbl_802A95A8;
    temp_r9->unk0x8 = 0;
    temp_r9->unk0x4 = -1;
    temp_r9->unk0x10 = temp_r9;
    temp_r9->unk0xC = temp_r9;
    arg0->unk0x54 = 1;
    arg0->unk0x38 = 0;
    arg0->unk0x40 = 0;
    arg0->unk0x44 = 0;
    arg0->unk0x48 = 0;
    arg0->unk0x4C = 0;
    arg0->unk0x50 = 0;
    arg0->unk0x58 = 0;
    arg0->unk0x5C = CStruct_ctor(CStruct_new(8));
    arg0->unk0x1C = CStruct_ctor(CStruct_new(8));
    arg0->unk0x3A8 = CStruct_ctor(CStruct_new(8));
    var_ctr = 0xD2;
    var_r9 = (s32 *)((char *)arg0 + 0x3A4);
    do {
        *var_r9 = 0;
        var_r9 -= 1;
        var_ctr -= 1;
    } while (var_ctr != 0);
    return arg0;
}
