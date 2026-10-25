# 67 — m2c invents a return value for a `void` function (crashes the frame)

**Status: SOLVED 2026-09-20 — `fn_80182B88` 62.5 % → 100 % EXACT, promoted
(DOL byte-identical).**

## The shape

m2c always produces a value-returning draft. When the retail function is
actually `void`, it synthesises a local that starts as an argument and
`return`s it at the end:

```c
void *fn_X(void *arg0, s32 arg1) {
    void *var_r3;
    var_r3 = arg0;                       /* m2c's invented "result" */
    ...
    var_r3 = fn_8017471C(...);           /* overwritten mid-body */
    ...
    return var_r3;                       /* never read by anybody */
}
```

That variable is **live across the later call** in the only path that matters,
so ngccc cannot keep it in `r3` — it spills it to a **callee-saved** register
and the whole function drifts: want saves a single register with a word store while got saves a two-register range with a multiple store and a wider frame, want tests the value in place in r3 while got tests it in the saved register, want needs no move before the tail call while got copies the saved register back into r3, and got carries the matching multiple-restore in its epilogue. The tell is a **`stmw`/`lmw` span one register wider than want's** (two-register multiple save versus single-register word save) plus a spare copy into r3 right before the tail call.

## The fix

Declare the function `void` and **delete the return statement** (and, if the
tail callee is genuinely void, declare it `void` too). The value then stays in
`r3` exactly as retail has it. `fn_80182B88`: 62.5 % → 67.6 % (keeping the
invented return but fixing everything else) → **100 %** the moment the return
was dropped.

Do **not** try to keep the pointer return and just change what is returned
(`return arg0;` = 81.8 %, `return call(...)` = 13.9 %) — both re-introduce a
move. The signature is the defect.

## Related

- Stacked with [doc 56](56-missing-prototype-calls.md) (both callees were
  undeclared → two `crclr cr1eq` words) and
  [doc 53](53-field-width-retype.md) (the `lha` needs a real `s16` lvalue —
  a `(s16)` cast on an `s32` member is a no-op).
- Cheapest general check for any `stmw`/`lmw` frame mismatch: compare the saved
  span against `want` before blaming register allocation.
