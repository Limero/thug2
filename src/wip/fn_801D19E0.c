// PARKED 12.2% (10/82): full semantic rebuild done; all PS ops decoded+emitted
// (ps_mul/merge00/01/madd/sum0/sub/abs/rsqrte/muls0 via builtins incl. scalar fmuls
// chain). Resisting: (1) want's [lfs f0,sp18][fmr f10,f0] lane-read pair - pins make
// GCC load direct-to-hard-reg, unpinned webs land in f7/f8, asm wedges reorder entry;
// (2) FPR coloring of unpinned dance temps (want cv->f0/zv->f13/bv->f11 needs full-web
// pinning which then perturbs middle-block); (3) frame +8 (0x40 vs 0x38).
// Control flow + all call-free PS math otherwise aligned modulo cascade.
// family=m2c range=0x801D19E0-0x801D1B3C size=348B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 12.6% ([2]rev->12.6%).
#include "types.h"
#include "structs.h"
extern char lbl_802AD278[];
extern f32 lbl_802AD3FC;
extern f32 lbl_802AD400;
extern f32 lbl_802AD404;
extern f32 lbl_802AD408;
typedef union {
    __ps_t ps;
    f32 f[2];
} psu_t;

void fn_801D19E0(Unk_C7387A53 *arg0, f32 farg1) {
    Unk_548A6C04 *obj;
    psu_t wk[6];
    psu_t *cp;
    register f32 k1 __asm__("fr12");
    f32 k2;
    register f32 k3a __asm__("fr9");
    f32 k3b;
    f32 k4a;
    f32 k4b;
    f32 t2;
    register f32 len2 __asm__("fr10");
    register f32 v94 __asm__("fr0");
    register __ps_t cv __asm__("fr0");
    register __ps_t sq __asm__("fr0");
    register __ps_t zv __asm__("fr13");
    register __ps_t bv __asm__("fr11");
    f32 prod;
    f32 newlen;
    __ps_t mg;
    __ps_t md;
    __ps_t md2;
    __ps_t pr;
    __ps_t ab;
    __ps_t rs;
    __ps_t sc;
    __ps_t sb;
    __ps_t pc;
    __ps_t pb;
    psu_t smu;

    obj = *((char * *)&arg0->unk0xC);
    cp = wk + 1;
    k1 = lbl_802AD3FC;
    cv = obj->unk0xC0;
    zv = *(__ps_t *)&lbl_802AD278;
    sq = __builtin_ps_mul(cv, cv);
    bv = obj->unk0xB8;
    mg = __builtin_ps_merge00(sq, zv);
    md = __builtin_ps_madd(bv, bv, mg);
    md = __builtin_ps_sum0(md, md, md);
    wk[2].ps = md;
    t2 = wk[2].f[0];
    len2 = t2;
    if (len2 < k1) {
        return;
    }
    v94 = *((f32 *)&arg0->unk0x94);
    k2 = lbl_802AD400;
    wk[0].ps = bv;
    cv = obj->unk0xC0;
    prod = farg1 * k2;
    k3a = lbl_802AD404;
    prod = prod * v94;
    cp[0].ps = cv;
    prod = prod * len2;
    wk[3].f[0] = prod;
    k3b = lbl_802AD404;
    pc = cp[0].ps;
    wk[3].f[1] = k3b;
    sq = __builtin_ps_mul(pc, pc);
    pr = wk[3].ps;
    ab = __builtin_ps_abs(pr);
    mg = __builtin_ps_merge01(sq, ab);
    pb = wk[0].ps;
    md2 = __builtin_ps_madd(pb, pb, mg);
    md2 = __builtin_ps_sum0(md2, md2, md2);
    smu.ps = __builtin_ps_abs(md2);
    if (!(smu.f[0] <= k3a)) {
        cp[0].ps = __builtin_ps_mul(pc, wk[4].ps);
        pc = cp[0].ps;
        wk[4].f[1] = k4a;
        k4a = lbl_802AD408;
        wk[0].ps = sb;
        wk[4].ps = sc;
        sb = __builtin_ps_muls0(pb, sc);
        sc = __builtin_ps_muls0(rs, ab);
        rs = __builtin_ps_rsqrte(md2);
    }
    pc = cp[0].ps;
    zv = *(__ps_t *)&lbl_802AD278;
    sq = __builtin_ps_mul(pc, pc);
    mg = __builtin_ps_merge00(sq, zv);
    pb = wk[0].ps;
    md = __builtin_ps_madd(pb, pb, mg);
    md = __builtin_ps_sum0(md, md, md);
    wk[5].ps = md;
    newlen = wk[5].f[0];
    if (!(newlen < len2)) {
        k4b = lbl_802AD408;
        {
            char *o2 = *((char * *)&arg0->unk0xC);
            ((Unk_24DD6A96 *)o2)->unk0xB8 = k3a;
            ((Unk_24DD6A96 *)o2)->unk0xC4 = k4b;
            ((Unk_24DD6A96 *)o2)->unk0xC0 = k3a;
            ((Unk_24DD6A96 *)o2)->unk0xBC = k3a;
        }
        return;
    }
    {
        char *o2 = *((char * *)&arg0->unk0xC);
        __ps_t od_b = ((Unk_412E16CE *)o2)->unk0xB8;
        __ps_t od_c = ((Unk_412E16CE *)o2)->unk0xC0;
        ((Unk_412E16CE *)o2)->unk0xB8 = __builtin_ps_sub(od_b, pb);
        ((Unk_412E16CE *)o2)->unk0xC0 = __builtin_ps_sub(od_c, cp[0].ps);
    }
}
