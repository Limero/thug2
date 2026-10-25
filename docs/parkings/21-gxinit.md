# GXInit — Feb-7-2003 (0x2301) revision, 4 of 5 wired

**Status: PARTIALLY WIRED (2026-08-19).** The DOL's GXInit block
(0x80284E20..0x802861A4, 5 functions) is a Dolphin SDK **Feb 7 2003 04:01:13
(0x2301)** build that exists in **no other decomp** (checked: tww Sep-2002,
mkdd Jul-2003, bfbb Apr-2003, tp Apr-2004, nfsmw, sims2, dolsdk2001).

**Wired byte-exact** (`libs/dolphin/src/gx/GXInit.c` + `GXInitGX.c`, both
carry `#pragma peephole off` — see docs/dolphin-sdk.md s8.17):

| addr      | size | name                          |
|-----------|------|-------------------------------|
| 0x80284E20| 0x7C | `__GXDefaultTexRegionCallback`|
| 0x80284E9C| 0x24 | `__GXDefaultTlutRegionCallback`|
| 0x80284EC0| 0x190| `__GXShutdown`                |
| 0x802858E0| 0x8C4| `__GXInitGX`                  |

**Still parked (auto-asm):**

| addr      | size | name                          |
|-----------|------|-------------------------------|
| 0x80285050| 0x890| `GXInit`                      |

## Revision identification (2026-08-19)

Banner string at 0x8030FA40: `<< Dolphin SDK - GX.release build: Feb  7 2003
04:01:13 (0x2301) >>` (68 bytes, stays in auto .data; the `__GXVersion`
pointer is auto .sdata at 0x803CA9F8).

Distinguishing features vs other revisions:

- **Arithmetic tex-region init** in `GXInit` — `gx->TexRegions0[i]` /
  `TexRegions1[i]` addresses computed as `0x10000*i`, **no
  `GXTexRegionAddrTable`** (tww/bfbb/mkdd all use the table; this is older).
  Loop of 8 over regions 0+1, then loop of 4 over region 2 (no TexRegions2
  init, no `__GXSetIndirectMask` — that symbol does not exist yet).
- `__GXInitRevisionBits` is **inlined** into `GXInit` (no separate symbol).
- `__GXShutdown` = bfbb-form body with tww-form time-sync loop (reads
  `__memReg` 0x4e/0x50 via `__GXReadMEMCounterU32` inline; no
  `__GXReadMEMCounterU32` call — it's a static inline in EA-lineage `__gx.h`
  that conflicts with our tww-lineage GX headers, so it must be copied
  locally, see below).
- `__GXInitGX` is the tww form exactly (reset func table, GXSetArray(gx),
  fog calls `GXSetFog`/`GXSetFogRangeAdj` at 0x8028BA08/0x8028BC24 — now
  named).

## Why only 1 of 5 remains parked (diff breakdown, 2026-08-19)

With `#pragma peephole off` the 3 small functions became **byte-exact** — the
earlier 62-85% diff numbers were measured WITHOUT the pragma and are void
(the peephole pass was removing retail's dead `b .+4` chains and reordering
the prologue). `__GXInitGX` was then also wired byte-exact (see below).

- `GXInit`: **the loop-unroll mystery is SOLVED** (2026-08-19 second pass):
  the missing ingredient was `-O4,p` in the compile flags (the probe harness
  had been using plain `-O4`), PLUS manual `i += 4` 4-coord loop bodies for
  the suTs AND vat loops. With those, all three loops reproduce retail's
  exact unroll decisions — tevc `mtctr 8` x2-coord (85 insns, exact),
  suTs `mtctr 2` x4-coord (82 vs retail 77), vat `mtctr 2` x4-coord (81,
  exact). The reconstruction compiles to **452/548 (82.5%) mnemonic match,
  +4 insns** in the real build; the remaining diffs are regalloc/scheduling
  coin flips (prologue `&gxData` hoist into r30, `addi`/`addis`/`mr` address-
  form distribution, suTs +5 insns) — the same class that permanently parked
  the GX tev family. See the recipe below.

