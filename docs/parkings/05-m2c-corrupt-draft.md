# Issue 05 — m2c-corrupt draft (fn_8008076C)

**Status: IMPROVED 51% → 94.79% (2026-08-23) — one register color left; re-verified 2026-08-29 (no lever beats it).**
Three NEW mechanisms stacked on the 51% reconstruction (full winning source is
now `src/wip/fn_8008076C.c`; levers below are order-independent and additive):

1. **node pin**: `register void *node __asm__("r10");` (recipe §6o-98
   postdates the doc's 13 variants) — fixes the node r10-vs-r3 color (+6.25).
2. **Named `sub` hoisted inside the flags-if**: want reuses the bound-check's
   `0x14`-load for component[0] (3 inner reloads, not 4); naming just that one
   deref aligns the entire loop body byte-for-byte.
3. **src pin r30 + barrier-copied loop counter**: `s32 n = cnt;
   __asm__("" : "+r"(n));` blocks coalescing so want's `mr` copy survives;
   countdown on n=r28, src reuses r30.

Remaining 5 words = ONE color: `sub` + its bottom-test reload temp sit in
r6/r9 vs want r11. Direct r11-pin cascades (88.5%); r6-clobbers/live-range
dummy pins don't displace it. Also verified this round: full 720-permutation
decl-order sweep → every perm exactly 51.04% on the OLD body (lever
conclusively dead here), flag sweep all ≤ baseline (`-fstrength-reduce`,
`-fno-move-all-movables` exist but neutral).

**Retry 2026-08-29:** `src/wip/fn_8008076C.c` → `tools/gen_leaves.compile_fn` (`-O2 -G0 -mcpu=750` ProDG/3.9.3) = **94.79% (91/96 words, 5 diffs, 384B)** — `tools/test_wip_drafts.py --addr 0x8008076C` → `NEAR m2c 94.8%`, doc claim exactly reproduced. 5-word diff = pre-loop `lwz r11,0x14(r10)` vs `lwz r6` / `lhz r0,0x28(r11)` vs `(r6)` / `lwz r9,0x34(r11)` vs `(r6)` / bottom `lwz r11,0x14(r10)` vs `lwz r9` / `lhz` vs `(r9)` — inner-loop reloads at `0x800807E4/F8` already match `r11`; path B `src r30/n r28` barrier is 100%. **≥47 variants scored:** `register sub __asm__("r11")` 84.38% (inductor cascade r7→r6), `r6`/`r9` clobber `::: "r6"` 93.75%, `+r`/`volatile`/struct/decl-reorder neutral, `i` pin `r6` 90.62%, `-fno-schedule-insns` neutral/`-fno-schedule-insns2` 71.88%/both 62.5%/`-fno-gcse`/`-fno-regmove` neutral — **none beat 94.79%**. Park reason stands: `global-alloc.c` gives pre-loop `sub` web low priority (`r6`/`r9`) vs inner-loop high priority (`r11`); pinning `r11` steals from high-priority inductors `i`/`off`. Retry hints: live-range-split/coalesce lever (single `sub` pseudo), alias-forced reload via `op` TBAA pun, or whole-function `"+r"` split variant.

---

# ORIGINAL ANALYSIS (historical)

**Status: STRUCTURE SOLVED (M4.92) — hand-reconstructed to 51% masked match
(up from the 692-byte m2c garbage). The frame, control flow, and all data
accesses now match exactly; the remaining gap is PURE GPR register allocation
(see the diff table at the bottom).** (1 function: fn_8008076C — the sole
exception in the verify36 regression set.)

## The problem (original)

fn_8008076C (384 bytes) has a huge 0x4E48-byte (20,040-byte) frame holding a big local array, saves the link register via r0 to frame offset 0x4E4C, saves float register f31 to frame offset 0x4E40, and saves registers r28 onward at frame offset 0x4E30 (see also the FPR-frame issue).

m2c's decompilation was **corrupt**: it invented a bogus `sp2718` local and
produced C compiling to 692 bytes vs the original's 384. It was the only
address in the 36-address postprocessor regression set (`tools/verify36.py`)
allowed to stay broken.

## What the function actually is (verified from disassembly)

The frame decomposition (user hypothesis — CONFIRMED):

- locals span `r1+0x08 .. r1+0x4E28` = **0x4E20 = 20,000 bytes = `s32 buf[5000]`**
- the two stack objects m2c called `sp8` / `sp2718` are **`&buf[0]` and
  `&buf[2500]`** (10,000 bytes apart — one 5000-element buffer used as two
  halves, passed to `fn_80080538(obj, &buf[0], &buf[2500])`)
- save area at 0x4E30 (stmw r28) / 0x4E40 (stfd f31); LR at 0x4E4C
- the frame is **0x4E48 = 0x4E28 + saves(24) + FPR-quirk(+8)** — so the
  Issue-01 dummy is STILL needed even with the giant array (it does not
  "mask" the quirk; it needs the dummy placed AFTER `buf` so `&buf[2500]`
  stays at r1+0x2718)

The function logic (reconstructed):

```c
void fn_8008076C(void *obj, void *out) {      // out = f32[4] records, 16B stride
    s32 buf[5000];                            // sp8.. / sp2718..
    s = fn_8007DF14(*(u32*)(obj + 0x18));
    if (*(s32*)((char*)s + 8) != 0) {         // path A: fast path
        node = **(void***)((char*)obj + 0x20);
        if (*(u16*)((char*)node + 4) & 0x10) {
            for (i = 0; i < node->sub->count; i++) {   // bound re-read per iter (u16 lhz)
                out[i] = { sub->vtx[i*3+0], sub->vtx[i*3+1], sub->vtx[i*3+2], 1.0f };
            }                                 // vtx = *(f32**)(node->sub + 0x34),
        }                                     //   re-deref'd PER COMPONENT (aliasing)
        fn_8007E89C();
    } else {                                  // path B: indexed fallback
        cnt = fn_80080538(obj, &buf[0], &buf[2500]);
        fn_8007E89C();
        if (cnt > 0) {
            do {
                idx = *src++;
                out->x = (*vtxptr)[idx*3+0];  // vtxptr = *(f32**)(fn_8007DF14(obj->0x18) + 0xC)
                out->y = (*vtxptr)[idx*3+1];  // fn_8007DF14 re-CALLED per component
                out->z = (*vtxptr)[idx*3+2];
                out->w = 1.0f;                // lbl_8029628C (.rodata2, value 1.0)
                out++; cnt--;
            } while (cnt != 0);
        }
        fn_8007E89C();
    }
}
```

## The two REAL m2c bugs (fixed in the reconstruction)

1. **f32 loads mis-typed as `(f32)` casts of `s32`** — m2c emitted
   `(f32) *((s32 *)off + vtx)` for what are `lfsx`/`lfs` float loads. Casting
   an s32 to float generates a conversion (fctiwz/etc.), inflating the code
   from 384 → 692 bytes. The vertex arrays are `f32*`.
2. **Path B's `+0xC` is a pointer FIELD, not an inline array** — want does
   `lwz r11, 0xc(r3); lfsx f0, r9, r11` (load the `f32*` from the struct at
   +0xC, then index it). Casting `(f32*)((char*)s + 0xC)` instead makes GCC
   fold the offset into `add`+`lfs`. The C must be
   `(*(f32**)((char*)s + 0xC))[idx*3 + k]`.
3. (Frame) `s32 buf[5000]` + a `volatile double` dummy declared AFTER the
   buffer reproduces the exact 0x4E48 frame and the 0x2718 offset.

## Remaining blocker: pure GPR register allocation (the last 49%)

Every opcode sequence now matches (verified instruction-by-instruction at
384B = 96 insns); only these register colors differ:

| role | want | got | 
|---|---|---|
| node (path A) | r10 | r3 |
| loop counter i | r7 | r8 |
| vtx offset | r8 | r10 |
| path B cnt / src | r28 / r30 | r30 / r28 |

Tried and FAILED to shift: node at top-level vs inside-if, node fully inline
(18%), plain `for` loop (46%), `register` hints on i/off/cnt, f32* typed
out pointer, two-array split (bufA/bufB), local declaration order, inverted
branch (path B as if-body, 19%), 13 total variants — all plateau at 51%.
GCC 2.95's rs6000 allocator colors node after the loop inductors in the want
(priority pass), but first in ours; no source shape found that flips it.

## Research directions for an external AI

1. Study GCC 2.95.2 rs6000 `global-alloc.c` priority/color order for this
   pattern (a long-lived pointer + 2 loop inductors, no calls in the loop).
   The want colors inductors r7/r8 first and the pointer r10; we get r3 first.
   A priority difference of one pseudo somewhere earlier in the function.
2. Check whether a compiler flag like `-fno-schedule-insns`, `-fno-gcse`, or
   `-fstrength-reduce` affects the colors (the build uses plain `-O2`).
3. If a sibling function uses the same node/loop pattern with r10 for node,
   diff its C against ours — the deciding expression may be visible there.

## Where to look

- Draft: `src/wip/fn_8008076C.c` (51% reconstruction, kept readable).
- Regression set: `tools/verify36.py` (still 35/36 — this fn stays parked).
- Verification: `tools/gen_leaves.compile_fn` + `tools/test_wip_drafts.py --addr 0x8008076C` (91/96), 47-variant sweep 2026-08-29 — none beat 94.79%; diff at `0x800807B0/B8/D4/818/81C` (pre-loop/bot `sub` color).
- History: `AGENTS.md` §4i/§4j, `docs/gamecube-decomp-plan.md`.
