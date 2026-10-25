// WIP DRAFT (non-matching) — hand-rebuilt from the PS disassembly, 2026-10-04
// family=m2c range=0x801F8768-0x801F8B94 size=1068B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// === PARKED (2026-10-04) — DIFF 19.85% (53/267 masked words),
// object .text 1060B vs want 1068B (8B / 2 words SHORT), frame 0xb8 vs want
// 0xb0 (the whole save area + LR home sit 8B too high).
//
// *** REMOVED the six `register f32 x __asm__("frN")` FPR pins
// the previous revision parked with (inline `__asm__` is banned for this task).
// The pins were worth +3.5 points and the frame; without them the honest
// ceiling on this body is lower. The 23.77% in the previous note is NOT
// reproducible without asm and must not be quoted as the state of this file.
//
// BODY STATUS (all verified by hand against the want):
//   every callee symbol EXACT, `stmw r24,0x78` LR home EXACT in form, every
//   stack displacement in 0x08..0x5c EXACT, all 20 intra-function branch
//   targets land on the same basic blocks, store order in both PS webs is
//   the want's own store order (ascending slot), and the semantics
//   (see WHAT WAS RECOVERED) are right.
//
// *** REMAINING BLOCKER, restated with a complete accounting. want-vs-got
// instruction MULTISET differs by exactly:
//     +5 ps_mr, +2 addi, +1 psq_l   (want only)   |  got has +3 lfs, +2 psq_st,
//                                            -1 fmr  (got only)
// The +3 lfs/+2 psq_st/-1 fmr is the §6ez `S ls; ls.p = sum0(); l = ls.w[0];`
// lane extraction (3 words where want has 1 `ps_mr`, twice). The +5 ps_mr are
// pure register copies with no plain-C spelling (recipes §6cw: "a `ps_mr` has
// no plain-C spelling in this cc1"; same wall as src/wip/fn_800EA4D8.c, and
// §6ez's "the copies only appear when the lane has a second live name").
// The +2 addi / +1 psq_l is the want's loop-invariant address materialisation
// (see UNPARKED LEAD). So the size can never reach 1068 in legal C: the 5
// `ps_mr` are worth 5 words that no legal spelling emits, and everything after
// the last one (the epilogue, 0x404..0x428, 10 words) is misaligned as a
// consequence, not on its own account.
//
// WHAT WAS RECOVERED (all of it; the m2c draft was corrupt — phantom calls,
// duplicated stores, wrong struct offsets):
//   void fn_801F8768(Node *a, Vec *b, Vec *c, f32 ang)      // f1 arg
//   * `Node` is the bone/segment node: pairs at +0x08 and +0x10 (one 16-byte
//     Vec), s32 bone @+0x18, s32 @+0x1C, f32 radius @+0x20, Node* @+0x24 and
//     @+0x28 (the two child bones), s32 @+0x30 (the collider). `a+8` is the
//     Vec handed to fn_801F7608.
//   * fn_800546A0(0x2756C52D) -> fn_80057CA0() -> the geo object; that ->
//     fn_8005F550() -> vertex count; Mem_Alloc_3(count*16) -> 16-byte vertex
//     array (fn_8005F584 "get verts"), freed with Mem_Free_3 at the tail.
//   * lbl_802AE540 = 1e6 / lbl_802AE544 = -1e6 are the y min/max sentinels
//     (min/max over `v[i].a.w[1]`); lbl_802AE53C = 2.625 is the falloff radius;
//     lbl_802AE54C/548 = 1.0/2.0 = 0.5 scale; lbl_802AE550 = 0.0 threshold;
//     lbl_802AE51C = {0,2,4,6,8,9,10,11} = the 8-vertex index table;
//     lbl_802AE430 = {0.0f,0.0f} (the ps_merge00 zero).
//   * PS web #1 (when both child bones exist) is the segment-segment closest-
//     point solve: dA = c28 - a, dB = a - c24, dC = a - c24.xy, then
//     e = 0.5*(dA.b + dB), g = 0.5*(dA.a + dC), len2 = e.x^2 + g.x^2 + g.y^2
//     (built as merge00(e*e, {0,0}) + g*g then ps_sum0), and
//     radius *= sqrtf(1 - (g.y/len)^2) when len2 > 0.
//   * PS web #2 (when c24 exists) is the same length in the XZ plane (the
//     dy lane is forced to 0 with `V[6].w[1] = lbl_802AE550`), then a rotation
//     of every vertex about Y by atan2(dz,dx): x' = v.x + cs*dx + neg*dz,
//     z' = v.z + sn*dx + cs*dz, with cs = dx*rsqrte(len2), sn = dz*rsqrte(len2)
//     (NOTE the want's own register web proves cs<->sn here: f8 = V[7].w[0] is
//     the one it negates and uses as the `dx` coefficient of z').  So `cs`
//     and `sn` are named the wrong way round relative to the maths; the code
//     is right, the names are not — do not "fix" them.
//
// THE LOCAL FRAME:
//   ONE non-volatile `S V[11]` at r1+0x08 is the whole scratch pool, and
//   NOTHING ELSE in this body needs a stack slot (verified: adding unused
//   locals of f32/double/__ps_t type, or deleting any single declaration, or
//   deleting an entire loop/web, does not change the frame by a byte — so the
//   locals area is exactly V).  V[0],V[1] = the fn_801F7608 output (re-read
//   with psq_l/lfs EVERY iteration because the pool's address escapes into
//   fn_801F7608 and every `buf` store is volatile).  V[2..V[5] = the 8 s32
//   vertex indices, written by a 6-word countdown loop and 2 more words, read
//   back by an 8-iteration walk.  V[6..V[10] = the PS webs.  `S ls` lands at
//   0x60 and is the only other slot; every slot the want touches (0x08..0x5c)
//   is reproduced with NO extra pad.
//   The `lbl_802AE51C` copy really is `s32 n = 0x18; do { 6 words } while (n
//   -= 0x18);` — cc1 2.95 does NOT fold that 1-iteration countdown, which is
//   what emits want's `li r10,0x18 / addic. r10,r10,-0x18 / bne`.
//
// MEASURED / TRIED (all with `export LEAF_TMPDIR=<scratch>):
//   1.1%  m2c draft (given)                                 1096B, frame 0xc8
//   7.1%  first semantically-correct C                      1068B, frame 0xd0
//  12.7%  + non-volatile `volatile Vec *buf` + pointer walks 1136B
//  14.2%  + V non-volatile (the address-escaping idiom)       1060B, frame 0xb8
//  16.6%  + `pointer-walk loops` instead of `buf[i]` indexing 1036B
//  20.2%  + `S ls; ls.p = sum0(); l = ls.w[0];` (§6ez route) 1060B
//  19.85% + MIN/MAX LOOP CURSOR `volatile f32 *q = &buf->a.w[1]; q += 4;`
//         (restored: it is what emits want's `addi r9,r28,4` + `lfs f0,0(r9)`
//          rather than `mr r9,r28` + `lfs f0,4(r9)`) + dz-before-dx in the
//         rotate loop, which reproduces want's load ORDER
//         (p->b.w0, V[1], V[0], p->a.w0) = the state left here. 1060B, frame 0xb8
//   Flags are ALL no-ops on the final body (byte-identical output):
//   -fno-schedule-insns, -fno-schedule-insns2, -fno-thread-jumps, -fno-gcse,
//   -fno-tree-loop-optimize, -fno-cse-follow-jumps, -Os, -O1.
//
// NEGATIVE RESULTS worth keeping (all measured on the final body
// unless noted; the earlier results are in AGENTS-recipes.md + §6cw/§6ez):
//   * REMOVING THE `ls` LANE-EXTRACTION AND USING `l = <ps_sum0 expr>;`
//     DIRECTLY IS STRUCTURALLY BETTER AND 4 WORDS SHORTER-BODYED, BUT WORSE:
//     1036B / 15.36%.  What it proves is the blocker precisely: with the
//     plain-f32 spelling cc1 emits `fcmpu cr0,f13,f7` straight off the live
//     pair register and NO `ps_mr` — the whole 5-word deficit is the missing
//     copies, and nothing else.  Its multiset is exactly `+5 ps_mr +2 addi
//     +1 psq_l` with everything else equal, i.e. this is a *complete* account
//     of what is missing.  Keep this as the diagnostic reference.
//   * `l = *(f32 *)&ls.p;` (the §6ez row-3 "ps_mr" spelling) is byte-identical
//     to `l = ls.w[0];` here — no ps_mr, so the documented row 3 of that table
//     does NOT fire for this `S` union.  The cast buys nothing; keep the
//     union member read.
//   * `volatile S ls; ((volatile f32 *)&ls.p)[0]` = psq_st + lfs, NO fmr:
//     2 words per site, 1052B / 16.48% — strictly worse than the plain union.
//   * `S *v0 = &V[0]` cursors (u1/u2/u3), `Vec *v0`, block- vs function-scope,
//     and `volatile S *v0` all DO produce want's load shape
//     (`V[0]` off `8(r1)`, `V[1]` off `8(rX)`), i.e. they add exactly the one
//     missing preheader `addi` (+4B -> 1064B) — but they cost +8B of FRAME
//     (0xc0) and the two cursors get CSE'd into ONE register, so only one
//     `addi` appears, not the want's two.  Net: worse (11.99%).
//   * Making V[0]/V[1] a real 16-byte `Vec v01` variable (with `S V[9]` behind
//     it, so the slot layout is unchanged) does NOT give `8(rX)` — still
//     `16(r1)`.  The reload decomposes `MEM[PLUS(ADDR_EXPR(v01),8)]` just as
//     eagerly as it decomposes the array form.
//   * The frame: `S V[11]` alone already lands the save area 8B above want's.
//     V[10] gives frame 0xb0 EXACTLY, so frame = 0x08 + sizeof(V) + 88 with no
//     slack, and want = 0x08 + 88 + 80.  No edit found the missing 8B: not any
//     single f32 deletion (x, f, dy, neg, cs, sn, lo — all 0xb8), not `register`
//     on t/l/p, not splitting `t`->t1/t2 (0xc0), not deleting a whole loop or
//     web (all 0xb8), not the parameter list.  Unused locals get NO slots at
//     all (8 unused f32s leave the frame at 0xb8), so the 8B is a dead-slot /
//     reserve-layout effect of cc1, not of a named local.
//
// UNPARKED LEAD (the single remaining structural instruction class):
// the want's `addi r11, r1, 8` in the preheaders of BOTH the translate loop
// (0x210) and the rotate loop (0x38c), after `mtctr r29`, with `V[1]` then read
// as `8(r11)` and `V[0]` still off `8(r1)`.  Same value, same register, TWO
// separate instructions — that is the signature of reload's
// `allocate_loop_invariant_reloads` running once per loop (it deliberately
// emits after the loop's initial-condition test, and CSE cannot merge them
// because reload runs after CSE).  Any spelling tried here instead produces a
// hoisted `addi r27, r1, 8` at 0x064 — the constant-address materialisation is
// placed at function entry, not in the preheader.  Getting this needs the
// loop body to reference `&V[0]` as a *reload base* rather than as a value cc1
// materialises; not achieved in plain C here.  Worth 2 words AND the exact
// 1068B size, which is why it is the first thing to retry.
#include "dolphin/SN_PS.h"
#include "structs.h"

