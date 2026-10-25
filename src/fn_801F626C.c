// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F626C-0x801F62D8 (108B). Byte-identical.
// extra_cflags: -fno-sched-spec
#include "types.h"
#include "structs.h"
extern s32 fn_801F443C(Unk_AF33B3CC * arg0);
void fn_801F203C(Unk_5FCDF30E * arg0);
void fn_801F626C(void *arg0) {
    s32 var_r30;
    s32 var_r9;
    void *var_r31;

    var_r31 = arg0 + 0x20;
    var_r30 = 0x32;
    do {
        var_r9 = 1;
        if ((s32) ((Unk_127FDB99 *)var_r31)->unk0x2BE == 0) {
            var_r9 = 0;
        }
        if ((var_r9 != 0) && (fn_801F443C(var_r31) == 0)) {
            fn_801F203C(var_r31);
        }
        var_r31 += 0x370;
        var_r30 -= 1;
    } while (var_r30 != 0);
}
