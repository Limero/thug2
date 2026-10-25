# 91 — Keeping consecutive dead stores: barriers work, threading wins anyway

**Status: WALL (verified 2026-10-19 on `fn_8000BA88`, ProDG/3.9.3, default
game flags).** Retail executes two back-to-back stores to the same stack slot
with no intervening load (`stw r9,4(r8)` / `addi r9,r3,4` / `stw r9,4(r8)` at
0x8000BAC0–0x8000BAC8), plus a provably dead `cmpwi r9,0` before the first.
Every C spelling tried routes the valid path *around* the stores.

## What keeps N consecutive dead stores (micro-tested, all at -O2)

| Attempt | Result |
|---|---|
| same-type `pa->c` x3 | 1 store |
| different struct types (`A*` / `B*`, identical layout) | 1 store — **ProDG ignores type punning for DCE** |
| `int*`-derived middle store | 1 store |
| `char*`-derived middle store | 1 store |
| `union { A; B }` alternating members | 1 store |
| one empty `__asm__ volatile("":::"memory")` between S1/S2 | 2 stores (pre-barrier + last survive) |
| **barrier between EACH pair** | **all 3 survive at zero instruction cost** |

So the only working keep-mechanism is a fence per gap. It is a stand-in,
not the true source: retail has no fence insns (all 58 want words map to
real ops), so whatever defeated DCE in the original (C++ alias sets?
inlining order?) is still unknown. Do not promote a barrier match as
source-truth without that answer.

## The threading wall (why barriers are not enough)

With the stores kept, ngccc jump-threads the `-1`-check's valid edge *past*
both stores and the second prime's address computation (which folds
`(arg0+4)+0xC` into `arg0+0x10`) straight to the extract join. Verified in
all 4 combos of {pure, memory second-prime read} x {no-barrier, barrier}.
`-fno-thread-jumps` produces byte-identical output (does not control this
pass in 2.95); `-O1`, `-fno-gcse`, `-fno-cse-follow-jumps` identical;
`-fno-jump` / `-fno-cse` / `-fno-crossjumping` rejected by ngccc.

Consequence: **straight-line consecutive dead stores are unreachable in C
when the downstream address computation is pure.** Any memory read that
would keep them live (reload of the slot) costs >= 1 extra insn, and in
this function want's 58 words are fully mapped, so there is no room.

## Doc-81 boundary completed (dead compare + store, branchless)

On the same function, completing the identical-arms matrix:

| Arms | Output |
|---|---|
| reg-copy into a local (`tmp = n` / `tmp = n`), single store after | folds ENTIRELY — no compare |
| loads (`state = a->x` both arms, doc-81 shape) | dead `cmpwi` + hoisted load (extra insn) |
| memory stores (`p->f = n` both arms) | dead `cmpwi` + unconditional `b` (extra insn) |
| `if (c) goto L; else goto L; L: store` / `if (c) goto L; goto L;` / `do { store; if (c) break; } while (0)` / bare store | all fold to a bare store |

A branchless compare-then-store of the same register is unreachable in
every construction. Same family as `fn_8000BD04` Wall 2 (dead zeroing) and
`fn_8000BB70` (twin, one-insn key-offset delta).

## Also re-confirmed here

- No-call `p`/`q` webs coalesce: `It *p = &it, *q; q = p;` with entry stores
  via `p` and the rest via `q` folds to one web (no `mr r8,r11`) — doc 88
  holds outside its call-splitting case too.
- A loop-invariant label used in a match arm hoists to the preheader
  (`mr r8,r9`) instead of rematerialising inside the arm; retail
  rematerialises (`lis` in the arm, shared tail via crossjump).
