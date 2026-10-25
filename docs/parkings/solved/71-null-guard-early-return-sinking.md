# 71 — a NULL guard written as an early `return 0` sinks the bail block (and the body is then NOT out of line)

**Status: SOLVED 2026-09-20 — `fn_80054D54` 30.0 % → 100 % EXACT, promoted, DOL
byte-identical.** Same size either way (112 B): the two spellings differ only in
*which* block gcc puts out of line, so the score is the only signal and a
same-size 30 % draft can look like a register-allocation wall when it is a
one-word change of polarity.

## The shape

```c
temp_r3 = fn_80054E1C();
if (temp_r3 == NULL) {          /* <- wrote this; retail did NOT */
    return 0;
}
temp_r29 = temp_r3->unk0x8C;
temp_r30 = temp_r3->unk0x84;
fn_80054C6C(temp_r3, 1);
fn_80054950(arg0, temp_r30, temp_r29 ^ 1, temp_r29, 0, 0);
return 1;
```

want (112 B) — the **body is out of line**, the bail block falls through:

```
    or.  r9, r3, r3          <- record-form compare, identical in both
    bne  <body>              <- taken path = the success body
    li   r3, 0
    b    <epilogue>
body:
    lwz  r29, 0x8c(r9)
    ...
    li   r3, 1
epilogue:
```

got (112 B, 42.9 %) — the **bail block is sunk** past the body (the `== NULL`
arm is treated as the improbable one, which is the layout an early `return 0`
guard produces):

```
    or.  r9, r3, r3
    beq  <bail>              <- branch jumps over the whole body
body:
    ...
    li   r3, 1
    b    <epilogue>          <- extra branch the other layout does not need
bail:
    li   r3, 0
epilogue:
```

Both contain exactly one extra branch, hence identical size — which is why this
reads as a scoring mystery rather than a branch problem.

## The fix

Write the success path as the `if` body and the failure as the trailing return:

```c
temp_r3 = fn_80054E1C();
if (temp_r3 != NULL) {
    temp_r29 = temp_r3->unk0x8C;
    temp_r30 = temp_r3->unk0x84;
    fn_80054C6C(temp_r3, 1);
    fn_80054950(arg0, temp_r30, temp_r29 ^ 1, temp_r29, 0, 0);
    return 1;
}
return 0;
```

`100 %` at DEFAULT flags. An `if (p == NULL) { v = 0; } else { <body>; v = 1; }`
shape that returns `v` at the end is ALSO 100 % (its single exit block lands in
the same place), so the real requirement is "the NULL arm must not be the
`if`-then arm that returns early".

Swept on the same draft (all 112 B): `if (temp_r3 == 0)`, `if (!temp_r3)`,
`s32`-in-place-of-pointer for both the callee result and the struct fields —
all 42.9 %. The pointer forms matter for the *body* (`or.` test, `lwz` field
loads) but not for the layout.

## Companion defect in the same draft (doc 56)

The three callees had no prototypes, so each `bl` grew a `crclr cr1eq` (2 extra
words, 120 B total). Always clear the `crclr`s first — with them present the
layout question is invisible in the size, and the two defects mask each other.

## Addendum 2026-09-21 — when the body *also* contains a bail return, use `goto`

Two more members hit this class where the plain polarity fix is not enough, because
the success body itself contains another `return 0` (or a bail inside a loop).  In
that case the success-arm-first spelling `if (p != NULL) { <body>; return 0; } return 0;`
lets ngccc **cross-jump the two identical `li r3,0` epilogue blocks into one**, so the
function comes out one word short and the surviving block is the *wrong* one:

```
want:  beq  bail_inline        ; bail block placed BETWEEN body and epilogue
       ... body ...
       li   r3, 0
       b    epilogue          ; <- its own block
bail_inline:
       li   r3, 0             ; <- distinct block, falls into epilogue
epilogue:
```

Route every inner bail through an explicit `goto` and put a single label just before
the trailing return — that pins the bail block where retail has it and stops the
merge:

```c
    if (p == NULL) {
        goto fail;
    }
    <body, including `goto fail;` for inner bails>
    return <value>;
fail:
    return 0;
```

`fn_80126620` (120 B) and `fn_800F29CC` (124 B) both went `EXACT` at default flags only
with this shape.  **The masked score hides it**: both spellings read 100 % under
`tools/test_wip_drafts.py` (REL14 displacements are masked) and it is
`tools/br_targets.py` / the `promote_wip.py` refusal that reports
`beq want 0x…90 got 0x…34`.  Run `br_targets` on any 100 % draft before promoting.

## Members

| fn | before | after | note |
|---|---|---|---|
| `fn_80054D54` | 30.0 % | **100 %**, promoted | null-guard polarity; + doc-56 prototypes |
| `fn_80126620` | 37.5 % | **100 %**, promoted | `goto fail` tail label (inner loop bail); `(u16)` index cast; `extern` symbols instead of raw `*(s32*)0x802FFE54` |
| `fn_800F29CC` | 48.4 % | **100 %**, promoted | `goto fail` tail label; 3-arg call `fn_800F2A48(arg0, arg1, arg3)`; `s16` at `+0x40` (`lha`) |

## Related

- doc 56 — undeclared callee ⇒ `crclr cr1eq` before the `bl` (stacked here).
- doc 70 — same family of "the score looks like something else": there the
  reloc masks hid a *store* permutation, here the equal size hid a *block*
  placement. In both cases the deciding variable is the **source order/shape**,
  not register pressure.
