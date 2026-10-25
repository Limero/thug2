// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018479C-0x8018483C (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

s32 fn_8018B4C0(s32, s32 *, s32 *);
s32 fn_8018E3B8(void);
s32 fn_8018BFAC(s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_8018B90C(s32);
s32 fn_80184168(s32);

void fn_8018479C(s32 arg0) {
    s32 sp8;
    s32 spC;
    s32 temp_r31;

    sp8 = 0;
    while (sp8 < fn_80184168(arg0)) {
        temp_r31 = fn_8018B4C0(arg0 + 4, &sp8, &spC);
        if (fn_8018E3B8() != 0) {
            Script_RunScript(QB_GOAL_CREATE_PROSET_GEOM, fn_8018BFAC(temp_r31), 0, 0, 0);
            fn_8018B90C(temp_r31);
        }
        sp8 += 1;
    }
}
