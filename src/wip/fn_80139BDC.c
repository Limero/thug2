// WIP DRAFT (non-matching) — C body reconstructed from the want disassembly
// 2026-10-08: reload_pin_sweep WIN — pin `p2` -> `register ... p2 __asm__("r0")` => official 53.0% (sweep base 24.62%). ONE pin only; pins are not additive.
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 2.5253% -> 24.2424% per-object flags: -Os -> -fno-rerun-cse-after-loop
// family=m2c range=0x80139BDC-0x80139EF4 size=792B
//
// PARSED 2026-10-04: 712B (m2c baseline, DIFF 5.1%) -> 780B object, i.e. 3 words
// SHORT of the 792B want. Frame 0x48, `stmw r26, 0x30(r1)`, `stw r0,0x4c(r1)`
// and both 45-word loop bodies + the 12-word epilogue are now structurally
// byte-equivalent to the want; every semantic reconstruction below is verified
// (u16 key compare, s16 vtable offset, 2-arg release helpers, unsigned tail
// compares, 16-byte iterator slots at sp+8/sp+0x18, dead store at sp+0x28).
// => The masked % is meaningless at this size (AGENTS §6cs-1); report the size.
//
// PARKED — remaining blocker is 3 want-EXTRA words that stock ngccc deletes:
//
//  (1) TWO preheaders, 1 word each. want advances the cursor with a *rotated*
//      diamond that keeps a provably-dead `li`:
//          cmpwi rX,0 ; bne L ; li rX,0 ; b J ; L: lwz rX,4(rX) ; J: or. rY,rX,rX
//      At every -O level ngccc's simplify_cond folds that to
//      `beq J ; lwz rX,4(rX) ; J:` (or rotates the `li rX,0` arm out of line
//      and shares it with the loop body, costing a further word). The `li` is
//      unreachable-by-construction (it only runs when rX is already 0), so no C
//      spelling resurrects it. This is docs/parkings/33's "root asymmetry": the
//      retail bytes come from an inlined C++ iterator helper expanded before
//      jump-threading. The promoted twins fn_8013F980 / fn_8013FC10 reproduced
//      exactly this arm with `__asm__("li %0,0")` / `__asm__("lwz %0,4(%0)")`
//      — banned for this draft.
//
//  (2) Prologue, 1 word: want materialises `&it1` TWICE — `addi r9,r1,8` for the
//      two preheader slot stores plus `mr r28,r9` for the loop + final store.
//      One C pointer variable gives one web (ngccc CSEs the second `&a`); two
//      C variables also CSE. Same inlined-`this` origin; the twins needed
//      `__asm__("mr %0,%1")` for it too.
//
// MEASURED / NEGATIVE RESULTS (all with `// FLAG: -Os`, LEAF_TMPDIR=<scratch>):
//  * -O0 1456B | -O1 780B | -O2 780B | -O3 780B | -Os 780B
//  * -fno-schedule-insns 776B (worse); -fno-schedule-insns2 / -fno-thread-jumps /
//    -fno-gcse / -fno-expensive-optimizations / -fno-delayed-branch / -fno-tree-pre
//    all no-ops at 780B. (-fno-crossjumping / -fno-if-conversion: option unknown.)
//  * ProDG 3.5 / 3.5b140 / 3.7 / 3.8.1 / 3.9.3 -> all 780B (codegen-identical).
//  * 5 semantically distinct spellings of the preheader advance
//    (separate `cur`; in-place then `cur = e`; `nx` then `cur = nx`;
//    `nx = 0; if (e) nx = e->f4; cur = nx`; m2c ternary) -> 780 / 772 / 772 /
//    772 B. The 780B form is the one kept.
//  * Two C pointer variables for `&it1` (preheader vs loop+final) -> still 780B
//    (CSE'd into one web).
//
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"

typedef struct Vt { char pad0[8]; s16 f8; char padA[2]; void (*fC)(void *, s32); } Vt;
typedef struct Key { u16 f0; char pad2[2]; } Key;
typedef struct Cnt { s32 pad; s32 cnt; } Cnt;
typedef struct RC1 { char pad0[8]; Cnt sub; } RC1;
typedef struct RC2 { char pad0[0xC]; Cnt sub; } RC2;

typedef struct N1 {
    char pad00[0x14];
    Vt *f14;
    s32 f18;
    RC1 *f1C;
    char pad20[2];
    u16 f22;
} N1;

typedef struct N2 {
    char pad00[0x14];
    Vt *f14;
    char pad18[6];
    u16 f1E;
    s32 f20;
    char pad24[8];
    RC2 *f2C;
} N2;

typedef struct E1 { s32 f0; N1 *f4; s32 f8; struct E1 *fC; } E1;
typedef struct E2 { s32 f0; N2 *f4; s32 f8; struct E2 *fC; } E2;

typedef struct Obj {
    char pad00[0x18];
    E1 e18;
    char pad28[8];
    E2 e30;
    char pad40[0x28];
    s32 f68;
    char pad6C[0x2048];
    u32 f20B4;
} Obj;

typedef struct A0 {
    Key *f0;
    s32 f4;
    s32 f8;
    s32 *fC;
    Obj *f10;
    s32 f14;
} A0;

