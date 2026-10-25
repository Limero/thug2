# 92 — objdiff relocation-form undercount (source-backed units scored below 100 %)

**Status: OPEN (2026-10-23).** 52 functions / 18,120 bytes. The linked DOL is
byte-identical for every one of them; they are counted as unmatched only
because of how objdiff compares a relocation-bearing word. Four members have
been converted so far (+2,044 B counted); the two sub-kinds at the end are not
reachable from C at all.

## Symptom

A `report.json` unit has `metadata.source_path` (it is compiled from `src/`),
`complete: true`, and a size that matches `symbols.txt` — but it has **no
`matched_functions_percent`** and its function sits at a fuzzy score of
99.4–99.96 %. Consequently:

* `PROGRESS.md` counts the function as unmatched,
* `src/wip/fn_XXXXXXXX.c` does not exist (the draft was deleted on promotion),
  so the function looks like a "no draft" park, and
* the ledger lists it with `state=uncounted` rather than `state=remaining`.

## Cause

The target object carries a relocation on the data access
(`R_PPC_ADDR16_HA` on the page half, `R_PPC_ADDR16_LO` on the access half),
while our object folded the same address into a **raw page literal plus a
displacement** (`lis` of `0x8030xxxx` and a negative/positive offset with no
relocation at all). Both link to the same address, which is why the DOL stays
identical; objdiff compares the *argument form*, sees a relocation on one side
and an immediate on the other, and scores the word as a partial argument
mismatch. The function-level score is then a fraction of a byte short of 100 %.

This is the doc-51 raw-literal pattern showing up on the *verification* side
rather than in the code: the body was written with a page literal because that
spelling was what produced the wanted register/`lis` shape.

## Identification

```sh
tools/venv/bin/python tools/wip_ledger.py --summary      # state=uncounted count
build/tools/objdiff-cli diff -p . -u main/fn_XXXXXXXX fn_XXXXXXXX \
      -o - --format json | grep -c DIFF_ARG_MISMATCH
```

The diff rows name the target relocation
(`lis rX, lbl_XXXXXXXX@ha`, `lwz rY, lbl_XXXXXXXX@l(rX)`) next to our
`lis rX, 0x80xx` + folded displacement.

## Fix, when it is free

Re-spell the page base as the symbol so the compiler emits the same relocation,
keeping any register pin only if the codegen stays identical. Verify in this
order — the masked scorer alone cannot see the difference:

1. `tools/score_body.py` still reports EXACT 100 %,
2. `objdiff-cli diff` reports **zero** `DIFF_ARG_MISMATCH` rows,
3. `cmp orig/G2TE52/sys/main.dol build/G2TE52/main.dol` still passes.

Worked examples, all verified with an unchanged DOL:

* `fn_8004A800` (1480 B) — two sites of
  `page = (char *)0x80300000; g = *(Unk_C7387A53 **)(page - 0x168);`
  rewritten as `page = lbl_802FFE98; g = *(Unk_C7387A53 **)page;`. Four
  argument mismatches disappeared.
* `fn_801D478C` (256 B) — a struct view of the page
  (`((Unk_DF48702C *)page)->unk0x3150`) replaced by the registered scalar
  `lbl_80303150`; the dead page pin and its literal were dropped. Two
  mismatches disappeared.
* `fn_80222660` (`ScriptFoundServers`, 80 B) — the promoted body carried four
  `register ... __asm__("rN")` pins with a literal page and a `mr` pin asm;
  rewriting it as plain C (`head = *(SNode **)((char *)(*(SMgr **)&lbl_80305F9C)
  + 0x184);`) with only the two empty-asm barriers kept the masked bytes exact
  and cleared the last mismatch. The lesson generalises: if the *only* reason
  for the page literal is to steer a register, try removing both the literal
  and the pin — the allocator frequently lands on the same register anyway.
* `fn_80186DF8` (248 B) — one `__asm__("lis %0,%1@ha")` pin feeding a single
  `*(s32 *)(pg + 0x5EAC)` access. Dropping the pin and spelling
  `*(s32 *)&lbl_80305EAC` restored the relocation; the only residue was a
  scheduling swap (`mr r28, r3` emitted before instead of after the `lis`),
  fixed by moving the pinned argument copy (`a0 = arg0;`) one statement later.
  Has `-fno-strength-reduce -fno-schedule-insns2`; the flags are unrelated.
