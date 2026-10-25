// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DC804-0x800DC868 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
#include "structs.h"
void fn_800DC680(Unk_C7387A53 *, void *, CStruct *);
s32 fn_800DCBD4(Unk_C7387A53 *, CStruct *, s32, void *, s32);
void fn_800DC804(Unk_C7387A53 *arg0, CStruct *arg1, s32 arg2) {
    s32 sp8[37];
    s32 var_ctr;
    var_ctr = 4;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    fn_800DC680(arg0, sp8, arg1);
    fn_800DCBD4(arg0, arg1, arg2, sp8, 0);
}
