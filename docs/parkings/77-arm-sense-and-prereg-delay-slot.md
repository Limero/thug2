# 77 — if/else arm sense ⇒ block layout, and pre-branch copies ⇒ delay slots

**Status: two NEW general matching rules (both verified on `fn_8002DB10`,
1.1% → 96.4%) + one open residual that is an FPR allocation tie-break.**

Both rules are about *where an instruction sits*, not about semantics, and both
are pure-C fixes: no flags, no pins, no asm. Read them together with
recipes §6a-138 (arm polarity) and §115b (the `mfcr`+`rlwinm` bool).

## Rule 1 — the branch sense tells you which arm is the fall-through

`expand_end_construct` emits `if (C) {A} else {B}` as
`if (!C) goto L_B;  A;  goto END;  L_B: B; END:` — **the then-arm is the
fall-through and the branch targets the ELSE arm, with the sense of `C`
inverted.** So given a want if/else pair:

| want shape | source to write |
|---|---|
| `bne <B>;  A;  b END;  B: …` (A inline, branch jumps over A to B) | `if (!C) { A } else { B }` |
| `beq <A>;  B;  b END;  A: …` (B inline, branch jumps over B to A) | `if (C) { B } else { A }` |

In `fn_8002DB10` the want is
`bne <big wrap loop> ; fmr f0,f11 ; b EXIT ; <big wrap loop>:` — the SMALL arm
is inline. Writing the "natural" `if (lo != hi) { big } else { small }` (what
you get from reading the branch polarity, and what most m2c-style rewrites
produce) compiles to `beq <small, out of line> ; <big> ; b merge` and inverts
the whole block order: **the two arms and the following block all shift by one
insn and the score sits at 73.9% instead of 96.4%.** The fix is to write the
*pre-flipped* sense, `if (lo == hi) { small } else { big }`.

This refines recipes §6a-138, which says "pre-flipping makes GCC re-invert to
`bne`… in the chain family the un-swapped source is always right": for a plain
two-arm if/else the **pre-flipped** form is the one that reproduces a want with
the small arm inline. §6a-138's rule still holds for else-if *chains*; the
disambiguation is: chain arms vs a single two-arm if/else.

## Rule 2 — a copy emitted BEFORE the top-level `if` can be hoisted into that branch's delay slot

ngccc's `final_insn_delayed_slot` will pull an instruction **out of the block
that ends in the branch** and into the branch's delay slot, as long as the
instruction is safe on the not-taken path. `fn_8002DB10`'s want compares r9 against 3, places the float copy from f1 to f0 in the delay slot of the equality branch below, branches to 0x8002dcb8 on equal, and loads r0 from offset 0x28 of r31 after the branch.

`f0 = f1` is the first statement of the `if (mode != 3) { … }` body, so with that
spelling GCC emits it *after* the branch and the delay slot stays empty
(`beq; lwz; fmr; …` — 3 words shifted, 96.4% → 73.9% at the time). Assigning the
copy **before** the test

```c
v = r;  lim = r;  wrapped = r;      /* all three inits first */
mode->f30 = 0;
if (mode->f2C != 3) { … }            /* `wrapped = r` lands in the beq slot */
```

puts the `fmr` in the same block as the branch, where the filler takes it. This
is a *source-order* lever, not a barrier: no `asm volatile`, no `volatile`
qualifier, no flag. Generalises to any want where one reg-reg copy sits in a
delay slot while the copy's source dies right there (the filler's precondition
is that the move's source is dead after it).

## Open residual (parked): the rotated loop-invariant copy pair picks f13, want f11

`fn_8002DB10` (444B) is at **96.4%, 4 words**: in *both* wrap loops the
pre-header rotation of the two loop invariants lands one register off —

At both 0x8002DBAC and 0x8002DC2C retail copies f10 into f11 and adds f11 into f0, while the build copies f10 into f13 and adds f13 into f0, landing one float register off in both wrap loops.

The loop-invariant hoisting (loop rotation + `pre_edge_cse`) gives the loop body
*fresh* allocnos and bridges them with a `fmr` pair in the pre-header; the
register each new allocno gets is a global-allocation tie-break (GCC 2.95 sorts
allocnos by `log2(n_refs) * n_refs / live_length`, ties by allocno number, then
hands out the lowest free FPR). Both wrap loops are semantically identical in
every spelling tried, so the tie-break lands on f13 instead of f11.

Tried, all byte-neutral or worse (see the draft's PARKED block): `while` vs
`if`+`do/while` vs raw `do/while`; `lo + (v - hi)` vs `(v - hi) + lo` vs
`v -= hi; v += lo`; hoisting `lo`/`hi` into locals; a temp for `x - hi`; a `dt`
local for `fn_800144C8() * 60.0f`; swapping the two top inits; moving the
`f30 =` store after the if/else; reordering the two wrap arms. **Someone with a
lever on the float allocno order (e.g. doc 75-style pins) should retry this
one** — it is 2 instructions away from EXACT and everything else is verbatim.

## Tooling: ngccc's per-pass RTL dumps (worth knowing for ANY regalloc park)

`ngccc -dall -c body.c` (through `build/tools/wibo`, `SN_NGC_PATH` set) writes
one dump per pass next to the source — `<base>.<pass>.rtl`, passes
`addressof bp combine cse cse2 flow flow2 gcse greg jump jump2 loop lreg mach
regmove rtl sched sched2` (only some passes fire). Two of them make a
register-allocation residual *readable* instead of guessable:

- **`.lreg`** (`local_alloc`): a per-pseudo census —
  `Register 113 used 5 times across 6 insns; set 1 time; dies in 0 places;
  FLOAT_REGS or none` — i.e. the `n_refs` / `live_length` / `calls_crossed`
  inputs that `global_alloc`'s `allocno_compare` sorts on, plus the per-block
  live sets, plus the RTL *after* local-alloc copies.
- **`.greg`** (`global_alloc`): the **allocation order** and the final map —
  `;; 33 regs to allocate: 112 138 85 113 … 115 … 105 …` (that is
  `allocno_order`, the qsort result) and `;; Register dispositions: 113 in 44,
  115 in 45` (44/45 = f12/f13 with `FIRST_PSEUDO_REGISTER == 32`), then
  `;; Hard regs used: 0 3 9 31 32 33 42 43 44 45 65 68 75`.

On this function the FPR pool in practice is only `{f0,f1,f10,f11,f12,f13}`
(f2-f9 and f14-f31 are skipped — call-clobbered regs are avoided for
allocnos that are not call-crossed) and it is handed out **in ascending order
of `allocno_order`**. The residual is that pseudo 115 (the loop's `lo`) sits at
position 26 of 33, by which point f11 is held by 102 (the pre-loop `hi`, which
does *not* conflict with it) — so the only variable is whether the `losers`
("registers a lower-priority conflicting allocno prefers", `prune_preferences`)
set contains f11. A different source that shifts one allocno's desirability by
one notch flips it; that is the lever to hunt, and the dumps show the ranking.

