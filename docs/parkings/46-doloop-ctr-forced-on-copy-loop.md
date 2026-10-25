# 46 — Doloop CTR forced where retail used addic.+bne (inverse of 37)

**Status: PARTIALLY SOLVED (2026-09-24 isolated candidate).** `fn_800F4450`
now has a 340-byte masked-exact candidate with matching internal-branch
targets. `fn_80114BAC`, `fn_8000E48C`, and `fn_8000E978` are already promoted
as byte-identical. The `fn_800F4450` candidate has not yet been copied into
`src/wip/` or promoted, so this document stays out of `solved/` for now.
First catalogued on `fn_800F4450`
(skater-state alloc+copy script command, 340B) and `fn_80114BAC`
(`ScriptIntegerEquals`, 116B).

## The shape

Retail expands a 3-iteration struct copy (0x48 bytes, 0x18 stride, six-word records) as a bottom-test counted loop at offset 0x5C inside the non-NULL-arg1 arm: it holds the 0x48 byte count in r11, loads the base from offset 0x54 of r31, copies the destination pointer from r29 into r4, then per iteration loads a word through r4 and performs six stores, subtracts the 0x18 record stride from r11 with a condition-setting subtract that sets CR0, and branches back on non-zero, followed by a 3-word peel. (The count initialization noted in older text is implicit in the byte-count form.)

ngccc 3.9.3 instead recognizes the constant trip count and strength-reduces to a CTR counted loop: it derives iteration count 3 into r0, loads the base from offset 0x54 of r31 into r11, moves that count to the count register, copies the destination pointer from r29 into r4, emits the same six load/store body, advances the destination side by 0x60 with a plain add, and loops with a decrement-and-branch-on-count.

…shifting every subsequent instruction and costing ~22% of the function
mask. (The `li r0,3` in GOT is GCC's own derived iteration count; WANT's
`li r11,0x48 / addic. -0x18 / bne` counts BYTES, not iterations — the
original source evidently looped while `bytes_remaining` hit zero, and
the ProDG scheduler then interleaved the stores with the addic.)

## Why ngccc cannot reproduce it

Proven unreachable from plain C on 3.9.3 (2026-08-29 sweep, 13 loop
shapes):

- do-while with `var_r11 -= 0x18` at the bottom (control: 74.1%) → mtctr+bdnz
- for-loop with the test at the top → same CTR form
- `while (var_r11 != 0)` (pre-test) → same
- decrement embedded in the condition (`while ((var_r11 -= 0x18) != 0)`)
  → same
- `goto`-based loop with the test inside the body → 77.6% (best; CTR
  avoided at the cost of a different bookkeeping order)
- unsigned/u16/s16/long counter types → CTR form persists (narrower types
  add zero-extends and get WORSE: 28.2%)
- pointer-end comparison (`while (p < end)`) → kills the counted form but
  drags in an extra compare + different reg allocation: 27.1%

GCC 2.95's doloop pass converts ANY loop whose trip count it can prove
constant into the CTR form; retail's byte-count loop hid the count from
the same pass (its `addic.` sets CR0 as a side effect of the arithmetic,
not from an explicit compare — the exact construct GCC's own `bne` test
needs but never generates when the count is provable).

## What might crack it

- A way to make the trip count **unprovable but loop-invariant** at the
  point of the doloop analysis (doc 37's opaque-count tricks kill the
  counted form entirely instead — wrong trade here).
- `-fno-doloop`-equivalent flag on ProDG (none known; the flag set is
  fixed by the retail build).
- A paired-single or struct-copy idiom that emits the six stores without
  entering the doloop pattern matcher (e.g. via 3×`__ps_t` stores — the
  records are six words, so a 2+2+2 split could sidestep it).

## Detection tell

WANT bottom-test `addic. rX, rX, -stride` + `bne` where GOT shows
`li rN, K / mtctr rN / … / bdnz` around the same body. `grep` wants for
`addic\.` adjacent to `bne` inside copy loops.

## Known instances

- `fn_800F4450` (isolated-exact candidate, 2026-09-24; not yet in `src/wip/`)
- `fn_80114BAC` (promoted byte-identical)
- `fn_8000E48C` (promoted byte-identical)
- `fn_8000E978` (promoted byte-identical)

---

### Addendum (2026-08-30) — down-counter latch `mr r0,r31` copy sub-class

A different non-CTR member of the count-down-loop family surfaced in the low-address allocator/table-constructor zone: `fn_8000E48C` and its near-twin `fn_8000E978` (table constructors allocating a `(1<<k)*12` byte array and invoking a slot constructor on each 12-byte record). These stay a plain stepping-pointer plus down-counter loop without triggering the count-register conversion, but the latch bookkeeping differs by one copy: retail steps the pointer in r30 by 0xC, compares the live counter in r31 directly against zero, decrements r31 by 1 and branches back on non-zero, while the compiler build steps the same pointer, copies r31 to r0 as an extra move, compares the copy, then decrements and branches, so the compare runs against the copy rather than the live counter.

