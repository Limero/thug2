# Issue 64 — Byte-twin / near-twin recipe (sibling source recovery)

**Status: SOLVED AS A TECHNIQUE (2026-09-19) — 151 functions promoted EXACT, DOL
byte-identical throughout (hash `ff6faeb0…`); PROGRESS.md went 8320 → 8474
matched. First session: 80 (18 + 42 + 16 + 4). Second session: 51 more
(9 + 5 + 3 + 16 + 8 + 2 + 4 + 3 + 1), including two whole label-pair families
generated from the DOL — see "Session 2" below, which also retires the old
"branch-relaxation cascade" caveat. Third session: 20 near-twins (see
"Session 3"), plus 39 drafts whose *starting body* was replaced by the twin's
and 3 re-parks with better bodies.** This is not a compiler wall
doc; it is the method that closes whole families of parks whose notes blamed
register allocation, scheduling, or "doc-15/32 class" coins.

## The lever

This DOL is full of functions that were emitted from **one source file by one
compiler** and are therefore *byte-identical* or *nearly byte-identical* to a
function that is already matched. When that happens, the parked draft's problem
is not the allocator — it is that the draft still carries m2c's expression
shape. The matched sibling's source is a **proven recipe**: copy it, rename the
function, done.

Two scans, both shipped as tools:

| tool | finds | typical fix |
|---|---|---|
| `tools/twin_scan.py` | retail bytes **identical** to a matched `src/fn_*.c` | rename the function (and its callees) — nothing else |
| `tools/near_twin_scan.py` | matched `src/fn_*.c` of the same size differing in **≤ N instruction words** | one literal, one table offset, one branch polarity, one operand type |

```
tools/venv/bin/python tools/twin_scan.py --min-size 16 --source
tools/venv/bin/python tools/near_twin_scan.py --max-diff 2
tools/venv/bin/python tools/near_twin_scan.py --addr 0x801A6D80 --apply
```

`--apply` renames the twin's function in its own source and scores it at the
draft's address, which is the fastest way to see what residue is left.

## What the 2026-09-19 session actually found

**A. Exact twins (18 members) — the hash-bucket list REMOVE family.**
`8000913C 8000ED78 80025F9C 800533A8 80053AF8 8005D2C8` + the `8005D8E4
8006A960 8006F0E4 8006F26C 8006F6BC 8006F998 80098C70 800A6910 800A6EFC
800B0CF8 800F123C 800F3438` siblings. Several of these carried years-old park
notes claiming a "pure GPR role rotation with no source lever" (doc-06/32) and
"nine flags leave it byte-identical". Both claims were true *of the draft body* —
the draft was m2c's fused guard:

```c
if ((base != 0) && (key = *arg1, prev = NULL,
     node = base + ((key & ((1 << bits) - 1)) * 0xC), node != 0))
```

The matched twin `fn_8006F3F4` uses the honest shape and reproduces every home
WANT has: early-return guard, `prev = 0` as its own statement, a **typed** node
address `(char *)head + (...) * 0xC` with `Rec3 *` locals, `next` loaded *before*
the compare, and a prototyped callee (`void fn_80012224(s32, void *)`) to kill
the spurious `crclr cr1eq`.

**B. Exact twins (42 members) — two more families + three singletons.**
- 188B hash-bucket **iterator** (13): `8000EB38 800577B4 8005D20C 8006F028
  8006F1B0 8006F338 8006F600 8006F8DC 8006FFBC 80098D3C 800A6AC0 800B0C3C
  800F1180` ← recipe = matched `fn_8000E878` verbatim.
- 164B scripted-call **dispatcher** (25): `800C0240 800C9F54 800CCAF0 800CD724
  800D31A4 800D63A0 800DB2B4 800DE8FC 800DFABC 800E2850 800E50F0 800EF41C
  800EF75C 801C1960 801C50FC 801D0BCC 801EF300 801EFB74 801F6684 801FE6F0
  802001BC 80201B6C 80203220 80204880 8020CD04` ← recipe = matched
  `fn_801B3104`. Two members needed one extra fix each: `fn_801D0BCC` **returns**
  the dispatch result (`s32`) and `fn_801C50FC`'s first parameter is the object
  pointer. `fn_801EF300` was parked in **doc 15** as "51% r0-homing unreachable,
  frameless allocator tie-break" — it was neither.
  *Type note:* drafts in this family alternate between `Unk_F5317C5D` and
  `Unk_5D1D68CC` for the command record; only `Unk_F5317C5D` has `unk0xA`/
  `unk0xC`, so the `Unk_5D1D68CC` drafts could not even compile the correct body.
