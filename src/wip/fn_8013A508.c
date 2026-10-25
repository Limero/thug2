// PARKED: NEAR 95.2%, size-exact 500B, 6 words off. The prologue and frame are
// byte-exact: frame 0x40, stmw r25, `&ctx` born in the r9 scratch (its two
// early stores go through it) and copied to the r25 home by `mr r25, r9`, all
// later uses through r25.
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x8013A508
//
// REMAINING 6 WORDS, two independent scheduler ties (the 5! order of the obj
// field stores was brute forced; 2026-10-22: the third tie is fixed):
//   a) 0x540-0x54C: want loads arg0->f10 before arg0->f0 and computes the table
//      base before the first byte load; got reverses both (4 words).
//   b) 0x600/0x610: obj->f1C (zero) and obj->f24 (val) are emitted in the other
//      order (2 words).//   c) 0x630 FIXED: the head-pointer add is a commutative `add` whose operand
//     order follows the C expression. Writing `ix + (s32)arg0->f10` (integer
//     first) instead of the pointer-plus-int form emits `add r3,r0,r9`.
//     Was 1 word; 94.4% -> 95.2%.
//
// LEVERS THAT ARE LOAD-BEARING (all measured; keep them):
//  0. The `&ctx` home is TWO pointers: a short-lived scratch pinned to r9 and
//     an unpinned home (`q`, then `c = q` after the two stores; the allocator
//     gives c r25). One pointer only, pinned to a caller-saved register (r5),
//     rematerialises the address after every call and shrinks the frame to
//     0x38/stmw r26 (74.4%). Pinning the home to r25 is neutral-to-worse once
//     the scratch pin is in place only if the copy is missing; with the copy
//     it is identical, so leave the home free.
//  1. The want's scaled-index opcode is `rlwinm r0,r0,2,0x16,0x1d`
//     (= (idx<<2) & 0x3FC, the byte*4 identity), NOT `slwi`.  It only appears
//     when the index goes through a *signed* byte + an unsigned cast:
//         s8 idx;  ... idx = p[0];  lim = tab[(u8)idx];
//     Every unsigned spelling (`u8 idx; tab[idx]`, `tab[idx & 0xff]`,
//     `(u8)idx` on a u8, u16/u32/int intermediates) folds to `slwi` because
//     ngccc range-propagates the lbz.  See recipes "masked-byte-index".
//     The sp18 store must read the *byte* (`sp18 = p[0];`), not `idx`: storing
//     the signed local emits an extra `extsb r0,r0` before the `stb`, which
//     the want does not have and which shifted every following word.
//  2. The p-walk: write it as `p++; val = *(s32*)p; p += 4;` (a SEPARATE
//     `p += 4` statement) and later `sp19 = *p; p++; p6 = p;`.  That reproduces
//     the want's `lwzu r28,1(r31)` + `addi r31,r31,4` (advance the walk pointer
//     to p+5 up front) instead of ngccc CSEing `p+5` into `addi r30,r28,5`.
//     This fixed the 8-byte length gap (492B -> 500B).
//  3. The three values that used to share one `val` local MUST be three
//     separate locals or the register allocation collapses (frame went 0x38,
//     stmw r26 instead of 0x40/stmw r25, and the object's key field got the
//     TRUNCATED u16 instead of the loaded s32):
//         val  = *(s32 *)p;              // survives to obj->key / obj->f24
//         slen = (u16)(arg0->fA - 6);    // call arg r5
//         cval = fn_80137F30(...);       // call arg r4 of fn_80137BD8
//     `obj->key = val;` really is the *buffer* value (want `stw r28,8(r31)`).
//  4. The bucket head is built in TWO statements on the same variable:
//         head = (Node *)((char *)arg0->f10 + ix);
//         head = (Node *)((char *)head + 0x884);
//     One fused expression makes the sum reuse the f10 register as the add's
//     destination and adds an extra move in front of the `addi` (93.6%, 2
//     words); the split form gives the want's `add r3,..` / `addi r3,r3,..`.
//     The `ix` local (`sp18 * 0x18`) must stay a named temp: inlined, the two
//     loads feeding it swap registers and the mul lands in the wrong one.
//
// WHAT THE WANT IS (re-derived from the disasm, not from m2c) — unchanged:
//   * arg0: {+0 ptr, +0xA u16, +0x10 base, +0xA0 flag}; `arg0->fA0 = 1`.
//   * stack Ctx at r1+8: +4 = 0, +8 = lbl_8029F350 (.rodata2 class ptr);
//     written once at entry and re-stored at all three exits.
//   * sp18/sp19 = two byte stack slots at 0x18/0x19, stored then RELOADED
//     (4x and 1x) — stack-resident, not registers.  `volatile` is what makes
//     them stack slots AND the reloads; a non-volatile u8 gets a register and
//     the frame loses 8 bytes (see RULED OUT).
//   * p = arg0->+0; tab = (s32*)(arg0->+0x10 + 0x480); lim = tab[byte];
//     p++ -> `lwzu` (the `p++` is load-bearing).
//   * Mem_Alloc2(0x14) result is arg0 of fn_80137F30(t1, sp19, slen, p6, sp18, 0)
//     (6 args, r3 from the alloc); Mem_NewZero(0x30) result is arg0 of
//     fn_80137BD8(t2, cval).
//   * fn_8000F2F8 / fn_8000F320 must re-READ `*(void**)lbl_8029FE98` at each
//     site (assigning it to a local makes GCC CSE it into a callee-saved reg).
//   * loop = find-or-insert into a sorted doubly-linked list whose `f4 == -1`
//     is the end sentinel; head = base + 0x884 + sp18*0x18; insert-at-head is
//     the loop's natural exit (`break`), the other two arms are `goto done`.
//   * `if (res == 0) {...; return 4;} ... return 1;`
//   * fn_80137FEC(ptr, flags) takes TWO args — it is fn_80137FEC(obj->f2C, 3).
//
// REMAINING RESIDUAL (after the extsb, all register assignment / scheduler
// order; the opcode stream is line-for-line the same):
//   * prologue: the original loads a page high half into r11, builds the
//     context address into the r9 temp off the stack pointer plus 8, and
//     derives r10 off r11 minus 0xcb0, then copies r3 to r27, stores r10
//     through r9 at offset 8, zeroes r26 and stores it through r9 at offset 4,
//     and copies r9 to r25 —
//     i.e. &ctx is materialized into a TEMP (r9) and only then copied into the
//     callee-saved r25.  got allocates &ctx straight into r26 and the constant
//     0 into r25 (the two callee-saved values are swapped) and hoists the
//     arg0->fA0 store.  The `mr r25,r9` accounts for the word that the missing
//     extsb frees, so this and the extsb are one combined residual.
//   * post-fn_80137BD8 stores: want [f1C, key, f20, (lbz), f24, f19] vs got
//     [key, f19, f1C, f24, f20, (lbz)] (same statements, same source order).
//   * insert-before block: the original loads the word at offset 0x10 through
//     r11 into r0, loads 1 into r10, stores r11 at offset 0xc off r31 and
//     stores r0 at offset 0x10 off r31, while this draft stores r11 at offset
//     0xc off r30 first, loads 1 into r10, reloads the word at offset 0x10
//     through r11, and stores it at offset 0x10 off r30 — the loop's obj
//     register is r31 in the original and r30 here.
//
// RULED OUT (don't re-try):
//   * Non-volatile `u8 sp18/sp19`: GCC keeps them in callee-saved regs, the
//     stack slots at 0x18/0x19 are never allocated, and the frame drops to
//     0x38 / stmw 0x1c (8 bytes short).  `volatile` reproduces the want's
//     store-then-reload exactly and fixes the frame; a separate non-volatile
//     `u8 idx` is needed so the table index reuses the register.
//   * Removing the `p6` local / inlining `p + 6`: frees a callee-saved reg,
//     same 8-byte frame loss as above.
//   * `break` for the `cur == 0` arm: puts the insert-at-head block *inside*
//     the loop and misplaces both other exit blocks.
//   * Writing `arg0->fA0 = 1` between the two Ctx stores to force the want's
//     f8/A0/f4 emission order — the scheduler re-hoists it either way.
//   * `u8 idx` + `tab[idx]` / `tab[(u8)idx]` / `tab[idx & 0xff]` and every
//     unsigned intermediate (u16/u32/int, address-taken non-volatile slot,
//     bitfield-8, s8* pointer, `(s8)` round trip): all give `slwi`, no mask.
//     `s8 idx` variants that store the signed value give mask + extsb.
//   * Flag variants: -O1/-O3/-Os, -fno-rerun-cse-after-loop,
//     -fno-schedule-insns{,2}, -fno-strength-reduce,
//     -fno-expensive-optimizations, -fno-regmove, -fno-peephole,
//     -fno-cse-follow-jumps, -fno-cse-skip-blocks, -fno-inline, -fno-defer-pop
//     — none change the mask/extsb pair.
//
// WIP DRAFT (non-matching) — C body generated by tools/fill_wip_drafts.py
// family=m2c range=0x8013A508-0x8013A6FC size=500B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// Body rewritten by hand from the want's disassembly (b44, 2026-10-03).
#include "types.h"
#include "structs.h"
#include "mem.h"

