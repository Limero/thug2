// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015BA18-0x8015BAE4 (204B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// PARKED: 92.2% (47/51 words). Two doc-15 arg-setup/register-choice artifacts:
// (1) second fn_80128E34 call site wants r5-before-r4 arg moves while GOT and
//     site #1 both emit const-r4 first — recipe 121 twin-site opposite-order
//     class, resists flags/decl order; (2) sp8 reload before `cmpw r3,r4` lands
//     in r0/r9/r11 but never r4 under every shape tried (pins on r3/r4 break
//     via call-clobber DCE of the pinned var; blocking r0 walks to r9/r11).
//     The lwz r4,8(r1);cmpw r3,r4 pair occurs exactly ONCE in .text — no twin
//     source to copy. Everything else exact incl. chained
//     fn_801A56F4(fn_80174A58(..)), extern s32 global loads, literal returns.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern s32 lbl_80305EFC;
s32 fn_80128E34(CStruct *, void *, void *, s32);
s32 fn_80174A58(void *, CStruct *);
s32 fn_801A56F4(s32);
void fn_801A5CF0(void *, s32);
s32 fn_801A5CE8(Unk_C7387A53 *);
s32 fn_801746A4(Unk_C7387A53 *, s32);
void fn_801436E0(Unk_F8E9878F *, s32);
bool ScriptSelectCurrentSkater(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r31;
    s32 temp_r3;

    if (fn_80128E34(pParams, QB_NAME, &sp8, 0) == 0) {
        fn_80128E34(pParams, 0, &sp8, 1);
    }
    temp_r31 = lbl_80305EAC;
    temp_r29 = lbl_80305EFC;
    if (fn_801A56F4(fn_80174A58(temp_r31, 0)) == sp8) {
        return false;
    }
    fn_801A5CF0(temp_r29, sp8);
    temp_r30 = fn_80174A58(temp_r31, 0);
    temp_r3 = fn_801746A4(temp_r31, fn_801A5CE8(temp_r29));
    if (temp_r3 != 0) {
        fn_801436E0(temp_r3, temp_r30);
    }
    return true;
}
