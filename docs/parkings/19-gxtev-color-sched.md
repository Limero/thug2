# 19 — GXTev Color family scheduling coin-flip (GXSetTevColor / GXSetTevColorS10 / GXSetTevKColor)

**Status: PERMANENTLY PARKED — pure scheduler-ordering coin-flip, re-verified
exhaustively 2026-08-17 AND 2026-08-19 (incl. 1.2.5e, full public-web search,
and decomp-permuter PERM_ONCE/LINESWAP runs). Do not reopen.** `GXTev.c` is
13/16 byte-exact; only these three have diffs, all pure scheduling (same
instruction SET, same size, correct semantics). **M8.2x: the file was SPLIT
into `gx/GXTevA.c` + `gx/GXTevB.c` around the three color functions, which are
wired byte-exact in the build; only the color trio stays auto-asm.**

> This file merged the former unnumbered family doc (`gx-tev-color-family.md`)
> with the file-split notes (2026-08-26). It is the single canonical doc for
> the GXTev Color trio.

## Region

- GXTev.o text: `0x8028B224..0x8028BA08` (16 functions, contiguous)
- GXTev.o data (tevopTable): `0x803108D0..0x80310944` (0x74)
- The three stragglers: `fn_8028B408` (GXSetTevColor, 0x74), `fn_8028B47C`
  (GXSetTevColorS10, 0x74), `fn_8028B4F0` (GXSetTevKColor, 0x74)

## What matches (13/16, verified byte-exact)

GXSetTevOp, ColorIn, AlphaIn, ColorOp, AlphaOp, KColorSel, KAlphaSel,
SwapMode, SwapModeTable, AlphaCompare, ZTexture, TevOrder, NumTevStages.

## Facts established

- The three color functions are **same-instruction-count** as retail (29 insns
  each) — pure **scheduling-order coin-flip**, the doc-10 class.
  All mnemonics match; only the load/schedule order differs.
- DOL order: loads color bytes `a, r` then `b, g` (b BEFORE g) and hoists the
  `gx` (.sbss, `lwz rX, -0x6218(r13)`) load before the first RAS write.
  mwcc 1.2.5n (and every tested source form / flag / compiler version) hoists
  `g` early and sinks the `gx` load.
