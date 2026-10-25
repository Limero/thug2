// PARKED 2026-10-03 (a62): DIFF 20.55% masked (116/150 words differ), object
// .text 584B vs retail 600B — still 4 insns SHORT, so per AGENTS §6cs-1 the
// index-aligned pct is not meaningful until the length matches.
// reproduce: LEAF_TMPDIR=<scratch> tools/venv/bin/python \
//              tools/test_wip_drafts.py --addr 0x800C2AB0
//
// Gekko VMX A-form decode, CALIBRATED BY COMPILING (do not re-derive — the old
// op names in this file were partly wrong). Field order is
// opcode(6) frD(25:21) frA(20:16) frC(15:11) frB(10:6) XO(5:1) Rc(0), so
// xo = (w>>1)&0x1f. Ground truth from one ngccc -mps-float compile of
// __builtin_ps_{mul,add,sub,madd,muls0,sum0,merge00,res,rsqrte}:
//   0x19 ps_mul (frA,frB)   0x15 ps_add (frA,frC)  0x14 ps_sub (frA,frC)
//   0x1d ps_madd = frA*frC + frB (!! not A*B+C in the Gekko encoding GCC emits)
//   0x0c ps_muls0 (frA,frB) 0x0a ps_sum0           0x10 ps_merge00 (frC,imm=0x10
//   in the frB field)        0x18 ps_res            0x1a ps_rsqrte
// With that, every one of the 21 opcode-4 words in retail decodes and the whole
// body is self-consistent: xo=0x08 (D=frC) is the vector MOVE GCC uses for the
// four b.p0..p3 copies, and the two dot products really are
//   sum0( madd(v0, merge00(mul(v1,v1), {0,0}), v0) )   <- NOT mul(v0,v0) as the
// older note claimed; sum0's lo half is what makes the "+v0" term.
//
// FIXED THIS ROUND (a62): the loop head. Retail provably keeps the node count
// and the index in ONE register (r27): `lwz r27,cnt; cmpwi r27,0; addi r27,-1;
// beq`. A separate `cnt` local forces GCC to copy (old draft: r9=cnt, r28=i).
// `if (i-- == 0) return;` reproduces the cmpwi/addi/beq triple exactly, so the
// whole 0x2ACC..0x2B08 prefix now matches retail INSTRUCTION-FOR-INSTRUCTION.
//
// RESIDUAL, region by region (got is right in count everywhere except below):
//  1. REGISTER NUMBERS in the prefix: want i=r27 off=r26, got i=r28 off=r27.
//     Want also parks &a in r28 (rematerialised at the loop top), so its
//     allocator consumed one more hard reg before the IVs. Nothing in the C
//     forces that; chasing it by inventing locals is not honest.
//  2. sinf/cosf call pair (0x2B3C): retail reloads 0x18(r1)/0x1c(r1) AFTER the
//     two bl's; got hoists a `lfs f2,0(r26)` (the 1.0f pool load) above them and
//     reloads a.p[1] early. Load-hoisting, not semantics.
//  3. Dot product (0x2B58..0x2BB4, ~28 words): retail interleaves the three
//     rows as [80][84][1c][88]/fmuls, [70]/fmuls, [74][18]/fmuls, [78]/fmadds.
//     Got groups the lfs first. Same DAG, same expression order, GCC-2.95
//     flow-phase difference. Statement order in the draft already matches.
//  4. THE BIG ONE (0x2C28..0x2C8C): got has 21 words hoisted up into the
//     `if (d.hi>0)` block (the `sc = unk8*unkC8` fmuls and the b.p2/b.p3
//     ps_muls0 + the reloads of b.p0/b.p1) and is then missing 23 words at
//     0x2C2C..0x2C88. Reordering the 5 statements inside the if-block (muls0
//     before `b.p6.flt.lo`, which IS retail's order) changed nothing at all —
//     proved by measurement, so this is pure hoisting, not source order.
//  5. b.p0.lo store: retail uses `stfs f30, 4(r25)` (via the &b pointer) where
//     got uses `stfs f30, 0x1c(r1)`, and retail re-loads 1.0f into f31 after
//     the sin store where got parks it in f2 before the calls.
// No register pins, no inline asm, no fake scaffolding. Best next idea: the
// 4-word length gap is entirely explained by (4)+(5); try making the A_t pair
// and the B_t frame ONE struct (a[2] at r1+8 then p0..p7 at r1+0x18 — they are
// contiguous in retail) so there is a single address pseudo, which both frees
// a hard reg for the IVs (kills item 1) and removes one rematerialisation.
//
// WIP DRAFT (non-matching) — hand-rebuilt from disasm (tools/ps_disasm.py +
// raw opcode-4 word decode). Supersedes the m2c stub (was DIFF/4.5%).
// family=m2c range=0x800C2AB0-0x800C2D08 size=600B
// FLAG: -mps-float            <- LOAD-BEARING, body is paired-single
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// VERDICT 2026-09-27: DIFF 20.0% masked, object .text 584B vs retail 600B
// (4 insns short), no `.rodata` in the object (so no §4n/doc-14 pool blocker),
// relocs only REL24/REL14/ADDR16_HA/ADDR16_LO. Prologue+epilogue are now
// BYTE-IDENTICAL (stwu -0xa0 / stfd f30 0x90 / stfd f31 0x98 / stmw r25 0x74 /
// stw r0 0xa4) — the ±8 FPR frame quirk and the 7-GPR save area are solved by
// (a) exactly 2 callee-saved FPRs, (b) a pre-loop `bp = &b;` that forces
// &frame-struct into r25 (7th callee-saved GPR).
//
// WHAT IS NOW CORRECT (all verified against the raw words):
//  * Full semantics: this is a skater node loop — n = sk->nodes + i*0x1E0,
//    skip n->unk4==1, two fn_80005854(&vec2,&n->mat68) calls sandwiching a
//    3x3 matrix-vector product dir=(sin t, 0.0f, cos t) -> (X,Y,Z), then two
//    PS dot-product + rsqrte/res normalisations, then
//    fn_800C29B4(sk, n, f32) writing n->unk78. Callee arity is audited:
//    fn_80005854(void*,void*), fn_800C29B4(void*,void*,f32)->f32 (3 args,
//    f32 in f1 — the old draft passed a bogus 3rd GPR arg), sinf=0x80271170,
//    cosf=0x80271070, both f32(f32).
//  * All 40 opcode-4 words hand-decoded and emitted from `__builtin_ps_*`:
//    ps_mul/ps_merge00/ps_madd/ps_sum0/ps_rsqrte/ps_res/ps_muls0/ps_sub/ps_mr
//    (Gekko A-form uses frA*frC+frB, frB unused for 2-operand forms — proved
    // against promoted src/fn_800A07F0.c, e.g. 0x11AD0372 = ps_mul f13,f13).
