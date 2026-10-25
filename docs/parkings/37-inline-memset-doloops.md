# 37 — Inline-expanded memset doloops (mfctr save/restore around intervening call)

**Status: OPEN (2026-08-26).** First catalogued in the texture-decode zone.

## The shape

Retail expands certain fixed-size memory clears as an inline doloop with an
explicit CTR save/restore around an INTERVENING CALL:

```
[ptr = base]
[li    rSIZE, N]          # byte size, NOT pre-divided
[mfctr rSAVE]             # save outer CTR
[srwi rCNT, rSIZE, 2]     # word count computed FROM THE SIZE REGISTER
[addi rCNT, rCNT, -1]
[mtctr rCNT]
[mr   rCOPY, ptr]
[stw peel, 0(rCOPY)]      # peeled first word
[stwu rCOPY, 4(rCOPY)]
loop: [stw r0,0(rCOPY)] … [stwu][bdnz loop]
[mtctr rSAVE]             # restore — a call happened inside the window
```

## Why ngccc cannot reproduce it

Proven unreachable from plain C on **all five ProDG cc1 versions (3.5–3.9.3)**:

- A constant-count C loop (`for(i=0;i<N;i++) arr[i]=0;`) always folds to the
  wrapperless `[li N/4; mtctr; stwu/bdnz]` form — no peel, no mfctr pair,
  size never materialized.
- Making the count OPAQUE (`__asm__("" : "+r"(size))`, volatile reads, pinned
  counts) kills the bct conversion entirely → plain lbz/lwz store loop.
- Retail's loop.c evidently computed the CTR init from the size *register*
  without folding the constant — a scheduling state stock GCC never reaches
  when the size is a literal it can see through.
- The `[mfctr rSAVE]/[mtctr rSAVE]` pair only exists because a `bl` sits
  inside the clear window; GCC never saves CTR around its own doloops.

Detection tell: WANT shows `mfctr`/`mtctr` sandwiching a `srwi` of a small
constant plus a peeled store before the `bdnz` — grep wants for
`mfctr.*\n.*srwi` near `bdnz`.

## Known members / scale

- **fn_8024AEF0** (792B, 59.1%) — two such windows (~11% of insns frozen as
  inline asm; rest exact).
- **fn_80249B70** (660B, ~27%) — alloc+zero window; runtime-derived size
  (`srwi size>>2`) reproducible only through an opaque `"+r"` size web.
- **fn_8024BA9C** (1640B, 12%) — mfctr/mtctr save-restore artifact component.
- **fn_8024A0B0** (904B, 88.9%) — zero-fill window frozen as 13-insn asm block.
- **~27 DOL sites share the template across 0x80249xxx–0x80252xxx (the whole
  texture-decode zone), none matched project-wide.**

## Working workaround (for NEAR parks)

Freeze each window as a short inline-asm block (≤13 insns keeps asm density
defensible). Notes that make the bytes land:

- WANT's doloop branches can carry the branch-prediction HINT bit
  (`BO=17` vs GCC's unhinted `BO=16`) — the SN assembler accepts
  `bdnz+ .label`; use the `+` when WANT's word has bit set.
- Numeric labels mis-resolve inside asm windows (see doc 30); prefer `.label`
  local labels.
- Keep total operands ≤10 (GCC 2.95 limit).

## Retry hints

None known from C source. If a future route appears, it will likely be
per-object flags affecting loop.c/bct (none of `-O1..-O4`,
`-fno-loop-optimize`-class knobs exist in these cc1 builds) or a linker-level
transformation. Do NOT re-grind loop spellings — five-version proof above.
