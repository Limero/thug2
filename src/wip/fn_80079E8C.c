// WIP DRAFT (non-matching) — hand-rewritten 2026-10-01 , not an
// auto-generated body any more.  The old m2c body and its history:
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s)
// re-ordered; score 12.2%.
// RESTORED 2026-09-20 by tools/restore_best_body.py (m2c body, 21.6% masked —
// but that body's `extsb`, 2-arg vcall, prototyped memcpy and countdown loop
// are all wrong; see the PARKED block for the rewrite).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// family=m2c range=0x80079E8C-0x80079FB4 size=296B
// FLAG: -O1
//
// === PARKED (2026-10-01) ===
// score: DIFF 12.2% masked, object .text = 292 B vs want 296 B (73 vs 74 words).
//        (The parked m2c body scored 21.6% masked at the same 292 B — that %
//        is index-aligned luck, not quality: this body has the EXACT CFG,
//        all 8 branch relocations on want's targets, the right frame class,
//        and every semantic fix below.  Do not "restore" the m2c body.)
//
// Semantics established (each is load-bearing, all verified against want):
//  1. arg0+0xC is a POINTER whose +6/+7 are u8 log2 shifts.  m2c read them as
//     `char`, which emits a spurious `extsb`; `u8` reproduces want's bare
//     `lbz`+`slw`.
//  2. that pointer field must be `volatile` (`E8C_Info *volatile info`): want
//     loads 0xC(arg0) TWICE in the straight-line prefix (and again in the
//     loop); with a plain pointer ngccc CSEs them into one.  Same for the
//     second `li rX,1` region — see (7).
//  3. arg0+8 is a vtable-ish pair: s16 self-adjust at +0x158, fn ptr at
//     +0x15C, called as `mtlr r0; blrl` through a PROTOTYPED 1-arg cast
//     (want has no `crclr` before either `blrl`).  m2c passed a bogus 2nd
//     argument -> extra `mr r4,r9`.
//  4. `memcpy` must stay UNPROTOTYPED: want has `crclr cr1eq` before the
//     `bl`, so drop the declaration (recipe 21 / §6bf).
//  5. the loop is a rotated counted loop with the INCREMENT IN THE BODY:
//     `i = 0; while (i < ncols) { i++; ... }` with an UNSIGNED counter
//     (`u32 i` -> `cmplw`, not `cmpw`), giving want's
//     `cmplw/bge` pre-test + `addi` in the body + `cmplw/blt` latch.
//     A plain `for` lets -O2 strength-reduce it into a countdown
//     (`addic. rN,rN,-1` + `cmpwi/blt`) which want does not have.
//  6. the row pitch is `((1 << exp6) << 2) & 0x3FFFC`; written as
//     `(1 << exp6) * 4` ngccc folds it to `li rX,4; slw` instead of want's
//     loop-invariant `li r24,1; slw; rlwinm r0,r0,2,0xe,0x1d`.
//  7. the min-clamp must be `if (a <= lim) x = (u16)a; else x = lim;`
//     (then-arm out of line).  The `if (a > lim) x = lim; else ...` spelling
//     and the ternary spelling give want's SHAPE only at -O1 (see below).
//  8. the pitch/`1` invariants must be computed in the loop PREHEADER, so
//     `src += h * 4` inline (not a hoisted `pitch` local) — a named local is
//     computed before the pre-test branch instead of after it.
//
// WHY IT IS STUCK — want combines two mutually exclusive compiler outputs:
//   * want's CFG (the two-arm min with real `b`s, and no IV strength-reduce)
//     is produced ONLY at -O1.  At -O2 ngccc's final crossjump/if-conversion
//     hoists the min's then-arm `mr` ABOVE the compare and leaves a no-op /
//     out-of-range `bgt` (verified: the same CFG in a 20-line micro case
//     emits `bgt` to an offset past the end of the function).  -O2 also
//     strength-reduces the loop to a countdown.  Identical at ProDG
//     3.5/3.5b140/3.7/3.8.1/3.9.3, and `-fno-crossjumping` / `-fno-loop-optimize`
//     / `-fno-cse` are all rejected by cc1 3.9.3, so there is no flag that
//     keeps -O2's passes and drops just that one.
//   * want's LINEAR ORDER is a -O2-grade global schedule: its first block is
//     a fourteen-operation sequence that moves r3 to r28, materialises 1 in
//     r0, loads word 0xc into r9, moves r5 to r24 and r7 to r26 and r4 to r30,
//     loads byte 6 of r9 into r11, subtracts r26 from r24 into r5, moves r6
//     to r31, then shifts, masks and compares. The four parameter copies are
//     therefore INTERLEAVED with the loads in that block.
//     parameter copies are INTERLEAVED with the loads.  At -O1 (with or
//     without -fschedule-insns2) assign_parms puts all four `mr`s at the top
//     of the block and no flag or source form moves them.
// Residual, in order of size: (a) that 8-insn order difference, (b) 6
// register-permutation swaps inside the same register SET (want this=r28,
// i=r29, src/dst=r30/r31, y=r24, w=r31; -O1 picks this=r29/r28 and
// src=r31/dst=r29 unless `i`/`src` are pinned), (c) want re-materialises the
// constant `1` for the second limit (3 `li`s total, we emit 2) because in
// want it shares r0 with lim1, so the live range must split — pure colouring,
// and `-fno-cse` does not exist here.
// The two `register __asm__` pins below (i->r29, src->r30) are the only
// codegen levers applied; they are semantically correct (no clobbered live
// value) and buy ~4 masked words.  0 emitted inline-asm instructions; no
// private .rodata; 8/8 branch relocations already land on want's targets.
// NOT TRIED: making the two min arms assign to two different variables and
// re-joining (a source shape that might give the then-block a second
// predecessor and so defeat the -O2 crossjump), and a `volatile`/`asm`
// barrier between the two limits to split the constant's live range.
#include "types.h"

typedef struct {
    char pad0x0[6];
    u8 exp6;
    u8 exp7;
} E8C_Info;
typedef struct {
    char pad0x0[0x158];
    s16 off;
    s32 (*fn)(void *);
} E8C_Vt;
typedef struct {
    char pad0x0[8];
    E8C_Vt *vt;
    E8C_Info *volatile info;
} E8C_Obj;

void fn_80079E8C(E8C_Obj *this, s32 x, s32 y, s32 w, s32 h, s32 h2) {
    u16 lim1 = (u16)((1 << this->info->exp6) & 0xFFFF);
    s32 rows = h - y;
    u16 lim2 = (u16)((1 << this->info->exp7) & 0xFFFF);
    s32 cols = h2 - w;
    u16 nrows, ncols;
    register u32 i __asm__("r29");
    register u8 *src __asm__("r30");
    u8 *dst;

    if (rows <= (s32)lim1) {
        nrows = (u16)rows;
    } else {
        nrows = lim1;
    }
    if (cols <= (s32)lim2) {
        ncols = (u16)cols;
    } else {
        ncols = lim2;
    }
    if (this->vt->fn((char *)this + this->vt->off) == 0) {
        return;
    }
    i = 0;
    dst = (u8 *)this->vt->fn((char *)this + this->vt->off);
    src = (u8 *)x + ((w * h + y) * 4);
    while (i < ncols) {
        i++;
        memcpy(dst, src, nrows * 4);
        src += h * 4;
        dst += ((1 << this->info->exp6) << 2) & 0x3FFFC;
    }
}
