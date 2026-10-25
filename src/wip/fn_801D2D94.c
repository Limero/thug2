// WIP DRAFT — hand-rebuilt from disasm (PS distance/rescale sibling of 19E0)
// family=m2c range=0x801D2D94-0x801D2F40 size=428B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AD278[];
extern f32 lbl_802AD434;
extern f32 lbl_802AD438;
extern f32 fn_8014030C(s32, s32, Unk_FFAD6788 *);
extern s32 fn_801D2F40(Unk_C7387A53 *);
typedef union {
    __ps_t ps;
    f32 f[2];
} psu_t;

// PARKED 5.7%: PS lane-read pair [lfs f0,sp8][fmr f30] + kv copy-pair coloring walls;
// adds ps_add reconcile path + hidden arg0 passthrough to fn_801D2F40; semantically
// complete body left in place — see sibling parks 801D17E4/801D19E0 for wall detail.
void fn_801D2D94(void *arg0) {
    register f32 d31 __asm__("fr31");
    register void *a0 __asm__("r31");
    register char *obj __asm__("r30");
    psu_t wk[6];
    register psu_t *cp __asm__("r29");
    __ps_t zv;
    __ps_t cv;
    __ps_t bv;
    __ps_t sq;
    __ps_t mg;
    __ps_t md;
    __ps_t pr;
    __ps_t ab;
    __ps_t rs;
    __ps_t sc;
    __ps_t sb;
    __ps_t pc;
    __ps_t pb;
    psu_t smu;
    psu_t u1;
    f32 ret1;
    f32 lim;
    f32 ka;
    f32 kb;
    f32 v94;

    a0 = arg0;
    ((Unk_71062261 *)a0)->unk0x388 = 1;
    if (fn_801D2F40((s32)a0) != 0) {
        ((Unk_71062261 *)a0)->unk0x388 = 0;
        return;
    }
    obj = *((char * *)&((Unk_71062261 *)a0)->unk0xC);
    zv = *(__ps_t *)&lbl_802AD278;
    cv = ((Unk_412E16CE *)obj)->unk0xC0;
    bv = ((Unk_412E16CE *)obj)->unk0xB8;
    sq = __builtin_ps_mul(cv, cv);
    mg = __builtin_ps_merge00(sq, zv);
    md = __builtin_ps_madd(bv, bv, mg);
    md = __builtin_ps_sum0(md, md, md);
    md = __builtin_ps_rsqrte(md);
    md = __builtin_ps_res(md);
    wk[2].ps = md;
    {
        __asm__("" : "=f"(d31) : "f"(wk[2].f[0]));
    }
    ret1 = fn_8014030C(QB_PHYSICS_BRAKE_ACCELERATION, 1, (s32)obj);
    lim = ret1 + ret1;
    lim = lim * *((f32 *)&((Unk_71062261 *)a0)->unk0x94);
    if (!(d31 < lim)) {
        goto big;
    }
    ka = lbl_802AD434;
    kb = lbl_802AD438;
    ((Unk_24DD6A96 *)obj)->unk0xB8 = ka;
    ((Unk_24DD6A96 *)obj)->unk0xC4 = kb;
    ((Unk_24DD6A96 *)obj)->unk0xC0 = ka;
    ((Unk_24DD6A96 *)obj)->unk0xBC = ka;
    return;
big:;
    cp = wk + 1;
    wk[0].ps = bv;
    cv = ((Unk_412E16CE *)obj)->unk0xC0;
    ret1 = fn_8014030C(QB_PHYSICS_BRAKE_ACCELERATION, 1, (s32)obj);
    v94 = *((f32 *)&((Unk_71062261 *)a0)->unk0x94);
    cp[0].ps = cv;
    ka = lbl_802AD434;
    {
        f32 neg = -ret1;
        neg = neg * v94;
        wk[3].f[0] = neg;
        wk[3].f[1] = ka;
    }
    pc = cp[0].ps;
    sq = __builtin_ps_mul(pc, pc);
    pr = wk[3].ps;
    ab = __builtin_ps_abs(pr);
    mg = __builtin_ps_merge01(sq, ab);
    pb = wk[0].ps;
    md = __builtin_ps_madd(pb, pb, mg);
    md = __builtin_ps_sum0(md, md, md);
    smu.ps = __builtin_ps_abs(md);
    if (!(smu.f[0] <= ka)) {
        rs = __builtin_ps_rsqrte(md);
        sc = __builtin_ps_muls0(rs, smu.ps);
        sb = __builtin_ps_muls0(pb, sc);
        wk[4].ps = sc;
        wk[0].ps = sb;
        kb = lbl_802AD438;
        wk[4].f[1] = kb;
        pc = cp[0].ps;
        cp[0].ps = __builtin_ps_mul(pc, wk[4].ps);
    }
    pb = wk[0].ps;
    sb = ((Unk_412E16CE *)obj)->unk0xB8;
    sc = ((Unk_412E16CE *)obj)->unk0xC0;
    ((Unk_412E16CE *)obj)->unk0xB8 = __builtin_ps_add(sb, pb);
    pc = cp[0].ps;
    ((Unk_412E16CE *)obj)->unk0xC0 = __builtin_ps_add(sc, pc);
}
