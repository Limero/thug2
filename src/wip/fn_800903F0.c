// WIP DRAFT (non-matching) — hand-rewritten from retail semantics (was m2c)
// family=m2c range=0x800903F0-0x80090958 size=1384B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-05 (w2_800903F0): best measured 18.26% masked (score_wip /
// test_wip_drafts verdict DIFF). Got 1380B vs want 1384B. The body below is a
// from-scratch typed rewrite: every stack offset, every block, every call
// sequence and every FP idiom now matches retail 1:1, so the residual is
// register-allocation / rematerialisation coin flips plus ONE structural
// length gap. What is left, in order of cost:
//
//  1) LENGTH (4 words). Retail's 0x800904E8 else-block re-materialises the
//     whole float!= test (lis r9 / lfs f13 / lfs f0 / fcmpu cr7 / crnot /
//     mfcr / clrlwi = 7 instrs) and the *branch* test at 0x80090418 uses
//     `fcmpu cr0`. My identical C source makes ngccc CSE the two, collapsing
//     the else block to `crnot cr7un,cr7eq; mfcr r0; clrlwi r0,0x1f` (3) and
//     moving the branch compare to cr7. Every other region is length-exact,
//     so this is the only thing keeping got 4 words short of 1384B.
//  2) FRAME (6 instrs). Retail: locals 0x08..0x103 (252B), save area at
//     0x104 (`stmw r23`), f31 at 0x128, frame 0x130. Mine: locals 0x08..0xff
//     (248B), save area at 0x100 (`stmw r24`), f31 at 0x120, frame 0x128.
//     All *used* offsets are identical, so retail simply has 4 bytes of dead
//     local space at 0x100 that I could not reproduce from any declaration
//     (ngccc drops unused locals, and compiler temps are allocated last, so
//     no user local can land at 0x100).
//  3) REGISTER CHOICES. retail keeps r23..r29 callee-saved, mine r24..r31;
//     `n` (p->i1C8) lives in r0 in retail and r22/r24 in mine; retail reloads
//     p->p1D4 into r8/r11 at 0x800905A0/0x800905E0 where mine keeps r30 or
//     picks r11; retail hoists `lis r24` (the 0x80290000 base) at 0x800906DC
//     and reuses it for lbl_80296EF0, mine uses r26/r28; retail materialises
//     QB_COLOR_GRAY64 once (r10) and mine twice.
//  4) Scheduling only: order of `addi r30,r30,-0x498c`, `li r23,0`,
//     `addi r25/r28, r1, ...`, and the lbl_8028E100 arg loads.
//
// SOLVED along the way (kept in the body): the `(f32)d` int->float block at
// 0x80090608 is byte-identical to retail modulo relocation masking (plain
// `(f32)d`, NOT the hand-written union + lbl_80296EF8 form, which split the
// xor into xoris+xori, reversed the fsub AND cost an extra 8-byte stack slot
// that pushed the fctiwz temp from 0xf8 to 0x100); the 0x800903F4 frame shape,
// f31 callee-save, all stack offsets, the `bge` (not `blt`) ring-capacity
// branch, lbl_8037B674+0x20 (f32[8], NOT Vec3[3] at +0x24), single merged
// `cmpwi r3,0` after the fn_80096D38/4C pair, and QB_COLOR_GRAY64 CSE.
//
// RULED OUT for (1): `volatile` casts on the else operands (gives cr0 for the
// branch but duplicates the `lis`, +1 instr; with BOTH operands volatile
// ngccc hoists the block into the hot path and the object grows to 1396B);
// `!(f13 == lbl_80296EEC)` (ngccc folds it straight back to !=, same 1380B);
// `static const f32` for lbl_80296EEC (no better than the named local).
// RULED OUT for (2): every declaration order/size permutation of the frame
// objects that keeps the used offsets (they all bottom out at 0x100).
#include "types.h"
#include "qb_constants.h"

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct Part {
    s32 i0;
    f32 f4;
    f32 f8;
    f32 fC;
    s32 i10;
} Part;

