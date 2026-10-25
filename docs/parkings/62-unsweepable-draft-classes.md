# 62 — Unsweepable draft classes (pool hygiene)

**Status: open (harness/process wall, not a codegen wall).** No body edit can
move these drafts, yet they are indistinguishable from ordinary non-matching
drafts if the candidate pool is built by grepping for the word *park*. They
therefore get re-picked by every residual-ranked sweep, score 0.0 forever, and
consume the sweep budget that the real near-misses need.

**Tool: `tools/sweepable_pool.py`** builds the pool with the exclusions below
(`--stats` to print the breakdown). Prefer it over
`grep -L -iE '^//.*park' src/wip/*.c`.

## The five classes

| class | tell in the draft | why no body edit can help |
|---|---|---|
| **promoted** | `src/fn_<addr>.c` exists | already matched; the scorer skips it, but pool builders that only glob `src/wip/` do not |
| **parked** | a leading `// ...park...` comment | human/agent decision — but note the grep only works if the note literally contains the substring `park` |
| **stub** | `family=stub` | the file holds **only the raw disassembly as comments and no C statements**. It compiles to an empty object, so it scores 0.0 *by construction*. Writing it is author work, not sweep work |
| **untestable** | `Status: UNTESTABLE` + `FRAGMENT:` | the address is in no `report.json` unit — it lies strictly inside a neighbouring function |
| **unlabeled** | `UNLABELED:` | no `symbols.txt` function symbol claims the region, so `check_markers` blocks any promotion even at 100 %. Also covers *data* regions the generator misread as code |

Counts at 2026-09-15 over 3,348 wip drafts: parked 260, untestable 38, stub 14,
unlabeled 2 → **3,034 sweepable**.

## The `untestable` mechanism, precisely

`tools/test_wip_drafts.py::test_one` gets the wanted length from
`report.json`:

```python
want = _want_sizes().get(addr, len(got))     # ← the fallback is the problem
orig = gl.d[gl.t_off + (addr - gl.t_addr) : ...]
```

For an address no unit owns, `want` silently becomes `len(got)` and the "want"
bytes are a **slice of the enclosing function**. A draft at such an address can
therefore even reach 100 % — as a *prefix of somebody else's function* — while a
promotion has nothing to attach the symbol to. These need a symbols/split fix
first; a body is beside the point.

In this pool the 38 `untestable` members all sit inside one of the six large
`0x80123xxx` / `0x80124xxx` / `0x80125xxx` runtime functions (for example
`0x801238A8` is inside `fn_80123864` (212B), `0x80124480`–`0x80124B6C` are all
inside `fn_80124478` (1820B)).

## The `stub` class in `.init`

The seven `0x80003100`–`0x80003468` drafts look like a different wall but are
not. All seven **are** `report.json` boundaries — they are the
`main/auto_00_80003100_init` unit, i.e. the region below `TEXT_START`
(`0x800034A0`). The harness's offset arithmetic still lands on the right bytes
by luck: the DOL places `.init` immediately before `.text`, and
`t_off + (addr - t_addr)` resolves through it.

