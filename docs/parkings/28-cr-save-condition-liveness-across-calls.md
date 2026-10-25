# 28 — CR-save: condition liveness across calls (mfcr/mtcrf epilogues)

**Status:** OPEN — but one member-class SOLVED (memory-backed
bitfield flag route, fn_801517BC EXACT; see below). True raw-CR liveness
members remain parked.
**Affected exemplars:** `fn_80141FAC` (2040 B, parked), plus a large pool —
survey of `.text` finds **406 functions containing `mfcr`**, of which only
3 are matched so far. Not every member is blocked (see the reproducible
form below) — but every long-range one tried so far is.

## Symptom

WANT saves the condition register in the prologue and restores selected fields in the epilogue: the prologue creates a 0x2c-byte frame, saves the link register and registers from r25 at frame offset 0xc, moves the condition register into r12 and stores r12 to frame offset 8 as the CR save, while the epilogue reloads r12 from frame offset 8 and restores condition fields 4 and 3 selected by mask 0x18.

The body compares two conditions early, then branches on each much later,
with one or more `bl`s in between. GCC cannot keep a raw comparison live
across a call in a crX scratch field (calls clobber CR), so it parks both
conditions in **callee-saved CR fields** at function entry (`mfcr`) and
restores them at exit (`mtcrf`). ngccc compiles every plain-C
reconstruction to re-compare (or fold to a boolean), producing no mfcr at
all and a different branch structure.

 exemplar `fn_80141FAC`: `arg5 == 0` feeds a cr4 test and
`arg5 == 1` a cr3 test; both branch ~20 instructions later, across
`bl fn_801A0D50`.

## The contrast case that proves the boundary

`fn_80143D28` (**EXACT**) carries the *identical*
`mfcr r12` + `mtcrf 0x18,r12` idiom. It matches because its two conditions
are consumed CLOSE together:

```c
if ((x != 0) || (y != 0)) { ... }   /* natural cr3/cr4 reuse incl. mfcr save */
```

So **mfcr/mtcrf itself is emittable by plain C** when short-range
condition reuse happens (`||`, `&&`, if/else chains within a basic-block
neighborhood). The wall is specifically LONG-RANGE liveness: a condition
consumed after intervening calls.

## SOLVED form (2026-08-23, fn_801517BC EXACT — memory-backed flag, not CR liveness)

ScriptCleanup (620 B) carries want's `cmpwi cr4` + mfcr/rlwimi/srwi/clrlwi
machinery and matched **byte-exact** once the condition was kept in MEMORY
instead of a live CR. The original source saved/cleared/restored a **1-bit
big-endian bitfield struct field** at `arg1+0xCC` around the calls:

```c
struct unkflags { u32 bit:1; u32 val:31; };
var = ((struct unkflags *)((char *)arg1 + 0xCC))->bit;
((struct unkflags *)((char *)arg1 + 0xCC))->bit = 0;   /* clear */
/* ... intervening bl's ... */
((struct unkflags *)((char *)arg1 + 0xCC))->bit = var; /* restore */
```

Memory survives the calls (no callee-saved register needed — this dodges the
register-steal cascade that blocked the asm-opaque route below), and the
bitfield extract/insert emits exactly the srwi/clrlwi + rlwimi + cr-test
idiom. This PROVES the doc's earlier hint that the original used stored flags
rather than raw-CR liveness. Extends AGENTS.md recipe 110 from single rlwimi
inserts to full save/clear/restore across calls.

**Triage rule for remaining members:** before parking any doc-28 candidate,
look for what the source could have stored in memory at/near the tested
address (a bitfield flag byte/word). True raw-CR-across-calls members without
a memory backing store remain parked (fn_80141FAC).

## partial route (2026-08-23, fn_8015307C — reproduces the CR dance, parks on regalloc)

`ScriptDoFlash` (688 B, parked 73.3%) carries the long-range form: ONE
`li r0,0; cmpwi cr4,r0,0` whose cr4 result branches twice, ~90 instructions
apart, across multiple `bl`s (nonvolatile-cr4 `mfcr r12`/`mtcrf 8` save in the
prologue). A construct DOES emit the exact caching shape:

