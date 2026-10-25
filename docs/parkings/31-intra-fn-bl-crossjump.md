# 31 — Intra-function duplicate-call crossjump (retail merged two `bl` sites; ngccc never merges calls)

**Status:** OPEN (discovered 2026-08-23, round)
**Affected exemplars:** `fn_80153844` (`ScriptLoadNetworkDrivers`, 176 B, parked ~39.5%)
**Related:** #08 cross-function-tail-merges (branches into the NEXT function — different
phenomenon), #15 call-arg-setup-scheduling (order of arg moves, not call-site count).

## Symptom

WANT contains exactly one call to fn_80137B64 that both control-flow paths reach: the zero path moves the global from r31 into r3 and stages zeros directly in argument registers r4 through r6 before jumping to the shared call, while the else path stages homes from saved registers with per-path copies and falls through, so the shared call plus epilogue serve both stagings. This is the retail compiler's call-level tail merge where two originally separate call sites with identical callee plus shared tail collapse into one call block, differing only in where argument values are staged.

## Why ngccc cannot reproduce it

Proved by a minimal synthetic test (two identical `f(a,b,c,d)` calls in an
if/else): **ngccc 3.9.3 crossjumping merges branches/epilogues but NEVER
merges the `bl` instructions themselves** — output is always 180 B with two
calls vs WANT's 0xB0 with one.

Both source shapes therefore fail, in complementary ways:

1. **Single-call-site C** (ternary-guarded args feeding one call): keeps one
   `bl` and the right size, but forces every argument web through a
   callee-saved home (GCC needs the values live across the merge point), so
   the zero path emits `li r29,0 / li r5,r29 / li r30,0...` + shared-tail
   copies instead of staging zeros directly in r4/r5/r6.
2. **Two-call-site C**: preserves path-local arg staging, but duplicates the
   `bl` (+size) — dead on arrival.

## What was tried (fn_80153844)

Decl-order permutations, init-at-declaration, register pins (`r29/r30/r31`),
early-return split, inverted condition, ternary-guarded driver calls in the
final args (explodes to 3 branches), empty-asm priority boosts, pointer-return
protos, sched flags (`-fno-schedule-insns`, `-insns2`, `-sched-spec`, alone
and paired), temp/var splits so arg webs cross no calls. Best shape reached:
single `bl`, correct size, perfect homes, zero path staging r4/r5/r6 direct —
remaining diffs are ONLY the zero path's leading `mr r3,r31` (ours shares it
in the tail) and the else-path copy order.

## Counter-evidence (2026-08-23) — "never merges bl" is SCOPED

fn_801340FC (EXACT this round) shows ngccc's crossjumping DOES merge duplicate
`bl` sites under some shapes: two error paths calling `fn_801323D4` with
DIFFERENT constant args (`addi r4,r28,-0x10D0` vs `addi r4,r27,-0x10B0`) but
identical `bl fn_801323D4; li r3,0; blr` tails were merged into ONE shared
`bl` by plain goto-C. An explicit `goto exit0;` label between the second call
site and the shared exit broke the merge (distinct block boundary stops it;
fall-through / shared-tail CFG shapes are what trigger the merge). The
synthetic if/else test above evidently produced per-path tails too different
for crossjumping to bite.

**New retry hint for fn_80153844:** write BOTH per-path call sites with
IDENTICAL post-call tails and let ngccc's own crossjumping perform the retail
merge — per-path arg staging survives because it precedes the merge point.
See AGENTS.md §6u-1.

## Retry hints

- A source idiom that makes GCC duplicate the arg0 copy per-path while
  sharing only `bl`+epilogue would crack it (no known construct).
- Any future compiler flag affecting crossjumping/call-merging (none found in
  ProDG 3.5–3.9.3) — retest this draft first.
- If another DOL function shows the same one-shared-bl-two-staging-paths
  shape, add it here before drafting from scratch.

## Members

