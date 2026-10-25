// WIP DRAFT (non-matching) — hand-reconstructed from the want (m2c draft was garbage)
// family=m2c range=0x80079A50-0x80079CC4 size=628B
// FLAG: -fno-rerun-cse-after-loop -fno-expensive-optimizations
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// === PARKED (2026-10-01) ===
// SCORE: 632B object vs 628B want (+4B), masked pct 23.6% with the FLAG line
// above (608B / 2.5% without it). Verdict DIFF.  Measured with
// test_wip_drafts.py's own masked_pct (BOTH sides masked — a script that masks
// only the got side under-reports by ~9 points here, don't trust such a number).
// Audit: no private .rodata; 0 emitted inline-asm insns; the 7 REL24 targets
// are fn_8000F2F8/Mem_Alloc/fn_8000F320/fn_80079CC4/fn_80079DA8/fn_80079FB4/
// Mem_Free2 = the want's 7 `bl`s in order; `extern lbl_802FFE98` hand-decodes
// (lis r30,-0x7fd0 = 0x80300000, lwz -0x168(r30) = 0x802FFE98) to symbols.txt.
// A semantically WRONG variant (p[col] pointer walk, vD) scores 28.0%/636B —
// higher only because the masked compare is index-aligned; do not switch to it.
// WHAT THIS IS: a full semantic reconstruction, not a guess.  Every one of the
// 157 want instructions now has a 1:1 counterpart in the same order/shape
// (two `clamp()` shapes, the `1<<f6`/`1<<f7` re-reads, the preheader guard +
// latch double test of the outer loop, the inner-loop guard sitting in the
// outer body, the 4-term OR chain with its 3 compares, and the r8/r9 dim-pointer
// reload copies).  fn_80079CC4 = screen->buf rect read, fn_80079DA8 = buf->screen
// rect write (both promoted byte-exact, so the arg order is proven: arg2 =
// column offset, arg3 = row offset, arg4 = W, arg5 = H).
// WHY STUCK (the wall): GCC puts the loop-crossing `x < 0` condition in CR4 —
// the callee-saved CR field — and pays for it with a prologue `mfcr`/`stw` +
// epilogue `lwz`/`mtcrf` (+4 insns, +1 stack slot, Gsave moves 0x08->0x10).
// The want instead SPILLS it: `mfcr r27` at the outer loop head + `mtcrf 0x80,
// r27` at each use, and spends CR7 on the two short-lived conditions (so its
// (x<H) compare is `cmpw cr7` and carries an extra `slwi r28,r28,0x1c` before
// `mtcrf 0x88`).  That 4-insn substitution shifts the whole inner block by one
// word and then cascades into the register allocation, which is the real
// blocker: the want allocates r16-r31 (arg0=r22, W=r31, H=r20, xp=r24,
// yp=r25, xn=r26, yn=r27, buf=r23, base=r21, x=r10, y=r30, j=r29) and this
// draft allocates r18-r31 (+r12) — every callee-saved value differs even though
// the live sets are identical.
// TRIED (all measured, all no-ops on the CR4 choice): 6 permutations of the OR
// chain terms (GCC 2.95 normalises `||`-chain term order — all 6 compile
// identically, so term order is NOT a lever here); `while`/`for`/`do-while` for
// both loops; negated `arg2` in place vs a separate temp; hoisted lw/lh bound
// temps; separate `base` var vs in-place `row *= W` vs a `p[col]` pointer walk;
// `u16` vs `s32` for W/H; `(u16)` casts at the fills vs u16 vars; clamp forms
// `x<0`+`>H-1`, `x<0`+`>=H`, ternary, if/else, testing `x` instead of `row`;
// hoisted lh/lw temporaries; `register __asm__("rN")` pins on x/y/j; three
// `"+r"` barrier placements; inverted condition (`!(x>=0 && ...)`); an extra
// call.  ~40 flag sets too: every -fno-schedule-insns{,2}, -fno-gcse,
// -fno-thread-jumps, -fno-expensive-optimizations, -fno-cse-follow-jumps,
// -fno-branch-count-reg, -fno-strength-reduce, -fno-sched-{spec,interblock},
// -fno-peephole, -fno-rerun-cse-after-loop (alone and in 1-3 way combos),
// -O1/-O3/-Os, -mcpu=603/401/750e/7400, -mno-sdata.
// NOT TRIED: a promoted-function oracle scan for "mfcr at a loop head" (only 9
// of 656 promoted fns have a late mfcr and none has this shape, so there is no
// sibling to copy a source construct from), and rebuilding GCC's reload
// preference order.  The diagnostic that identifies the wall in one
// comparison: count `cr4` in `want_got.py`'s G column — if G has `cmpwi cr4`
// where W has a bare `cmpwi` followed by `mfcr`, the CR4 route is in play and
// every downstream register number is suspect.
//
// === what the FLAG line is doing (keep it if you rework this) ===
// -fno-rerun-cse-after-loop is REQUIRED to reproduce the want's dim-pointer
// pattern: the want loads `arg0->unk0xC` four times (0x80079A74/0x80079A9C/
// 0x80079B7C/0x80079C5C) and keeps a copy in r8 via `mr r8,r9`, i.e. the
// available-expression was NOT propagated across the two `if` diamonds.  With
// the default build GCC merges the four loads into one (r9) and drops 4 `mr`s;
// with this flag it keeps the reloads.  -fno-expensive-optimizations is worth
// ~2 more points of shape.  Both flags are already used by promoted files
// (src/fn_8017DD54.c, src/fn_801840F0.c; src/fn_8000901C.c,
// src/fn_8000A0A8.c, src/fn_80011BB8.c).
#include "types.h"
#include "structs.h"

