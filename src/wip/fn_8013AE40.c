// PARKED 2026-10-03 (b72/0x8013AE40): DIFF 4.80% (m2c baseline was DIFF 7.1%),
// compiled .text = 500B vs want 504B (125 of 126 instructions; 1 word SHORT).
//   Reproduce:
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x8013AE40
//
// The pct went DOWN for the length-500 body vs the length-504 variant below
// (14.29%) purely because of the strictly-positional scorer (BRIEF "THE BIG
// ONE") — this body is the more instruction-faithful of the two.
//
// WHAT THE WANT IS (re-derived from the disassembly, not from m2c):
//   * arg0 in r24, arg1 in r26; `Ctx ctx` (0x10B) at r1+8 and `S s` (0xA4B) at
//     r1+0x18 → frame 0xe8, `stmw r22,0xc0`, LR 0xec.  The frame is only
//     reachable if the local S is a ~0xA4-byte aggregate (fn_80138038 writes
//     S+0xa0 and treats r3 as a 0xa4-byte object); m2c's `Unk_59AB5482` (0x40)
//     gives frame 0x78 and every offset after it shifts.
//   * `Ctx *c = &ctx;` (r29) — with r1-relative stores GCC keeps &ctx OUT of a
//     register and the register assignment cascades; the named pointer fixes
//     r29 and lifts the score 4.8 -> 14.3 (see variant note below).
//   * fn_80138038(&s, arg1) — 2 args, r4 is the raw incoming r4 (m2c passed
//     &ctx).  Declaring every callee is mandatory: undeclared → `crclr cr1eq`
//     before each `bl` plus a self-relative `bl` for fn_80138038.
//   * Outer walk `while (i <= 0xff)` over `p = arg1 + 0x884, p += 0x18`
//     (i++ emitted BEFORE p += 0x18 in the latch, so the two increments are
//     written `p += 0x18; i++;` at the end of the body).
//   * Per outer step: `n = p->fC; c->f4 = (s32)p; m = (n->f4 == -1) ? 0 : n;
//     c->f4 = (s32)m; o = m ? (Obj*)m->f4 : 0;` — the TERNARY form is what
//     emits the want's `mr r11,r9` phi copy; `m = n; if (n->f4 == -1) m = 0;`
//     coalesces the two variables and loses that word (measured).
//   * Inner `for(;;)`: `n = ((Obj *)c->f4)->fC; if (n->f4 == -1) n = 0;
//     c->f4 = (s32)n; o2 = n ? (Obj*)n->f4 : 0;` — SINGLE variable here (the
//     want has no `mr` in the inner head).  It re-reads `c->f4` from memory
//     every iteration because the store to c->f4 may alias (no strict aliasing).
//   * `lbl_80303450 == o->f24` guard has `beq` polarity (skip the store) —
//     m2c's `if (a != b) a = b;` gives `bne`, i.e. backwards.
//   * obj fields: f19 = u8 (lbz + slwi 2, m2c's `*(s32*)(..+0x19)*4` gave
//     `lwz`+`slwi 4`), f24 = s32 (`cmpw`), f2C = pointer to `{u8;u16;s32}`,
//     vt->f8 = s16 (`lha`), and s.f8 is an **s32** field fed by a `(u16)` cast
//     (a u16 field makes ngccc emit `sth`, the want stores a word).
//   * fn_80137FEC(o->f2C, 3) takes TWO args (m2c's 1-arg call is flat wrong);
//     vcall is `mtlr`+`blrl` through `vt->fC`.
//   * `res` handling is m2c's block_20/block_21 shape and IS correct:
//     `if (res != 5) { if (res != 3) {37FEC; vcall;} goto b20; } ... b20:
//      if (res == 3) {b21: return 0;} if (res != 1) return 1; o = o2; ...`
//
// REMAINING RESIDUAL (block layout + register colouring; content is otherwise
// line-for-line):
//   1. 1 word SHORT: the want's prologue does `addi r9,r1,8` for the two entry
//      stores and THEN `mr r29,r9`; ngccc folds mine into `addi r29,r1,8`.
//      RE-CONFIRMED and EXTENDED 2026-10-05 (w2_8013AE40).  The SAME two-pointer
//      recipe that took 0x8018C080 from 2.7% to 51.9% (see that file's header:
//      a second named pointer plus an explicit ASSIGNMENT copy whose live
//      ranges overlap) was tried here in 11 spellings and NONE produced the
//      `mr` -- every one is still 500B / 4.76%:
//        * `Ctx *c, *cp = &ctx;` + `c = cp;` as the first statement (the exact
//          8018C080 shape) -- folded;
//        * the copy BEFORE / AFTER the two prologue stores, both orders;
//        * swapping which pointer feeds the prologue stores vs the loop body
//          (`c` short-lived, `cp` long-lived and vice versa);
//        * routing the copy through a `char *` bridge (`cb = (char*)&ctx;
//          c = (Ctx*)cb;`) so CSE cannot fold the types -- folded;
//        * routing the prologue STORES through the `char *` instead;
//        * declaring both pointers with no initialiser and assigning both late.
//      So the 8018C080 fix is NOT a general recipe: it works there because
//      `&sp8` is passed to TWO different callees, which genuinely splits the
//      live ranges across calls.  Here `&ctx` is never passed to any call
//      (verified: the want's only `mr r4,r22` arg is `&s`, the OTHER local),
//      so both spellings of "&ctx" have identical, fully-overlapping ranges and
//      ngccc coalesces them unconditionally.  Getting the extra `mr` here needs
//      the block LAYOUT (item 4) fixed first, not another pointer.
//   2. `tab`: want materialises `addi r10, r26, 0x480` inside the inner body
//      and uses `lwzx`; mine strength-reduces to `add r11,r11,r28` +
//      `lwz r9,0x480(r11)`.  Same length, different form (recipes §6q-3 /
//      "Base-pointer indexed load" wants a named base var — but a named
//      `s32 *tab` is hoisted out of the loop into a callee-saved reg AND
//      pushes the frame to 0xf0/stmw r21: measured, both worse).
//   3. GCC emits a 2-word dead-store block (`stw r11,0(r9); b ...`) for the
//      `c->f4 = (s32)p` store that the want keeps in place at `stw r27,4(r29)`.
//   4. Block ORDER: the want lays out outer-head → const-hoist → inner-head →
//      compare → found arm → res blocks → not-found arm → latch; mine puts the
//      inner head after the found arm.  Not controllable from C so far.
//   5. Register numbers differ throughout (mine p=r26/arg1=r28, want
//      p=r27/arg1=r26) — pure colouring after the tab/&ctx decisions above.
//
// VARIANT WORTH RE-TRYING (2-line change): using the TERNARY form in the INNER
// loop too (i.e. a second variable `m2`) gives exactly 504B (length-exact)
// and scores DIFF 14.29%, but carries one spurious `mr r11,r9` in the inner
// head that the want does not have.  Pick length-exact (14.29%) or
// instruction-faithful (4.80%) deliberately.
//
// RULED OUT (don't re-try):
//   * `Unk_59AB5482`-sized ctx (m2c) — wrong frame (0x78) and every offset.
//   * `m = n; if (...) m = NULL;` init-then-if — coalesces m/n, loses `mr`.
//   * Named `s32 *tab` inside the loop — hoisted to the outer preheader AND
//     costs a register: frame becomes 0xf0 / `stmw r21,0xc4`, 492B.
//   * `if (lbl_80303450 != v) lbl_80303450 = v;` — wrong `bne` polarity.
//   * u16 `s.f8` field — emits `sth`, want stores a word.
//   * `for (i = 0; i <= 0xff; i++)` with `p += 0x18` as the last statement —
//     emits `p += 0x18` BEFORE `i++` in the latch; the `while` form with
//     `p += 0x18; i++;` fixes the order.
//   * Declaring `typedef struct X X;` twice (once as a forward typedef, once
//     with the body) — ngccc rejects the redefinition; use
//     `typedef struct X X;` + `struct X {...};`.
//
// WIP DRAFT (non-matching) — C body generated by tools/fill_wip_drafts.py
// family=m2c range=0x8013AE40-0x8013B038 size=504B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// Body rewritten by hand from the want's disassembly (b72, 2026-10-03).
#include "types.h"

