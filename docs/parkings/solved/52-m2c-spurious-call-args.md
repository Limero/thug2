# 52 — m2c spurious call-args (label re-args, phantom rodata consts, self-args) + the crclr prototype companion

**Status: CLOSED (2026-09-06) — 31 members promoted EXACT in one session.**
Three related m2c corruptions all produce "extra argument at the call site"
bodies that never match, plus a companion artifact (unprototyped-call
`crclr cr1eq`) that masks the fix if it is applied alone.

## The shapes

### 1. Label re-arg (label-stash)

m2c turns `arg0->unkNN = (s32)lbl_X; fn_Y(arg0);` into

```c
arg0->unkNN = (s32)lbl_X;
fn_Y(arg0, (s32)lbl_X);   // 2nd arg is m2c noise
```

**Diagnostic in want:** r3 (=arg0) stays live across the call — want shows
`mr r11, r3` (or `mr r30/r31`) BEFORE the label materialization, and the `bl`
is immediately followed by the return-home. The draft instead shows
`mr r3, r9` (label into r3) before the `bl`.

**Fix:** drop the second arg. Every confirmed callee really is 1-arg.

### 2. Phantom rodata constant arg

`fn_801282E0(a, b, c, d, 0x80290000)` — the trailing `0x80290000` (and
`0x8028FCxx`-class literals) is m2c spilling the rodata base register as a
call argument. The real callee here is 4-arg:
`s32 fn_801282E0(Unk_2EF06E12 *, s32, f32 *, s32);`. Same for
`fn_80005854(0x80290000)`-style single-arg phantoms.

**Fix:** drop the phantom arg; restore the real arity from the callee's own
promoted source.

### 3. Self-arg (fnptr re-arg)

m2c appends the called function pointer itself as the last argument:

```c
temp_r9_2 = sub->unk0x44;
temp_r3 = temp_r9_2((char *)obj + off, temp_r9_2);   // 2nd arg = noise
```

**Fix:** drop it; also prefer the single-source-variable form (reuse the
receiver variable for the call result) when want reuses the same register.

### 4. Companion artifact: `crclr cr1eq` on the call

After fixing any of the above, the call still shows `crclr cr1eq; bl` in got
vs plain `bl` in want whenever the callee lacks a prototype in the draft TU
(ngccc treats it as a K&R-style unprototyped call).

**Fix:** add the real prototype, e.g. `void fn_800107A0(Unk_B6E8234C *);`.
This is REQUIRED — the arg fix alone leaves a 2-word residual.

## Results (2026-09-06, all DOL byte-identical)

- Label re-arg, 17 promoted: fn_80010910 fn_80011EA8 fn_80011F64 fn_80013144
  fn_80014B94 fn_8002448C fn_80034684 fn_80041F5C fn_8004F15C fn_8004F1E0
  fn_80055A48 fn_8007D4B0 fn_8009A758 fn_800B6D30 fn_8010192C fn_80203EC4
  fn_80235190 (plus the 48B quartet fn_800726F8 fn_8007C6BC fn_800948AC
  fn_80205460 earlier the same day).
- Phantom rodata arg, 6 promoted (all 68B siblings): fn_800702E0 fn_80070394
  fn_80070470 fn_800705F4 fn_800707F4 fn_800708D0.
- Self-arg / wrong-struct / dropped-first-arg one-offs: fn_8005742C
  (wrong struct type hid an s16 `lha` offset; single source var for the call
  result; store-pair reversal), fn_8005F100 (2-arg unprototyped fnptr
  dispatch; VOID return — want re-loads arg0 after `blrl`), fn_800A3BDC
  (dropped FIRST call arg; load-before-store order vs `sp8 = 0`).

## 2026-09-13 — one more self-arg member, plus the dispatch-entry companion

`fn_80077718` (64B) promoted EXACT with no special cflags. Its draft was the
shape-3 self-arg exactly as m2c wrote it:

```c
((s32 (*)(void *, s32, void *))temp_r9->unk0xC)(
    (char *)arg0 + temp_r9->unk0x8, 3, temp_r9);   // 3rd arg = the fn pointer
```

want never loads r5 (`li r4, 3` then straight to `blrl`), so the callee is
2-arg. Dropping the third argument alone got it to 93.8%; the last word needed
recipe 47 as well: the +0x214 entry is the 8-byte `{ s16 self-offset; s16 pad;
s32 handler; }` pair, and retail's `lha r3, 8(r9)` only matches if that offset
is *signed halfword*, not m2c's s32 view:

