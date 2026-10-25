// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80196E7C-0x80196EF8 (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8012720C(CStruct *, s32);
void fn_80196E7C(Unk_24B9B8E5 *arg0) {
    s32 *var_r11;
    s32 var_ctr;
    s32 one = 1;
    void *var_r9;

    var_ctr = 0x1E;
    arg0->unk0x524 = 0;
    arg0->unk0x52C = 0;
    var_r11 = (char *)arg0 + 0x550;
    var_r9 = (char *)arg0 + 0x74;
    do {
        ((Unk_DB0E2BAB *)var_r9)->unk0x0 = 0;
        ((Unk_DB0E2BAB *)var_r9)->unk0x4 = 0;
        ((Unk_DB0E2BAB *)var_r9)->unk0x10 = 0;
        ((Unk_DB0E2BAB *)var_r9)->unk0x8 = 0;
        ((Unk_DB0E2BAB *)var_r9)->unk0x20 = 0;
        ((Unk_DB0E2BAB *)var_r9)->unk0x24 = one;
        ((Unk_DB0E2BAB *)var_r9)->unk0x18 = 0;
        ((Unk_DB0E2BAB *)var_r9)->unk0x14 = 0;
        *((s32 *)var_r11) = 0;
        var_r9 += 0x28;
        var_r11 += 1;
        var_ctr -= 1;
    } while (var_ctr != 0);
    fn_8012720C(arg0->unk0x20, QB_SINGLE_COMBO_ADDED);
}
