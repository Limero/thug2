// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80107998-0x80107A28 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
// Matrix/transform init: zeroes the object header fields, copies two PS
// pairs from arg1/arg2 into arg0, and seeds the scale/pos vectors with the
// lbl_8029CB8C constant before fn_80107A28(arg0).
// Suggested rename: fn_80107998_transform_init.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029CB8C;
extern void fn_800063B4(void);
extern void fn_80107A28(Unk_C5652918 *);
void *fn_80107998(Unk_C7387A53 *arg0, __ps_t *arg1, __ps_t *arg2) {
    Unk_4C649A8C *temp_r9;
    Unk_5EF41E38 *temp_r11;
    f32 temp_f0;

    fn_800063B4();
    temp_r9 = (char *)arg0 + 0xA8;
    temp_r9->unk0x4 = 0;
    temp_r9->unk0x8 = 0;
    temp_r11 = (char *)arg0 + 0x28;
    arg0->unk0xA8 = 0;
    temp_f0 = lbl_8029CB8C;
    ((__ps_t *)arg0)[0] = arg1[0];
    ((__ps_t *)arg0)[1] = arg1[1];
    ((__ps_t *)arg0)[2] = arg2[0];
    ((__ps_t *)arg0)[3] = arg2[1];
    *(f32 *)temp_r11 = temp_f0;
    temp_r11->unk0x4 = temp_f0;
    temp_r11->unk0x8 = temp_f0;
    ((Unk_4C649A8C *)temp_r11)->unk0xC = temp_f0;
    fn_80107A28(arg0);
    return arg0;
}
