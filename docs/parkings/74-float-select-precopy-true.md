# doc 74 — GCC 2.95 never emits a "pre-copy the TRUE value + forward branch" float select

**Status:** NEW WALL, found 2026-09-28. First (and so far only) member
`fn_800C4560` (468B, 94.9%). This is the first fully-enumerated datum of the
float-register-select family — before parking another one, check the shape
below, because the answer is that no C source exists.

## The shape

Retail clamps a float and keeps the pre-clamp value in the *same* register,
branching forward over the else-assign:

```
WANT:  fmr  f1, f0        ; pre-copy the TRUE value
       fcmpu f0, f13
       bgt  END
       fmr  f1, f13       ; else: overwrite with the clamp
```

GCC 2.95 (all ProDG point versions) emits the identical computation
**mirrored** — pre-copy of the *false* value, and the branch flipped:

```
GOT:   fmr  f1, f13       ; pre-copy the FALSE value
       fcmpu f0, f13
       ble  ...
```

## Why no C spelling exists

GCC 2.95 has exactly two expansions for a scalar float register destination,
and **both pre-copy the false value**. There is no source-level control over
which value is copied. Eight hand-motivated spellings were all measured and
all produce the *same* mirrored six words:

* ternary `v > K ? v : K`;
* the same ternary used inline as a call argument;
* `if`/`else` with both arms assigning;
* no-temp direct member read;
* the **swapped** ternary `(v <= K) ? K : v` — GCC canonicalises the `<=`;
* `<=` / `!(v > K)` — emits `cror`+`bns`, the wrong shape entirely;
* empty-then `if`/`else`;
* a goto-into-merge triangle — both if-convert to `fsubs` + `fsel`.

Two zero-code `"+f"` barriers do **not** block the RTL if-conversion, and they
additionally perturb the other path.

## Exhausted (do not re-run)

the eight spellings above, the two `"+f"` barriers, and
`-fno-cse-follow-jumps` / `-fno-cse-skip-blocks` / `-fno-thread-jumps` /
`-fno-gcse` / `-fno-expensive-optimizations` (the last regresses to 93.2%).

## How to tell this family from the ones you CAN fix

| residual | cause | fixable? |
|---|---|---|
| `fmr`/`fcmpu`/`b?` mirror (this doc) | GCC's float select expansion | **no** — park |
| 2-word `lfs`-vs-`lwz` order in a float block | pool-node identity (doc 14 / AGENTS L4) | yes — use a C literal |
| a `fmr` that lands one block off | preheader LUID / block shape (AGENTS earlier §6bc) | yes — peel the loop, stage the pre-decremented offset |
| a *dead* PS spill that won't survive | needs `volatile __ps_t` (doc 06 M5.0u) | yes |
| `fctiwz` pool in the wrong section | doc 14 | yes, mechanically |

## Promotion note

`fn_800C4560`'s other residual (a preheader `lis`/`slwi` swap) has a clean
future route: the 2^52 double is the pool constant the `(f32)(f64)(u32)` cast
**expander** synthesises, so the "preheader own statement" lever cannot reach
it (there is no source-level value to reference). But `lbl_802990F8` is a real
`.rodata2` **double** (size 0x8) at exactly the address retail's
`lfd f30,-0x6f08(r9)` targets — so a 1-insn `lis %0,%1@ha` anchor to it would
make the function promote-clean (no private `.rodata` to retarget). The §6j-1
hand-written union dance was tried and wrecks the body (21.2%, frame
0x48→0x50), so leave that to a future attempt.