If re-attempted, the reconstruction's arithmetic tex-region init and inlined
`__GXInitRevisionBits` are the suspect extra-code sources.

## How `__GXInitGX` was solved (2026-08-19)

Three fixes took it from structurally-off to byte-exact (561=561 insns):

1. **Drop the spurious tex-obj block.** The reconstruction was based on bfbb
   (Apr-2004), which added `GXInitTexObj`/`GXLoadTexObj` x8 after the
   callback setup. thug2's Feb-2003 retail (and tww's Sep-2002) go straight
   from `GXSetTlutRegionCallback` to `GXSetTevOrder` — removed the block
   (9 calls / 26 insns gone).
2. **`GXSetChanAmbColor`/`GXSetChanMatColor` take `GXColor` BY VALUE.** The
   tp-derived `GXLight.h` declared `GXColor*`; thug2's retail copies the
   4-byte struct to a temp stack slot and passes a pointer to it (mwcc's
   by-value 4-byte struct ABI). Fixed the header + callers
   (`docs/dolphin-sdk.md`). This matched retail's stack-copy pattern exactly.
3. **`.sdata2` placement: split the claim at the 8-byte alignment boundary.**
   The C file's constants (0, 0xFFFFFFFF, 1.0, 0.0, 0.1, 2^52 magic double)
   are 8-aligned because of the trailing double, so they cannot start at
   4-aligned 0x803CC06C. Retail's `clearColor` word (0x404040FF) sits alone
   at 0x803CC06C in the auto unit; the C file references it via
   `extern const GXColor lbl_803CC06C` (same-TU-static trick from the GXInit
   FifoObj fix: an extern that mwcc loads as one `lwz`). The claimed range is
   `0x803CC070..0x803CC090`, and the compiler's own constants land there in
   retail's exact order. Load order of the three colors was fixed by
   declaring `clearColor = lbl_803CC06C` first (mwcc emits loads in source
   order).

`__GXInitGX` needed its own file (`GXInitGX.c`) because a C unit cannot
claim two non-contiguous `.text` ranges — dtk hits a link-order cycle with
`GXInit` main (auto-asm) between them.

## Second matching session (2026-08-19 late) — prologue SOLVED, loops pinned

A second attack on `GXInit` main made a structural breakthrough and then hit
the same coin-flip wall. Findings, in order:

1. **Prologue `&gxData` hoist SOLVED via the tww-form same-TU statics.**
   Declaring `static GXData gxData; static GXFifoObj FifoObj;` in GXInit.c
   and claiming the `.bss` range `0x803C8880..0x803C8DF8` makes mwcc know
   `&FifoObj == &gxData + 0x4F8` at compile time, so it keeps the base in a
   callee-saved reg and emits retail's exact `lis; addi r30` hoist +
   `addi r3,r30,0x4f8` per use (was +3 `lis/addi/addi` + `mr` on the
   extern route). Only GXInit.c references gxData; the auto `.bss` gap is
   exactly gxData+FifoObj.
2. **`gx` must be defined in the C file, not externed.** The auto `.sdata2`
   `gx` pointer emits an `R_PPC_ADDR32 gxData` relocation that needs a
   GLOBAL `gxData`, but the C unit defines it static (local) — link fails.
   Fix: `GXData* const gx = &gxData;` in GXInit.c + claim the full 3-word
   `.sdata2` block `0x803CC064..0x803CC070` (float-0 word 0x803CC064 is
   unreferenced/dead, `clearColor` word 0x803CC06C referenced from
   GXInitGX). The `-sdata2 0` route (gx stays in auto, scope:local so the
   generator emits a literal `.4byte 0x803C8880`) also links and was the
   first working state.
3. **tevc loop is mnemonic-identical (113/113)** with the plain 8-statement
   loop under `-O4,p`.
