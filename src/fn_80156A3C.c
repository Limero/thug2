// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80156A3C-0x80156BFC (448B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 sprintf(s32, ...);
extern s32 ContainsFlag(CStruct *, s32);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 fn_8012591C(s32, s32);
extern s32 fn_801259C8(s32, s32);
extern s32 fn_80129528(CStruct *, s32);
extern s32 fn_801A6E64(Unk_93C2DF4D *);
extern s32 fn_801A6ECC(Unk_93C2DF4D *);
extern void AddComponent(CStruct *, s32, s32, void *);
extern char lbl_802A809C[];
extern s32 lbl_80305EAC;
bool ScriptGetNextLevelRequirements(void *arg0, CScript *arg1) {
    char sp8[104];
    s32 sp70;
    s32 sp74;
    s32 temp_r27;
    s32 temp_r28;
    CStruct *temp_r29;
    s32 temp_r30;
    s32 temp_r30_2;
    u32 var_r31;
    register s32 str __asm__("r4");

    temp_r30 = *(s32 *)((char *)(*(s32 *)&lbl_80305EAC) + (s32)0x24);
    str = (s32)lbl_802A809C;
    var_r31 = 0U;
    sprintf((s32)sp8, str);
    temp_r27 = fn_801A6E64(temp_r30);
    temp_r28 = fn_801A6ECC(temp_r30);
    temp_r29 = fn_801259C8(QB_UNKNOWN_0x1D8F1A7E, 0);
    if (var_r31 < (u32) *((u32 *)&temp_r29->unk0x4)) {
        do {
            temp_r30_2 = fn_80129528(temp_r29, var_r31);
            sp70 = 0;
            sp74 = 0;
            if ((ContainsFlag(temp_r30_2, QB_GOALS) != 0) || (ContainsFlag(temp_r30_2, QB_GOAL) != 0)) {
                GetInteger(temp_r30_2, 0, &sp70, 0);
            }
            if ((ContainsFlag(temp_r30_2, QB_UNKNOWN_0x56907F8B) != 0) || (ContainsFlag(temp_r30_2, QB_MEDAL) != 0)) {
                GetInteger(temp_r30_2, 0, &sp74, 0);
            }
            if (temp_r27 < sp70) {
                sprintf((s32)sp8, fn_8012591C(QB_CFUNCS_STR_GOALSFORNEXTLEVEL, 0), sp70 - temp_r27);
                break;
            }
            if (temp_r28 < sp74) {
                sprintf((s32)sp8, fn_8012591C(QB_CFUNCS_STR_MEDALSFORNEXTLEVEL, 0), sp74 - temp_r28);
                break;
            }
            var_r31 += 1;
        } while (var_r31 < (u32) *((u32 *)&temp_r29->unk0x4));
    }
    AddComponent(arg1->unk0x18, QB_UNKNOWN_0xAF2305A6, 3, (void *)sp8);
    return true;
}
