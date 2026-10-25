# Issue 29 — AltiVec/VMX instructions are unemittable by ngccc

> **RE-AUDIT WARNING (2026-08-24, round):** capstone/objdump MISLABEL many Gekko paired-single words as VMX mnemonics — PS A-form bits 21–25 collide with VMX VA-form `vc`. fn_801BF5B8's "152 VMX words" probed 100% as valid, emittable PS ops against ngccc builtin encodings (probe method + verified xo10 map in `src/wip/fn_801BF5B8.c`). Before trusting ANY vm* mnemonic below as a wall reason, hand-decode or probe the word. Members flagged for re-audit: fn_800FDE38, fn_80161AC0, fn_801ADCE4, fn_801BBAE0. **OUTCOMES (2026-08-25):** fn_80161AC0/fn_801ADCE4 EXACT; fn_800FDE38 re-parked on real scheduler walls (52%); fn_801BBAE0 confirmed zero-unknown across 252 op4 words, front rebuilt, parked on doc-28 CR walls. Also cracked from the same correction: fn_801792D4's "xo5=8" park invalidated (frame now byte-exact; re-parked on allocator roles), fn_8014E440 EXACT (3516B, was deleted-draft), fn_800FE204 EXACT, fn_801FFE78 decode-complete husk. NOTE (2026-08-25 audit): member retries that produced whole-body asm transcription EXACTs (AC66C/ACBC0/ACF84/AC9CC/B7C80/B99A8/B9FD0/B8678/BA464 + ADCE4 + B23FC) were REVERTED as ASM_FUNC violations and refilled — the decode corrections stand, the fake EXACTs do not. Re-retry with real C only (asm ≤ ~30% of instructions). Git-history audit 2026-08-25: NO pre-escalation real-C candidates exist for any of the 11 — every historical blob is either the m2c baseline or the whole-asm rewrite (the structural work was never committed before it was overwritten). Retries start from the refilled m2c baselines + fresh ps_disasm work; the decode tables from the reverted drafts remain recoverable from git (commits 1adf1476/60e81860/98a5e10d/e83bb380/57686b15/e2778399) if their header analysis is wanted.
>
> **PROOF FROM BATCH-63 (2026-08-24):** two functions parked on exactly this misdecode went **EXACT** after re-audit + `-mps-float` retry — `fn_801B19DC` ("two xo5=8 encodings" = X-form ps_mr XO10=72) and `fn_801B4404` ("vmhaddshs/vmsumshm + undecoded op4" = all 35 words standard PS). Decode recipe + full builtin map: docs/parkings/06 **M5.0q** + AGENTS.md §6ae-167..169. Counter-proof that a real wall exists: `fn_801B1278` re-decoded to mostly PS PLUS four words of a genuine unknown op (101DF00C/109DF00C XO10=6 + F00E Rc=1 variants) — that one stays parked, but under the doc06 xo5=6/7 class, NOT VMX.

**Status: OPEN (hard wall). First catalogued 2026-08-23.**

## Root cause

THUG2 contains functions with **AltiVec/VMX code** (primary opcode 4
VMX-form instructions). The project compiler, SN Systems ProDG ngccc
(GCC 2.95.2 derivative), has **no VMX backend at all**: unlike paired-single
(§ issue 06, where SN's own SNAPS `__builtin_ps_*` intrinsics cover every
opcode), there is **no C construct and no builtin** that makes ngccc emit
any VMX instruction. GCC upstream gained AltiVec only much later
(GCC 3.x + `-maltivec`), and none of the five installed ProDG builds
accepts `vector` types or altivec builtins.

The DOL's opcode-4 space therefore holds TWO different instruction sets:

