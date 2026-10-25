// WIP DRAFT (non-matching) — hand-restructured from DOL disassembly
// family=m2c range=0x800BE854-0x800BF7C4 size=3952B
// FLAG: -mps-float -Os -fno-gcse -fno-expensive-optimizations
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// ===== VERDICT 2026-09-27: DIFF, 17.41% masked (test_wip_drafts --addr) =====
// want 3952B / 988 insns · got 3716B / 929 insns (236B / 59 insns SHORT)
// opcode-sequence match 36.6%. `_dummy` variant scores WORSE (15.2%) so no
// volatile-double pad is wanted. Prologue now EXACT: stwu -0xd0 / mflr /
// stfd f30,0xc0 / stfd f31,0xc8 / stw r0,0xd4, and the saved-GPR COUNT is
// right (16 = stmw r14,0x78 in got vs stmw r16,0x80 in want; same count, the
// window sits 2 low because arg0 lands in r28 instead of r31).
//
// ---- KEY INSIGHT (new, reusable): ngccc's (f64)(s32)x uses a 16-BIT sign
// mask. Probed: `float f(s32 x){return (f32)(f64)(s32)x;}` emits
//   xoris r3, r3, 0x8000        <-- NOT 0x80000000
//   lis r0,0x4330 / stw r0,hi / stw r3,lo / lfd / lfd / fsub / frsp
// i.e. only the low half is flipped (correct only for |x| < 2^15 — the game
// relies on that). `u32`/`u16` get NO xoris and subtract 2^52; `s32`/`s16`/
// plain `int` all get the 0x8000 xoris and subtract 2^52+2^31. That is why
// retail's 0x800BEDF4 is `xoris r0,r27,0x8000` + `-0x7090(r10)`
// (lbl_80298F70 = 2^52+2^31) while the wheel loop at 0x800BF73C is a bare
// `stw` + `-0x7070(r11)` (lbl_80298F90 = 2^52).  Do NOT "fix" that 0x8000.
//
// ---- SEMANTIC BUGS FOUND AND FIXED THIS ROUND (all were real, all in the
// old body): (1) the shared `Unk_C7387A53` types every slot 0x20..0xAC and
// 0x160..0x180 as s32, but retail loads/stores them as f32 (psq/stfs) — the
// file-local `Self_t` below with the true f32 layout is what fixed the frame,
// the callee-saved count and the whole body in one edit (M6.89d-note);
// (2) the contact-normal block read the 3x3 at obj+0x78 with stride 0x10; the
// `lfsx` pair at 0x800BF21C/0x800BF228 is `base + i*16 + i*4` = stride
// 0x14, not 0x10; (3) its 2nd/3rd quaternion terms were `(m[i1][i] +
// m[i][i1])` — retail is `m[0][i1] + m[i1][i2]` and `m[0][i2] + m[i2][i1]`
// (0x800BF2D8/0x800BF2EC read m[i][i1] and m[i1][i2]); (4) the `sum > 0` /
// `k` branch used the *uninitialised* `fs_t` before assigning it (m2c's
// statics-DCE husk) — retail is `fs = sqrtf(sum + 1.0f)`;
// (5) `len2 = y²+(z²+(x²+w²))` had the wrong association; retail's
// fmadds chain is `y²; x²+y²; z²+(…); w²+(…)` = `w²+(z²+(x²+y²))`;
// (6) arg0+0x124 is a `stb`, not a `stw`; (7) the FC8C4AC6 loop called
// fn_801294E0 before fn_8012954C and re-used one temp for all three
// elements — retail fetches the element first, then three fn_801294E0 calls;
// (8) the 8 identity quaternions / vec4 / matrix copies are psq_l+psq_st
// PAIRS, not 16+4 scalar stfs; the 16-float matrix publish to obj+0x78 and
// obj+0xD0 is now byte-exact (8+8 straight-line pairs, a loop gives
// mtctr+indexed psq instead); (9) `li r29,0` for the C023FA75 loop is
// materialised BEFORE the GetArray call; (10) the QB engine block re-reads
// 0x1C0/0x1C4, not 0x1B4/0x1B8.
//
// ---- PRECISE RESIDUAL (why plain C cannot reach it yet):
// (a) 59 insns short, all of it in the FC8C4AC6 loop (retail
// 0x800BEBF0..0x800BEDDC = 239 insns). The 44 opcode-4 words hand-decode as
// xo5 = 10(sum0)/12(muls0)/16(merge)/20(sub)/21(add)/24(res)/25(mul)/
// 26(rsqrte)/29(madd) plus TWO xo5=8 VC=2 words (0x800BF35C, 0x800BF3F0) —
// i.e. all standard Gekko PS (so the "illegal opcode-4" park reason in the
// old header is WRONG, per doc-06 M5.0t/§6ax-218), but retail's accumulate is
// a FOUR-way sum0→rsqrte→res→scale product whose operand web and whose
// 0x08/0x10/0x30/0x38/0x40/0x48/0x50 stack staging I could not reproduce;
// the xo5=8 VC=2 word (f12 = f(f0, f11)) has no probe hit — it is the
// scalar-broadcast step of `v[i] *= s` when `s` comes from a stack slot, and
// `__builtin_ps_muls0` alone emits only the two muls0s.
// (b) `arg0->phase % 3` compiles to GCC's mtctr/mfctr-as-scratch sequence
// (15 insns) instead of retail's mulhw/srawi/subf/slwi/add/subf (8) — a pure
// register-pressure symptom that only clears once the whole allocation
// window matches.
// (c) The base-pointer materialisation: retail sinks 8 `addi`s
// (r23,r22,r17,r16,r20,r19,r18,r21 at 0x800BEB18..0x800BEB98) into the
// call-setup delay slots of the eight GetFloat calls; mine hoist them to the
// prologue. Assigning them at the right place in the source (see the block
// comment there) fixed the FRAME but not the placement.
// (d) LINK-CLEAN: NO. `powerpc-eabi-readelf -r` on the object shows a 16-byte
// module `.rodata` = {0x4330000080000000, 0x4330000000000000} — ngccc's own
// int->double pool. Retail has those two doubles in `.rodata2` as
// lbl_80298F70 / lbl_80298F90, so a promote needs tools/fix_fp_pool.py
// (doc-14) before the DOL stays byte-identical. Reloc mix otherwise fine:
// 75 REL14 / 45 ADDR16_HA / 43 REL24 / 33 ADDR16_LO.
// (e) Flag ladder (masked %): default -O2 1.4 · -Os 9.9 · -Os -fno-gcse 11.8 ·
// -Os -fno-gcse -fno-expensive-optimizations 17.4 (current) ·
// + -fno-strength-reduce 17.4 (no better) · + -fno-sched-spec no change.
// `-fno-schedule-insns` HURTS (0.3-1.1) and `-fno-omit-frame-pointer`
// collapses the frame — do not add. The sibling fn_800BA9C8 uses
// `-fno-rerun-cse-after-loop`, which this cc1 REJECTS ("Invalid option") —
// that sibling's FLAG line is bogus.
//
// ===== RE-MEASURED 2026-10-07 — still PARKED =====
// Verdict re-confirmed with the draft's own header flags: 17.41% (masked,
// full want span) / 18.51% positional; object .text 3716B vs want 3952B.
//
// FIRST REAL DIVERGENCE — 0x800BE88C, and it is REGISTER COLOUR ONLY.
//   want 0x88C lwz r11,0x1350(r31) / lis r9,0x5555 / ori ...0x5556 /
//             addi r11,r11,1 / b 0x800BE8C8        (straight-line %3)
//   got  0x88C lwz r9,0x1350(r31) / addi r9,r9,1 / b ...
//        + the join expands `% 3` through CTR (mtctr r9 / mfctr r9 / mfctr r10)
// i.e. the same mulhw/srawi/subf/slwi/add/subf chain, spilled through CTR
// because one more pseudo is live in got.  Everything from 0x800BE854 down to
// ~0x800BEB4C lines up 1:1 otherwise: identical prologue shape, identical
// mr r24,r4 / mr r31,r3 (arg0 IS in r31), identical QB hash pairs
// (0x9359B858 then 0xE6B5FCD9 then 0x751DA48B), identical bl targets, identical
// branch senses and identical `stw r30,0x1350(r31)` shape.  Verified against
// the PS-decoded want|got packet (build/b34pkt/fn_800BE854.psdiff.txt) and the
// capstone side-by-side (build/b34pkt/fn_800BE854.diff.txt).
//
// The frame is 16B SHORT (got stwu -0xc0 / stfd 0xb0,0xb8 / stmw r15,0x6c /
// LR 0xc4 vs want stwu -0xd0 / stfd 0xc0,0xc8 / stmw r16,0x80 / LR 0xd4) and
// the GPR window is one register WIDER (stmw r15 saves r15..r31 = 17 vs want's
// 16).  Both are downstream of the same cause, not independent bugs: the
// 239-instruction FC8C4AC6 loop (retail 0x800BEBF0..0x800BEDDC) owns the
// 0x30/0x38/0x40/0x48/0x50 stack staging that makes up the missing 128 bytes
// of locals, and the extra callee-saved register the draft keeps for that
// region is r15.
//
// WHY IT IS STILL PARKED: plain C for that loop has NOT been reconstructed.
// The want side of the loop is readable (psdiff offsets 0x39C+ show
// `mulli r11,r28,0x88; addi r11,r11,0x1c8; add r29,r11,r31` then
// `psq_l f11,0(r29),W0,I0` / `psq_l f10,8(r29),W0,I0` — the delta vectors are
// built straight out of the arg0+0x1C8 record, not from a stack copy), but the
// draft's speculative `__builtin_ps_*` body is far shorter and its 4-way
// sum0->rsqrte->res accumulate, the scalar-broadcast of `v[i] *= s`, and the
// two xo5=8 VC=2 words (0x800BF35C/0x800BF3F0) remain unmatched.  The 59-word
// shortfall is entirely inside that loop, so no amount of local register
// nudging outside it can raise the score: the CTR spill at 0x800BE888 and the
// r15 window are symptoms of the same missing region.
//
// Do NOT spend effort on the early region: it is right.  Do NOT add
// -fno-rerun-cse-after-loop (rejected by this cc1) and do not touch
// -fno-schedule-insns / -fno-omit-frame-pointer (documented regressions above).
// The only useful next step is the FC8C4AC6 loop body.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