typedef struct Obj {
    char pad00[0x34];
    f32 f34;
    f32 f38;
    char pad3C[0xFC];
    f32 f138;
    char pad13C[0x30];
    s32 i16C;
    s32 i170;
    char pad174[0xC];
    s32 i180;
    char pad184[0x24];
    Vec3 v1A8;
    char pad1B4[0xC];
    s32 i1C0;
    s32 i1C4;
    s32 i1C8;
    Part *p1CC;
    Part *p1D0;
    Part *p1D4;
    char pad1D8[0x80];
    s32 i258;
    u8 u25C;
    u8 u25D;
    char pad25E[0x2];
    char pad260[0x40];
} Obj;

typedef struct G1 {
    s32 a00;
    u8 a04;
    u8 a05;
    u8 a06;
    f32 a08;
    u16 a0C;
    u16 a0E;
    char pad10[0x10];
} G1;

typedef struct G2 {
    s32 a20;
    u16 a24;
    u8 a26;
    u8 a27;
    u16 a28;
    u32 a2C;
    u16 a30;
    u16 a32;
    u16 a34;
    u8 a36;
    u8 a37;
    char pad38[8];
} G2;

extern f32 lbl_80296EEC;
extern f32 lbl_80296EF0;
extern f64 lbl_80296EF8;
extern f32 lbl_80296F00;
extern f32 lbl_8037B614[];
extern f32 lbl_8037B674[];

s32 fn_8026AA08(void);
f32 fn_800144C8(void);
void fn_800903C0(Part *, s32);
s32 fn_80096D38(Vec3 *);
s32 fn_80096E4C(Vec3 *);
void fn_8001E248(s32, s32, s32, s32, s32, s32, s32);
void fn_8001F2D8();
void fn_800231C4(G1 *, G2 *, s32, s32, s32, s32, s32, s32);
void fn_8001FAA4(s32, s32, s32, s32, s32);
void fn_8001D440(Vec3 *, f32, f32, f32);
void fn_8001D424(Vec3 *);
void fn_8001D478(Vec3 *, Vec3 *, Vec3 *);
void fn_8001D4C8(Vec3 *);
void fn_80269EC0(s32, s32, s32, s32);
void fn_80269EF8(s32, s32, s32, s32);
void GX_GetProjectionv(f32 *);
void GX_GetViewportv(f32 *);
void lbl_8028E100(Part *, f32, s32, f32, void *, void *, f32, f32 *, void *, f32 *);