extern char lbl_8029F350[];
extern void *lbl_8029FE98[];

typedef struct Node Node;

typedef struct Arg0 {
    u8 *f0;
    char pad0x4[0x6];
    u16 fA;
    char pad0xC[0x4];
    u32 f10;
    char pad0x14[0x8C];
    s32 fA0;
} Arg0;

typedef struct Vt {
    s32 f0;
    s32 f4;
    s16 f8;
    s16 fA;
    s32 fC;
} Vt;

typedef struct Obj {
    char pad0x0[0x8];
    s32 key;
    Node *next;
    Node *prev;
    Vt *vt;
    u8 f18;
    u8 f19;
    u8 f1A;
    u8 f1B;
    s32 f1C;
    s32 f20;
    s32 f24;
    char pad0x28[0x4];
    s32 f2C;
} Obj;

struct Node {
    char pad0x0[0x4];
    s32 f4;
    s32 key;
    Node *next;
    Node *prev;
};

typedef struct Ctx {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
} Ctx;

void *Mem_NewZero(s32 size);
s32 fn_80137F30(void *, u8, u16, void *, u8, s32);
Obj *fn_80137BD8(void *, s32);
void fn_80137FEC(void *, s32);
void fn_8000F2F8(void *, s32);
void fn_8000F320(void *);