//    No capstone VMX mislabels here: every opcode-4 word is real PS.
//  * File-local typedefs (trap #1): the shared Unk_C7387A53/Unk_C8FEE62D classes
//    type 0x70..0x98 / 0x8 / 0x10 / 0xC8 as s32; the node's 0x100..0x11F are
//    4 psq pairs, not scalars.
//  * The frame struct is 8 pairs: p0={sin,0} p1={cos,1} p2=p4 p3=p5
//    p4={X,Y} p5={Z,1} p6={rsqrte,1} s={n->unk8*n->unkC8, <never written>}.
//    GCC 2.95 keeps the "dead" scalar stores to 0x18/0x1C and 0x20/0x24 that
//    the later psq_st overwrites — matching retail for free.
//  * The dir vector is STORED to p0 then RELOADED for the matrix product
//    (retail: stfs 0x18/0x1C then lfs 0x18/0x1C). Modelled with
//    `((volatile H_t *)&b.p0)->flt.hi/.lo` staged into vh/vl — a plain lvalue
//    read gets copy-propagated and loses the two lfs (+3.3% when forced).
//
// PRECISE RESIDUAL (not "regalloc" — four concrete, localised causes):
//  1. LOOP HEAD REGISTER ROTATION. want: `lwz r27,0x1ac; cmpwi r27,0;
//     addi r27,r27,-1; beq` (ONE register for count and index, index in r27,
//     byte offset in r26). Got: `lwz r9; cmpwi r9,0; addi r28,r9,-1; beq`
//     with off in r27 — GCC copies the count instead of co-locating it.
//     4 spellings tried (i=cnt-1 / test-then-decrement / single-var / early
//     return); all keep the r9/r28 split. Costs 8 words, 2 GPRs.
//  2. LATCH ORDER. want `cmpwi r27,0; addi r26,-0x1e0; addi r27,-1; bne` (test
//     on the PRE-decrement value, addi not addic.); got `addi r27,-0x1e0;
//     addic. r27,-1; bne`. 3 latch forms (do-while, post-decr, explicit
//     break) all score lower. Costs ~4 words — this is the 584B vs 600B gap.
//  3. DOT-PRODUCT LOAD SCHEDULE. want interleaves the three matrix rows as
//     [0x80][0x84][1C][0x88]/fmuls,[0x70]/fmuls,[0x74][18]/fmuls,[0x78]/fmadds
//     and stores 0x3C,0x38,0x40,0x44. Got groups all nine lfs first, then the
//     fmuls, and stores 0x40,0x44,0x3C,0x38 (a rotate of want's run).
//     One principled store reorder (rotate-right by 2) is the obvious next
//     probe; the lfs schedule is GCC-2.95 flow-phase.
//  4. SECOND NORMALISATION ORDER. want: ps_muls0 p0,ps_muls0 p1,psq_st p2,
//     ps_sub a0,psq_st p3,psq_st a0,ps_sub a1,psq_st a1,ps_mul,psq_l a0,
//     ps_merge00,ps_madd,sum0,rsqrte,res. Got hoists the ps_sub of a1 ahead
//     of the first psq_st and reloads psq(0x08)/psq(0x10) once extra. The op
//     set is identical; only block layout and two redundant psq_l differ.
//     Also: want keeps `ps_rsqrte` result in f0 and copies to f13, got keeps
//     it in f13 (one-register shift) in the conditional block.
// Retrying from here: start with (2) then (1) — they are the size mismatch and
// the register-role shift; (3)/(4) are the remaining ~90 words of PS schedule.
// No register pins and no inline asm used in this draft.
#include "types.h"
#include "dolphin/SN_PS.h"
#include "structs.h"