typedef union {
    __ps_t p;
    f32 w[2];
    s32 i[2];
} S;

typedef struct {
    S a;
    S b;
} Vec;

typedef struct Node {
    s32 f00;
    s32 f04;
    Vec v08;
    s32 bone;
    s32 unk1c;
    f32 rad;
    struct Node *c24;
    struct Node *c28;
    s32 phys;
} Node;

extern f32 lbl_802AE53C;
extern f32 lbl_802AE540;
extern f32 lbl_802AE544;
extern f32 lbl_802AE548;
extern f32 lbl_802AE54C;
extern f32 lbl_802AE550;
extern const s32 lbl_802AE51C[];
extern const S lbl_802AE430;

CStruct *fn_800546A0(s32);
CStruct *fn_80057CA0(CStruct *);
s32 fn_8005F550(CStruct *);
void fn_8005F584(CStruct *, void *);
void *Mem_Alloc_3(s32);
void Mem_Free_3(void *);
void fn_8005F70C(CStruct *, void *);
s32 fn_801F76E4(s32);
void fn_801F7608(Vec *, Vec *, Vec *, Vec *, f32);
void fn_801F8BD4(Node *);
f32 sqrtf(f32);

void fn_801F8768(Node *arg0, Vec *arg1, Vec *arg2, f32 arg3) {
    S V[11];
    CStruct *obj;
    volatile Vec *buf;
    volatile Vec *p;
    s32 cnt;
    s32 i;
    f32 lo;
    f32 hi;
    f32 rad;
    f32 yoff;
    f32 cs;
    f32 sn;
    f32 neg;
    f32 f;
    f32 x;
    f32 dy;
    f32 l;
    S ls;
    __ps_t t;

    if (arg0->bone == 0) {
        fn_801F8BD4(arg0);
        return;
    }
    if (arg0->rad < lbl_802AE53C) {
        fn_801F8BD4(arg0);
        return;
    }
    obj = fn_80057CA0(fn_800546A0(0x2756C52D));
    cnt = fn_8005F550(obj);
    buf = Mem_Alloc_3(cnt * 16);
    fn_8005F584(obj, buf);

    lo = lbl_802AE540;
    hi = lbl_802AE544;
    {
        volatile f32 *q = &buf->a.w[1];
        for (i = 0; i < cnt; i++) {
            f = *q;
            if (f < lo) {
                lo = f;
            }
            if (f > hi) {
                hi = f;
            }
            q += 4;
        }
    }

    rad = lbl_802AE53C;
    if (arg0->c24 != 0 && arg0->c28 != 0) {
        V[8].w[0] = lbl_802AE54C / lbl_802AE548;
        V[1].p = arg0->c28->v08.b.p - arg0->v08.b.p;
        V[0].p = arg0->c28->v08.a.p - arg0->v08.a.p;
        V[3].p = arg0->v08.b.p - arg0->c24->v08.b.p;
        V[2].p = arg0->v08.a.p - arg0->c24->v08.a.p;
        V[7].p = V[1].p + V[3].p;
        V[5].p = __builtin_ps_muls0(V[7].p, V[8].p);
        V[6].p = V[0].p + V[2].p;
        V[4].p = __builtin_ps_muls0(V[6].p, V[8].p);
        t = __builtin_ps_mul(V[5].p, V[5].p);
        t = __builtin_ps_merge00(t, lbl_802AE430.p);
        t = __builtin_ps_madd(V[4].p, V[4].p, t);
        ls.p = __builtin_ps_sum0(t, t, t);
        l = ls.w[0];
        if (l > lbl_802AE550) {
            t = __builtin_ps_rsqrte(t);
            V[9].p = t;
            V[9].w[1] = lbl_802AE54C;
            V[4].p = __builtin_ps_muls0(V[4].p, t);
            V[5].p = __builtin_ps_mul(V[5].p, V[9].p);
        }
        x = V[4].w[1];
        rad = sqrtf(lbl_802AE54C - x * x) * rad;
    }

    fn_801F7608((Vec *)&V[0], &arg0->v08, arg1, arg2, arg3);
    yoff = hi + rad;
    for (p = buf, i = 0; i < cnt; i++) {
        p->a.p = __builtin_ps_add(p->a.p, V[0].p);
        p->b.p = __builtin_ps_add(p->b.p, V[1].p);
        p->a.w[1] -= yoff;
        p++;
    }
    {
        volatile s32 *d = &V[2].i[0];
        const s32 *s = lbl_802AE51C;
        s32 n = 0x18;
        do {
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
            d[3] = s[3];
            d[4] = s[4];
            d[5] = s[5];
            n -= 0x18;
            d += 6;
            s += 6;
        } while (n != 0);
        d[0] = s[0];
        d[1] = s[1];
    }
    dy = arg0->rad - yoff;
    dy -= hi;
    {
        volatile s32 *d = &V[2].i[0];
        for (i = 0; i < 8; i++) {
            buf[*d].a.w[1] -= dy;
            d++;
        }
    }
    if (arg0->c24 != 0) {
        V[6].p = arg0->v08.a.p - arg0->c24->v08.a.p;
        V[6].w[1] = lbl_802AE550;
        V[7].p = arg0->v08.b.p - arg0->c24->v08.b.p;
        t = __builtin_ps_mul(V[7].p, V[7].p);
        t = __builtin_ps_merge00(t, lbl_802AE430.p);
        t = __builtin_ps_madd(V[6].p, V[6].p, t);
        ls.p = __builtin_ps_sum0(t, t, t);
        l = ls.w[0];
        if (l > lbl_802AE550) {
            t = __builtin_ps_rsqrte(t);
            V[10].p = t;
            V[10].w[1] = lbl_802AE54C;
            V[6].p = __builtin_ps_muls0(V[6].p, t);
            V[7].p = __builtin_ps_mul(V[7].p, V[10].p);
        }
        sn = V[7].w[0];
        cs = V[6].w[0];
        neg = -sn;
        for (p = buf, i = 0; i < cnt; i++) {
            f32 dz = p->b.w[0] - V[1].w[0];
            f32 dx = p->a.w[0] - V[0].w[0];
            p->a.w[0] = V[0].w[0] + (cs * dx + neg * dz);
            p->b.w[0] = V[1].w[0] + (sn * dx + cs * dz);
            p++;
        }
    }
    if (arg0->phys == 0) {
        arg0->phys = fn_801F76E4(0x2756C52D);
    }
    fn_8005F70C(fn_80057CA0(arg0->phys), buf);
    Mem_Free_3(buf);
}