void fn_800903F0(Obj *p, s32 arg1) {
    s32 v;
    s32 n;
    s32 i;
    f32 f11;
    f32 zero;
    u32 gray;
    f32 f13;
    Part *cur;
    G1 s1;
    G2 s2;
    Vec3 v48;
    Vec3 v58;
    Vec3 v68;
    f32 blk[8];
    f32 proj[8];
    f32 vp[6];
    f32 clr[10];

    f11 = lbl_80296EEC;
    f13 = p->f34;
    if (f13 == f11) {
        v = (p->f34 != lbl_80296EEC);
    } else if (p->i1C0 == 0 || f13 != p->p1D0->f4) {
        if (p->i1C8 < p->i1C4) {
            p->i1C8 = p->i1C8 + 1;
            p->p1D0 = (Part *)((u8 *)p->p1D0 + 0x14);
            if (p->p1D0 == (Part *)((u8 *)p->p1CC + p->i1C4 * 0x14)) {
                p->p1D0 = p->p1CC;
            }
            p->p1D0->f4 = p->f34;
            p->p1D0->f8 = lbl_80296EF0 / p->f34;
            p->p1D0->fC = f11;
            p->p1D0->i0 = 0;
            p->p1D0->i10 = fn_8026AA08() & 0x3FFF;
            if (p->p1D0->i10 == 0) {
                p->p1D0->i10 = 1;
            }
            v = 1;
        } else {
            v = 0;
        }
    } else {
        v = (p->f34 != lbl_80296EEC);
    }
    p->i1C0 = v;

    n = p->i1C8;
    if (n == 0) {
        return;
    }
    if (arg1 != 0) {
        i = 0;
        cur = p->p1D4;
        for (; i < p->i1C8; i++) {
            cur->fC = cur->fC + fn_800144C8();
            cur = (Part *)((u8 *)cur + 0x14);
            if (cur == (Part *)((u8 *)p->p1CC + p->i1C4 * 0x14)) {
                cur = p->p1CC;
            }
        }
    }
    if (p->i1C0 != 0) {
        p->p1D0->i0 = (s32)(p->p1D0->fC * p->p1D0->f4 + lbl_80296EF0);
    }
    if (p->p1D4->fC > p->f38) {
        s32 d;
        d = (s32)((p->p1D4->fC - p->f38) * p->p1D4->f4 + lbl_80296EF0);
        p->p1D4->i0 = p->p1D4->i0 - d;
        if (p->p1D4->i0 > 0 || (p->i1C8 == 1 && p->i1C0 != 0)) {
            p->p1D4->fC = p->p1D4->fC - (f32)d * p->p1D4->f8;
            fn_800903C0(p->p1D4, d);
        } else {
            p->i1C8 = p->i1C8 - 1;
            p->p1D4 = (Part *)((u8 *)p->p1D4 + 0x14);
            if (p->p1D4 == (Part *)((u8 *)p->p1CC + p->i1C4 * 0x14)) {
                p->p1D4 = p->p1CC;
            }
            if (p->i1C8 == 0) {
                return;
            }
        }
    }
    if (p->i16C == 0) {
        s32 r3v;
        r3v = (p->i180 != 0 ? fn_80096D38(&p->v1A8) : fn_80096E4C(&p->v1A8));
        if (r3v == 0) {
            return;
        }
    }
    fn_8001E248(4, 0, 0, 0, 0, 0, 2);
    i = 0;
    fn_8001F2D8(2, 9, 1, 0xD, 1);
    s2.a20 = p->i258;
    s2.a24 = 0x61;
    s2.a26 = p->u25C;
    s2.a27 = p->u25D;
    s2.a34 = 0;
    s1.a00 = 0;
    s1.a05 = 0;
    s1.a0C = 0;
    s1.a0E = 0;
    s2.a28 = 0;
    s2.a30 = 0;
    s2.a32 = 0;
    s1.a04 = 1;
    s1.a06 = 2;
    gray = QB_COLOR_GRAY64;
    s2.a2C = gray;
    s2.a37 = 0;
    zero = lbl_80296EEC;
    s1.a08 = zero;
    s2.a36 = 0;
    fn_800231C4(&s1, &s2, 1, 1, 0, 0, 1, gray);
    fn_8001FAA4(0, 0x3C, 0x3C, 0x3C, 0x3C);
    fn_8001D440(&v48, zero, lbl_80296EF0, zero);
    fn_8001D424(&v58);
    fn_8001D424(&v68);
    fn_8001D478(&v58, (Vec3 *)&lbl_8037B674[8], &v48);
    fn_8001D478(&v68, &v58, (Vec3 *)&lbl_8037B674[8]);
    fn_8001D4C8(&v58);
    fn_8001D4C8(&v68);
    blk[0] = v58.x;
    blk[1] = v58.y;
    blk[2] = v58.z;
    blk[4] = v68.x;
    blk[5] = v68.y;
    blk[6] = v68.z;
    blk[3] = lbl_80296EF0;
    blk[7] = lbl_80296EF0;
    fn_80269EC0(6, 7, 6, 7);
    fn_80269EF8(0xE, 7, 0xE, 7);
    GX_GetProjectionv(proj);
    GX_GetViewportv(vp);
    clr[0] = lbl_8037B614[8];
    clr[1] = lbl_8037B614[9];
    clr[2] = lbl_8037B614[11];
    clr[3] = lbl_8037B614[10];
    clr[4] = proj[1];
    clr[5] = vp[2];
    cur = p->p1D4;
    if (i >= n) {
        return;
    }
    for (; i < p->i1C8; i++) {
        if (cur == (Part *)((u8 *)p->p1CC + p->i1C4 * 0x14)) {
            cur = p->p1CC;
        }
        if (cur->i0 > 0) {
            lbl_8028E100(cur, p->f38, p->i170, p->f138, (void *)(p->pad13C), (void *)(p->pad260), lbl_80296F00, blk, (void *)&blk[4], clr);
        }
        cur = (Part *)((u8 *)cur + 0x14);
    }
}