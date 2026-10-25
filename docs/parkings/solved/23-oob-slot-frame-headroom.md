# Issue 23 — OOB-slot frame headroom (fn_802334D4)

**Status: SOLVED (2026-08-23) — BOTH members byte-exact at 100.0%.** The +8
headroom comes from two PLAIN same-size pads declared AFTER the OOB anchors,
with ONE empty asm pinning all locals as `"m"` operands at function END
(§6p-105 confirmed and refined): escaped plain locals all tie on cost, so
declaration order assigns slots low-after-high — anchors stay at r1+8/0xC,
pads inflate the frame to 0x20, saves land at 0x18/0x1C. Barrier POSITION
matters: pins before the body or on pads alone displace the anchors; only the
end-of-body 4-way pin preserves the bases.

## Solution — fn_802334D4 (168B, 100.0%, plain flags)

```c
extern char lbl_8029FC18[];
s32 fn_8019CF2C(s32);
void fn_8019CF94(void);
void fn_8019D3E0(s32, s32);

void fn_802334D4(void *arg0) {
    s32 spC;
    s32 sp8;
    s32 padA;
    s32 padB;
    s32 var_r9;

    *(s32 *)((char *)&sp8 + 0xC) = (s32)lbl_8029FC18;
    *(s32 *)((char *)&spC + 0x4) = fn_8019CF2C(0);
    if (*(s32 *)((char *)arg0 + 0x44) == 0x7ECA21E5) {
        var_r9 = 1;
        if (!(*(s32 *)((char *)arg0 + 0x4C) & 2))
            var_r9 = 0;
        if (var_r9 == 0) {
            fn_8019D3E0(*(s32 *)((char *)&spC + 0x4), 0);
        } else {
            goto block_5;
        }
    } else {
block_5:
        fn_8019D3E0(*(s32 *)((char *)&spC + 0x4), 1);
    }
    *(s32 *)((char *)&sp8 + 0xC) = (s32)lbl_8029FC18;
    fn_8019CF94();
    __asm__("" : : "m"(sp8), "m"(spC), "m"(padA), "m"(padB));
}
```

## Solution — sibling fn_8019D3E0 (88B, 100.0%, plain flags)

Three stacked fixes: (a) prototypes for all three callees kill both spurious
crclrs; (b) SEMANTIC fix — `fn_8009D354`'s arg0 is `fn_8009CFB8`'s RESULT
(r3 passthrough), staged through a named temp which reproduces want's
`mr r0,r3; stw r0,0x10(r1)` copy; (c) the anchor is modeled as an **f64 at
slot 8..F** — that explains the "empty" 0xC halfword in the frame map while
`&dbl + 0xC` keeps the OOB `addi r28,r1,8` base materialization:

```c
extern char lbl_8029FD38[];
s32 fn_8009CFB8(s32);
void fn_8009D354(void *, s32);
void fn_8009D020(void);

void fn_8019D3E0(void *arg0, s32 arg1) {
    f64 dbl;
    s32 sp10;
    s32 v;

    *(s32 *)((char *)&dbl + 0xC) = (s32)lbl_8029FD38;
    v = fn_8009CFB8(0);
    sp10 = v;
    fn_8009D354((void *)v, arg1);
    *(s32 *)((char *)&dbl + 0xC) = (s32)lbl_8029FD38;
    fn_8009D020();
    __asm__("" : : "m"(dbl), "m"(sp10));
}
```

Generalizable: for odd frame maps with unexplained holes, an f64 anchor models
"empty" inter-slot halfwords while preserving OOB base adds; volatile pads are
useless here (volatiles sort LOW); end-of-function `"m"` pins are what decide
the layout.

---

# ORIGINAL ANALYSIS (historical)

**Status: STRUCTURE SOLVED — body 100% masked, parked on a +8 frame-size
quirk.** The m2c reconstruction is byte-exact for the whole body; the only
unmasked diffs are the 6 frame instructions (0x20 vs 0x18). Best reachable:
95.24% (frame fixed, bases displaced — see below).

## The function

