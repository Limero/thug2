# 55 — A `// FLAG:` line is a cached decision; re-sweep it after every body fix

**Closed 2026-09-13.** Status: SOLVED (two promotions, one of them a draft that had
been *parked* with a detailed "GPR colouring wall" note that turned out to be an
artefact of its own flag line).

## The bug class

`src/wip/fn_*.c` drafts carry a `// FLAG: <extra cflags>` line. It is written by
whatever sweep happened to find a local maximum at the time — usually
`tools/flagmatrix*.py` under the old blind per-draft flag matrix. Nothing ever
re-tests it.

So a draft's flag line is a decision cached against a **body that no longer
exists**. Two things then go wrong:

1. The flag *regresses* the improved body, and every later reader of the park note
   describes the flagged compile. `fn_80079FB4` was documented as "a pure GPR
   colouring tie ... instruction-order, local-lifetime, named-local,
   pointer/byte-ptr/u8-array and inline-call forms all reproduce the same swap;
   do not re-grind without a new allocator lever". All of that was measured with
   `// FLAG: -fno-schedule-insns -fno-sched-spec`, which the draft had carried
   since *before* the retype that took it 77.8% -> 91.7%. Those two flags cost
   **8.3 points**: with plain `-O2` the draft is **100.0%**.
2. The flag *masks* a different regression the body fix introduced. `fn_8005D4F4`
   had `// FLAG: -O1` because the pre-prototype body scored 48% -> 51.7% with it.
   Once the callee prototype was restored, `-O1` was worth 85.2% and the default
   `-O2` was **100.0%**.

## The sweep

`tools/flagrefresh.py` (this is the version to keep; it supersedes the blind
matrix):

* only drafts that *have* a `// FLAG:` line (451 of 3556 at the time);
* candidates: `[]`, `-O1/-O2/-O3/-Os`, the four scheduling flags,
  `-fno-expensive-optimizations`, `-fno-gcse`, `-fno-strength-reduce`,
  `-ffixed-r9/r11`, `-mps-float`, `-fno-rerun-cse-after-loop`,
  `-fno-branch-count-reg`, and two pairs;
* report any draft where a candidate beats the stored flags.

Result: **34 of 451 drafts**, including one instant EXACT (`80079FB4`) and five
worth >= 5 points (`8018DFE0` +25.8, `80244E48` +22.7, `802305B0` +17.8,
`80230774` +13.6, `80041FDC` +10.0).

**Verification rule (do not skip):** the candidate list must be re-measured
through `gen_leaves.draft_flags()` before writing, because that function
*auto-adds* `-mps-float` for drafts containing `__ps_t`/`__builtin_ps_*`. A sweep
that passes `extra_flags` straight through will test such a draft with
`-mps-float` missing and report an improvement that does not exist. Five of the
34 rows reverted exactly this way (`tools/apply_na.py` / `/tmp/apply_fr.py` both
re-score before writing and revert on mismatch).

## Two axes that were simply absent from the vocabulary

The same way `-fno-rerun-cse-after-loop` was discovered for `fn_8017DD54`, a
pool-wide pass over **every** draft found two more flags nobody had in the list:

* **`-Os`** — 265 drafts improved, five by >= 10 points, best `800CCD34`
  92.8 -> 97.2. `-Os` is not just "-O2 smaller": it flips `-fno-*` defaults that
  change basic-block ordering, so it lands in the same class as
  `-fno-schedule-insns*`.
* **`-fno-rerun-cse-after-loop` / `-fno-expensive-optimizations`** — 208 more
  drafts improved, including `80175690` +51.9 (14.9 -> 66.8), `80077CFC` +36.3,
  `8001E248` +35.6, `80117FC0` +32.3 (60.0 -> 92.3, then EXACT after a call-arity
  fix), `8021D990` +27.8, `801C2B04` +23.7.

Both passes are `tools/newaxis.py <flag> [flag...]` — one baseline compile plus
one compile per candidate over the whole `src/wip` tree.