4. **suTs/vat oscillate around retail — the pinned wall.** Running-induction
   manual 4-coord bodies (v0/v1 bumped `addi +2` per coord, as retail's
   `r10/r11` do) give suTs 75 / vat 79 (retail 81/81, total 543). The
   fresh-`(i+1)*2` manual form gives 82/81 (total 551). The simple
   `0x30 + i*2` nfsmw-style loop fully unrolls (556). Every permutation
   shuffles ±5 insns; there is no expression form that lands on 81/81.
   Retail additionally reloads the gx pointer via `lwz r3,-0x6218(r13)` at
   the loop head each pass (aliasing) and keeps dead `b; b` chains — the
   built code hoists/elides them.
5. **DOL-clean is all-or-nothing on size.** The builder packs units; a
   GXInit 0x14 short of retail's 0x890 pushes every later unit 0x14 earlier
   and misplaces ~42KB of code bytes + 1992 sdata pointers (deltas +0x14 in
   the GX region, +0x10 after rdata) — the DOL cannot be left in that
   state. Byte-exact requires the exact 0x890 AND matching registers; even
   at 548 insns the remaining regalloc renames would keep the DOL dirty.

Conclusion: same coin-flip class as the permanently-parked GX tev color
family; parked for good unless a new compiler/source angle appears. Best
reconstruction lives in `src/wip/fn_80285050.c`
(with the statics + `gx` definition, ready to wire; the former
`docs/parkings/gxinit-reconstruction/GXInit.c` artifact was removed
2026-08-26 as a byte-identical duplicate).

## Data symbols already named (kept in symbols.txt, auto-asm)

- `FifoObj` @ 0x803C8D78 — auto `.bss` gap object. For GXInit main, define
  it (and `gxData`) as same-TU statics + claim `0x803C8880..0x803C8DF8` —
  that is the prologue-hoist fix (second session, see above). Do NOT leave
  a partial `.bss` claim: it duplicates into the .bss tail and shifts
  .sdata/.sbss/.sdata2 by its size.
- `gx` (sdata2 pointer), `gxData` (bss 0x803C8880) — named in the auto units.
- `peCount` 0x803CAEC0, `time` 0x803CAEC8, `calledOnce` 0x803CAED0,
  `resetFuncRegistered` 0x803CAED4 (auto .sbss).
- `DefaultTexData` @ 0x80302EE4 (auto .data).

## GXInit main — solved loop mystery + remaining coin flips (2026-08-19)

**The `-O4,p` flag is REQUIRED.** The probe harness originally used plain
`-O4`; with `-O4,p` the compiler's per-function unroll budget is allocated
the way retail's was. Everything below is measured with the project's real
flags: `-O4,p` + `#pragma peephole off`.

**Recipe that reproduces all three unroll decisions** (reconstruction is in
`src/wip/fn_80285050.c`, updated):

1. **tevc loop** (16 iters): plain `for (i = 0; i < GX_MAX_TEVSTAGE; i++)`
   with the 8-statement body (`tevc[i]=0; teva[i]=0; tref[i/2]=0;
   texmapId[i]=NULL;` + 4 SET_REG_FIELDs). The `i / 2` indexing keeps it a
   loop; `-O4,p` gives it the x2 unroll (`mtctr 8`, 85 insns, exact).
2. **suTs loop** (8 iters): the dead-var trick alone works only while the
   vat loop is also a simple loop. Once vat is manual (below), suTs must
   ALSO be a **manual `i += 4` 4-coord body** (zero-stores + SET_REG_FIELDs
   for i, i+1, i+2, i+3) or it collapses to a 1-coord `mtctr 8` loop.
3. **vat loop** (`__GXInitRevisionBits` inline, 8 iters): a manual
   `i += 4` 4-coord body, per-coord order
   `SET_REG_FIELD(vatA); SET_REG_FIELD(vatB); GX_WRITE_U8(8);
   GX_WRITE_U8(i|0x80); GX_WRITE_U32(vatB[i])` (u32 LAST — bfbb/nfsmw
   order). Gives `mtctr 2`, 4-coord bodies, 81 insns (exact size). The
   compiler rotates the trailing u32 to the front of the next coord's block
   naturally; retail's per-coord pattern is `[vatA][vatB][u8][u8][u32]`.
   The `u32`-FIRST order also loops but at 1-coord `mtctr 8`.