They are parked because they are `family=stub` (**no C body at all**), and
because the spans are raw-asm blobs — early-init `lis r1` / `mfmsr` / `mtspr`
sequences, with `0x80003254` (108B) containing an interior `blr`, i.e. it merges
two functions that no single C function can reproduce. `0x80003464` is the
exception: a 4-byte empty `blr` leaf that is genuinely **EXACT** and simply has
no registration path (recorded earlier as *"4B empty fn below TEXT_START, not
promotable"*).

## Related

- `0x802572C4` (20B) is **data**, not code — its first word `0x3F3504F3` is the
  IEEE754 bit pattern of a float, and the symbol table labels it
  `lbl_802572C4`.
- `0x8025D010` (3940B) is an unclaimed runtime-lib region already audited
  against branch escapes; it contains 24 interior `blr` (≥ 25 functions).

## Addendum 2026-10-08 — three phantom gap spans (drafts deleted, PARKED)

`gen_wip_drafts.py` mints a `fn_<addr>` stub for every report.json unit the
match list does not own — including units dtk manufactured around bare `lbl_`
gap symbols. Three such phantoms (all `symbols.txt` labels, none a function)
were re-reported 2026-10-06/08 as "unmatchable, need a split fix". Verified
against the original DOL and removed (`src/wip/fn_*.c` deleted, `WIP.md` rows
dropped, addresses added to `PARKED` in `tools/gen_leaves.py` so neither
generator resurrects them). Do NOT re-create drafts for these addresses:

| addr | gap | bytes are | evidence |
|---|---|---|---|
| `0x8024FD8C` | 4B between `fn_8024FAD0` end and `fn_8024FD90` start (`blr` at `FD88`) | float `0.5f` (`3F000000`) pool word | `symbols.txt` already `lbl_... data:float`; consumer is `fn_8024F9CC`'s call sequence |
| `0x802575C4` | 8B between `fn_802572D8` end and `fn_802575CC` start (`blr` at `575C0`) | paired-single `(-1.0f, +1.0f)` (`BF800000 3F800000`) owned by `fn_802575CC` | consumer does `lis r8,-0x7fdb / addi r8,r8,0x75c4 / psq_l f18,0(r8)`; cf. doc-06 |
| `0x8025AD34` | 48B head (`AD34–AD64`) of the `AD34–AE38` hand-asm restore routine ending in `rfi` | `li/lwbrx/mfmsr/mtmsr` + PI/VI pokes + `mtcrf/mtlr` context restore — ngccc-unemittable | dual vtable entries (`data-vtables.tsv`: slot 5 = `AD64`, slot 14 = `AD34`); needs an *asm* unit, never a C re-pick |
| `0x802572C4` | 20B pool (`C4–D8`) before `fn_802572D8` (`blr` at `C0`) | float data (`3F3504F3` = 0.7071…) — the draft's "instructions" are capstone mis-decodes plus the *next* function's paired-single body | `symbols.txt` already `lbl_... data:float` (cf. Related above); draft deleted 2026-10-08 |
| `0x8028E038` | 8B of zeros, last bytes of `.text` (`sec1` ends `8028E040` = `.rodata` start) | section trailing pad — not even a pool (WIP.md note already named it `pad_01_8028E038_text`) | nothing to wire; draft deleted 2026-10-08 |

"Split fix first" applies to none of them: the two pool words are correctly
labeled data in auto-covered gaps, and `AD34` is correctly a `lbl_` second
entry point (vtable slot 14 references it and already builds). The genuine
future split work nearby is wiring `fn_802575CC` et al. (`splits.txt` jumps
`575C4→58840`, ~13 function symbols unwired) once the FPR blocker clears.

## Addendum 2026-09-15 (m) — the *other* half of pool hygiene: the pool was
## 44 % too small

Excluding non-sweepable drafts is only half the job; the pool also has to be
*complete*.  The pools used by every sweep up to and including 2026-09-15 held
**1,748** addresses.  Rebuilding it from scratch (`tools/sweepable_pool.py`)
gives **3,034**, and after removing the 1,748 already known there are **1,338
sweepable drafts that had never been scored** — not FAILs, not huge, just never
selected.

Scoring all 1,338 with `tools/score_addrs.py`:

| status | count |
|---|---|
| EXACT | 3 |
| NEAR | 479 |
| DIFF | 853 |
| FAIL | 3 |

The NEAR tail is far richer than the old pool's: `0x801CE65C` 99.0,
`0x801A71DC` 99.0, `0x80167E04` 98.9, `0x801575E0` 98.9, `0x8020CAA4` 98.7,
`0x801903B8` 98.6, `0x801025D0` 98.6 — i.e. **a whole second worklist that
docs 56/59/60 declared "exhausted" without ever having seen it.**

Re-running only the doc-56 prototype sweep over the new addresses yielded 136
improvements and **3 promotions** (`fn_80118104`, `fn_800E448C`, `fn_800DF5B4`;
see the doc-56 addendum).  The two other EXACTs, `0x8001DFF4` and `0x801D2C58`,
are the already-documented doc-51 reloc-target and doc-50 linker-relaxation
blockers, and `0x801B5A54` is the parked SN-asm `bdnz $` case.

**Rule for future rounds:** build the pool with the tool, print `--stats`, and
record the count in the sweep note.  "Exhausted" is only meaningful relative to
a stated pool.
