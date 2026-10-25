// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A4B40-0x800A4BB0 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80301A78[];
void fn_800A5BF4(CStruct *, s32, s32);
void fn_800A4B40(CStruct *arg0, s32 arg1) {
    void *var_r31;
    s32 var_r30;
    s32 elem;

    var_r30 = 0;
    var_r31 = *((void * *)&arg0->unk0x0);
    while (var_r30 < (s32) arg0->unk0x4) {
        elem = *(s32 *)var_r31;
        if (elem != 0) {
            fn_800A5BF4(*(s32 *)&lbl_80301A78, elem, arg1);
        }
        var_r30 += 1;
        var_r31 += 0x14;
    }
}
