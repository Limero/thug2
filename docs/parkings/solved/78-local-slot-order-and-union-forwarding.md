# Issue 78 — Local stack-slot ORDER is decided by first *use*, not declaration order; and a `union` scratch lets cc1 forward a byte store into the following word load

**Status: SOLVED 2026-10-02 — `fn_800456F4` (196B) DIFF 32.0% → 100% EXACT.**
Two independent, general ngccc behaviours, both found on the same function and
both reusable on the script-command "sp8 = spC" family (`fn_8004523C`,
`fn_80042F44`, … all still carry the shape).

## The want

Want loads the 4-byte value from offset 0x40 of the input object, spills it to the scratch slot at stack offset 0xC before the branch, runs the float-compare branch on the 0.0001f threshold, stores the scaled flag byte into byte 3 of the scratch on the taken path (or zeroes that byte on the else path), reloads the scratch word in the join, takes the out-param address at stack offset 8, copies the scratch value into the out slot, and calls the callee.

So the shape is **two separate 4-byte locals**: a scratch written before the
branch and copied into the callee's out-param after it, and the out-param must
land at **r1+8** while the scratch lands at **r1+0xc**.

## Finding 1 — the slot race, and `volatile` wins it

cc1 gives a local its stack slot **when its MEM (DECL_RTL) is first needed**,
not at its declaration and not in declaration order. Two same-size locals
therefore land at ascending offsets *in order of first use*: a scratch used
before the branch gets r1+8 and the callee out-param (used only after it) gets
r1+0xc — the **opposite** of retail.

Tested and all byte-neutral: swapping the declaration order; renaming
(`aaa`/`zzz`); making the out-param a `s32[1]` array or a 1-member struct;
a dead early `if (&out == 0)`. What works is forcing DECL_RTL at the
declaration with **`volatile`** on the out-param:

```c
volatile s32 outv;   /* volatile ⇒ frame MEM exists before the body is expanded */
s32 tmp;
...
outv = tmp;
fn_8005EC1C(script, (s32 *)&outv);   /* addi r4, r1, 8   ← want */
```

`volatile` costs zero instructions here (the value is written once and only
reached through the address that escapes). Same-size slots then come out
`outv`→r1+8, `tmp`→r1+0xc, and the frame/F64-temp offsets snap into place too.

**Rule:** when want shows two same-size stack locals at swapped offsets from
what your source produces, do **not** try declaration order, names, array/struct
wrappers or pins — mark the *late-used* local `volatile` so it wins the slot
race. (Contrast solved/23, where an end-of-body `"m"` pin made plain escaped
locals tie and declaration order decided; here the two locals do **not** tie,
so the pin buys nothing and `volatile` is the lever.)

## Finding 2 — do NOT type the scratch as a union

Retail's scratch is written as a **word load, then a byte store into that word,
then a word reload**. Spelling the scratch honestly as

```c
union { u32 w; u8 b[4]; } tmp;
tmp.w = in->unk0x40.w;
tmp.b[3] = (s8)(...);        /* cc1 now FORWARDS the byte into the word */
outv = tmp.w;
```

lets cc1 keep the word live in a register and merge the byte with
`rlwimi r7,r11,0,0x18,0x1f` + `rlwinm r7,r7,0,0,0x17`, and the object comes out
**12 bytes SHORT** (184B vs 196B). The loose pun defeats the forwarding
analysis and reproduces retail exactly:

```c
s32 tmp;
tmp = in->unk0x40.w;
if (arg0->unk0x128 >= lbl_8029270C)
    *((u8 *)&tmp + 3) = (s8)((f32)(f64)(u32)in->unk0x40.b[3] * arg0->unk0x128);
else
    *((u8 *)&tmp + 3) = 0;
outv = tmp;
```

**Rule (sister of doc-14's "type the 4-byte slot as a union"):** when want
*stores then reloads* the same word after a partial-width store into it, cc1's
forwarding is stronger than retail's and you must spell the partial store
through an opaque `u8 *` so the two stores stay independent webfs. The
`in->unk0x40` side can still be typed honestly — it is only *read* both ways
(`lwz`+`lbz`), so the union there is free.

## Why the overlapping byte is real

`lwz 0x40(r11)` and `lbz 0x43(r11)` are the **same 4 bytes**: the u32 at
arg0+0xC8 and the u8 at arg0+0xCB (its high byte). No plain C struct can hold
both (a `u8` after a `u32` lands at +0x44), and `(u32)(w >> 24)` is a dead end —
ngccc emits `srwi r0,r0,0x18`, never an `lbz`. Modelling `+0x40` as
`union { u32 w; u8 b[4]; }` is the honest spelling and gives both `lwz`/`lbz`.

## Side findings (not load-bearing, but reusable here)

* `if (!(a >= b)) A else B` compiles to `fcmpu; bso <B>`; `if (a >= b) A else B`
  is retail's `fcmpu; cror cr0un,cr0eq,cr0gt; bns <B>`. m2c gets this polarity
  **backwards** for every member of this family — flip the source condition when
  you see `bso`.
* `(f32)(f64)(u32)x` gives retail's unsigned 2^52 magic (`lis 0x4330; stw;
  lfd; fsub pool 0x4330000000000000; frsp`); `(f32)(f64)(s32)x` adds `xoris`
  and uses 0x4330000080000000 (recipes §6au-231). The `(u32)` cast is mandatory.
* `extern f32 lbl_8029270C;` must stay an **extern symbol**, not a literal
  (`0.0001f`), or you lose the `lis`/`lfs` HA16/LO16 pair.
* The synthesised 2^52 pool is a private 8-byte `.rodata`; it is byte-identical
  to the game's `.rodata2` copy at `lbl_80292710` (0x80292710), so
  `tools/fix_fp_pool.py` retargets the pair at promote time — the usual doc-14
  case, **not** a fake match.

## Reusable

* `fn_800456F4` (196B) ✅ EXACT — object `.text` = 196 = `symbols.txt size:0xC4`
  = `range=` marker; 3 `bl` + 1 `b` (REL24) + 1 `bns` (REL14) all correct.
* Same slot shape still parked: `fn_8004523C` (608B), `fn_80042F44`.