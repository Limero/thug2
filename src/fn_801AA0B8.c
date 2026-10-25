// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AA0B8-0x801AA158 (160B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 Mem_NewZero(s32);
extern s32 fn_8009F678(Unk_6A70655D *);
extern void fn_801A0D50(Unk_6A70655D *);
extern void fn_8009E274(Unk_31DE137E *, s32);
extern s32 fn_800D2FB4(Unk_9AA07378 *);
extern void fn_8009FB20(Unk_6A70655D *, Unk_C7387A53 *);
extern void fn_800F078C(CStruct *, Unk_9994C3F5 *);
extern void *lbl_80301A38;
extern void fn_801A9FD8(Unk_9994C3F5 *, CStruct *);
void fn_801AA0B8(CStruct *arg0) {
    Unk_C7387A53 *temp_r10;
    Unk_89391A04 *temp_r9;
    s32 temp_r30;

    temp_r30 = fn_8009F678(Mem_NewZero(0x118));
    fn_801A0D50(temp_r30);
    fn_8009E274(temp_r30, QB_OBJECT_TYPE_CAR);
    fn_8009FB20(temp_r30, fn_800D2FB4(Mem_NewZero(0x5C)));
    fn_800F078C(arg0, temp_r30 + 0x58);
    temp_r10 = lbl_80301A38;
    temp_r9 = *((void * *)&temp_r10->unk0x2C);
    ((void (*)(void *, void *))(*((void * *)&temp_r9->unk0x14)))((char *)temp_r10 + temp_r9->unk0x10, temp_r30);
    fn_801A9FD8(temp_r30, arg0);
}
