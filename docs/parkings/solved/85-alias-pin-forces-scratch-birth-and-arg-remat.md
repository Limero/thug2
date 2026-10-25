# 85 — The alias pin: force a scratch-birth split, or force an argument rematerialisation

**Status:** SOLVED 2026-10-03. Three parked drafts went to byte-exact clean C,
no inline `__asm__`:

| function | size | was | now |
|---|---|---|---|
| `fn_80232B98` | 324B | 71.6% (wrong frame, wrong bool lowering) | **EXACT** |
| `fn_80227D64` | 344B | 96.5% (1 word) | **EXACT** |
| `fn_80221C00` | 180B | 97.8% (1 word), parked as *"not reachable from C. Keep as asm leaf."* | **EXACT** |

Not promoted (per this round's brief).

---

## 1. The symptom: `addi rX, r1, off` + `mr rY, rX`

A long-lived stack address that retail computes **once** and keeps in a
callee-saved register is emitted by retail in two instructions: the address is born into a scratch register, copied into the long-lived home, the first use still addresses off the scratch, and later uses address off the home. Plain C always folds this into one home-register computation with all stores through the home.
Thirteen parked drafts carried a note to exactly this effect ("pA base-web
wants scratch-birth", "every C form homes directly", "pin r26 direct-birth
folds the copy"). Two of them turned out to be exactly this, and one had been
declared unreachable.

### The lever: pin a *short-lived alias*, copy out of it

Pin the **transient** register, not the long-lived variable. The long-lived
variable is then forced to be born by a copy rather than by a second `addi`:

```c
register s32 *q __asm__("r11");      /* the SCRATCH, short-lived */
s32 *pA;                             /* the HOME, long-lived  */
...
q = &sp8[0];
q[3] = (s32)lbl_8029FC18;            /* first use -> stw via r11 */
pA = q;                              /* <- the copy that becomes mr r28,r11 */
...
pA[3] = (s32)lbl_8029FC18;           /* later use -> stw via r28 */
```

**The order of the two statements is load-bearing.** In `fn_80227D64` the
alias must be assigned *after* the two stores it precedes, not before, or the
`addi` hoists above them and you lose a word (98.8% instead of 100%).

### What does NOT work (measured, do not re-try)

| attempt | `fn_80232B98` | `fn_80227D64` |
|---|---|---|
| array decay `pA = sp8` | 1 word short | — |
| `pA = pB - 1` | 1 word short | — |
| real `struct` local | frame collapse, 24% | — |
| first store by `sp8[3]` index | register map flips | 2 words short |
| last store by `sp8[3]` index | — | 2 words short |
| address taken at its use site | 10 diffs | 8 diffs |
| `pA` born before the branch chain | 10 diffs | r30/r31 cascade, 12 diffs |
| a redundant extra alias `q` | 1 word short (dead-code eliminated) | — |
| **pin `pA` itself** (`__asm__("r28")`) | **1 word short** | **1 word short** |

Pinning the long-lived variable is the trap: r28 is *already* what local-alloc
picks for it, so the pin is a no-op and there is nothing left to copy out of.
The whole recipe is "make the copy source explicit", and it only works if the
copy source is a register the allocator would otherwise have reused.

---

## 2. The same pin, applied to a call argument

`fn_80221C00` (180B) is the argument-register face of the same defect. Retail
**rematerialises** the stack address into the argument register on the second
call inside a loop instead of copying the home it already has: the address is homed once, the first call reuses the home (which got matches), and the second call recomputes the address into the argument register where got emits a copy from the home. While the home is live, CSE + reload fold the argument into a home-register copy. The
pin makes the destination register a named variable, which stops the fold:

```c
register CStruct *q4 __asm__("r4");
...
q4 = (CStruct *)&sp8;
var_r3 = fn_8021D4E8(temp_r31, q4, 1);
```

Assigning `q4` at **both** call sites also scores 100%, so the pin does not
disturb the site that wants the reuse. Ruled out: a plain braced temp (97.8%,
unchanged), an `r9`-pinned alias (68.9%, the homes swap), and dropping the
draft's `__asm__("" : : "m"(_pad))` barrier (86.7% — the locals region
collapses and the frame flips to `0x20`/`stmw r29`, so the barrier is
load-bearing for the frame, exactly as recipes §6x-84 says).

---

## 3. Corollary: a redundant save-copy live across a call steals the argument

`fn_80227D64`'s second residual was `mr r4,r25` where retail has `mr r4,r30`.
`wp` is pinned to r30, and `wp2 = &fr.o0` copies it to r25 because `wp` is
reassigned inside the loop. While `wp2` is live at `fn_8021D454(temp, wp, 0)`,
local-alloc's *prefer* pass substitutes the copy.

**Take the save-copy after the call that should use the original.**

```c
var_r3 = fn_8021D454((s32)temp_r28, wp, 0);
wp2 = (s32 *)&fr.o0;          /* <- sunk past the call */
```

The copy still lands above the call in the output (`mr r25,r30`), so this is
purely about which value is *live* at the call site. Both `wp2 = wp` and
`wp2 = (s32 *)&fr.o0` score 100%. Ruled out: passing `&fr.o0` directly at the
call (98.8%), pinning `wp2` to r25 explicitly (98.8%).

**Generalisation:** whenever a draft keeps "the old value of a variable that
gets reassigned" in a second local, check whether that second local is live at
a call that passes the first. Sinking the copy is a zero-code fix.

---

## 4. Why the rest of the pool did not fall

399 parked drafts contain this `addi`+`mr` signature (scanner: any `addi rX,
r1, off` within 3 instructions of `mr rY, rX`, `X != Y`, `X != sp`). But
scored individually, **all** of them are either below 80% or length-mismatched
except the three closed here plus `fn_80161880` (92.7%, a 3-word hoist window)
and `fn_800F3BB0` / `fn_80190ACC`, whose residuals are a different coin
(`li` register-order rotation; adjacent-web r20/r21 colouring). The
scratch-birth word is real but rarely the *only* difference.

The highest-scoring members of the pool, for whoever picks this up next:

| function | size | current | residual |
|---|---|---|---|
| `fn_80223FA0` | 592B | 98.65% | `[li r6,1]` must precede `[addi r5,r1,0x58]`; an `r5` pin **hoists the `addi` out entirely** (object 1 word short), so the pin does not transfer |
| `fn_8021BC54` | 652B | 96.93% | `addi r9,r1,0x10` / `lwz r3` / `li r0` / `mr r29,r4` window rotation |
| `fn_8021C080` | 308B | 94.81% | `lis r11` window position |
| `fn_80190ACC` | 1232B | 96.75% | r20/r21 colour flip for the `&sp108` web + the `var_r21` bool; see §4 note below |

**`fn_80190ACC` note:** retail also splits this address — `addi r3,r1,0x108 ;
mr r20,r3` — so §1 applies verbatim to `&sp108`. The draft's own note records
that pinning `var_r21` to r21 directly *breaks* the `arg4` guard's CR pair and
reshapes the `subfic/adde`; the alias-pin route (pin a short-lived `r3`
alias for `&sp108`, copy into the long-lived web) was **not** tried. That is
the most promising untried lever on this function.

---

## 5. Related

- Doc 75 (`reload_pin_sweep.py`) — the same pin idiom for reload/arg
  residuals; this doc is the address-of-a-local variant.
- Doc 15 / 32 — "role rotation" and adjacent-web colouring, which this pin
  sometimes clears as a side effect (the `r25`/`r30` argument in §3).
- Recipes §6x-84, §7e-2 — register pinning conventions; every pin in §1 is
  the zero-code `register … __asm__("rN")` form, no statement-level asm.