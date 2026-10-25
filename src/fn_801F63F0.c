// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F63F0-0x801F64B8 (200B). Byte-identical.
// extra_cflags: -fno-sched-spec
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_801F4DC8(Unk_F64BBBF6 * arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
bool fn_801F63F0(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    s32 var_r29;
    s32 var_r9;
    void *var_r31;
    s32 magic;
    volatile double _dummy;
    volatile double _dummy2;
    volatile double _dummy3;
    volatile double _dummy4;

    var_r29 = 0;
    magic = -QB_UNKNOWN_0x174B47CA;
    var_r31 = arg0 + 0x20;
    do {
        var_r9 = 1;
        if ((s32) ((Unk_127FDB99 *)var_r31)->unk0x2BE == 0) {
            var_r9 = 0;
        }
        if ((var_r9 != 0) && ((s32) ((Unk_127FDB99 *)var_r31)->unk0x0 == magic) && (fn_801F4DC8(var_r31, farg0, farg1, farg2, farg3) != 0)) {
            return true;
        }
        var_r29 += 1;
        var_r31 += 0x370;
    } while (var_r29 <= 0x31);
    return false;
}
