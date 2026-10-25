// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80012E88-0x80012FD0 (328B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80290844[];
extern void *lbl_802FFE8C;
s32 fn_8000E39C(void *, void *, s32 *, s32);
s32 fn_8001475C(void *);
s32 fn_80014764(void *, s32);
s32 fn_800146E0(void *);
void *fn_800147E8(void *, void *);
void fn_80014898(void *);
s32 fn_80014904(s32, s32, s32, void *);
s32 Mem_Alloc_3(s32);
void Mem_Free_3(void *);
void fn_80010670(s32, void *);

s32 fn_80012E88(void *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    s32 sp8;
    s32 var_r31;
    s32 temp_r3;
    void *temp_r30;

    sp8 = 0;
    var_r31 = fn_8000E39C(lbl_802FFE8C, arg0, &sp8, arg2);
    if (var_r31 != 0) {
        goto out;
    }
    temp_r3 = fn_8001475C(arg0);
    sp8 = temp_r3;
    if (temp_r3 != 0) {
        if (arg2 == 0) {
            var_r31 = Mem_Alloc_3((temp_r3 + 0x7FF) & QB_UNKNOWN_0xFFFFF800);
        } else {
            var_r31 = arg2;
        }
        if (fn_80014764(arg0, var_r31) == 0) {
            if (arg2 == 0) {
                Mem_Free_3((void *)var_r31);
            }
            var_r31 = 0;
        }
    } else {
        temp_r30 = fn_800147E8(arg0, lbl_80290844);
        temp_r3 = fn_800146E0(temp_r30);
        sp8 = temp_r3;
        if (arg2 == 0) {
            var_r31 = Mem_Alloc_3((temp_r3 + 0x7FF) & QB_UNKNOWN_0xFFFFF800);
        } else {
            var_r31 = arg2;
        }
        fn_80014904(var_r31, 1, sp8, temp_r30);
        fn_80014898(temp_r30);
    }
    if ((arg2 == 0) && (var_r31 != 0)) {
        fn_80010670(sp8, (void *)var_r31);
    }
out:
    if (arg1 != NULL) {
        *arg1 = sp8;
    }
    return var_r31;
}
