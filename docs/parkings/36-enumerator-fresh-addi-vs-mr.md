# 36 — Enumerator out-param: fresh-`addi` vs homed-`mr` (fresh-addi-vs-mr wall)

**Status: OPEN (7 members, 96.6–97.4% each; +1 member fn_8021EEF4 added
2026-09-21 — want's split reproduced verbatim, see the member table).** First
catalogued
(2026-08-25); extends the doc-15/doc-32 scheduling family with a distinct,
self-consistent signature.

## Signature

Small "next-entry" enumerator wrappers that keep a 2-word iterator struct on
the stack (`{void *unk4; void *unk8;}` at `r1+8`). WANT:

1. **Homes `&iter` in a saved register** for the two late/tail stores
   (`stw rX, 8(r29)` tail sentinel restore, exit-path store), i.e. ONE
   `addi rN,r1,8` birth early + `mr rHome,rN`, then displacement stores off
   `rHome`.
2. **Rematerializes `addi rX,r1,8` fresh at INTERIOR call sites** — every
   call passing `&iter` gets its own addi (or takes it via the arg-passing
   convention) instead of reusing `rHome`.

GOT (ngccc from any C shape tried): either (a) all sites share the one
homed web (interior calls get `mr rX,rHome`) or (b) everything rematerializes
and the tail loses the home. The mirror-image trap: base-pointer form gets
the addis but wrong frame; padded/frame-template form gets the frame but
`mr`s.

## Members

| Function | Score | Note |
|---|---|---|
| fn_8021D2C4 | 97.3% | (s32,s32)->s32 entry walker |
| fn_8021D5DC | 97.2% | twin |
| fn_8021D990 | 97.2% | twin |
| fn_8021D7F0 | 97.4% | twin, single diff @ loop-call arg |
| fn_8021D888 | 97.4% | twin of D7F0 |
| fn_80159894 | ~97% | earlier member |
| fn_8021FE30 | ~90% structural | larger variant: bucket-chain iterator + node-insert; same wall plus walker-select fusion (see draft header) |
| fn_80216C4C | **SOLVED 2026-09-28** (196B) | Smallest member yet and it yields the general rule: **give each access to the out-param its OWN address web.** Three distinct `T *` locals over the same stack slot (`p1`, `p2`, `p3`, each `= (T *)&sp8` at its point of use) reproduce want's one `addi` birth + `mr` home + **two separate fresh `addi`s at the interior sites**, with no pins, barriers or flags. Collapsing to one shared pointer is exactly the GOT case (a) above and scores 81.6%. Also needed its promoted twin **src/fn_8021DA20.c** for the record type and a 3-arg `fn_801A1AE8` — the named "twin" for this member was *itself only a parked WIP draft at 86.7%*, so a twin is a lead, not a source of truth. |
| fn_8021ED5C | 92.2% (408B, DIFF 15.5% → NEAR) | net-lobby command, the BIG twin of fn_8021EEF4 (two walks over the same `search_t`, 9 callee-saved homes). Want's scratch/home split reproduced in **pure C, no pin**, by the fn_80216C4C rule below + two scheduling-order fixes: 15.5% → 78.4% (semantics: the m2c scalars are ONE 0x44B record — as separate scalars every store was dead and deleted) → 84.3% (`volatile` + two address webs) → 87.2% (swap the +0x38/+0x40 field writes) → 89.2% (`GLOBAL_T *g = lbl_802FFE98` named local) → **92.2%** (`e.unk0x20 = 0x10` written after `e.unk0x14`). 8 words left = one root cause (see the 2026-10-02 section) |
| fn_8021EEF4 | 12.7% masked (284B want) | net-lobby command (2026-09-21). WANT reproduces the split VERBATIM: `addi r11,r1,8` birth + `mr r28,r11` home, then BOTH interior call sites emit their own fresh `addi r4,r1,8`, and the tail `stw r9,8(r28)` uses the home. New data points: (a) each site with a bare `&sp8` rematerializes everything and the tail loses the home → got is 4B SHORT (276–280B), which is why the masked score collapses (the 54.9% of the old draft was a length coincidence from a wrong 0x44-byte record type); (b) a named `S21EEF4 *sp = &sp8;` used for the stores homes it everywhere (`addi r28,r1,8`, no copy) = GOT case (a). Also fixed its semantics first: the record is 12 bytes (NOT the shared `Unk_59AB5482` 0x44B → 0x58 frame vs want 0x28), `fn_80219698` takes arg0, and `fn_8019915C` is 2-arg `(s32,s32)` |

## Cracked components (do NOT re-derive)

- **Frame**: `s32 sp8; s32 pad2[2];` + OOB `(char*)&sp8+4/+8` casts +
  a LATE reachable `"m"` pin before the final store → exact frame/stmw and
  keeps slot 8 for sp8. Volatile/align-8 pads sort earlier and steal slot 8.
- **Latch forms**: countdown via recycled variable + `while (--v != 0)`
  gives want's fused `addic.` where flags do nothing (see AGENTS.md §6ap).

## Tried and resisted (per-member lists in draft headers)

named `srch_t*` member stores; §6s-1 two-web init→barrier→copy;
§6x-85 opaque-p on late stores only; in-loop staging var (GCSE folds);
§7d-1 nv "+r" staging before loop call (becomes loop-carried);

**NEGATIVE (2026-08-31): AGENTS §6ao-165 (`-fno-expensive-optimizations`
+ M8.31 void↔s32 proto flip) does NOT crack this family.** Verified on
fn_8021D888: the flag alone, both proto spellings (void*/s32 return), and
flag+proto combos all keep the identical single `mr r4,Home` vs
`addi r4,r1,8` diff (masked-diff stays exactly 1). That recipe solved the
structurally-different 8023D788 family; the enumerator home/remat split here
is controlled by something else web split cannot disambiguate.
`-fno-gcse` / `-fno-schedule-insns` / `-fno-schedule-insns2` /
`-fno-sched-spec` pairs; double-GPR birth/home pins (fixes OTHER functions,
flips this wall into the mr-form); volatile readback.

## Retry hints

Need a construct keeping the two late stores through a homed reg while both
call-site args stay fresh addis. Candidates not yet tried: (a) `__builtin`
opaque copy is unavailable — try `.cpp` frontend test; (b) make the interior
call sites take the iter through a DIFFERENT opaque web each (per-site
`=r"` wedges keyed by call index); (c) check whether retail split a larger
function (register-pressure origin like doc 35).

## MIRROR DIRECTION SOLVED (2026-09-09): source-address-birth rule

The opposite wall — want HOMES `&slot` into a saved reg above a guard
(`addi rN,r1,8` hoisted above `lwz;cmpwi;beq`) while GOT rematerialized a
fresh addi inside the branch (or hoisted into a callee-saved reg only when
expensive-optimizations ran) — was cracked on the screen-element Script
pair (promoted EXACT: fn_8004CD10 ScriptSetScreenElementLock 156B,
fn_8004D4CC ScriptScreenElementExists 100B):

1. **The address must be BORN once, unconditionally, in the SOURCE as a
   named local** — `s32 *h = &sp8.a;` placed between the preceding call
   diamond and the guard. GCC then hoists the addi above the guard into
   the home reg exactly like want. A bare `&sp8.a` at the call site or a
   pre-declared init local is what produced the WRONG
   rematerialize/hoist shapes in the old drafts (their park notes called
   the mechanism a "register shape coin-flip" — wrong: it was source
   address-birth placement).
2. **Slot must be a 16-BYTE struct local** `struct { s32 a,b,c,d; } sp8;`
   accessed as `sp8.a` (want frame = 8 + 16 locals + saved regs; a plain
   `s32 sp8` undershoots the frame by 8).
3. **`-fno-expensive-optimizations` is a two-edged lever**: REQUIRED when
   the CSES pass would invent a SECOND homing across two call sites
   (fn_8004D4CC's early-return CFG — without it GCC CSEs `&sp8.a` into a
   callee-saved reg and shifts the whole prologue); but FORBIDDEN when
   want's tail needs crossjumping to share the `li r3,1` return block
   (fn_8004CD10's two-call diamond — plain -O2 crossjumps it, the flag
   duplicates it).

The original home+remat SPLIT (want homes for late stores AND rematerializes
at interior calls) remains OPEN for the 7 members above — but re-derive
their drafts with rule 1 first (none of the recorded attempts spell an
unconditional mid-function `p = &iter;` birth; all init the pointer at the
declaration site or pass bare `&iter`).

## 2026-10-02 — the fn_80216C4C rule extends to the BIG twin (no pins needed)

`fn_8021ED5C` (408B, 92.2%) is the first *large* member of this wall to be
driven by the pure-C rule the table credits to `fn_80216C4C`. Three
generalisations, each independently measured:

1. **TWO address webs are enough, and the interior walk call wants BARE
   `&sp8`.** `volatile search_t sp8; search_t *q = &sp8; … fn_D454(arg0, q, 1);
   … fn_D4E8(arg0, &sp8, 1); … search_t *s; s = &sp8; s->name = sentinel;`
   → want's `addi r4,r1,8` birth + `mr r23,r4` home + stores off r4 + tail
   store off the home. Collapsing to one shared pointer = GOT case (a)
   (78.4%); passing `&sp8` at every site = 404B with the stores folded to
   `0x10(r1)` (the tail loses the home, GOT case (b)). So the rule is
   *q for the init stores + the FIRST walk call, bare `&sp8` at the interior
   walk calls, a second pointer born at the tail* — a third web was not
   needed even with two walks over the same record. What matters is that the
   second web is born as `s = &sp8` **at the tail**, not as `s = p` (a copy
   of the first web's pseudo, which is always CSE-folded back into it — that
   is the shape the fn_8021EEF4 attempts tried). The `volatile` qualifier
   that the fn_80216C4C recipe carries measured **byte-identical with or
   without it here** (both 92.2%), so it is not load-bearing for this
   member; keep it only as insurance for the split.
2. **NEW LEVER — a loop-invariant `T *g = <global>;` named local decides
   where the global's VALUE load and its page anchor land (+3.1%).** Reading
   `lbl_802FFE98` directly twice leaves ngccc hoisting the `lis` anchor to
   the *end* of the preheader and the reload one slot too low; inserting
   `g = lbl_802FFE98;` between the last `stb` and the field-assignment run
   puts the `lwz r3,-0x168(r25)` exactly where want has it AND pulls
   `lis r25` up to 4th in the preheader (want's slot). Naming the local is
   what matters; using it for only one of the two calls is fine (the second
   use stays a direct global read, as in want).
3. **Field-assignment order: one adjacent swap is worth 3.1%.** Want emits
   the constant store `stw r24,0x38(r1)` (the `= 0x10`) AFTER the
   `lwz r9,0x1c(r31)` that feeds the *next* store; writing
   `e.unk0x20 = 0x10;` first instead of after `e.unk0x14 = node->unk0x1C;`
   costs those 3 words. The `= 0`-family stores must be written
   `+0x40, +0x38, +0x3C, +0x34` (m2c's order with +0x38/+0x40 swapped).

**Residual of the member (8 words) and its negatives.** The only thing left
is a callee-saved home SWAP between two live-across-call pseudos — want
r26 = the `0` shared by the three `= 0` stores and r27 = the loop counter,
got the reverse — plus the two-word order consequence at the head of the
preheader. Measured, all 92.2% or worse: declaration order of every local,
`s32` vs `u32`, decimal vs hex constants, a `s32 zero = 0` named local
assigned in the entry block (89.2%), `var_r27` initialised before the guard
(82.4%) or as the first statement of the loop body, and a plain `while`
instead of `if` + `do/while` (87.2%). Two conclusions for the family:

* **`x = <const>` at the top of a loop body is NOT hoisted to the preheader**
  by ngccc's loop pass (object came out 400B with the `li` still inside the
  body). Loop-invariant *pseudos* hoist; invariant *assignments* do not —
  so a preheader-resident counter always loses the home contest against a
  body-hoisted constant.
* **The live-across-call homes here are handed out in ascending pseudo
  order, i.e. source first-use order**, and the preheader emits its
  preheader-resident insns before the loop-hoisted ones. That is why no
  source spelling could put the `0` before the counter. (Counter-check: in
  this same function `&sp8`→r23, `0x10`→r24, anchor→r25, `&e`→r28,
  `next`→r29, `arg0`→r30, `node`→r31 all match, and only the two
  same-priority body constants swap.)
