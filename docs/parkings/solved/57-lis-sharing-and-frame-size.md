# 57 — `lis` sharing: the address of a symbol used twice, and how the *frame
size* tells you the buffer

**Status: SOLVED — this doc is the recipe that closed `fn_801FBE60` (124B,
promoted 2026-09-15, DOL byte-identical) from a 71% draft in one pass.**

## What it is

Retail materialised a rodata symbol's address as a shared high-half load into a callee-saved register followed by a low-half add into a different destination register, while ngccc emitted the ordinary two-instruction form with **one** register reused for both halves. The tell that this is *not* a regalloc coin is
the frame: want also saves `T`, so want's frame is bigger and the `stmw/lmw`
line differs.

## Why it happens

MWCC materialises a symbol address once and *shares* the `lis` when the same
symbol is referenced more than once in a function. Shared `lis` needs a
register that survives the intervening code — including calls — so the
allocator is forced into a callee-saved register, and the `addi` at each use
site cannot coalesce with it. Matched exemplars:

| fn | evidence |
|---|---|
| `fn_801F707C` (104B, matched) | `lis r29,-0x7fd5; addi r4,r29,-0x1c80` … `addi r4,r29,-0x1c80` — same symbol used by both calls |
| `fn_80018DEC` (64B, matched) | `lis r31,-0x7fce; addi r3,r31,-0x4d8` twice (`lbl_8031FB28`, 2 uses) |
| `fn_80121798` (220B, parked 90.9%) | `lis r30; addi r29,r30` — `lbl_8039BA58` used twice (`+0x0` and `+0x90`) |
| `fn_801FBE60` (124B, **solved here**) | `lis r28,-0x7fd5; addi r4,r28,-0x1a4c` — see below |

A whole-DOL scan for `lis rT(callee-saved)` followed by `addi rD!=rT,rT` finds
only **4** functions, so the shape is rare but unambiguous when it appears.

## The `fn_801FBE60` case in full

Draft was 71.0% (`-fno-expensive-optimizations`). Want loads the list head into r31, homes arg1 in r29, zeroes the counter in r30, null-tests the head with an early null return, hoists the format-string high half into callee-saved r28, and enters the loop at the low-half address computation (which is also the back-edge target at offset 0x60): each iteration copies the counter into the next argument register, takes a stack buffer address, keeps the ABI marker, calls the formatter, re-takes the buffer address, calls the comparator, compares the saved arg1 against the result with a not-equal branch, returns the saved head on match, otherwise advances the head via its offset-4 link, increments the counter, null-tests the new head, loops back on non-null, and returns null at the end.

Three independent levers, all needed:

1. **The format string was a raw `0x802AE5B4` literal.** Passing an integer
   constant makes ngccc emit `lis+ori` (a *value*), not `lis+addi` with the
   `@ha/@l` pair (an *address*). Use the rodata symbol + a prototype:
   `extern char lbl_802AE5B4[]; s32 sprintf();`.
   Note `sprintf` needs the prototype **without** varargs — with `-mno-…`
   defaults the bare `s32 sprintf();` form is what keeps `crclr cr1eq`
   (which want has at `+0x34`) and avoids the implicit-decl `lis+ori`.
2. **The local buffer is `char sp8[0x38]`.** Frame size is a *solvable*
   constraint, not a guess: want's frame is `0x50` and the only locals region
   before the `stmw` slot at `0x40` is `8..0x40` = **0x38** bytes. Sweeping
   buffer sizes 0x18/0x20/0x28/0x30/0x38/0x40 gives frames
   0x30/0x38/0x40/0x48/**0x50**/0x58 — the frame size picks the buffer for you.
3. **The loop must be written as the plain `while`**, not m2c's
   `if (p != NULL) { loop_2: … goto loop_2; }` idiom. With the m2c shape the
   `lis` stays *inside* the loop and coalesces with the argument register
   (71%); with `while (var_r31 != NULL) { … }` the `lis` is hoisted out of the
   loop into the callee-saved temp and r28 appears (100%). This is the whole
   point of the frame-size check: the hoisted `lis` is what forces r28, and
   r28 is what makes want's frame 0x50.

Final source (byte-exact, default flags):

```c
extern char lbl_802AE5B4[];
s32 sprintf();
s32 fn_80131A88(s32);
void *fn_801FBE60(Unk_C7387A53 *arg0, s32 arg1) {
    char sp8[0x38];
    s32 var_r30;
    Unk_2EF06E12 *var_r31;

    var_r31 = arg0->unk0x24;
    var_r30 = 0;
    while (var_r31 != NULL) {
        sprintf(sp8, lbl_802AE5B4, var_r30);
        if (arg1 == fn_80131A88(sp8)) {
            return var_r31;
        }
        var_r31 = var_r31->unk0x4;
        var_r30 += 1;
    }
    return NULL;
}
```

