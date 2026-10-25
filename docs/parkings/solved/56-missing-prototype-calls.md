# 56 — Missing-prototype implicit-int calls (`crclr cr1eq` + 4-byte frames)

## Symptom

A wip draft calls `fn_XXXXXXXX(...)` that has **no prototype line** in the
draft. MWCC/GCC then treats the callee as implicit-int varargs-style:

1. every call site gets a `crclr cr1eq` (4 bytes) the retail code does not
   have, and
2. struct-return / pointer-return ABI is discarded (the call result is
   treated as `s32`).

Both effects change the frame: the typical signature is a **+4 length
mismatch** with a `!!` pair `want <bl> / got crclr cr1eq` sitting *before an
unrelated call* (the crclr lands on the next call boundary, not on the
undeclared call itself — chase the word, not the function).

## Detection

```sh
tools/venv/bin/python tools/undecl_scan.py   # lists drafts with callees lacking decls
```

Cross with the length-mismatch census (`+4`/`+8` class) or with any draft
whose residue is a single crclr. The scan flags ~30% of drafts because most
drafts never declared callees and got away with it (m2c guessed `s32` for
everything and only self-recursion showed up); the profitable population is
the intersection with length mismatches or 1–3-word residues.

## Fix

Add a normal prototype before the definition (arg count inferred from call
sites, `s32` params):

```c
char *strcpy(char *, const char *);   // libc needs it too — implicit strcpy
void fn_800092B0(s32, s32);
```

- `strcpy` (and other libc) calls are the same bug: an undeclared `strcpy`
  emits `crclr cr1eq`.
- Return type matters only when the result is used (`char *` vs `s32`); for
  discarded results the arg-count prototype alone kills the crclr.

## Scored results (2026-09-13)

