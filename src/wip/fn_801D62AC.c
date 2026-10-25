// WIP DRAFT (non-matching) — hand-rebuilt from disasm (m2c husk had statics-DCE'd body)
// REFRESHED 2026-10-07 (FPR-pin RETARGET sweep): 35.5705% -> 36.2416%
//   the `nv` pin was retargeted fr31 -> fr0 (nothing else touched).  New axis:
//   fr-pin REMOVAL had been swept, retargeting had not.  AGENTS-recipes §6hk.
// family=m2c range=0x801D62AC-0x801D6500 size=596B
// extra_cflags: -mps-float
//
// PARKED 35%: head/guard/first-eq-chain/muls-chain byte-exact; resisted:
//  - COMPARE IDIOM CRACKED: want [fcmpu][cror cr0un,cr0eq,cr0lt][bns->normalize]
//    comes from `if (!(nv <= k90)) {normalize} else {clamp}` — but ngccc places
//    THEN(normalize) at fall-through while want has it at the BRANCH TARGET
//    (clamp falls through). Swapping arms changes the cror encoding. Remaining
//    lever: find a source shape that keeps the !(<=) expansion AND puts the
//    normalize block out-of-line (§6ae-5 class).
//  - nv computation interleave: want [fmuls f1,f1,f0][lfs f30 const][lfs f0
//    arg0->90][fmuls][fsubs f31,f0,f1][stfs] — GCC reorders the two fmuls vs
//    the lfs's under every statement order tried.
//  - &v18 cached into r30 across its two call sites (addi r30,r1,0x18 + mr r3)
//    where want emits fresh addi per site; sc pair read wants load+ps_mr f11,f0
//    feeding BOTH ps_madds0 (single-web coalesces; barrier gives memory reload).
//  - frame: want 0x60 with stmw@0x48 (8-byte FPR quirk gap); dummy/pads shift
//    slots instead of opening the gap at 0x40.
// Structure: guard arg0->90 != lbl_802AD4E8; eq-chain arg0->80..8C == 70..7C
//   (mfcr/rlwinm idiom) -> reset 90 or decay 90 -= fn_8012570C(0xD8120182,1)
//   * *(arg0+0x94) * lbl_802AD4EC; if new 90 > const: v18.s28=nv;
//   fn_8002B8E4(&v18) (dead-arg proto, real body blr); sc=[nv,_] pair;
//   d = pos_hi-lo pairs @112..143; d = madds(d, base, sc) stored q18; 
//   fn_8002B8E8(sp8, q18) copies pairs; dot = madd(p0²,p1²)+sum0;
//   if dot.hi > const: len=rsqrte(dot), arg0->60=p0*len lane0,
//   s30=[len,lbl_802AD4F0], arg0->68=s30²; else clamp-copy 78-pair->68,
//   70-pair->60 and 90=const. Second eq-chain 30..3C==60..6C -> copy pairs
//   60/68->30/38, fn_80004518(arg0+0x20,1), p20(arg0+0x20)[0/1]=obj+120/128
//   then overwritten by obj+152/160 (both kept).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "dolphin/SN_PS.h"
#include "structs.h"

extern f32 fn_8012570C(s32, s32);
extern void fn_8002B8E4(void *);
extern void fn_8002B8E8(__ps_t *, __ps_t *);
extern void fn_80004518(s32, s32);
extern f32 lbl_802AD4E8;
extern f32 lbl_802AD4EC;
extern f32 lbl_802AD4F0;

