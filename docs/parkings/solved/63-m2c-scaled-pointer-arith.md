# Issue 63 — m2c scaled scalar-pointer arithmetic (draft defect, not a wall)

**Status: SOLVED as a draft defect (2026-09-18). 31 wip drafts rewritten, up to
+33.9 points on a single function and +31.0 on another; scanner is
`tools/fix_scaled_ptr.py`.**

## The defect

m2c sometimes prints a pointer chain where the displacement is applied to a
pointer that came out of a cast, e.g.

```c
temp_r7 = *(s32 *)*(s32 *)((s32 *)((s32 *)(*((s32 *)((char *)arg0 + 0x30) + 0x54) + 0x58)
                                   + (var_r7 * 4)))) + 0x14) + 0x4);
```

Read the parens: the `+ 0x14` and `+ 0x4` sit **outside** the `(s32 *)` cast,
so they are C *element* arithmetic on an `s32 *` and add `0x14 * 4 = 0x50`
bytes. The binary uses plain byte displacements: it walks arg0 plus 0x30, then offset 0x54, then offset 0x58, performs the indexed load by the scaled loop variable, and finishes with byte-displacement loads of 0x14 and 4.

So the whole walk points at the wrong addresses and the score sits wherever the
surrounding structure happens to still line up.

## The repair

Keep the outer dereference type, but make the base a `char *` so the offset is
byte-wise:

```c
(s32 *)((s32 *)(X) + 0x14)   ->   (s32 *)((char *)(X) + 0x14)
```

i.e. mechanically `(T *)((T *)` → `(T *)((char *)`.

**Do not touch `(T *)(X + 0x14)`** — when the displacement is *inside* the cast
the arithmetic is done on an integer (an address held in an int), which is
already byte-correct.  That spelling appears in **406 already-matching promoted
files** (e.g. `src/fn_80009C00.c`, 97 occurrences of the
`*(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x10) + 0xC)` shape), so a blanket
"pointer arithmetic in m2c output is suspicious" pass would be actively harmful.
Only the *cast-of-cast* form is a defect.

## Scanner

`tools/fix_scaled_ptr.py` (same recipe class as `tools/raw_sym_scan.py`):

```
tools/fix_scaled_ptr.py scan  [N] [jobs]     # score current vs repaired
tools/fix_scaled_ptr.py apply [min-delta]    # rewrite + add the UPDATED note
```

* `SAME` pass: `(T *)((T *)`   — the common shape.
* `ANY` pass:  `(T *)((S *)`   — mixed scalar types; only 2 extra hits
  (0x80099B2C 0.0→7.9, 0x800BF7C8 4.6→4.9), so the same-type rule is the real
  signal.
* Candidates: 303 drafts of 1512 contain the shape; 31 score strictly better
  after the rewrite.  A/B honours each draft's own `// FLAG:` line.

Largest wins (baseline = the recorded best body):

| addr | before | after |
|---|---|---|
| 0x8022D074 | 48.3 | **82.1** |
| 0x801211B8 | 44.0 | **75.0** |
| 0x8005DDF4 | 30.8 | **44.7** |
| 0x80013A3C | 28.3 | **40.0** |
| 0x8005CCFC | 15.6 | **25.4** |
| 0x800537FC | 14.3 | **21.4** |
| 0x800596E4 | 21.0 | **27.4** |
| 0x8004631C | 42.5 | **46.6** |
| 0x801F0FC4 | 44.8 | **48.3** |
| 0x80102A40 | 61.8 | **64.7** |
| 0x8007A9F8 | 70.3 | **73.0** |

All 31 rewritten drafts carry a header note naming the tool, so a future rescan
does not re-report them.

## Related

- **The defect also appears as a pointer INCREMENT, which the scanner does not
  cover** (hand-found 2026-09-18): `src/wip/fn_80032588.c` had
  `void **var_r11; ... var_r11 += 4;` — m2c's *byte*-stride intent written on a
  pointer type, so ngccc scaled it to `addi r11,r11,0x10` (4 elements * 4 bytes)
  and the entire array walk landed on wrong addresses (47.1%, every element
  stride wrong).  Rewriting the walk as a byte walk / indexed expression lifted
  it to 76.5%.  A `+= N` / `-= N` pass over pointer locals declared as `void **`
  or as a mismatched scalar type is the natural extension of
  `tools/fix_scaled_ptr.py` (its two passes only match cast-offset chains).
- `src/wip/fn_8007F7F8.c` — found here while hand-matching; also needed two
  field-width repairs (`lbz` on a byte field, `lhz` on a 16-bit field) and is
  parked at 91.0% on a loop-preheader/register-home residual.
- Same defect family as issue 05 (m2c corrupt draft), which covers mis-typed
  `f32` loads and field-vs-inline-array confusion.
- `tools/fix_sw*.py`, `tools/fix_raw_lit.py` etc. are the other "m2c printed it
  wrong" repair passes; this one belongs in that set.
