// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018568C-0x801857D0 (324B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_8009CF2C(CStruct *);
extern void* lbl_80305F9C;
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void CStruct_delete(CStruct *, s32);
extern void fn_80127C14(CStruct *, s32, CStruct *);
extern s32 fn_80184168(void *);
extern void *fn_8018B4C0(void *, s32 *, s32 *);
extern void *fn_8018BFAC(void *);
extern s32 fn_8018E24C(void *);
extern s32 fn_8018E28C(void *);
extern s32 ContainsFlag(void *, s32);

typedef struct GoalVtbl {
    char pad0x0[0x40];
    s16 unk0x40;
    s32 unk0x44;
} GoalVtbl;

typedef struct Goal {
    char pad0x0[0x14];
    GoalVtbl *vtbl;
} Goal;

void fn_8018568C(Unk_526DA6F2 *arg0) {
    s32 spC;
    s32 sp8;
    s32 temp_r3;
    s32 temp_r31;
    s32 temp_r3_2;
    Goal *temp_r30;
    GoalVtbl *temp_r9;

    temp_r3 = fn_8009CF2C(lbl_80305F9C);
    if (temp_r3 == 0) {
        temp_r31 = CStruct_ctor(CStruct_new(8));
        fn_80127C14(temp_r31, QB_DIFFICULTY_LEVELS, arg0->unk0x3A8);
        fn_80127C14(arg0->unk0x1C, QB_GOALMANAGER_PARAMS, temp_r31);
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
        sp8 = temp_r3;
        while (sp8 < fn_80184168(arg0)) {
            temp_r30 = fn_8018B4C0((char *)arg0 + 4, &sp8, &spC);
            if ((ContainsFlag(fn_8018BFAC(temp_r30), QB_NULL_GOAL) == 0)
                && (fn_8018E28C(temp_r30) == 0)) {
                temp_r3_2 = CStruct_ctor(CStruct_new(8));
                temp_r9 = temp_r30->vtbl;
                ((s32 (*)(void *, void *))temp_r9->unk0x44)((char *)temp_r30 + temp_r9->unk0x40,
                                                             temp_r3_2);
                fn_80127C14(arg0->unk0x1C, fn_8018E24C(temp_r30), temp_r3_2);
                if (temp_r3_2 != 0) {
                    CStruct_delete(temp_r3_2, 3);
                }
            }
            sp8 += 1;
        }
    }
}
