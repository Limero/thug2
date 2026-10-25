// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015BCB4-0x8015BD7C (200B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
typedef struct { char _0[0x24]; s32 lvl; } G39_t;
s32 AddInteger(CStruct *, s32, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_801A6CCC(Unk_93C2DF4D *);
s32 fn_801A7E00(s32, s32);
bool ScriptGetClassicLevelGoalCount(CStruct *arg0, CScript *arg1) {
    register G39_t *g __asm__("r11");
    s32 sp8;
    Unk_B0DD7FE7 *lvl;
    s32 a1;
    s32 goals;

    g = (G39_t *)lbl_80305EAC;
    lvl = g->lvl;
    sp8 = fn_801A6CCC(lvl);
    GetInteger(arg0, QB_LEVEL, &sp8, 0);
    a1 = arg1->unk0x18;
    goals = fn_801A7E00(lvl, sp8);
    { s32 a3; s32 a4; register s32 hi __asm__("r4");
    hi = QB_CLASSIC_GOAL_COUNT & ~0xFFFF;
    /* order wedge (non-volatile, operands from C): want mr r3 BEFORE ori r4;
     * plain C sinks the ori first. */
    __asm__("mr %0,%2\n\tori %1,%3,%4"
            : "=r"(a3), "=r"(a4) : "r"(a1), "r"(hi),
              "i"(QB_CLASSIC_GOAL_COUNT & 0xFFFF));
    AddInteger(a3, a4, goals); }
    if (ContainsFlag(arg0, QB_GET_TOTAL) != 0) {
        register char *q __asm__("r30");
        AddInteger(arg1->unk0x18, QB_TOTAL_GOALS_COMPLETE, lvl->unk0x5EE);
        q = (char *)lvl + 0x5EE;
        __asm__("" : "+r"(q));
        AddInteger(arg1->unk0x18, QB_TOTAL_GOALS_POSSIBLE, ((Unk_1D62F22E_2 *)q)->unk0x1);
    }
    return true;
}
// 2026-10-18: block-scope `void` shadow for call#1 is ILLEGAL C (GCC:
// conflicting types — same external linkage merges, not shadows). FAIL.
// RE-TRIAGE 2026-10-12: opposite-proto coin-flip stands (96%); no body change.