typedef struct It1 { s32 f0; E1 * volatile f4; void * volatile f8; s32 fC; } It1;
typedef struct It2 { s32 f0; E2 * volatile f4; void * volatile f8; s32 fC; } It2;

extern char lbl_8029F3E0[];
extern char lbl_8029F3C8[];
extern u32 lbl_8029F3F8;

s32 fn_80137EE4(RC1 *a, s32 b);
s32 fn_80137FEC(RC2 *a, s32 b);
s32 fn_8013F764(Obj *a);
s32 fn_8013F74C(Obj *a);
void fn_8013B6F4(u32 *a, u32 b);
// FLAG: -fno-rerun-cse-after-loop

s32 fn_80139BDC(A0 *arg0) {
    It1 a;
    It2 b;
    volatile s32 f28;
    u32 var_r26;
    u32 rem;
    u32 lim;
    s32 flag;
    Obj *obj;
    Key *key = arg0->f0;
    It1 *pa = &a;
    It2 *pb = &b;
    N1 *cur1;
    N1 *nxt1;
    E1 *e1;
    E1 *p1;
    N2 *cur2;
    N2 *nxt2;
    E2 *e2;
    register E2 *p2 __asm__("r0");
    RC1 *rc1;
    RC2 *rc2;
    Cnt *cp1;
    Cnt *cp2;
    Vt *v1;
    Vt *v2;
    s32 t;

    pa->f8 = lbl_8029F3E0;
    pa->f4 = 0;
    b.f8 = lbl_8029F3C8;
    var_r26 = 0;
    pb->f4 = 0;
    arg0->f8 = 2;
    if (arg0->f14 & 1) {
        pa->f8 = lbl_8029F3E0;
        b.f8 = lbl_8029F3C8;
        return 4;
    }

    p1 = &arg0->f10->e18;
    pa->f4 = p1;
    e1 = p1->fC;
    if (e1->f4 == (N1 *)-1) {
        e1 = NULL;
    }
    pa->f4 = e1;
    if (e1 != NULL) {
        cur1 = e1->f4;
    } else {
        cur1 = NULL;
    }
    if (cur1 != NULL) {
        do {
            e1 = pa->f4->fC;
            if (e1->f4 == (N1 *)-1) {
                e1 = NULL;
            }
            pa->f4 = e1;
            if (e1 != NULL) {
                nxt1 = e1->f4;
            } else {
                nxt1 = NULL;
            }
            if (key->f0 == cur1->f22 && cur1->f18 != 0) {
                rc1 = cur1->f1C;
                cp1 = &rc1->sub;
                t = 1;
                cp1->cnt -= 1;
                if (cp1->cnt == 0) {
                    t = 0;
                }
                if (t == 0 && rc1 != NULL) {
                    fn_80137EE4(rc1, 3);
                }
                var_r26 = cur1->f18;
                if (cur1 != NULL) {
                    v1 = cur1->f14;
                    v1->fC((char *)cur1 + v1->f8, 3);
                }
            }
            cur1 = nxt1;
        } while (cur1 != NULL);
    }

    p2 = &arg0->f10->e30;
    b.f4 = p2;
    e2 = p2->fC;
    if (e2->f4 == (N2 *)-1) {
        e2 = NULL;
    }
    b.f4 = e2;
    if (e2 != NULL) {
        cur2 = e2->f4;
    } else {
        cur2 = NULL;
    }
    if (cur2 != NULL) {
        do {
            e2 = b.f4->fC;
            if (e2->f4 == (N2 *)-1) {
                e2 = NULL;
            }
            b.f4 = e2;
            if (e2 != NULL) {
                nxt2 = e2->f4;
            } else {
                nxt2 = NULL;
            }
            if (key->f0 == cur2->f1E && cur2->f20 != 0) {
                rc2 = cur2->f2C;
                cp2 = &rc2->sub;
                t = 1;
                cp2->cnt -= 1;
                if (cp2->cnt == 0) {
                    t = 0;
                }
                if (t == 0 && rc2 != NULL) {
                    fn_80137FEC(rc2, 3);
                }
                var_r26 = cur2->f20;
                if (cur2 != NULL) {
                    v2 = cur2->f14;
                    v2->fC((char *)cur2 + v2->f8, 3);
                }
            }
            cur2 = nxt2;
        } while (cur2 != NULL);
    }

    if (fn_8013F764(arg0->f10) != 0) {
        obj = arg0->f10;
        f28 = 1;
        flag = 1;
        if (!(obj->f68 & 1)) {
            flag = 0;
        }
        if (flag != 0 && var_r26 != 0) {
            rem = *arg0->fC - var_r26;
            lim = 0;
            if (fn_8013F74C(obj) == 0) {
                lim = obj->f20B4;
            }
            if (rem > lim) {
                if (rem > lbl_8029F3F8) {
                    rem = lbl_8029F3F8;
                }
                fn_8013B6F4(&arg0->f10->f20B4, rem);
            }
        }
    }
    pa->f8 = lbl_8029F3E0;
    b.f8 = lbl_8029F3C8;
    return 1;
}
