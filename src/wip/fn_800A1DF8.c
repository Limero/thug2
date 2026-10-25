// WIP DRAFT (non-matching) — hand reconstruction from the retail disassembly.
// 2026-10-08: 74.19% -> **76.6%** (official) from one pin: `u32 m0` ->
// `register u32 m0 __asm__("r0")` (sweep predicted 76.61).
// family=m2c range=0x800A1DF8-0x800A1FE8 size=496B
//
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-03.  NEAR 74.19% / 32 of 124 words / SIZE-EXACT
// 496B, up from the DIFF 8.9% baseline (the m2c husk was 460-476 B, i.e. the
// wrong length, so its 8.9% was pure index coincidence — per the batch brief
// the honest metric here is instruction-for-instruction, and the body is now
// instruction-for-instruction IDENTICAL to want except for register colours).
// Reproduce: LEAF_TMPDIR=<scratch> tools/venv/bin/python \
//   tools/test_wip_drafts.py --addr 0x800A1DF8      -> NEAR 74.2%
//   tools/want_got.py 0x800A1DF8                   -> 32 `>>>` lines
//
// *** THIS IS THE CALLBACK-FREE SIBLING OF 0x800A3778. ***
// Both are 496 B and share the ENTIRE block skeleton (12-byte stack iterator
// initialised to {…, NULL, lbl_80297BF0}; "first free bit" shift loop over
// self->f1C; the `base->c` / `-1` sentinel / `->f4` advance idiom at FOUR
// sites; the first walk clearing mark 0x20; the `do{loop_16:}while(mark&bit)`
// outer loop; `it->def = lbl` + `*pm &= clr` epilogue).  0x800A3778 just
// calls `cb(tmp, arg2)` where this one inlines
// `if (arg1) tmp->f114 |= 1; else tmp->f114 &= ~1;` (hence no LR spill, no
// `mtlr/blrl`, frame 0x20 with only r30/r31 saved, and `self` staying in r3).
// Its PARKED note (src/wip/fn_800A3778.c) is the oracle for the layouts and for
// every idiom below; re-read it before grinding this further.
//
// WHAT IS LOAD-BEARING (each measured — do not "simplify" any of these away):
//   * The struct layouts.  `Nd` needs NINE 4-byte head fields
//     (f0 f4 f8 c p def f18 f1C f20) — the m2c/fn_800A3778 8-field version puts
//     `mark` at 0x1C and the flag at 0x110, i.e. 4 bytes short at BOTH offsets.
//     `Cs` is the 6-field 0x18 prefix, `Self {s32; Cs n; u32 f1C; u32 f20;}`
//     (embedded `Cs n` at +4 puts f1C at 0x1C), `It {s32 pad; Cs *n; void
//     *def;}` (12 B at sp+8 — the pad is what forces frame 0x20).
//   * The FOUR zero-code `__asm__ volatile("")` barriers inside the
//     `if (sub == 0) { … }` arms of the advance idiom.  Remove them and gcc
//     folds the known-false CR into the branch: 9 words short (460 B vs 496 B),
//     one `li rX,0` + `b` per site becoming `li r0,0` + `beq`.  Worth ~14 pts.
//   * The `{ Nd *cv; if (sub==0) {barrier; cv=0;} else {cv=(Nd*)sub->f4;}
//     cur = cv; }` BLOCK form at sites 1 and 3.  Flattening it to
//     `cur = sub ? (Nd *)sub->f4 : 0;` (or folding it into `sub`) is a
//     DISASTER: 74.2% -> 21.0%, because the block's extra name is what makes
//     gcc emit want's `lwz r9,4(r9)` / `or. r11,r9,r9` pair instead of a
//     direct load into `cur`.
//   * The advance idiom is written as THREE steps (`sub = X->c; if
//     (sub->f4 == -1) sub = 0; it->n = sub;` then the `cv` block), NOT as one
//     ternary.  The `it->n = sub` store must sit BETWEEN the `cmpwi sub,0`
//     pair and the `cv` read.
//   * `register u32 mm __asm__`-free `"+r"(mm)` barrier after `mm = m` in the
//     shift loop — without it gcc coalesces `mm` back onto `m` and want's
//     `mr r0, r10` disappears (1 word short).
//   * Seven hard register-var pins — `it`->r7, `base`->r4, `pm`->r6, `m`->r10,
//     `bit`->r5, `bit2`->r8, `clr`->r12 — plus `cur`->r11 and the two
//     block-local `c2`->r6 / `p2`->r10 / `p3`->r6.  These are what produce the
//     five COALESCED COPIES want has and gcc otherwise deletes: `mr r7,r11`
//     (it=itp), `mr r31,r4` (arg1 evicted off r4 by base), `mr r4,r11`
//     (base after `it->n = &self->n`), `mr r10,r7` (p2=it) and `mr r6,r7`
//     (p3=it).  Adding the pins took the object 476 -> 496 B in ONE step and
//     62.1 -> 74.2%.
//   * Merging m2c's `n2` into `cur` (one loop variable for both the first walk
//     and the outer walk) is worth +2.4 pts: want uses ONE colour (r11) for
//     both, and the extra name pushes the allocator a whole register out.
//   * `pm = &self->f1C` as a POINTER, dereferenced at the `|=`, the `-=`-free
//     `&=` and the final `&=`.  Inlining `self->f1C` materialises the address
//     and adds a callee-saved register.
//
// THE 32 REMAINING WORD DIFFS (`tools/want_got.py 0x800A1DF8`), ALL PURE
// COLOUR/SCHED, NO SEMANTIC DIFFERENCE LEFT:
//   (a) 14 words: at the site-1 (0x800A1E60) and site-3 (0x800A1EF4) advance,
//       want holds `sub` in r9 (`lwz r9,0xc(r11)` / `li r9,0` / `stw r9,4(r7)`)
//       and got holds it in r11, because `sub` COALESCES with the r11-pinned
//       `cur` (their live ranges do not overlap, so gcc may legally share the
//       register).  Note want ITSELF uses r11 for `sub` at site 4 (0x800A1F38)
//       and r9 at sites 1/2/3, so the value is a fresh dead temp per site.
//   (b) 3 words: prologue ORDER — the want build stores a word to offset 4 of
//       the iterator, derives the mask-pointer with a 0x1c displacement,
//       copies the iterator and the second argument into their homes, then
//       stores the second word at offset 8; this build places the
//       mask-pointer derivation after the two copies.  Moving the
//       mask-pointer assignment to the top of the body
//       does NOT move it (measured).
//   (c) 4 words: the `|= bit` read-modify-write scratch — the want build uses
//       a single scratch pseudo for the offset-0 load, OR and store through
//       the mask pointer, while this build hands the load and the OR distinct
//       pseudos so the copy survives as a separate register.
//   (d) 2 words: outer-body order — want `lwz r0,0x20(r3)` BEFORE
//       `stw r4,4(r7)`; got the reverse.
//   (e) 2 words: site 1 — want `or. r11,r9,r9` THEN `nor r12,r5,r5`; got the
//       `nor` first.
////   (f) 4 words: epilogue — the want build reloads the flag word at offset
//       0x1c, materialises the label address, ANDs the two, then stores the
//       label into the iterator at offset 8 and the masked word back at 0x1c;
//       this build emits the label store BEFORE the AND and uses different
//       registers for the read-modify-write.
//   (g) 1 word: site 3's null-test is `or. r11,r11,r11` (a no-op copy) in got.
//
// RULED OUT (measured, do NOT re-grind):
//   * `register Cs *sub __asm__("r9")` — the obvious fix for (a).  CATASTROPHIC:
//     r9 is also the HI16 anchor for `lbl_80297BF0`, and the hard pin makes
//     global-RA reshuffle everything — `self` moves to r31, `arg1` to r30,
//     `tmp` to r3, and the object comes out 16 B SHORT (20.97% with `cur`
//     unpinned, 25.81% pinned).  Same trap as fn_800A3778's dropped pins.
//   * Splitting `sub` into three per-site names (`sub1/sub2/sub3`) — 44 diffs
//     (74.2 -> 64.5).  The coalescing is not a name artefact.
//   * A staging local `mk = self->f20;` in the outer body to force want's
//     `lwz … stw … and … stw` order — it DOES fix (d) but injects a dead
//     `mr r9,r0` + `and. r10,r0,r8` pair into BOTH `self->f20 & bit2` tests.
//     Net 74.2 -> 64.5%.  Same for `mk = m0 & clr` in the epilogue (neutral).
//   * Pinning `cur` to r11 WITHOUT pinning c2/p2/p3: 62.1% (c2/p2/p3 pins are
//     what put r6/r10 on the preheader copies).
//   * Flattening / fusing the `cv` block (see LOAD-BEARING above).
//   * `m0 = *pm; it->def = lbl; *pm = m0 & clr;` vs
//     `m0 = *pm; mk = m0 & clr; it->def = lbl; *pm = mk;` — byte-identical.
//
// NEXT LEADS (in the order I would try them):
//   1. (a) is 14 of the 32 words, i.e. the only prize left.  It needs `sub` to
//      pick r9 WITHOUT a hard pin.  Per recipe 6ga ("a per-block temp split
//      shifts the WHOLE colour map by exactly one") the lever is to change the
//      NUMBER OF LIVE WEBS in the advance block rather than name `sub`
//      differently — e.g. give the site-1/site-3 `cv` its own `register
//      Nd *cv __asm__("r9")` while `sub` stays free, or split site 3's
//      `self->f20` read back into a named temp ONLY there (the global `mk`
//      attempt failed because it touched BOTH sites).  Untested.
//   2. (b)+(d)+(e)+(f) are `reorder_basic_block` / `sched2` placement, i.e.
//      post-front-end.  fn_800A3778's author reached the same conclusion on the
//      same skeleton: dump the post-reload RTL with
//      `cc1 -dr` and compare order before trying any more C statement moves.
//   3. Do NOT spend time on flags: fn_800A3778 measured all 15 project flags
//      byte-identical on this exact code shape.
//
// VERIFIED BEFORE PARKING: object `.text` = 496 B == `symbols.txt size:0x1F0`;
// object carries ONLY `.text` + `.rela.text` (no private `.rodata`, so no
// doc-14 promote caveat); ZERO emitted asm instructions — the `__asm__` uses
// are 10 `register … __asm__("rN")` pins + 4 zero-code `volatile("")`
// barriers + 1 zero-code `"+r"(mm)` barrier; and the branch skeleton is
// positionally aligned 1:1 with want across all 23 branch sites, so no
// hidden guard-extent difference hides behind the 32 colour diffs.
#include "types.h"

