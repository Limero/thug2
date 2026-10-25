// WIP DRAFT (non-matching) — hand-rebuilt from disasm 2026-10-15
// (prior body was a raw m2c stub at 0.8%: literal MMIO addresses emitted as
// lis+ori+lwz chains, indirect calls via blrl, wrong spin shape).
// family=hand range=0x8025D3CC-0x8025D550 size=388B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// WHAT IT IS: ARAM/DMA drain helper in the unsymbolized 0x8025D010-0x8025D550
// gap (no symbols.txt entries: score via tools/score_wip.py which needs no
// symbol, e.g. LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/score_wip.py
// 0x8025D3CC src/wip/fn_8025D3CC.c). If lbl_80308C70==1 call fn_8025D32C;
// spin on MMIO 0xCC006834&1; decrement the CD08 counter and while it is not
// -1 repeatedly call fn_8025CD6C(CD04, 0x400) bumping CD04 by 0x400 (0x400-
// chunk DMA pump); if the CD0C remainder slot is nonzero flush it via
// fn_8025CD6C(CD04, CD0C) and clear it; clear MMIO 0xCC006828; while the CD10
// flag is set repeat the whole sequence starting with fn_8025D32C; tail-call
// fn_8025D5F8. Prologue: stwu -0x28, stmw r24, frame has NO locals.
// SLOT MAP (all .bss, all accessed via 0x803B-page lis remats in the want):
// CD04=0x803ACD04 (DMA addr), CD08=0x803ACD08 (counter), CD0C=0x803ACD0C
// (remainder), CD10=0x803ACD10 (outer flag). NOTE the first version of these
// notes swapped CD0C/CD10: the remainder block is CD0C, the outer-loop flag
// is CD10 (verified against 0x8025D458/0x8025D494 disasm).
// WANT'S REGISTER SET: r30=CD08 base (head+tail), r31=CD04 base (head+inner),
// r27=CD0C base (kept across the head remainder into the tail), r24=CD0C
// tail-cond, r25=CD04 tail-remainder, r26=CD10 tail, r29=MMIO-tail base,
// r28=tail zero; head uses caller-saved r9/r11 remats + li r0 zeros.
// PARKED 2026-10-15 at 19.8% (73/91 words, got 364B vs want 388B).
// LOAD-BEARING (ablation-verified, each measured via score_wip.py):
//  * extern u8 arr[] + (off) anchors (never literal addresses, never
//    scalar-extern-used-as-pointer: the latter double-loads, D288 recipe).
//  * Blanch MMIO stays a bare literal (no ELF symbol can exist for 0xCC00).
//  * Pinned pointer homes assigned LAZILY at first use (register s32 *cnt
//    __asm__("r30") etc.): pins at declaration burst 8 inits into the
//    prologue region (v8: 2.2%), lazy assignment births each base at its
//    first use like the want AND absorbs scheduler-hoisted lis's (fixes the
//    MMIO double-lis the plain build emits).
// WALLS (do not redo without a new idea):
//  * Reload-after-store (4-5 words): want emits stw;lwz(same);cmp for every
//    counter update, but ProDG reuses the kept value for `*p -= 1;
//    if (*p != -1)` in every spelling (plain, statement-form, volatile
//    condition-read). Volatile conditions do NOT reload on this compiler —
//    they emit a junk `mr r0,rX` + compare instead (v6: 19.8% at 384B, same
//    score via 4 mr words, keep that variant in mind). Cross-anchor alias
//    reads (cond via CDA0-0x98, store via CCC0+0x48) DO force the reload but
//    poison all CSE: +36B and +2 saved regs (v7: 7.9%). The want's merged
//    addresses + unmerged loads combination is not reachable from plain C;
//    -fno-gcse would unmerge the addresses too.
//  * Exact reg homing: got keeps bases in caller-saved remats where want
//    uses r30/r31/r27; pins fix the homes but shift the prologue (frame
//    -0x20 vs want -0x28: fewer other pseudos go callee-saved once pinned).
// VARIANT LOG (all ProDG/3.9.3 default flags, scores from score_wip.py):
//  v1 volatile-everywhere, single CCC0 anchor: 9.1%, 396B (anchor collapse).
//  v2 +fixed 8C70 decl, 3 BSS anchors: 15.2%, 396B.
//  v3 +CD0C/CD10 unswap, 2 anchors: 15.2% (extra r23 saved: 9 regs).
//  v4 plain BSS, volatile only on MMIO: 17.4%, 368B, prologue EXACT.
//  v5 statement-form updates: 17.4% (gcc still reuses across -=/read).
//  v6 volatile != -1 conds: 19.8%, 384B (4 mr words, no real reloads).
//  v7 alias-anchor conds: 7.9%, 404B (CSE poison, +2 regs).
//  v8 eight upfront pointer locals: 2.2% (init burst in prologue).
//  v9 (this body) lazy pins: 19.8%, 364B, MMIO block exact.
// PROMOTION PREREQUISITES (bigger job, not just this file): the whole
// 0x8025D010-0x8025D550 gap has no symbols.txt entries and no splits; the
// true neighbors (real entries, not m2c guesses) must be established first,
// then symbols + splits + configure wiring for each function in the gap.
// Compare the matched ProDG neighbors src/fn_8025D550.c / src/fn_8025D5F8.c
// (plain non-volatile globals, same anchor style) and the parked sibling
// src/wip/fn_8025D288.c (75.6%: the distinct-anchor recipe for this cluster).
#include "types.h"

extern u8 lbl_80308C70[];
extern u8 lbl_803ACCC0[];
extern u8 lbl_803ACDA0[];

void fn_8025D32C(void);
void fn_8025CD6C(s32, s32);
void fn_8025D5F8(void);

void fn_8025D3CC(void) {
    register s32 *cnt __asm__("r30");
    register s32 *addr __asm__("r31");
    register s32 *rem __asm__("r27");

    if (*(s32 *)lbl_80308C70 == 1) {
        fn_8025D32C();
    }
    while (*(volatile u32 *)0xCC006834 & 1) {
    }
    cnt = (s32 *)(lbl_803ACCC0 + 0x48);
    addr = (s32 *)(lbl_803ACDA0 - 0x9C);
    *cnt -= 1;
    if (*cnt != -1) {
        do {
            fn_8025CD6C(*addr, 0x400);
            *cnt -= 1;
            *addr += 0x400;
        } while (*cnt != -1);
    }
    rem = (s32 *)(lbl_803ACDA0 - 0x94);
    if (*(s32 *)(lbl_803ACCC0 + 0x4C) != 0) {
        fn_8025CD6C(*addr, *(s32 *)(lbl_803ACCC0 + 0x4C));
        *(s32 *)(lbl_803ACCC0 + 0x4C) = 0;
    }
    *(volatile u32 *)0xCC006828 = 0;
    if (*(s32 *)(lbl_803ACDA0 - 0x90) != 0) {
        do {
            fn_8025D32C();
            *cnt -= 1;
            if (*cnt != -1) {
                do {
                    fn_8025CD6C(*addr, 0x400);
                    *cnt -= 1;
                    *addr += 0x400;
                } while (*cnt != -1);
            }
            if (*rem != 0) {
                fn_8025CD6C(*addr, *rem);
                *rem = 0;
            }
            *(volatile u32 *)0xCC006828 = 0;
        } while (*(s32 *)(lbl_803ACDA0 - 0x90) != 0);
    }
    fn_8025D5F8();
}
