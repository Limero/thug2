// WIP DRAFT (non-matching) - hand-reconstructed from the want disassembly.
// family=m2c range=0x800768A8-0x80076EEC size=1604B
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// VERDICT: NEAR 66.1% masked, object EXACTLY 1604B (= want size), and every
// hard structural invariant of the want now matches:
//   stwu r1,-0x48(r1) / stmw r21,0x1c(r1) / stw r0,0x4c(r1)  == want, byte-exact
//   callee-saved set = {r21..r31} (11 regs), frame 0x48, LR slot 0x4c
//   .text == 1604B, no private .rodata, 22 REL24 calls in the want's order
//   the E20 byte store is the want's exact 7-instruction shape with ONE `stb`
//     at the merge and `li r0,0xff` materialised INSIDE the taken arm
//   378 of the 401 want words match in (mnemonic, operand-shape) - i.e. the
//     instruction SEQUENCE is right; what is left is register numbering.
//   tools/venv/bin/python tools/want_got.py 0x800768A8
//
// ---------------------------------------------------------------------------
// THIS PASS (61.6% -> 66.1%, and from "wrong frame" to "right frame").
// Four real defects found; all four are worth writing into AGENTS-recipes.md.
//
// (A) The hoisted `li 0xff` is caused by the TEMP VARIABLE, not by the
//     ternary.  Writing
//         f = e20->unk0x5;  e20->unk0x5 = (f & 0x80) ? 0xFF : f << 1;
//     lets ngccc's loop-invariant motion lift the loop-invariant 0xFF into
//     the E20 loop preheader.  A def in the preheader is live across the
//     WHOLE loop body - including the fn_8005D420 call inside it - so the
//     value can no longer live in a caller-saved register: global-alloc
//     gives it a callee-saved one.  That is 12 saved registers instead of
//     11, i.e. a 0x50 frame instead of 0x48, and it also splits the single
//     `stb` into two (one per arm).  Writing the SAME expression directly on
//     the lvalue -
//         e20->unk0x5 = (e20->unk0x5 & 0x80) ? 0xFF : e20->unk0x5 << 1;
//     - reproduces the want exactly: `lbz / andi. / bne / slwi / b /
//     li r0,0xff / stb`.  Reproduced in a 30-line standalone file, so this
//     is a property of the expression, not of this function.
//     NEGATIVE RESULTS (all leave the hoist in place, so this is NOT a
//     flag problem and must be fixed in the source):
//       -fno-loop-invariant-moves  -> cc1: Invalid option (does not exist)
//       -fno-move-all-movables     -> accepted, no effect
//       -fno-gcse                  -> accepted, no effect on the hoist
//       -fno-cse-follow-jumps      -> accepted, no effect on the hoist
//     (`if (g & 0x80) p->f = 0xFF; else p->f = g << 1;` also hoists; a
//     `u8`-typed temp triggers reload's byte-store optimisation instead and
//     turns the shift into `rlwinm r0,r0,1,0x18,0x1e` - both worse.)
//
// (B) ONE counter variable reused by several loops collapses into ONE pseudo.
//     The old body used `u` for the E20 loop, the vertex loop and the
//     node-append loop, and `j` for both the join/attach inner loop and the
//     node-chain walk.  GCC 2.95's life analysis gives a pseudo a single
//     [born, dead] interval, so the gaps do not split it: the merged pseudo
//     is live across every call between the first and last loop, hence
//     callee-saved (one register too many), and it also blocks strength
//     reduction of the vertex loop (`mulli r30,r8,0xc` every iteration
//     instead of `li r30,0` + `addi r30,r30,0xc`).  Giving each loop its own
//     counter (`u` / `uv` / `uw`, `j` / `nc`) is what took the frame from
//     0x50 to 0x48, produced `stmw r21`, and restored the vertex loop's
//     induction variable.  Worth 61.6% -> 70.6% on its own.
//
// (C) `meta->unk0x38 + e20->unk0xc * 0x20` scales the index by sizeof(E20)
//     TWICE in C (once for the `* 0x20`, once for the pointer arithmetic) and
//     compiles to `slwi rN,rN,0xa`.  The want has a single `slwi 5`, so the
//     byte offset has to be formed on a char pointer:
//         (E20 *)((char *)meta->unk0x38 + e20->unk0xc * 0x20)
//     Masked scoring cannot see this at all (same instruction count) - it
//     was silently wrong before this pass.
//
// (D) `(char *)hd + hd->unk0x4 + 0x40` associates as `(hd + unk0x4) + 0x40`
//     and emits `add r9,r23,r9 ; addi r9,r9,0x40`.  The want emits
//     `addi r9,r9,0x40 ; add r9,r23,r9`, i.e. the constant is grouped with
//     the field: `(char *)hd + (hd->unk0x4 + 0x40)`.
//
// ---------------------------------------------------------------------------
// WHY IT IS STILL PARKED - the remaining blocker.
//
// The instruction sequence is now essentially the want's; what is left is
// (1) four register-number choices and (2) one 4-instruction block that is
// emitted in a different order.  Nothing here is a semantics problem any
// more.  Word-level remainder (want-only / got-only, ignoring the
// relocation artifacts `lis r9,0` vs `lis r9,-0x7fd0` which are identical
// once the ADDR16 reloc is applied):
//
//  1. `mr r28, r8` at 0x80076A04 - the want copies the build cursor into a
//     callee-saved register BEFORE `meta->unk0x28 = cur` and computes
//     `hd = cur + scr->unk0xc` from that copy.  Here GCC coalesces the copy
//     away because the cursor is already in the same register.  Making the
//     pre-walk cursor a distinct variable from the post-join one (so it can
//     live in a caller-saved r8, which is what the want does) does produce
//     the `mr r28,r8`, but it costs one more word elsewhere and lands at
//     1608B / 17.7%.
//
//  2. The `lbl_80301728` accumulation block (0x80076A00-0x80076A4C).  The
//     want keeps the global's address in r7 across the walk loop (r7 is not
//     touched inside it), so one `lis` serves both the load and the store:
//         lhz r0,0x1a(r9) / cmpwi r0,0 / beq / lis r7 / mtctr r0 /
//         lwz r11,0x1728(r7) / <loop> / stw r11,0x1728(r7)
//     Here loop.c emits `mtctr` next to the `lhz`, so the `if (ctr != 0)`
//     test needs `mfctr r9`, and the address - which landed in r9, a register
//     the loop clobbers with `slwi r9,r0,3` - is re-materialised after the
//     loop.  Net: got has `mfctr r9` + a second `lis r9`, want has neither.
//     Reproducing it needs GCC to keep the address in a register that the
//     loop does not touch; the offset-loop counter `i` has to land in r6
//     (as in the want) so that r7 is free, and this body puts `i` in r7.
//
//  3. `mr r29, r11` at 0x80076B1C - the want assigns the E20 loop pointer
//     through a caller-saved temporary (`mr r11,r28 ; lwz r9,8(r31) ;
//     mr r29,r11 ; li r10,0`) where this body copies straight into r29.
//     Every C spelling tried (`t20 = (E20 *)cur; e20 = t20;`, splitting the
//     loop pointer, hoisting the assignment) makes GCC delete the dead copy.
//
//  4. `meta->unk0x68 = &hd->unk0x4` lands in r0 here and in r3 in the want,
//     and the E20 loop counter `u` lands in r8 here and r10 in the want.
//
// ---------------------------------------------------------------------------
// MEASURED VARIANTS THIS PASS (all object sizes are the real .text size;
// `want_got.py` SILENTLY TRUNCATES an over-long object, so a "1604B" line
// with no SIZE MISMATCH can still be 1608 - always confirm with the ELF
// section size, which is what `tools/`'s compile_fn reports).
//
//   61.6%  1604B  13 saved regs r19..r31, frame 0x50, stmw r19   (start point)
//          + fix (C) only                                        61.6%
//          + fix (B)                                             70.6%
//          + fix (B)+(D)                                         71.1%
//          + fix (B)+(D)+ node-chain counter `nc`  <- BEST %     72.3%
//            ... but stmw r20, 12 saved regs, hoisted `li r20,0xff`,
//                two `stb`s in the E20 byte store.  UNMATCHABLE: the want
//                provably saves exactly r21..r31.  Kept out of the draft
//                on purpose; recipe is in the note above ((A)+(B)+(D)).
//   66.1%  1604B  11 saved regs r21..r31, frame 0x48, stmw r21  <- IN THIS FILE
//          (fix A+B+D + `nc` + the `blk` copy for unk0x28/unk0x30/unk0x34)
//   26-38% the same fixes with the build cursor split into two variables
//          (`cur` before the walk loop, `blk` after) so `cur` can live in a
//          caller-saved r8: right frame and save list, but 1600B/1608B.
//
// Reference: the regalloc-shift family is discussed in AGENTS-recipes.md 6a
// ("declaring two locals, one per arm, removes the shared live range"); (A)
// and (B) above are the same lever applied to a ternary constant and to a
// shared loop counter, and are the generic form of it.
#include "types.h"