| XO5 range | Meaning | Emittable? |
|---|---|---|
| 10–15, 18, 20, 21, 23–26, 28–31 | Gekko paired-single (`ps_*`) | YES via `__ps_t` + `-mps-float` + SNAPS |
| VMX-form words (e.g. raw `0x1xxxxxxE`-style `vmsumshm`, `vmhaddshs`, `vsel`, `vpkuhum`) | AltiVec int/pack ops | NO — nothing emits them |

(Discriminator when diffing: PS A/X-form words have XO5 ≤ 31 in bits
26–30 with the C field at bits 21–25; VMX V-form words use bits 6–10 as
VD and carry VRc/V5 fields the PS forms never use.)

## Blocked functions

All parked with structural sketches in their `src/wip/fn_*.c` drafts:

| Function | Size | VMX ops seen | Notes |
|---|---|---|---|
| `fn_800FDE38` | 0x220 | `vmsumshm` ×4, `vmhaddshs` ×2, `vsel` ×2 | **RE-AUDITED 2026-08-25 (M5.0q): NOT VMX** — all 18 op4 words standard PS. Retried: prologue+guards+blocks2/3 byte-exact; PARKED 52% on f0-recycle/arg-setup scheduler walls (`src/wip/fn_800FDE38.c`) |
| `fn_800FE204` | 0x78 | `vmsumshm` ×2 | **EXACT 2026-08-25** — the two words are A-form ps_sub; cracked via explicit `mr %0,%1` asm into r9-pin, __ps_t sp[2] array, -fno-schedule-insns (`src/wip/fn_800FE204.c`) |
| `fn_800FE42C` | 0x4AC | `vmhaddshs`/`vmsumshm` @0x800FE79C–0x800FE850 | **RE-AUDITED 2026-08-25 (doc06 M5.0q): NOT VMX** — all 25 opcode-4 words are standard PS (sub/merge/mul-with-B=0/madd/sum0/rsqrte/muls0/ps_mr), fully emittable. Retried with `-mps-float`: prologue/frame, preheader, v1/v2 vertex blocks, calls, the whole PS block FE74C–FE884 (frozen verbatim) and tail all match; PARKED instead on a vertex-3 block-placement wall — want keeps two IDENTICAL v3 then-arms inline and shares only the else pair, 3.9.3 crossjumps both pairs far ([bne shared-then][b shared-else]) under every web-shape/pin/goto/flag variant tried (14 flags; `-fno-crossjumping` absent from SN cc1). Same intermediate-SN-build behavior family as doc06 M5.0j. Best-match body: `src/wip/fn_800FE42C.c`. |
| `fn_800FE8D8` | 0x758 | `vmhaddshs`/`vmsumshm` @0x800FEC90–0x800FED38 | twin of FE42C, helper fn_800F8858 — do NOT extend FE42C conclusions here: contains one genuine unknown word (115C300E, XO10=7) |
| `fn_800FF030` | 0x448 | `vpkuhum` @0x800FF3F8 | + PS block @0x800FF3C4–0x800FF3E4 |
| `fn_800FF478` | 0x454 | `vpkuhum` @0x800FF83C | twin of FF030, helper fn_800FAE1C |
| `fn_800FFE78` | 0x614 | 8 VMX words (`vmsumshm` …) | **RE-AUDITED 2026-08-25 (M5.0q): all 33 op4 words standard PS, zero unknown** — filled compiling husk + full decode table + structural map in `src/wip/fn_800FFE78.c`; needs multi-session hand-rebuild (~600B+ zone threshold class) |
| `fn_8010048C` | 0xA7C | 12× `vsel` | repeated min/max-select accumulation |
| `fn_80161AC0` | 0x1EC | `vmsumshm`/`vmhaddshs` @0x80161BF0–0x80161C24 (+ "undecodable" op-4 words) | **EXACT 2026-08-25** — those words are ps_mul/madds0/sum0 (M5.0q); distance block rebuilt from builtins (`src/wip/fn_80161AC0.c`) |
| `fn_801AC66C` | 0x314 | `vsel`/`vmsumshm`/`vmhaddshs`-dominated | round; structural sketch in draft |
| `fn_801AC9CC` | 0x1F4 | two raw `vmsumshm` words (squared-distance test) @ACE08-class | ; cr3 pre-loop CR test + twin call pairs documented; fn_800EA4D8 arity fixed (arg3-first, no arg0) — **PARK REASON INVALID (w75, 2026-10-02): both opcode-4 words are A-form `ps_sub` (XO5=20, frD=frA, frB=arg1 pair), not VMX.** Whole function rebuilt from C with `-mps-float` + `__builtin_ps_sub` to **NEAR 42.4%** (496B/500B): frame 0xC0, param homes, flags bool, all three fabs guards, both call pairs, cr3/cr4 tail and epilogue all byte-exact. Two reusable findings: (1) `for (i = n; i--;)` is the only loop shape that reproduces a want latch of `cmpwi r27,0; addi r24,-0x60; addi r27,-1; bne loop` (12–38% for `i!=0`/`while(i){i--}`/`n-1`+`break` — GCC reorders or splits the loop); (2) for the `e->v` address shared between a `psq_l` and a call arg, want folds the psq_l displacement onto the element pointer and materialises `addi r30,r31,0x28` only at the call, while ngccc CSEs both into one register hoisted into the PS block — this 1-word displacement is what shifts the whole twin-call block. Best body + full reject list in `src/wip/fn_801AC9CC.c` |
| `fn_801ACBC0` | 0x3C4 | `vmsumshm`/`vmhaddshs` block @ACE08–ACE30 | ; rest reproducible (old draft wrongly blamed FPR frame — corrected) |
| `fn_801ACF84` | 0x458 | ~19 VMX word sites across two distance blocks | |
| `fn_801B7C80` | 0x254 | `vmhaddshs`×8 / `vmsumshm`×2 / `vsel`×4 (word-verified) | ; also §6j-4 statics-DCE |
| `fn_801B8678` | 0x630 | 9+ VMX words (`vmsumshm`/`vmhaddshs`/`vsel`), psq_l→v-reg aliasing | ; body fully hand-reconstructed, positional ceiling ~12% |
| `fn_801B9444` | 0x3B4 | `vmhaddshs`/`vmsumshm`/`vsel` from @9514+ | ; statics-DCE shrink (436 vs 948B) |
| `fn_801B99A8` | 0x254 | `vmsumshm`/`vmhaddshs` @9A3C/50/58 | |
| `fn_801B9FD0` | 0x2B8 | `vmsumshm`/`vmhaddshs`/`vsel` (op-4 words incl. one maddhd-class) interleaved with psq ops | |
| `fn_801BA464` | 0xBEC | two genuine `vsel` (xo6=42) @BB024/28 | ; full semantics restored from statics-DCE stub (-mps-float) |
| `fn_801ADCE4` | 0x434 | `vsel`/`vmsumshm`/`vmhaddshs` | **PARK INVALID (M5.0q): all 37 op4 words standard PS** — a retry reached byte-exact but via 83% transcribed asm (banned ASM_FUNC, §4g/recipe 180); REFILLED to m2c baseline 2026-08-25. Retry honestly with real C + builtins; the decode groundwork in doc06 M5.0q still applies |
| `fn_801DE248` | 0x4EC | vmhaddshs/vsel/vmsumshm @0x288–0x3EC | ; velocity calc |
| `fn_801DE50C` | 0x5C4 | vmhaddshs ×2 + 5 raw op-4 words @0x574/0x5A8 | ; rest (hash chain, fneg blocks) reconstructable |
| `fn_801DE8BC` | 0xA20+ | vmsumshm/vmhaddshs @0x9E8–0xA10 | ; skitch-search distance test; head/tail plain C documented |

 caveat: capstone mislabels several PS ops as VMX mnemonics
