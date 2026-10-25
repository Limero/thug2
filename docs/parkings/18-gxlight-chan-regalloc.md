# 18 — GXSetChan* regalloc coin-flip (GXLight.c)

## Symptom

`GXSetChanAmbColor` (0x80289AE4, 0xF4) and `GXSetChanMatColor` (0x80289BD8,
0xF4) are parked as auto-asm. The rest of `gx/GXLight.c` — `GXInitLightSpot`
(0x802898BC), `GXInitLightPos` (0x80289A4C), `GXInitLightColor` (0x80289A5C),
`GXLoadLightObjImm` (0x80289A68) — is wired byte-exact (M8.2x).

## Facts established

- **C signature is `GXColor` BY VALUE** (corrected 2026-08-26; an earlier
  revision of this doc claimed `GXColor*` — superseded). The current header
  declares `void GXSetChanAmbColor(GXChannelID channel, GXColor color);`
  (`libs/dolphin/include/dolphin/gx/GXLight.h`, fixed per
  [21](21-gxinit.md)). The DOL still *dereferences* r4 (`lwz r0, 0(r4)` in
  GXInitLightColor; `lbz r7, 3(r4)` in the Chan functions) because mwcc's
  by-value 4-byte-struct ABI makes the CALLER copy the struct to a stack temp
  and pass its address. Do not flip the header back to pointer form.
- **`gx` is an `.sbss` global** (`lwz rX, -0x6218(r13)`), reloaded per use.
- Both functions are 244B in the DOL (61 insns); best GOT is 240B (60 insns)
  with every source form tried.

## Root cause (pure regalloc, doc-10 class)

The DOL emits, per color case: a rotate-and-mask of r0 into scratch r0, a copy from r0 into the register home r7, and an in-place merge of r3 shifted by 8 into r7.

GOT (all mwcc versions 1.0–3.0a5.2, all `-O4`/`-schedule`/`-ipa`/`-opt`
combinations, all decl orders, `register` hints, one-liner vs multi-statement
vs temp-mask forms) instead fuses the mask into the reg home (`clrrwi r7`
or `rlwinm r7, r7, 0, 0, 0x17`) and merges in place — 1 instruction short.
ALPHA0 (first switch case) additionally gets a scratch+move where the DOL
loads directly into the reg home; ALPHA1 already allocates correctly.

The DOL's per-case load order is also fixed: `gx` load, `li r5` (colorID),
color word, ambColor — with the amb load reusing gx's dead r3. No source
restructuring or flag combination reproduced this. Compare solved
`10-pure-regalloc-coin-flip.md` (same class, that one was cracked via decl
order; this one resisted all permutations).

## Attempted levers (all failed)

- GXColor by value vs pointer (by value is the correct ABI — see the
  corrected signature note above; neither form reached 244B)
- `const gx` vs non-const `gx` extern (non-const fixes ALPHA0 but shifts
  regs: colorID→r7/reg→r6 vs DOL's r5/r7)
- temp-mask / two-statement / one-liner `GX_SET_TRUNC` forms
- all 24 declaration orders; `register` hints on reg/colorID/color
- all mwcc versions 1.0–3.0a5.2; `-schedule off`, `-ipa`, `-opt`, `-O4` w/o `,p`
- caching `gx` in a local (breaks size to 224B)

## Status

**Parked (re-audited, 2026-08-26).** The earlier claim "no form
reaches the retail 244B" is SUPERSEDED: a mwcc-harness reconstruction using
the `__rlwimi` INTRINSIC with bfbb-form swapped operand roles
(`GX_SET_TRUNC(new_color_masked, old_stored, field)` instead of tww's
mask-reg-in-place), COLOR cases as expression form (rgb temp loaded first)
and ALPHA cases as statement form now reaches EXACT 244B size / 61/61 insns.
The residual is per-CASE-case `[mr]`/`[rlwimi]` transpositions + register
renames (55.7% masked word-match) — doc-15-class, park stands. Promote-time
prerequisite: `global.h`'s `extern int __rlwimi(...)` SHADOWS mwcc's
intrinsic (turning each merge into a real call + frame) — guard or remove
that decl before wiring these. Drafts refreshed in src/wip with full notes.

Parked. The 4 wired functions plus `.data` (jump table 0x80310598) and
`.sdata2` (0x803CC0C0..0x803CC0E8) are byte-exact. `lbl_803CC0E8` (8 floats:
-2, 0.5, 1.75, 0, 2.125, 0, -1e18, 0) is a merged object spanning
0x803CC0E8..0x803CC108 whose tail floats are orphans from dead-stripped
functions — it stays in the auto unit; the GXLight `.sdata2` split must end
at 0x803CC0E8 (object boundary), not 0x803CC0EC.
