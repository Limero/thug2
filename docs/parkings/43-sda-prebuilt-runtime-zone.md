# 43 — SDA-addressed prebuilt runtime-library objects (small-data ON)

**Status: OPEN (zone-level wall + promotion route). Identified
(2026-08-26).**

## Root cause

Whole regions of `main.dol` are the game's **prebuilt SDK/runtime library**
(Dolphin libc/libm, SN runtime) compiled with **small-data addressing ON**.
Every constant, string literal and table is materialized r13-relative: a word load from small-data offset -0x7e7c into r9, a float-constant load from offset -0x7b38 into f0, and a double load from small-data2 offset -0x7e00 into f1.

Game-code sources in this project compile `-G0` (absolute lis+addi), so a C
reconstruction can never emit those forms standalone — and the standalone
sweep (`test_wip_drafts.py`) cannot mask the resulting R_PPC_EMB_SDA21
(type-109) reloc words, so such drafts score as false DIFF even when every
instruction matches.

## The promotion route that WORKS (proven ×9 in)

1. Reference constants through real `extern` lbl symbols (never bare literals).
2. Add per-object flag line: `// FLAG: -msdata=eabi -GN`.
3. ngccc then emits SDA21 relocs; mwld resolves them vs `_SDA_BASE_` =
   0x803D2280 byte-identically at link (patch_dol leaves r13 accesses alone).
4. **Threshold is TYPE-WIDTH-dependent**: `-G4` routes f32 externs to SDA21,
   but f64 (8 bytes) falls back to HA/LO absolute → use `-G8`. Array externs
   need explicit sizes (`extern f64 lbl_X[3];`) and a threshold ≥ the largest
   object (`-G128`/`-G256` probed working).
5. Standalone verification: `tools/sda_verify.py <addr> <flags>` (wildcards
   the SDA21 words). `promote_wip.py` CANNOT verify these — register manually
   in configure.py (`Object(Matching, ..., extra_cflags=["-msdata=eabi","-GN"])`),
   build, rely on the linked-DOL cmp. Do not diagnose from `flagdiff.py`
   alone — it compiles flagged drafts through a different path than
   sda_verify and can show different regalloc on identical input.

** confirmations + extensions (2026-08-26):**

- The ProDG runtime zone 0x80273480..0x80274A78 is **gcc-2.95.2 libgcc2.c
  objects, one TU per `-D L_xxx`**: `__divdi3` (fn_8027353C), `__udivdi3`
  (fn_802740FC), `__umoddi3` (fn_802745E0) went LINK-SIM EXACT via faithful
  upstream ports (`static __inline__` to kill out-of-line helper copies;
  strip the always-NULL `rp` param for div/udiv flavors; union members must
  be s32 for `uu.s.high < 0` sign tests; longlong.h's nested-ternary clz
  spelling `< 0x100 ? 0 : 8` reproduces the subfic/subfe/rlwinm chain).
  Each object carries its OWN `static const __clz_tab` -> the .sdata2
  copies lbl_803CBC3C/CBD3C/CBE3C/CBF3C; `-G256` is the probed threshold.
- fn_8028E008 (zone-edge, after GXStubs) is also ProDG+SDA (-G4).
- mwcc-compiled SDK zones need a DIFFERENT verifier:
  `tools/mwcc_verify.py <addr> <file.c>` (GC/1.2.5n harness, dolphin-lib
  cflags, SDA21 link-simulation + HI(4)/HA(6)/LO(3) halfword masks). The
  ngccc-only sweep/sda_verify cannot score those objects.

 link-sim EXACTs landed this way: fn_8026D1B4 (-G4), fn_8026E5B8
(-G4), fn_8027052C (-G8), fn_80270174 (-G8), fn_80270290 (-G8),
fn_802704A4 (-G8), fn_80273268 (-G4), fn_80271A34 (-G4), fn_80271538 (-G8).

 (2026-09-05): `tools/sda_verify.py` now also resolves ADDR16_HI