- **Header lesson (the fix that unblocked the other 13):** the file was copied
  from bfbb and used `__GXData` (the internal `__gx.h` struct, 0xB8 larger
  than the DOL's actual layout). The DOL only has the public `gx` symbol with
  the `GXInit.h` `_GXData` layout (`texmapId@0x49C`, `tevTcEnab@0x4E0`,
  `dirtyState@0x4F4`). Converting the file to `gx` + the public macro set made
  `GXSetTevOrder` and `GXSetNumTevStages` EXACT instantly.

## The fix already applied (data-temp form)

All three now use the **data-temp** structure instead of the old direct
two-merge form (which was 1-2 instructions short / wrong structure):

```c
data = color.a << 12;
SET_REG_FIELD(745, data, 8, 0, color.r);      // data1 = (a<<12)|r
regRA = (0xE0 + id * 2) << 24;
SET_REG_FIELD(746, regRA, 20, 0, data);       // 20-bit merge, top byte = addr
```

- **S10**: 11-bit fields, 23-bit merge at LSB 9 (`SET_REG_FIELD(regRA, 23, 9, data)`).
- **KColor**: same as Color + `SET_REG_FIELD(data, 4, 20, 8)` on the DATA temp
  (retail: `rlwinm r0,r0,0,0xc,7` clears LSB 20-23 + `oris r0,r0,0x80` sets
  8<<20), then 24-bit merge at LSB 8. Only 2 FIFO writes (not 4).

## Approach that worked for the rest of the file (split around the trio)

Rather than parking the whole file, split GXTev.c around the three stubborn
functions:

- `gx/GXTevA.c` — 5 fns, .text 0x8028B224..0x8028B408, .data
  0x803108D0..0x80310920 (TEVCOpTableST0/ST1)
- `gx/GXTevB.c` — 8 fns, .text 0x8028B564..0x8028BA08, .data
  0x80310920..0x80310944 (c2r table, 9 words: `{0,1,0,1,0,1,7,5,6}`)
- 3 color fns 0x8028B408..0x8028B564 stay auto-asm.

The .data symbol `lbl_80310920` originally spanned 10 words (9-word c2r + the
first 0x00000000 word of GXPixel's table) — split it in symbols.txt so each
wired file's .data maps 1:1.

## The remaining diffs (all scheduling)

Retail GXSetTevColor (29 insns) loads the four color bytes in order
`a(3), r(0), b(2), g(1)` and keeps the constants (`li 0x61`, `lwz __GXData`,
`lis CC008000`) grouped right before the first `stb`. mwcc 1.2.5n under
`-O4,p` always hoists `g`'s load early (pos 2) and hoists `li`/`lis` into the
load block. Every source variant produced the same schedule:

- v2/v3/v5/v6/v8/v9/v10/v12 (data-temp, locals-first, interleaved writes,
  `__GXData` local, reordered statements) → 16-18 norm-diffs
- v4 (writes interleaved) → 20; v7 (single expression) → 23; v9/v11
  (`b | (g<<12)`) → 26 and folds into one `rlwimi` (28 insns, wrong)

Compiler-version sweep (same flags): 1.2.5 == 1.2.5n (identical bytes),
1.3/1.3.2/1.3.2r all worse (size mismatches across the whole file). The 13
matching functions prove 1.2.5n is the right compiler for this file; the Color
family is a genuine scheduler coin-flip. The instruction SET is
identical — only ORDER differs (load order + constant placement).

---

# Exhaustive dead ends (do NOT redo any of these)

## 2026-08-19: decomp-permuter runs — PERM_ONCE + deterministic LINESWAP

Ran the permuter on GXSetTevColor with the proper macros (this version has
`PERM_ONCE`/`PERM_LINESWAP`/`PERM_RANDOMIZE` — it does NOT have
`PERM_START`/`PERM_STMT`; those do not exist in any public permuter fork,
confirmed against upstream `simonlindholm/decomp-permuter` main). Three
setups, all compiled with the real project flags (`GC/1.2.5n`, `-O4,p`,
`-char unsigned` — verified identical to build.ninja):

- **work3** — `PERM_ONCE` write1-placement slots + two temps (value flow
  fixed: dataRA→regRA, dataBG→regBG) + `PERM_RANDOMIZE` wrapper: best 650.
- **work4** — pure deterministic `PERM_LINESWAP` (all 40,320 statement
  orders, NO randomizer wrapper), two temps: best 940 (base 1090). The
  earlier work2 run (single `data` temp, 40,320 orders + randomizer) found
  570; all three are garbage (see below).
- **w1mid** (hand test) — first FIFO write pair placed *between* the two
  compute blocks (the doc's 630-interleaving search never interleaved the
  writes): 29 ins, **20/29 mnemonic diffs — worse** than the natural 15/29.
  Also tested two-temp natural (15/29, same as single-temp) and split
  stb/merge/stw forms (30 ins, worse).

**Every score "improvement" the permuter reports is an exploit, not a match.**
Compiling each best output and checking for the compiler's
uninitialized-variable warning:

- work4 940: `dataRA is not initialized before being used` → compiles to 24
  ins (retail 29); the `a`/`r` loads vanish entirely — the reordered source
  reads `dataRA` in the regRA merge *before* assigning it, so the compiler
  drops the loads. The scorer rewards the lost diffs.
- work3 650: same `dataRA` uninit warning + dead `if (new_var)` / `if (!(&color))`
  blocks inserted by the randomizer to steer scheduling.
- work2 570: no uninit warning, but value flow broken — the shared `data`
  temp lets the compiler feed the g/b composite into regRA (verified: wrong
  colors written; also only 27 ins vs 29).

**Conclusion:** the permuter cannot crack this family. Its scorer rewards
"fewer diffs", and the cheapest way to lose diffs is undefined behavior
(uninitialized reads) or value-flow corruption — never retail's actual
schedule. Even with value flow structurally fixed (two temps) and the
full 40,320-order deterministic search, the best *correct* C remains the
natural order (15/29), matching the 630-interleaving hand search (best
13/29). Combined with the 2026-08-17 compiler/flags/source sweep, this is
now proven from every angle: **the family stays permanently parked in
auto-asm; the DOL is byte-clean.** Remaining theoretical avenue: inline
asm (rejected by project policy).

## 2026-08-19: gx/GXFIFO access-pattern sweep

The last untried structural angle — the `__GXData` load sits at pos 10 in
retail vs pos 13 in every build (the stb→stw gap is filled by `addi addr2` in
retail vs the `gx` load in built). Tested 9 access-pattern variants compiled
with the real project flags (GC/1.2.5n, `-O4,p`, `-char unsigned`):

- gx const / non-const / `volatile` / local-copy-at-top / cast-at-write /
  real SDK name `__GXData` → **all 15/29 mnemonic diffs, byte-identical
  schedules** (constness and naming don't move the load)
- `volatile gx`, FIFO via pointer-deref, FIFO via direct `*(volatile u8/u32*)`
  casts → **23/29, worse**
- FIFO as `volatile u32[2]` at 0xCC008000 → 21/29, worse

The `gx` load position is a pure scheduler decision insensitive to how the
pointer is declared or accessed. **This closes the final structural angle;
the family stays permanently parked.**

## 2026-08-17: the 1.2.5e avenue is DEAD (tested, byte-proven)

decomp.me's compiler archive (`files.decomp.dev/compilers_20240706.zip`,
package `GC/1.2.5e`) hosts the only obtainable 1.2.5e: EpochFlame's
**profile-hacked 1.2.5** (its own README: "not a real version but an edited
CW 1.2.5 compiler... performs the profile hack found by EpochFlame",
`mwcceppc.exe` still reports "2.3.3 build 163"). It forces a `bl
__PROFILE_EXIT; nop` tail on every function; the real-world 1.2.5e build
pipeline runs `frank.py` (doldecomp/melee @d196686) to merge the profile
object with the vanilla 1.2.5 object and strip those calls (this is how TP's
"2.3.3 build 163 (GC MW 1.2.5e)" preset works).

Test: compiled `GXTev.c` with vanilla GC/1.2.5 and profile-hacked GC/1.2.5e
(identical cflags, `-O4,p`), ran frank.py, compared. Result: **frank output
is byte-identical to vanilla 1.2.5 — 0 differing instruction slots in the
whole 0x7e4 `.text`** (the color functions' `sth`+`blr` tails don't match
frank's lwz/li/lmw epilogue patterns, so nothing gets rescheduled). The three
functions score identically to vanilla 1.2.5/1.2.5n under the same
comparison (mnemonic counts measured with a normalized/reloc-masked harness).
1.2.5e is not a different scheduler — it IS 1.2.5 codegen. **Do not reopen.**

## 2026-08-17: public-web search exhaustive (no usable source exists)

Every public repo that could hold thug2's Sep-2002 → Mar-2003 SDK GXTev.c was
audited; **none contains the data-temp form**:

- `doldecomp` org (19 repos: assets, brawl, decomp-training, dolcp-apr2001,
  dolsdk2001, dolsdk2001-dec, dolsdk2004, Ghidra-GameCube-Loader, gnt4, kar,
  melee, mkdd, mkw, ogws, sadx, smg, sms, sonicriders, ttyd) — **no 2002/2003
  SDK decomp exists publicly**; dolcp-apr2001/dolsdk2001 are 2001-era,
  dolsdk2004 is Apr-2004.
- `doldecomp/dolsdk2004` `src/gx/GXTev.c`: Apr-2004 single-`lwz` form
  (identical to tp/nfsmw) — not our form. Ruled out.
- `ogamespec/DolphinSDK_Decompile` `gx/src/GXTev.c`: Ghidra decomp output
  (`param_1`, `iRam00000000` globals), 2001-era — not usable C. Ruled out.
- `doldecomp/sms` `src/dolphin/gx/GXTev.c`: bfbb-style form
  (`regRA=0` + 11-bit fields + regID embedded). Ruled out.
- `doldecomp/kar`, `doldecomp/sadx`: no Dolphin SDK GX sources at all. Ruled out.
- Local clones (tww, bfbb, tp, nfsmw, ratatouille, crashwoc, mkdd): unchanged
  conclusions (see summary). Ruled out.

Conclusion: thug2's exact GXTev.c form exists in no public repo. Combined
with the compiler sweep below, **every avenue is now proven dead** except
inline asm (project policy rejects it) or accepting the park.

## 2026-08-17: exhaustive re-verification

Every lever was pulled; retail's schedule is not reproducible with any
available toolchain state. Concretely:

- **Merges are correct.** The `SET_REG_FIELD(745, data, 8, 0, color.r)`
  (size 8, shift 0 → `rlwimi r,r,0,24,31`) and `SET_REG_FIELD(746, regRA, 20, 0,
  data)` (→ `rlwimi r,r,0,12,31`) encodings match retail instruction-for-
  instruction. (A prior note worried retail's `rlwimi r8,r10,0,9,0x1f` vs the
  intrinsic's `rlwimi r8,r10,9,0,22` differed — they are the SAME operation;
  objdump canonicalizes both to `0,9,0x1f`.)
- **All 16 compiler versions 1.0–3.0a3** in `build/compilers/GC/`:
  1.0/1.1/1.1p1/1.2.5/1.2.5n give the identical (non-matching) schedule;
  1.3+ give 32 insns (size mismatch). No version produces retail's order.
- **All opt levels/flags** `-O2 -O3 -O4 -O4,p -O4,s`, `-pragma scheduling
  on/off`, `-opt schedule/peephole/all`, `-fp_contract`, `-char signed/unsigned`,
  `-str reuse`, `-inline off`, `-pragma speed_code on`: identical schedule.
  `-O3` alone restructures (block1→block2→writes, no write interleaving) and
  is worse (20–23 mnemonic diffs vs 15).
- **630 exhaustive statement interleavings** of the 8 compute statements
  (all valid topological orders of both blocks): best is 13/29 mnemonic diffs
  (current form: 15). The scheduler is robust to statement order.
- **Structural variants**: u32 `*(u32*)&color` form → 24 insns (single `lwz`,
  NO load-splitting on any compiler version — definitively rules it out;
  retail's 4 `lbz` needs the data-temp form), OLD_SET_REG_FIELD (mask+or) →
  25 insns, byte-locals-first, block2-first, direct construction, raw
  `GX_WRITE_U8`/`GX_WRITE_U32` — all worse or equal.
- **The delta is tiny**: both schedules interleave the regRA merge between
  write1's `stb`/`stw`. They differ only in (a) block1 load order
  (retail a,r,b,g vs built a,g,r,b), (b) constant hoisting (`li 0x61`/`lis
  CC008000` late in retail, hoisted to pos 3/8 in built), (c) `__GXData` load
  pos 10 vs 13 (the stb→stw gap is filled by `addi addr2` in retail vs the
  `__GXData` load in built).

Remaining avenues if ever revisited: inline asm (avoided per project policy).
Every other combination is proven dead — including the 1.2.5e/Japanese-market
variant (byte-identical to 1.2.5, tested 2026-08-17) and the full public web.

Brute-force levers tried and exhausted across rounds: statement-order
permutations (all worse), bfbb's exact source form, tww's word-load form, tp's
form, all mwcc 1.0–1.2.5n versions, `-schedule off`.

---

# Notes for whoever picks this up

- The `SET_REG_FIELD` macro is LSB-based: `SET_REG_FIELD(reg, size, shift, val)`.
- The written value's top byte is the register address (`0xE0+id*2` / `0xE1+id*2`);
  dolphin's CP FIFO reads `data[0]`=0x61 tag, `data[1]`=register, `data[2..4]`=value.
- Do not try bfbb's EA-lineage form (regID at bits 24-31 via `SET_REG_FIELD(reg, 8, 24, ...)`)
  — that is the EA-modified SDK, not THUG2's Nintendo Sep/Feb SDK.
- Useful compare harness: `/tmp/gxtev_cmp.py` pattern (capstone-normalized,
  reloc-aware per-function compare vs retail bytes from `gen_leaves`).

## Next steps if revisited

- The DOL's second 9-word table at 0x80310944..0x80310968 belongs to
  **GXPixel** (referenced from 0x8028BE48), not GXTev.