```c
typedef struct DispEntry { s16 unk0x0; char pad0x2[0x2]; s32 unk0x4; } DispEntry;
temp_r9 = (DispEntry *)arg0->unk0x214;
((s32 (*)(void *, s32))temp_r9[1].unk0x4)(
    (char *)arg0 + temp_r9[1].unk0x0, 3);
```

**Lesson:** when a self-arg call still shows a 1-word residual after dropping
the phantom arg, look at the *arguments* for an `lha`/`lbz` width mismatch — the
arg fix and recipe 47 are independent and both have to land. NOTE: unlike the
2026-09-06 members, this one needed **no** `-fno-schedule-insns` and no
prototype companion.

## Caveats

- **Always A/B with my_diff before keeping** — for fn_801A1B2C the same
  reasoning produced a tie, and blind application elsewhere regressed.
- Drafts with additional m2c corruption (statement noise `0;` lines, raw
  rodata derefs, wrong struct types) become honest-but-low DIFFs after the
  arg fix; they need full re-matches (fn_800058CC etc.).
- Members where want's callee arity genuinely includes a pointer the draft
  dropped (e.g. fn_800A3BDC dropping arg0) show up as a swapped
  register/operand set at the call — compare full want listings, not just
  the score line.

## 2026-09-15 — ten more members, and the *trailing*-literal signature

A random-then-censused sweep of the 1,787 no-park drafts found **ten** more
doc-52 members, all byte-exact (DOL `ff6faeb0…` verified after promotion):

| fn | size | phantom arg m2c invented |
|---|---|---|
| `fn_80050140` | 56B | `fn_8004F2C4(0, 0x80292CB0)` → `fn_8004F2C4(arg0)` |
| `fn_80066E68` | 56B | `fn_80062DBC(0, 0x80294340)` → `fn_80062DBC(arg0)` |
| `fn_80067554` | 56B | `fn_80062DBC(0, 0x802944D8)` → `fn_80062DBC(arg0)` |
| `fn_800677A8` | 56B | `fn_80062DBC(0, 0x80294560)` → `fn_80062DBC(arg0)` |
| `fn_80067BA4` | 56B | `fn_80062DBC(0, 0x80294670)` → `fn_80062DBC(arg0)` |
| `fn_80067DB4` | 56B | `fn_80062DBC(0, 0x802946F8)` → `fn_80062DBC(arg0)` |
| `fn_80067FC4` | 56B | `fn_80062DBC(0, 0x80294780)` → `fn_80062DBC(arg0)` |
| `fn_800681D4` | 56B | `fn_80062DBC(0, 0x80294808)` → `fn_80062DBC(arg0)` |
| `fn_80069130` | 72B | `fn_80068F70((char *)arg0 + 8, 0x80294980)` → 1-arg |
| `fn_8006E9AC` | 72B | `fn_8005CF80(lbl_80366478, lbl_8030145C, 0x80360000)` → 2-arg |
| `fn_8009F60C` | 56B | `temp_r9_2(a, b, temp_r9_2)` (the fnptr itself) → 2-arg |

The eight `0x8005xxxx`/`0x8006xxxx` vtable setters are one family: they store
two rodata-table pointers into the object and then call a shared base
initialiser. The 2026-09-06 note said each of these needed
`-fno-schedule-insns` — that is a *symptom*, not the fix: with the phantom arg
dropped the whole family is exact at **default flags**, because the removed
`li r3,0` + `lis/ori r4` (3 words) was what the scheduler flag was hiding.

### The signature, refined

The literal m2c invents is usually a **`0x80300000`/`0x80360000`-style high
half** or the low half of a label it also passed for real. Read it as: *"m2c
mistook the `lis` that forms some symbol's `@ha` for a third argument"*. So
before adding a prototype, look at retail's arg registers — if the last arg's
register is **never written** between the previous call and the `bl`, the
argument does not exist.

### Automation

`tools/drop_phantom_arg.py` (2026-09-15) does the whole sweep: a paren-matching
scanner finds every call whose argument list contains a bare `0x80xxxxxx`
literal, drops that argument, trims the matching prototype parameter, scores
the variant and prints `addr orig% -> STATUS variant%`. Over the 124 drafts
that contain such a literal it produced **36 improvements** (the four biggest:
`fn_8004567C` 40.9→76.2, `fn_800A3C50` 19.4→75.9, `fn_800A33E4` 19.4→74.3,
`fn_800685A4` 36.7→72.4) and the ten complete matches above. The tool kept the
best body in place for all 36.

### Companion levers still required