void fn_801D62AC(CStruct *arg0) {
    __ps_t sp8[2];
    struct {
        __ps_t q18[2];
        SN_PS_type s28;
        SN_PS_type s30;
    } v18;
    volatile double _dummy;
    register f32 k90 __asm__("fr30");
    register f32 nv __asm__("fr0");
    SN_PS_type e8u;
    s32 var_r0;
    __ps_t t11;
    __ps_t t12;

    if (arg0->unk0x90 != lbl_802AD4E8) {
        char *b80 = (char *)arg0 + 0x80;
        var_r0 = ((((Unk_59AB5482_2 *)b80)->unk0x0 == *((f32 *)&arg0->unk0x70)) &&
                  (((Unk_59AB5482_2 *)b80)->unk0x4 == *((f32 *)&arg0->unk0x74)) &&
                  (((Unk_5EF41E38 *)b80)->unk0x8 == *((f32 *)&arg0->unk0x78)) &&
                  (((Unk_59AB5482_2 *)b80)->unk0xC == *((f32 *)&arg0->unk0x7C)));
        if (var_r0 != 0) {
            arg0->unk0x90 = lbl_802AD4E8;
        } else {
            nv = arg0->unk0x90 - fn_8012570C(QB_NORMAL_LERP_SPEED, 1) * *((f32 *)&arg0->unk0x94) * lbl_802AD4EC;
            arg0->unk0x90 = nv;
            k90 = lbl_802AD4E8;
            if (!(nv <= k90)) {
                /* normalize path */
                __ps_t sc;
                __ps_t sc2;
                __ps_t d0;
                __ps_t d1;
                __ps_t o0;
                __ps_t p0;
                __ps_t p1;
                __ps_t p1b;
                SN_PS_type dot;

                v18.s28.flt.hi = nv;
                fn_8002B8E4(&v18);
                sc = v18.s28.ps;
                sc2 = sc;
                __asm__ volatile("" : "+f"(sc2));
                t12 = ((__ps_t *)arg0)[15];
                t11 = ((__ps_t *)arg0)[14];
                d1 = ((__ps_t *)arg0)[16];
                d0 = ((__ps_t *)arg0)[17];
                d1 = ps_sub(d1, t11);
                d0 = ps_sub(d0, t12);
                d0 = ps_madds0(d0, t12, sc2);
                d1 = ps_madds0(d1, t11, sc2);
                v18.q18[0] = d1;
                v18.q18[1] = d0;
                fn_8002B8E8((__ps_t *)sp8, (__ps_t *)&v18.q18[0]);
                p0 = ((__ps_t *)sp8)[0];
                p1 = ((__ps_t *)sp8)[1];
                p1b = ((__ps_t *)sp8)[1];
                ((__ps_t *)arg0)[12] = p0;
                ((__ps_t *)arg0)[13] = p1;
                p1b = ps_mul(p1b, p1b);
                o0 = ps_madd(p0, p1b, p0);
                o0 = ps_sum0(o0, o0, o0);
                dot.ps = o0;
                if (dot.flt.hi > k90) {
                    __ps_t scaled;

                    dot.ps = ps_rsqrte(dot.ps);
                    scaled = ps_muls0(p0, dot.ps);
                    ((__ps_t *)arg0)[12] = scaled;
                    v18.s30.flt.hi = dot.flt.hi;
                    v18.s30.flt.lo = lbl_802AD4F0;
                    o0 = ps_mul(v18.s30.ps, v18.s30.ps);
                    ((__ps_t *)arg0)[13] = o0;
                }
            } else {
                ((__ps_t *)arg0)[13] = ((__ps_t *)arg0)[15];
                ((__ps_t *)arg0)[12] = ((__ps_t *)arg0)[14];
                arg0->unk0x90 = k90;
            }
        }
    }
    /* second eq-chain block */
    {
    char *b30 = (char *)arg0 + 0x30;
    var_r0 = ((((Unk_59AB5482_2 *)b30)->unk0x0 == *((f32 *)&arg0->unk0x60)) &&
              (((Unk_59AB5482_2 *)b30)->unk0x4 == *((f32 *)&arg0->unk0x64)) &&
              (((Unk_5EF41E38 *)b30)->unk0x8 == *((f32 *)&arg0->unk0x68)) &&
              (((Unk_59AB5482_2 *)b30)->unk0xC == *((f32 *)&arg0->unk0x6C)));
    if (var_r0 == 0) {
        __ps_t *p20;
        void *obj;

        ((__ps_t *)arg0)[6] = ((__ps_t *)arg0)[12];
        ((__ps_t *)arg0)[7] = ((__ps_t *)arg0)[13];
        fn_80004518((s32)(char *)arg0 + 0x20, 1);
        obj = *((void * *)&arg0->unk0xC);
        p20 = (__ps_t *)((char *)arg0 + 0x20);
        p20[0] = ((Unk_130D31C8 *)obj)->unk0x78;
        p20[1] = ((Unk_130D31C8 *)obj)->unk0x80;
        p20[0] = ((Unk_130D31C8 *)obj)->unk0x98;
        p20[1] = ((Unk_130D31C8 *)obj)->unk0xA0;
        }
    }
}
