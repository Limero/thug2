# GameCube Matching Decompilation — Setup Plan

**Status: historical — milestones below end at M4.15; for the current matched
count see `PROGRESS.md` (85%+ and climbing), for later history see `WIP.md`
and `AGENTS-recipes.md`. The DOL builds byte-identical.**
**Date:** 2026-08-07 (setup executed; historical sections frozen at M4.15)

> **Agents: read `AGENTS.md` first** — it is the operational handoff (commands, tool
> inventory, environment quirks, next steps). This file is the plan/history/risks.
**Approach:** Matching decompilation via `decomp-toolkit` (dtk) + `dtk-template`
**Target game:** Tony Hawk's Underground 2 (USA) — GameCube — Game ID `G2TE52`
**Compilers:** mwcc GC/1.3.2 for CRT/runtime + **SN Systems ProDG ngccc (GCC 2.95.2) for game code** (see §5)

---

## 1. Goal

Produce a **rebuildable, byte-identical** copy of a GameCube game's `main.dol` (and `.rel` overlays) from
C/C++ source, using the same Metrowerks CodeWarrior compiler the original was built with. The
"matching" methodology means:

- **Day one:** the project builds a DOL that is hash-identical to the original — a runnable game.
- **Throughout:** each function decompiled to C is verified by compiling it and diffing against the
  original assembly. The binary stays byte-identical the whole time.
- **End state:** 100% of the code is readable C; the game builds purely from source, and can then be
  *modified* (FPS unlock, widescreen, etc.) with full control.

Correctness is machine-checked at every step — you can't silently write wrong code.

---

## 2. Environment (as executed)

| Item | State |
|---|---|
| OS | Fedora 44, x86_64, 8 cores / 31 GB |
| dtk | ✅ v1.8.3 in `tools/dtk` |
| ninja | ✅ v1.13.2 in `tools/ninja` |
| Python venv | ✅ `tools/venv` (pip bootstrapped via get-pip.py — `ensurepip` broken on 3.14) |
| m2c / asm-differ / capstone | ✅ installed in `tools/venv` |
| wibo + CodeWarrior GC 1.3.2 | ✅ auto-downloaded to `build/compilers` on first build |
| Game image | ✅ `orig/G2TE52/game.rvz` (lossless, user-supplied) |

---

## 3. Project layout (as executed)

```
thug2/
  orig/G2TE52/game.rvz      disc image (gitignored); main.dol extracted to orig/G2TE52/sys/
  config/G2TE52/
    config.yml              dtk project config
    splits.txt / symbols.txt  analysis output (edited: .rodata2 rename, __start)
    build.sha1              hash check: ff6faeb0... == original main.dol
    ldscript.tpl            custom LCF (fixes _stack_end mis-attribution)
  tools/                    dtk, ninja, venv, patch_dol.py, replace_dol.py, dolphin-cli.sh
  src/                      (empty — C source to be written)
  configure.py, build.ninja (generated), build/ (outputs, gitignored)
```

---

## 4. What it took to reach a byte-identical DOL (the interesting part)

The stock dtk-template analysis does **not** produce a matching DOL for this game out of the box.
Five issues had to be fixed; the last one is the deep one:

| # | Issue | Fix |
|---|---|---|
| 1 | Control-flow analysis stalls on Neversoft computed jump tables (`mtlr r0; blrl`) — *overlapping functions* at 0x8025B92C | `skip_cfa_ranges` in `config.yml` |
| 2 | Two `.rodata` sections (DOL sec 7 + 8) → dtk's *Multiple sections with name .rodata* | rename second to `.rodata2` in `splits.txt` + relabel symbols |
| 3 | Linker: undefined `__start` (mwld default entry) | label DOL entry 0x80003100 `__start` in `symbols.txt` |
| 4 | 862 differing bytes: init r2 = 0x803D2F80 instead of 0x803E2280 | custom `ldscript.tpl` (see below) |
| 5 | 429 instructions access section 11 via `r2` instead of `r13` | `tools/patch_dol.py` post-link patch |

**Root cause of #4/#5:** the original was compiled with `-sdata2 0` — *all* small data, including the
constant pool (DOL section 11 @ 0x803CAF80), is addressed via r13 (SDA base 0x803D2280). dtk's
analysis only sees read-only + small-data-addressed, so it classifies that region as `.sdata2`, which
makes mwld emit r2-based accesses against its computed `_SDA2_BASE_ = 0x803D2F80`. The two bases
differ by exactly `0xD00`, so the post-link patch rewrites each r2-based access to r13 (+0xD00 on the
displacement, target address unchanged) and fixes the init's r2 setup. The patch only touches
instructions whose resolved target lies inside the sdata2 region (0x803CAF80–0x803CC200), so
embedded data in `.text` is never corrupted. The custom LCF fixes one more mis-attribution: the
init's `ori r5, r5, lo(0x803CAF80)` was resolved against `_stack_end` (dtk tracker guessed
stack_end = 0x803CAF80); the template pins `_stack_end = 0x803CAF80`.

Both fixes are deterministic and part of the build (`patch_dol.py` runs in the `elf2dol` ninja rule;
`ldscript.tpl` is referenced from `config.yml`). The patch script is also hardened: it fails fast if
the init's r2 setup doesn't compute the expected base, validates the DOL entry point, skips FPU
offsets vs GPR offsets correctly, and only touches targets inside the sdata2 region. (One bug was
caught in final verification: the r2-setup scanner was missing its loop increment and could spin
forever — fixed with `pos += 4`.)

**Verification (M2):**
```sh
cmp orig/G2TE52/sys/main.dol build/G2TE52/main.dol   # identical
sha1sum build/G2TE52/main.dol                         # ff6faeb0f2b524ecbe1aeaff78ff154a284c27c9 ✓
ninja                                                  # "build/G2TE52/main.dol: OK" hash check
```

---

## 5. M3 — first matched function & the compiler discovery (the good part)