- 168B cursor **seek** (2): `8018B4C0`, `801A65EC` ← matched `fn_8018322C`
  verbatim. **`fn_801A65EC` was the biggest surprise**: parked at 97.6% with a
  long note ("only `mtctr r0` vs want's `mtctr r9`; ~38 variants tried; no source
  form produces mtctr r9 with the guard-first ordering"). The twin already had
  the answer — do **not** pin the counter (that kills the doloop conversion);
  pin the *copy* to r9 and pass it through an empty `__asm__("" : "+r"(v))`
  barrier.
- 168B bucket **walker** (1): `8000E7BC` ← matched `fn_801A9C1C`.
- 48B indexed **accessor** (1): `8010195C` ← matched `fn_800FE19C`.

**C. Near-twins (16 members, all at ≤ 2 words).** Every one came from a sibling
in the same family, and the residue was always one of five things:

| defect | example | fix |
|---|---|---|
| bit-mask literal | `80042110` | `andis. r9,r9,K` — the sibling tests bit 22, this one bit 21 (`0x400000` → `0x200000`) |
| table base offset | `801A6D80`, `801A6D34`, `801A6DC4`, `800CBB74`, `8009C62C` | `addi r11,r3,K` — replace the twin's K |
| branch polarity | `80054E94` | `beqlr` vs `bnelr`: sibling returns on `== 0`, this one on `!= 0` |
| operand type | `80023348` | sibling's param is `u16` (`mr r30,r3`); this one narrows a wider param (`rlwinm r30,r3,0,16,31`), so `s32 arg0` + `u16 v = arg0` |
| operand direction | `802406A4` | sibling is `-=` (subf), this one `+=`; also `*(s32 *)0x80306090` → the registered `lbl_80306090` (doc 51) |

Two of the 16 were solved by *crossing* twins: `80058DC0` and `8005E948` are the
same setter template as `8005E988` and `80058D80` but with swapped field offsets,
and the naive "closest twin" pairing was the wrong sibling in both cases.

**D. The `--max-diff 3` list (4 more promotions).** Including
`801139B0`/`801139F4` (`ScriptSetMusicVolume` / `ScriptSetMusicStreamVolume`,
whose 82.4% drafts had dropped the script object and made `fn_801282E0` a 3-arg
call instead of 4-arg) and `8021D7F0`/`8021D888` — the pair parked in **doc 15/36**
at 97.4% on a "`addi r4,r1,8` fresh materialisation vs `mr r4,r29` shared wall"
shared by five members; the matched twin `fn_8021D758` already had the working
shape (named `search_t sp8` local + `search_t *p = &sp8` view + a
`register ... __asm__("r29")` pin for the late stores).

## How to run the recipe

1. `tools/twin_scan.py` first, `--min-size 16` (the 4B/8B `blr` leaves are
   noise). If a hit exists, copy the twin's source and rename; score it.
2. `tools/near_twin_scan.py --max-diff 2`, then `--max-diff 3`. Work the list
   in diff order: 0 → 1 → 2 words. `--addr X --apply` for one address.
3. Fix the residue **by reading the differ**, not by permuting: the differing
   word tells you which literal/offset/polarity/type is wrong.
4. Preserve the draft's OWN symbol names, callee names and rodata globals where
   the twin's differ — the scorer **masks** `bl` targets and `lis/addi`
   addresses, so a wrong symbol still scores 100 but fails the linked-DOL check.
   Resolve the differing branches first (`near_twin_scan.py --addr X` prints
   "same target" vs "want/got"); fix callees by symbol name, data labels by
   address lookup, before scoring.
5. Set the draft's `range=`/`size=` marker from the original draft or from the
   symbol table, never by guessing: a wrong size registers a wrong split and
   shifts the DOL (this cost one round-trip on `801A6DC4`, which is 72B, not
   84B).
6. `tools/promote_wip.py <addr...>` — the linked-DOL verify is the real gate.
   When a batch fails, bisect the address list; `promote_wip` reverts cleanly and
   reports the first differing byte.

## Session 2 (2026-09-19, later) — 25 more, and what the residue actually was

The same recipe produced 25 further promotions (`8414` → `8439` matched, DOL
still `ff6faeb0`). The residue that had been written off as a wall was, in every
case, one of five mechanical causes:

1. **Unprototyped callee.** A call to a function with no visible declaration is
   unprototyped in C, so ngccc brackets it with the ABI marker
   `crxor 6,6,6` — one extra instruction, invisible in the C source. `800B02A4`
   and `800E43B4` were parked for a "regalloc wall" that was only this marker
   plus the `!= 0` vs early-return spelling. Declare the callee and use the
   early-return form.
2. **`-mps-float` + `__ps_t` views.** Paired-single code (`psq_l`/`psq_st`,
   `E004…`/`F005…`) only appears when the object is compiled with
   `-mps-float`, and scalar `f32` member reads stay `lfs` even then. Read the
   scratch buffer back through an 8-byte `__ps_t` view (`Unk_2D7DC1B6`-style)
   and carry the twin's `extra_cflags:` line over. `800360E8`/`80036108`/`800CD83C`.
3. **Branch words must be RESOLVED, not compared.** `tools/near_twin_scan.py`
   now decodes every differing REL14/REL24 to its absolute target: "same target,
   different encoding" is noise, "different target" is a wrong callee — which is
   the whole bug. `8005BB50`'s callee is `fn_8005B9B4`, not the twin's
   `fn_8005BA3C`; `800F4A78` calls `fn_8005656C`, not `fn_80062AD4`.
4. **A wrong callee silently DELETES an object.** This is the real explanation
   for the old `fn_80184BE8` "branch-relaxation cascade" caveat: its body called
   the twin's `fn_8018D108` instead of retail's `fn_8018D0F8`, so the object that
   provided `fn_8018D108`'s 44 bytes became unreferenced and mwldeppc dropped it
   entirely — the DOL then came out short/shifted and the failure looked like a
   neighbouring-split problem. Renaming the callee made it byte-exact.
5. **`lis`+`addi` data-symbol references are masked too.** `801FC3D8` scored
   100% masked while pointing at the twin's `lbl_80303244`/`lbl_80303234`
   instead of the draft's `lbl_80305F70`/`lbl_80305F60`. Re-derive every data
   label by *address* (the scan prints the immediates; `config/G2TE52/symbols.txt`
   maps address → name) before promoting.

Statement order also matters when a register-pin asm is involved: in
`80036810` the table load had to be written *before* the
`__asm__ volatile("mr %0,%1")` pin to land before it in the schedule.

### Family automation

When a matched twin has many same-size siblings, do not hand-port each one.
`fn_801FC1D0` has 16 siblings that differ only in a `(table, index)` global
pair. Their addresses are recoverable straight from the DOL words
(`lis rX,hi` at `+0x14`, `lwz r0,lo(rX)` at `+0x18`, `addi r9,r9,lo` at `+0x1C`),
so a 40-line scratch script decoded the pair for each address, looked the names
up in `symbols.txt`, substituted them into the twin's body, and handed 16
byte-exact drafts to `promote_wip.py` in one batch.

## Session 3 (2026-09-19, third pass) — 12 more; the twin's SOURCE SHAPE is the lever

`8439` → `8473` matched, DOL still `ff6faeb0`. Promoted (all as near-twins):
`80131960` `8013F980` `800703D8` `80070838` `80184BB0` `801A34B4` `80058E00`
`800E0A7C` `800DE11C` `801C5780` `800DE2A4` `80014A5C` `8005F984`
`80112F8C` `80113304` `800B01CC` `801175D4`.

### A. Copy the twin's *statement shape*, not just its bytes

`80184BB0` / `801A34B4` were parked (43.8% / 44%) under doc-15 as "the second
call's argument materialisation order — the pinned arg1 home is scheduled last at
retail". They are not scheduling at all. The matched twin writes:

```c
temp = callee(...);
if (temp == 0) { return K; }     /* K = 0 here, 1 in the twin */
return tail(temp);
```

which ngccc compiles to `or. r0,r3,r3 ; li r3,K ; beq end ; mr r3,r0 ; bl` — the
`li` hoisted *above* the branch and the value parked in `r0`. The parked drafts
wrote the logically equivalent `if (temp != 0) { tail(temp); } return 0;`, which
emits `or. r3,r3,r3` (no `mr r3,r0`) and sinks the `li` past the call: four words
apart, branch offsets shifted. **Equivalent C is not equivalent bytes.** When a
matched sibling exists, transcribe its control-flow shape verbatim and change only
the constants. (The same twin also fixes the argument passes: the real head call
forwards the incoming `r3`/`r4` and materialises `li r5,1` / `li r4,0`, with no
leading call at all.)

### B. Six of the twelve were wrong DATA, described as scheduler walls

A wrong field offset or literal shifts every following word in the function, so
the residue *reads* like a rotation. Recovered by re-deriving the numbers from the
twin's disassembly rather than trusting the park note:

| addr | park note said | actually was |
|---|---|---|
| `800703D8` | "2nd call's arg materialisation (words 18/19/20)" | record pad `0x30` → `0x28` (words 24/25) |
| `80070838` | same | record pad `0x30` → `0x38` |
| `800DE2A4` | "scheduling/regalloc", best 60.7% | `arg0+0x50/0x4C` → `0x1C/0x18`, record ptr `+0x10` → `+0x8` |
| `800DE11C` | " scheduling/regalloc" 23.7% | 3 callees + literal `0x60` → `0x58` |
| `80014A5C` | "needs the counter compare/dec emission rule" 61.5% | counter init `0` → `2`, stride `0x1008` → `0xFC`, arg `p` → `p+0x84` |
| `80058E00` | `-O1` best 35.3% | offsets `0x10/0x4/0x14` → `0x38/0x34/0x50`, constant `1` → a load from `*arg1`, and the load needs its own temp to hoist |

`80014A5C` is the sharpest example: the loop *shape* was already right, and the
"comparison/dec emission rule" it was parked on never had to be found — the
counter simply had to start at 2 (`li r30,2`, three iterations).

### C. QB constants masquerade as un-nameable data labels

`801C5780` was parked for a "doc-15 scheduler tie-break on the two rodata anchor
loads". The whole residue was `lis r4,0x4B88 / ori r4,0xE4E4` instead of
`lis r4,0x27F4 / ori r4,0x8E93`: the draft passed `QB_STATEDURATION` where retail
pushes `QB_TIMESINCEPHYSICSSWITCH`. Its own header comment already named the right
constant. `tools/label_twin_fix.py` reports such a pair as an un-nameable
`lbl_4B88E4E4` — grep `include/qb_constants.h` before concluding
"scheduler".

### D. Workflow that made this cheap

`tools/label_twin_fix.py <wipaddr> <twinaddr> --write` takes the twin's source,
decodes both immediate halves out of the DOL, maps them through `symbols.txt`, and
writes the substituted body straight into `src/wip/`. Run it over the whole
`near_twin_scan.py --real --max-diff 8 --min-words 8` list and 39 drafts get a
better starting body. It is a *batch* operation, so it can also regress a draft
that was already better: `tools/keep_better_wip.py` scores both the HEAD and the
working-tree version of every modified draft and `git checkout`s the loser (7
reverted, 39 kept on this pass). Always run it before reading the numbers.

### E. The symbol NAME is load-bearing at link time

Three more promoted from the same `--max-diff 8` list (`80112F40`, `80032A18`,
`801138D0`), and the link caught two things the scorer cannot see:

- **Take the name from `symbols.txt` for the DRAFT's address, never the twin's.**
  Copying the twin's body brought its script name along, and promoting
  `80112F40` as `ScriptSetCaptureDestTexture` collided with the real
  `fn_8011429C.o` ("multiply-defined"). Renaming to the draft's own
  `fn_80112F40` then broke the link the other way: **`symbols.txt` calls
  0x80112F40 `ScriptStopStream` and 0x801138D0 `ScriptSetSfxVolume`**, so the
  script table's references went undefined ("undefined: 'ScriptStopStream' /
  'ScriptSetSfxVolume' referenced from lbl_80303464"). The addresses in
  `splits.txt`/`symbols.txt` are the authority — `fn_XXXXXXXX` is only the
  default when no script name is known.
- **The masked `lis`+`addi` trap struck again.** `801138D0` scored a masked
  100% with `lbl_802A7FDC` where retail reads `lbl_8029D108` (both are floats in
  `.rodata2`); only the DOL byte-compare caught it (2 bytes, vaddr 0x801139E6).
  Re-derive float constants by decoding the `lis`+`lfs` pair, not by pattern-
  matching a plausible-looking `lbl_*`.

These three also show the most common *content* bug in the leftover parks: a
recovered call written as a STORE (`801138D0`: retail loads offset 0x2C34 through r9, loads a float from stack offset 8 and calls the helper, while the draft wrote a float store to offset 0x420 instead), a wrong
callee argument list (`80112F40`: retail has an else arm that loads -1 into the return register and calls its helper, which the draft did not have at all), and a missing CSE temp
(`80032A18`: without a named local the two `lbl_80291B44` reads emit two `lfs`).

### F. When there is no matched twin left: scan the RETAIL bytes for the family template

`twin_scan.py` / `near_twin_scan.py` both need an already-matched function to
copy from. Once the vein is exhausted for a family, the next lever is the
family's **instruction template**: several of these families were emitted from one
source file, so their retail byte shape is fixed apart from a few immediates.
`tools/template_scan.py` holds those templates and matches them against the
retail bytes of every `src/wip` draft.

The first template (`--family query`) is the QB bool-query shape:

```
sp8 = 0; fn_801286D0(arg0, 0, &sp8, K4); if (<tail>(sp8) != 0) { return K; } return 0;
```

and it found `ScriptCleanUpAndRemoveSymbol` (`801175D4`, parked at 13.6% then
30% with a completely different body — a `lbl_80366474` global this function never
touches) plus `ScriptIsStreamPlaying` / `ScriptFreeStreamFrameAmp` members. The
source form that matches is the guard:

```c
    fn_801286D0(arg0, 0, &sp8, 1);
    r = fn_8012543C(sp8);
    if (r == 0) { return 0; }      /* li r3,0 hoisted above the beq */
    fn_8012DE30(r);
    return 1;                      /* li r3,1 sunk below the tail bl */
```

**Text-grepping `src/wip` for a family idiom under-reports badly** — it only finds
drafts whose body was already near-correct. `80113304` would have been missed
that way (its parked body tested the wrong variable), yet its retail bytes match
the template exactly. Scan the DOL words, not the draft text.

### G. Residue that survived an honest attempt (parked with better bodies)

- `8000DDB0` (89.47%) / `8000DDFC` (88.24%) — spin-wait pair. Bodies corrected to
the real semantics (`while (test(...) == 0) { yield(); } return 0;` — no
increment, return the constant). The residue is one two-word slot: retail emits
`cmpwi ; li r3,0 ; beq <loop-body>` (the returned constant hoisted above the
loop-back branch), ngccc emits `cmpwi ; beq <body> ; li r3,0`. Five loop shapes
(while / named res / res-assigned-in-body / for(;;)+break / do-while-return) and
five flag sets (`-fno-schedule-insns{,2}`, `-O1`, `-O2`, both) all land on the
identical residue.
- `801A1AAC` (87.50%, up from 78.12%) — the if-branch of the notification
dispatch is exact after fixing the twin's offsets (`arg0+0x70`, record base
`arg0+0x74`); the else branch keeps a 4-word fpr-assignment residue (retail loads
`lbl_802AB1BC`→f1, `lbl_802AB1B4`→f2, `lbl_802AB1B8`→f4, then `fsubs f1,f0,f1`,
then `fmr f3,f2`; ngccc swaps the f1/f2 constants and emits the `fmr` first).

## How to run the recipe
- Near-twin pairing is a heuristic: same size + fewest differing words is not
  always the right sibling (see `80058DC0`/`8005E948`). If the residue looks
  structural, try the *other* same-size sibling in the family.
- The twin vein is exhaustible (it is a function of what is already matched), so
  re-run both scans after every promotion batch — each new match can create new
  twins. After the 2026-09-19 batches, `twin_scan.py --min-size 16` reports
  **0** remaining exact twins, so the remaining value is in `near_twin_scan.py`
  at max-diff 3+.