| Address | Size | Best | Blocker |
|---|---|---|---|
| fn_80153844 | 0xB0 | 39.5% (17/43), structure otherwise exact | retail merged 2 call sites; ngccc never merges `bl` |
| fn_800ABCA8 | — | **SOLVED 2026-09-28 (EXACT, 96B)** — **removed from this table, it was never a crossjump case.** See the section below. |
| fn_80054388 | 0x98 | 42.5% (2026-09-07) | retail merged 2 `bl strstr` sites into ONE at +24 (both `bne` paths reach it); ngccc emits two bls (160B vs 152B) and the whole tail sits one word off. 3/4/5-arg × goto/ifelse/twin-gate swept: 5-arg varargs call best. Sister fn_8005529C (2 strstr sites, EXACT) proves retail only merges when tails are shareable — merge condition narrower than this doc recorded. Twin-gate identical-tail shape also refused to merge. |

## inverse member (2026-08-24): ngccc threads IDENTICAL dispatch
## sequences want keeps inline

fn_801C17F4 (52% park): three structurally identical vtable-dispatch call
sequences that WANT emits inline and separate get merged/threaded by ngccc at
every -O level and all five ProDG versions. This is doc-31's merge behavior
running the OPPOSITE direction of the original member (there retail merged,
ngccc didn't; here retail kept separate, ngccc merges). Same family root:
crossjumping decisions are not source-controllable in either direction —
when you see N identical call sequences disagreeing about merge state between
want and got, don't grind shapes; check whether making the sequences
textually distinct (per §6u-1 goto-boundary trick) breaks the merge.

## fn_800ABCA8 removed from this doc (2026-09-28): the rule it was filed under

The 2026-09-22 entry blamed ngccc for not merging two call sites. **ngccc never
had to merge anything** — the function is EXACT (58.3% → 100%) with ONE
textual call. The real lever, and a generalisable one for the guard +
varargs + shared-callee shape that recurs across the Script* wrapper zone:

> **When WANT's two arms converge on ONE shared call with the arg0 field load
> DUPLICATED per arm, the source must re-stage BOTH call arguments in BOTH
> arms — including the one that is unchanged — and put the trivial arm in the
> `then` position.**

```c
if (arg2 == -1) { p = arg1;  h = arg0->unk0x34BC; }              /* then arm  */
else           { sprintf(sp8, lbl_80298568, arg1, arg2);
                  p = (s8 *)sp8; h = arg0->unk0x34BC; }
fn_8000A7F8(h, p);
```

One change fixed four deltas at once:

1. the then-arm finally has real content, so GCC stops deleting it and stops
   reversing the branch (`bne E` / then-arm inline / `b` over E — WANT's block
   order);
2. the per-arm `h = arg0->unk0x34BC` keeps the arg setup in each arm, so the
   shared block is a **bare `bl`** and the `lwz` is *duplicated* — a one-call
   form always CSEs the per-path field load into the join block (22 insns);
3. `p = arg1;` compiles to **nothing** (r4 already holds arg1 at the join),
   which removes the `mr r4,r5` the old draft emitted because GCC had homed
   arg1 in r5 for the sprintf vararg;
4. `char sp8[0x200]` at r1+8 gives the exact 0x210 frame.

Dead ends recorded: single-call forms (p local / ternary / param-reassign
`arg1 = sp8` / `goto done`) → 22–26 insns, 33–68%; **two real call sites** →
26 insns / 30.8% (right order + duplicated load, but two `bl` + `mr r4,r5` —
this is what produced the original misdiagnosis); staging `h` only in the then
arm → 20.8%; an empty then arm (`arg1 = arg1;`) → 33.3% (branch flips); no `p`
staging in the then arm → 68%. `s32 arg1` also reaches 100% (the param type is
not load-bearing). No inline asm.

**Broader lesson for this doc:** before blaming crossjumping, check whether the
ONE-call form differs only by (a) the load being hoisted into the join block
and (b) the two arms' order. Those two symptoms have a pure-C fix (stage both
args per arm); an actual missing merge does not.
