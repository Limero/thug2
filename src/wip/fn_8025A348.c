// WIP DRAFT — EnableMetroTRKInterrupts, plain C (no asm).
// family=m2c range=0x8025A348-0x8025A3AC size=100B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// REBUILT 2026-10-11: dropped the register-asm pins (r5 zero,
// ctx barrier) per no-asm policy; plain C with a TYPED struct-pointer local
// (char * + per-use casts CSE identically, so the struct-pointer form is
// kept as the readable one). Region check: want prologue is mflr-first +
// single stw r31 + lis/ori materialisation = mwcc, so ProDG scoring is
// meaningless here; all scores below are mwcc masked compares (branch/
// address-half masked, <scratch> + opt_cmp.py).
// PARKED 44% (GC/1.2.5n -O2, size-exact 100B; was 40% ProDG / 32% mwcc
// -O4,p). The -O2 prologue (mflr/stw/stwu/stw r31) matches want's first 4
// words except the r31 home slot (want 8(r1), all mwcc 0xc(r1)).
// VERSION MATRIX (same source): 1.0/1.1/1.2.5/1.2.5n -O4,p = 32%, 1.1p1 =
// 40%, 1.3/1.3.2/1.3.2r/2.5/2.6/2.7/3.0a5 = stwu-first family (<=20%),
// 1.2.5n -O2/-O3 = 44%, -Os/-O1 = size 108B. So: mflr-first family +
// low opt is the closest; the residual is scratch-reg choice (zero r0 vs
// r5, fnptr r12 vs r0, msg-lo addi vs ori, cmp r0 vs r3) + the r31 slot.
// No source shape moves them (local vs 3x-inline-extern CSE identically;
// address load always hoists above the saves at -O4,p, stays put at -O2).
// NEXT: a mwcc version whose saved-reg slot + ori-idiom match (slot 8 and
// ori suggest older/different patch than all tried), or accept as wall.
#include "types.h"
#include "structs.h"

extern char lbl_803A44A0[];
extern char lbl_80308A98[];
extern void OSReport(const char *msg, s32 a);
extern void lbl_8025D8D4(void);
extern void lbl_8025DE3C(void);

void EnableMetroTRKInterrupts(void) {
    Unk_23BC96A2 *ctx = (Unk_23BC96A2 *)lbl_803A44A0;

    ctx->unk0x6BC = 0;
    OSReport(lbl_80308A98, ctx->unk0x698());
    if (ctx->unk0x6CC == 4) {
        lbl_8025D8D4();
        lbl_8025DE3C();
    }
}
