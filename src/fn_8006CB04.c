// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006CB04-0x8006CB8C (136B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_80294BB8;
void memset(s32, s32, s32);
void *fn_8006CB04(Unk_FFAD6788 *arg0) {
    f32 temp_f0;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32 var_ctr_4;

    var_ctr = 4;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    var_ctr_2 = 4;
    do {
        var_ctr_2 -= 1;
    } while (var_ctr_2 != 0);
    var_ctr_3 = 4;
    do {
        var_ctr_3 -= 1;
    } while (var_ctr_3 != 0);
    var_ctr_4 = 4;
    do {
        var_ctr_4 -= 1;
    } while (var_ctr_4 != 0);
    memset(arg0, 0, 0xC0);
    temp_f0 = lbl_80294BB8;
    arg0->unk0xB4 = QB_BLEND;
    *((f32 *)&arg0->unk0xBC) = temp_f0;
    *((f32 *)&arg0->unk0xB8) = temp_f0;
    return arg0;
}
