// UPDATED 2026-09-13 (c): extended flag matrix (recipe 49) found `-O1` -> 7.14% to 17.78%.
// WIP DRAFT (non-matching) — hand-rebuilt SNAPS paired-single reconstruction.
// family=m2c range=0x801792D4-0x80179654 size=896B
// PARKED: best-match compiling body, 7.1% masked (ps_diff.py 16/224, 888B vs
// 896B; test_wip_drafts --extra-cflags "-mps-float" = DIFF) after exhausting
// ~15 shapes. doc06 M5.0q correction applied: "FIVE
// xo5=8 words unemittable" was WRONG — all five decode as X-form ps_mr
// (XO10=72): 0x10005090 f0,f10 / 0x11604890 f11,f0 / 0x11a00090 f13,f0 /
// 0x11200090 f9,f0 / 0x10004890 f0,f9 — plain pair moves. EVERY opcode-4
// word in the function is emittable (probe-verified operand maps:
// __builtin_ps_madd(a,b,c) -> enc(D,A,B,C)=(a,c,b), i.e. multiplier SECOND;
// muls0(x,m) enc C=m; sum0(x,x,x)). Frame template EXACT (stwu -0x98,
// stmw r25,0x7c, no FPR saves) via f32-array FR struct incl. the est1
// pair+1.0f overlap group @[r1+0x58] (1.0f overwrites lane1 BEFORE the
// psq_l reload -> muls lane1 multiplier = 1.0) and shared cvt union @0x70
// reused by all SIX fctiwz dances (inline asm per §6ac-3; plain casts take
// anon slots + break frame).
// REMAINING WALLS (retry angles):
// 1. Saved-reg role permutation: want homes v/arg0->r31, *(arg0)->r30,
//    mgr/total->r29 (web REUSE across fn_80219698!), &lbl_8029F480->r28,
//    &out38->r27, chk->r26, derived r30+8->r25 (scratch-birth r11 + mr).
//    GOT mirrors {arg0,mgr} and {chk,derived} swapped. EXHAUSTED: creation-
//    order permutations (mgr-before/after obj-load; mgr-before/after v),
//    mgr "+r" barrier (keeps the prologue lwz lbl_80305F9C but does NOT flip
//    the home), sched flag ladder. UNTRIED: chk pin-a-copy §70-130a
//    (register s32 chkp __asm__("r26")), full-web pinning, two-reg web-split
//    (§6y-134-style split ctx web).
//    NOTE want recycles r31: arg0 -> fn_8013E034 ret (if-path) -> obj;
//    model v as ONE reassigned variable (done).
// 2. Block-1 scheduler interleave: want sprinkles address-setup insns
//    (addi r10/addi r11/lis/addi rod/mr r25) BETWEEN the volatile pair
//    stores; got groups them. Modeled pp=&sp8[0] (r10 covers sp8+sp10
//    stores/reloads) + t11/r25 split via barrier — placement still off.
// 3. dv/d0 dual-type view ("=f"/"0" empty-asm binding §6ag-3) ICEs cc1
//    post-reload in this context (worked on simpler fns) — worked around
//    with typed-asm ps_mr/ps_rsqrte (f32 view d0 + __ps_t eraw), which
//    emits want's exact [ps_mr][fcmpu][rsqrte] triple.
// Structure (want disasm) + full body below are otherwise faithful:
//   chk = fn_8017471C(arg0->18, (s8)*(r30->38)); !chk -> return 4.
// Structure (want disasm):
//   chk = fn_8017471C(arg0->18, (s8)*(r30->38)); !chk -> return 4.
//   PS BLOCK 1 @0x80179314: stack-pair traffic (sp8/sp10 store+reload),
//   dist2 = sum0(madd(P,P, merge00(P*P,{0,0}))); > 0.0f -> rsqrte normalize,
//   est pair -> sp58, P*est -> sp20, scaled -> sp18 (overwrites).
//   total = *(r30); if (!fn_80219698(lbl_80305F9C)): out struct @[r1+0x38]
//   ([0x40]=&lbl_8029F480, [0x3C]=0), cur = fn_8013E034(cur->C, &out),
//   extra = fn_8013F74C() ? 0 : cur->20B4, [0x40]=ptr again, total += extra.
//   scale = §6ag-5 union dance (f64)total - lbl_802A9028 / lbl_802A9030.
//   PS BLOCK 2 @0x8017942C: sp18/sp20 *= scale.hi -> sp48/sp50,
//   sp30 += scaled-sp20 -> sp30, sp28 += scaled-sp18 -> sp28.
//   obj = CStruct_ctor(CStruct_new(8)) [nested idiom -> early li r3,8];
//   AddChecksum x2; six fctiwz (s32) lane casts -> AddInteger x6 (+QB_RADIUS
//   direct int); fn_8012772C(float-in-f1); fn_801279A0 x2 w/ psq pair copies
//   into @[r1+0x38]; signature 0xD039432C select -> Script_RunScript(hash,obj,
//   chk,0,0); guarded CStruct_delete(obj,3); return 1.
// extra_cflags: -mps-float -O1
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_8029F480[];
extern s32 lbl_80305F9C;
extern f32 lbl_802A9020;
extern f32 lbl_802A9024;
extern f64 lbl_802A9028;
extern f32 lbl_802A9030;
extern char lbl_802A8F88[];
void *fn_8017471C(s32, s32);
s32 fn_80219698(CStruct *);
void *fn_8013E034(s32, CStruct *);
s32 fn_8013F74C(void);
s32 CStruct_new(s32);
void *CStruct_ctor(void *);
void AddChecksum(CStruct *, s32, s32);
void AddInteger(CStruct *, s32, s32);
void fn_8012772C(CStruct *, s32, f32);
void fn_801279A0(CStruct *, s32, CStruct *);
void Script_RunScript(s32, void *, s32, s32, s32);
void CStruct_delete(CStruct *, s32);

