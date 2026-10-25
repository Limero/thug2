# Issue 13 — mwldeppc silently drops an object at an auto-asm boundary

**Status: MECHANISM SOLVED (2026-08-23) — it is reachability-based dead-strip
GC, not a seam/alignment/section-flags bug, and a legal in-repo mitigation
exists.** A minimal repro built entirely from ngccc objects + adapted LCF +
`wibo .../GC/1.3.2/mwldeppc.exe -fp hardware -nodefaults` proved both
directions: unreferenced objects vanish SILENTLY; referenced ones (one `bl`
flipped) are retained AND placed correctly. The "seam" was coincidence: a
full-DOL scan finds ZERO references to 0x8025254C (no bl, no literal) — it is
a true orphan function; content/symbol/position insensitivity follows
naturally.

**Mitigation (verified in repro):** list the symbol in the linker's
FORCEACTIVE block. The repo knob already exists — `config/G2TE52/config.yml`
`force_active:` (its 37 entries map 1:1 to the generated ldscript.lcf
FORCEACTIVE lines; same mechanism already retains GXGetOverflowCount, another
unreferenced 8B object). Fix = add `fn_8025254C`. Note: `#pragma force_active`
inside the OBJECT did NOT survive this invocation (tested) — mitigation must
be at config.yml/LCF level.

**STATUS NOTE (2026-08-26 audit): the mitigation is still NOT executed
in-repo.** `tools/gen_leaves.py` still carries `PARKED = {0x8025254C}` and
`config.yml force_active:` does not list the symbol — the range remains under
auto-asm coverage. Applying the fix means: add `fn_8025254C` to config.yml,
remove it from the gen_leaves PARKED set, rebuild, and `cmp`-verify the DOL.

**Verification 2026-08-29:** Full `wibo` + `GC/1.3.2/mwldeppc.exe 2.4.2` + `ProDG/3.9.3/ngccc -O2 -G0` repro with adapted `ldscript.tpl:23` `FORCEACTIVE` proves GC (not seam): **orphan no FORCEACTIVE → dropped silently (output 456B, no symbol)**, **orphan + `FORCEACTIVE {fn_8025254C}` → retained (552B at `0x80003008` with `38600380 4e800020` = `li r3,0x380; blr`)**, **entry calls orphan → retained via reachability (584B with `bl`)**. `config.yml:39` has 36 `force_active` entries (text says 37 — off by one), `symbols.txt:10595` `fn_8025254C = .text:0x8025254C; // size:0x8` (`c` leaf `return 896`), `splits.txt` gap `0x80250EAC->0x80252C00` is the current auto-asm workaround. Fix that was tested: add `fn_8025254C` to `config.yml force_active:` (→ 37 entries, `ldscript.lcf` `FORCEACTIVE` block) and clear `tools/gen_leaves.py:54` `PARKED=set()`, then `gen_leaves.py` emits `s32 fn_8025254C(void){return 896;}` → split `0x8025254C-0x80252554`; verify via `python3 configure.py --dtk tools/dtk --ninja tools/ninja && tools/ninja build/G2TE52/main.dol && cmp orig/G2TE52/sys/main.dol build/G2TE52/main.dol && sha1sum build/G2TE52/main.dol` (`ff6faeb0f2…`). `#pragma force_active` inside object does NOT survive — must be `config.yml` LCF level.

**CONFIRMED SECOND INSTANCE (2026-09-02): `fn_8025A248` (16B, NS ctx-pointer
fn).** Its C promotion silently broke the whole build: linked .text lost
0x10 bytes, every symbol from 0x8025A258 upward shifted -0x10, r2/r13 patch
targets and .sdata moved, ~39886 DOL bytes differed. Symptom was misleading —
the parked note blamed the file-scope global register `__asm__` vars, but a
plain `#pragma force_active on` in the object ALSO failed (dropped anyway,
consistent with the repro) and a full DOL/ELF/asm scan found ZERO references
(bl or literal) to the fn: it is dead code in retail that only survived
because it shared a unit with referenced neighbors. Diagnosis recipe that
worked: rebuild w/ `nm main.elf | sort`, diff symbol addresses against
`symbols.txt` (`SHIFT` walk), the first shifted symbol sits right after the
orphan; `grep` the object off `main.elf.rsp` (still listed) and `nm` the ELF
(symbol absent) — drop, not misplacement. Current workaround: delete
`src/fn_8025A248.c` so dtk auto-assembles `asm/fn_8025A248.s` (`dtk elf
fixup` exports its symbol) — DOL byte-identical (`ff6faeb0f2…`). Same
permanent fix as above applies: add to `config.yml force_active:` and restore
the C unit. The same cause likely applies to its parked twins fn_8025A5FC /
fn_8025A1D0 (NS ctx-pointer family) if anyone tries to promote
them.