> **SDK library version (not the compiler):** see `docs/dolphin-sdk.md`. thug2
> links Dolphin SDK `0x2301` — a Sep-2002 base with OS/GX/AX/EXI updated
> Feb–Mar 2003 — while the in-repo `libs/dolphin` is tp's 2004 build (a superset;
> revert to match).

**Result: `src/fn_800034A0.c` (RNG state init; now merged into `src/rng.c`)
compiles byte-identical to the original — objdiff fuzzy 100.0%, relocation
layout identical, DOL hash unchanged (`ff6faeb0…`).**

But it took a while, and the lesson is important for this game **and** for any
2003–2005 game that won't match:

### 5.1 The mystery: `lis+ori` constants

The first function loads constants like `0x12B9B0A1`. The original loads high half 0x12b9 into r0 and then ORs in low half 0xb0a1 into the same register.

The whole `.text` uses this **unsigned** constant form 18,212 times (vs 10,404
`lis+addi`). But **every** mwcc version (GC/1.0 → 4.x, `-O0` → `-O4,p`,
`-schedule`, `-opt level=…`, all source shapes, `u32`/`s32`) emits the **signed**
form `lis/addi`. We swept every flag and version in the archive for days-worth of
CPU and nothing matched — same instructions, different encoding, different
scheduling.

### 5.2 The answer: ProDG

Two clues broke it:

1. The DOL contains the literal string **"Please See the ProDG manual"** — the
   runtime's error text. SN Systems **ProDG** was Metrowerks' GC toolchain
   *rival*, and it was **GCC-based**.
2. dtk's compiler archive already ships **ProDG 3.5–3.9.3** (a.k.a. `ngccc.exe`,
   with `cc1.exe`/`cpp.exe`; banner: "GCC 2.95.2 SN BUILD v1.46 for Nintendo
   GameCube").