/* ---- retail self layout (all f32 slots the shared Unk_C7387A53 class types
   as s32 -> every load/store came out fctiwz+stw; see M6.89d-note) ---- */
typedef struct {
    char pad0x00[0x0C];
    s32 obj;                    /* 0x0C */
    char pad0x10[0x10];
    f32 pos[4];                 /* 0x20 */
    f32 q0[4];                  /* 0x30 */
    f32 q1[4];                  /* 0x40 */
    f32 q2[4];                  /* 0x50 */
    char pad0x60[0x10];
    f32 mat[16];                /* 0x70 .. 0xAF */
    char pad0xB0[0x74];
    u8 flag124;                 /* 0x124 stb */
    char pad0x125[0x7];
    s32 unk12C;                 /* 0x12C */
    char pad0x130[0x8];
    f32 q3[8];                  /* 0x138: 0x138/13C/140/144, 0x148/14C/150/154 */
    char pad0x158[0x8];
    f32 q4[4];                  /* 0x160 */
    f32 mass;                   /* 0x170 */
    char pad0x174[0x4];
    f32 moi[3];                 /* 0x178 */
    char pad0x184[0x4];
    f32 f188, f18C, f190, f194, f198, f19C, f1A0, f1A4;
    s32 f1A8;                   /* 0x1A8 */
    s32 wheels;                 /* 0x1AC */
    s32 live;                   /* 0x1B0 */
    f32 maxsteer;               /* 0x1B4 */
    char pad0x1B8[0x8];
    f32 f1C0, f1C4;             /* 0x1C0 */
    char pad0x1C8[0x120];       /* 0x1C8 = FC8C4AC6 entry array, stride 0x88 */
    s32 exitable;               /* 0x2E8 */
    s32 f2EC;                   /* 0x2EC */
    s32 warr;                   /* 0x2F0 */
    f32 eng[2];                 /* 0x2F4, 0x2F8 */
    s32 ecount;                 /* 0x2FC */
    f32 earr[8];                /* 0x300 */
    char pad0x320[0x4];
    f32 f320;                   /* 0x320 */
    char pad0x324[0xFE4];
    s32 f1308;                  /* 0x1308 */
    char pad0x130C[0x4];
    f32 skpos[4];               /* 0x1310 */
    s32 cks1320;                /* 0x1320 */
    s32 cks1328;                /* 0x1328 */
    f32 f132C, f1330;           /* 0x132C, 0x1330 */
    char pad0x1334[0x10];
    s32 skel;                   /* 0x1344 */
    char pad0x1348[0x8];
    s32 phase;                  /* 0x1350 */
} Self_t;