## How to find candidates

- Scan the DOL for `lis rT` + `addi rD,rT` with `T != D` and `T` in r14..r31
  (the `tools/` one-off that found the four members above is ~20 lines of
  `struct.unpack` over the text section).
- Whenever a draft's residual is **only** the prologue `stmw`/`lmw` line plus
  a `lis` register number, check the symbol for a second reference before
  blaming the allocator.

## Companion truth: the buffer size is derivable

For any `sprintf`/`strcpy`/`memcpy` draft whose want frame differs, sweep the
buffer size — the frame is `8 + locals`, and the locals extend to the saved-GPR
slot (`stmw rX, N(r1)` sits at `frame_size - 16` for MWCC). `fn_80055CB0`
(2026-09-15) was closed from 71.7% → 82.3% by exactly this kind of arithmetic
plus the doc-53 width retype.

## ADDENDUM 2026-09-15 (e): the frame size is also a *source-shape* tell

`fn_80125020` (104B) was 14.8% with `stwu r1,-0x18` / `stmw r29,0xc(r1)` where
retail has `stwu r1,-0x10` / `stmw r30,8(r1)` — one fewer saved register and 8
bytes less frame, so the whole body after the prologue slid one word.

Cause was an m2c local temp:

    fs_t = (char *)fn_800105CC(lbl_80303190);   // m2c's invention
    *(s32 *)&lbl_80303188 = temp_r3;
    lbl_8030318C = fs_t;

Holding the malloc result in a C local keeps a pointer live across **both**
calls, which costs an extra callee-saved register (r29) and pushes the frame
from 0x10 to 0x18. Retail instead stores the result straight into the u32 global
and *reads it back* — MWCC CSEs the reload away, so no register has to survive:

    lbl_80303188 = (u32)fn_800105CC(arg0);
    lbl_8030318C = (char *)lbl_80303188;        // 100%

Both forms are byte-exact; the read-back one is smaller and matches the draft's
own `temp_r3` (m2c emitted a *bare, uninitialised* temp, which is the tell).

## Addendum 2026-09-21 — sharing one `lis`: hoist the base into a local

m2c writes every access to a big global object as `lbl_XXXX + off`, so ngccc
materialises the address **per access** (`lis`+`ori` each time) while retail
materialises it once into a callee-saved register and then uses
`disp(r31)`. Two promotions came out of this in one batch:

* `fn_8012156C` (184 B, 47.8 % → **100 %**): bind the base once —
  `char *base; base = lbl_8039BA58;` then `*(s32 *)(base + 0x2C4)`, … — and
  retail's single `lis r9,-0x7fc6; addi r31,r9,-0x45a8` plus
  `lwz r29,0x2c4(r31)` falls out. The draft recomputed `lbl_8039BA58 + off`
  at all ~12 sites. Same draft also had m2c's **scaled-pointer-arithmetic** bug
  (`*((s32 *)p + n)` = `n*4` bytes) at the `slwi` site: the fix is a byte
  displacement off the same base, `*(s32 *)((char *)temp_r9 + idx*0x10)`.
* `fn_80120464` (104 B, 46.7 % → **100 %**): when several adjacent addresses sit
  inside ONE symbol, index it — `lbl_8038F714` is a 0xC-byte object, so
  `&lbl_8038F714[0..2]` gives retail's `addi r3,r3,-0x8ec` base plus
  `addi r4,r3,4 / addi r5,r3,8`. The draft's raw literals `0x8038F718`,
  `0x8038F71C`, … have **no symbols of their own** (the object is one 0xC blob),
  so `tools/fix_raw_lit.py` cannot rewrite them — the array form is the only fix.

Both are the same diagnosis: **`lis` is shared iff the source keeps one base
value live**, so check `symbols.txt` for the containing object's size before
reaching for raw literals.

Tool: `tools/frame_only_scan.py` lists drafts whose only diffs are the
prologue/epilogue (`frames=want/got`). It found only this one hit in the
1,787-draft no-park pool, but the shape generalises: **`frame + 4` together with
exactly one extra callee-saved register is almost always a redundant m2c local
temp.** `tools/shift_scan.py` is the wider version — it slides `got` against
`want` by ±N words over the body and reports drafts that match once aligned,
which is how this one was spotted (14.8% → 100%).
