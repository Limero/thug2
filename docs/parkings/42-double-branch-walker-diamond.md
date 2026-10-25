# 42 — Double-branch walker-extract diamond (out-of-line `dest == base` load)

**Status:** OPEN (discovered 2026-08-25, round)
**Affected exemplars:** `fn_8022BBD0` (`depth-walk` list helper, 200 B, ~85% structural / DIFF positional)
**Related:** #15 call-arg-setup-scheduling (order artifacts — not this), #32 walker-role-rotation
(register roles — separate axis), #33 inlined-iterator-volatile-webs (zone sibling; that doc's
walls are web-sharing/dead-code, this one is pure BLOCK LAYOUT of a null-check).

## Symptom

The function extracts a walker twice via the classic guarded-load idiom. WANT lays each
extract out as a **two-branch diamond with the load OUT-OF-LINE**:

```
want:   cmpwi rN, 0          ; walker != NULL?
        bne   Lload          ; -> load block
        li    rN, 0          ; NULL path materialized INLINE
        b     Lend
Lload:  lwz   rN, 4(rN)      ; dest == base: load overwrites the tested reg
Lend:   or.   rW, rN, rN     ; fused test-copy of the result
```

Note the two signatures packed together:
1. **dest == base** — the loaded field lands back in the SAME register that was tested;
2. **the load sits in an out-of-line block**, with the `li rN,0` NULL-materialization inline
   and an explicit branch around the load.

GOT (ngccc 3.9.3) emits the **skip-load single-branch form** from every C shape tried:

```
got:    cmpwi rN, 0
        beq   Lskip           ; or li/beq pairing
        lwz   rN, 4(rN)      ; load stays INLINE on the taken path
Lskip:  ...
```

i.e. GCC if-converts/rotates the diamond into "branch over the load" instead of
"branch TO the load". The register-recycling detail follows the same missing context:
WANT recycles web-1's `r9` for the extracted value; GOT births a fresh `r11`.

## What was tried (all failed to move the diamond)

- Ternary, both polarities (`w ? w->next : NULL` / inverted)
- `if/else` with split destination vars; self-assign `dest == base` form
- Redundant-else; default-first two-if ordering; explicit goto diamond mirroring want's blocks
- `volatile` load (forces reload but not the layout); memory-clobber barrier (reshuffles
  allocation only)
- `-fno-schedule-insns`, `-fno-schedule-insns2`, `-fno-thread-jumps`
- Hard-reg pin r9 (fixes n/walker homes but BLOCKS web-1→r9 recycling per §74-161c —
  pins forbid post-death register reuse)

Frame (0x18 via 3 pinned s32 locals + OOB `&sp8` idiom), ctx-label store, address webs
r9/r8 (+mr copy) and page anchor r11 all match — the ONLY residue is the two diamonds
plus their knock-on register choice.

## Working hypothesis

The original context was likely part of a **larger function** (later split by the linker/
dead-strip, cf. #08/#31 family history): register pressure from surrounding code is what
makes a compiler lay a null-check as branch-to-load rather than branch-over-load. A
standalone TU at -O2 never reproduces it.

## Retry hints

- Scan for promoted/parked siblings elsewhere in the DOL whose want shows the same
  `[cmpwi][bne Lload][li 0][b][lwz]` shape INSIDE a bigger body — cracking one there
  (with real register pressure) transfers here.
- If found, try reproducing under synthetic pressure: enough simultaneously-live webs to
  force spill territory (full-web pinning §6an-216 style) before concluding.
- Do NOT re-grind the ternary/if/goto space — exhausted above.

## Sibling wall from the same zone : iterator entry-forwarding trio

`fn_8022B75C` (34.1%), `fn_8022B8E8` (36.2%), `fn_8022BB14` (34.0%) share a different
block-layout artifact: **want forwards the extracted val-web straight into the return
register via a branchy r9-web + `or.` copy at the ENTRY block**, while ngccc forwards the
value into r3 directly (dying-web forwarding). The jp→r9 address-pin matched the 16-insn
entry on B75C; the residual is the same class of "which web dies where" layout choice.
Treat these three + fn_8022BBD0 as one investigation cluster before declaring either wall
permanent.