extern char lbl_8029F3C8[];
extern s32 lbl_80303450;

typedef struct Obj Obj;
typedef struct Vt Vt;
struct Rec {
    u8 f0;
    u8 f1;
    u16 f2;
    s32 f4;
};
typedef struct Rec Rec;


struct Vt {
    s32 f0;
    s32 f4;
    s16 f8;
    s16 fA;
    s32 fC;
} ;
struct Obj {
    s32 f0;
    s32 f4;
    s32 f8;
    Obj *fC;
    Obj *f10;
    Vt *vt;
    u8 f18;
    u8 f19;
    u8 f1A;
    u8 f1B;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    Rec *f2C;
} ;
typedef struct Ctx {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
} Ctx;

typedef struct S {
    s32 f0;
    u8 f4;
    u8 f5[3];
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    u8 f18[0x88];
    s32 fA0;
} S;

void fn_80138038(S *s, s32 a);
s32 fn_801399D8(s32 base, S *s);
void fn_80137FEC(Rec *p, s32 flags);

s32 fn_8013AE40(s32 arg0, s32 arg1) {
    Ctx ctx;
    Ctx *c;
    S s;
    s32 i;
    Obj *p;
    Obj *n;
    Obj *o;
    Obj *m;
    Obj *o2;
    Vt *vt;
    s32 res;

    c = &ctx;
    c->f8 = (s32)lbl_8029F3C8;
    c->f4 = 0;

    fn_80138038(&s, arg1);

    i = 0;
    p = (Obj *)(arg1 + 0x884);
    while (i <= 0xff) {
        n = p->fC;
        c->f4 = (s32)p;
        m = (n->f4 == -1) ? NULL : n;
        c->f4 = (s32)m;
        o = m ? (Obj *)m->f4 : NULL;
        if (o == NULL) {
            continue;
        }
        for (;;) {
            n = ((Obj *)c->f4)->fC;
            if (n->f4 == -1) {
                n = NULL;
            }
            c->f4 = (s32)n;
            o2 = n ? (Obj *)n->f4 : NULL;
            if (o->f24 != ((s32 *)((char *)arg1 + 0x480))[o->f19]) {
                if (lbl_80303450 == o->f24) {
                    break;
                }
                lbl_80303450 = o->f24;
                break;
            }
            s.f10 = arg1;
            s.f0 = 0;
            if (o->f2C->f4 != 0) {
                s.f0 = o->f2C->f4;
            }
            s.f14 = 0;
            s.fC = arg0;
            s.f4 = (u8)o->f2C->f0;
            s.f8 = (u16)o->f2C->f2;
            ((s32 *)((char *)arg1 + 0x480))[o->f19] += 1;
            res = fn_801399D8(arg0 + 4, &s);
            if (res != 5) {
                if (res != 3) {
                    fn_80137FEC(o->f2C, 3);
                    if (o != NULL) {
                        vt = o->vt;
                        ((void (*)(void *, s32))vt->fC)((char *)o + vt->f8, 3);
                    }
                    goto block_20;
                }
                goto block_21;
            }
block_20:
            if (res == 3) {
block_21:
                c->f8 = (s32)lbl_8029F3C8;
                return 0;
            }
            if (res != 1) {
                c->f8 = (s32)lbl_8029F3C8;
                return 1;
            }
            o = o2;
            if (o != NULL) {
                continue;
            }
            break;
        }
        p = (Obj *)((char *)p + 0x18);
        i++;
    }
    c->f8 = (s32)lbl_8029F3C8;
    return 1;
}
