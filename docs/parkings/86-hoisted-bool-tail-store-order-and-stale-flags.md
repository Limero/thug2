# 86 — Hoisted `== 0` bools, tail store-order, stale `// FLAG:` lines, and frame size from live-across-call values

**Status:** partial round-up 2026-10-03. Four small, independent, *general*
levers. Each closed a different draft; none is a new wall.

| function | size | was | now |
|---|---|---|---|
| `fn_801CD68C` | 584B | 94.5% | **EXACT** (§2) |
| `fn_802347D0` | 148B | 73.0% | **94.6%** (§3 + §4) |
| `fn_80161880` | 384B | 91.7% | **92.7%** (§5) |
| `fn_80232B98` | 324B | 71.6% | **EXACT** (doc 85; §1 here) |

Not promoted (per this round's brief).

---

## 1. `subfic rD,rA,0 / adde rD,r0,rA` is a *named hoisted* `== 0`, not an inline test

ngccc lowers `x == 0` to `subfic r0,x,0 / adde rD,r0,x` **only when the
boolean is a named variable assigned before the value is tested**. Written
inline in a call argument it sinks below the test and costs 2–4 words, and
spills the operand into a callee-saved register.

```c
/* WRONG — 75% : the pair sinks below the sp8 test */
fn_X(a, (f ^ 1) == 0, 0);

/* RIGHT — 100% : the flag is homed, then the memory slot is tested */
nv = f ^ 1;
fn_X(a, (nv == 0), 0);
```

`fn_80113BCC` and `fn_80232B98` both close on this. `fn_80113BCC`'s draft also
needed the flag compared the other way round (`b = !f`); `fn_80232B98` needed
the enclosing call hoisted into its own statement first (see §6).

A scanner for parked drafts whose want contains `subfic` + `adde` found 28+
candidates (`fn_80232B98`, `fn_80192854`, `fn_800C7234`, `fn_80172ED4`, …).
Several are doc-15 parks where this was only part of the residual.

---

## 2. A call tail wants the flag store BEFORE the argument load

`fn_801CD68C` (584B, `-mps-float`) was parked at 94.5% on a "doc-15
call-arg interleave" at the final `fn_8009F054` call. Three spellings of the
tail, measured:

| source | score |
|---|---|
| comma-in-arg staging `(oc = ..., oc)` — the m2c shape | 94.5% |
| hoist `oc` into its own statement, store after the load | 98.6% |
| **hoist `oc`, and put the flag store BEFORE the load** | **100%** |

```c
nv = temp_r0 ^ 1;
*(s32 *)((char *)a0 + 0x570) = nv;   /* stw first  */
oc = *(s32 *)((char *)a0 + 0xC);     /* lwz second */
var_r4 = 0x5E27200A;
if (nv != 0) { var_r4 = 0xF225FE69; }
fn_8009F054(oc, var_r4, 0, lbl_802AD2C0);
```

Every modern scheduler sinks a store below an independent load. ngccc 2.95.2
does not, and retail agrees with it. Ternary forms for `var_r4` are worse
(94.5% / 93.8%). **Triage order:** when a call tail differs only by a store
and a load being transposed, try moving the store earlier in *source* before
touching flags.

---

## 3. Re-measure every `// FLAG:` line after any body edit — stale flags are usually harmful

`fn_802347D0` carried `// FLAG: -fno-expensive-optimizations` from an earlier
round. Once the body was corrected the flag became actively **harmful**: with
it the u16 store sank below the first call's argument setup (72.97%); without
it the whole body was right except a 2-word window (94.59%). The flag had been
load-bearing for the *old* body.

There is no way to see this from the diff — the flag's damage is a whole
reordering, not a few words. Treat every inherited `// FLAG:` as unverified
whenever the body changes, and A/B it (this is recipes §6cs-1 discipline
applied to flags rather than to size).

---

## 4. A shared m2c struct's field WIDTH is often wrong; read the field at its real width locally

`fn_802347D0` (148B): `Unk_F0FD48D1.unk0x18` is declared `u8` in
`include/structs.h`, so every call emitted `lbz r3,0x18(r29)`
where retail has `lwz` — 4 wrong words, 73.0% → 83.8%.

Fix by reading the field at its true width **locally** rather than editing the
shared header (the header is consumed by dozens of drafts):

```c
AddInteger(*(s32 *)((char *)arg1 + (s32)0x18), QB_X, ((u8 *) &sp8)[0]);
```

Lesson: before grinding scheduling, check the *widths* against the want. A
`lbz`/`lhz` in the got where the want has `lwz` is a type error, not a
schedule tie.

Same function, second finding: the 6-byte local is **one aggregate** reached
by char-punning `&sp8` (`s32` at `r1+8`, `u16` at `r1+0xC`, byte reads at
`r1+8` / `r30+0,2,3,5`). A separate `u16` local, a real `struct` local, or
`>>16`/`>>24` shifts all collapse the aggregate (24% / 8B-short / 62%), and
ngccc keeps both stores in the preheader **only when the u16 store is written
second** — writing it first gives 24%.

---

## 5. In a paired-single struct builder, the emitted store order can invert two source statements

`fn_80161880` (384B, `-mps-float`): 91.7% → 92.7% purely by writing
`F.w80 = F.wa0;` **before** `F.b88 = byte_value;`. Retail emits
`stb r9,0x88(r1)` then `stw r0,0x80(r1)` — the radius store precedes the
id-byte store even though `b88` is assigned first — and that single swap also
flips the r0/r9 allocation coin on both operands.

Ruled out at 92.7%: reading the byte through the live `id_ptr` base
`((u8 *)id_ptr)[3]` (63.5%), hoisting `F.w50 = 0` to the top of the tail
(89.6%), moving `F.p2c = payload` after `F.b28` (85.4%) or after `F.h2a`
(84.4%), moving `F.h2a` before `F.b28` (88.5%), `u8` / `((u8*)&F.id90)[3]`
spellings, and `-fno-sched-spec` / `-fno-expensive-optimizations` /
`-fno-strength-reduce` (all no-ops). `-fno-schedule-insns2` is much worse
(75%).

---

## 6. Frame size is a *liveness* fact: one value live across a call costs 8 bytes

`fn_80232B98`'s old draft was length-correct at 71.6% but had the wrong frame
(`stwu -0x30` / `stmw r27` against retail's `-0x28` / `stmw r28`), because it
held one extra value live across a call — an m2c use-before-def,
`pB[1] = temp_r3;` written *before* `temp_r3 = fn_8019CF2C(0);`. Moving the
store after the call removes the register *and* the frame, and it is the same
edit that makes the rest of the body fall into place.

This is doc 83's local-size arithmetic seen from the other side: don't only
compute the locals area from the want, check that the number of values live
across each `bl` accounts for the `stmw`/`lmw` span and the frame size. An
inert extra callee-saved register can be silently cancelled by a missing
instruction elsewhere, which is why the old draft was "size-exact" and still
wrong.
---

## 7. The locals-area allocation rule (address-taken above, volatile below)

`fn_8000BC4C` / `fn_8000BD04` (184B twins) park on one word — `addi r9, r1, 8`
against `addi r9, r1, 0x10` — and chasing it produced a clean rule that is
worth more than the two functions.

The want needs a 12-byte **address-taken** node at `r1+8` *and* a frame of
`0x20` (locals `[0x8,0x1c)` = 20 bytes, `Gsave` at `0x1c`, LR at `0x24`). The
draft buys the extra 8 bytes with a `volatile s32 spC[2]` pad, which lands the
node at `r1+0x10`. Delete the pad and the node lands at `r1+8` exactly — but the
frame collapses to `stwu -0x18`.

The rule, established over 14 measured forms:

| local kind | where it goes in the locals area | why |
|---|---|---|
| address-taken **scalar** | **top** (highest offsets) | its `force_const_mem` runs late, during RTL expansion |
| `volatile` object | **bottom** (lowest offsets) | allocated in the early volatile pass |

Declaration order is irrelevant, and an *aggregate* (array/struct) folds its
address to a frame offset, so it behaves like a normal local. Confirmed with:
`volatile struct`, two separate `volatile s32`, `volatile char[8]`, `volatile
s64`, a nested-scope `volatile`, both declaration orders, and a pad made
address-taken by a dead pointer store placed before *and* after the node's
first store.

The dead-store form gets the **order** right (node at `r1+8`) but GCC removes
the store before RTL expansion, so `force_const_mem` never runs and the slots
are never assigned — the frame drops back to `0x18`. A folded
`if (&padA == &padB) padA = 1;` folds away too (and overshoots to `0x28`).

**The only measured form that gets both** is an address-taken pad kept alive by
a zero-code memory-constraint barrier placed *after* the node's first store:

```c
s32 sp8, padA, padB;
...
__asm__("" : : "m"(padA), "m"(padB));   /* 0 emitted instructions */
```

That fixes the entire prologue (`stwu -0x20`, `stw r31,0x1c`, `stw r0,0x24`,
`addi r9,r1,8` all match) — but it also lets cc1 CSE the `lbl_` address and hoist
the final vtable store above the address-taken chain, which costs more than the
frame wins. Recorded rather than applied (this round's no-inline-asm rule), and
worth remembering the next time a want's node sits at the *bottom* of a frame
that is bigger than the node.

**Generalisable reading:** if a want's stack object sits at a LOWER frame offset
than yours while your frame size already matches, you have a *volatile* local
where retail had an address-taken one (or vice versa) — it is not a scheduling
problem and no store-order or flag lever will move it.

---

## 8. A "dead" `li Rx,0` in the want is a *merge-point* fingerprint, not dead code

Retail sometimes emits an assignment that is provably redundant: it compares r11 against zero, branches on non-zero to a load path, otherwise zeroes r11 even though r11 is already zero on that edge and jumps to join, loads r11 from offset 4 on the taken path, ORs r11 with itself setting the condition into r3 at the join, then branches to exit on zero.

`ngccc` deletes the `li` and collapses the whole select to four instructions
(`cmpwi / li r0,0 / beq .exit / lwz r0,4(r11) / or. r3,r0,r0`). Telling: the
draft's `G:` stream is **one word SHORTER** in that window, not merely
reordered.

The reason is a **flow** difference, not a scheduling one. Retail's two select
arms converge on `.B: or. r3,r11,r11` and only *then* branch to the exit.
ngccc jump-threads the zero arm straight past the `or.` to the exit, because on
that edge the guard value is provably already 0 — retail's loop-guard variable
is dead after the loop there, so the guard register and the exit value coincide.

**Triage rule:** when a want contains a store/`li` to a register whose value is
already known, do **not** look for a source shape that forces the redundant
write (5 further spellings measured on `fn_8000BC4C`: write-back into the pinned
variable, both arm orders, ternary, redundant re-assign — all 1–2 words short or
identical). Instead ask *why the merge point exists* — i.e. whether the value is
genuinely dead on the early-exit edge. If it is, the `li` is unreachable from C.

Same shape in `fn_8021B6C8` (`bne / li r11,0 / lwz r11,4(r11)`), so any fix is
worth both.

## 9. `addi rX,rBase,off` + `stfsx/stwx ...,rX,rIdx` is one strength-reduce decision, not seven

In `fn_8011C820` retail gives **every** store in the block its own base
(`addi r7,r30,0xc ; stfsx f13,r7,r29`, `addi r10,r30,8 ; stfsx f0,r10,r29`, …,
seven of them). ngccc gives some of them a shared address expression instead
(`add r10,r29,r30 ; stfs f0,8(r10)`) and swaps the operands of the indexed ones
it does emit (`stfsx f13,r29,r9` — index first — against want's base-first
`stfsx f13,r7,r29`).

Two traps when chasing this:

1. **The emission order is not the source order here.** Swapping the two `f32`
   stores and/or the two `s32` stores produces *byte-identical* output — so a
   store-order search will burn a lot of compiles for nothing.
2. **Once the streams diverge, the index-aligned diff lies.** The `G:` words
   printed against a shifted region do not correspond to the `W:` words beside
   them; a "field offset is swapped" reading can be pure misalignment. Read the
   got object (`tools/reloc_diff.py` / the raw `.o`) before concluding anything
   semantic.

Ruled out there: named `f32 *` / `s32 *` locals for the accesses, unifying the
two spellings of the base pointer (that one is *load-bearing* — the mixed
spelling keeps 6 words of code alive), hoisting the interleaved call, and eight
scheduler/strength-reduce flags. Note that `-fno-tree-loop-optimize`,
`-fno-ivopts` and `-fno-tree-ch` **do not exist** in ProDG cc1 — it is GCC 2.95,
so a flag list copied from a modern GCC manual will silently do nothing.

---

## 10. Pool-wide A/B of every inherited `// FLAG:` — the pool is CLEAN (2026-10-03)

§3 found one stale flag by hand (`fn_802347D0`). That prompted an automated
sweep: **every** draft carrying a `// FLAG:` or `// extra_cflags:` line was
compiled twice, with and without it, and the two scores compared.

```
287 flagged drafts A/B-ed across the whole pool (2 chunks of 900)
IMPROVE  0        hurts  0
```

So the remaining flags are all still load-bearing. Worth knowing before anyone
spends time on it again — and worth *re*-running after any bulk body edit, since
§3's failure mode is created by edits, not inherited.

## 11. A pinned *argument* register cannot stop GCC forwarding the *value*

`fn_800A16B8` (308B, `-mps-float`, 98.7% — one word) looks exactly like
doc 85's `fn_80221C8` case: want `mr r3,r28` where got has `mr r3,r30`, and the
draft already pins `sp28` to r28 and `sp30` to r30. The doc-85 pin does **not**
transfer, and the reason generalises:

```c
register A16B8 *sp28 __asm__("r28");
register A16B8 *sp30 __asm__("r30");
...
register A16B8 *q3 __asm__("r3");
q3 = sp28;                       /* -> still emits mr r3,r30 */
f(q3);
```

GCC does not choose r3 for the *argument*; it chooses **r30 for the value** and
then copies into r3. Because `sp28` and `sp30` are provably the same value,
CSE looks straight through the intervening `mr r28,r30` and the intervening
`bl`. Pinning the destination register constrains where the copy lands, not
where the copy's *source* is read from.

**Rule:** doc 85's argument pin works when the register allocator has a *choice*
between two home registers for the value (the `addi`-rematerialisation case).
It cannot work when the two candidates are already proven equal — then there is
no choice left to constrain, and the only lever would be making the two
variables non-equivalent, which no spelling of `&sp8` manages.

Measured and ruled out there (7 variants): r3 alias sourced from sp28 or sp30,
the alias live across both `if` arms, `sp28 = sp30` moved to just before the
`if`, `sp28` assigned inside the then-arm, `sp30 = sp28` after the `if`, and
`-fno-gcse` / `-fno-cse-follow-jumps` / `-fno-thread-jumps` (all no-ops).
