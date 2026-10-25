// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801857D0-0x80185898 (200B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    char pad0x0[0x38];
    s16 off0x38;
    char pad0x3A[2];
    s32 (*fn0x3C)(void *, s32);
} VT_t;
typedef struct {
    char pad0x0[0x14];
    VT_t *vt;
} Goal_t;

void *GoalManager_GetGoal(void *, s32, s32);
void CStruct_dtor(CStruct *);
void fn_80126FF4(void *, void *);
s32 GetStructure_2(void *, void *, void *, void *);
s32 fn_80127358(s32, s32);

void fn_801857D0(Unk_526DA6F2 *arg0) {
    s32 sp8;
    s32 h;
    CStruct *var_r31;
    s32 temp_r29;
    void *temp_r3;
    VT_t *vt;

    var_r31 = (CStruct *)fn_80127358(arg0->unk0x1C, 0);
    if (var_r31 != NULL) {
        do {
            temp_r29 = fn_80127358(arg0->unk0x1C, (s32)var_r31);
            h = var_r31->unk0x4;
            if (h == QB_GOALMANAGER_PARAMS) {
                GetStructure_2((void *)var_r31->unk0x8, QB_DIFFICULTY_LEVELS, &sp8, 1);
                CStruct_dtor((CStruct *)arg0->unk0x3A8);
                fn_80126FF4((void *)arg0->unk0x3A8, (void *)sp8);
            } else {
                temp_r3 = GoalManager_GetGoal((void *)arg0, h, 0);
                if (temp_r3 != NULL) {
                    vt = ((Goal_t *)temp_r3)->vt;
                    vt->fn0x3C((char *)temp_r3 + vt->off0x38, var_r31->unk0x8);
                }
            }
            var_r31 = (CStruct *)temp_r29;
        } while (var_r31 != NULL);
    }
}
