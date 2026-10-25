// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B05E0-0x800B0664 (132B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern CStruct * lbl_80301B08;
void fn_800B0C28(CStruct *);
void fn_800B0CF8(CStruct *, s32 *);
s32 fn_800B0C3C(CStruct *, s32 *);
void fn_800B05E0(void) {
    s32 sp8;
    void *temp_r30;
    CStruct *var_r31;
    s32 g;

    g = lbl_80301B08;
    if (g != 0) {
        fn_800B0C28(g);
        var_r31 = fn_800B0C3C(lbl_80301B08, 0);
        if (var_r31 != NULL) {
            do {
                temp_r30 = fn_800B0C3C(lbl_80301B08, 0);
                sp8 = var_r31->unk0x4;
                Mem_Free(var_r31);
                fn_800B0CF8(lbl_80301B08, &sp8);
                var_r31 = temp_r30;
            } while (var_r31 != NULL);
        }
    }
}
