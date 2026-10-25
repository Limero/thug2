// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F0A70-0x800F0AC4 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_8029B318;
extern f32 lbl_8029B31C;
void GetVector(s32, s32, void *, s32);
typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
} Fn800F0A70Angles;
void fn_800F0A70(s32 arg0, Fn800F0A70Angles *arg1) {
    f32 temp_f0;
    f32 temp_f13;

    temp_f0 = lbl_8029B318;
    temp_f13 = lbl_8029B31C;
    arg1->fC = temp_f13;
    arg1->f0 = temp_f0;
    arg1->f4 = temp_f0;
    arg1->f8 = temp_f0;
    GetVector(arg0, QB_ANGLES, arg1, 0);
}