this zone (ps_add→vsel, ps_sub→vmsumshm) — hand-decode opcode-4 words per
AGENTS.md §6ai-152 map BEFORE adding members here.

(The game engine is Neversoft C++ compiled with ProDG; these are almost
certainly from a vector-math library compiled with a VMX-capable pass or
hand-written intrinsics under a different toolchain invocation than the
rest of the game.)

## What does NOT work

- All five ProDG versions (3.5/3.5b140/3.7/3.8.1/3.9.3): no `vector`
  keyword, no `-maltivec`, no altivec builtins — ICE or syntax error.
- `__asm__` passthrough of the VMX words: dtk's flow compiles `.text` from
  C objects only for matched functions; an `.s`/mixed object would need
  assembler support for VMX mnemonics that the shipped binutils lack
  (`as` rejects `vmsumshm`), and hand-encoded `.word`s inside a function
  break the objdiff byte-compare premise (it would be "asm-in-C", banned
  per AGENTS.md §4g). ** rounds closed even the inline-asm
  window route: the game's own SN assembler (`ngcas 1.0.25`, the one cc1
  drives) rejects `vmsumshm`/`vmhaddshs` outright ("Unrecognised opcode") —
  so unlike doc-30's `bdnz $` fix, there is NO assembler path here at all.
  The blocker is toolchain-level, full stop.**