4. **`EnableWriteGatherPipe` is NOT a symbol in thug2's SDK.** Retail calls
   `PPCMfhid2` (0x80261DD4) / `PPCMtwpar` (0x80261DE4) / `PPCMthid2`
   (0x80261DDC) directly — the EA-lineage inline:
   `u32 hid2 = PPCMfhid2(); PPCMtwpar(0xC00F8000); hid2 |= 0x40000000;
   PPCMthid2(hid2);` (bfbb has the same inline in GXInit.c; the
   `OSUncachedToPhysical(GXFIFO_ADDR)` form is for the OLDER tww SDK and
   folds to a different constant).
5. **Externs needed** when wiring into GXInit.c: `gxData` and
   `GXResetFuncInfo` are `scope:local` in symbols.txt — they must be flipped
   to `scope:global` or the link fails with "undefined".

**Remaining coin flips** (why it's parked):

- Prologue: SOLVED by the same-TU statics route (second session, see above)
  — `lis; addi r30` hoist + `addi r3,r30,0x4f8` per use are now exact.
- Loop bodies: suTs/vat oscillate −6/+5 around retail depending on the
  induction-value expression form (running induction 75/79, fresh-compute
  82/81, simple loop fully unrolls) — pure scheduling/regalloc, same class
  as the permanently-parked GX tev color family. `stmw r23` vs `stmw r25`
  prologue regalloc also differs.

## Notes for re-attempting `GXInit` / `__GXInitGX`

The reconstruction in `src/wip/fn_80285050.c` is the
starting point, but the two big functions need hand-matching against the
retail disasm (dump with the tools used for other GX files). The `-sdata2 0`
addition means all constant accesses go through the r13/r2 patch path —
compare via the linked ELF + `patch_dol.py`, not raw .o bytes. Expect this
to be a multi-session effort on par with the GX tev family (which was
permanently parked after exhaustive permuter runs).

**Peephole-off signature (2026-08-19 survey):** all 5 functions carry the
`b .+4` dead-branch chains that mark `#pragma peephole off` compilation (see
docs/dolphin-sdk.md §8.17 — the same artifact that unlocked
`__ppc_eabi_init.c`). Retail GX was compiled with peephole off. The full-DOL
scan found this signature in *only* SDK/MSL code (OS/AI/runtime-init, all
matched) and the GXInit block — no game code uses it.

**What peephole off fixed (and what it didn't):** with `#pragma peephole off`
the 3 small functions became byte-exact (dead `b .+4` chains + the
address-load-after-prologue scheduling both appeared), and `__GXInitGX`
followed once the three fixes above were applied. `GXInit` main is at
82.5% mnemonic match (+4 insns) with all three loops correctly unrolled —
the remaining diffs are regalloc/scheduling coin flips (see the recipe
above).

Second session verdict (2026-08-19): the loop-shape mystery is solved and
the prologue hoist is solved; the suTs/vat bodies are a ±5 insn
regalloc/scheduling oscillation with no expression form that lands on
retail's 81/81 — the same permanently-parked class as the GX tev color
family. Wiring is reverted to DOL-clean; the best reconstruction (543 insns,
statics + `gx` in-TU, ready to wire) lives in
`src/wip/fn_80285050.c` with the splits/symbols
changes documented in its header.

## Third attack (2026-09-08) — tww source recovered, wall confirmed

**tww's original `GXInit.c` (Sep-2002) was fetched** (zeldaret/tww
`src/dolphin/gx/GXInit.c`): its suTs loop is the PLAIN form
(`for (i = 0; i < GX_MAXCOORD; i++)` + zero/RMW per coord, plain vat loop
likewise). So retail's x4 bodies are COMPILER-unrolled plain loops — the
manual-unroll approach can only approximate the unroller's output. Direct
consequence tested: plain loops under 1.2.5n/`-O4,p` do NOT unroll 4x
(suTs-plain → branch loop, 556B total; both-plain → 589B). The manual
bodies are required for the mtctr-2 skeleton, but they enable the
induction substitution below.

**Precise residual** (mnemonic histograms of the mtctr regions, want vs
`src/wip/fn_80285050.c`): tevc 89/89 exact; suTs 81 vs 79, vat 86 vs 83.
suTs differs by EXACTLY THREE `addi` (want 20, got 17) minus got's one
`li r29,0` (want keeps zero in r0 from pre-loop): want recomputes
`r8=r9+0xb8` / `r7=r9+0xd8` per coord from the running `r9+=4` induction
plus running `r10/r11+=2` value inductions with carried `r12/r25` address
webs; got fans all offsets off one `r8+=0x10` base and derives per-coord
values as `base+2k`. The narrower coloring (stmw r25 vs r23) follows from
the fan's extra live webs — one problem, not two.

**Exhausted this round** (all on the standalone draft via
`tools/mwcc_verify.py`-style harness; region sizes quoted as tevc/suTs/vat):
- interleaved `v0+=2`/`v1+=2` between the RMW groups (want bumps v0 after
  the suTs0-RMW): no effect, still 89/79/83 — the scheduler hoists bumps
  regardless of source order.
- `#pragma unroll(4)` / `#pragma unroll 4`: silently ignored (mwcc
  GC/1.2.5n has an internal IRO unroller but no user pragma; probe
  functions fold identically with/without it).
- `-O` matrix on plain loops (1.2.5n): `-O4`/`-O3` shrink everything
  (tevc 49/48 — loses the required 2x unroll); `-O2` worse. `-O4,p` is
  pinned by tevc's exact 89.
- mwcc version matrix (`-O4,p`): 1.1 and 1.2.5 are bit-identical to 1.2.5n
  (89/79/83, both manual and plain sources); 1.3.2/2.0 unroll differently
  and smaller (manual 41/68/70, plain 41-only). No version unrolls plain
  suTs 4x.

**Why it cannot land (fundamental):** explicit per-coord `v+=2` bumps always
forward-substitute into `base+8` on 1.2.5n (copy-prop on straight-line
code, independent of unrolling — a manual-2x body re-unrolled by the
compiler folds identically); the only single-bump-per-iteration source is
index-derived values, which fully unroll (pure-memory loop, no side
effects to force a counted loop like vat's FIFO writes do... and vat-plain
still doesn't unroll 4x either). mtctr-2 skeleton and running inductions
are mutually exclusive on every available compiler/flag combination.
Park stands; do not re-grind without a new mwcc version or a substitution
blocker (unavailable: no extended asm barriers, volatile adds traffic,
calls add `bl`s).

**Inline-asm route closed by experiment (2026-09-08):** a SINGLE no-op
`asm { mr r0, r0 }` at the suTs loop top (1 insn, 0.2% of the function)
does not stay local — total output collapses 543→497 insns with regions
89/79/83 → 77/64/64 (the barrier perturbs unroll decisions GLOBALLY,
including the tevc loop before the asm site; the wedge itself is duplicated
5x). So small asm can neither stay surgical nor pin the missing 5 insns /
global recolor, and transcribing the diff regions as asm is the banned
ASM_FUNC pattern (objdiff 100% with nothing decompiled — 2026-08-25
incident rule: asm must stay a small minority, ≤30%). Same barrier verdict
as the mtx Frustum defunct inline-asm form (33+ diffs). Bonus hazard: CW
`asm{}` resolves identifiers against C locals (`v0`/`v1` ambiguity warnings
on an `r0`-only block).

## Fourth attack (2026-09-26) — SMS donor + bisection, wall localized to suTs homing

**Donor settled: `sms` (not `pikmin2`).** `sms/libs/dolphin/src/gx/GXInit.c`
has the same `0x4F8` `GXData` (`TexRegions[8]+TexRegionsCI[4]`) and the same
arithmetic tex/CI/tlut init, `TmemConfig(0)→InitGX` tail and `freqBase`
dance as retail — verified word-for-word against the retail disasm.
`pikmin2` (`0x5B0` + addr table) is the wrong generation. thug2 deltas vs
SMS are small: `OSRegisterVersion` + reset-func + `abtWaitPECopy`. Probes in
`<scratch> (NOT in repo — tmpfs; re-derive from SMS + the deltas
above if lost).

**Bisection proof (the "impossible" verdict is half-dead):** prologue + tevc
alone (`bis_tevc_only.c`) compiles under `1.2.5n -O4,p + peephole off` to
**80.9% with byte-exact prologue** (`stmw r25`, `mr r27/r25`, `&gxData→r30`)
**and tevc** (counter `r9`, `srwi r7,r9,1`, zero in `r0`). The compiler CAN
emit retail's shapes from plain C — the failure is purely the suTs/vat
register coloring, not emission.

**Size hits (skeleton):** tevc `mtctr`/`bdnz` offsets exact; suTs `bdnz
0x408` absolute-exact (2-coord `k+=2` body, double-unrolled to 4/iter by the
compiler); vat region-size exact (`v = m|0x80` staged temp per coord).
Best full probe `gx_v08_combo2.c`: 473/546 words, total 546/548.
`PPCMtwpar` constant must be `0x0C008000` (not the doc's old `0xC00F8000` —
`lis 0xC01/addi -0x8000`).

**Localized wall: suTs webs home saved (`stmw r23`) vs retail scratch
(`stmw r25), and the widener is the SET count, not the counter.** Pressure
bisection (tevc + suTs-cut variants, signal = `stmw` span): zeros-only →
`r25`; 1-coord zeros+SETs → `r25`; suTs0-only → `r25`; 4 SETs no zeros →
`r24`; full 4 zeros + 4 SETs → `r23`. Each SET pair costs one saved reg;
retail keeps all 8 SETs' values/offsets/addresses in scratch (`r9/r10/r11`
running inductions + one `r25` address). Census: retail suTs touches ONE
saved reg (`r25`×7); ours touches six (`r23–r28`, 76 mentions) with 2–3x the
`r3`/`r9` copy traffic. Resists: body forms (plain/2/4-coord,
running/fresh/temps/dual-induction `j=k+1`), counter split/share/single,
`int`/`u32` (int = signed-div penalty), expression shapes (`k*2` vs `k<<1`),
compilers 1.0/1.1/1.2.5/1.3.2/2.7 (all keep `r23` on the full file; 1.3.2
also fully unrolls plain suTs), statement orders (texmapId-first = 80.9% →
29.5% with doubled 255; original SMS order confirmed).

