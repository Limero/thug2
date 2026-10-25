// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015BB78-0x8015BC5C (228B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
typedef struct { char _0[0x24]; s32 lvl; } G39_t;
s32 AddInteger(CStruct *, s32, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_801A6CCC(Unk_93C2DF4D *);
bool ScriptGetCareerLevelScore(CStruct *pParams, CScript *pScript) {
    register G39_t *g __asm__("r11");
    s32 sp8;
    Unk_B0DD7FE7 *lvl;
    u16 *pa;
    u16 *pb;

    g = (G39_t *)lbl_80305EAC;
    lvl = g->lvl;
    sp8 = fn_801A6CCC(lvl);
    GetInteger(pParams, QB_LEVEL, &sp8, 0);
    pa = (u16 *)((char *)lvl + 0x584);
    AddInteger(pScript->unk0x18, QB_LEVEL_SCORE, pa[sp8]);
    pb = (u16 *)((char *)lvl + 0x5AE);
    AddInteger(pScript->unk0x18, QB_LEVEL_SCORE_TOTAL, pb[sp8]);
    if (ContainsFlag(pParams, QB_GET_TOTAL) != 0) {
        register char *q __asm__("r30");
        AddInteger(pScript->unk0x18, QB_TOTAL_SCORE, lvl->unk0x5D8);
        q = (char *)lvl + 0x5D8;
        __asm__("" : "+r"(q));
        AddInteger(pScript->unk0x18, QB_TOTAL_SCORE_POTENTIAL, ((Unk_21634967 *)q)->unk0x2);
    }
    return true;
}