| fn | before | after | note |
|---|---|---|---|
| `fn_8019BB98` | 65.0% | **EXACT** | `strcpy` + `fn_800092B0` protos |
| `fn_8017E340` | 52.2% | **EXACT** | `fn_80182E98` proto (was 2nd call after an undeclared one) |
| `fn_80174A58` | 57.7% | **EXACT** | batch-inferred `s32` protos |
| `fn_80175450` | 54.2% | **EXACT** | batch-inferred |
| `fn_801754AC` | 52.2% | **EXACT** | batch-inferred |
| `fn_80185D10` | 57.7% | **EXACT** | protos + `(char *)` base for the `+0x18` load (m2c `(s32 *)` scale bug: `(s32 *)p + 0x18` emits `0x60(r3)`) |
| `fn_80185E9C` | 57.7% | **EXACT** | twin of the above |
| `fn_80113C5C` | 55.6% | 84.6% | `fn_8011E0E4` proto |
| `fn_8023499C` | 50.0% | 81.0% | `fn_80232F24` proto |
| `fn_801B07D4` | 52.4% | 92.5% | protos + `lbl_802ABD98` as **symbol** (numeric literal `0x802ABD98` emits `lis/ori`; symbol address emits want's `lis/addi` %hi/%lo form) |

## Failures / negative results

- Wrong-arity or wrong-type prototypes **regress hard**: `fn_8003CF18`
  98.0→73.8 (reverted), `fn_8004F4E4` 61.2→55.7 (reverted), and 8 drafts in
  the NEAR pool collapsed to DIFF when the guessed `s32` types broke pointer
  args. Batch tool A/B-tests and reverts automatically.
- Adding a decl to an *already-correct implicit call* can hurt:
  `fn_80112A94` 81.1→68.3 — the implicit-call frame happened to match retail.
- Self-recursion flags in the scan are noise (own name only).

## 2026-09-14 — the `+4` signature can also be a *9-word* signature

`fn_801280E0` (144B want, 148B got) was parked at **67.6%** sitting on an
undeclared `fn_80129570` — and the damage was far larger than the 4-byte
`crclr cr1eq` the doc's symptom table implies: the extra word shifts the whole
tail, so **9 of 36 words scored wrong**. Adding `void fn_80129570(s32, s32);`
(the spelling every promoted caller of `fn_80129570` uses) jumped it straight
to **88.9%**; the remaining 4 words are the unrelated param-home order
(see doc 38). Two takeaways:

1. `+4 length` is a *lower bound* on the score damage. Always re-diff after
   any prototype fix — do not size the win from the byte delta.
2. `void` / `s32` / `(void *, s32)` / `(Unk_2EF06E12 *, s32)` all score the
   same here, so the choice only matters for the project-wide header
   convention (use the plain `(s32, s32)` form).

## Tooling

`tools/undecl_scan.py` (scan), `/tmp/proto_batch.py` pattern (batch A/B with
revert-on-regress, EXACT-banner-aware parse). test_wip_drafts EXACT output
has no `%` on its line — parsers must check the banner first.

## Addendum 2026-09-15 — the undeclared-callee sweep is a *large* family

`tools/proto_undeclared_scan.py` (new) generalises this doc into a whole-pool
sweep. For every draft it finds each `fn_XXXXXXXX(...)` **call whose name has no
prototype in scope**, adds a declaration, and A/B-scores it. The declaration is
the callee's own definition signature when `src/fn_XXXXXXXX.c` already exists
(so the types are exactly right), otherwise `void fn_X(void *, …)` with the
parameter count **inferred from the call site** — `void *` and `s32` pass
identically on PPC, so only the count changes the call setup.

Two implementation notes that matter:

1. **The "already declared" test must require a return type.** A naive
   `\bfn_X\s*\([^;]*\)\s*;` regex also matches the *call statement*
   `    fn_8005C944(arg0, arg1);`, so the callee is wrongly skipped. Require a
   type token (`void|s32|u32|…|Unk_\w+`) before the name.
2. **Prefilter on the object code, not the source.** Compile the draft once and
   skip it unless the disassembly actually contains a `crclr`/`crset`; without
   this the sweep tries ~5 prototypes for each of a draft's ~10 callees and runs
   for hours (1785 drafts → <5 min with the filter).

Results on the 1,785-draft no-park pool: **275 drafts improved, 3 promoted
EXACT** — `fn_801A0D50` (45.8 → 100), `fn_8012E018` (47.4 → 100, needed
`void *fn_800105CC(u32 size);` — the return type is what matters when the call
is `fn_80009AAC(fn_800105CC(0x1C))`), `fn_8007ABB8` (63.2 → 100). Best partials:
`fn_8004CDAC` 50.0 → 97.0, `fn_80010C1C` 32.4 → 94.4, `fn_8004238C` 46.2 → 92.0,
`fn_8005C944` 42.3 → 84.0, `fn_800A1AE8` 33.3 → 82.8, `fn_80234FC0` 41.2 → 81.2,
`fn_80062934` 40.9 → 81.0.

**Flag trap when verifying:** for a draft with a `// FLAG:` header, compare
before/after *with those flags applied* (`score_body.py 0xADDR body.c "$flags"`).
Scored at default flags, nine of the 275 applied edits looked like regressions
(e.g. `fn_800F45A4` 23.3 vs 21.4); under its real `-O1` the same pair is
57.1 → 73.2, i.e. the improvement the sweep measured. The sweep itself uses
`draft_flags()`, so its own `BETTER` lines are trustworthy.

## Addendum 2 (2026-09-15, i) — make the sweep *iterative*, and the `r5` variant

**Iterate.** A draft usually carries **more than one** undeclared callee, and
the first prototype only removes the *first* `crclr` — the second one is still
there, so a single-pass sweep under-reports. `proto_undeclared_scan.py` now
loops up to four rounds, re-deriving the declaration set from the current best
body each round (so an already-added prototype is never retried). Restricting
the pool to drafts whose object code still contains a `crclr`/`crset`
(1,026 of the 1,771 no-park drafts) keeps this cheap: **114 drafts improved,
2 more promoted EXACT** — `fn_8018B90C` (26.4 → 100, four-arg
`void fn_80128228(void *, void *, void *, void *);`) and `fn_801992A8`
(62.5 → 100). Best partials: `fn_800AAEA4` 64.9 → 97.1, `fn_8018403C`
55.6 → 96.2, `fn_80185474` 61.9 → 95.0, `fn_80171868` 66.7 → 89.7,
`fn_8021B3E0` 70.7 → 89.3.

**The literal can be a *later* argument — that is a different defect.** Where a
call's arg register is not r3, no prototype fixes it; the *callee's* real
parameter list has to be used and the missing leading arguments supplied by the
enclosing function's own parameters. `fn_801839F0` is called by 26 wip drafts,
and retail puts the literal in **r5**: want branches to the helper and loads the constant 1 into r5 with r3/r4 left as the caller's incoming args, while got loads the constant into r3 instead.

m2c dropped the two pass-through arguments, so the enclosing function must be
declared with (at least) two leading parameters and forward them:
`fn_801839F0((s32)a, (s32)b, 1)`. Applying that to the eight drafts of the
family whose call argument is a literal closed **`fn_8018403C` (96.2 → 100)**
and **`fn_80185474` (95.0 → 100)**, and improved `fn_8018694C` 85.7 → 89.3,
`fn_80184BB0` 37.5 → 43.8, `fn_80184EB4` 40.7 → 44.4, `fn_80183F08` 13.6 → 15.3,
`fn_80183FDC` 8.3 → 12.5. The other 18 members pass a computed value, and the
same edit makes them worse — always A/B.

**Stop-loss:** two adjacent drafts in that family (`fn_80184558`, `fn_8018BC14`)
looked similar but the residual is *not* a prototype issue — `fn_80184558`
carries a redundant loop-carried copy (`var_r4 = arg1;`) that costs two `mr`s,
and removing it drops 66.7 → 62.5 %. Recorded here so the next pass does not
re-try it.

## Addendum 2026-09-15 (m) — the lever was NOT exhausted; the *pool* was incomplete

The "exhausted" verdicts recorded on 2026-09-15 for the doc-56 prototype sweep
(and for docs 59/60) were measured against a candidate pool of **1,748**
addresses.  That pool was not the whole non-parked corpus: a full re-derivation
found **1,338 further sweepable drafts** that had never been scored or swept
(see `tools/sweepable_pool.py`, doc 62).  Re-running this sweep over just those
1,338 addresses produced **136 improvements and 3 promotions**:

| fn | size | score | prototype |
|---|---|---|---|
| `fn_80118104` | 128B | 63.6 → **100** | `void fn_801286D0(void *, void *, void *, void *)` |
| `fn_800E448C` | 204B | 56.6 → **100** | `void fn_80064494(void *, void *, void *, void *)` |
| `fn_800DF5B4` | 180B | 43.8 → **100** | `void fn_801286D0(void *, void *, void *, void *)` |

All three were carrying a stale `// PARKED (/20)` note ("instruction
scheduling / register allocation / lis+ori vs lis+addi") that had nothing to do
with the actual defect — the undeclared callee's `crclr cr1eq`.  **Lesson: when a
sweep reports a lever "exhausted", state the pool it was run over; an incomplete
pool reads exactly like an exhausted lever.**

Best remaining partials from the new set: `fn_800DC804` 61.5 → 76.0,
`fn_800F0EF0` 57.9 → 78.4, `fn_8011348C` 55.2 → 89.3, `fn_80103280` 51.2 → 95.0,
`fn_800DFB64` (inside `fn_800DF5B4`) 43.8 → 84.8, `fn_8020630C` 40.4 → 91.8.

## Addendum 2026-09-15 (n) — the prototype must have the FLOAT parameter, and it can only be seen after a stale flag is dropped

`fn_8005E4B8` (`ScriptSet2DIn3DSpaceParams`) came back **EXACT** from the
no-park pool, but *not* through this sweep — the sweep cannot find it, and this
is the general failure mode to watch for:

- The undeclared callee is `fn_8005E2DC(sp8)` where `sp8` is an `f32`. The
  sweep's arity fallback declares `void fn_8005E2DC(void *)`, which **converts
  the float to an integer GPR** (plus `crclr cr1eq`); that scores *worse* than
  the bare call, so the sweep correctly refuses it. The winning declaration is
  `void fn_8005E2DC(float v);` — the parameter type decides the FPR/GPR class,
  and for a float arg only a float parameter is right.
- Even with the right prototype the draft still scored 31.7 %, because it
  carried a stale `// FLAG: -fno-expensive-optimizations` line. Dropping the
  flag (doc-55 axis) on top of the prototype gives **100 %** (41/41). So the
  two levers are *joint*: either alone looks like a regression.

Practical rule: when a call passes a float/`f32` expression to an undeclared
callee, do not trust the arity fallback — write `void callee(float);`
explicitly, then re-test the flag axis. (The same draft's `Script*` neighbours
are recorded in doc-15.)

## ADDENDUM 2026-09-20 — a `crclr` can be *standing in* for a word you are missing

All of the above assumes the crclr is purely additive. It is not always: a
`crclr` adds one word at a point where the draft may be one word **short**,
so removing it (by writing the prototype) *shifts the whole tail* and the
score can collapse rather than rise. Two cases measured today:

* `fn_801F559C` — 62.5 % with the crclr, **13.9 % with the prototype alone**
  (284 B: the missing word elsewhere had been hidden by the extra one). The
  function only became tractable after the real defect was found (m2c had
  scrambled a `case` arm: 86.1 % now, doc 69's batch note).
* `fn_8000CCF4` — 63.8 % with the crclr, **19.0 % with the prototype**
  (58 -> 57 words). Its tail is still one word out of phase; the note in the
draft records both clusters.

Rule to apply before trusting a draft's score: **if the body still contains an
undeclared callee, the score is not a measurement of the body.** Compare
`want_words` vs `got_words` (the `crclr` makes them agree), then add the
prototype and re-read: a collapse means there is a second, independent defect —
do not "restore" the crclr to get the score back.

(Also seen: the same shape where the missing word is a real instruction the
source should have produced, e.g. a second argument copy — see the park note in
`fn_80129A90`.)

## Counter-case 2026-09-21 — some callees must STAY undeclared

`fn_8005F688` (132 B, 47.2 % → **100 %**) is the mirror image: retail *has* a
`crclr cr1eq` immediately before its `bl memcpy`, i.e. the original source called
`memcpy` with **no prototype in scope**. Adding `void *memcpy(void *, s32, s32);`
(which is what the sweep does mechanically) removes that word and the function
comes up *one word short* — 78.8 % with the tail shifted, not 100 %.

The rest of the same draft did need prototypes (`fn_8000F320` had none), and its
`fn_800105CC` was also mis-arity'd (1-arg `fn_800105CC(temp_r29 * 4)`, not
`(arg0, size)`). So the rule is per-call, not per-draft: **declare the callees
whose `bl` has no crclr; leave undeclared (or declare old-style) the ones whose
`bl` does.** A one-word `crclr` in want is a fact about the original TU's
declarations, and it survives into the shipped binary.