extern Unk_9994C3F5 *lbl_802FFE98;

void Mem_Free2(void *);
void *Mem_Alloc(s32);
void fn_8000F2F8(Unk_9994C3F5 *, s32);
void fn_8000F320(Unk_9994C3F5 *);
void fn_80079CC4(Unk_9994C3F5 *, s32, s32, s32, s32, u32);
void fn_80079DA8(Unk_9994C3F5 *, s32, s32, s32, s32, u32);
void fn_80079FB4(Unk_9994C3F5 *, s32, s32, s32);

s32 fn_80079A50(Unk_9994C3F5 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 xn, xp, yn, yp;
    s32 W, H;
    s32 *buf;
    s32 i, j, x, y, row, col, base;

    arg2 = -arg2;
    if (arg1 >= 0) {
        xn = 0;
        xp = arg1;
        W = (u16)(1 << *(u8 *)(*(s32 *)((char *)arg0 + 0xC) + 6)) - arg1;
    } else {
        xp = 0;
        xn = -arg1;
        W = (u16)(1 << *(u8 *)((*(s32 *)((char *)arg0 + 0xC)) + 6)) - xn;
    }
    if (arg2 >= 0) {
        yn = 0;
        yp = arg2;
        H = (u16)(1 << *(u8 *)(*(s32 *)((char *)arg0 + 0xC) + 7)) - arg2;
    } else {
        yp = 0;
        yn = -arg2;
        H = (u16)(1 << *(u8 *)((*(s32 *)((char *)arg0 + 0xC)) + 7)) - yn;
    }
    fn_8000F2F8(lbl_802FFE98, lbl_802FFE98->unk0x118);
    buf = (s32 *)Mem_Alloc(W * H * 4);
    fn_8000F320(lbl_802FFE98);
    fn_80079CC4(arg0, buf, (u16)xn, (u16)yn, (u16)W, (u16)H);
    fn_80079DA8(arg0, buf, (u16)xp, (u16)yp, (u16)W, (u16)H);
    if (arg3 == 0) {
        i = 0;
        x = -yp;
        while (i < (u16)(1 << *(u8 *)(*(s32 *)((char *)arg0 + 0xC) + 7))) {
            row = x;
            if (row < 0) {
                row = 0;
            }
            if (row > H - 1) {
                row = H - 1;
            }
            base = row * W;
            y = -xp;
            j = 0;
            while (j < (u16)(1 << *(u8 *)(*(s32 *)((char *)arg0 + 0xC) + 6))) {
                if (y < 0 || y >= W || x < 0 || x >= H) {
                    col = y;
                    if (col < 0) {
                        col = 0;
                    }
                    if (col > W - 1) {
                        col = W - 1;
                    }
                    fn_80079FB4(arg0, buf[base + col], (u16)j, (u16)i);
                }
                j++;
                y++;
            }
            i++;
            x++;
        }
    }
    if (buf != 0) {
        Mem_Free2(buf);
    }
    return 1;
}
