# 20 — GXPixel fog functions regalloc/scheduling (file trim approach)

**Status: PARKED — but the other 10 functions of GXPixel.c are wired
byte-exact (M8.2x).**

## Symptom

`GXSetFog` (0x8028BA08, 0x214) and `GXSetFogRangeAdj` (0x8028BC24, 0x100)
are parked as auto-asm. The other 10 functions (0x8028BD24..0x8028C040,
incl. `GXSetPixelFmt` + its static `p2f` table at 0x80310948..0x80310968)
are wired byte-exact via `gx/GXPixel.c`.

## Facts established

- The DOL's `GXSetFog` is **0x2301-era tww math** (calls
  `__cvt_fp2unsigned`, while-loop fog ramp) combined with the **older
  direct-MMIO register form** (`stb` addr + `stw` data via
  `GX_WRITE_RAS_REG`), and loads fog color bytes individually
  (`lbz r6,1(r29); lbz r9,2(r29); lbz r5,0(r29)`), not `*(u32*)&color`.
  Switching the in-tree file to per-byte color made the size match (0x21C).
- `GXSetFog` is then a **pure regalloc coin-flip**: all 135 insns match in
  mnemonic order; the DOL saves only 4 FPRs, mwcc saves 8+. Exhausted:
  all compiler versions 1.0–1.2.5n (identical output), every source form.
- `GXSetFogRangeAdj` differs in addressing: DOL uses pointer-increment
  `lhzu` with constant-folded addr bytes into the register write; mwcc keeps
  fixed-base indexing even with `const` restored on the pointer.
- `GXSetZCompLoc`/`GXSetFieldMode` needed the OLD mask+or form
  (`OLD_SET_REG_FIELD`) — the DOL uses `rlwinm`/`rlwimi` masks, not the
  newer `SET_REG_FIELD` shift/or — before they matched.

## Approach that worked (trim dead functions)

The in-tree copy (bfbb-style) had extra dead functions
(`GXSetFogColor`, `GXInitFogAdjTable`) and used `table->r[i]` (tp field name;
our header uses `fogVals`, same layout). Trimmed to the 10 linked functions
and fixed field names; dead-stripped `.sdata2` orphans (1.75/2.125) are
dropped at link.

## .data layout note

- `lbl_80310944` = single orphan 0x00000000 (separate symbol, keep it).
- `lbl_80310948` = p2f table (8 words `{0,1,2,3,4,4,4,5}`) — GXPixel.o .data.
- These boundaries had to be split out of the old merged `lbl_80310920`
  (10 words) symbol in symbols.txt.

## Next steps if revisited

- GXSetFog: the DOL's 4-FPR save pattern vs mwcc's 8+ is the doc-10 class;
  no source lever found.
- GXSetFogRangeAdj: pointer-increment loop is the target; `lhzu` + folded
  addr bytes defeat mwcc's addressing selection.

## 2026-10-02: schedule/flag/version/source-shape matrix (new data, park holds)

Surveyed every `~/ai` tree for a new source form: tww (word-load
`*(u32*)&color`), bfbb/sms/SFA-Decomp/crashwoc (reg=0 + `SET_REG_FIELD`),
ratatouille/nfsmw (sRG/sBA word-load), pikmin2 (`GX_SET_REG`) — all previously
tried shapes, none matches retail's data-temp/`lha` form (S10) or unrolled-`lhzu`
form (fog). fzero's `GXFog.c` is asm-only. No new inspiration exists locally.

`mwcc_verify` results on the current wip drafts (GC/1.2.5n, dolphin flags):

| Variant | Verdict |
|---|---|
| fog loop (array-index) + default `-O4,p` | DIFF 52/65 (20%), 260B — iter0 head byte-identical thru +0030; every iter same insn SET as retail (OLD iters 0/4, NEW iters 1-3, next-iter `li` hoist, `stb` interleave all reproduce); single delta is `addi r5,r5,4` where retail fuses `lhzu r10,4(r5)` — the other 51 diffs are that 4-byte cascade |
| fog loop + `-schedule off` | DIFF 55/64 (14%) but SIZE EXACT 256B — fuses the single `lhzu` at exactly retail's spot; order scrambles (no scheduling) and tail `oris` lands before `stb` instead of after. First reproduction of the fusion |
| fog u16-walk (`p[0]/p[1]`, `p+=2`) ± schedule | identical to array-index both ways |
| fog post-increment (`*p++`) | catastrophic (1.5%, emits `sthu`) — dead |
| fog × CC 1.0 / 1.1 / 1.2.5 | identical 52/65 — not a version gap in 1.x |
| fog × CC 2.7 | no unroll (136B) — dead |
| fog × `-O3` | identical 52/65; × `-O2` keeps loop rolled (148B) — dead |
| fog hand-unrolled ×5 | 236B, reg-byte `li r7,k` folds away — confirms the loop IV must stay live |
| S10 + `-schedule off` | 26/29 (10.3%), worse than baseline 19/29 |

Root cause (fog): retail needs schedule-ON ordering AND the `lhzu` fusion
simultaneously; no 1.x version/flag/shape does both. The loop is mandatory
(hand-unrolling folds the per-iter `li`). If ever cracked, it needs its own
file with its own flags (the other 10 `GXPixel.c` fns need defaults —
same precedent as `GXInitGX.c`). S10: nothing new; `-schedule off` worse.

2026-10-02 addendum — surgical-asm path closed: mwcc 1.2.5n REJECTS GCC-style
`__asm__` with operands entirely (`=r`/`b`/`+b`, memory clobbers, empty
barriers all fail with `User break, cancelled...`); only opaque `asm { }`
blocks compile, and those cannot bind C operands (no values in/out, no
clobbers) — so a 1-insn `lhzu` wedge or zero-cost scheduling barrier is
inexpressible, and emitting the diff regions raw would be whole-body
transcription (banned, `promote_wip.py` refuses). Peel experiment
(iter0-peeled + `i=2..` loop): exact 256B via a different trade
(`oris`-fold + `addi r8,r5,4` into a side reg) but only 31.2% — pieces
perturb each other across the peel boundary. Plain-C + policy-legal asm
both exhausted; park stands.
