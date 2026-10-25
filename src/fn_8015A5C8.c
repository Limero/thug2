// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015A5C8-0x8015A788 (448B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8009F498(s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801746A4(Unk_C7387A53 *, s32);
s32 fn_801745B4(s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_801A2C10(Unk_31DE137E *, s32);
void fn_801A2A58(s32);
s32 fn_80128E34(CStruct *, void *, void *, s32);
void fn_801A2F2C(Unk_31DE137E *, s32);
s32 fn_801A269C(Unk_31DE137E *);
void fn_80233328(void);
void Script_RunScript(s32, s32, s32, s32, s32);
extern void* lbl_80305EAC;
extern char lbl_80305FF8[];
// PARKED: tail xor-bool cracked via `(x ^ K) == 0` + `!(!(a || 0))` store-flag
// trick (xor+subfic+adde+cmpwi+beq all match); last 2 words are a load-target
// regalloc coin-flip: want loads *lbl_80305FF8 into r3, ngccc picks r11.
// Resists: register-pin to r3, asm "+r" barrier temp, direct-vs-temp call
// result, extern char[] vs s32 decl, -fno-schedule-insns(-2), -fno-gcse,
// pinned-key xor operand, ternary/volatile/u32 condition variants.
// 2026-09-02 re-probe: applied the matched-codebase idiom (`extern char
// lbl_80305FF8[]` + `*(void**)&lbl_80305FF8 + 0x44` deref, as in the
// promoted lbl_80305FF8 users) — no-op, 110/112; the r3-vs-r11 load-target
// coin is a regalloc artifact of this fn's own web, not the decl form.
// SOLVED 2026-09-02 (112/112 EXACT): pin the POINTER LOAD itself to r3 —
// `register s32 pff8 __asm__("r3") = *(s32 *)&lbl_80305FF8;` then deref
// pff8+0x44. Earlier attempts pinned the xor operand / used barriers; the
// load-target web must BE r3 for the sda21 load to land there.
s32 ScriptKillSkaterCamAnim(CStruct *pParams, CScript *pScript) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r0;
    s32 temp_r3;
    s32 var_r0;
    s32 var_r30;
    Unk_FFAD6788 *var_r3;

    spC = 0;
    var_r30 = 1;
    if (GetChecksum_2(pParams, QB_SKATERID, &sp8, 0) != 0) {
        var_r3 = fn_8009F498(sp8);
    } else if (GetInteger(pParams, QB_SKATER, &spC, 0) != 0) {
        var_r3 = fn_801746A4(lbl_80305EAC, spC);
    } else {
        var_r3 = fn_801745B4(lbl_80305EAC);
    }
    if ((var_r3 != NULL) && (var_r3->unk0xC8 != 0)) {
        temp_r3 = ContainsFlag(pParams, QB_CURRENT);
        if (temp_r3 != 0) {
            var_r30 = fn_801A2C10(((Unk_40426380 *)lbl_80305EAC)->unk0x378, 0);
        } else {
            temp_r3 = ContainsFlag(pParams, QB_ALL);
            if (temp_r3 != 0) {
                var_r30 = 1;
                fn_801A2A58(((Unk_40426380 *)lbl_80305EAC)->unk0x378);
            } else {
                sp10 = temp_r3;
                fn_80128E34(pParams, QB_NAME, &sp10, 1);
                var_r30 = 1;
                fn_801A2F2C(((Unk_40426380 *)lbl_80305EAC)->unk0x378, sp10);
            }
        }
    }
    temp_r3 = fn_801A269C(((Unk_40426380 *)lbl_80305EAC)->unk0x378);
    var_r0 = temp_r3 != 0;
    if (var_r0 == 0) {
        {
            register s32 pff8 __asm__("r3") = *(s32 *)&lbl_80305FF8;
            s32 a = (((Unk_1D62F22E_2 *)pff8)->unk0x44 ^ QB_EDIT) == 0;
            if (!(!(a || 0))) {
                fn_80233328();
            } else {
                Script_RunScript(QB_RESTORE_SKATER_CAMERA, 0, 0, 0, 0);
            }
        }
    }
    return var_r30;
}
