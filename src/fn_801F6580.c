// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F6580-0x801F65F0 (112B). Byte-identical.
// extra_cflags: -fno-sched-spec
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_801F2320(Unk_7258DEBD *);
void fn_801F6580(void *arg0) {
    s32 var_r29;
    s32 var_r9;
    void *var_r31;
    s32 magic;

    magic = -QB_UNKNOWN_0x174B47CA;
    var_r31 = arg0 + 0x20;
    var_r29 = 0x32;
    do {
        var_r9 = 1;
        if ((s32) ((Unk_127FDB99 *)var_r31)->unk0x2BE == 0) {
            var_r9 = 0;
        }
        if ((var_r9 != 0) && ((s32) ((Unk_127FDB99 *)var_r31)->unk0x0 == magic)) {
            fn_801F2320(var_r31);
        }
        var_r31 += 0x370;
        var_r29 -= 1;
    } while (var_r29 != 0);
}