```c
cond_raw = 0;
__asm__("" : "+r"(cond_raw));   /* value becomes asm-opaque -> not foldable */
cond = cond_raw;                /* both gates test cond == 0 */
```

Placed before the first gate this produces mfcr/mtcrf + a single
`cmpwi cr4,r0,0` + two distant `bne cr4` — i.e. **the raw comparison survives
the calls** because GCC treats the opaque `cond_raw` as data, materializes it
once, and tests it per gate. The wall moves one level up: the asm-opaque value
must itself live ACROSS the intervening calls, so GCC demands a callee-saved
register for it (r30), which pushes arg1's home to r29 and cascades into frame
size, CR-slot offset and final-call load order (~46 insn diffs). Every variant
tried (plain zero folds both gates; late copy loses caching; volatile /
input-only / memory-clobber barriers; `-O1`; all ProDG versions; static-inline
helper with literal arg) fails one way or the other — full list in the draft's
PARKED comment (`src/wip/fn_8015307C.c`). A DOL-wide scan found this idiom at
exactly ONE address, so it is low-priority unless another member appears.

Refines the retry hints below: an "inlined helper param substituted
post-expansion" remains the leading hypothesis for what the original source
looked like — the barrier trick proves the *codegen* is reachable, only the
register budget is not.

## What was tried (all fail on fn_80141FAC)

- Early/late `if` orderings, inverted conditions, nested vs flat.
- Boolean temps — GCC folds them to `subfic`/`adde` arithmetic (loses the
  branch structure AND the CR save).
- `__builtin_expect`, switch dispatch, goto forms.
- Volatile/asm barriers around the compare points.
- All five ProDG versions (3.5–3.9.3) — identical behavior.

## Distinguishing from related issues

- **#16 branchy-boolean-shadow-alloc**: allocation of the boolean RESULT
  variable (r3 vs r31 with `li` in branch shadows). This issue is about
  RAW CONDITION fields surviving calls — no result variable involved.
- **#15 call-arg-setup-scheduling**: emission ORDER of arg moves. Here
  the entire CR-save prologue/epilogue pair is missing from GOT.

## Retry hints

- A source form that materializes two named bools early and branches on
  them late would need GCC to keep the COMPARISONS (not folded bools)
  alive — no known C construct does this across calls in GCC 2.95.x.
- Worth checking whether the original source used a helper macro/function
  returning two flags via reference out-params (the stores would explain
  the early tests; the late branches would be on the loaded bytes).
- If dtk ever supports per-function asm scaffolding for the next pass.text (it does
  not today), these become trivially coverable — until then every
  long-range member stays parked.

## Members

| Address | Size | Best | Blocker |
|---|---|---|---|
| fn_80141FAC | 0x7F8 | fully hand-rebuilt body | cr4/cr3 across `bl fn_801A0D50` |
| fn_8015307C | 0x2B0 | 73.3% — CR-cache shape reproduced via asm-opaque value | opaque value needs a callee-saved home → saved-reg steal cascade (see section above) |
| (pool) | — | — | 406 mfcr fns in .text, 403 unmatched — triage needed to separate short-range (matchable) from long-range members |

## Members added — (2026-08-23)