fn_802334D4 (168B, region 0x80233xxx, sibling of fn_8019CF2C /
fn_8019D3E0). It writes two stack slots, dispatches on a magic field of
`arg0`, then calls fn_8019D3E0 with `(slot, 0|1)` and restores one slot. Want opens with a 0x20 frame, saves registers r30 onward at offsets 0x18/0x1C plus the link register, materialises one base as the stack pointer plus 8 (held in r30, addressing the slot at r1+0x14 via displacement 0xC) and a second base as the stack pointer plus 0xC (held in r10, addressing the slot at r1+0x10 via displacement 4).

## The blocker: +8 frame headroom for OOB slots

The m2c model that reproduces the body byte-exactly is **two s32 locals with
out-of-bounds accesses**:

```c
s32 spC;
s32 sp8;
*(s32 *)((char *)&sp8 + 0xC) = (s32)lbl_8029FC18;   /* -> r1+0x14 */
*(s32 *)((char *)&spC + 0x4) = fn_8019CF2C(0);      /* -> r1+0x10 */
```

The two accessed slots live at r1+0x10/0x14 — **8 bytes above** the two
declared locals (r1+8/0xC). The game's build allocated **16 bytes** of local
frame (0x20 total) so the OOB slots land inside the local area and the saves
go at 0x18/0x1C. Our ngccc (all ProDG versions 3.5–3.9.3, identical) packs
the two locals into 8 bytes, keeps frame 0x18, and places the saves at
0x10/0x14 — **overlapping** the OOB slot accesses. Because the accesses are
out-of-bounds, GCC 2.95 does not fold them (good — that is what forces the
`r1+8` / `r1+0xC` base materialization) but also does not reserve the space.

## What was tried (all fail to satisfy both frame AND bases)

- **m2c model (`s32 spC; s32 sp8;` + OOB casts)** — body 100% masked, frame
  0x18 (saves overlap the slots). Best *body* candidate, in the draft.
- **Volatile pads** (`volatile s32 pad0, pad1;` first/last, all declaration
  orders) — GCC always places volatile pads at the LOW slots (r1+8/0xC),
  pushing sp8/spC to 0x10/0x14; frame 0x20 but base `addi` values become
  0x10/0x14 instead of 8/0xC → 95.24%.
- **16-byte array / `s32 spC[2]`** — folded, 8-aligned, or eliminated
  entirely (dead stores).
- **16-byte struct with member-address arithmetic** — members fold to
  direct r1-relative accesses; base materialization lost.
- **Union with `volatile double` dummy** — folds.
- **`volatile double _dummy`** (Issue-01 recipe) — always lands at the
  bottom, displacing the bases by 8.
- **`__attribute__((used))` pads** — ignored for locals.
- **`(void)&var` keep-alive casts** — eliminated.
- **Declaration-order permutation** — every order fails the same way.
- **Compiler flags** — `-fno-schedule-insns{,2}`, `-fno-gcse`,
  `-fno-peephole`, `-fno-strength-reduce`, `-fno-omit-frame-pointer`,
  `-O1`, `-Os`: none change the 0x18 frame.
- **All ProDG versions (3.5 / 3.5b140 / 3.7 / 3.8.1 / 3.9.3)** — identical
  output for this shape.

## Root cause classification

The game's build reserved +8 headroom for OOB-slot functions (the same class
of compiler difference as Issue 01's FPR-frame quirk, but in the opposite
direction: this one allocates *more* local space than ngccc, where Issue 01
needs a dummy to add space). No source-level recipe found that keeps the OOB
base materialization AND forces the extra 8 bytes without displacing the
bases.

## Where to look

- Draft: `src/wip/fn_802334D4.c` (m2c model, body 100% masked).
- Iteration harness: `tmp_iter.py <addr> tmp_cand.c` (compile + masked diff).
- Sibling with the same pattern and same +8 quirk: `fn_8019D3E0` (frame
  0x28 vs 0x20) — also unpromoted.
- Related: `docs/parkings/solved/01-fpr-frame-quirk.md` (the +8 dummy
  recipe), `docs/parkings/05-m2c-corrupt-draft.md` (frame-vs-locals class).
