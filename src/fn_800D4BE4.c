// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D4BE4-0x800D4C88 (164B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_80299AFC;
extern char lbl_80299CB0[];
void fn_800D6544(Unk_7A675EAB *);
void *fn_800D4BE4(Unk_FE004FE1 *arg0) {
    f32 temp_f0;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32 var_ctr_4;

    fn_8009F53C();
    var_ctr = 3;
    arg0->unk0x18 = (s32)lbl_80299CB0;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    var_ctr_2 = 3;
    do {
        var_ctr_2 -= 1;
    } while (var_ctr_2 != 0);
    var_ctr_3 = 3;
    do {
        var_ctr_3 -= 1;
    } while (var_ctr_3 != 0);
    var_ctr_4 = 3;
    do {
        var_ctr_4 -= 1;
    } while (var_ctr_4 != 0);
    temp_f0 = lbl_80299AFC;
    arg0->unk0x1B0 = temp_f0;
    arg0->unk0x204 = 0;
    arg0->unk0x1B4 = temp_f0;
    arg0->unk0x4 = QB_MOTION;
    arg0->unk0x110 = 0;
    arg0->unk0x78 = 1;
    fn_800D6544(arg0);
    return arg0;
}