typedef union { __ps_t p; f32 w[2]; } S;

typedef struct {
    volatile f32 sp8[2];     /* r1+0x08 */
    volatile f32 sp10[2];    /* r1+0x10 */
    volatile f32 sp18[2];    /* r1+0x18 */
    volatile f32 sp20[2];    /* r1+0x20 */
    volatile f32 sp28[2];    /* r1+0x28 */
    volatile f32 sp30[2];    /* r1+0x30 */
    f32 out[4];     /* r1+0x38 (fn_8013E034 buf / fn_801279A0 arg) */
    volatile f32 sp48[2];   /* r1+0x48 */
    volatile f32 sp50[2];   /* r1+0x50 */
    volatile f32 est1[2];   /* r1+0x58: [0]=est.hi, [1]=lane1 overwritten by 1.0f */
    volatile f32 sp60[2];   /* r1+0x60 */
    f32 hole68[2];          /* r1+0x68 */
    union { u32 w[2]; volatile f64 d; } cvt;  /* r1+0x70 */
} FR;

s32 fn_801792D4(Unk_DB0E2BAB *arg0) {
    FR fr;
    Unk_BFBBA303 *v;
    s32 mgr;
    Unk_EA529D06 *r25p;
    s32 chk;
    s32 extra;
    s32 total;
    f32 scale;
    __ps_t pP;
    __ps_t pQ;
    __ps_t pc;
    __ps_t ca;
    __ps_t cb;
    __ps_t q2;
    __ps_t rod;
    __ps_t sq;
    __ps_t mg;
    __ps_t acc;
    __ps_t dv;
    f32 d0;
    __ps_t eraw;
    __ps_t estc;
    __ps_t scl;
    __ps_t nrm;
    __ps_t a11;
    __ps_t a13;
    __ps_t a10;
    __ps_t a12;
    __ps_t scpair;

    v = arg0;
    {
        void *r30 = *((void * *)&arg0->unk0x0);
        mgr = lbl_80305F9C;
        __asm__("" : "+r"(mgr));
        chk = (s32)fn_8017471C(arg0->unk0x18,
                               (s8) * (s8 *)((char *)r30 + (s32)0x38));
        if (chk == 0) {
            return 4;
        }
        /* ---- PS BLOCK 1 ---- */
        {
            volatile f32 *pp;
            void *t11;
            pP = *((volatile __ps_t *)&((Unk_5F85C510 *)r30)->unk0x18);
            pp = &fr.sp8[0];
            t11 = (char *)r30 + (s32)8;
            __asm__("" : "+r"(t11));
            r25p = t11;
            *(__ps_t *)pp = pP;
            pQ = *((volatile __ps_t *)&((Unk_5F85C510 *)r30)->unk0x20);
            *(__ps_t *)&pp[2] = pQ;
            *(__ps_t *)&fr.sp28[0] = *((volatile __ps_t *)&((Unk_390DF891 *)r30)->unk0x8);
            pc = *(__ps_t *)pp;
            __asm__ __volatile__("ps_mr %0, %1" : "=f"(ca) : "f"(pc));
            *(volatile __ps_t *)&fr.sp30[0] = *((volatile __ps_t *)&((Unk_EA529D06 *)t11)->unk0x8);
            *(__ps_t *)&fr.sp18[0] = ca;
            q2 = *(__ps_t *)&pp[2];
            rod = *(__ps_t *)&lbl_802A8F88[0];
            *(__ps_t *)&fr.sp20[0] = q2;
        }
        __asm__ __volatile__("ps_mr %0, %1" : "=f"(cb) : "f"(ca));
        sq = __builtin_ps_mul(cb, cb);
        mg = __builtin_ps_merge00(sq, rod);
        acc = __builtin_ps_madd(pc, mg, pc);
        {
            __ps_t dst2 = __builtin_ps_sum0(acc, acc, acc);
            __asm__ __volatile__("ps_mr %0, %1" : "=f"(d0) : "f"(dst2));
            if (d0 > lbl_802A9020) {
                __asm__ __volatile__("ps_rsqrte %0, %1" : "=f"(eraw) : "f"(d0));
                __asm__ __volatile__("ps_mr %0, %1" : "=f"(estc) : "f"(eraw));
                scl = __builtin_ps_muls0(pc, eraw);
                *(volatile __ps_t *)&fr.est1[0] = estc;
                fr.est1[1] = lbl_802A9024;
                *(volatile __ps_t *)&fr.sp18[0] = scl;
                nrm = __builtin_ps_mul(ca, *(volatile __ps_t *)&fr.est1[0]);
                *(volatile __ps_t *)&fr.sp20[0] = nrm;
            }
        }
        /* ---- count / manager ---- */
        total = ((Unk_390DF891 *)r30)->unk0x0;
        if (fn_80219698(mgr) == 0) {
            *(s32 *)((char *)&fr.out[0] + 8) = (s32)lbl_8029F480;
            *(s32 *)((char *)&fr.out[0] + 4) = 0;
            v = fn_8013E034(v->unk0xC, &fr.out[0]);
            if (fn_8013F74C() == 0) {
                extra = v->unk0x20B4;
            } else {
                extra = 0;
            }
            *(s32 *)((char *)&fr.out[0] + 8) = (s32)lbl_8029F480;
            total += extra;
        }
        /* ---- scale dance (§6ag-5) ---- */
        fr.cvt.w[1] = (u32)total;
        fr.cvt.w[0] = QB_INT_TO_DOUBLE_BIAS;
        scale = (f32)((fr.cvt.d - lbl_802A9028) / lbl_802A9030);
        /* ---- PS BLOCK 2 ---- */
        a11 = *(volatile __ps_t *)&fr.sp18[0];
        a13 = *(volatile __ps_t *)&fr.sp20[0];
        a10 = *(volatile __ps_t *)&fr.sp28[0];
        a12 = *(volatile __ps_t *)&fr.sp30[0];
        fr.sp60[0] = scale;
        scpair = *(volatile __ps_t *)&fr.sp60[0];
        a11 = __builtin_ps_muls0(a11, scpair);
        a13 = __builtin_ps_muls0(a13, scpair);
        *(volatile __ps_t *)&fr.sp48[0] = a11;
        a12 = __builtin_ps_add(a12, a13);
        *(volatile __ps_t *)&fr.sp50[0] = a13;
        a10 = __builtin_ps_add(a10, a11);
        *(volatile __ps_t *)&fr.sp30[0] = a12;
        *(volatile __ps_t *)&fr.sp28[0] = a10;
        /* ---- object build ---- */
        {
            void *obj;
            v = CStruct_ctor((void *)CStruct_new(8));
            obj = v;
            AddChecksum(obj, QB_OWNER_ID, (s8) * (s8 *)((char *)r30 + (s32)0x38));
            AddChecksum(obj, QB_AMMO_TYPE, ((Unk_390DF891 *)r30)->unk0x2C);
            { __asm__ __volatile__("fctiwz 13, %0\n\tstfd 13, %1" :: "f"(fr.sp28[0]), "m"(fr.cvt.d) : "fr13"); AddInteger(obj, QB_X, (s32)fr.cvt.w[1]); }
            { __asm__ __volatile__("fctiwz 13, %0\n\tstfd 13, %1" :: "f"(fr.sp28[1]), "m"(fr.cvt.d) : "fr13"); AddInteger(obj, QB_Y, (s32)fr.cvt.w[1]); }
            { __asm__ __volatile__("fctiwz 13, %0\n\tstfd 13, %1" :: "f"(fr.sp30[0]), "m"(fr.cvt.d) : "fr13"); AddInteger(obj, QB_Z, (s32)fr.cvt.w[1]); }
            { f32 fv = *((f32 *)&((Unk_5F85C510 *)r30)->unk0x18); __asm__ __volatile__("fctiwz 13, %0\n\tstfd 13, %1" :: "f"(fv), "m"(fr.cvt.d) : "fr13"); AddInteger(obj, QB_SCALED_X, (s32)fr.cvt.w[1]); }
            { f32 fv = ((Unk_390DF891 *)r30)->unk0x1C; __asm__ __volatile__("fctiwz 13, %0\n\tstfd 13, %1" :: "f"(fv), "m"(fr.cvt.d) : "fr13"); AddInteger(obj, QB_SCALED_Y, (s32)fr.cvt.w[1]); }
            { f32 fv = ((Unk_5F85C510 *)r30)->unk0x20; __asm__ __volatile__("fctiwz 13, %0\n\tstfd 13, %1" :: "f"(fv), "m"(fr.cvt.d) : "fr13"); AddInteger(obj, QB_SCALED_Z, (s32)fr.cvt.w[1]); }
            AddInteger(obj, QB_RADIUS, ((Unk_390DF891 *)r30)->unk0x30);
            fn_8012772C(obj, QB_SCALE, ((Unk_390DF891 *)r30)->unk0x34);
            *(__ps_t *)&fr.out[0] = *((__ps_t *)&((Unk_390DF891 *)r30)->unk0x8);
            *(__ps_t *)&fr.out[4] = r25p->unk0x8;
            fn_801279A0(obj, QB_POS, &fr.out[0]);
            *(__ps_t *)&fr.out[0] = *((__ps_t *)&((Unk_5F85C510 *)r30)->unk0x18);
            *(__ps_t *)&fr.out[4] = *((__ps_t *)&((Unk_5F85C510 *)r30)->unk0x20);
            fn_801279A0(obj, QB_VEL, &fr.out[0]);
            if (((Unk_390DF891 *)r30)->unk0x28 == (s32)QB_FIREBALL) {
                Script_RunScript(QB_CLIENTLAUNCHFIREBALL, obj, chk, 0, 0);
            } else {
                Script_RunScript(QB_CLIENTLAUNCHPROJECTILE, obj, chk, 0, 0);
            }
            if (obj != NULL) {
                CStruct_delete(obj, 3);
            }
        }
    }
    return 1;
}
