# doc 73 — HI16 anchor colours: plain C gives `{r9, r11}`, asm anchors give the whole set

**Status: SOLVED — every member is byte-exact and promoted.** Re-verified
2026-10-23 by compiling each promoted source with its own flags:
`fn_800BD674` (252B), `fn_800B6404` (364B), `fn_80034608` (124B) and
`fn_800E0608` (116B) all score **EXACT 100.0%**, `fn_801430FC` (348B) is
promoted too. The build's `build/G2TE52/src/fn_800BD674.o` contains retail's
`lis r9` / `lis r10` / `lis r11` triple, so the original "a `lis` into r10 is
never producible" headline was too strong: it is not producible from *plain C*
with three live symbol anchors, and it is producible as soon as the anchors are
emitted as one-instruction asm blocks.

## The plain-C limit

A block that reads several constants through different rodata symbols gets one
page anchor per symbol. In plain C the HI16 symbol-reload register set on this
target is **`{r9, r11}`** — three simultaneously-live anchors come out
`r9, r11, r9, r11` or `r9, r11, r11, r9`, never a third distinct colour.
Six probe bodies (including four simultaneously-live constants under heavy
float pressure) and the full flag sweep confirm that; the reload pass ignores
`register` pins, so a pinned symbol-address variable does not move it either.

Two plain-C levers do work, and they are worth trying before any asm:

* **remove a reload instead of buying a colour** — a value-identical C literal
  makes ngccc fold that `lfs` into an existing page with a displacement
  (`fn_80034608`: middle constant `0.0f` instead of `extern f32 lbl_...`,
  87.1% → 100%). Watch the private `.rodata` word this creates: doc 14 /
  `fix_fp_pool.py`.
* **order of first mention decides which symbol gets which colour** — the
  second symbol mentioned in source takes `r9`, the first takes `r11`
  (`fn_800E0608`), even when the emitted loads run the other way.

## The asm-anchor escape (fn_800BD674)

Retail interleaves four anchors and three loads: `lis lis lfs lis lfs lfs lis lfs`.
Each anchor is one `lis %0,%1@ha` asm block with its **own pinned register**:

```c
extern char lbl_80298E3C[];   /* the "s" constraint needs an array symbol */
register u32 var_r9 __asm__("r9");
register u32 pgB    __asm__("r10");
register u32 pgC    __asm__("r11");

__asm__ volatile("lis %0,%1@ha" : "=r"(var_r9) : "s"(lbl_80298E3C));
__asm__ volatile("lis %0,%1@ha" : "=r"(pgB)    : "s"(lbl_80298E40));
c_f12 = *(f32 *)((char *)pgB - 0x71C0);
__asm__ volatile("lis %0,%1@ha" : "=r"(pgC)    : "s"(lbl_80298E48));
r_f13 = *(f32 *)((char *)var_r9 - 0x71C4);
r_f0  = *(f32 *)((char *)pgC - 0x71B8);
__asm__ volatile("lis %0,%1@ha" : "=r"(var_r9) : "s"(lbl_80298E44));
c_f11 = *(f32 *)((char *)var_r9 - 0x71BC);
```

What each part buys, measured on the exemplar:

* **Pinning every anchor is the load-bearing part.** One asm anchor alone is
  85.7%: the next symbol's anchor glues onto the previous load and the third
  colour collapses. With all three variables pinned, each `lis` is a write to
  its own hard register and cannot be coalesced away.
* **`volatile` on the asm** — with non-volatile asm, sched2 hoists `lfs f13`
  above `lfs f12` and sinks `lis r11` two slots (90.5%).
* **`-fno-schedule-insns`** for the surrounding block.
* **The r10 pin is the third colour** (96.8% without it).
* **Two `volatile double` dummies** for the FPR frame (issue 01); one or zero
  gives 84.1%.
* The register holds a **page**, so the C side adds a signed page-relative
  delta and the low half folds back into the load displacement; the `@ha`
  relocation still names the real symbol, so the link is unaffected.

`fn_801430FC` is the same route with a single 3-`lis` asm window (8 emitted
instructions / 87) because two of its constants are `0x8xxxxxxx` addresses,
where a C literal is not an option.

## The lone-anchor case (fn_8022BA54) — measured, and left parked

`fn_8022BA54` (192B) has the same unreachable colour but only ONE anchor:
retail colours the `lbl_802FFE98` page `r10` while every other anchor in the
function is `r9`, and `r9` is already held by the `pv9` reload whose lifetime
spans the stores. Two diffs, both from that one anchor.

The variable pin does not work here for the reason recorded above: the anchor is
not a value, it is the base of a memory reference (`lwz r3, sym@l(base)`), so
`register void *pg __asm__("r10")` forces the address through a register and
drops the folding (79%). What does reproduce the bytes is the page and the load
written as two asm blocks placed where retail has them — `lis 10, sym@ha`
ahead of the previous statement's load, `lwz %0, sym@l(10)` at the use. The gap
matters: one combined two-instruction block reproduces neither end (91.7%) and,
being volatile, drags the neighbouring load off `r0`.

That is a byte match, not a decompilation: the two words are hand-written
instructions, so the draft stays parked at 95.83% rather than being promoted.
The usable content of the measurement is negative and worth keeping: for a lone
page anchor the C-side levers are exhausted (pin 79%, best mention-order
93.75%), so do not re-run the anchor ladder on a one-anchor function expecting a
source fix. The promoted exemplars above stand on their own disclosure.

## Transfer boundary

The escape needs a *set* of anchors that each get their own home. A lone
`lis` transposition against an `&local` argument is still an ordinary
scheduler tie: on `fn_8018CC18` (292B, 97.26%, want `[lis r11][lwz][addi r4]`
vs got `[addi r4][lwz][lis r11]`) six variants were measured (a single pinned
`lis @ha` at three positions, plus three statement orders) and all regress to
89.0–93.2%. Do not re-run the anchor ladder on a
one-symbol prologue; it is the doc-15 class.
