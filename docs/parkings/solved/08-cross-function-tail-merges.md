# Issue 08 — Cross-function tail merges (branches into the next function)

**Status: SOLVED — class empty (surveyed 2026-08-23, re-verified 2026-10-14; moved to solved/).** A whole-.text scan
(last instruction is bc/b, target ≥ next symbol start) over all symbols.txt
boundaries found only: (a) 4-byte `b` thunks with long-range ABSOLUTE branches
(AA bit — jump-table dispatch, not merges) in the 0x8025D000/0x80262xxx zones,
and (b) fn_8025A610 branching into the known Neversoft jumptable stall region
(0x8025AD64, inside the skip_cfa_ranges overlap). Zero genuine
conditional-branch-into-next-prologue cases remain among current boundaries.
The class either evaporated when earlier stubs were resolved or exists only
inside the un-split stall range. If a future NEAR crop shows a masked branch
diff whose want target is the NEXT function's body, re-run this scan first.

**Re-verification 2026-10-14** (over current boundaries, stricter rule: a
*conditional* tail branch landing strictly *inside* the next real function,
tiny fragment symbols excluded): every remaining instance lives in an
already-matched function — the SDK `FooAsync`-into-`Foo`-body wrapper idiom
(AR/AX/CARD/DVD/EXI/GX, all matched) and ordinary shared-tail jumps in matched
game code (sampled 14, 13 matched). The single wip instance (`fn_800142FC`)
is parked on doc 75/76, not here, and no draft cites this doc as its park
reason (one draft explicitly excludes it). Nothing parked is blocked by this
class.

---

# ORIGINAL ANALYSIS (historical)

**Status:** PARKED (as of M4.9x; park set is a moving target — re-verify before trusting) (several functions; part of the 77 "stub" drafts)

## The problem

Some functions end with a conditional branch that jumps **into the next
function's body** instead of into their own code:

```
fn_X:
    ...
    beq  fn_Y+4        # branch target is INSIDE the next function
    blr
fn_Y:
    stwu r1, ...
    ...
```

GCC 2.95.2 sometimes merges identical tail blocks of two adjacent functions
(a classic cross-function optimization when the functions were compiled in
the same translation unit and the linker/compiler merged their epilogues).
This means:

- The "function boundary" in the DOL is not a clean `blr` — fn_X's code
  logically extends past where the splitter would cut it.
- A standalone C file for fn_X cannot reproduce the branch, because in a
  standalone compilation fn_Y is a separate symbol and its body isn't
  merged.
- The splitter/classifier (which truncates at the first `blr`) cuts fn_X's
  disasm window too early, so even the *pattern* is misread.

## Why it's parked

- Reproducing requires compiling fn_X and fn_Y **in the same C file** so GCC
  can re-merge the tails — but then the split entries (one per function) and
  the linker order break, and GCC 2.95.2's tail-merging behavior must be
  triggered by exactly the right source shape.
- It's an intra-TU optimization artifact: the original functions lived in one
  source file (or were emitted by the same compiler pass).

## What was tried

- Standalone per-function files (standard workflow) — cannot reproduce.
- Drafts kept as `stub` with the disassembly documented.

## Research directions for an external AI

1. Find the function *pairs* that share merged tails. If both halves belong
   to the same original source file, writing them as **two functions in one
   C file** (with one split entry covering both, or a group object) may let
   GCC 2.95.2 reproduce the merge. dtk supports multiple symbols per object
   via a single split range.
2. GCC 2.95.2's `-fmerge-...`/`crossjumping` (tree-ssa-era flag; in 2.95 it's
   the `crossjumping` pass in `cfgrtl.c`) decides tail merging — check which
   option (`-fcrossjumping`?) was on by default and what source shape
   triggers it.
3. If the merged tail is only reachable from fn_X's conditional, an
   alternative is to restructure fn_X's C so its epilogue duplicates the
   bytes instead of branching (accepting that the *branch* is the diff).

## Where to look

- WIP `stub` drafts (77 total, includes cross-function branch bodies).
- History: `AGENTS.md` §4f/§4g, `docs/gamecube-decomp-plan.md` §5.13.