`ngccc -O2 -G0` reproduces the original **byte-for-byte, relocations included**.
`-G0` disables small-data (the original uses plain `@ha/@l` everywhere in this
file; game-wide SDA handling is separate — see §4 #5). One more twist: the C
must store to the globals in **ascending address order** (50, 54, 58, 5C, 60,
64) — that's the exact statement order the original compiler saw, and it drives
register allocation. ProDG 3.5–3.9.3 produce the same code for this function;
the project is now on `ProDG/3.9.3` (upgraded since — see `configure.py`).

### 5.3 Build-system integration (dtk)

`tools/project.py` now has an `ngccc` ninja rule, selected per-object when
`mw_version` starts with `ProDG/`:

- `SN_NGC_PATH=<compilers>/<mw_version>` env (points at the dir with `sn.ini`),
- `-MD` produces a GCC-format depfile (ninja `deps=gcc`),
- post-compile `powerpc-eabi-objcopy -R .sdata -R .sdata2 -R .sbss -R .sbss2`
  — GCC always emits those sections (empty here) and mwld's LCF has no `.sbss2`
  output section, so they must be stripped before linking.

`configure.py` defines `cflags_game` (`-O2 -G0 -mcpu=750 -fno-common …`) and a
`game` lib entry with `"mw_version": "ProDG/3.9.3"` (was `ProDG/3.7` at the
time). The CRT lib stays mwcc
GC/1.3.2. Rebuild + hash check both pass; the matched function is verified via
`objdiff-cli` (fuzzy 100%).

**Cold-rebuild verified:** `tools/cold_rebuild.sh` (wipe `build/`, keep
compilers, `--compilers`, full rebuild) reproduces the byte-identical DOL.
One cold-rebuild bug was found & fixed: dtk's compiler-existence check
hardcoded `mwcceppc.exe` and rejected ProDG versions when `--compilers` was
passed — now it checks `ngccc.exe` for `ProDG/*` versions (project.py).

Per-object cflags **replace** the lib cflags entirely (no merge), so any future
per-file `-G>0` override must repeat the whole `-O2 -G0 -mcpu=750 -fno-common`
list. `Missing scratch compiler mapping for ProDG/3.9.3` at configure time is a
harmless decomp.me-preset notice (no THUG2 preset exists).

### 5.4 Recipe: when mwcc won't match a GameCube game

1. Grep the binary for compiler fingerprints: `strings main.dol | grep -i
   -E 'prodg|SN Systems|CodeWarrior'`.
2. Check constant-loading style: `lis+ori` (unsigned) vs `lis+addi` (signed).
   `ori`-heavy → likely ProDG/GCC, not mwcc.
3. Try dtk's bundled ProDG compilers (`build/compilers/ProDG/…/ngccc.exe`)
   with `-O2 -G0`.
4. If instructions match but relocations/registers differ, experiment with
   **statement order** (especially store order to globals) and `-G` per file.

### 5.5 M4 — first subsystem: RNG (`src/rng.c`)

Merged the two RNG functions into one source file; the DOL stays byte-identical
(cold-rebuild verified). Both functions verified 100% in objdiff:

| Function | Addr | Bytes | Role | Match notes |
|---|---|---|---|---|
| `fn_800034A0` | 0x800034A0 | 68 | seed both 3-word streams (`s0,s1,s2` = 50/54/58 and 5C/60/64) with `0x12B9B0A1`/`0x0AA2FB3F` | stores in **ascending address order** |
| `fn_800034E4` | 0x800034E4 | 88 | PRNG step: `t = s0*s1 + s2; s0 = t; s1 = (s1^t) + (t>>4); s2 = (s2 - 0x10101010) + (t>>3); return ((t&0xFFFF)*scale)>>16` | `s2n` must be a local so GCC emits `addis/addi -0x10101010` early (interleaved with `t`), matching the original |

`fn_8000353C` (0x8000353C) — the second stream's PRNG step — was matched
instantly by copying `fn_800034E4`'s shape with the 125C/1260/1264 globals
(objdiff 100%, hash unchanged). The RNG cluster (0x800034A0–0x80003594) is now
fully in C. `fn_80003594` (next function) calls `fn_800034E4`, confirming the
RNG is live game logic worth naming.

The RNG is a linear congruential generator with XOR-mix (a classic late-90s
console RNG); `fn_800034A0` is likely called once at startup with a seed and
`fn_800034E4` scales results via its arg (`(t&0xFFFF)*scale>>16`).

### 5.6 M4.5 — first non-RNG match: `fn_8000B680` + the FPR frame quirk

Matched `src/fn_8000B680.c` (a deferred-call countdown dispatcher: decrement a
global counter; at 1, invoke a stored callback through a table at task+0x20,
then clear both globals). GPR-only saves (`stmw r30/r31`) — the frame formula
`8 + 4·nGPR + locals + 4` agrees between the game and ngccc, so it matched
byte-identically on the first real attempt (DOL hash unchanged, objdiff 100%).
Two source-shape gotchas discovered:

- The two globals must be **separate** externs (not a struct): the original
  materializes the 0x80300000 base twice (r31/r30), and separate globals
  reproduce that.
- The final zero-out must be written **task-first, counter-second** — ngccc
  then reorders the stores to counter-first, which is what the original does.
- When a fresh object shows branch-target diffs, check `readelf -r` first:
  intra-function branches are `R_PPC_REL14/REL24` relocations whose raw field
  is the target offset, not the displacement — the linker writes the real
  value. The relocations here matched the original's targets exactly.

**The blocker that explains fn_80003594/fn_800035FC being parked:** functions
that save FPRs come out 8 bytes smaller from every available ngccc build (ProDG
3.5→3.9.3, C/C++, all flags): the game's compiler aligns the double slot to 16
and frames to `16 + 8·nFPR + locals`, ngccc uses `8 + 8·nFPR + locals`.
Instruction streams are otherwise identical. We scanned all 540 int→double pun
sites in the DOL: ~49 use 16-aligned slots and ~51 use 8-aligned slots, i.e. it
is per-function/frame-dependent, not a global flag — and unreproducible with
the compiler builds we have. **Match leaf / GPR-only / pure-integer functions
instead** (`tools/find_int_fns.py`, `tools/classify_fns.py`); ~778 of ~6,500
functions are FPR-blocked.

---

## 5b. The decomp loop (Phase 5, the long game)

Per function (or per source file):

```
1. Pick an assembly region (from the split objects)
2. Draft C:  m2c (ppc-mwcc-c target) or LLM, using context from Ghidra on a merged ELF
3. Compile:  ngccc (ProDG GCC 2.95.2) with the game flags (`-O2 -G0 -mcpu=750 -fno-common`);
   mwcc (via wibo) only for CRT/runtime objects
4. Diff:     objdiff / asm-differ  (objdiff GUI works — display is available)
5. Iterate until byte-identical
6. Move on (no CI yet — verify locally with `tools/ninja build/G2TE52/ok` + `cmp`)
```

Supporting tools:

| Tool | Purpose |
|---|---|
| **objdiff** (encounter/objdiff) | GUI diff viewer, best PPC matching UI |
| **asm-differ** (simonlindholm/asm-differ) | terminal diff, `-mwo` auto-rebuild mode |
| **m2c** (ethteck/m2c) | auto-drafts C from asm for `ppc-mwcc-c` |
| **Ghidra** (optional, on host) | human browsing of `dtk rel merge` output ELF |

Merge a browsable ELF when needed:
```sh
dtk rel merge main.dol -o build/merged.elf
```

---

## 6. Milestones

| # | Milestone | Exit criteria | Status |
|---|---|---|---|
| M1 | Toolchain installed | `dtk`, `ninja`, `wibo`, compilers (mwcc + ProDG) all run | ✅ |
| M2 | Project builds original | DOL hash == original | ✅ (see §4) |
| M3 | First function matched | `fn_800034A0.c` compiles byte-identical; objdiff 100%; hash unchanged | ✅ (see §5) |
| M4 | First subsystem done | **RNG** — `src/rng.c` (fn_800034A0 seed + fn_800034E4 + fn_8000353C PRNG steps), 3/3 functions, 244B, objdiff 100%; cold rebuild hash OK | ✅ (see §5.5) |
| M4.5 | First non-RNG match | `fn_8000B680.c` deferred-call dispatcher (120B), GPR-only frame formula proven; FPR-frame quirk documented (§5.6) | ✅ |
| M4.6 | Auto-matched dispatch families | `gen_dispatch_*.c`: 204 functions (table-dispatch / field-fnptr / store+dispatch / const+dispatch), all byte-identical, warm + cold verified | ✅ (see §5.7) |
| M4.6b | Auto-matched vcall-dispatch families | `src/vcall_*.c`: 29 functions (6 guard + 10 global-count + 13 setter+dispatch), all byte-identical; r11-register quirk documented | ✅ (see §5.8) |
| M4.9 | Leaf-family auto-match round | `tools/gen_leaves.py` (+61 this round): ptr-table (13), SPR accessors (11), array-index reads `ai` (12), bit-test `bt` (3), null-check getters `nc` (2), flag-set `fs1` (1), float-copy `fc1` (2), 3-float stores `fs3` (2), guarded-zero `gz` (2), indexed-float-set `if2`/`ifsz` (4), field-ptr reads `fir` (4), cross-base copies `cc` (3), SDK-named SPR fns; parked at the time: cross-fn tail merges, GC `subfic/adde` bool idiom, Paired-Single ops, r13/HW-relative (most since un-parked by M4.11 — see §5.13) | ✅ (see §5.9) |
| M4.10 | WIP-draft bulk | `tools/gen_wip_drafts.py`: inert best-guess C draft for **every** unmatched function (9,596) in `src/wip/` + `WIP.md` — real C via leaf patterns + survey matchers (subfic/adde bool, HW regs, r13, cond-store), else disasm-documented stubs. DOL byte-identical, progress unchanged. | ✅ (see §5.11) |
| M4.11 | Draft promotion rounds | `tools/test_wip_drafts.py` compiles every non-stub draft and finds **38 already byte-exact**; `tools/promote_wip.py` promotes them. **Wave 1**: 37 (24 subfic/adde bool, 9 r13 SDA reads, 3 SPR, 1 MMIO; added `lbl_CC008000` absolute symbol to `ldscript.tpl`). **Wave 2**: the NEAR-misses had trivial fixes — `cs` conditional store needed its else branch (8 fns), `cos` needed else branch + per-function offsets (4 fns), `fm` needed the `b * a` operand-order trick (2 fns), all byte-exact. 1832 → **1871** (16.37%). | ✅ (see §5.13) |
| M4.12 | m2c bulk-fill of stubs | `tools/fill_wip_drafts.py` runs **m2c** on every `stub` draft and post-processes output into ngccc-compilable C (9,246/9,323 filled; 77 stayed stub — FPR-frame/Paired-Single/cross-fn-branch bodies). Parallel `--slice i/8` sweeps of all m2c drafts found **~600 byte-exact** (271 + 66 + 263 across three postprocessor-fix rounds); FAIL went 5,100 → 793. 1871 → **2155** (18.85%). DOL byte-identical. | ✅ (see §5.14) |
| M4.13 | compile-FAIL attack | Sampled the 793 m2c drafts that didn't compile; added 6 postprocessor rule families (bare/hex idx-first, ptr-literal-deref paren fix, s32*+ptr+off byte arithmetic, fn-ptr decl unwrap, stack-array `[0]`/`[0].unkN`, float-arg→fn-ptr cast). Refill + 8-slice sweep: FAIL **793 → 252** (−68%), +2 EXACTs promoted. 2155 → **2157** (18.87%). DOL byte-identical. | ✅ (see §5.15) |
| M4.14/4.15 | second FAIL attack: rule-BUG fixes | Bucketed all 250 remaining errors (diverse singletons). Root cause was mostly **rule corruption**, not missing rules: fixed fix_float_ptr_sum depth-1 scan, fix_paren_field one-match-per-call, fix_call_deref absolute-index bugs (×2), added ptr+ptr/ptr−ptr byte-arithmetic rule. verify5 set 16 → **22/22**; verify36 holds 35/36. Refill + sweep: FAIL **234 → 187** (−20%). Progress unchanged 2157 (18.87%), DOL byte-identical. | ✅ (see §5.16) |
| M5 | 100% | full game builds from source; modifications possible | ⏳ next |

### 5.7 M4.6 — auto-matching the indirect-call helper families (204 functions)

After the hand-written dispatch helpers (fn_8005C2F8, fn_800575DC,
fn_8005F28C) proved the 13/16/17-insn table-dispatch shapes compile
byte-identical, `tools/gen_dispatch_fns.py` generalized the discovery:

- Scans the whole DOL for exact prologue/body/epilogue patterns (no FPRs, 8-byte
  frame), generates C for all hits, compiles, and byte-compares each function
  against the DOL. Only exact matches are kept.
- Four patterns matched: **d** table-dispatch (151), **f** field-fnptr call
  (23), **s** store-then-dispatch (11), **l** const-arg dispatch (19) = 204.
- One source file per contiguous address range (multi-range single files cause
  dtk link-order cycles), registered idempotently by `tools/add_gen_dispatch.py`.
- Verified: warm build byte-identical + `tools/cold_rebuild.sh` from scratch +
  objdiff 204/204 at 100%.

Key gotchas recorded in AGENTS.md §4d (capstone drops `0x` for small offsets,
`{:x}` vs decimal f-strings, flat file names for objdiff base_path, C89
store-before-declare ordering for the 's' pattern).

The remaining unmatched GPR-only `blrl` shapes (~574 candidates) are listed by
`tools/find_more_blrl.py` — next candidates: the 42-insn dispatch switch
(17 fns), the `or.`/`beq`-guarded field-call shapes, and no-frame leaf
variants. (The `li r4,1` const-arg dispatch is already matched as the `l`
pattern.)

### 5.8 M4.6b — the vcall-dispatch families (+29 functions)

`tools/gen_vcall_fns.py` auto-matched the remaining indirect-call shapes that
gen_dispatch didn't cover — all using the standard 8-byte-frame prologue, no
FPRs. Three patterns:

- **a** (17 insns): vcall-guard — `if (o) { t=*(o+TB); fp=t[3]; fp(o+
  (s16)t[4], 3); } return 1;` (6 fns, vtable base TB varies)
- **b** (30 insns): global-countdown — two `lis`-addressed globals with an
  `if (cnt>1) cnt--; else { if (obj) vcall; obj=NULL; cnt=0; }` shape (10 fns)
- **g** (12-17 insns): generalized setter+dispatch — `[0-4 stores of
  stfs/stw/sth to r3]; lwz rX,V(r3); lha r0,H(rX); lwz rX,W(rX); add r3,r3,r0;
  mtlr rX; blrl;` (13 fns). Fully parameterized over frame F, store list,
  vtable offset V, dispatch slots H/W — replaces the old hardcoded float-
  setter pattern, which had only ever matched the 16-insn 3-store variant.

Key discoveries this round:

- **The old float-setter's blind spot was a disasm-window bug**: 15-insn
  functions leaked the *next* function's `stwu` into the window, so the
  store-count check misread them as 16-insn. Truncating at the first `blr`
  fixed it and immediately unlocked the 2-store setters.
- **A whole-DOL scan found 177 dispatch-core functions across 102 signatures**
  — but 163 of them were already matched (the big V=0x18 no-store group was
  gen_dispatch's 'f'). The remaining 14 were store-prefix variants.
- **r11 dispatch-register quirk (parked)**: at 0x8005C038/0x8005C338 (both
  V=0x8) the DOL loads the vtable pointer into r11, but GCC 2.95.2 always
  picks r9 for every C shape tried (11 variants). These 2 stay parked.
- **Out-of-order store offsets** (fn_8009C7F4: stw r4,0x28; r5,0x30; r6,0x34;
  r7,0x2C) match by writing the C stores in exactly the DOL's order.
- **`fn_size` returns instruction count**, the caller multiplies by 4 — a
  bytes/already-multiplied mixup made everything look size-mismatched.

Verified: 29/29 byte-identical through the real dtk/mwldeppc build, DOL hash
unchanged (243/11,430 = 2.13%). All gotchas recorded in AGENTS.md §4e.

### 5.9 M4.9 — leaf-family auto-match round (+61 functions → 1832)

`tools/gen_leaves.py` (built up over M4.7/M4.8 and this round) scans every
function in the objdiff report, classifies tiny leaf shapes (≤10 insns, no
frame/call/branch), generates C, compiles with ngccc, and byte-compares — only
exact matches get written to `src/`. This round added/refined patterns:

- **`ai` array-index read** (12 fns): `slwi r4,r4,2; addi r3,r3,OFF; lwzx`.
  The winning C form is a struct with `char _pad[OFF]` + `s32 _arr[]` member
  access — bare pointer arithmetic makes ngccc fold OFF into `lwz` displacement
  instead of emitting `addi`+`lwzx`.
- **`bt` bit-test** (3 fns): game emits `li r0,1; slw r0,r0,r4; and.` — the
  mask must be held in a local `u32 m = 1u << i;` or ngccc strength-reduces to
  `srw`+`andi.`.
- **`nc` null-check getter** (2), **`fs1` flag-set + return** (1),
  **`fc1` float-copy pair** (2), **`fs3` 3-float store** (2): all matched
  first-try with plain C.
- **SPR accessors** (11): `mtspr`/`mfspr` need `__asm__ volatile` — and three
  (PPCMfhid2/PPCMthid2/PPCMtwpar) have SDK global names in symbols.txt that
  other asm references via `bl`, so the generator now looks up
  `config/G2TE52/symbols.txt` (scope:global) and emits the SDK name.
- **pt/ptf ptr-table reads** (13): declared as `extern void *lbl_T[]` (array)
  not `void **` (pointer) so ngccc emits `addi`+`lwzx`.

Remaining short-leaf blockers (parked): cross-function tail merges
(`beq`/`bne` into the next function's body), Paired-Single `ps_add/ps_madd`
ops (capstone shows them as `.byte`), 0xCC00 HW-register *loads*, and the
`mr r9,r3` byte-fill quirk. **Note (superseded by M4.11, §5.13):** the
`subfic/adde` bool idiom, r13/SDA reads, `cos`, `fm`, and `cs` were all in
this "unreproducible" list — their *drafts* compiled byte-exact once someone
actually compiled them. The classifier's verdict is not the arbiter; the
draft test loop is.

### 5.10 — WIP (non-matching) drafts for parked functions (`tools/wip.py`)

For functions that can't match yet, keep best-guess C in `src/wip/` (not
wired into the build): the DOL stays byte-identical, objdiff progress stays
honest, and the C is ready to activate when a blocker is solved. This exists
**instead of** the "C file containing asm" (`ASM_FUNC`) pattern — that
pattern compiles to identical bytes and would fake the match count to ~100%.
See AGENTS.md §4g for the workflow; registry in `WIP.md`.

Proof of concept (verified end-to-end): `fn_80003594` (RNG-scale caller,
parked on the FPR frame quirk §4c) — `wip.py add` registered the draft;
`activate` wired it in, compiled the object, and objdiff reported 77.8%
fuzzy (not matched, not counted); `deactivate` restored DOL byte-identity.
The draft's logic is `arg * ((float)fn_800034E4(10000) - 5000.0f) / 5000.0f`
(0x8028FB80 = u32→double magic, 0x8028FB88 = 5000.0f).

### 5.11 — M4.10: bulk WIP drafts for every unmatched function

`tools/gen_wip_drafts.py` closed the "every function has readable C" gap:

- **Scope:** all 9,597 unmatched functions → 9,596 drafts (one was already
  registered by §5.10). Every function in the DOL now has a versioned C file
  in `src/wip/` — real best-guess C where a pattern exists, otherwise a
  documented stub with the original disassembly as comments.
- **Real C sources (234 fns):** `gen_leaves.classify()+gen_one()` reuse for
  the ~66 leaf families (even when the compiler can't reproduce the bytes —
  drafts don't need to match), plus new survey matchers: `subfic/adde` bool
  idiom (`s1`/`s2`/`s3`, 24 fns — the `(x ^ M) == 0` shape the GC compiler
  emits), MMIO/HW-register access (`hws`, 11 fns — `volatile` pointer
  stores; game's `lis+stb` vs ngccc's `lis+ori` split), r13/SDA2 global
  reads (`r13`, 9 fns — honest inline asm, since the SDA2 symbol layout is
  unknown), 4-byte fill (`bf4`), conditional store (`cs`).
- **Stubs (9,362 fns):** header documents the family + range; the original
  disassembly (first 48 insns) is embedded as comments with a TODO.
- **Safety:** drafts are never registered in splits.txt/configure.py → the
  DOL build is byte-identical and objdiff progress is unchanged (verified:
  `cmp` clean, 1832 matched before/after). All non-stub drafts compile
  cleanly with ngccc (verified). Idempotent regeneration.

### 5.12 — blocker status after M4.10

The WIP drafts document (not solve) the remaining blockers. To actually
match the remaining functions: FPR-frame quirk (§4c) blocks ~778
FPR-saving functions; Paired-Single PS ops, cross-function tail merges,
HW loads, and jump-table dispatch families remain. Next auto-match targets:
the 42-insn dispatch switch (17 fns), `or.`/`beq`-guarded field-call
shapes, and the remaining pure-integer families from
`tools/find_int_fns.py` / `tools/find_more_blrl.py`. (The `subfic/adde`
idiom and r13 reads listed here at the time were un-parked by M4.11 — see
§5.13.)

### 5.13 — M4.11: draft promotion (compile-and-compare the drafts!)

The user asked whether auto-generating C for every WIP function could yield
instant matches — and it did. `tools/test_wip_drafts.py` compiles every
non-stub draft (real C, ~243 fns) with the exact ngccc command and does the
relocation-masked byte-compare against the DOL:

- **38 of 243 non-stub drafts were already byte-exact** — they were only
  parked because the old classifier had no pattern for them and nobody had
  ever compiled them. The `subfic/adde` bool idiom (24 fns) was long assumed
  unmatchable, but the drafts' C shape (`(x ^ M) == 0`) reproduces it exactly.
- `tools/promote_wip.py` promotes the byte-exact drafts into `src/fn_*.c`,
  registers them (splits.txt + configure.py), rebuilds, and cmp-verifies.
- **37 promoted (wave 1)**: 24 s1/s2/s3 subfic-adde bool, 9 r13 SDA reads
  (inline asm — byte-exact but objdiff undercounts them at 70% fuzzy due to
  the known r2/r13 analysis artifact §4 #5), 3 mfs/mts SPR (already existed
  at HEAD as SDK-named fns — no net change), 1 gs MMIO store.
- **Two real fixes:** (1) the 4-byte `e` fn at 0x80003464 lives in `.init`
  (0x80003100–0x800034A0), not `.text` — dtk can't split it as a `.text`
  block, so it stays in WIP; the promote script now skips non-`.text`
  addresses. (2) the `gs` MMIO store needs `lbl_CC008000` defined as an
  absolute linker symbol — added to `config/G2TE52/ldscript.tpl`.
- **Wave 2 — the NEAR-misses were one-edit fixes (+14):** `cs` conditional
  store (8 fns, was 60%) — add the missing `else` branch; `cos` bit
  set/clear (4 fns, was 83.3%) — add the `else` bit-clear + per-function
  offsets (0x1C/0x8/0x0/0x4); `fm` float multiply (2 fns, was 75%) — the
  fmuls register encoding needs the operand-order trick: load 0x15C into a
  var, 0x178 into another, multiply `b * a` (reproduced `fmuls f1,f0,f1`;
  offsets vary per fn — 0x178/0x15C vs 0x17C/0x160). All 14 now byte-exact.
- Progress: 1832 → **1871** (16.37%). WIP.md drops to 9,545 rows (promoted
  drafts deleted from `src/wip/`).

### How to repeat the loop (fresh agent)

1. `tools/venv/bin/python tools/test_wip_drafts.py` — full sweep of every
   non-stub draft (`--family X` / `--addr 0x...` to scope). Verdicts:
   EXACT → promotable, NEAR → edit, DIFF/FAIL → leave parked.
2. `tools/venv/bin/python tools/promote_wip.py <addrs...>` — promotes
   byte-exact drafts (re-verifies each, refuses non-exact, skips non-`.text`
   like the `.init` fn 0x80003464), re-registers, rebuilds, cmp-verifies.
3. Delete the promoted drafts from `src/wip/` + drop their `WIP.md` rows
   (and fix the family-count summary table at the top of WIP.md — re-running
   `tools/gen_wip_drafts.py` is idempotent and rewrites both from the current
   `src/wip/`). Note: `promote_wip.py` itself doesn't delete drafts, and its
   no-args built-in EXACT list is historical — always pass explicit addrs.
4. `build/tools/objdiff-cli report generate -o build/G2TE52/report.json`
   then `tools/venv/bin/python tools/gen_progress.py`, then commit.

When a draft is NEAR, the fixes that worked: add the missing `else` branch
(`cs`, `cos`), fix per-function field offsets (read them from the DOL, not
an assumed constant), flip float-operand order (`fm`: `b * a` with the
second-loaded value first), add missing args (`(o, v)` → `(o, i, v)`), or
add an absolute linker symbol to `ldscript.tpl` (`gs`: `lbl_CC008000`).

Lesson: **every parked draft is a potential match** — cheap to test, and the
compile-and-compare loop (not the classifier's assumptions) decides.

---

### 5.14 — M4.12: m2c bulk-fill of the stubs (9,246 stubs → real C)

The user asked whether auto-generating C for *all* WIP functions could yield
more instant matches — the remaining 9,323 stubs were just disasm comments
and never compiled. `tools/fill_wip_drafts.py` runs **m2c** (decomp.me's
decompiler, target ppc-mwcc-c) on every stub and post-processes the output
into standalone C that compiles with ngccc.

- **9,246/9,323 stubs filled (~6.5 min).** 77 stayed `stub` — m2c produced
  no real body for FPR-frame quirks, Paired-Single ops, and cross-function
  branches.
- **The postprocessor is a series of compile-error fixes**, each discovered
  by sampling failing bodies: `?`→s32 (m2c's unknown-type placeholder),
  `->unkN`/`.unkN`/`(expr)->unkN` field access → byte-offset casts
  (a `[.->]` char class is a **range** — must use `(->|\.)` alternation),
  deref-of-field with proper pointer casts, indirect calls,
  `saved_reg_*`/`sp*` decls, m2c `Warning:` stdout lines, prototype
  stripping, pointer-arithmetic casts.
- **Sweep**: `tools/test_wip_drafts.py --slice i/8` (8 parallel bashers)
  compiled every m2c draft and byte-compared. Three rounds as the
  postprocessor improved: 271 → +66 → +263 EXACT (last round had the fewest
  FAIL, 5,100 → 793 overall).
- **~600 promoted** via `tools/promote_wip.py`; DOL byte-identical each
  round. Progress: 1871 → **2155 (18.85%)**.
- Lessons: (1) never trust a classifier's "unmatchable" verdict — m2c C
  that merely *compiles* is often byte-exact; (2) the sweep is trivially
  parallelizable (`--slice i/m`) and the EXACT yield per slice is uniform;
  (3) keep the postprocessor rules as a documented list (AGENTS.md §4i) —
  the remaining 793 FAIL drafts are the next target (new m2c forms not yet
  post-processed).

### 5.15 — M4.13: the compile-FAIL attack (793 → 252 FAIL, +2 promoted)

After M4.12, ~793 of the m2c drafts still didn't compile — m2c's output is
often not valid C, and the postprocessor can't anticipate every shape. M4.13
attacked exactly those: sampled 80 FAIL drafts, bucketed the compiler errors,
and added six new rule families to `tools/fill_wip_drafts.py`:

- **bare/hex idx-first**: the old `fix_ptr_index_first` regex demanded a `)`
  before the `*` (`*((idx) * N) + ptr`), so the common bare form
  `*((var_r8 * 4) + arg2)` never matched. Rewritten with a lazy capture;
  output is now char*-based byte arithmetic `*((s32 *)((char *)ptr +
  (idx * N)))` — exact even for non-multiple-of-4 strides like `0xA` (an
  element-count divide-by-4 rewrite would be wrong there).
- **ptr-literal-deref paren fix**: `*(*(s32 *)0xADDR + offs)` re-wrap
  double-counted parens (`inner = text[start+1:j]` included the opening
  paren but not the matching close), producing unbalanced
  `*(s32 *)((char *)(...);`. Now `start+2:j`.
- **s32*+ptr+off byte arithmetic**: `fix_int_deref` rewrites `*(X + (ptr +
  0xN))` to `*((s32 *)X + (ptr + 0xN))` — invalid C (s32* + void*). New
  follow-up rule: `*((s32 *)((char *)ptr + (s32)0xN + (s32)X))`.
- **fn-ptr decl unwrap**: m2c's `? (*temp_r9)(?);` became the mangled decl
  `s32 (*((s32 *)temp_r9))(s32);` after the scalar-deref rule — rewrapped
  to `s32 (*temp_r9)(s32);`.
- **stack-array [0]**: m2c reads a 3-float stack slot as `sp8[0]` /
  `sp8[0].unk8` while declaring `static s32 sp8;` — rewritten to
  `*((f32 *)&sp8)` and `*((f32 *)((char *)&sp8 + 8))`.
- **float-arg→fn-ptr cast**: table-slot calls cast float args to fn-pointer
  types (`(s32 (*)(s32)) farg1`) which GCC rejects — cast to `(s32)`.

Verification: 35/36 known-FAIL addresses fixed (0x8008076C parked — m2c's
output there is genuinely corrupt: truncated mid-expression lines, not a
postprocessor miss). Full `--force` refill (8,992 filled, 71 empty, 0
failed) + 8-slice parallel sweep: **FAIL 793 → 252 (−68%)**, +2 EXACTs
promoted (0x8009C468, 0x80258840). Progress: 2155 → **2157 (18.87%)**, DOL
byte-identical. The remaining 252 FAILs (list in `/tmp/fail3.txt`) are the
next round's sample.

### 5.16 — M4.14/4.15: second FAIL attack (234 → 187 FAIL, rule-BUG fixes)

Bucketed all 250 remaining errors (`tools/bucket_fail5.py`) — far more diverse
than M4.13's set, many singletons. Debugging revealed most were NOT missing
rules but **corruption inside existing rules** (balanced-paren scans and
index math). Built a reusable debugger: `tools/trace_rules.py` (per-step line
trace), `tools/bisect_rules.py` (injects a step counter into a copy of
`postprocess` and reports the exact step where a corruption marker first
appears; note its limit N executes steps 1..N+1 — off-by-one), and
`tools/iso_chunk31.py` (run one chunk in isolation).

Five fixes:
1. **fix_float_ptr_sum depth**: started depth at 0 after the group's `(`, so
   `(f32 *)`'s own parens hit depth 0 early → `(s32)(var + *(f32 *))((char *)...)`.
   Start at depth 1 (already inside the group).
2. **fix_paren_field multi-match**: while-loop rewrote the first `)->unkN` into
   `res` but scanned the ORIGINAL text for the second, misaligning base offsets
   → `(A + B)*(s32 *)(...)` garbage. One match per call now; outer 8× loop
   re-runs on the updated text.
3. **fix_call_deref _decl_star**: used relative `m.start()` to index the full
   `out` — wrong from the 2nd match on; declaration stars (e.g. `s32 *fn_X(`)
   were misdetected as derefs. Now checks absolute `text[:start]`.
4. **fix_call_deref open_idx**: `start + m.end() - 1` mixed absolute start with
   relative end — off by `m.start()` after the first match, so the balanced
   scan landed mid-args (`*((s32 *)fn_X(...), 1);` + orphan `)`). Now
   `i + m.end() - 1`.
5. **ptr+ptr arithmetic**: `A = B + C;` / `A = B - C;` with both operands
   pointer-typed vars (byte-address math m2c typed as pointers) →
   `(char *)B + (s32)C` / `(s32)B - (s32)C`.

Verification: `tools/verify5.py` cluster set 16 → **22/22**; `tools/verify36.py`
regression set holds 35/36 (0x8008076C parked — m2c-corrupt). Full refill +
8-slice sweep: **FAIL 234 → 187 (−20%)**. Progress unchanged at
**2157/11,430 (18.87%)**, DOL byte-identical. Current FAIL list:
`/tmp/fail5.txt`.

## 7. Risks & caveats

1. **`patch_dol.py` is game-specific.** It encodes the sdata2 region addresses and base values for
   G2TE52. If the DOL layout changes later (it won't for matching work — addresses are fixed), the
   patch's target-range check would simply skip; the assert would catch anything unexpected.
2. **Compiler version:** resolved — game code is ProDG ngccc (GCC 2.95.2, `-O2 -G0`), CRT is mwcc
   GC/1.3.2. ProDG version 3.5–3.9.3 are interchangeable for matched functions so far; re-sweep if
   a future function won't match. Some files may need `-G>0` (small data) — see configure.py notes.
3. **No RELs, no map file** for this game — a single 3.06 MiB `main.dol`. Simple.
4. **Clean-room: no leaked source.** Leaked source code for THUG1 is publicly
   circulating, but **nothing from it is used here** — this project works from
   the binary only. Function names come mainly from Tony Hawk's Proving Ground
   (Wii) symbol data, not from the leak. No DWARF/ELF line info either:
   `main.dol` is stripped and the disc ships no ELF, so line-info tooling
   (the kind NFS clones run against their shipped ELFs) has nothing to work
   on here.
5. **CI needs a remote** (GitHub/GitLab) for the auto-match-checking workflow — optional for solo work.
6. **m2c targets mwcc codegen.** Its drafts are a starting point for ngccc too, but expect to
   hand-adjust statement order / registers (see §5.2).

---

## 8. Next actions

- [x] User supplies lossless RVZ → `orig/G2TE52/game.rvz`
- [x] Execute Phase 1–4 (toolchain, scaffold, config, first build) — **M2 done**
- [x] Verify the built DOL runs in Dolphin — **done headlessly**:
      `tools/dolphin-cli.sh dolphin-tool convert -i orig/G2TE52/game.rvz -o build/G2TE52/test_game.iso -f iso`
      → `tools/venv/bin/python tools/replace_dol.py build/G2TE52/test_game.iso build/G2TE52/main.dol`
      → `tools/dolphin-cli.sh dolphin-emu-nogui -e build/G2TE52/test_game.iso ...`
      Result: **0 "Invalid read"** and sustained emulation (boottest_iso.log); the bare-DOL
      control reproduces the crash (30 invalid reads, boottest_baredol.log). Dolphin cannot boot
      the bare `main.dol` (no disc → DVD reads fail); the disc image is required. `test_game.iso`
      is ready for a visual boot on the user's machine. Note: `dolphin-cli.sh` runs the host's
      flatpak Dolphin tools via the runtime's own dynamic loader (bubblewrap can't nest).
- [x] **M3 — first matched function** — `src/fn_800034A0.c` (RNG init), ProDG `-O2 -G0`,
      objdiff 100%, DOL hash unchanged (see §5).
- [x] **M4 — first subsystem** — `src/rng.c` = `fn_800034A0` + `fn_800034E4` + `fn_8000353C`
      (RNG: seed + two PRNG steps), objdiff 100% all three, cold rebuild hash OK (see §5.5).
- [x] **M4.5 — first non-RNG match** — `src/fn_8000B680.c` (deferred-call
      dispatcher), 120B, objdiff 100%, cold rebuild hash OK. Also mapped the
      FPR-frame quirk (see §5.6) that blocks FPR-saving functions.
- [x] **M4.6 — auto-matched dispatch families** — `src/gen_dispatch_*.c` (204
      functions: 151 table-dispatch + 23 field-fnptr + 11 store-dispatch + 19
      const-dispatch), all byte-identical; generator `tools/gen_dispatch_fns.py`
      (see §5.7). Cold rebuild hash OK.
- [x] **M4.6b — auto-matched vcall-dispatch families** — `src/vcall_*.c` (29
      functions: 6 vcall-guard + 10 global-countdown + 13 setter+dispatch),
      all byte-identical; generator `tools/gen_vcall_fns.py` (see §5.8).
- [ ] M5: keep matching pure-integer / GPR-only / leaf functions
      (`tools/find_int_fns.py` + `tools/find_more_blrl.py` for candidates;
      `fn_80003594` stays parked — FPR frame quirk). Workflow in `AGENTS.md` §5.

---

## 9. Reusable recipe — starting a fresh matching decomp of another game

This project's setup is the working example. To bootstrap a **new** GameCube (or
other mwcc-era) game, reuse the same pipeline:

1. **Scaffold:** clone `encounter/dtk-template`, drop the game image in `orig/`,
   `configure.py --dtk tools/dtk --ninja tools/ninja` (auto-selects the mwcc
   version and downloads tools + compilers).
   Extract the game's `main.dol` from the image first (Dolphin CLI, if available:
   `dolphin-tool extract -i <image> -o <dir>` then copy `<dir>/sys/main.dol`; or
   convert to ISO and read the DOL at the boot offset in the header `0x420`).
2. **Split:** `tools/ninja build/GAMEID/config.json` — then fix the standard
gotchas, in this order:
   - *Two `.rodata` sections* → dtk errors "Multiple sections with name .rodata":
     rename the second to `.rodata2` in `splits.txt` and relabel symbols
     (`tools/fix_rodata.py` automates the relabel).
   - *Undefined `__start`* (mwld default entry): label the DOL entry address in
     `symbols.txt`.
   - *CFA analysis stalls* on computed jump tables (`mtlr r0; blrl`): add the
     region to `skip_cfa_ranges` in `config.yml`.
   - *SDA mismatch* (original used `-sdata2 0`, dtk emits r2 accesses the game
     never makes): compare r2/r13 usage in both binaries, then either fix the
     section classification or apply the `patch_dol.py` post-link approach
     (the two base registers differing by a constant offset makes this a
      deterministic byte patch — see §4 for the math).
   - *Linker symbol mis-attribution* (e.g. `lo(_stack_end)` where a constant was
     intended): override the symbol in a custom LCF via `ldscript_template`.
3. **Verify matching:** `tools/ninja build/GAMEID/ok` + `cmp` the DOL against the
   original; iterate the two fixes above until byte-identical (this is the
   milestone equivalent of M2).
4. **Boot-verify** the built DOL with a converted ISO in Dolphin (see `AGENTS.md` §8).
5. **Fingerprint the compiler before decompiling** (M3 gate): `strings main.dol |
   grep -iE 'prodg|SN Systems'`; count `lis+ori` vs `lis+addi` in `.text`. If
   `ori`-heavy or ProDG strings → the game was built with SN Systems ProDG
   (GCC 2.95.2): use dtk's bundled `ngccc` with `-O2 -G0` (see plan §5.4 for the
   full recipe, incl. statement-order gotcha).
6. **Decomp loop:** m2c + objdiff per function (see `AGENTS.md` §8), now with the
   ngccc build rule wired in (mw_version `ProDG/<ver>` selects it automatically).

The generic takeaway: dtk handles the 90% case; the last 10% is almost always
section-classification and linker-symbol nits, all fixable at the config/link
tool level without touching dtk itself.
