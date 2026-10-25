// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002C43C-0x8002C490 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
void CStruct_new(s32);
s32 CStruct_ctor(void);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
void fn_8002C43C(CStruct *arg0, s32 arg1, s32 arg2, CStruct *arg3) {
    s32 temp_r3;

    arg0->unk0x0 = arg1;
    arg0->unk0xC = arg2;
    arg0->unk0x4 = 0;
    CStruct_new(8);
    temp_r3 = CStruct_ctor();
    arg0->unk0x10 = temp_r3;
    fn_80126FF4(temp_r3, arg3);
}