extern char lbl_80297BF0[];

typedef struct Nd {
    s32 f0;
    s32 f4;
    s32 f8;
    struct Nd *c;
    struct Nd *p;
    void *def;
    s32 f18;
    s32 f1C;
    u32 f20;
    char pad0x24[0xF0];
    u32 f114;
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

void fn_800A1DF8(Self *self, s32 arg1) {
    It itbuf;
    It *itp;
    register It *it __asm__("r7");
    Cs *sub;
    register Nd *cur __asm__("r11");
    Nd *tmp;
    register Cs *base __asm__("r4");
    register u32 *pm __asm__("r6");
    register u32 m __asm__("r10");
    register u32 m0 __asm__("r0");   /* 2026-10-08 pin-sweep +2.4 */
    u32 mm;
    register u32 bit __asm__("r5");
    register u32 bit2 __asm__("r8");
    register u32 clr __asm__("r12");
    s32 v;
    s32 b;

    pm = &self->f1C;
    itp = &itbuf;
    itp->n = 0;
    itp->def = lbl_80297BF0;
    it = itp;
    m = *pm;
    bit = 1;
    if (m & 1) {
        mm = m;
        __asm__ volatile("" : "+r"(mm));
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
        register u32 c2 __asm__("r6") = clr;
        register It *p2 __asm__("r10") = it;
        Cs *pn;
        do {
            cur->f20 = cur->f20 & c2;
            pn = p2->n;
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
        self->f20 = self->f20 & clr;
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
        if (cur != 0) {
            register It *p3 __asm__("r6") = it;
            do {
                tmp = cur;
                sub = p3->n->c;
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
                v = tmp->f20;
                b = 1;
                if (!(v & bit2)) {
                    b = 0;
                }
                if (!b) {
                    tmp->f20 = v | bit;
                    if (arg1) {
                        tmp->f114 |= 1;
                    } else {
                        tmp->f114 &= ~1;
                    }
                    if (self->f20 & bit2) {
                        goto loop_16;
                    }
                }
            } while (cur != 0);
        }
    } while (self->f20 & bit2);
    m0 = *pm;
    it->def = lbl_80297BF0;
    *pm = m0 & clr;
}