s32 fn_8013A508(Arg0 *arg0) {
    Ctx ctx;
    volatile u8 sp18;
    volatile u8 sp19;
    s8 idx;
    register Ctx *q __asm__("r9");
    Ctx *c;
    u8 *p;
    u8 *p6;
    Node *head;
    Node *cur;
    Node *nx;
    Obj *obj;
    Vt *vt;
    s32 *tab;
    s32 lim;
    s32 val;
    u16 slen;
    s32 cval;
    s32 key;
    s32 res;
    void *t1;
    Node *pv;
    void *t2;

    q = &ctx;
    q->f8 = (s32)lbl_8029F350;
    arg0->fA0 = 1;
    q->f4 = 0;
    c = q;

    p = arg0->f0;
    tab = (s32 *)((char *)arg0->f10 + 0x480);
    idx = p[0];
    sp18 = p[0];
    lim = tab[(u8)idx];
    p++;
    val = *(s32 *)p;
    p += 4;
    if ((u32)val < (u32)lim) {
        c->f8 = (s32)lbl_8029F350;
        return 1;
    }

    fn_8000F2F8(*(Unk_FFAD6788 **)lbl_8029FE98,
                (*(Unk_FFAD6788 **)lbl_8029FE98)->unk0x134);

    sp19 = *p;
    p++;
    p6 = p;
    slen = (u16)(arg0->fA - 6);
    t1 = Mem_Alloc2(0x14);
    cval = fn_80137F30(t1, sp19, slen, p6, sp18, 0);
    t2 = Mem_NewZero(0x30);
    obj = fn_80137BD8(t2, cval);

    obj->key = val;
    obj->f20 = 0;
    obj->f24 = val;
    obj->f19 = sp18;
    obj->f1C = 0;

    fn_8000F320(*(Unk_FFAD6788 **)lbl_8029FE98);

    key = obj->key;
    { s32 ix = sp18 * 0x18; head = (Node *)(ix + (s32)arg0->f10); head = (Node *)((char *)head + 0x884); }
    cur = head;
    for (;;) {
        nx = cur->next;
        if (nx->f4 == -1) {
            cur = 0;
        } else {
            cur = nx;
        }
        if (cur == 0) {
            break;
        }
        if (cur->key == key) {
            res = 0;
            goto done;
        }
        if (cur->key > key) {
            pv = cur->prev;
            obj->next = cur;
            obj->prev = pv;
            cur->prev->next = obj;
            cur->prev = obj;
            res = 1;
            goto done;
        }
    }
    pv = head->prev;
    obj->next = head;
    obj->prev = pv;
    head->prev->next = obj;
    head->prev = obj;
    res = 1;
done:

    if (res == 0) {
        if (obj->f2C != 0) {
            fn_80137FEC(obj->f2C, 3);
        }
        if (obj != 0) {
            vt = obj->vt;
            ((void (*)(void *, s32))vt->fC)((char *)obj + vt->f8, 3);
        }
        c->f8 = (s32)lbl_8029F350;
        return 4;
    }
    c->f8 = (s32)lbl_8029F350;
    return 1;
}