extern bool lbl_803016A8;
extern s32 lbl_80301858;
extern s32 lbl_80301724;
extern s32 lbl_80301728;
extern f32 lbl_80295714;

typedef struct Vec3 Vec3;
typedef struct Scr Scr;
typedef struct Meta Meta;
typedef struct Obj Obj;
typedef struct E20 E20;
typedef struct LNode LNode;
typedef struct LOut LOut;

typedef struct {
    s32 size;
    s32 off;
} Ent8;

typedef struct {
    s32 size;
    s32 off;
    s32 pad8[4];
} Ent18;

typedef struct {
    s32 unk0x0;
    s32 unk0x4;
} Ent8b;

struct E20 {
    s32 unk0x0;
    u8 unk0x4;
    u8 unk0x5;
    u8 unk0x6;
    u8 unk0x7;
    s32 unk0x8;
    u16 unk0xc;
    u16 pad0xe;
    s32 unk0x10;
    u8 pad0x14[0xc];
};

struct Scr {
    s32 unk0x0;
    u16 pad0x4;
    u16 unk0x6;
    u16 unk0x8;
    u16 unk0xa;
    s32 unk0xc;
    u16 unk0x10;
    u16 unk0x12;
    s32 unk0x14;
    u16 unk0x18;
    u16 unk0x1a;
    u16 unk0x1c;
    u16 unk0x1e;
    u16 unk0x20;
    u8 pad0x22[0x1e];
    Ent8 unk0x40[1];
};