---

# ORIGINAL ANALYSIS (historical)

**Status:** PARKED (as of M4.9x; park set is a moving target — re-verify before trusting) (1 address: 0x8025254C)

## The problem

`mwldeppc` (Metrowerks GC/1.3.2 linker, used by dtk-template) **silently
drops an 8-byte object** placed at the boundary between two auto-generated
asm ranges in the DOL text section, regardless of the object's content,
symbol name, or position. The DOL then shifts by 8 bytes and the byte-
identity check fails.

- The 8-byte range around 0x8025254C sits exactly at the seam of two
  `auto_XX_8025..._text` split ranges.
- Any C function whose split covers that boundary is dropped by the linker
  with no error — the build "succeeds" but `cmp` shows a DOL difference.
- Verified 2026-08-08 (documented in `tools/gen_leaves.py`): content,
  symbol, and position variations all reproduce the drop.

## Why it's parked

- It is a **linker/toolchain bug**, not a codegen problem: no C source can
  fix a linker that discards the object.
- Mitigation in-repo: the split is removed so the auto-asm covers 0x8025254C
  again (`gen_leaves.py` `PARKED = {0x8025254C}`), keeping the DOL
  byte-identical.

## What was tried

- Reordering splits, renaming symbols, changing the covered range start/end
  by ±1 word — all dropped.

## Research directions for an external AI

1. Investigate dtk-template's `mwldeppc` usage: how `.text` sections from
   split objects are concatenated and where the boundary-drop could come from
   (likely an alignment/`-align` mismatch: if the second auto-asm range
   requires 8-byte alignment and the object fills 4 bytes of a gap, the
   linker may round it away).
2. Check whether the drop is caused by the object's section flags vs the
   auto-asm sections (`.text` vs `.text.startup`, etc.) — a `-section
   .text,0x80252540` directive mismatch could make the linker place it
   elsewhere or discard it.
3. If dtk's `dol split` output for that boundary has a duplicate/overlap
   (both ranges claim the same byte), fix the split generation instead.