| Address | Size | Best | Notes |
|---|---|---|---|
| fn_8015B698 (ScriptGetPlayerFacePoints) | 0x160 | 81.8% w/ `-fno-schedule-insns2` | mfcr/mtcrf CR0-liveness across TWO calls in the AE20-chain block; everything else structural was cracked (hidden arg0 ×2, chained malloc idiom, field-pass args, 56-byte copy loop). Remaining 16-word diff = one register-role swap (chain result r31/walker r30 vs ngccc's r30/r31, CR-spill home follows). Exhausted creation orders, pins, wedges, volatile, walkers, schedule/GCSE flags, all five ProDG versions |

Reinforces the doc's boundary: short-range CR reuse stays matchable
(fn_80143D28 EXACT), but this member shows a LONG-RANGE case can be
*combined* with an ordinary role swap — fix everything else first so the
CR structure is the only residual before concluding #28 is the blocker.

## addition (2026-08-23)

- fn_80184170 (216B, ~75% content / low positional): arg1 is homed in r27
  and tested TWICE around two bls — cr4 preserved pre-call via
  mfcr/mtcrf 8, cr7 recomputed post-call. Every C shape tried yields either
  ONE shared compare on the unhomed param register or, when the home reg is
  pinned, NO CR-save machinery at all. Same blocked pattern as the original
  survey (conditions tested early, branched later ACROSS bls). Note the
  working counter-example remains the memory-bitfield route (§6t-2,
  ScriptCleanup/ScriptResetLevel) — check whether the tested flag could
  live in MEMORY before treating any new member as blocked.

## additions (2026-08-23, ScriptTODManager zone)

| Address | Size | Best | Notes |
|---|---|---|---|
| fn_8016F820 | 0x844 | structural rebuild | cr3/cr4 live across ~40 calls INCLUDING `blrl` vcall dispatches; also genuinely 9-param (9th arg read from caller stack `lwz r19,0x80(r1)`) |
| fn_80170930 | 0x64C | 5.3% (m2c fill + full disasm analysis) | `cmpwi cr4,r27,0` (loop-index test) live ~150 insns / 6+ bls with mfcr/stw save + epilogue restore |

**Nuance on the memory-bitfield route:** it requires a MEMORY-backed flag.
fn_80170930's distant condition is the bare loop index — written every
iteration in registers, never stored — so §6t-2 cannot apply even though a
memory location conceptually "holds" the index. Triage question refines to:
*is the tested value stored anywhere in memory around its uses?* Only then
try the bitfield form.

## data point (2026-08-24, fn_801689C8 ScriptSaveToMemoryCard)

fn_801689C8 (1476B, parked 98.1% on unrelated doc-15 words) reproduces the
full long-range CR machinery in **plain C with no asm and no flags**:
prologue `mfcr r17` + `mtcrf 0x80,r17` for a flag condition, PLUS
callee-saved `cmpwi cr2/cr3/cr4` results cached ~170 instructions across
~10 intervening `bl`s. It fell out free once the source structure was right —
no bool temps (those fold to subfic/adde), just naturally-ordered conditions
consumed far from their tests.

**Lesson: before attributing a park to doc-28 CR liveness, first build the
rest of the body to ground truth — the CR cache dance may simply appear when
the surrounding regalloc matches.** The genuinely blocked members are those
where CR fields are tested ~20 insns after their compares across calls AND
the rest of the body already matches otherwise.

## update — PARTIAL CRACK (2026-08-23): single-invariant members

TWO members this round reproduced the long-range CR machinery from PLAIN C,
no bitfield/memory trick needed:

- fn_80186624: single `cmpwi cr4,r26,0` shared with a distant `beq cr4`
  across ~10 bls, incl. mfcr r12/mtcrf 8 and the 0x38 frame — fell out of
  plain C once an m2c comma-call rendering bug was repaired (AGENTS.md
  §7a-132). The tested value lives in a callee-saved GPR (param home).
- fn_801875CC: loop-invariant condition tested pre-loop, consumed post-call
  (`cmpwi cr4` hoist + mfcr/mtcrf prologue) — also plain C.

REFINED RULE: doc-28 splits by SHAPE now — (a) single invariant condition
with its value homed in a saved-reg/param: try plain C FIRST (both halves of
this split have now matched plainly); multi-condition or re-tested-twice
variants remain blocked (fn_80184170); (b) conditions tested early
and branched much later across multiple calls with intervening clobbers:
still blocked unless the flag can live in MEMORY (§6t-2 route, proven twice).

## avoidance recipe (2026-08-24)

**Memory-reload compares prevent cr3/cr4 pairing even with NO calls between
the tests.** fn_8017C2CC showed adjacent hash equality tests getting cached
into shared CR fields (mfcr/mtcrf machinery) purely from register-resident
operands; forcing each test to RELOAD its operand from memory between the
compares keeps every compare independent and drops the CR-save entirely —
cheapest dodge yet, works mid-function, no bitfield struct needed. Triage
order is now: (1) can the tested value live in MEMORY at all (§6t-2)?
(2) reload it per-test to stop CR caching (this recipe); (3) only then treat
long-range CR liveness as blocked.

## addition (2026-08-23, fn_8018C580)

| Address | Size | Best | Notes |
|---|---|---|---|
| fn_8018C580 (goal-manager hash dispatcher) | 0x450 | 58.3% w/ `-fno-schedule-insns` | 1104B; TWO mfcr/mtcrf sites, both reproduced structurally; residual = saved-reg role rotation (case-A value web wants scratch r9; freeing it shifts all roles into place) COMBINED with CR-liveness block placement at both sites. All semantics cracked first (chained fn_8009FDD8/fn_801745B4, fn_80126EAC(fn_80019D08(8)), s16 vcalls ×5, unsigned case compare, inverted if/else layout). Full-web pins collapse per AGENTS.md §6y-125; nested-scope decls collapse the body |

Second independent confirmation of the lesson: in big multi-site
members, fix every non-CR artifact first and treat #28 as one of TWO
residual walls, not the sole blocker.

## +61 members (2026-08-24)

- fn_8017C2CC (1576B, 34.3%): cr3/cr4 pairing on adjacent hash tests — SOLVED
  as blocker via the memory-reload compare recipe above; residual park is
  saved-reg role rotation.
- fn_801A8A6C (876B, 6.8%, entity zone): want does mid-function
  `mfcr r30` / `mtcrf 0x80` around cr0 after an early flag test; ngccc parks
  that test in callee-saved cr4 instead (+8 frame, every GPR role shifts).
  Resisted nesting/else-chain/u32-flag/sched flags across a full hand rebuild
  of all 219 insns — memory-reload route not applicable (flag is computed,
  never stored by the original either). Full signature + 10 callee arities in
  the draft header.

## additions (2026-08-24)

- fn_80196EF8 (parked ~11% on multi-cause regalloc): cr4 `(created1 != NULL)`
  cache lives live across UI blocks 1–3 with mfcr/mtcrf save/restore — one of
  several coexisting walls there, see its header for the full map.
- fn_801979CC (parked 40.8%): CR4-across-calls fell out NATURALLY from the
  reconstructed body (no CR-specific work needed) — further evidence the CR
  machinery itself is usually not the blocker; fix the rest first.

## addition (2026-08-25, 0x801F34F4–0x801F6684)

- fn_801F5218 (144B, **EXACT**) — **second plain-C positive for doc-28**:
  out-param is a *callee-written HANDLE* (`mgr`/`sp8` block). Splitting
  `idx` vs `j` into separate counters and recycling early `pOut=&sp8` as
  `idx` makes `gcc` emit the `mfcr rX / mtcrf 0x80` + `cmpwi cr4` block
  across `loop2`'s `bl`s with *no* `__asm__` and no flags. When a Plain-C
  split-handle shape works, the CR cache is simply the consequence of
  lifetime — not a wall. Reinforces the lesson from `fn_801689C8` / `fn_801F5218`:
  **build the rest of the body to ground truth first; the CR dance may appear
  on its own.**

## contrast-case WIN (2026-08-24, fn_80219FE0 EXACT)

When want's CR-save spans only ONE loop, plain structure beats mfcr
emulation: keeping the loop-invariant condition in a SEPARATE temp (not a
param write-back) lets GCSE hoist `(arg1 != 0)` into cr4 across the loop,
and declaring the magic constant as the FIRST body statement makes LICM
sink it into want's exact `[bge][lis][cmpwi cr4][ori]` window. Reinforces
the doc's boundary: check for single-loop spans and try pure C structure
before concluding #28 is the blocker.

## addition (2026-08-25, Script*-command zone)

- fn_80224E28 (908B, parked 30.0% on an unrelated single node↔flags register
  swap cascade): the `mfcr`+`mtcrf` CR-save block FELL OUT OF PLAIN C — third
  plain-C positive (after fn_801689C8 and fn_801F5218). Full disasm rebuild
  (frame/stmw/chained allocs/u16 field dance) was done first; the CR machinery
  appeared on its own. Reinforces the standing lesson: build the body to ground
  truth before ever citing doc-28 as the blocker.