- `fn_8009F60C` needed doc-53 as well (the dispatch offset it reads is `s16`,
  retail `lha`), exactly like the `fn_801A1B2C` lesson below.
- `fn_8004567C`, `fn_800A3C50`, `fn_800685A4` plateau at 72–76% after the arg
  fix: their residual is the `crclr cr1eq` from an unprototyped callee
  (`fn_8005EBE4`). Adding the real prototype drops them to ~33% because it
  re-colours the whole function — the same "prototype cannot be separated from
  the colouring" wall as doc 56. Left as improvements, not parks.

## 2026-09-15 (b) — two more transcriptions of the same family

Chasing the residual of `fn_8009F054` (64B) exposed two further ways m2c
mangles a call, both now promoted:

1. **`fn_8009F054` — the argument ORDER is transposed.** m2c wrote
   `fn_800A54AC(lbl, -1, arg0->unk0x18, arg2, 1, f)`; retail leaves **r4
   untouched** (the callee's 2nd argument is this function's own 2nd parameter,
   passed straight through) and shifts the rest one slot:
   `fn_800A54AC(lbl, arg2, -1, arg0->unk0x18, arg1, 1, f)` — 7 args, not 6.
   Diagnostic: an **off-by-one down the whole argument register set** — want
   `lwz r6,0x18(r3)` where ngccc has `lwz r5,0x18(r3)`, want `mr r7,r5` where
   ngccc has `mr r6,r4`, `li r5,-1` vs `li r4,-1`, `li r8,1` vs `li r7,1`.
   Four shifted words in a 16-word function is not regalloc noise: it is a
   missing/extra argument. `tools/argshift_scan.py` (2026-09-15) scores every
   draft for this signature (`shift=N real=M total=T`), but the naive
   "all registers move" test is too strict — the *destination* moving while a
   base register holds still (as in `lwz r6,0x18(r3)` vs `lwz r5,0x18(r3)`) is
   the common half of it, so read the diff, don't trust the counter alone.
2. **`fn_80041FDC` — the *address* of a float label instead of its value.**
   m2c emitted `fn_800A54AC(…, 0, lbl_80292398)` with `extern f32
   lbl_80292398;` and **no prototype for the callee**, so ngccc passed the
   label as an integer (`lwz r4,0(r29)`) and inserted `crset cr1eq` for the
   unprototyped call. Declaring the real 7-param prototype ending in `f32`
   gives retail's `lfs f1,0x2398(r9)` and removes the `crset`: 71.8 → **96.1%**
   in one line. Residual is 3 words of pure scheduler slot-fill before the
   `fn_80127684` call (want materialises `&sp8` first); parked with a note.
   This is the doc-57 lesson in the other direction: **the last argument's type
   decides whether you get `lfs` or `lwz`, and the prototype is what carries
   it** — an unprototyped call also gets a `crset`/`crclr cr1eq`.

Both were found by reading `tools/real_diffs.py` output (non-branch mismatches
only) on the *residual-ranked* pool, not by sampling.

### Addendum 2026-09-15 (e): the phantom arg can be a *label*, not just a literal

`fn_800249A4` (156B) is the clean example. m2c produced

    arg0->unk0x8 = (s32)lbl_802913F8;
    fn_800550D4(arg0->unk0x10, (s32)lbl_802913F8);      // 2nd arg is invented

but retail only materialises that label for the *store*; the call receives the
function's own `arg1` (already live in r4 — no `mr r4, r9` anywhere in want).
Two other fixes rode along: the vtable offset is `s16` (doc 53, `lha r3,8(r9)`),
and the `arg0->unk0x10` field has to be read into a local *before* the
`arg0->unk0x8` store, otherwise MWCC hoists `mr r30, r4` above
`lwz r3, 0x10(r31)` and the body lands at 94.9%.

Scanner: `tools/label_arg_scan.py` — same A/B shape as drop_phantom_arg.py but
matching *symbol* arguments (`(s32)lbl_X`, `&lbl_X`, `lbl_X`, `(s32)0x8029xxxx`)
in any argument position except the trailing one. 179 candidate drafts →
33 improvements, best `fn_8006A8C0` 41.7→91.3 (then 100 with the doc-51
literal→symbol fix) and `fn_80054388` 50.0→73.7 (then 89.5 by hand).

**Detection:** if want's call has *no* instruction that loads/moves the
register m2c assigned to the extra argument, the argument is invented. A label
in want usually appears once, feeding a store; m2c re-reads the `lis/addi` pair
as an argument because it cannot tell the two uses apart.