typedef struct {
    s32 unk0x0;
    s32 unk0x4;
} Y2;

typedef struct {
    s32 pad0x0[8];
    Y2 *unk0x20;
} Sub;

struct Meta {
    s32 unk0x0;
    s32 unk0x4;
    Scr *unk0x8;
    Vec3 *unk0xc;
    void *unk0x10;
    void *unk0x14;
    void *unk0x18;
    Sub *unk0x1c;
    Ent8 *unk0x20;
    Ent18 *unk0x24;
    s32 *unk0x28;
    s32 *unk0x2c;
    s32 *unk0x30;
    E20 *unk0x34;
    E20 *unk0x38;
    void *unk0x3c;
    void *unk0x40;
    s32 unk0x44;
    f32 unk0x48;
    f32 unk0x4c;
    f32 unk0x50;
    f32 unk0x54;
    s32 unk0x58;
    s32 unk0x5c;
    s32 unk0x60;
    s32 unk0x64;
    void *unk0x68;
    s32 unk0x6c;
};

struct Obj {
    u8 pad0x0[0x88];
    s32 unk0x88;
    s32 unk0x8c;
    u8 pad0x90[0x40];
    void *unk0xd0;
    u8 pad0xd4[0x1b4];
    Meta *unk0x288;
};

typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    void *unk0x8;
} A1;

typedef struct {
    s32 pad0x0[3];
    s32 unk0xc;
} N5;

typedef struct {
    s32 count;
    s32 unk0x4;
} Head;

typedef struct {
    s32 count;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xc;
} JBlk;

struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
};

struct LOut {
    s32 pad0x0[0xF];
    f32 f;
};

typedef struct {
    s32 pad0x0[8];
    LOut *unk0x20;
} LY;

typedef struct {
    s32 pad0x0[5];
    LY *unk0x14;
} LX;

struct LNode {
    s32 pad0x0;
    LX *unk0x4;
    s32 pad0x8;
    LNode *unk0xc;
};

typedef struct {
    u8 pad0x0[0x18];
    Obj *unk0x18;
} WObj;