Caveat recorded from the earlier pairwise sweep (doc 09): *pairs* of flags almost
never beat their best single flag. These two new axes are single flags; the
"+0 pairs" verdict still holds.

## The recipes

**Recipe 66 (stale FLAG).** Any time a draft's body changes, re-run
`tools/newaxis.py` on it with `[]` and `-O2` included. A `// FLAG:` line whose
value came from an older body is a liability, and the *park note next to it* is
describing that older body — treat both as suspect. Corollary: never copy a park
note's score into a new note without re-measuring.

**Recipe 67 (call-arity repair by register shift).** `fn_80117FC0` was a 3-arg
call to a 4-arg callee, where the missing argument was the *enclosing function's
own arg0* and therefore already live in r3 — so the word count was identical and
neither the length check nor the score flagged it. The tell is that want's
argument-setup registers are each one slot **higher** than ours and r3 has no
load-or-move before the branch-and-link: want loads zero into r4, takes a stack address into r5 and zeroes r6 with r3 left untouched as arg0, while the 3-arg prototype build loads the same three values one slot low into r3, r4 and r5.

That is the mirror image of doc 52's "callee has *fewer* args than declared".

## Promotions

* `fn_80079FB4` — parked "GPR colour wall" -> EXACT by *deleting* the flag line.
* `fn_8005D4F4` — 57.1% -> 85.2% (prototype) -> EXACT by deleting `-O1`.
* `fn_80044F60` — 54.7% -> 83.6% (two prototypes) -> EXACT (a dropped 2nd argument
  of a third callee, which made the function 4B short).
* `fn_80117FC0` — 60.0% -> 92.3% (`-fno-expensive-optimizations`) -> EXACT
  (call-arity repair).

## Addendum (same session): the recursion

Applying recipe 66 is not a one-shot. The prototype sweep touched 992 drafts
(see `WIP.md` 2026-09-13 (k)); each of those is a *new body*, so every one of
their flag lines is stale again. `tools/newaxis.py` was therefore re-run over the
whole tree as the closing step of the session.

Budget note: `tools/newaxis.py` is one baseline compile + one per candidate per
draft over ~3550 drafts. Three candidates is ~25 minutes on 8 cores. Run it in
`sestsid nohup` with `LEAF_TMPDIR` unset (each worker sets its own), and always
feed the result through an applier that re-scores through
`gen_leaves.draft_flags()` before writing.

## ADDENDUM 2026-09-15 (f): two narrow scanners + a promotion from a stale flag

`tools/flagrefresh.py` re-sweeps 14 flag combinations per draft and is the
thorough option, but it is ~11k compiles over the 809 flagged drafts. Two narrow
A/B scanners get most of the value for ~1,600:

  - `tools/flagdrop_scan.py` — header flags vs **no** flags. 809 drafts → 14
    where the recorded flag is now a regressor.
  - `tools/flagtok_scan.py` — peel **one token** out of a multi-token flag line
    (the middle ground: `-mps-float -fno-schedule-insns` can be right about the
    first and wrong about the second). 809 drafts → 7 token drops, all ≤ 2pt.

**`fn_80079DA8` came back EXACT from the first scanner.** It had been parked
with *"doc-15 scratch-color coin flip, 3 words: want homes the shift …"* — a
register-colouring diagnosis for what was actually a stale flag: 94.7% with the
recorded flags, **100% with none**. That is worth remembering when a park note
blames register allocation for a 2–4 word residual: re-test the flag axis
*before* accepting the regalloc story. The other 13 drafts were kept at their
better (flag-free) scores, and `fn_80054388` was the same failure mode found by
hand (see its park note).

Mechanics: keep the body, delete the `// FLAG:` line (or the one token), and
record the A/B in the draft header so the next sweep does not re-add it.

## ADDENDUM 2026-09-15 (k): the two-solve case — a stale flag can hide an EXACT