extern f32 lbl_8029906C;    /* .rodata2 0.0f  */
extern f32 lbl_80299070;    /* .rodata2 1.0f  */
extern __ps_t lbl_80298F18; /* .rodata2 {0,0} */

typedef union {
    sn_ps ps;
    struct {
        f32 hi;
        f32 lo;
    } flt;
} H_t;

typedef struct {
    char pad0x0[4];
    s32 unk4;
    f32 unk8;
    char pad0xC[4];
    f32 theta;
    char pad0x14[0x14];
    f32 v28;
    f32 v2C;
    f32 v30;
    f32 v34;
    char pad0x38[0x30];
    char mat68[0x10];
    f32 unk78;
    char pad0x7C[0x4C];
    f32 unkC8;
    char pad0xCC[0x34];
    H_t v100;
    H_t v108;
    H_t v110;
    H_t v118;
} N_t;

typedef struct {
    H_t p[2];
} A_t;

typedef struct {
    H_t p0;
    H_t p1;
    H_t p2;
    H_t p3;
    H_t p4;
    H_t p5;
    H_t p6;
    H_t s;
} B_t;

typedef struct {
    char pad0x0[0x70];
    f32 m70;
    f32 m74;
    f32 m78;
    char pad0x7C[4];
    f32 m80;
    f32 m84;
    f32 m88;
    char pad0x8C[4];
    f32 m90;
    f32 m94;
    f32 m98;
    char pad0x9C[0x110];
    s32 cnt;
    char pad0x1B0[0x140];
    N_t *nodes;
} S_t;

