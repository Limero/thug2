// PARKED 2026-10-03 — base 8.3% (680 B but only 24 words score; the rest of
// the function is VMX/PS that plain capstone will not decode).  FPR/VMX wall —
// `bdnz` self-branch at 0x801B8310 plus a `mtctr` loop over FPR pairs.
// Not a GPR-only candidate; left as the m2c best guess.
//
// family=m2c range=0x801B82F0-0x801B8598 size=680B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// RESTORED 2026-09-20 by tools/restore_best_body.py.  The working body
// scored 0.6% while git revision b84f19fe8 scores 1.2%;
// the pool's struct-ification sweep and/or tools/store_order_search.py had
// rewritten this body in place and kept the worse result while the notes
// above stayed put.  Winner picked from 6 distinct committed bodies.
// Re-verify with tools/score_addrs.py before editing again.
#include "types.h"
void fn_801B82F0(void *arg0, f32 farg11, f32 farg12) {
    f32 sp7C;
    f32 sp74;
    f32 sp6C;
    f32 sp64;
    f32 sp5C;
    f32 sp54;
    f32 sp48;
    s32 sp8;
    f32 temp_f6;
    f32 temp_f7;
    f32 var_f12;
    s32 var_ctr;

    var_f12 = farg11;
    var_ctr = 4;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    0;
    temp_f6 = *(f32 *)0x802AC214;
    temp_f7 = *(f32 *)0x802AC218;
    0;
    0;
    0;
    0;
    0;
    sp48 = temp_f6;
    0;
    *(s32 *)((char *)&sp48 + 0x8) = temp_f6;
    *(s32 *)((char *)&sp48 + 0x4) = temp_f7;
    sp54 = temp_f7;
    0;
    if (farg12 > temp_f6) {
        0;
        sp5C = temp_f7;
        0;
    }
    0;
    0;
    0;
    0;
    0;
    0;
    sp64 = temp_f7;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    if (var_f12 > temp_f6) {
        var_f12 = temp_f7;
        0;
        sp6C = var_f12;
        0;
    }
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    sp74 = temp_f7;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    if (var_f12 > temp_f6) {
        0;
        sp7C = temp_f7;
        0;
        0;
    }
    0;
    0;
    0;
    0;
    0;
    0;
}
