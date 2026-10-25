# Issue 27 — Float working-value coalesced onto the incoming arg register

**Status: SOLVED (2026-08-23) — BOTH twins byte-exact at 100.0%.** The doc's
untested lever works, with two additions: (1) the fr1 pin needs an identity
init `var_f1 = farg0;` as the FIRST statement — the elided copy occupies fr1
before any other pseudo can steal it (without it, the CE30 constant load
grabs `lfs f1, ...`); (2) the conditional must be SINGLE-DEF (no else
reassignment) so one web flows through the branch; (3) pinning fr1 alone
rotates every other FPR up one slot — pin the colliding role (`temp_f10` →
fr10) simultaneously and the rest of the pool snaps back.

## Solution — fn_8010CEB0 / fn_8010CF10 (96B each, plain flags)

```c
// fn_8010CEB0 (twin CF10: offsets 0x70/0x6C, consts lbl_8029CE34/38/3C)
extern char lbl_8029CE28[];
extern char lbl_8029CE2C[];
extern char lbl_8029CE30[];

f32 fn_8010CEB0(void *arg0, s32 arg1, f32 farg0) {
    register f32 var_f1 __asm__("fr1");
    register f32 temp_f10 __asm__("fr10");

    var_f1 = farg0;
    temp_f10 = *(f32 *)((char *)arg0 + (s32)0x78);
    if ((temp_f10 != *(f32 *)&lbl_8029CE28) || (*(f32 *)((char *)arg0 + (s32)0x74) != *(f32 *)&lbl_8029CE2C)) {
        var_f1 = ((*(f32 *)((char *)arg0 + (s32)0x74) - temp_f10) * var_f1 * *(f32 *)&lbl_8029CE30) + temp_f10;
    }
    if ((arg1 != 0) && (var_f1 > *(f32 *)((char *)arg0 + (s32)0x74))) {
        return *(f32 *)((char *)arg0 + (s32)0x74);
    }
    return var_f1;
}
```

---

# ORIGINAL ANALYSIS (historical)

**Status:** PARKED (2026-08-22) — 2 functions: fn_8010CEB0 (63%), fn_8010CF10 (63%, byte-twin with offsets 0x70/0x6C and consts lbl_8029CE34/38/3C).

## The problem

The game keeps the working float in **farg0's own register**: the `fmadds`
writes straight into f1 and every later op consumes it there — zero copies.
ngccc instead routes the result through a fresh volatile FPR (f0) and pays
two `fmr` merge copies to get back into f1 (+8 bytes, one extra block edge).

Want (fn_8010CEB0 at offset 0x44 onward): the fused multiply-add writes its result straight into the incoming float argument register f1, the integer argument is tested against zero with an early return, the result in f1 is compared in place against the f11 constant with a second early return, and the fall-through moves f11 into f1 before returning — zero copies anywhere. Got (every source shape tried): the product lands in a fresh FPR f0, an unconditional branch leads to a first merge copy moving f1 into f0, the same integer test and early return follow, the compare runs on f0 instead, and a second merge copy shuttles the result back from f0 to f1 before the final move of f11 into f1 and return.

## What was tried (all produce the split+copies form)

- pre-initialized local (`var_f1 = farg0;`)
- if/else assignment forms, ternary forms
- parameter reassignment (`farg0 = farg0 * x + y;`)
- goto-skip / named-temp chains
- `-fno-schedule-insns`, `-fno-schedule-insns2`, `-fno-sched-spec`,
  `-fno-strength-reduce`
- cc1plus (the C++ front-end)

## Why this looks RA-level

GCC 2.95 web-coalescing refuses to extend farg0's live range across the
multiply when the value is also *conditionally* replaced by another constant
(`f11`) on the fall-through path; it treats f1 as "incoming arg, must be
preserved until last use" and allocates a separate web for the product.
No source-level transform re-merged them.

## Retry hints

- Try a shape where the conditional replacement ALSO flows through the same
  named variable as the product (single web), e.g. compute both arms of the
  final `fmr f1, f11` from one expression.
- Try pinning: `register f32 v __asm__("fr1");` (recipe 67 form) — untested
  at the time of parking; note recipe 98's warning that pins move other
  allocations too.
- The twins share everything but offsets/constants — any fix must mirror.
