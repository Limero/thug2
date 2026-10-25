# Issue 50 — Linker branch relaxation diverges from retail (masked-EXACT ≠ linked-EXACT)

**Status: NEW WALL (2026-09-03). One known victim; diagnose-only.**

## Symptom

A draft compiles **masked-EXACT** (compile_fn 100%, relocation-masked compare)
and its linear instruction stream equals retail word-for-word — yet the
**linked DOL differs** inside the function, with no section/header shift
anywhere.

Exemplar: `fn_801D2C58` (0x801D2C58, 0x13C bytes). Post-link diff: 4 bytes at
fn+0xDE/fn+0xF6 — two conditional-branch displacements.

## Mechanism

The object encodes the two conditional branches (`blt`/`bne`) with **+0x70
displacements and R_PPC_REL14 relocations**, targeting an *out-of-line tail*
placed after the epilogue (obj+0x12C: `li r10,1; mr r3,r10; addi r1; blr`) —
identical to retail's post-link shape.

`mwldeppc` then **relaxes** both branches backward to the semantically
identical in-function tail at fn+0x70 (`li r3,1; b epilogue`), while the
original retail link kept the forward targets (`41800050` / `41820038` →
fn+0x12C). Result: `4180ff94` / `4182ff7c` in our build. Both tails return 1
via the same epilogue — a semantic no-op, but 4 byte-level diffs.

## Why it escapes every existing gate

- `compile_fn`/`test_wip_drafts` mask REL14 displacements (correctly, in
  general) → the draft scores EXACT.
- The divergence only materializes at the **final link**, and
  `promote_wip.py`'s DOL compare then auto-reverts the whole batch.

## Not source-reachable

The C source that reproduces the flow compiles to exactly this object — the
choice belongs to the linker's relaxation pass, not the compiler. Any
source-level reshuffle either keeps the object identical or craters the
masked score.

## Path forward

1. **Gate**: add a link-level REL14-target check to promote_wip.py (simulate
   relaxation or diff branch targets post-link) so this class fails fast with
   a diagnosis instead of a DOL-DIFFERS revert.
2. Investigate whether a linker option (e.g. disabling branch relaxation /
   `-relax` off in mwldeppc) reproduces the retail link environment.

## Members

| fn | state |
|---|---|
| fn_801D2C58 | parked, full diagnosis in draft header; do NOT re-promote without the link check |
