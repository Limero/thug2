// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015D174-0x8015D258 (228B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern char lbl_80305EFC[];
extern s32 ContainsFlag(CStruct * arg0, s32 hash);
extern s32 fn_801A5C04(Unk_9994C3F5 * obj);
extern s32 fn_801A5C40(s32 obj, s32 idx);
extern s32 fn_801A531C(s32 a, s32 b);
extern s32 fn_80128978(s32 arg0, s32 hash);
extern s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 *arg2, s32 arg3);
extern s32 fn_801A5DAC(s32 obj, s32 val);
extern s32 fn_80174A58(void * obj, CStruct * idx);
bool ScriptAwardSpecialTrickSlot(CStruct *arg0) {
    s32 sp8;
    s32 temp_r29;
    s32 temp_r3;
    s32 var_r31;

    temp_r29 = *(s32 *)&lbl_80305EFC;
    if (ContainsFlag(arg0, QB_ALL) != 0) {
        temp_r3 = fn_801A5C04(temp_r29);
        for (var_r31 = 0; var_r31 < temp_r3; var_r31++) {
            fn_801A531C(fn_801A5C40(temp_r29, var_r31), 1);
        }
    } else if (fn_80128978(arg0, QB_PROFILE) != 0) {
        const s32 enabled = 1;
        /* Zero-code barrier: without it the scheduler hoists the QB_PROFILE
           argument setup above the constant birth. */
        __asm__ volatile("" ::: "memory");
        GetChecksum_2(arg0, QB_PROFILE, &sp8, enabled);
        fn_801A531C(fn_801A5DAC(*(s32 *)&lbl_80305EFC, sp8), 1);
    } else {
        fn_801A531C(fn_80174A58(*(s32 *)&lbl_80305EAC, 0), 1);
    }
    return true;
}
