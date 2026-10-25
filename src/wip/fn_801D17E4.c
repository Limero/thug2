// PARKED 24.8% (31/125): full semantic rebuild done; all PS ops decoded+emitted
// REVERTED 2026-10-07: the FPR-pin retarget swept k29 fr29 -> fr1 (+3.1%)
//   but it broke SIZE-EXACTNESS (508B == symbol -> 504B), so the gain is an
//   alignment artifact, not progress.  Pin restored to fr29.  AGENTS-recipes §6hk.
// (ps_mul/merge00/madd/sum0/rsqrte/res/abs/merge01/muls0 via builtins). Resisting:
// (1) want's [lfs f0,sp8][fmr f30,f0] two-step lane read - every form (plain copy,
// "+f" barriers, volatile read, "=f" asm wedge, explicit lfs-asm) either folds to a
// direct load into pinned f30 or reorders the whole entry block; (2) frame 8B
// sensitivity (pad 24 vs 32 flips smu slot); (3) kv copy-pair (lfs f9+fmr f13)
// needs an asm "=f" wedge that then perturbs middle-block FPR coloring.
// Body/control-flow/calls otherwise aligned modulo the 2-insn cascade.
// family=m2c range=0x801D17E4-0x801D19E0 size=508B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 31.5% ([3]rev->31.5%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// FLAG: -mps-float -Os
extern char lbl_802AD278[];
extern f32 lbl_802AD3EC;
extern f32 lbl_802AD3F0;
extern f32 lbl_802AD3F4;
extern f32 lbl_802AD3F8;
extern f32 fn_801417B8(CScript *, s32);
extern f32 fn_8012570C(s32, s32);
extern f32 fn_8014030C(s32, s32, Unk_FFAD6788 *);
void fn_801D19E0(void *);
typedef union {
    __ps_t ps;
    f32 f[2];
} psu_t;

void fn_801D17E4(Unk_17FD7108 *arg0) {
    Unk_C7FCFFAB *o1;
    Unk_548A6C04 *o2;
    char *o3;
    Unk_548A6C04 *ob;
    Unk_C7FCFFAB *ot;
    struct {
        psu_t s8;
        psu_t s10;
        psu_t s18;
        char _p[24];
    } fr;
    register f32 k29 __asm__("fr29");
    register f32 s28 __asm__("fr28");
    register f32 d30 __asm__("fr30");
    register f32 v31 __asm__("fr31");
    f32 f1v;
    f32 t;
    f32 delta;
    f32 tmpd;
    f32 kv;
    f32 kvc;
    psu_t smu;

    k29 = lbl_802AD3EC;
    o1 = arg0->unk0xC;
    s28 = o1->unk0xBC;
    o1->unk0xBC = k29;
    o2 = arg0->unk0xC;
    {
        __ps_t z = *(__ps_t *)&lbl_802AD278;
        __ps_t a = o2->unk0xC0;
        __ps_t b = o2->unk0xB8;
        __ps_t sq = __builtin_ps_mul(a, a);
        __ps_t mg = __builtin_ps_merge00(sq, z);
        __ps_t md = __builtin_ps_madd(b, b, mg);
        md = __builtin_ps_sum0(md, md, md);
        md = __builtin_ps_rsqrte(md);
        md = __builtin_ps_res(md);
        fr.s8.ps = md;
    }
    tmpd = fr.s8.f[0];
    d30 = tmpd;
    v31 = fn_801417B8((s32)o2, QB_SKATER_MAX_MAX_SPEED_STAT);
    o3 = arg0->unk0xC;
    f1v = fn_801417B8((s32)o3, QB_SKATER_MAX_SPEED_STAT);
    t = arg0->unk0x3B8;
    if ((t == k29) || (t == lbl_802AD3F0) || (t == lbl_802AD3F4)) {
        goto join;
    }
    arg0->unk0x3B8 = delta;
    delta = t - arg0->unk0x94;
    if (!(delta < k29)) {
        v31 = arg0->unk0x3C0;
        f1v = arg0->unk0x3BC;
        goto join;
    }
    arg0->unk0x3B8 = k29;
    v31 = arg0->unk0x3C0;
    f1v = arg0->unk0x3BC;
join:;
    if (d30 > v31) {
        d30 = v31;
        ob = arg0->unk0xC;
        kv = lbl_802AD3EC;
        fr.s10.f[0] = d30;
        {
            __ps_t pC = ob->unk0xC0;
            __ps_t pB = ob->unk0xB8;
            __ps_t sq = __builtin_ps_mul(pC, pC);
            __ps_t pr = fr.s10.ps;
            __ps_t ab = __builtin_ps_abs(pr);
            __ps_t mg = __builtin_ps_merge01(sq, ab);
            __ps_t md = __builtin_ps_madd(pB, pB, mg);
            __ps_t rs;
            __ps_t sc;
            __ps_t sb;
            __ps_t pc;
            fr.s10.f[1] = kv;
            __asm__("" : "=f"(kvc) : "f"(kv));
            md = __builtin_ps_sum0(md, md, md);
            smu.ps = __builtin_ps_abs(md);
            if (smu.f[0] > kvc) {
                rs = __builtin_ps_rsqrte(md);
                sc = __builtin_ps_muls0(rs, ab);
                sb = __builtin_ps_muls0(pB, sc);
                ob->unk0xB8 = sb;
                fr.s18.ps = sc;
                fr.s18.f[1] = lbl_802AD3F8;
                pc = __builtin_ps_mul(pC, fr.s18.ps);
                ob->unk0xC0 = pc;
            }
        }
    }
    ot = arg0->unk0xC;
    if (d30 > f1v) {
        fn_8012570C(QB_UNKNOWN_0x850DB87A, 1);
        fn_801D19E0(arg0);
    }
    ot->unk0xBC = s28;
    t = arg0->unk0x384;
    if (t == lbl_802AD3EC) {
        return;
    }
    delta = t - arg0->unk0x94;
    arg0->unk0x384 = delta;
    if ((delta == k29) || (delta < k29)) {
        arg0->unk0x384 = k29;
        arg0->unk0x378 = fn_8014030C(QB_PHYSICS_ROLLING_FRICTION, 1, (s32)ot);
    }
}