**Cascade theory (unproven, guides next session):** got homes 255 in `r0`
and zero in saved `r11`; retail is swapped (255 in saved `r31`, zero in
`r0` from prologue). The dead `r0=0` lets retail init the suTs counter with
`mr r9,r0` (1 word); ours needs `li` (+1 word, matches the suTs-mtctr +4
offset). Later pressure plausibly spills 255 out of saved (backward
interference: suTs webs displace tevc's homes — tevc colors `r8` scratch
alone but `r24` saved once suTs exists). Next experiment: suTs bodies that
provably shrink simultaneous live webs (fuse zero-store and SET addresses
via explicit pointer temps), watching `stmw` per variant as established.

## Fifth attack (2026-09-26, cont.) — dead driver + pointer bases hold r25

**Breakthrough: a DCE'd trip driver kills the counter web.** suTs with
running pointer bases `p0/p1` + running values `v0/v1` + a `t<2` driver that
is dead in the body (CTR only, no compare) holds **`stmw r25` and scores
61.2% in bisection** (`p_tdriver.c`), vs 17% for every counter form (which
also drag the tevc counter `r9`→`r12`). Grown to the full file
(`gx_v10_fulltdrv.c`): **23.5%, `stmw r25` still holds** (no backward
widening), size 532/548, prologue diffs gone from the report top.
mwcc has no register pins (`register __asm__` ICEs wibo); `-schedule off`
on the full file scores 5.9% (worse — scheduling ON confirmed). Probes in
`<scratch> (tmpfs).

**Refined rule: recompute temps, not carried count, drive the spill.**
Folded accesses (pointer `p0[c]`, 0 temps) fit `r25`; 16 inline recompute
temps spill 2–3 regs (`r20`–`r23`) whether integer-domain, char-`*`,
alias-split, or running-offset flavored; per-coord `+N` literals each
materialize a temp. Named reassigned temps get homes even when short-lived;
unnamed inline temps fare no better at 16/iter. Backward interference is
real (same suTs head colors `r26/r25/r27` cut vs `r31/r25/r28` full, zero in
`r0` vs `r29`), but the span effect is second-order next to temp count.

**Remaining gap is size, and it cascades.** Pointer-folded suTs is 62w vs
want 80w (-18: the indexed-zero `addi`s and RMW `add`s); the -16 total
shortfall misaligns ~290 downstream words (vat/tex/tlut/tail), which is
most of the 407 diffs. Growing suTs with recomputes reintroduces the spill
in every form tried (offset/lean/continuous-bump/split-index/alias/inline:
`r20`–`r23`). The missing piece is a recompute form whose temps land
scratch the way retail's do (`r8/r7/r12` + one `r25` spill). Next lead:
recomputes that reuse the ALREADY-homed set (no fresh temps) rather than
fresh `addi`s per coord.

## Sixth attack (2026-09-26, cont.) — region agents: suTs +29 via shared temp

Three isolated region agents (own verifier WORK dirs, frozen baseline at
393/548, 8-compile budget each) worked suTs, vat+gap, tail in parallel.
src/wip/fn_80285050.c now holds the integrated best at **364/548 (33.6%),
size-exact**. Vat/tail agents confirmed their regions already optimal
(vat u32-last + `v=m|0x80` staging; tail induction exact-modulo-regs with
`0x50` frame), blockers explicitly downstream of suTs.

**Agent A (suTs) +29: share ONE sequential temp.** Winning shape keeps the
k-counter but computes a per-iter byte base `b = (u32)(k << 2)`
(block-scope, fresh per iter) and routes all 8 offset/address recomputes
through a single reused `t` (`t = b + 0xB8` … `t = b + 0xDC`, zeros + SETs
all via `(gx + t)`). Span stays `r23`, but the recompute *instructions* now
exist with retail-like forms, so masked words match instead of missing.
Lesson: one reused home beats fresh-per-coord temps (which the allocator
coalesces into a spanning home anyway) — sequential reuse is free,
parallelism costs slots. Next: re-sweep vat/tail once suTs holds `r25` —
their remaining diffs may evaporate with the pressure.

## Sixth attack — recolor specialist + vat/tail resweep

A suTs recolor specialist (12 compiles, per-web targets r8/r7/r12/r25/
r9/r10/r11) proved declaration-position steers split-web homes with zero
other changes (r28/r31 swap, byte-identical otherwise) but moved nothing
saved-to-scratch: values stay 4 webs (r11/r12 + r26/r27) vs want 2
(r10/r11), zero stays r29+li (r0 clobbered as 4th offset home), mtctr stays
r0 vs r3, tevc counter stays r12. A vat/tail re-sweeper confirmed vat
u32-LAST (u32-first is 1 word worse), gap freqBase/BP/cpTex verified, and
shipped 4 opcode-exact words: tail loop compares cast to `(u32)j` for
retail `cmplwi` (zero object delta otherwise — merged into the WIP).
src/wip/fn_80285050.c holds the integrated best at **364/548 (33.6%),
size-exact**. Per-web table (got vs want): base r8 vs r9; values 4 vs 2;
offsets saved vs r8/r7; addresses partial (r25 hit once); zero r29+li vs
r0; gx HIT (per-iter `lwz r3`); mtctr r0 vs r3; tevc counter r12.