void *Mem_Alloc2(s32);
void *Mem_NewZero(s32);
Obj *fn_8007DE80(void *, s32);
Meta *fn_80099428(void *);
N5 *fn_8005D420(void *, s32 *, s32);
void fn_800200D8(Ent18 *, E20 *, u8);
void *fn_8005742C(Obj *);
WObj *fn_8007E8F8(void);
void fn_80057CA8(void *, WObj *);
void fn_8007E9E8(WObj *);
Head *fn_8007787C(void *, Head *);
void fn_80055EA4(Obj *, void *);
void fn_800955AC(void);
void fn_800577A0(LNode *);
LNode *fn_800577B4(LNode *, s32);
LNode *fn_80057CA0(LNode *);
LNode *fn_8007EC14(LNode *);
void fn_8001D424(Vec3 *);
f32 PSVEC_Mag(Vec3 *);   /* wrapper @ 0x8001D4A8, not PSVECMag @ 0x8025E92C */

Obj *fn_800768A8(Scr *arg0, A1 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    Meta *meta;
    Obj *obj;
    E20 *e20;
    E20 *t20;
    Head *hd;
    LNode *root;
    LNode *nd;
    LNode *chain;
    LNode *p;
    N5 *t;
    WObj *wo;
    Ent8b *eb;
    char *cur;
    char *nx;
    char *base;
    u32 i;
    s32 j;
    s32 nc;
    s32 ii;
    u32 u;
    u32 uv;
    u32 uw;
    s32 n;
    s32 c;
    s32 ctr;
    s32 acc;
    s32 pad;
    void *nd2;
    LOut *nd3;
    f32 mag;
    f32 f0v;
    JBlk *blk;
    Vec3 v3;

    if (lbl_803016A8 != 0) {
        lbl_80301858 = 1;
    }
    if (arg2 != 0) {
        obj = fn_8007DE80(Mem_Alloc2(0x290), 0xA);
    } else {
        obj = fn_8007DE80(Mem_Alloc2(0x290), 1);
    }
    obj->unk0x88 = arg2;
    obj->unk0x8c = arg3;
    meta = fn_80099428(Mem_Alloc2(0x70));
    i = 0;
    obj->unk0x288 = meta;
    meta->unk0x0 = arg4;
    meta->unk0x8 = arg0;
    base = (char *)arg0->unk0x40;
    meta->unk0x20 = (Ent8 *)base;
    meta->unk0x24 = (Ent18 *)(base + arg0->unk0x18 * 8);
    c = arg0->unk0x12;
    n = arg0->unk0x18;
    pad = n * 8 + c * 0x18;
    cur = (char *)meta->unk0x24 + c * 0x18 + (((pad + 0x1F) & ~0x1F) - pad);
    while (i < meta->unk0x8->unk0x18) {
        meta->unk0x20[i].off = (s32)cur;
        cur += meta->unk0x20[i].size;
        i++;
    }
    i = 0;
    while (i < meta->unk0x8->unk0x12) {
        meta->unk0x24[i].off = (s32)cur;
        cur += meta->unk0x24[i].size;
        i++;
    }
    blk = (JBlk *)cur;
    meta->unk0x28 = (s32 *)blk;
    hd = (Head *)((char *)blk + meta->unk0x8->unk0xc);
    nx = cur + 8;
    ctr = meta->unk0x8->unk0x1a;
    if (ctr != 0) {
        acc = lbl_80301728;
        do {
            acc += *(s32 *)cur;
            cur = nx + *(s32 *)cur * 8;
            nx = cur + 8;
        } while (--ctr != 0);
        lbl_80301728 = acc;
    }
    lbl_80301724 += meta->unk0x8->unk0x1a;
    blk = (JBlk *)cur;
    if (meta->unk0x8->unk0x20 != 0) {
        meta->unk0x2c = (s32 *)blk;
        base = (char *)blk + 0x10;
        for (ii = 0; ii < meta->unk0x8->unk0x20; ii++) {
            for (j = 0; j < blk->count; j++) {
                eb = (Ent8b *)(base + j * 8);
                t = fn_8005D420(arg1->unk0x8, &eb->unk0x4, 1);
                eb->unk0x4 = t ? t->unk0xc : 0;
            }
            blk = (JBlk *)(base + blk->count * 8);
            base = (char *)blk + 0x10;
        }
    }
    meta->unk0x30 = (s32 *)blk;
    e20 = (E20 *)blk;
    u = 0;
    meta->unk0x34 = (E20 *)((char *)blk + meta->unk0x8->unk0x12 * 0x20);
    meta->unk0x38 = (E20 *)((char *)meta->unk0x34 + meta->unk0x8->unk0x1c * 0x20);
    cur = (char *)meta->unk0x38 + meta->unk0x8->unk0x1e * 0x20;
    while (u < meta->unk0x8->unk0x12) {
        e20->unk0x5 = (e20->unk0x5 & 0x80) ? 0xFF : e20->unk0x5 << 1;
        t20 = (E20 *)((char *)meta->unk0x38 + e20->unk0xc * 0x20);
        e20->unk0x7 = t20->unk0x6;
        for (j = 0; j < e20->unk0x4; j++) {
            t = fn_8005D420(arg1->unk0x8, &t20->unk0x0, 1);
            t20->unk0x0 = t ? t->unk0xc : 0;
            t20++;
        }
        fn_800200D8(meta->unk0x24 + u,
                    (E20 *)((char *)meta->unk0x38 + e20->unk0xc * 0x20),
                    e20->unk0x4);
        e20++;
        u++;
    }
    meta->unk0x18 = 0;
    meta->unk0xc = 0;
    meta->unk0x10 = 0;
    meta->unk0x14 = 0;
    if (meta->unk0x8->unk0x0 != 0) {
        meta->unk0xc = (Vec3 *)cur;
        cur += meta->unk0x8->unk0x0 * 0xC;
    }
    if (meta->unk0x8->unk0x8 != 0) {
        meta->unk0x14 = cur;
        cur += meta->unk0x8->unk0x8 * 4;
    }
    if (meta->unk0x8->unk0xa != 0) {
        meta->unk0x18 = cur;
        cur += meta->unk0x8->unk0xa * 4;
    }
    if (meta->unk0x8->unk0x6 != 0) {
        meta->unk0x10 = cur;
        cur += meta->unk0x8->unk0x6 * 6;
    }
    if (meta->unk0x8->unk0x14 != 0) {
        meta->unk0x3c = cur;
        cur += meta->unk0x8->unk0x14 * 6;
        meta->unk0x40 = cur;
    }
    f0v = lbl_80295714;
    meta->unk0x54 = f0v;
    meta->unk0x48 = f0v;
    meta->unk0x4c = f0v;
    meta->unk0x50 = f0v;
    for (uv = 0; uv < meta->unk0x8->unk0x0; uv++) {
        fn_8001D424(&v3);
        v3.x = meta->unk0xc[uv].x;
        v3.y = meta->unk0xc[uv].y;
        v3.z = meta->unk0xc[uv].z;
        mag = PSVEC_Mag(&v3);
        if (mag > meta->unk0x54) {
            meta->unk0x54 = mag;
        }
    }
    meta->unk0x1c = (Sub *)((char *)hd + (hd->unk0x4 + 0x40));
    for (uw = 0; uw < meta->unk0x8->unk0x10; uw++) {
        nd2 = fn_8005742C(obj);
        Mem_NewZero(0x58);
        wo = fn_8007E8F8();
        wo->unk0x18 = obj;
        fn_80057CA8(nd2, wo);
        fn_8007E9E8(wo);
        hd = fn_8007787C(nd2, hd);
        fn_80055EA4(obj, nd2);
    }
    if (meta->unk0x1c->unk0x20->unk0x4 != 0) {
        fn_800955AC();
    }
    n = hd->count;
    if (n != 0) {
        meta->unk0x6c = n;
        meta->unk0x68 = &hd->unk0x4;
        root = (LNode *)obj->unk0xd0;
        if (root != 0) {
            fn_800577A0(root);
            while ((nd = fn_800577B4(root, 0)) != 0) {
                chain = fn_8007EC14(fn_80057CA0(nd));
                p = chain->unk0xc;
                nc = 0;
                while (1) {
                    if (p->unk0x4 == (LX *)-1) {
                        p = 0;
                    }
                    if (p == 0) {
                        break;
                    }
                    p = p->unk0xc;
                    nc++;
                }
                if (nc != 0) {
                    p = chain->unk0xc;
                    if (p->unk0x4 == (LX *)-1) {
                        p = 0;
                    }
                    nd3 = p->unk0x4->unk0x14->unk0x20;
                    nd3->f = nd3->f + nd3->f;
                }
            }
        }
    }
    if (lbl_803016A8 != 0) {
        lbl_80301858 = 0;
    }
    return obj;
}
