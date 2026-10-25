// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FB550-0x801FB6B4 (356B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F78;
s32 fn_801F8170(Unk_9994C3F5 * arg0, Unk_9994C3F5 * arg1);
s32 fn_801F81E0(Unk_9994C3F5 * arg0, Unk_9994C3F5 * arg1);
void fn_801FB50C(Unk_C7387A53 * arg0);
s32 fn_801F7FEC(void *arg0, void *arg1, void *arg2);
s32 fn_801F76E4(s32 arg0);
s32 fn_801F7B04(void *arg0, void *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
s32 Script_GetInteger(s32 arg0, s32 arg1);
void fn_80057D30(s32 arg0, s32 arg1);

register void *gp_item __asm__("r28");
register void *gp_item8 __asm__("r30");

void fn_801FB550(Unk_C7387A53 *arg0, Unk_9994C3F5 *arg1) {
    s32 sp8[4];
    register void *temp_r4 __asm__("r4");
    s32 temp_r0;
    s32 temp_r3;
    s32 var_r31;
    s32 var_r4;
    s32 a34;
    s32 a30;

    temp_r4 = arg0->unk0x28;
    if ((temp_r4 != NULL) && (gp_item = ((Unk_C7387A53 *)temp_r4)->unk0xC, (gp_item != NULL))) {
        gp_item8 = (char *)gp_item + (s32)8;
        var_r31 = QB_SK5ED_RADOT_DYNAMIC_GREEN;
        if (fn_801F8170(gp_item8, arg1) != 0) {
            if (fn_801F81E0(gp_item8, arg1) != 0) {
                fn_801FB50C(arg0);
                return;
            }
            goto block_7;
        }
        temp_r3 = ((Unk_C7387A53 *)gp_item)->unk0x24;
        if ((temp_r3 != 0) && (fn_801F7FEC((char *)temp_r3 + (s32)8, gp_item8, arg1) == 0)) {
block_7:
            var_r31 = QB_SK5ED_RADOT_DYNAMIC;
        }
        if ((arg0->unk0x34 == 0) || (var_r31 != arg0->unk0x30)) {
            fn_801FB50C(arg0);
            arg0->unk0x34 = fn_801F76E4(var_r31);
            arg0->unk0x30 = var_r31;
        }
        a34 = arg0->unk0x34;
        temp_r4 = (char *)gp_item + (s32)8;
        __asm__("" : "+r"(temp_r4), "+r"(a34));
        a30 = arg0->unk0x30;
        fn_801F7B04(&sp8[0], temp_r4, arg1,
                    a34, a30, 0, 0);
        if (var_r31 == QB_SK5ED_RADOT_DYNAMIC) {
            temp_r3 = Script_GetInteger(QB_RAILEDITORREDLINEFLASHRATE, 0);
            temp_r0 = lbl_80305F78;
            var_r4 = -1;
            if (temp_r0 >= (temp_r3 / 2)) {
                var_r4 = 0;
            }
            lbl_80305F78 = temp_r0 + 1;
            if ((temp_r0 + 1) >= temp_r3) {
                lbl_80305F78 = 0;
            }
            fn_80057D30(arg0->unk0x34, var_r4);
        }
    }
}