The strongest form of recipe 66 seen so far: **two functions whose remaining
residual was entirely the cached flag.** `fn_800F3F3C` and `fn_800F45A4` (a
matched pair of vtable-dispatch teardown wrappers, 172B/164B) each carried
`// FLAG: -O1` from the 2026-09-13 flag matrix. After the body fixes below, both
sat at 90.7% / 78.0% and looked like two separate regalloc walls — in both cases
the one defect was the `li r4,0` for a call's constant 2nd argument being
*scheduled one slot late* (`lwz r9; lha r3; lwz r0; add; li r4,0; mtlr` instead
of `lwz r9; li r4,0; lha r3; lwz r0; add; mtlr`). Dropping `-O1` (default `-O2`)
emits the DOL order and both are **100.0%**. Same shape as the `fn_80079FB4`
case above: a 3–4 word *instruction-order* residual is not automatically a
colouring coin — re-test the flag axis first.

The body fixes that had to land first (they are what made the flag line stale):

1. **A one-argument call declared with two.** Both wrappers' first guarded call
   is `((s32 (*)(void *))temp->unk0x14)((char *)arg0 + temp->unk0x10)` — one
   argument. m2c added the vtable temp itself as a 2nd argument, which forces the
   temp into r4 (an *argument register*) for the first block; without it ngccc
   picks r9, exactly as the DOL uses in all four blocks. Tell: want's first block
   has **no** `mr r4,<temp>` / `lwz r4,<temp>` word, yet our block does.
2. **A call result that is the *next* call's first argument** (`fn_800F45A4`
   only): the 2nd guarded call's return stays in r3 across `blrl` and is passed
   straight into `fn_80054C6C`, so retail shows `li r4,0` (a **2nd** argument)
   where the one-arg prototype produced `li r3,0`. Tell: the constant lands in an
   argument register that is *not* r3.
3. **Signed 16-bit vtable fields** (`unk0x58`, `unk0x80`) needing the doc-53 pun,
   otherwise `lwz` where want has `lha`.

Detection shortcut: if a `blrl`-dispatch block's constant argument lands in r4+
while the callee looks 1-arg, count the arguments want actually *materialises*
(the words before `bl`/`blrl`) rather than trusting m2c's argument list.

This session's pool-wide re-run (`tools/flagrefresh.py` over the 754 flagged
drafts, ~11k compiles) produced 8 rows worth >= 8 points — `812244A8`
(`-fno-schedule-insns2 -ffixed-r11` -> `-O1`) 41.2 -> **81.3**, `80015E34`
(`-ffixed-r9` -> `-fno-rerun-cse-after-loop`) 44.2 -> **65.1**, `801182BC`
(`-fno-schedule-insns` -> `-fno-expensive-optimizations`) 38.7 -> **63.3** — plus
the two EXACTs above, which the sweep *did* flag (the drafts' own FLAG line was
never in the candidate set).

## ADDENDUM 2026-09-20 — third two-solve case (`fn_801F0E84`)

`fn_801F0E84` (196B) carried `// FLAG: -fno-schedule-insns` from the 2026-09-17
per-draft flag-matrix sweep, adopted as a ~5-point win *on the broken body* (the
same stamp that appears in the draft header). The body fixes landed this session
(argument sequencing + a `u16` field + two callee prototypes — see
[doc 69](69-nested-call-arg-liveness.md)) took it to **91.8% under that flag**,
where the residual looked exactly like a `global-alloc` colour coin: 4 words,
want homing the symbol base in `r30` and the surviving global load in `r29`, ours
the other way round.

With **no flags at all the same body is byte-exact** (196B, promoted). The stale
flag was the thing pinning the register order.

State the rule plainly: a scheduling flag is not a "win", it is a *decision*, and
a decision recorded against a body that has since been edited is a liability.
That is now three EXACTs recovered this way (`fn_80079FB4`, `fn_80079DA8`, and
this one) plus two more from addendum (k). When a 2–4 word residual looks like a
register colouring tie, the first thing to try is still the flag axis.
