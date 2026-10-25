// WIP DRAFT (non-matching) — hand reconstruction from the retail disassembly.
// family=m2c range=0x800A3778-0x800A3968 size=496B
//
// PARKED 2026-10-02 (agent sweep of non-parked drafts — this file was picked
// because it lacked any "park" marker, but it is already deeply worked).
// Re-verified at NEAR 61.3% / 7 diffs / 496B, unchanged from the analysis
// below, which is exhaustive and still accurate. I deliberately did NOT
// re-grind it: the "ALREADY EXHAUSTED" list already covers all 15 project
// flags (byte-identical), 6 scratch register-pin combinations, the lis-anchor
// trick, and every `bit2`/`bit`/RMW staging position. The 7 residual words
// are ALL pure `local_alloc` scratch colouring plus two order transpositions
// in `reorder_basic_block` — a post-front-end wall. The two untried leads in
// the "NEXT LEADS" section (a `cc1 -dr` post-reload RTL dump, and shifting
// the first-walk loop's live-web count) are the honest next steps; neither is
// a statement-placement fix, so more C-level permutation is wasted effort.
// Treat this as parked unless you intend to attack post-reload allocation.
//
// STATUS: NEAR 61.3% (authority `test_wip_drafts.py --addr 0x800A3778`),
//   7 of 124 instruction words differ (LCS metric 94.35%). Baseline was 4.03%.
//   Object is EXACTLY 496B = `symbols.txt size:0x1F0`; only `.text` in the
//   object (no `.rodata`, so no doc-14 promote caveat). Frame, save area and
//   the whole callee-saved register MAP are already correct:
//     stwu -0x40 / stmw r23,0x1c / stw r0,0x44 ; 9 saved GPRs r23..r31
//     r23=cb  r24=arg2  r25=base  r26=clr  r27=bit  r28=bit2  r29=it
//     r30=self  r31=n2   (+ r8 = &self->f1C in a scratch)
//   Inline asm: 0 emitted instructions (4 `register ... __asm__("rN")` attribute
//   declarations + 4 zero-code `__asm__ volatile("")` barriers). 0 `__asm__`
//   count toward the section 4g 30% budget is violated; there is no
//   instruction transcription of any kind.
//
// WHAT IT DOES (fully recovered): a "visit every sub-object" callback driver.
//   1. `it` (a 12-byte stack object) is initialised: `it->n = NULL`,
//      `it->def = lbl_80297BF0`.
//   2. `m = self->f1C`; `bit = 1`; while (m & 1) bit <<= 1  -> first free bit.
//   3. `it->n = &self->n`; `base = &self->n`; `self->f1C |= bit`.
//   4. `bit2 = bit`; `sub = base->c`; `if (sub->f4 == -1) sub = NULL`;
//      `it->n = sub`; `cur = sub ? sub->f4 : NULL`.
//   5. First walk: for each `cur`, `cur->f20 &= ~bit`, then advance
//      `it->n = it->n->c` (with the -1 -> NULL sentinel normalisation) and
//      `cur = <that>`.
//   6. Main loop: `it->n = base`; `self->f20 &= ~bit`; advance once to `n2`;
//      if `n2`: inner loop — `tmp = n2`, advance `it->n` once more to `n2`;
//      if `!(tmp->f20 & bit2) { tmp->f20 |= bit; cb(tmp, arg2);
//      if (self->f20 & bit2) goto loop_16; }` until `n2 == 0`.
//      Outer `while (self->f20 & bit2)`.
//   7. `it->def = lbl_80297BF0`; `self->f1C &= ~bit`.
//
// LAYOUTS (all three file-local; the corpus-merged Unk_* classes are wrong
// here, so M6.89d applies — do NOT edit the shared header):
//   Nd  0x24: f0 f4 f8  c=+0xC  p=+0x10  def=+0x14  +0x18  mark=+0x20
//   Cs  0x18: f0 f4 f8  c=+0xC  p=+0x10  def=+0x14      (a Cs* == an Nd* pair)
//   Self     : f0, embedded Cs n at +4, u32 f1C=+0x1C, u32 f20=+0x20
//   It  0x0C : f0, Cs *n = +4, void *def = +8   (retail touches only +4 and +8)
//   Confirmed against promoted sibling src/fn_800A3680.c (the only caller):
//   it passes `&self->n` and the same +0xC/+0x10 link pair, so `Self.n` is the
//   list head and `Cs.c` is the successor link with an -1 sentinel at +0x4.
//
// WHAT IS LOAD-BEARING (each was measured; do not "simplify" these away):
//   * 4 hard register-var pins: it->r29, base->r25, pm->r8. Without them the
//     pool assigns 10 callee-saved regs and `stmw r22,0x18` + frame 0x40 ->
//     every colour in the function shifts by one (this alone was ~40 points).
//   * `pm = &self->f1C` as a POINTER and `*pm` at both the `|=` and the `&=`.
//     Inlining `self->f1C` materialises the address instead and adds an
//     11th saved register.
//   * Storing the two initialisers through `itp` BEFORE `it = itp` (so `itp`
//     stays a live second name). That is what produces retail's
//     `addi r11,r1,8` + `mr r29,r11` copy instead of `addi r29,r1,8`
//     (x1: 43.9% -> the `mr r29,r11` appeared; worth ~20 points).
//   * The first walk's iterator MUST be typed `It *p2` and read through
//     `pn = p2->n; sub = pn->c;`. Declaring `p2` as `Cs *` and writing
//     `p2->c` compiles to a single `lwz r9,0xc(r11)` and the whole function
//     sits at 43.9% with a 4-word-short object. Naming the intermediate
//     `pn` restores retail's two-load `lwz r9,4(r10)` / `lwz r11,0xc(r9)`
//     (g1: 43.90% -> 83.06%, and the object becomes size-exact).
//   * The first-walk preheader needs its OWN loop-local `c2 = clr` and
//     `p2 = it`; that is what materialises retail's `mr r8,r26` / `mr r10,r29`
//     preheader copies (n2 on the old base: 43.90% -> 48 B, later kept).
//   * Site 3 (the outer loop's advance) MUST use the two-name + barrier form
//     and site 4 (the inner loop's advance) the plain single-name form. That
//     combination alone is worth 10 words (sCA: 83.06% -> 91.94% at 496B);
//     all four other combinations of the two sites were measured (A/A 59.8%,
//     A/B 61.8%, A/C 62.9%, B/A 65.0%, B/C 71.8%, C/B 72.6%, C/C 72.6%).
//   * `m0 = *pm;` immediately before `*pm = m0 | bit;` (a separate named
//     local, NOT hoisted to the top of the function) — that is what puts
//     retail's `lwz r0,0(r8)` before the `addi r11,r30,4` and the `mr r28,r27`
//     between the `or` and the `stw` (o6: 91.94% -> 94.35%).
//   * `it->n = &self->n; base = &self->n;` written as TWO statements with the
//     store FIRST (q2 form) is load-bearing for the `addi`+`mr r25` pair.
//
// THE 7 REMAINING DIFFS (all read off `tools/want_got.py 0x800A3778`):
//   (a) ONE order transposition: want `...stw r9,8(r11); li r27,1; andi. r0,r10,1`
//       got  `...li r27,1; stw r9,8(r11); andi. r0,r10,1`. The `li r27,1` has
//       3 users (slwi, nor, mr r28) and `reorder_basic_block` sorts it ahead of
//       the 1-user `stw`; nothing in C reaches retail's slot. 7 statement
//       positions and 7 declaration-order permutations were measured: all
//       byte-identical or worse (best alternative 87.90%).
//   (b) FIVE words of scratch naming in the `|= bit` block: want uses r0
//       (`lwz r0,0(r8)` / `addi r11,r30,4` / `stw r11,4(r29)` / `or r0,r0,r27`
//       / `stw r0,0(r8)`), got uses r9 for the RMW and r0 for the address.
//       Same instruction sequence, same order, different scratch colours.
//   (c) The first-walk loop: want `mr r8,r26` + `mr r10,r29` (clr copy -> r8,
//       it copy -> r10) and the link kept in r11; got uses r10/r11 and r9.
//       `register Cs *pn __asm__("r9"/"r11")`, `register It *p2 __asm__("r10")`
//       and `register s32 c2 __asm__("r8")` were each measured: the pin is
//       either silently dropped (byte-identical) or costs one extra diff.
//   (d) Site 3: want `or. r31,r9,r9` (a copy into r31) vs got `mr. r31,r0`.
//   (e) The inner loop: want `mr r10,r31` / `lwz r0,0x20(r10)` / `and. r11,r0,r28`
//       vs got `mr r11,r31` / `lwz r0,28(r11)` / `and. r10,r0,r28`.
//
// ALREADY EXHAUSTED (do not re-grind):
//   * All 15 project flags are BYTE-IDENTICAL on the final body:
//     -fno-schedule-insns, -fno-schedule-insns2, -fno-sched-spec,
//     -fno-sched-interblock, -fno-gcse, -fno-thread-jumps,
//     -fno-expensive-optimizations, -fno-rerun-cse-after-loop,
//     -fno-strength-reduce, -fno-branch-count-reg, -fno-sched-round, -Os, -O3,
//     -mcpu=603. (Re-measured on the FIXED body, per the section 6bx rule —
//     this body never had a `// FLAG:` line.)
//   * Scratch register-var pins on c2/p2/pn/tmp (6 combinations) — all
//     dropped or -1 word.
//   * An opaque `lis %0,%1@ha` anchor in r9 or r11 to free the other anchor
//     register (1 emitted insn): 492B, -4 words. The `"s"` constraint needs
//     `extern char lbl_80297BF0[]` (already present) but the C-side
//     `pg + 0x7BF0` does not fold the way the plain reference does.
//   * `bit2 = bit` at 4 different source positions (79.0% / 72.6% / 73.4% /
//     91.9% unchanged) and a `btmp` staging temp (byte-identical).
//   * Hoisting the RMW load to the top of the function (`m0 = *pm;` there)
//     breaks the length (492B, index alignment off by one) — the load must
//     stay adjacent to the `|=`.
//   * `*pm |= bit` compound form, `*pm = *pm | bit` after the base setup,
//     `bit2` before the store, a `dv` staging local for `lbl_80297BF0`, and a
//     `bit`-pinned-to-r27 declaration: all byte-identical or worse.
//   * `nxt` + `n2 = nxt` two-name at site 3 (500B, 72.6%) and a `"+r"(nxt)`
//     barrier on it (500B, 65.3%).
//   * Site 1/2 barrier removal (92.2% -> 22.8% / 24.6%): the four zero-code
//     barriers are load-bearing, not stale.
//
// NEXT LEADS (untried, in the order I would try them):
//   1. `cc1 -dr` on this body. The two remaining order transpositions and all
//      the scratch colours are post-reload (`reorder_basic_block` +
//      `local_alloc`); if the post-reload RTL is already in want's order the
//      honest conclusion is a post-front-end wall, same class as section 6bz /
//      6ek-3 / 6fz. Dump: `build/tools/wibo build/compilers/ProDG/3.9.3/cc1.exe
//      -O2 -G0 -mcpu=750 -fno-common -dr body.c -o body.s` with the typedefs
//      inlined and `#include` dropped (cc1 does not preprocess).
//   2. (a) specifically: the `li r27,1` sorts early because its pseudo has 3
//      users. Per the section 6bg-8 "give it 2 users / take it away" lever,
//      try making the `clr = ~bit` and `bit2 = bit` derive from a SECOND copy
//      of `bit` taken after the shift loop, so the `li` has 1 user and sorts
//      last. (Not measured — the `mr r28,r27` / `nor r26,r27,r27` pair would
//      then read from the copy instead of r27, so check the +2 cost first.)
//   3. (b)+(c)+(d)+(e) are all one thing: which scratch registers
//      `local_alloc` hands out inside a block that has a live `reload` anchor.
//      A `-ffixed-rN`-style approach does not exist in ProDG cc1, and every
//      hard pin tried is dropped. An alternative is to change the number of
//      live webs in the block (e.g. give the inner loop its own `clr` copy, as
//      the first walk already has) so the pool order shifts by one the same
//      way the `p2`/`c2` locals shifted the first walk's colours.
//   4. A promoted twin search: no `twin_scan` / `near_twin_scan` hit exists
//      (different size and no shared callee), and `rg "<<= 1" src/*.c` only
//      turns up unrelated promoted files. `fn_800A3680` is the only promoted
//      neighbour and supplies the `Self`/`Cs` layout confirmation, nothing more.
//
// BRANCH-RELOC AUDIT (section 6bw method) — DONE on this exact body:
//   21 want intra-function branches vs 21 got R_PPC_REL14/REL24 branch
//   relocations, 0 missing, 0 extra. There is NO hidden control-flow or
//   guard-extent difference behind the 7 residual words (the section 6bq /
//   6ca masked-branch hazard is cleared). The 4 non-branch relocations are
//   2 x R_PPC_ADDR16_HA + 2 x R_PPC_ADDR16_LO, both against the real
//   `lbl_80297BF0`; want's `lis r9,-0x7fd7` + `addi r9,r9,0x7bf0` decodes by
//   hand to 0x80297BF0, so the hazard-277 masked-wrong-label case cannot
//   apply. Object carries only `.text` (0x1F0) + `.rela.text`.
//   Re-run this audit (and re-measure with each draft's own `// FLAG:` line —
//   there is none here) before any promote attempt.
extern char lbl_80297BF0[];

