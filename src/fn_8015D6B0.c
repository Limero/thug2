// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015D6B0-0x8015D744 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 fn_80128C80(CStruct *, void *, void *, s32);
void *fn_801746A4(Unk_C7387A53 *, s32);
s32 fn_801403CC(void *);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_80182E10(Unk_C7387A53 *, s32);
// PARKED 94.6%: single doc-15 arg-setup coin-flip at GetInteger call — want
// [li r4,0; stw r29,0xc(r1); mr r3,r31], got [li r4,0; mr r3,r31; stw]. Resists
// 12 flag configs, comma-fold into args, named-zero web, proto flips (M8.31),
// r3-clobber barrier.
bool ScriptAddBonus(CStruct *arg0) {
    s32 sp8;
    s32 spC;
    Unk_FFAD6788 *temp_r3;
    s32 temp_r30;
    s32 g;

    g = lbl_80305EAC;
    sp8 = 0;
    fn_80128C80(arg0, QB_SKATER, &sp8, 1);
    temp_r3 = fn_801746A4(g, sp8);
    if (temp_r3->unk0xC8 != 0) {
        temp_r30 = fn_801403CC(temp_r3);
        GetInteger(arg0, 0, ((spC = 0), &spC), 0);
        fn_80182E10((s32)temp_r30, spC);
    }
    return true;
}
