// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80197B5C-0x80197C80 (292B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80300434;
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 GetString(CStruct *, s32 *, s32 *, s32);
s32 Script_GenerateCRC(s32);
f32 fn_8012570C(s32, s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void GetElement_2(void *, s32, void *, s32);
void CScreenElement_SetAlpha(Unk_6A70655D *, f32, s32);

void fn_80197B5C(void *arg0, CStruct *arg1) {
    s32 sp8[8];
    register s32 a0 __asm__("r26");
    f32 temp_f31;
    s32 temp_r23;
    s32 temp_r24;
    s32 temp_r29;
    s32 temp_r31;
    s32 *var_r30;
    s32 var_r28;
    s32 var_r27;
    register char *p88 __asm__("r25");
    register s32 one __asm__("r22");

    a0 = arg0;
    GetStructure_2(arg1, QB_PARAMS, &sp8[4], 1);
    GetString(sp8[4], QB_NAME, &sp8[5], 1);
    temp_r23 = Script_GenerateCRC(sp8[5]);
    if (((Unk_D4A84CA9 *)a0)->unk0x540 != 0) {
        temp_r24 = lbl_80300434;
        p88 = (char *)a0 + 0x88;
        temp_f31 = fn_8012570C(QB_GOAL_TRICK_BEAT_FADED_TRICK_ALPHA, 1);
        one = 1;
        var_r30 = (s32 *)((char *)a0 + 0x80);
        var_r28 = 0;
        var_r27 = 0x1E;
        do {
            register char *p84 __asm__("r9");
            if (*(s32 *)(var_r28 + (s32)p88) == 0) {
                __asm__ volatile("" : "=r"(p84) : "r"((char *)a0 + 0x84));
                temp_r29 = *(s32 *)(p84 + var_r28);
                if (temp_r29 == 0 && *(s32 *)((char *)var_r30 - 0xC) == temp_r23) {
                    *(s32 *)(p84 + var_r28) = one;
                    GetElement_2(&sp8[0], temp_r24, *(void **)var_r30, 1);
                    {
                        s32 *pr;
                        pr = &sp8[0];
                        temp_r31 = *pr;
                        if (temp_r31 != 0) {
                            CObject_RemoveRefLink((void *)temp_r31, pr);
                            *pr = temp_r29;
                        }
                    }
                    CScreenElement_SetAlpha((void *)temp_r31, temp_f31, 1);
                }
            }
            var_r30 += 0xA;
            var_r28 += 0x28;
            var_r27 -= 1;
        } while (var_r27 != 0);
    }
}
