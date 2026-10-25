// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F6164-0x801F61E8 (132B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_801F203C(Unk_5FCDF30E *);
void fn_801F6164(Unk_F0C166E4 *arg0) {
    s32 var_r9;
    u32 var_r29;
    void *var_r31;
    s32 magic;

    var_r29 = 0U;
    magic = -QB_UNKNOWN_0x174B47CA;
    var_r31 = (char *)arg0 + 0x20;
    do {
        var_r9 = 1;
        if ((s32) ((Unk_127FDB99 *)var_r31)->unk0x2BE == 0) {
            var_r9 = 0;
        }
        if ((var_r9 != 0) && ((s32) ((Unk_127FDB99 *)var_r31)->unk0x0 != magic)) {
            fn_801F203C(var_r31);
        }
        var_r29 += 1;
        var_r31 += 0x370;
    } while (var_r29 <= 0x31U);
    arg0->unk0xAC00 = 0;
}
