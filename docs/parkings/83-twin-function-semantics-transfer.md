# 83 — Twin-function semantics transfer: read the parked neighbour's matched twin before attacking anything

**Status:** method + two reusable rules. Exemplar `fn_800F46C8` (304B) went
**DIFF 7.9% → EXACT 100.0%** in a single attempt; the whole recovery came from
reading an already-matched *twin* (`fn_800F4130`) in the same neighbourhood,
not from m2c, flags, or scheduling guesses.

All findings verified on ProDG/3.9.3 with the default game flags
(`-O2 -G0 -mcpu=750 -fno-common`), pure C, no asm, no hard-register pins.

---

## 1. The method: a parked "big frame" draft is usually a twin with a solved sibling

Before attacking an m2c draft, run
`rg -n "fn_<one of its callees>" -g '*.c' src` and read **every** hit. Script/
container loaders in this game are template-generated near-duplicates: the same
callee cluster (`fn_800F3690`/`fn_800F36C8` handoff, `fn_800F49A0`, `fn_8001371C(buf,
flag ^ 1, 0x64)`, `fn_800132A4`, `Mem_Alloc_3`, `fn_80013294`, `fn_800132F8`,
`fn_8001075C`/`fn_80010760` no-op leaves, and the `mtlr`+`blrl` vcall through
`self->unk0x50`) recurs in a run of functions with only *one* or *two* arguments
changed between them. When one member of the run has a MATCHED body, the m2c
draft's "HUGE frame vs got" wall is not a wall at all — it is the twin's
`char buf[256]` local plus the twin's real parameter list, both of which you can
read off instead of guessing.

Known runs in `0x800F3xxx-0x800F4xxx` (all share the callee cluster above):

| want | role | state |
|---|---|---|
| `fn_800F4130` | add-model | EXACT (2026-10-02) — the reference |
| `fn_800F46C8` | add-model (no heap-accounting enter/leave) | EXACT (2026-10-02, this doc) |
| `fn_800F47F8` | script-add | parked 16.1%, "HUGE frame -0x120 vs got -0x20" — same `char buf[256]` at `r1+8` (want 0x800F4864/0x800F4874) |
| `fn_800F429C` | script-add-array | parked 17%, "HUGE frame -0x128 vs got -0x30" |
| `fn_800F3BB0` | two-buffer variant, `char sp8[0x100]; char sp108[0x100]` → `-0x218` | parked; same rule, two buffers |

**Rule 1 (transfer, then delta).** Copy the matched twin's body, then change
*only* what the two wants actually differ in. Count the diffs by hand against the
two `want_dis.py` dumps side by side; each remaining difference is a real
semantic delta (a different sprintf helper, `+0x14` vs `+8` on the `strcpy`
destination, `unk0x10` vs `unk0x4` as the third sprintf argument, an extra
prologue/epilogue pair) and each one is usually a one-token edit.

## 2. Deriving the local's byte count from the prologue

The frame layout ngccc emits (offsets from the new `r1`, `stwu r1,-N(r1)`):

```
0x00  back chain / arg spill            8 bytes
0x08  locals                            <your char buf[N] / struct>  (+ 0 or 4 slack)
      saved nonvolatile GPRs            4 bytes each, stmw r27 / stmw r25 ...
      4 bytes                           gap
      saved LR                           `stw r0, <savebase + 4*nsaved + 4>(r1)`
```

So **`locals_bytes ≈ (LR_offset - 4) - 4*nsaved - 12`**, i.e. subtract 12 for the
8-byte header and the LR gap and you get the stack-local byte count (±4).
Worked examples: `fn_800F46C8` want LR@0x124, 5 saved ⇒ 256 ⇒ **`char buf[256]`**
(this single fact accounts for the whole 0x120 vs 0x28 frame gap that had the
draft at 7.9%); `fn_800F4130` LR@0x12C, 7 saved ⇒ 256, same local; a 4-byte-local
probe gives `savebase 0x10` ⇒ 4. Both locals land at `r1+8`, which is what the
want's three separate `addi r3,r1,8` argument setups show.

**Rule 2 (a dead parameter is NOT homed — and that alone moves the frame).** This
is the whole explanation for the prologues of a twin pair differing, and it needs
no flag or cast. Parameters live in `r3..r10` on entry and are copied into
callee-saved registers only when they must survive a call:

* `fn_800F4130` calls `fn_80010D94` *before* using any parameter ⇒ all six
  parameters are live across a call ⇒ six callee-saved homes ⇒
  `stmw r25` (7 saved with the global base) and frame `0x128`.
* `fn_800F46C8` has no such early call ⇒ `p4` (which arrives in `r6`) is dead
  after the first `bl`, so it is passed through in `r6` untouched and never
  homed ⇒ 5 saved ⇒ `stmw r27` and frame `0x120`.

Corollary for triage: when a want's save count is one lower than your draft's and
the missing home is a middle parameter, look for a call in the *prologue* of the
want (or the absence of one in the draft) before touching the allocator. Keep the
parameter count equal to the highest incoming argument-register the want reads —
a 6-argument `self, name, flag, a3, a4, a5` signature with an unused `a3` is not
optional.

## 3. Non-transferable bits that are *not* re-derivable (all re-confirmed here)

* **Every callee needs a real prototype.** The m2c draft declared none, which put
  `crclr cr1eq` before all seven `bl`s and cost ~40 points of word alignment.
  Return types matter as types (`void *Mem_Alloc_3(u32)`), not just arity.
* **`self->unk0x20` must be re-read, never staged.** The want loads it three
  times in the `flag != 0` arm; holding it in a local lets ngccc forward the
  `= 0` store into the `|= 8` load and deletes the whole `lwz/ori/stw` RMW
  (object 20B short). Write the two statements as two full paths.
* **Vtable layout:** `char pad[0x68]; s16 name; char pad[2]; void (*fn)(void*)`
  — the `lha` reads the s16 *member name* at 0x68 and the `lwz` the pointer at
  0x6C. A pad sized to the *offset* instead of the member silently shifts the
  pair.
* **Label arguments:** `(s32)fn_800F39DC` (a function address) gives retail's
  `lis`+`addi`; casting a `char[]` global to `s32` folds to `lis`+`ori` (doc 51).
* **doc-28 does not apply.** The two `mtcrf 0x80, r29` sites (with `mfcr r29`
  before the first `bl`) come out of plain `if (flag != 0) {...} ... if (flag == 0)
  {...}` because ngccc CSEs the `cmpwi flag,0` across the intervening calls by
  saving CR once in the (dead) `p6` home. Do not reach for pins.

## 4. Residual / promotion state

`fn_800F46C8`: 304B object == 304B want, zero masked diffs, no `.rodata` section
in the object at all, no `_dummy` injection, no flags, all 15 relocations
symbolic (13 REL24/REL14 + the HA/LO16 pair for `fn_800F39DC`). It is a
legitimate EXACT, but it stays **inert** — promoting is a separate, manual step
(`// range=0x800F46C8-0x800F47F8 size=304B` still matches `symbols.txt`).
`fn_800F47F8` / `fn_800F429C` are the obvious next users of this transfer.