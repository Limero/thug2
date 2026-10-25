// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B3220-0x801B3514 (756B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void fn_8009E3D0(s32, s32, s32 *);
s32 fn_8009E408(s32, s32, s32 *);
s32 GetStructure(s32, s32);
s32 GetStructure_2(s32, s32, s32 *, s32);
s32 GetChecksum_2(s32, s32, s32 *, s32);
s32 ContainsFlag(s32, s32);
void SetChecksumTag(s32, s32, s32);
void fn_8009F204(s32, s32, s32);
void fn_801B30A4(void *);
void fn_801B31AC(void *);
s32 fn_801316D8(void);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_801B97F8(void *, s32);
void fn_801309EC(s32);

bool fn_801B3220(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 spC = arg2;
    s32 sp8;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    register s32 vw __asm__("r3");
    s32 temp;

    sp8 = 0;
    fn_8009E3D0(arg0->unk0xC, QB_PED_INIT, &sp8);
    if (sp8 != 0) {
        if ((spC == 0) && (fn_8009E408(arg0->unk0xC, QB_UNIQUESTATETABLE, &spC) == 0)) {
            spC = QB_PED_STATELOGIC_TABLE;
        }
        temp = GetStructure(spC, 0);
        if (temp != 0) {
            sp10 = 0;
            if (GetStructure_2(temp, arg1, &sp10, 0) == 0) {
                if (spC == QB_PED_STATELOGIC_TABLE) {
                    return false;
                }
                spC = QB_PED_STATELOGIC_TABLE;
                if (GetStructure_2(GetStructure(spC, 0), arg1, &sp10, 0) == 0) {
                    return false;
                }
            }
            sp14 = 0;
            GetChecksum_2(sp10, QB_SCRIPT_PED_STATE, &sp14, 1);
            sp18 = QB_NO_MOVE_UPDATE;
            GetChecksum_2(sp10, QB_PED_UPDATE_TYPE, &sp18, 0);
            if (arg0->unk0x28 != -QB_UNKNOWN_0x25CBFC50) {
                temp = GetStructure(arg0->unk0x2C, 0);
                if (temp != 0) {
                    sp1C = 0;
                    if (GetStructure_2(temp, arg0->unk0x28, &sp1C, 0) != 0) {
                        if (GetChecksum_2(sp1C, QB_EXIT_STATE_ACTION, &sp20, 0) != 0) {
                            vw = sp20;
                            if (vw == QB_WAIT_ANIM_FINISHED) {
                                if (ContainsFlag(sp10, 0x30AC01) == 0) {
                                    SetChecksumTag(arg0->unk0xC, QB_DELAYEDSTATE, arg1);
                                    arg1 = -QB_UNKNOWN_0x0B3E9C62;
                                    SetChecksumTag(arg0->unk0xC, QB_DELAYEDTABLE, spC);
                                    spC = QB_PED_STATELOGIC_TABLE;
                                    sp14 = QB_STATECONTROL_DELAY_WAITANIM;
                                    sp18 = QB_NO_MOVE_UPDATE;
                                }
                            } else if (fn_801316D8() != 0) {
                                Script_RunScript(sp20, 0, arg0->unk0xC, 0, 0);
                            }
                        }
                        if (ContainsFlag(sp1C, QB_HIDE_BOARDGEOM) != 0) {
                            fn_801B97F8(arg0, 0);
                        }
                    }
                }
            }
            arg0->unk0x28 = arg1;
            arg0->unk0x2C = spC;
            arg0->unk0x30 = sp18;
            fn_8009F204(arg0->unk0xC, sp14, arg3);
            fn_801B30A4(arg0);
            fn_801B31AC(arg0);
            if (ContainsFlag(sp10, QB_HIDE_BOARDGEOM) != 0) {
                fn_801B97F8(arg0, 1);
            }
            if (*(s32 *)((char *)arg0->unk0xC + 0x14) != 0) {
                fn_801309EC(*(s32 *)((char *)arg0->unk0xC + 0x14));
            }
            return true;
        }
    }
    return false;
}