- Replacing the semantics with scalar C: changes the instruction stream
  completely (these are 4-wide SIMD ops on 128-bit regs).

## Unpark condition

One of:
1. A VMX-capable assembler/binutils appears in-tree AND dtk gains a way to
   link one auto-split unit per function with hand-encoded words
   (essentially an approved ASM_FUNC carve-out with honest progress
   accounting), or
2. The game's actual compiler build (with VMX support) is recovered, or
3. Per-function exception in the split/build system routing these to
   preserved assembly forever (they would then simply never count as
   source-matched).

Until then: do NOT spend time drafting these bodies beyond the structural
sketches already in `src/wip/` — the blocker is upstream of source-shape.

## CORRECTION (2026-08-24): `vpkuhum` words are NOT proof of VMX

fn_8019FC70's disassembly contains the opcode-4 word `vpkuhum v0,v31,v0`
(0x8019FDC4) that this doc treated as an AltiVec wall. Under `-mps-float`,
ngccc 3.9.3 emits the **identical word** for a plain Gekko paired-single
element copy (`d[k] = s[k]` on `__ps_t`) — capstone simply mislabels Gekko
PS pair-moves as VMX mnemonics. fn_8019FC70's draft reproduces it verbatim.

Consequences:
1. Members parked PURELY on "vpkuhum + psq mix" deserve re-test with
   `-mps-float` + `__ps_t` element copies: **fn_800FF030, fn_800FF478**
   (both were parks of exactly this shape).
2. Members with genuine V-form usage (`vmsumshm`, `vsel`, VRc/V5 fields per
   §6r-93) remain walled — the correction only covers pair-move encodings.
3. Tooling note: raw-word inline asm (`.long 0x...`) DOES assemble through
   ngcas — this doc's wall applies to MNEMONICS, not raw words.

## members (2026-08-25, 0x801EFxxx zone)

| Address | Size | Best | Notes |
|---|---|---|---|
| fn_801EF3A8 | 0xA4 | 42.1% | genuine `vmsumshm/vmhaddshs` block (0x11ADxxxx words, VD bits set) interleaved with psq_l pairs at 0x801EF3F4–0x801EF420; `__ps_t`/`__builtin_ps_*` probes emit lis/stw/lfd instead |
| fn_801EF44C | 0x104 | 2.8% | same VMX tail at 0x801EF4DC + stfd f31 FPR frame; loop/count logic before it is close |

Both verified against the §6r-93 V-form discriminator (VD in bits 6-10 +
VRc/V5 fields) — these are genuine walls, NOT the vpkuhum pair-move
mislabel class. Do not re-test with -mps-float.
