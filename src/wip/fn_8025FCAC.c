// WIP DRAFT (non-matching) — hand-written from disasm 2026-10-09.
// family=hand range=0x8025FCAC-0x8025FE28 size=380B
// INERT: not wired in configure.py — never compiled.
//
// ============================ STATUS 2026-10-09 ====================
// mwcc region (GC/1.3.2 + cflags_dolphin).  NOT an asm wall — this is plain C.
// Current best: object 380B == symbols.txt size, 66/95 words (69.5%), residual
// is register colour + 2 materialisation-order slots; no semantic diff left.
// Verify: tools/venv/bin/python <scratch> \
//              0x8025FCAC src/wip/8025FCAC.c
// (mscore.py = /tmp copy of the mwcc scorer; the ngccc sweep reports FAIL on
//  `asm {}` bodies, which is expected for this region.)
//
// Retail structure (four records; every call is DCFlushRangeNoSync(addr, 4)):
//   base r5 = 0x80000000 shared by the vector load/store and the call arg
//   A1 vec   = 0x80000300, handler = fn_8025FE28, tramp = 0x8025FF14
//      old = *(u32*)0x80000300;
//      *(u32*)0x80000300 = 0x48000000 | (0x8025FE28 - 0x80000300);
//      DCFlushRangeNoSync(0x80000300, 4); sync; isync; icbi r3,r0;
//      *(u32*)0x8025FF14 = old;   (+ flush/icbi)
//   B1 tramp = 0x8025FF18 — NEGATIVE-displacement form:
//      *(u32*)0x8025FF18 = 0x48000000 | ((0x80000304 - 0x8025FF18) & 0x3FFFFFF);
//      [ = 0x4BDA03EC, i.e. `b 0x80000304` ]
//   A2 vec = 0x80000400 / handler fn_8025FFD0 / tramp 0x802600BC, B2 0x802600C0
//      (same shape as A1/B1 with the 0x400 base).
//
// CODEGEN FACTS ESTABLISHED THIS ROUND (they are what the draft encodes):
//  * The branch word CANNOT be constant-folded: with literal handler addresses
//    mwcc folds `0x48000000 | (A - B)` into one `lis/ori` and the object comes
//    out 340B instead of 380B.  The handlers must be SYMBOL references
//    (`(u32)fn_8025FE28` — declared extern), which is what generates the retail
//    `lis r3,handler@ha ; addi r3,r3,handler@l ; addis r6,r3,-0x8000 ; addi
//    r6,r6,-0x300 ; oris r0,r6,0x4800` runtime computation.
//  * B1/B2's `neg` is a source-level unary minus: writing
//    `off = (u32)slot - 0x80000304; *slot = 0x48000000 | ((-off) & 0x3FFFFFF);`
//    reproduces retail's `addis r5,r31,-0x8000 ; addi r5,r5,-0x304 ; neg r0,r5 ;
//    clrlwi r0,r0,6 ; oris r0,r0,0x4800` exactly.  (The `0x3FFFFFF` mask, not
//    `0x3FFFFFC`, is what makes mwcc emit `clrlwi 6`.)
//  * The icbi wedge must name a `register`-qualified variable (mwcc error
//    "x was not assigned to a register" otherwise; a plain parameter/mnemonic
//    operand does not parse).  Declaring the temp at function top and ASSIGNING
//    it *after* the `sync` statement is what puts retail's address
//    rematerialisation between `sync` and `li r0,0`; with the assignment before
//    `sync` (or with the address passed as an inlined helper parameter) the
//    materialisation lands one slot earlier and the whole 8-insn block shifts.
//    Constant addresses rematerialise (`lis r3,-0x8000 ; addi r3,r3,0x300`),
//    slot addresses stay live in a callee-saved reg (`icbi r31,r0`) — both
//    match retail.
//  * Declaration order `u32 *slot;` BEFORE `u32 old;` is load-bearing for the
//    r31/r30 colours: slot first => slot=r31/old=r30 (want), old first =>
//    the two swap (43 diffs vs 29).
//
// RESIDUAL (29 of 95 words, all colour/order — do not re-grind blind):
//   1. A1/A2 base `lis r5,-0x8000` (want) vs `lis r6,-0x8000` (got): in want the
//      vec base is materialised SECOND (right after the handler `lis`) and gets
//      r5, in ours the branch value takes r5 and the base r6.  Statement and
//      declaration permutations tried this round: value named in a local, the
//      `old` load split from the store, block-scoped `u32 *v1 = (u32*)0x80000000`
//      with `v1[0xC0]` (grows the object to 392B — the local stays live), `vec`
//      local (392B), (void*)0x80000300 vs &v[0xC0] call arg.  All inert or worse.
//   2. `stw r30,0(r31)` (want) vs `stw r30,-0xec(r3)` (got): mwcc folds the
//      literal tramp address into the store's displacement off the symbol base;
//      retail computed the address into r31 first.  Only the *first* store of
//      each pair folds; the B-records (`0(r31)`) already match.
//   3. B1/B2 value colour r0 (want) vs r5 (got) — follows from (1).
// If the allocator/ordering residual is to be attacked, it needs `mwcceppc -S`
// (or the .lreg dump) on this body, not more statement permutations.
// 2026-10-15: function-local fixed-register pins are DEAD in mwcc —
// `register u32 *vb __asm__("r5")` (+ r6 value pin) compiles byte-identical
// to the unpinned body (pins silently ignored; the only project precedent is
// file-scope pins on call-preserved regs). Score via mwcc 1.3.2, not the
// ngccc sweep: tools/mwcc_verify.py with GC/1.3.2 (69.5%, size-exact).
// =========================================================================
#include "types.h"

