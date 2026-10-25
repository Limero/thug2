// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800BE68C-0x800BE7A4 (280B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80299220[];
void fn_8009F53C(Unk_C8FEE62D * arg0);
void fn_80006C60(void *arg0);
void fn_80105BF4(Unk_5CB48605 * arg0);
void *fn_800BE68C(Unk_3C525816 *arg0) {
    Unk_5EF41E38 *temp_r11;
    char *temp_r3;
    char *var_r27;
    Unk_5EF41E38 *var_r28;
    char *var_r31;
    f32 temp_f0;
    f32 temp_f13;
    f32 temp_f0_2;
    f32 temp_f13_2;
    s32 var_ctr;
    u32 var_r29;

    fn_8009F53C(arg0);
    arg0->unk0x18 = (s32)lbl_80299220;
    temp_f0 = 0.0f;
    temp_f13 = 1.0f;
    temp_r11 = (char *)arg0 + (s32)0x40;
    arg0->unk0x40 = temp_f0;
    temp_r11->unk0x4 = temp_f0;
    temp_r11->unk0x8 = temp_f0;
    ((Unk_4C649A8C *)temp_r11)->unk0xC = temp_f13;
    var_ctr = 4;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    temp_r3 = (char *)arg0 + (s32)0x1C8;
    var_ctr = 4;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    var_r27 = (char *)arg0 + (s32)0x338;
    var_r28 = (char *)arg0 + (s32)0x1310;
    var_r31 = temp_r3;
    var_r29 = 1;
    do {
        fn_80006C60(var_r31);
        fn_80006C60(var_r31 + (s32)0x30);
        var_r31 += (s32)0x88;
    } while (var_r29-- != 0u);
    fn_80105BF4(var_r27);
    arg0->unk0x4 = QB_VEHICLE;
    temp_f0_2 = 0.0f;
    temp_f13_2 = 1.0f;
    arg0->unk0x1348 = 0;
    arg0->unk0x1350 = 0;
    arg0->unk0x1354 = 0;
    arg0->unk0x1324 = temp_f0_2;
    arg0->unk0x1310 = temp_f0_2;
    ((Unk_4C649A8C *)var_r28)->unk0xC = temp_f13_2;
    var_r28->unk0x8 = temp_f0_2;
    var_r28->unk0x4 = temp_f0_2;
    arg0->unk0x1328 = QB_DEFAULT;
    arg0->unk0x134 = temp_f0_2;
    arg0->unk0x60 = 1;
    arg0->unk0x2F0 = 0;
    arg0->unk0x68 = 0;
    arg0->unk0x64 = 0;
    return arg0;
}