(type 6) and ADDR16_LO (type 4) relocs — the lis/addi address pairs ngccc
emits for the next pass.bss/.rodata objects too large for SDA21 (e.g. the lbl_803CA240
printf base table under -G4). mwld's ADDR16_HI applies the +0x8000 HA
adjustment, and these relocs point at the immediate halfword (insn+2), not
insn+0. This unblocked link-sim EXACT for fn_8024C5A0 / fn_8024C474 /
fn_8024C5E8 / fn_8024EE00 / fn_8024EE6C / fn_80249898 (-G4) and
fn_802703EC / fn_80270FAC (-G8); `promote_wip.py` now promotes SDA drafts
end-to-end via sda_verify (no manual configure.py registration needed when
it passes).

## Members parked on the FULL wall (engine-scale + SDA together)

These are large prebuilt engines where even the §5q route doesn't rescue a
standalone rebuild — the body itself needs a multi-session hand rebuild AND
every probe of the flag route left structural gaps (frame/size mismatch):

| Function | Identity | Size | Parked @ |
|---|---|---|---|
| fn_8026BD70 | `__svfprintf_r` (float printf engine, 1297 insns; proof: "bug in vfprintf: bad base" literal, pad/digit tables, %e/%g consts) | 0x1444 | 1.9% |
| fn_8026D288 | `__svfiprintf_r` (integer-only twin TU — owns DUPLICATED rodata literals at +0x90 from BD70's) | 0x12F4 | 1.7% |
| fn_8026F55C | `pow(x,y)` modern e_pow.c (hand-rebuilt semantically complete; all 35 constants as lbl_* externs with computed SDA addresses documented) | 0x7D0 | 0.8% |

## Zone map (apply this reasoning wholesale before grinding any draft here)

0x80269xxx vsnprintf wrappers → fn_8026BC98 float-dispatcher →
{svfprintf BD70 / svfiprintf D288}; writer twins fn_8026BBC4/fn_8026D1B4;
format scanner fn_8026EEF0 reads `.sdata` words @CA40C/CA420; libm starts
~fn_8026FD2C (sqrt) / 0x80270xxx (sin/cos/kernels/pow/log family).

## Related tells discovered with this zone

- **Duplicate-literal tell**: neighboring functions owning byte-identical
  string literals at different addresses = separate TUs (identifies
  float/no-float engine pairs).
- **Crclr map for libc calls**: memcpy/udiv-style helpers keep want-side
  crclr cr1eq (leave the call implicit); named libc fns (strlen/memchr) need
  prototypes — per-site decision as always.

## Addendum 2026-09-19: three more members promoted with the route

`fn_80249A00` (16B, three `.sdata` pointer stores — the whole body),
`fn_8024C5D4` (20B) and `fn_8024C294` (280B, allocator/walker: indirect call
through 0x803CA320, `lbl_803CA330/334/338` counters, `lbl_803CA240` list walk
with inlined `memset`s). All three: `FLAG: -msdata=eabi -G4`, verified with
`tools/sda_verify.py`, promoted with the DOL byte-identical. Two source-shape
levers mattered beyond the flag:

- `fn_8024C5D4` — the residual was a store-order permutation (doc 09 addendum):
  three stores to *distinct* globals, written rotated.
- `fn_8024C294` — the one remaining word was `stw r3,-0x7f48(r13)` (retail) vs
  `stw r31,...` (draft). Storing a *local* that holds the call result makes
  ngccc copy it into the callee-saved home first; assigning the **call
expression straight to the global and reading the global back into the local**
  lets store-to-load forwarding keep the value in r3 (caller-saved), matching
  retail. Worth trying whenever a single store of a call result is in the wrong
  register.

Note both `fn_8024C294` and `fn_8024C5D4` had been parked with the verdict
"needs extra_cflags `-msdata=eabi -G4`" — that was only half the fix; the
*other* half was a plain source-shape defect. Re-test parked "SDA-only"
drafts at the SDA route before believing the residual is a wall.