extern void DCFlushRangeNoSync(void *addr, u32 len);
extern void fn_8025FE28(void);
extern void fn_8025FFD0(void);

void fn_8025FCAC(void) {
    u32 *slot;
    u32 old;
    u32 off;
    register u32 ib;

    old = *(u32 *)0x80000300;
    *(u32 *)0x80000300 = 0x48000000 | ((u32)fn_8025FE28 - (u32)0x80000300);
    DCFlushRangeNoSync((void *)0x80000300, 4);
    asm { sync }
    ib = 0x80000300;
    asm { li r0, 0 }
    asm { isync }
    asm { icbi ib, r0 }

    slot = (u32 *)0x8025FF14;
    *slot = old;
    DCFlushRangeNoSync(slot, 4);
    asm { sync }
    ib = (u32)slot;
    asm { li r0, 0 }
    asm { isync }
    asm { icbi ib, r0 }

    slot = (u32 *)0x8025FF18;
    off = (u32)slot - 0x80000304;
    *slot = 0x48000000 | ((-off) & 0x3FFFFFF);
    DCFlushRangeNoSync(slot, 4);
    asm { sync }
    ib = (u32)slot;
    asm { li r0, 0 }
    asm { isync }
    asm { icbi ib, r0 }

    old = *(u32 *)0x80000400;
    *(u32 *)0x80000400 = 0x48000000 | ((u32)fn_8025FFD0 - (u32)0x80000400);
    DCFlushRangeNoSync((void *)0x80000400, 4);
    asm { sync }
    ib = 0x80000400;
    asm { li r0, 0 }
    asm { isync }
    asm { icbi ib, r0 }

    slot = (u32 *)0x802600BC;
    *slot = old;
    DCFlushRangeNoSync(slot, 4);
    asm { sync }
    ib = (u32)slot;
    asm { li r0, 0 }
    asm { isync }
    asm { icbi ib, r0 }

    slot = (u32 *)0x802600C0;
    off = (u32)slot - 0x80000404;
    *slot = 0x48000000 | ((-off) & 0x3FFFFFF);
    DCFlushRangeNoSync(slot, 4);
    asm { sync }
    ib = (u32)slot;
    asm { li r0, 0 }
    asm { isync }
    asm { icbi ib, r0 }
}