typedef struct { f32 x, y, z; } V3;

/* FC8C4AC6 result entry: 3x Vec3 at 0x00/0x10/0x20 + 2 floats at 0x80/0x84,
   stride 0x88 (mulli rX,rY,0x88 at 0x800BEBD8). */
typedef struct {
    f32 a[3];
    char p0[4];
    f32 b[3];
    char p1[4];
    f32 c[3];
    char p2[0x54];
    f32 out0;                   /* 0x80 */
    f32 out1;                   /* 0x84 */
} Ent_t;

extern s32 lbl_80305EAC;
extern f32 lbl_80298F18[2];
extern f32 lbl_80298F5C;
extern f32 lbl_80298F60;
extern f32 lbl_80298F64;
extern f32 lbl_80298F68;
extern f32 lbl_80298F6C;
extern f64 lbl_80298F70;
extern f32 lbl_80298F78;
extern f32 lbl_80298F7C;
extern f32 lbl_80298F80;
extern f32 lbl_80298F84;
extern f32 lbl_80298F88;
extern f64 lbl_80298F90;

extern s32 ContainsFlag(CStruct *, u32);
extern s32 fn_80128978(s32, u32);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern s32 GetVector(CStruct *, s32, CStruct *, s32);
extern s32 GetStructure_2(CStruct *, s32, s32 *, s32);
extern s32 GetArray(CStruct *, s32, s32 *, s32);
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 GetChecksum_3(void *, u32);
extern s32 fn_8012954C(CStruct *, s32);
extern s32 fn_801294E0(CStruct *, s32);
extern s32 fn_80129528(CStruct *, s32);
extern f32 fn_80129420(CStruct *, s32);
extern void fn_801745B4(s32);
extern void fn_801455F0(f32);
extern void *Mem_Alloc(s32);
extern void fn_8010794C(void *);
extern void fn_800C1AA4(s32, void *, CStruct *);
extern f32 fn_80036304(CStruct *);
extern f32 sqrtf(f32);
extern void fn_8002C8FC(void *, f32);
extern void fn_8002C904(void *, f32, f32, f32);

