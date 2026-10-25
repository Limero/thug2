// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80197CF0-0x80197DB8 (200B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80300434;
void CObject_RemoveRefLink(CStruct *, CStruct *);
void GetElement_2(void *, s32, s32, s32);
void CScreenElement_SetAlpha(Unk_6A70655D *, f32, s32);
f32 fn_8012570C(s32, s32);

void fn_80197CF0(s32 arg0) {
    s32 sp8[6];
    register s32 a0 __asm__("r26");
    f32 temp_f31;
    s32 temp_r25;
    s32 temp_r30;
    s32 temp_r31;
    s32 *var_r29;
    s32 var_r28;
    s32 var_r27;

    a0 = arg0;
    temp_r25 = lbl_80300434;
    temp_f31 = fn_8012570C(QB_GOAL_TRICK_BEAT_UNFADED_TRICK_ALPHA, 1);
    var_r29 = (s32 *)((char *)a0 + 0x80);
    var_r28 = 0;
    var_r27 = 0x1E;
    do {
        register char *p84 __asm__("r9");
        temp_r30 = var_r29[2];
        __asm__ volatile("" : "=r"(p84) : "r"((char *)a0 + 0x84));
        if (temp_r30 == 0 && *(s32 *)(p84 + var_r28) == 1) {
            *(s32 *)(p84 + var_r28) = temp_r30;
            GetElement_2(&sp8[0], temp_r25, *var_r29, 1);
            temp_r31 = sp8[0];
            if (temp_r31 != 0) {
                CObject_RemoveRefLink((void *)temp_r31, &sp8[0]);
                sp8[0] = temp_r30;
            }
            CScreenElement_SetAlpha((void *)temp_r31, temp_f31, 1);
        }
        var_r29 += 0xA;
        var_r28 += 0x28;
        var_r27 -= 1;
    } while (var_r27 != 0);
}
