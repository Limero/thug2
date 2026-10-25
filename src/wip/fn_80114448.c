// WIP DRAFT (non-matching)
// family=m2c range=0x80114448-0x80114520 size=216B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-23: 77.8% NEAR, 216B (length-exact), 12 differing words that
// are all downstream of ONE extra copy: retail keeps the `terrain` value in r3
// across the branch merge (`mr r4, r3`), ngccc homes it in r0 (`mr r0, r3`,
// then `mr r4, r0`).
// Decoded semantics (all callee protos confirmed against their units):
//   GetChecksum_2(pParams, QB_PARAM,      &sp8,  1)
//   if (GetChecksum_2(pParams, QB_TERRAIN, &spC, 0)) terrain = fn_8010BA84(spC)   /* u8 */
//   else { GetInteger(pParams, QB_TERRAIN_ID, &sp10, 1); terrain = ((u8*)&sp10)[3]; }
//   if (fn_8010BDDC(&sp14, terrain, sp8)) { fn_80127C14(pScript->unk0x18, sp8, (CStruct*)sp14); return 1; }
// The zero-init of the out block needs the first zero staged through r3
// (`li r3,0` / `stw r3,0x10`) — a plain `= 0` initialiser folds all three stores
// onto r0 and loses two words. `r3` pin + empty-asm barrier reproduces it.
// Levers tried and measured on the copy: pinning `terrain` to r3 (frame drops
// r29 and the byte load disappears entirely — wrong code, rejected), pinning
// pParams/pScript to r31/r29 (prologue matches, copy remains), u8/vs s32
// `terrain` (neutral), all six declaration orders and all six assignment orders
// of the out block (best = sp8/spC/sp10 as written), struct-backed out block
// (memset call, frame grows).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern u8 fn_8010BA84(s32);
extern s32 fn_8010BDDC(void *, s32, s32);
extern void fn_80127C14(CStruct *, s32, CStruct *);

s32 ScriptGetTerrainTypeParam(CStruct *pParams, CScript *pScript) {
    register s32 zero __asm__("r3");
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 terrain;

    zero = 0;
    __asm__ volatile("" : "+r"(zero));
    sp8 = 0;
    spC = 0;
    sp10 = zero;
    GetChecksum_2(pParams, QB_PARAM, &sp8, 1);
    if (GetChecksum_2(pParams, QB_TERRAIN, &spC, 0) != 0) {
        terrain = fn_8010BA84(spC);
    } else {
        GetInteger(pParams, QB_TERRAIN_ID, &sp10, 1);
        terrain = ((u8 *)&sp10)[3];
    }
    if (fn_8010BDDC(&sp14, terrain, sp8) != 0) {
        fn_80127C14(pScript->unk0x18, sp8, (CStruct *)sp14);
        return 1;
    }
    return 0;
}