void fn_800BE854(Self_t *arg0, CStruct *arg1) {
    s32 temp_r30;
    s32 temp_r11;
    s32 count;
    s32 var_r10;
    s32 var_r11;
    s32 var_r25;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;
    s32 temp_r0;
    f32 f10;
    f32 temp_f1;
    f32 var_f31;
    f32 sp18;                  /* 0x18 */
    s32 sp1C;                  /* 0x1C */
    s32 sp20;                  /* 0x20 */
    s32 sp24;                  /* 0x24 */
    s32 sp28;                  /* 0x28 */
    s32 sp2C;                  /* 0x2C */
    f32 sp58;                  /* 0x58 */
    f32 sp60;                  /* 0x60 */
    __ps_t sp8[2];             /* 0x08: the vec4 (r23 = &sp8) */
    Ent_t *ent;
    CStruct *el;
    s32 i;
    s32 n;
    s32 cnt;
    s32 objp;
    f32 sum;
    f32 fs;
    f32 inv;
    s32 i1;
    s32 i2;
    f32 *mr;
    f32 *m0;
    f32 *m1;
    f32 *m2;
    f32 vx, vy, vz, vw;
    f32 len2, k, xx, yy, zz, xy, xz, yz, wx, wy, wz;
    void *wbase;
    s32 wi;
    s32 woff;
    f32 wval;
    f32 *wp;
    s32 wn;
    s32 sidx;
    __ps_t e0, e1, e2, va, vb, vc, acc0, acc1, sv, t0, t1;
    f32 *ef;
    f32 *ef0, *ef1, *ef2;
    V3 *v3;
    f32 *ppos;      /* r17 = ppos   */
    f32 *pq0;       /* r20 = &arg0->q0[0]    */
    f32 *pq1;       /* r22 = &pq1[0]    */
    f32 *pq2;       /* r19 = &arg0->q2[0]    */
    f32 *pq3a;      /* r18 = &arg0->q3[0]    */
    f32 *pq3b;      /* r21 = &arg0->q3[4]    */
    s32 *pcks;      /* r16 = &arg0->cks1328  */
    __ps_t *pro;    /* r25 = lbl_80298F18    */
    __ps_t *ppos2;
    __ps_t *pobj;
    __ps_t *psp;    /* r23 = &sp8[0] */
    __ps_t *psp2;   /* r26 = 2nd web of &sp8[0] */


    /* ---- 0x800BE854: phase counter, debug +2 +1 else 0 ---- */
    if (ContainsFlag(arg1, QB_DEBUG) != 0) {
        var_r11 = arg0->phase + 1;
    } else {
        temp_r30 = ContainsFlag(arg1, QB_UNKNOWN_0xE6B5FCD9);
        if (temp_r30 != 0) {
            var_r11 = arg0->phase + 2;
        } else if (ContainsFlag(arg1, QB_UNKNOWN_0x751DA48B) != 0) {
            arg0->phase = temp_r30;
            goto block_next;
        } else {
            goto block_next;
        }
    }
    arg0->phase = var_r11 % 3;
block_next:
    /* ---- 0x800BE904: bound-penalty quaternion ---- */
    if (fn_80128978(arg1, QB_UNKNOWN_0x93346B8C) != 0) {
        GetFloat(arg1, QB_UNKNOWN_0x93346B8C, &sp18, 0);
        arg0->q4[0] = lbl_80298F5C;
        ef = arg0->q4;
        ef[3] = lbl_80298F60;
        ef[1] = sp18;
        ef[2] = lbl_80298F5C;
    }
    /* ---- mass ---- */
    if (fn_80128978(arg1, QB_MASS) != 0) {
        GetFloat(arg1, QB_MASS, &arg0->mass, 0);
        arg0->mass = lbl_80298F64 / arg0->mass;
    }
    /* ---- moment of inertia ---- */
    if (fn_80128978(arg1, QB_MOMENT_OF_INERTIA) != 0) {
        GetVector(arg1, QB_MOMENT_OF_INERTIA, arg0->moi, 0);
        arg0->moi[0] = lbl_80298F64 / arg0->moi[0];
        arg0->moi[2] = lbl_80298F64 / arg0->moi[2];
        arg0->moi[1] = lbl_80298F64 / arg0->moi[1];
    }
    /* ---- 8 unconditional scalars ---- */
    GetFloat(arg1, QB_UNKNOWN_0x79C3B862, &arg0->f188, 0);
    GetFloat(arg1, QB_UNKNOWN_0xF476273C, &arg0->f18C, 0);
    GetFloat(arg1, QB_UNKNOWN_0x4A23A53C, &arg0->f194, 0);
    GetFloat(arg1, QB_UNKNOWN_0x01DD4890, &arg0->f190, 0);
    GetFloat(arg1, QB_UNKNOWN_0xB9F026ED, &arg0->f198, 0);
    GetFloat(arg1, QB_UNKNOWN_0x8C14709E, &arg0->f19C, 0);
    GetFloat(arg1, QB_UNKNOWN_0x2C91E49B, &arg0->f1A0, 0);
    GetFloat(arg1, QB_UNKNOWN_0x280F0E0B, &arg0->f1A4, 0);
    arg0->f1A8 = ContainsFlag(arg1, QB_UNKNOWN_0x5341806A);
    if (fn_80128978(arg1, QB_MAX_STEERING_ANGLE) != 0) {
        GetFloat(arg1, QB_MAX_STEERING_ANGLE, &arg0->maxsteer, 0);
        arg0->maxsteer = arg0->maxsteer * lbl_80298F68;
    }
    /* retail materialises these 8 base pointers HERE (r23,r22,r17,r16,r20,
       r19,r18,r21 at 0x800BEB18..0x800BEB98) — the scheduler sinks them into
       the call-setup delay slots of the eight GetFloat calls that follow. */
    psp = sp8;
    pq1 = arg0->q1;
    ppos = arg0->pos;
    pcks = &arg0->cks1328;
    pq0 = arg0->q0;
    pq2 = arg0->q2;
    pq3a = arg0->q3;
    pq3b = arg0->q3 + 4;
    GetFloat(arg1, QB_UNKNOWN_0x386837DB, &arg0->f1C0, 0);
    GetFloat(arg1, QB_UNKNOWN_0x469CF79A, &arg0->f1C4, 0);
    arg0->exitable = ContainsFlag(arg1, QB_EXITABLE);
    arg0->f2EC = ContainsFlag(arg1, QB_UNKNOWN_0xAD6C0A46);

    /* ---- FC8C4AC6: 3x3 -> orthonormal frame + accumulate length ---- */
    if (fn_80128978(arg1, QB_UNKNOWN_0xFC8C4AC6) != 0) {
        pro = (__ps_t *)lbl_80298F18;
        psp2 = psp;
        GetArray(arg1, QB_UNKNOWN_0xFC8C4AC6, &sp1C, 1);
        var_f31 = lbl_80298F5C;
        cnt = ((CStruct *)sp1C)->unk0x4;
        var_r28 = cnt - 1;
        if (cnt != 0) {
            ent = (Ent_t *)((char *)arg0 + 0x1C8 + var_r28 * 0x88);
            ef0 = ent->a;
            ef1 = ent->b;
            ef2 = ent->c;
            do {
                el = (CStruct *)fn_8012954C((CStruct *)sp1C, var_r28);
                /* want 0x3AC/0x3B0: `li r4,0` + `bl 0x801294e0` -- the FIRST
                   vector is also a fn_801294E0(p, 0) call (0,1,2), not `el+4`. */
                v3 = (V3 *)((char *)fn_801294E0(el, 0) + 4);
                ef0[0] = v3->x;
                ef0[1] = v3->y;
                ef0[2] = v3->z;
                v3 = (V3 *)((char *)fn_801294E0(el, 1) + 4);
                ef1[0] = v3->x;
                ef1[1] = v3->y;
                ef1[2] = v3->z;
                v3 = (V3 *)((char *)fn_801294E0(el, 2) + 4);
                ef2[0] = v3->x;
                ef2[1] = v3->y;
                ef2[2] = v3->z;
                /* want 0x40C (ps_sub hi) + 0x418 (ps_sub lo): ef1 -= ef0.
                   f11 = psq_l 0(r29) and f10 = psq_l 8(r29) are the ef0 pair. */
                va = *(__ps_t *)ef1 - *(__ps_t *)ef0;
                vb = *(__ps_t *)((char *)ef1 + 8) - *(__ps_t *)((char *)ef0 + 8);
                *(__ps_t *)ef1 = va;
                *(__ps_t *)((char *)ef1 + 8) = vb;
                /* want 0x468 (ps_sub hi) + 0x474 (ps_sub lo): ef2 -= ef0, NOT
                   -= ef1 (f8 = psq_l 0(r29) and f11 = psq_l 8(r29) are ef0).
                   The old body subracted ef1 twice, giving c-b+a instead of
                   the want's c-a. */
                va = *(__ps_t *)ef2 - *(__ps_t *)ef0;
                vb = *(__ps_t *)((char *)ef2 + 8) - *(__ps_t *)((char *)ef0 + 8);
                *(__ps_t *)ef2 = va;
                *(__ps_t *)((char *)ef2 + 8) = vb;
                acc0 = *(__ps_t *)((char *)ef0) + *(__ps_t *)ef2;
                acc1 = *(__ps_t *)((char *)ef0 + 8) + *(__ps_t *)((char *)ef2 + 8);
                t0 = acc0 * *(__ps_t *)lbl_80298F18;
                t1 = acc1 * *(__ps_t *)lbl_80298F18;
                t0 = t0 + acc0 * t0;
                t1 = t1 + acc1 * t1;
                sv = __builtin_ps_sum0(t0 + t0, t0 + t0, t0 + t0);
                sv = __builtin_ps_rsqrte(sv);
                sv = __builtin_ps_res(sv);
                t0 = t0 * sv;
                ent->out0 = (f32)sv;
                var_f31 = var_f31 + (f32)sv;
                ent->out1 = (f32)sv;
                ent -= 1;
                var_r28 -= 1;
            } while (var_r28 != 0);
        }
        fn_801745B4(lbl_80305EAC);
        fn_801455F0((var_f31 / lbl_80298F6C) / (f32)(f64)(s32)cnt - lbl_80298F78);
    }

    /* ---- 1757E572 engine block ---- */
    if (fn_80128978(arg1, QB_ENGINE) != 0) {
        GetStructure_2(arg1, QB_ENGINE, &sp20, 1);
        if (fn_80128978(sp20, QB_UNKNOWN_0x9AA9FAEE) != 0) {
            GetFloat(sp20, QB_UNKNOWN_0x9AA9FAEE, &arg0->eng[0], 0);
            arg0->eng[0] = arg0->eng[0] * lbl_80298F7C;
        }
        if (fn_80128978(sp20, QB_UNKNOWN_0xB2268648) != 0) {
            GetFloat(sp20, QB_UNKNOWN_0xB2268648, &arg0->eng[1], 0);
            arg0->eng[1] = arg0->eng[1] * lbl_80298F7C;
        }
        if (fn_80128978(sp20, QB_UNKNOWN_0x33921583) != 0) {
            GetFloat(sp20, QB_UNKNOWN_0x33921583, &arg0->f320, 0);
            arg0->f320 = arg0->f320 * lbl_80298F80;
        }
        GetFloat(sp20, QB_UNKNOWN_0x94EA6601, &arg0->f1C0, 0);
        GetFloat(sp20, QB_UNKNOWN_0x82BCBB10, &arg0->f1C4, 0);
        var_r29 = 0;
        if (fn_80128978(sp20, QB_UNKNOWN_0xC023FA75) != 0) {
            GetArray(sp20, QB_UNKNOWN_0xC023FA75, &sp24, 1);
            count = ((CStruct *)sp24)->unk0x4;
            arg0->ecount = count;
            if (var_r29 < count) {
                var_r30 = (s32)arg0->earr;
                do {
                    *(f32 *)var_r30 = fn_80129420((CStruct *)sp24, var_r29);
                    var_r30 += 4;
                    var_r29 += 1;
                } while (var_r29 < arg0->ecount);
            }
        }
    }

    /* ---- wheels ---- */
    if (fn_80128978(arg1, QB_WHEELS) != 0) {
        sp28 = NULL;
        GetArray(arg1, QB_WHEELS, &sp28, 1);
        temp_r30 = ((CStruct *)sp28)->unk0x4;
        arg0->wheels = temp_r30;
        if (arg0->warr == 0) {
            var_r29 = temp_r30 - 1;
            var_r28 = (s32)Mem_Alloc((((temp_r30 * 0x10) - temp_r30) << 5) | 8) + 8;
            *(s32 *)((char *)var_r28 - 8) = temp_r30;
            var_r30 = var_r28;
            if (temp_r30 != 0) {
                do {
                    fn_8010794C((void *)(var_r30 + 0x120));
                    var_r30 += 0x1E0;
                    var_r29 -= 1;
                } while (var_r29 != 0);
            }
            arg0->warr = var_r28;
        }
        temp_r30 = arg0->wheels;
        var_r30 = temp_r30 - 1;
        if (temp_r30 != 0) {
            do {
                var_r29 = ((var_r30 * 0x10) - var_r30) << 5;
                fn_800C1AA4((s32)arg0, (void *)(arg0->warr + var_r29),
                           fn_80129528((CStruct *)sp28, var_r30));
                var_r30 -= 1;
            } while (var_r30 != 0);
        }
    }

    /* ---- 371BADFF: apply default wheel to all ---- */
    if (fn_80128978(arg1, QB_UNKNOWN_0x371BADFF) != 0) {
        GetStructure_2(arg1, QB_UNKNOWN_0x371BADFF, &sp2C, 1);
        var_r30 = arg0->wheels - 1;
        temp_r30 = arg0->wheels;
        if (temp_r30 != 0) {
            do {
                var_r29 = ((var_r30 * 0x10) - var_r30) << 5;
                fn_800C1AA4((s32)arg0, (void *)(arg0->warr + var_r29), (CStruct *)sp2C);
                var_r30 -= 1;
            } while (var_r30 != 0);
        }
    }

    /* ---- count live wheels ---- */
    temp_r11 = arg0->wheels;
    arg0->live = 0;
    var_r11 = temp_r11 - 1;
    if (temp_r11 != 0) {
        var_r10 = (((var_r11 * 0x10) - var_r11) << 5) + 0xBC + arg0->warr;
        do {
            temp_r0 = *((s32 *)var_r10);
            var_r10 -= 0x1E0;
            if (temp_r0 != 0) {
                arg0->live += 1;
            }
            var_r11 -= 1;
        } while (var_r11 != 0);
    }

    /* ---- contact-normal frame from the 3x3 inertia block at obj+0x78 ---- */
    objp = arg0->obj;
    mr = (f32 *)((char *)objp + 0x78);
    sum = mr[0] + mr[5] + mr[10];
    if (sum > lbl_80298F5C) {
        fs = sqrtf(sum + lbl_80298F60);
        var_f31 = fs;
        inv = lbl_80298F84 / fs;
        temp_f1 = fs * lbl_80298F84;
        fn_8002C8FC((void *)psp, temp_f1);
        fn_8002C904((void *)psp,
                    (mr[9] - mr[6]) * inv,
                    (mr[2] - mr[8]) * inv,
                    (mr[4] - mr[1]) * inv);
    } else {
        var_r25 = 0;
        if (mr[5] > mr[0]) {
            var_r25 = 1;
        }
        if (mr[10] > mr[var_r25 * 5]) {
            var_r25 = 2;
        }
        i1 = (var_r25 + 1) % 3;
        i2 = (i1 + 1) % 3;
        m0 = mr + var_r25 * 5;
        m1 = mr + i1 * 5;
        m2 = mr + i2 * 5;
        temp_f1 = sqrtf(m0[var_r25] - (m1[var_r25] + m2[var_r25]) + lbl_80298F60);
        var_f31 = temp_f1;
        inv = lbl_80298F84 / temp_f1;
        *(f32 *)((char *)psp + var_r25 * 4) = temp_f1 * lbl_80298F84;
        *(f32 *)((char *)psp + i1 * 4) = (m0[i1] + m1[i2]) * inv;
        *(f32 *)((char *)psp + i2 * 4) = (m0[i2] + m2[i1]) * inv;
        *(f32 *)((char *)psp + 0x0C) = (m2[i1] - m1[i2]) * inv;
    }
    /* vec4 -> q1 as two pair copies (psq_l/psq_st at 0x800BF314..0x800BF32C) */
    *(__ps_t *)&pq1[0] = sp8[0];
    *(__ps_t *)&pq1[2] = sp8[1];

    /* ---- renormalize ---- */
    temp_f1 = sqrtf(fn_80036304((CStruct *)&pq1[0]));
    var_f31 = lbl_80298F5C;
    if (temp_f1 > var_f31) {
        sp58 = lbl_80298F60 / temp_f1;
        sv = *(__ps_t *)&sp58;
        *(__ps_t *)&pq1[0] = __builtin_ps_muls0(*(__ps_t *)&pq1[0], sv);
        *(__ps_t *)&pq1[2] = __builtin_ps_muls0(*(__ps_t *)&pq1[2], sv);
    }

    /* ---- orientation override -> inverse-scale rotation matrix ---- */
    if (fn_80128978(arg1, QB_SAVE) != 0) {
        *(f32 *)&psp[0] = var_f31;
        *(f32 *)((char *)psp + 4) = var_f31;
        *(f32 *)((char *)psp + 8) = var_f31;
        *(f32 *)((char *)psp + 0x0C) = lbl_80298F60;
        GetVector(arg1, QB_ORIENTATION, (CStruct *)psp, 0);
        pq1[0] = *(f32 *)&psp[0];
        pq1[1] = *(f32 *)((char *)psp + 4);
        pq1[2] = *(f32 *)((char *)psp + 8);
        temp_f1 = sqrtf(fn_80036304((CStruct *)&pq1[0]));
        if (temp_f1 > var_f31) {
            sp60 = lbl_80298F60 / temp_f1;
            sv = *(__ps_t *)&sp60;
            *(__ps_t *)&pq1[0] = __builtin_ps_muls0(*(__ps_t *)&pq1[0], sv);
            *(__ps_t *)&pq1[2] = __builtin_ps_muls0(*(__ps_t *)&pq1[2], sv);
        }
        vx = pq1[0];
        vy = pq1[1];
        vz = pq1[2];
        vw = pq1[3];
        len2 = (vy * vy) + ((vz * vz) + ((vx * vx) + (vw * vw)));
        if (len2 > var_f31) {
            k = lbl_80298F88 / len2;
        } else {
            k = lbl_80298F5C;
        }
        xx = vx * (vx * k);
        yy = vy * (vy * k);
        zz = vz * (vz * k);
        xy = vx * (vy * k);
        xz = vx * (vz * k);
        yz = vy * (vz * k);
        wx = vw * (vx * k);
        wy = vw * (vy * k);
        wz = vw * (vz * k);
        m0 = &arg0->mat[0];
        m1 = &arg0->mat[4];
        m2 = &arg0->mat[8];
        m0[1] = xy - wz;
        m0[2] = xz + wy;
        m2[1] = yz - wx;
        m0[0] = lbl_80298F60 - (yy + zz);
        m1[0] = xy + wz;
        m1[1] = yz + wx;
        m2[2] = lbl_80298F60 - (xx + zz);
        m2[3] = lbl_80298F60 - (xx + yy);
        m2[0] = xz - wy;
        arg0->mat[12] = lbl_80298F5C;
        m2 = &arg0->mat[12];
        m2[3] = lbl_80298F60;
        m2[2] = lbl_80298F5C;
        m2[1] = lbl_80298F5C;
    }

    /* ---- publish the matrix to obj (0x78 and 0xD0) as 8 pair copies ---- */
    {
        f32 *d0 = (f32 *)((char *)arg0->obj + 0x78);
        f32 *d1 = (f32 *)((char *)arg0->obj + 0xD0);
        __ps_t *src = (__ps_t *)arg0->mat;
        __ps_t *t0 = (__ps_t *)d0;
        __ps_t *t1 = (__ps_t *)d1;
        t0[0] = src[0];
        t0[1] = src[1];
        t0[2] = src[2];
        t0[3] = src[3];
        t0[4] = src[4];
        t0[5] = src[5];
        t0[6] = src[6];
        t0[7] = src[7];
        t1[0] = src[0];
        t1[1] = src[1];
        t1[2] = src[2];
        t1[3] = src[3];
        t1[4] = src[4];
        t1[5] = src[5];
        t1[6] = src[6];
        t1[7] = src[7];
    }

    /* ---- QB_POS into the object, and read-back ---- */
    *(__ps_t *)ppos = *(__ps_t *)((char *)arg0->obj + 0x58);
    if (fn_80128978(arg1, QB_POS) != 0) {
        GetVector(arg1, QB_POS, ppos, 0);
        *(__ps_t *)((char *)arg0->obj + 0x58) = *(__ps_t *)ppos;
    }

    /* ---- f1308 latch ---- */
    temp_r30 = 0;
    if (arg0->f1308 != 0) {
        temp_r30 = 1;
    } else if (ContainsFlag(arg1, QB_UNKNOWN_0x2ED67657) != 0) {
        temp_r30 = 1;
    }
    arg0->f1308 = temp_r30;
    if (ContainsFlag(arg1, QB_UNKNOWN_0x2ED67657) != 0) {
        GetVector(arg1, QB_SKATER_POS, arg0->skpos, 1);
        GetChecksum_2(arg1, QB_UNKNOWN_0xDA75A33E, &arg0->cks1320, 1);
    }
    GetChecksum_2(arg1, QB_SOUNDS, pcks, 0);

    /* ---- 4 identity quaternions (r20/r19/r18/r21 base pointers) ---- */
    pq0[0] = lbl_80298F5C;
    ef = pq0;
    ef[3] = lbl_80298F60;
    ef[1] = lbl_80298F5C;
    ef[2] = lbl_80298F5C;
    pq2[0] = lbl_80298F5C;
    ef = pq2;
    ef[3] = lbl_80298F60;
    ef[1] = lbl_80298F5C;
    ef[2] = lbl_80298F5C;
    pq3a[0] = lbl_80298F5C;
    ef = pq3a;
    ef[3] = lbl_80298F60;
    ef[1] = lbl_80298F5C;
    ef[2] = lbl_80298F5C;
    pq3b[0] = lbl_80298F5C;
    ef = pq3b;
    ef[3] = lbl_80298F60;
    ef[1] = lbl_80298F5C;
    ef[2] = lbl_80298F5C;

    /* ---- per-wheel reset + 10x scaled fill ---- */
    count = arg0->wheels;
    if (count != 0) {
        sidx = count - 1;
        f10 = lbl_80298F64;
        do {
            wbase = (void *)(arg0->warr + (((sidx * 0x10) - sidx) << 5));
            woff = 0;
            *((f32 *)wbase + 1) = lbl_80298F60;
            *((f32 *)wbase + 3) = lbl_80298F5C;
            *((f32 *)wbase + 2) = lbl_80298F5C;
            *((f32 *)wbase + 0) = *((f32 *)wbase + 0x30);
            *((f32 *)wbase + 4) = lbl_80298F5C;
            *((f32 *)wbase + 5) = lbl_80298F5C;
            *((f32 *)wbase + 0x29) = lbl_80298F5C;
            wp = (f32 *)((char *)wbase + 0x60);
            wn = 0xA;
            do {
                wval = (f10 / arg0->mass) / (f32)(f64)(u32)arg0->wheels;
                *wp = wval;
                wp -= 1;
                wn -= 1;
            } while (wn != 0);
            sidx -= 1;
        } while (sidx != -1);
    }
    arg0->flag124 = 0;
    arg0->f1330 = lbl_80298F5C;
    arg0->f132C = lbl_80298F60;
    arg0->unk12C = 0;
    arg0->skel = GetChecksum_3((void *)arg0->obj, QB_SKELETON);
}
