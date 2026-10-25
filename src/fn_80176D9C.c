// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80176D9C-0x80176E68 (204B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_8030191C;
extern s32 fn_801746A4(Unk_C7387A53 * arg0, s32 arg1);
extern s32 fn_80141FA4(Unk_5FCDF30E * arg0);
extern s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
extern s32 fn_8009D364(s32 arg0, s32 arg1);
extern void fn_800DFB64(Unk_49A90AFC * arg0, s32 arg1);
extern s32 fn_80141988(Unk_C7387A53 * arg0);
void fn_80176D9C(Unk_C7387A53 *arg0) {
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_child;
    s32 var_r28;
    Unk_FFAD6788 *temp_r31;

    var_r28 = 0;
    do {
        temp_r31 = fn_801746A4(arg0, var_r28);
        var_r28 += 1;
        if (temp_r31 != NULL) {
            if (temp_r31->unk0xC8 != 0) {
                temp_r29 = fn_80141FA4(temp_r31);
                temp_r30 = GetChecksum_3(temp_r31, QB_INPUT);
                fn_800DFB64(temp_r30, fn_8009D364(lbl_8030191C, temp_r29));
                temp_child = fn_80141988(temp_r31);
                if (temp_child != NULL) {
                    temp_r30_2 = GetChecksum_3(temp_child, QB_INPUT);
                    fn_800DFB64(temp_r30_2, fn_8009D364(lbl_8030191C, temp_r29));
                }
            }
        }
    } while (var_r28 <= 7);
}
