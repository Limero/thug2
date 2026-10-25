// WIP DRAFT (non-matching) — hand decode from disasm 2026-10-11.
// family=hand range=0x8025D32C-0x8025D3CC size=160B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED 2026-10-11 at 95.0% NEAR (38/40 words, SIZE-EXACT 160B; started
// 10%). Reproduce: LEAF_TMPDIR=<scratch>
// tools/venv/bin/python <scratch> <file> 0x8025D32C 0xA0
// (score_gap.py scores unregistered gap addresses; the normal sweep reports
// no-boundary here).
// RESIDUAL: exactly 2 words — the then-arm stores are swapped: got
// (stw-A, stw-B), want (stw-B, stw-A). Everything else byte-exact: frame
// (stwu -0x18 + stmw r29), r30=WORD_A live across calls, r29 page-base,
// spin do{}while(C72C), MMIO *(u32*)0xCC003000=0x1000, D1A0 call,
// cond via r9, full then-arm (lis r9 / lwz r11 / lwz r10 / li r31 /
// addi / addi), else-arm (lwz r31 + r0-reuse stw), CCAC + CD6C(r30,r31)
// tail. Tried and neutral-or-worse: naive store swap in source (85% —
// the whole arm reschedules AND regs flip r9<->r10, i.e. scheduling is
// global over the block, bottom-up seeded); split decl/init orders (85%);
// precomputed nb/na + both store orders (95%/85%); memory barrier between
// stores (87.5% — clobbers allocation); -fno-schedule-insns{,2} (95% same
// wall). The store tie-break follows program order and no reordering that
// flips it preserves the head. Next idea (untried): route the two store
// VALUES through different temps (e.g. store B via r11-pinned temp computed
// in else-position) so heights differ.
// 2026-10-20 (re-measured, same wall): descending source order with both
// values precomputed into locals 85%; pinning the SECOND base to r9 so both
// stores use pinned bases 60%/57% (the tail re-materialises `lis r9` and the
// branch displacement self-references). The draft as it stands is the
// optimum: 2 words, store-pair order only.
// 2026-10-11 (~15 more variants, best still 95%): the pin ITSELF
// perturbs scheduling (pinned tb renumbers webs -> different cascade), so
// unpinned (B,A)-stores gives right store ORDER with rotated regs (V19/V29:
// orders exact, B-tmp r9/A-base r10/A-tmp r11 vs want r11/r9/r10). Pinning
// both temps (V30-V34) fixes regs but re-seeds the cascade (90%: lis/lwz
// + addi/stw swaps). V11 (one pin) and V11+ta-pin (V34) both 95% same wall.
// CASCADE MAP: storing A-then-B completes the B address arithmetic first and
// then the A arithmetic before either store, while storing B-then-A interleaves
// each address computation immediately ahead of its own store, plus a head
// register flip. The lis-A-first cascade would fix the
// addi swap too (earlier lwz-A -> earlier addi-A), but no program order
// produces it with (B,A) stores — global bottom-up seeding confirmed
// (V11-vs-V12 diff is ONLY store order yet the whole arm reschedules).
// STRUCTURE LESSONS (all load-bearing, verified by ablation):
// - r29 = literal page: `register s32 *pB __asm__("r29") = (s32 *)0x803B0000`
//   gives the bare `lis r29` (a symbolic (lbl+K) ALWAYS costs an extra addi
//   word — V3/V4 proved it). Uses via NEGATIVE index `pB[-0xCBE]` so the
//   folded disp is -0x32F8 in one lwz (positive 0x3342 index makes the
//   compiler materialize 0xCD08 through r29 itself, clobbering the base).
// - WORD_A/C via a DIFFERENT base symbol (lbl_803ACDA0-0x9C/-0x94) than the
//   condition (lbl_803ACCC0+0x48): same-symbol lets the compiler keep an
//   r10 = base+0x48 anchor (V6) instead of fresh r9 lis's (the want
//   re-lis's r9 in-arm even though r9 already holds the page — separate CSE
//   classes confirmed).
// - Split temp loads (ta, tb) + tb pinned r11: forces the scheduler's
//   load-interleave (lis-A / lwz-B / lwz-A / li) and the r11/r10 cascade.
// - Source arm order is A-then-B (A-inc statement first): program (B,A)
//   scores 85% with flipped regs; the scheduler completes B first for
//   latency (r29 ready) giving want's (B-op, A-op) execution order.
#include "types.h"

extern u8 lbl_803ACCC0[];
extern u8 lbl_803ACDA0[];

s32 fn_8025C72C(void);
void fn_8025D1A0(void);
void fn_8025CCAC(void);
void fn_8025CD6C(s32, s32);

void fn_8025D32C(void) {
    s32 a = *(s32 *)(lbl_803ACCC0 + 0x44);
    register s32 *pB __asm__("r29") = (s32 *)0x803B0000;
    s32 x;

    do {
    } while (fn_8025C72C() == 0);
    *(volatile u32 *)0xCC003000 = 0x1000;
    fn_8025D1A0();
    if (*(s32 *)(lbl_803ACCC0 + 0x48) != 0) {
        s32 ta = *(s32 *)(lbl_803ACDA0 - 0x9C);
        register s32 tb __asm__("r11") = pB[-0xCBE];
        x = 0x400;
        *(s32 *)(lbl_803ACDA0 - 0x9C) = ta + 0x400;
        pB[-0xCBE] = tb - 1;
    } else {
        x = *(s32 *)(lbl_803ACDA0 - 0x94);
        *(s32 *)(lbl_803ACDA0 - 0x94) = 0;
    }
    fn_8025CCAC();
    fn_8025CD6C(a, x);
}
