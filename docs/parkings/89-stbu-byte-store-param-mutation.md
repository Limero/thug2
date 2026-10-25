# 89 — `stbu`/`stwu` is a WIDTH + DESTINATION finding, not a scheduling wall

**Date:** 2026-10-05 · **Status:** SOLVED (exemplar EXACT, unpromoted)
**Exemplar:** `fn_80129574` (248B, 96.8% → **100.0%**, default flags, no pins, no asm)
**Class:** call it "update-form store" (`stbu`/`stwu`/`stbu`-family).

---

## The symptom

A want contains an update-form store in the middle of a store/return region: at 0x801295CC a byte store of r27 to offset 0 of r28 writes the tag byte, at 0x801295D0 a byte-store-with-update of r31 to offset 1 both stores and bumps r28 by 1, and at 0x801295D4 the return value is formed as r28 plus 1 into r3, equal to the incoming base plus 2.

Plain C cannot produce this. Every local-variable spelling emits the same three words in a different order, or emits the non-updating form: the tag byte store stays at 0x801295CC, the return value is computed up front at 0x801295D0, and a plain word store without update appears at 0x801295D4.

The previous park note on this draft blamed *scheduling* ("ngccc's combine folds
the bump into the return's constant before reload, so the increment never
survives to be fused into a post-increment store form") and listed ~12 rejected
spellings. **That diagnosis was wrong on two counts**, and both are cheap to
check.

---

## Rule 1 — read the store WIDTH out of the opcode before writing the C

`stbu` is **store BYTE and update**. It is not a spelling of `stw`.

The draft had `*(s32 *)((s8 *)arg0 + 1) = i;` — a **word** store. That single
wrong width is enough to forbid `stb`/`stbu` from ever appearing, no matter how
the pointer arithmetic is written. In this family the byte width is *semantically*
right too: the value being stored is a small lookup-table index, and the
neighbouring branches of the same function write a one-byte tag and hand a
cursor to a callee — a packed byte stream, not a struct of fields.

Generalised: `stbu` ⇒ `*(u8*)p = v` (with the destination's increment fused),
`stwu` ⇒ `*(u32*)p = v`, `stfsu`/`stfdu` ⇒ float/double. Never infer the width
from how many bytes the surrounding code looks like it is moving.

**Check first, because it is free:** the disassembly already told you. A parked
note that says "we need `stbu` but C gives `stw`" has usually misread `stw` as
the target when it should have questioned the source's element type.

## Rule 2 — the update form needs the bump on the variable the RETURN reads

Even with the correct byte width, an update-form store only appears when the
bumped pointer is *the same live value the subsequent use reads*. Two ways to
satisfy that, and only one of them works:

| spelling | emitted |
|---|---|
| `*(s8*)((s8*)arg0+1) = (s8)i; return arg0+2;` | `stb` + hoisted `addi r3,r28,2` |
| `s8 *p = (s8*)arg0; *p = tag; p++; *p = (s8)i; return p+1;` | `stb` + `addi r3,r28,2` |
| `s8 *p = (s8*)arg0; *(s8*)(++p) = (s8)i; return p+1;` | `stb` + `addi r3,r28,2` |
| **`arg0++; *(s8*)arg0 = (s8)i; return arg0+1;`** | **`stbu` + `addi r3,r28,1`** ✅ |
| `arg0 = (s8*)arg0 + 1; *(s8*)arg0 = (s8)i; return arg0+1;` | `stbu` + `addi r3,r28,1` ✅ |
| `*(s8*)(arg0 = (s8*)arg0 + 1) = (s8)i; return arg0+1;` | `stbu` + `addi r3,r28,1` ✅ |

The three that work all mutate the **parameter** (the callee-saved home `r28`)
in place. Every variant that copies the pointer into a fresh local loses: the
local's live range is identical to `arg0`'s, so local-alloc coalesces them,
combine sees the increment as dead, and folds it back into the return's
constant offset. The bump has to survive as a *register modification of a value
that outlives the store* — a local that dies at the store does not qualify.

This is the mirror image of **doc 88** (two named pointers to keep one address in
two registers) and of **doc 85** (pin a short-lived alias so a copy survives):
here the lever is the opposite, *merge* the two webs back onto the parameter.

Note the `arg0++` form needs no cast at all — the parameter is `void *`, and
`void *` arithmetic is a GNU extension that ProDG accepts silently.

---

## Scan hint

`stbu`/`stwu`/`stfsu`/`stfdu`/`lmw`-with-update in a want, with a `stX` of the
non-update form in the draft ⇒ check the store width first, then check whether
the bumped pointer is a local or the parameter.

The signature of a mis-parked member is a park note that
(a) names `stbu`/`stwu` explicitly as the blocker, and
(b) lists several pointer-local spellings among the "tried and rejected" set.
Those are exactly the two rules above.

---

## Cross-references

- **doc 88** — keep two registers for one frame address (the *opposite* lever).
- **doc 85** — pin a short-lived alias to force a scratch birth + arg remat.
- **doc 86 §7** — address-taken scalars vs `volatile` objects and locals-area
  placement; relevant because Rule 2's working form changes what is
  address-taken.
- **recipes 7c** — the "only an increment textually between the stores ever
  fuses" claim this note supersedes: the increment fuses when the *variable* is
  right, not when the statement position is.