Historical pre-promotion note (superseded by the promoted sources): want
compares the live counter (`cmpwi r31,0` then `addi r31,-1`), a
copy-free compare-before-decrement; ngccc spills the reordered `left--`
post-decrement through `mr r0,r31` and compares the copy. Tried loop shapes
to drop the copy: `for(i=count;i>0;i--)`, `while(left!=0)`, do/while on
`--left`, plain `left--` post-decrement, guard `if(count!=0)` wrap — GCC
insists on the `mr`. The pre-promotion best (fn_8000E48C) was **18/31 (58%),
size-exact 128B**;
E978 mirrored it. The alloc tail stores and the loop entry PROLOGUE
(li 1/slw/mulli 0xc/addi count-1) matched exactly — only the 3-word latch
reorder diverged. Both were parked in `src/wip/` before promotion.

Route not found: `left = count - 1` pre-decrement with the compare BEFORE the
store is the want shape, but ngccc's scheduling of the post-decrement always
routes through r0. An opaque counter (`volatile`/asm-consumed) kills the
counted form instead — wrong trade (same as the CTR wall above).

---

### Addendum (2026-09-24) — `fn_800F4450` isolated-exact route

An isolated investigation found a plain-C candidate that scores masked
`EXACT 100.0%` over all 340 bytes and has no internal-branch-target
differences. The 3.9.3 candidate was independently re-scored here with the
standard body scorer; its accompanying probe validation reports empty masked
and branch-target difference lists, and its version matrix reports exact
results for all five installed ProDG point versions.

The load-bearing source changes are:

- Use the retail `0x48` byte counter rather than the older `0x30` draft value.
- Advance the destination through `(char *)` arithmetic so `0x18` remains a
  byte stride rather than being scaled as an `s32 *` element count.
- Keep the existing byte-count `goto` latch.
- Name the initializer/loop webs with `register` bindings:
  ```c
  register s32 *p9 __asm__("r9");
  register s32 *p11 __asm__("r11");
  register s32 one __asm__("r10");
  ```
- Reload the same destination base through `p9` and `p11` in alternating
  order during initialization so the allocator follows the retail register
  order.

The candidate carries `// FLAG: -Os`; it is exact with that project-supported
per-object setting, not with default `-O2`. These are ordinary C register
declarations, not emitted assembly instructions and not a whole-body
transcription.

The earlier “5-word records” wording is corrected above: the loop copies six
`s32` fields at offsets `0x00`, `0x04`, `0x08`, `0x0C`, `0x10`, and `0x14`.

Promotion still needs the normal standalone-exact check and linked-DOL
comparison after the candidate enters `src/wip/`. Until that happens, retain
the historical failed-shape list as diagnostic history rather than treating
the doloop class as proven promotable.

---

### Addendum (2026-10-02, fn_80130598) — the CTR guard is the LATCH COMPARE, and a runtime count does NOT hide it

Isolated-compile matrix (single small snippet, wibo + `ngccc -O2 -G0 -mcpu=750`,
cc1 3.9.3), copy-loop body held constant while the latch spelling varies:

| latch spelling | ngccc 3.9.3 output |
|---|---|
| `do { n -= 1; … } while (n != 0)` (n = 1) | `li r0,1; mtctr r0; …; bdnz` |
| same with n from a parameter (runtime count) | `mtctr r5; …; bdnz` |
| `do { … } while (n-- != 0)` / `while (0 != n--)` | `mr; cmpwi; addi; bne` (no ctr, 4-word latch) |
| `do { n -= 1; … } while (n >= 0)` | `addic. rN,rN,-1; bge` — **no ctr** |
| `while (n > -1)` / `while (n > 0)` / `while (n < 1)` | `addic.` + `bgt`/`ble`/`blt` — **no ctr** |
| `do { n -= 1; … ; CALL(); } while (n != 0)` | `addi; cmpwi; bne` — **no ctr** |
| counter pinned `register s32 n __asm__("rN")` | `addic.; bne` (recipe 141) |

Two corrections to the historical text above:

1. **The guard is the latch COMPARE, not loop-invariant-ness of the count.**
   The doloop matcher consumes a `cmpwi`+branch pair; a SIGN test
   (`>=`, `> -1`, `> 0`, `< 1`) is folded into `addic.`'s CR0 by `combine`,
   long before the matcher's pass, so no compare survives and no conversion
   happens — even with a fully provable constant trip count. Conversely an
   EQUALITY test (`!= 0`, truthiness) always leaves a compare and is always
   converted, *including when the count is a runtime value* (`mtctr <param>`),
   so "retail's byte-count loop hid the count from the pass" is not the
   mechanism — a byte count that is tested with `!= 0` converts exactly as a
   unit count does.
2. **Consequently `addic. … ; bne` is unreachable from plain C** unless the
   loop body contains a CALL, or the counter is hard-register-pinned, because
   every sign test that escapes the doloop emits a *sign* branch
   (`bge/ble/blt/bgt`), never `bne`. Every promoted `addic./bne` twin in the
   game uses one of those three escapes: `fn_80043800` (a `bl` in the loop
   body), the `li r0,0 + addic. + bge` zero-fill loops (`fn_801A594C`,
   `fn_802037AC`, `fn_801F1094`, `fn_801F12D8`, `fn_80207030` — sign test),
   `fn_80183068` (pin). A want with `addic. + bne`, no call in the loop and no
   pin in the original source — e.g. `fn_80130598` @0x801305F8, a 1-trip
   member copy with a literal `li r4,1` — has no plain-C spelling; do not
   re-sweep loop shapes or flags for it.

Corroborating recipe additions: recipe 89 (`-fno-strength-reduce
-fno-schedule-insns2`), recipe 141 (pin) and recipe 6 (sign-test filler loops)
all stay valid; the flag route simply never applied to the equality-test class.