void fn_80005854(void *, void *);
f32 fn_800C29B4(void *, void *, f32);
f32 sinf(f32);
f32 cosf(f32);

void fn_800C2AB0(S_t *sk) {
    A_t a;
    B_t b;
    B_t *bp;
    SN_PS_type d;
    SN_PS_type res;
    s32 i;
    s32 off;
    N_t *n;
    f32 zero;
    f32 vh;
    f32 vl;
    f32 sn;
    f32 cs;
    f32 X;
    f32 Y;
    f32 Z;
    f32 sc;

    i = sk->cnt;
    if (i-- == 0) {
        return;
    }
    zero = lbl_8029906C;
    off = ((i * 0x10) - i) << 5;
    bp = &b;
    do {
        n = (N_t *)((char *)sk->nodes + off);
        if (n->unk4 != 1) {
            a.p[0].ps = *(sn_ps *)&n->v28;
            a.p[1].ps = *(sn_ps *)&n->v30;
            fn_80005854(&a, n->mat68);
            sn = sinf(n->theta);
            cs = cosf(n->theta);
            b.p0.flt.hi = sn;
            b.p0.flt.lo = zero;
            vh = ((volatile H_t *)&b.p0)->flt.hi;
            vl = ((volatile H_t *)&b.p0)->flt.lo;
            Y = (cs * sk->m94) + ((vh * sk->m74) + (vl * sk->m84));
            X = (cs * sk->m90) + ((vh * sk->m70) + (vl * sk->m80));
            Z = (cs * sk->m98) + ((vh * sk->m78) + (vl * sk->m88));
            b.p4.flt.hi = X;
            b.p4.flt.lo = Y;
            b.p5.flt.hi = Z;
            b.p5.flt.lo = lbl_80299070;
            b.p1.flt.hi = cs;
            b.p1.flt.lo = lbl_80299070;
            b.p0.ps = b.p4.ps;
            b.p1.ps = b.p5.ps;
            b.p2.ps = b.p4.ps;
            b.p3.ps = b.p5.ps;
            fn_80005854(bp, n->mat68);
            d.ps = __builtin_ps_madd(
                b.p0.ps, b.p0.ps,
                __builtin_ps_merge00(__builtin_ps_mul(b.p1.ps, b.p1.ps),
                *(volatile __ps_t *)&lbl_80298F18));
            d.ps = __builtin_ps_sum0(d.ps, d.ps, d.ps);
            if (d.flt.hi > zero) {
                d.ps = __builtin_ps_rsqrte(d.ps);
                b.p6.ps = d.ps;
                b.p0.ps = __builtin_ps_muls0(b.p0.ps, d.ps);
                b.p6.flt.lo = lbl_80299070;
                b.p1.ps = __builtin_ps_mul(b.p1.ps, b.p6.ps);
            }
            n->v100.ps = b.p0.ps;
            n->v108.ps = b.p1.ps;
            sc = n->unk8 * n->unkC8;
            n->v110.ps = a.p[0].ps;
            n->v118.ps = a.p[1].ps;
            b.s.flt.hi = sc;
            b.p2.ps = __builtin_ps_muls0(b.p0.ps, b.s.ps);
            b.p3.ps = __builtin_ps_muls0(b.p1.ps, b.s.ps);
            a.p[0].ps = __builtin_ps_sub(a.p[0].ps, b.p2.ps);
            a.p[1].ps = __builtin_ps_sub(a.p[1].ps, b.p3.ps);
            d.ps = __builtin_ps_madd(
                a.p[0].ps, a.p[0].ps,
                __builtin_ps_merge00(__builtin_ps_mul(a.p[1].ps, a.p[1].ps),
                *(volatile __ps_t *)&lbl_80298F18));
            d.ps = __builtin_ps_sum0(d.ps, d.ps, d.ps);
            d.ps = __builtin_ps_rsqrte(d.ps);
            d.ps = __builtin_ps_res(d.ps);
            res.ps = d.ps;
            n->unk78 = fn_800C29B4(sk, n, res.flt.hi);
        }
        off -= 0x1E0;
        i -= 1;
    } while (i != 0);
}
