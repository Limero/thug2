# 69 — a nested call inlined into an argument makes the OTHER arguments live across it

**Status: SOLVED 2026-09-20 — `fn_801F0E84` 53.1 % → 100 % EXACT, promoted
(DOL byte-identical).**

## The shape

m2c writes a whole call as one expression, with a call of its own buried in a
later argument:

```c
fn_801F0DC8(arg0, x->unk0x18, arg0->unk0x1C ^ 1,
            *(s32 *)fn_8021B55C(g, fn_8022A9D0()), 1);
```

Retail evaluated the nested chain **first** and only then loaded args 2 and 3.
Ours loads args 2/3 *before* the inner call, so they are live across it and must
go into callee-saved registers — the prologue grows a fourth `stmw` slot and the
argument registers get filled by `mr` from those registers instead of by the
loads themselves. The side-by-side comparison tells the story: both sides open identically (offset-0xC load, symbol high-half materialisation, global double-word load, halfword-versus-word load of the 0x1A field, first helper call), then want reloads the global and calls the parameterless helper while got hoists the arg2 and arg3 loads above that call. Want then moves the helper results into the argument registers and calls the value-producing helper, while got xors its hoisted arg3, moves values across, and carries an extra ABI-marker word from the undeclared callee before its own value-helper call. The tails diverge the same way: want reloads the base, sets the constant fifth argument, loads the remaining call arguments directly (offsets 0x1C and 0x18), homes the object, xors the flag and calls the outer function, while got loads through the produced pointer and fills the argument registers with moves from the spilled callee-saved copies before the same outer call.

Prologue: `want  stwu r1,-0x18(r1) / stmw r29,0xc(r1)` (196B) vs
`got stwu r1,-0x18(r1) / stmw r28,8(r1)` (208B) — same frame, one extra saved
GPR and an extra `lmw`/`addi` pair in the epilogue.

Three tells, in increasing order of usefulness:

1. **The `stmw`/`lmw` span is one register wider than want's** — the same tell
   as [doc 67](67-m2c-invented-void-return.md). Compare it before blaming
   register colouring.
2. **want's argument loads appear AFTER the inner `bl`, ours before it.** The
   inner call marks the boundary: any argument whose load sits on the far side in
   want was sequenced first in the original source.
3. The argument registers at the outer call are filled with `mr r4,r28` /
   `mr r5,r30` copies from callee-saved registers; want loads r4/r5 directly.

## The fix

Sequence the nested call into its own statement and pass the value on:

```c
fn_8021D358(*(s32 *)&lbl_80305F9C, *(u16 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x1A));
t = *(s32 *)fn_8021B55C((void *)*(s32 *)&lbl_80305F9C, fn_8022A9D0());
fn_801F0DC8(arg0, ..., t, 1);
```

53.1 % → **91.8 %** (still with the draft's recorded `-fno-schedule-insns`) →
**100 % at DEFAULT flags**.

The `s32 t` local is a *sequencing* device only: `t` is used once, immediately, so
no spill appears — ngccc keeps the call result in `r3` and the deref reads
`lwz r6, 0(r3)`, exactly as want does. A `void *t` local scores identically.

Stacked defects in the same draft (both already known, both needed):

* `0x1A` is a **u16** (`lhz`, not `lwz`) — doc 53 class.
* `fn_8021B55C` / `fn_8022A9D0` needed **prototypes**; the undeclared callee
  emitted the `crclr cr1eq` (doc 56).

## Batch-scan result (negative, 2026-09-20)

`tools/fix_nested_call_hoist.py` already does this for a nested call in the
**last** argument. Generalising it to *any* argument position and running it over
every wip draft that still contains one (232 drafts, one baseline + one compile
per candidate position, kept only on improvement) gave **0 improvements**. The
pool's nested-call cases were already harvested by the last-argument form, and
the remaining 232 are dominated by low-scoring drafts whose blocker is elsewhere
(90% of them are below 40%). Do not re-run this as a broad sweep — apply it by
hand to a *near* draft whose prologue is one saved GPR wide.

## Related

* [doc 67](67-m2c-invented-void-return.md) — same "one callee-saved register too
  many / wider save-GPR span" tell, different cause (an invented return value).
* [doc 15](../15-call-arg-setup-scheduling.md) — the general call-argument-setup
  scheduling wall. This doc is the *solver-relevant* corner of it: when the
  residual is "which side of the inner `bl` does the load sit on", reshaping the
  source (statement sequencing) is the lever, not a flag.
* [doc 55](55-stale-flag-refresh.md) — the recorded flag was the last defect
  here: `-fno-schedule-insns` held the r29/r30 colour swap in place at 91.8 %
  while default flags are byte-exact. Third instance of recipe 66.