typedef struct Nd {
    s32 f0;
    s32 f4;
    s32 f8;
    struct Nd *c;
    struct Nd *p;
    void *def;
    s32 f18;
    u32 f20;
} Nd;

typedef struct Cs {
    s32 f0;
    s32 f4;
    s32 f8;
    struct Cs *c;
    struct Cs *p;
    void *def;
} Cs;

typedef struct Self {
    s32 f0;
    Cs n;
    u32 f1C;
    u32 f20;
} Self;

typedef struct It {
    s32 pad0;
    Cs *n;
    void *def;
} It;

typedef s32 (*cb_t)(void *, s32);

void fn_800A3778(Self *self, cb_t cb, s32 arg2) {
    It itbuf;
    register It *it __asm__("r29");
    It *itp;
    register Cs *base __asm__("r25");
    Cs *sub;
    Nd *cur;
    Nd *n2;
    Nd *tmp;
    register u32 *pm __asm__("r8");
    u32 m;
    u32 m0;
    u32 mm;
    u32 bit;
    u32 bit2;
    u32 clr;
    s32 v;
    s32 b;

    itp = &itbuf;
    itp->def = lbl_80297BF0;
    itp->n = 0;
    it = itp;
    pm = &self->f1C;
    m = *pm;
    bit = 1;
    if (m & 1) {
        mm = m;
        do {
            bit <<= 1;
        } while (mm & bit);
    }
    m0 = *pm;
    it->n = &self->n;
    base = &self->n;
    *pm = m0 | bit;
    bit2 = bit;
    sub = base->c;
    if (sub->f4 == -1) {
        sub = 0;
    }
    it->n = sub;
    {
        Nd *cv;
        if (sub == 0) {
            __asm__ volatile("");
            cv = 0;
        } else {
            cv = (Nd *)sub->f4;
        }
        cur = cv;
    }
    clr = ~bit;
    if (cur != 0) {
        s32 c2 = clr;
        It *p2 = it;
        Cs *pn;
        do {
            pn = p2->n;
            cur->f20 = cur->f20 & c2;
            sub = pn->c;
            if (sub->f4 == -1) {
                sub = 0;
            }
            it->n = sub;
            if (sub == 0) {
                __asm__ volatile("");
                cur = 0;
            } else {
                cur = (Nd *)sub->f4;
            }
        } while (cur != 0);
    }
    do {
loop_16:
        it->n = base;
        sub = base->c;
        self->f20 = self->f20 & clr;
        if (sub->f4 == -1) {
            sub = 0;
        }
        it->n = sub;
        {
            Nd *cv;
            if (sub == 0) {
                __asm__ volatile("");
                cv = 0;
            } else {
                cv = (Nd *)sub->f4;
            }
            n2 = cv;
        }
        if (n2 != 0) {
            do {
loop_22:
                tmp = n2;
                sub = it->n->c;
                if (sub->f4 == -1) {
                    sub = 0;
                }
                it->n = sub;
                if (sub == 0) {
                    n2 = 0;
                } else {
                    n2 = (Nd *)sub->f4;
                }
                v = tmp->f20;
                b = 1;
                if (!(v & bit2)) {
                    b = 0;
                }
                if (!b) {
                    tmp->f20 = v | bit;
                    cb(tmp, arg2);
                    if (self->f20 & bit2) {
                        goto loop_16;
                    }
                }
            } while (n2 != 0);
        }
    } while (self->f20 & bit2);
    it->def = lbl_80297BF0;
    *pm = *pm & clr;
}
// 2026-10-22: 66.9% (was 61.3%): `itp->def` before `itp->n`; `pn = p2->n` above the f20 clear; `sub = base->c` above the self clear.
