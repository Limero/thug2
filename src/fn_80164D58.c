// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80164D58-0x80164ED4 (380B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
extern s32 lbl_802A83D0;
typedef struct { s32 w[4]; } S4;
s32 fn_80128C80(CStruct *, void *, void *, s32);
s32 fn_80174AB8(void *, s32);
s32 fn_8003AB44(s32, s32);
s32 fn_8003ABA0(s32, s32);
s32 fn_80128E04(CStruct *, void *, void *, s32);
s32 fn_80127C14(CStruct *, s32, CStruct *);

bool ScriptResolveHeadBoneScale(CStruct *pParams, CScript *pScript) {
    s32 sp8[4];
    s32 sp18[4];
    s32 sp28[4];
    s32 sp38;
    s32 sp3C;
    s32 temp_r31;
    register s32 var_r28 __asm__("r28");
    register s32 var_r29 __asm__("r29");
    register s32 var_r30 __asm__("r30");
    register s32 *p8 __asm__("r27");
    register s32 *p18 __asm__("r26");

    sp38 = 0;
    fn_80128C80(pParams, QB_PLAYER, &sp38, 1);
    temp_r31 = fn_80174AB8(lbl_80305EAC, sp38) + 4;
    if (temp_r31 != 0) {
        var_r28 = fn_8003AB44(temp_r31, QB_SKATER_M_HEAD);
        if (var_r28 == 0) {
            var_r28 = fn_8003AB44(temp_r31, QB_SKATER_F_HEAD);
            if (var_r28 == 0) {
                return false;
            }
        }
        *(S4 *)sp8 = *(S4 *)&lbl_802A83D0;
        p8 = sp8;
        sp28[0] = fn_8003ABA0(temp_r31, sp8[0]);
        sp28[1] = fn_8003ABA0(temp_r31, sp8[1]);
        sp28[2] = fn_8003ABA0(temp_r31, sp8[2]);
        sp28[3] = fn_8003ABA0(temp_r31, sp8[3]);
        *(S4 *)sp18 = *(S4 *)sp28;
        p18 = sp18;
        var_r30 = 0;
        var_r29 = 4;
        do {
            if ((*(s32 *)((char *)(var_r30 + (s32)p18)) == 0) && (fn_80128E04(var_r28, *(s32 *)((char *)(var_r30 + (s32)p8)), &sp3C, 0) != 0)) {
                fn_80127C14(temp_r31 + 0x58, *(s32 *)((char *)(var_r30 + (s32)p8)), sp3C);
            }
            var_r30 += 4;
            var_r29 -= 1;
        } while (var_r29 != 0);
    }
    return true;
}