* `fn_8015C5F0` (`ScriptReinsertSkaters`, 184 B) — two page pins; both
  accesses were single, so both re-spelled as `*(s32 *)&lbl_80305EAC` /
  `*(volatile s32 *)&lbl_802FFE98`, pins deleted, zero residue.

The shape that converts is therefore **one access site per symbol** (plus, if
needed, one scheduling reorder of a pinned argument copy). One access is
necessary but *not* sufficient: the page register must also be hoisted to the
same slot and land in the same register, and that is where most members die.
Measured examples of the residual after a clean single-access rewrite:

| function | size | residual |
|---|---|---|
| `fn_800BD96C` | 360 B | the `@ha` page `lis` sits one slot after the second of two preheader zero-inits instead of between them (91/91 words, one displacement) |
| `fn_80014FCC` | 140 B | the `@ha` `lis` for `lbl_803CAF54` is emitted at the store instead of before the callback `lis`, and takes r9 instead of r10 |
| `fn_800AB604` | 520 B | the `@ha` `lis` stays inside the loop instead of being hoisted to the preheader |

Roughly two in ten single-access members convert. Everything below is where
that stops working.

## Do not force it

In several members the page literal is **load-bearing for the masked shape**:
`fn_80059A30`, `fn_80186F60`, `fn_801FA534` / `fn_801FA58C`, `fn_8022B000` and
`fn_8000CCF4` all hold an exact register/`lis` slot with the literal (or with an
`__asm__("lis ...")` pin, `fn_8000CCF4`), and spelling the symbol changes the
allocation and drops the masked score. Those stay uncounted — the bytes are
already exact, and this class is a reporting artifact, not a decomp gap. The
only cost is that `PROGRESS.md` under-reports by the size of the class.

### Sub-kind A — one page register shared by several accesses

`fn_8013881C` (900 B), `fn_80138F84` (776 B), `fn_800A234C` (228 B) and the rest
of the `lbl_8029F3F8` / `lbl_80301A44` members. The original keeps the `@ha`
page in a callee-saved register across the whole body and reuses it for 2–4
`@l` accesses; plain C re-materialises the `lis` at each site, so the object
gets *longer* (32 B in `fn_8013881C`) and every downstream address shifts (the
linked-DOL r2 init then fails its sanity assert, which is the symptom to expect
here — not a `patch_dol` bug). Pinning the value register narrows the residual to
the page register and then to a single rematerialised `lis`, never to zero.
C cannot name "the `@ha` page of a symbol", so this sub-kind is out of reach
without an asm `lwz %0,%1@l(%2)` transcription, which is banned.

### Sub-kind B — target shows `@h` + `ori`, ours shows `@ha` + `addi`

`ScriptSetEventHandlerOnObject` (`fn_8010EC1C`), `ScriptSetEventHandler`
(`fn_80117620`) and friends that pass `0x80367192` as a flag value. The word in
the DOL is a *raw* `lis 0x8036` + `ori 0x7192`; dtk's disassembly reconstructed
`R_PPC_ADDR16_HI` / `LO` relocations on `lbl_80367192` from it, so the expected
side has relocations our object cannot have. Every C spelling of the address
(`(s32)&sym`, `(u32)&sym`, cast through an array/struct, masking, `+0`) makes
ngccc emit `@ha` + `addi` instead (verified by compiling each form standalone),
which changes the instruction as well as the relocation. Keep the literal; the
DOL stays identical and the function stays uncounted.

### Sub-kind C — target `addi rX, rY, sym@l` from a page register

`fn_801399D8` (296 B) and the `-0xCB0`-style members: our body computes
`tag = (s32)pg - 0xCB0` from a pinned `@ha` page, the target's body starts from
the symbol (`tag = (s32)lbl_8029F350;`). That spelling does restore
`lis @ha` + `addi @l`, but ngccc then folds the `lis` into the *destination*
register when the value is pinned (giving `lis rX`/`addi rX, rX`) and moves a
live-range pair when it is not, so the residual never reaches zero. Same wall as
A: the original interposed a scratch register that C cannot request.
