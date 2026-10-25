// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F65F0-0x801F667C (140B). Byte-identical.
// extra_cflags: -fno-sched-spec
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_801F348C(Unk_4D38C000 *, u8);
void fn_801F65F0(s32 arg0, s32 arg1) {
    s32 var_r28;
    s32 var_r9;
    void *var_r31;
    s32 magic1;
    s32 magic2;

    magic1 = -QB_UNKNOWN_0x174B47CA;
    magic2 = QB_GAP;
    var_r31 = arg0 + 0x20;
    var_r28 = 0x32;
    do {
        var_r9 = 1;
        if ((s32) ((Unk_127FDB99 *)var_r31)->unk0x2BE == 0) {
            var_r9 = 0;
        }
        if ((var_r9 != 0) && ((s32) ((Unk_127FDB99 *)var_r31)->unk0x0 == magic1) && ((s32) ((Unk_127FDB99 *)var_r31)->unk0x114 == magic2)) {
            fn_801F348C(var_r31, (u8)arg1);
        }
        var_r31 += 0x370;
        var_r28 -= 1;
    } while (var_r28 != 0);
}
