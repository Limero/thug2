// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801533D0-0x80153568 (408B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8000F2F8(void *, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_8012E970(void);
s32 fn_80219698(void *);
u32 fn_80198CD0(s32);
s32 fn_8021A784(void *, s32, s32, s32, s32);
void fn_8021A910(void *, s32, s32, s32);
void fn_8017D524(void *, s32, s32);
s32 fn_8009CF2C(void *);
s32 GetText(s32, s32, void *, s32);
void fn_8000F320(void *);
s32 GetInteger(s32, s32, void *, s32);
extern char lbl_802FFE98[];
extern char lbl_80305EAC[];
extern char lbl_80305EC0[];
extern char lbl_80305F9C[];
bool ScriptJoinServer(s32 arg0) {
    s32 sp8;
    s32 spC;
    s32 temp_r27;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r3;
    s32 temp_r3_2;
    u32 temp_r3_3;
    u32 var_r31;
    s32 hash1;

    temp_r3 = *(void **)&lbl_802FFE98;
    temp_r27 = *(s32 *)&lbl_80305EAC;
    temp_r29 = *(s32 *)&lbl_80305F9C;
    fn_8000F2F8(temp_r3, ((Unk_9994C3F5 *)temp_r3)->unk0x11C);
    hash1 = QB_PATCHCLEANUP;
    Script_RunScript(hash1, 0, 0, 0, 0);
    fn_8012E970();
    if ((temp_r3_2 = fn_80219698(temp_r29)) != 0) {
        temp_r3_3 = fn_80198CD0(*(s32 *)&lbl_80305EC0);
        for (var_r31 = 0U; var_r31 < temp_r3_3; var_r31 += 1) {
            temp_r30 = fn_8021A784(temp_r29, 0, 1, 1, var_r31);
            fn_8021A910(temp_r29, 0, 0U, var_r31);
            fn_8017D524(temp_r27, temp_r30, var_r31);
            if (fn_8009CF2C(temp_r29) != 0) {
                Script_RunScript(QB_ENTERED_NETWORK_GAME, 0, 0, 0, 0);
            }
        }
    } else {
        sp8 = temp_r3_2;
        spC = temp_r3_2;
        GetText(arg0, 0, &sp8, 0);
        GetInteger(arg0, 0, &spC, 0);
        if ((sp8 != 0) && (spC != 0)) {
            fn_8021A784(temp_r29, 0, 0, 1, 0U);
            fn_8021A910(temp_r29, 0, ((Unk_B0EC4F37 *)&spC)->unk0x2, 0U);
        }
    }
    fn_8000F320(*(s32 *)&lbl_802FFE98);
    return true;
}