4. **Cross-clone lead (2026-08):** tww is the only other local clone
   (`~/ai/tww`) that shares mwldeppc **GC/1.3.2** with this
   project — it can serve as a same-linker-version testbed for reproducing
   the drop (e.g. the same splits.txt boundary shape). bfbb (GC/1.2.5n),
   mkdd (GC/2.6) and tp (Wii/3.0a3) use different mwld versions; the other
   clones (thug2's game code itself, snap IDO) don't use mwldeppc at all.
5. **dtk mechanism alternative (2026-08, plan Item F):** nfsmw's
   keep.lst mechanism is ngcld-specific (their linker is SN's, not
   mwldeppc) - NOT transferable. For mwldeppc, the retention knobs are
   dtk's per-object `force_active`/`export_all` split options and the
   `.comment`-section presence rules (`nfsmw/docs/comment_section.md`):
   an object whose symbols are all considered dead gets dropped by
   mwld's unreferenced-symbol GC. If the boundary-drop is really
   ref-GC (not section alignment), marking the split
   `force_active` should retain the 8 bytes - worth one test before
   accepting the linker-bug theory.

## Where to look

- `tools/gen_leaves.py` `PARKED = {0x8025254C}` (with the full verified note).
- Build pipeline: `config/G2TE52/splits.txt`, `configure.py` (auto-asm
  ranges), `build/G2TE52/main.dol` vs `orig/G2TE52/sys/main.dol` (`cmp`).

---

## 2026-09-02 — CONFIRMATION: force_active generalized to 6 orphans

The diagnosis (orphan fn_8025A248 deadstripped; config.yml
`force_active:` fix) was generalized: a retail-DOL reference scan over all
EXACT wip candidates found **6 orphans** — 0x8025A248, 0x8025A5FC (twins),
0x8013A744, 0x8013A8D0, 0x8013A9FC, 0x802245A4. All 6 were promoted as C
units with their symbols in `config/G2TE52/config.yml force_active:` and the
DOL stayed byte-identical (`ff6faeb0f2b5…`). All ~29 other promotions that
session linked clean — the old ".sdata2 +0x40 blocker" was these orphans'
fragile tail region plus stale draft flags, not a global wall.

**Mechanism caveats (learned the hard way):**
- `python3 configure.py` alone does NOT rewrite
  `build/G2TE52/ldscript.lcf`. The .lcf is regenerated by dtk during
  configure *when it rewrites build files* — the reliable flow after editing
  config.yml is `python3 configure.py --dtk tools/dtk --ninja tools/ninja`
  followed by an actual build step (e.g. `tools/ninja build/G2TE52/main.dol`
  or a promote run, whose add_gen_leaves+reconfigure does it).
- dtk's YAML reader mishandles inline `#` comments on the SAME line as list
  items in `force_active:` — put comment lines on their own lines ABOVE the
  list block.
- Verify the symbol actually landed: `grep fn_XXXX build/G2TE52/ldscript.lcf`
  (FORCEACTIVE block) AND `powerpc-eabi-nm main.elf | grep fn_XXXX` after
  linking. nm-shift walk + rsp-listed + ELF-absent = this doc's deadstrip
  signature.

---

# SOLVED 2026-09-02 — mitigation EXECUTED in-repo; doc closed

The last open item from the 2026-08-26 audit is done. The original orphan
**fn_8025254C** (8B leaf `return 896`) is now a normal C unit:

- `config/G2TE52/config.yml force_active:` lists `fn_8025254C`
- `tools/gen_leaves.py` `PARKED = set()` (empty — the stale "boundary drop"
  theory comment removed; keep the set only for genuine future cases)
- `tools/gen_leaves.py` regenerated `src/fn_8025254C.c`; registered +
  rebuilt via `tools/register_build.sh`
- Verified: `nm main.elf` → `8025254c T fn_8025254C`, FORCEACTIVE present
  in `ldscript.lcf`, **DOL byte-identical** (`ff6faeb0f2b5…`)

Session tally for this mechanism: fn_8025254C (original), fn_8025A248 +
fn_8025A5FC (twins), fn_8013A744, fn_8013A8D0, fn_8013A9FC, fn_802245A4 —
7 orphans total retained via force_active, all DOL-verified.

**Remaining non-solved caveat (NOT doc-13):** twin `fn_8025A1D0` (120B,
NS-family ctx-pointer) is still a ~80% parked draft in `src/wip/` for
*codegen* reasons (caller-r31 global register var + andi. dead-web), not
linker reasons. When it ever goes EXACT, promote it with its symbol in
config.yml force_active per this doc.

---

## 2026-09-25 — THIRD VARIANT: "cross-unit branch" orphans (dtk emits a raw
displacement, so retail's own callers do not reference the symbol)

`fn_8025B180` (448B MetroTRK FP/PS restore) is **the first orphan whose
retail callers exist** — the earlier seven were true dead code. It was still
dead-stripped, and the reason is a dtk disassembler detail worth knowing:

```
build/G2TE52/asm/auto_01_8025B340_text.s:255  bl fn_8025B340      <- same unit
build/G2TE52/asm/auto_01_8025B340_text.s:256  bl -0x578           <- target 0x8025B180, BEFORE the unit's start
build/G2TE52/asm/auto_01_8025B340_text.s:597  bl -0xa68           <- ditto
```

Retail's two call sites (0x8025B6F8, 0x8025BBE8) sit in the *next* auto-asm
unit; their target lies **behind** the unit's start, and dtk emits those
branches as literal relative displacements with **no relocation and no
symbol name**. (Forward cross-unit targets ARE named — compare
`auto_01_8025AC18_text.s:120  bl fn_8025AFC0`, which links fine because the
symbol reference keeps the object reachable.)

**Diagnosis signature** (same as the others, but the scan must include this
case): `grep -c fn_X build/G2TE52/main.elf` → 0 while
`grep -c fn_X build/G2TE52/main.elf.rsp`/`build.ninja` shows the object IS in
the link; the DOL is short by exactly the function's size and
`patch_dol.py` trips `Init r2 setup computes 0x803D2DC0, expected
0x803D2F80` (the shift equals the missing size). Decisive tell:
`grep -rn "fn_X\b" build/G2TE52/asm/*.s` — if the only hits are the function's
own unit (or stale superseded units), and any real caller shows as
`bl -0xNNN`, it is this variant. Cheap confirmation: hand-add the symbol to
`build/G2TE52/ldscript.lcf`'s FORCEACTIVE block and relink with
`wibo .../mwldeppc.exe -fp hardware -nodefaults -lcf <lcf> -o /tmp/t.elf @<rsp>
(rebuild the rsp from build.ninja's `main.elf` edge, or
`tools/ninja -t commands build/G2TE52/main.elf`)`; the symbol appears in the
ELF and the raw displacements still resolve, because the layout is byte-exact.

**Fix (executed):** `- fn_8025B180` in `config/G2TE52/config.yml`
`force_active:` with the comment above it; then re-promote. DOL byte-identical
(`ff6faeb0f2b5…`).

## 2026-09-25 — related: promoting a `.init` function

`fn_80003334` = `__OSFPRInit`, a 304B `.init` leaf (0x80003334-0x80003464)
that had been "intentionally not promoted" for years. Two things were wrong
with the obvious route, and one extra knob fixes it:

1. `tools/promote_wip.py` refuses addresses outside `.text`, so the
   registration is manual: a `\t.init       start:… end:…` block in
   `config/G2TE52/splits.txt` (place it **after** the whole `Sections:` list,
   not inside it) plus an `Object(Matching, "fn_80003334.c", …)` line in
   `configure.py`. A range marker `range=0x…-0x…` in the source header is
   still required so `add_gen_leaves.py` recognises the file (it only ever
   rewrites *missing* entries, so a hand-written `.init` block survives).
2. dtk's `.init` claim alone does **not** move the C object there: the object
   emits a `.text` section (its symbol landed at the END of `.text`,
   0x8028DF10, and the DOL grew 32B).
3. **Fix:** put the code in the right section yourself —
   `__attribute__((naked, section(".init")))` on the definition. Probed:
   ngccc 3.9.3 emits a real `.init` section (SHF_ALLOC|SHF_EXECINSTR) for it,
   the LCF's leading `.init ALIGN(0x4):{}` collects it, and the unit is placed
   first — DOL byte-identical.

Unlike the orphans above, no `force_active` entry was needed: the unit's own
`auto_00_80003100_init.s` calls it *forward* (`bl fn_80003334` at 0x8000311C),
which dtk does name.

## 2026-09-25 — the `force_active:` entry must use the REAL symbols.txt name

Three more orphans promoted the same day, and the first attempt failed with the
identical signature (`.text` 0x4C short, `patch_dol`'s `Init r2 setup computes
0x803D2F40, expected 0x803D2F80`, every symbol after the void shifting by the
missing byte count). The `force_active:` entries had been written from the
**split key**, not from `symbols.txt`:

| split key (wrong) | real symbol (needed) | source |
|---|---|---|
| `fn_80274A78` | `__save_gpr` | `.text:0x80274A78; size:0x4C scope:global` |
| `fn_8025ABC4` | `Vtable0x80308A40_m17` | `.text:0x8025ABC4; size:0x28 scope:global` |
| `fn_8025ACDC` | `Vtable0x80308A40_m19` | `.text:0x8025ACDC; size:0x58 scope:global` |

`force_active: fn_80274A78` is a no-op — mwld keeps symbols, and there is no
such symbol. Diagnosis that pins it in one command:

```sh
build/binutils/powerpc-eabi-nm build/G2TE52/main.elf | grep -i 80274a
# 80274a78 T __restore_gpr      <- the WRONG unit got packed down into the hole
# 80274ac4 T fn_80274B10        <- and everything after is -0x4C
```

The give-away is a **plausible-looking symbol at the wrong address**: mwld
places input sections sequentially (the LCF has no fixed addresses), so a
single dropped input section shifts every later symbol down by exactly its
size. Compare a symbol's address against `symbols.txt` — if the whole tail is
offset by one function, that function is the dropped one, and the name in the
`nm` line is the *next* function, not the missing one.

Two more notes from this round:

- `Vtable0x80308A40_m17` / `_m19` are already referenced from `src/vt_80308A40.c`
  (`(void *)Vtable0x80308A40_m17,`), so once the split names match the symbol
  names they link without any `force_active` entry at all. The failing batch
  was caused by `__save_gpr` alone; the other two only needed clean promotion.
- `__save_gpr` is expressible as C without transcription: file-scope
  `register unsigned int save_rN __asm__("rN")` for r11 and r14-r31 binds the
  operands to the *incoming* registers, and zero-width
  `__asm__(".globl _savegpr_14\n_savegpr_14:")` directives preserve the
  `_savegpr_14..31` jump-in labels. ngccc only warns ("call-clobbered register
  used for global register variable"), and the object's `.text` is exactly
  0x4C with no `.rodata`. This supersedes doc 45's "not expressible in C"
  verdict for the save half; `__restore_gpr` (0x80274AC4) is the same shape.
