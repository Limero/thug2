// WIP DRAFT — hand rebuild from ps_disasm/decode (M5.0t unpark attempt,
// 2026-08-26). family=m2c range=0x801F77B8-0x801F7B04 size=844B
// STATUS: PARKED — semantic rebuild COMPLETE (every insn decoded, all ops
// mapped to C/builtins) but scheduling/regalloc alignment is function-wide;
// best masked positional score 2.3% (-mps-float), got 214 insns vs want 211.
// The three former "xo5=6/7 wall" words decode and emit as indexed pair memory
// operations: the word at 0x801F77EC (0x11AB280C) loads a pair into f13
// indexed by r11 plus r5, i.e. a pair read from base plus offset; the word at
// 0x801F7A98 (0x1005000C) loads a pair into f0 indexed by r5 plus r0 for the
// loop element read; the word at 0x801F7ADC (0x11A5000E) stores the f13 pair
// indexed by r5 plus r0, i.e. a pair write to base plus offset. All three are
// emitted by this draft in some builds (the two loads never merge into a
// quad-word load when the quat loads are split correctly).
// SEMANTICS (quat-blend skinning): args r3=offset-pair ptr, r4=quat b,
// r5=base quat array (char*), r6=idx list walker, r7=count. Entry computes
// |b|^2 via mul->merge00(rodata zero pair @lbl_802AE430)->madd->sum0;
// guard q.z>0 -> rsqrte/muls0 normalize of sp28/sp30 pairs; |y|>0.99999 ->
// const pairs (0,0)/(1,1) else matrix-ish merge10/00 block; two more
// guarded normalizes; tail: 4x empty spin (doc-30 window li4/mtctr/bdnz$),
// spill cluster c58..s80/r98..rb0 (store-only!), stage loop-live values
// (want homes f30=[sp8] f31=[sp28] f2-f5<-pc/pd/na/nb f6/f7=lfs [88]/[90]),
// blend loop: Q[j] += blend(Q[j]-Q[first]) + vtx offset, psq_lx load +
// psq_stx store per entry.
// PROBED IDIOMS (all verified vs ngccc 3.9.3):
//   * (f32)pairvar casts extract lane0 IN-REGISTER -> want's direct
//     fcmpu-on-pair-reg after psq_st (no union pun; union puns split to
//     lwz pairs or ICE).
//   * guards are direct '>' forms -> bare ble/bgt (no cror NaN dance);
//     !(x<=y)/<= spellings emit cror+bso and never match.
//   * __builtin_ps_madds0(x,y,z) = x*y.lane0 + z (multiplier = 2nd arg,
//     CONTRADICTS the doc note "multiplier = third arg"); muls0(x,y)=
//     x*y.lane0. Probed by compiling single-builtin TU and decoding.
//   * plain float vars passed to madds become broadcast pairs -> want's
//     bare lfs multipliers f6=[88] f7=[90].
//   * two quat loads must NOT merge into lq: volatile on the FIRST only.
//   * &mm byte-pointer web lives r10->r0->r10 across whole fn (mn store
//     and loop reload go through it); &ua web (r9) covers the 4 unit-pair
//     member writes (two direct-disp, two via ptr - mixed!).
// RETRY RECIPE: body below is semantically exact; remaining work is pure
// scheduler negotiation region-by-region using tools/ps_diff.py --all +
// a masked positional scorer. Order of attack: (1) prologue stfd f30/f31
// (pins exist; check placement vs preheader), (2) entry q23in must stay
// in reg across i/zp/kz/mul/slwi/merge/kz (currently spills to 0x88),
// (3) first-guard compare must consume the LATE q23 slot-reload web not
// an early remat, (4) loop latch wants mtctr r7/bdnz not addic./bne,
// (5) mr r10,r0 (&mm preservation) + loop head double-hop staging
// (load slot -> ps_mr home) for f2-f5.
// INERT: not registered in splits.txt/configure.py — never compiled.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 3.3% ([1]rev->3.3% [9]rev->3.3%).
extern char lbl_802AE430[];
extern f32 lbl_802AE484;
extern f32 lbl_802AE488;
extern f32 lbl_802AE48C;

// FLAG: -mps-float
#include "structs.h"
typedef union { __ps_t p; f32 w[2]; } PSU;

void fn_801F77B8(Unk_EA529D06 *vtx, Unk_EA529D06 *quat, char *base, s32 *idxp, s32 count) {
    PSU mm;
    PSU mn;
    PSU ua;
    PSU ub;
    PSU q01;
    PSU q23;
    PSU na;
    PSU nb;
    PSU pc;
    PSU pd;
    PSU c58;
    PSU c60;
    PSU s68;
    PSU s70;
    PSU s78;
    PSU s80;
    PSU e88;
    PSU e90;
    PSU r98;
    PSU ra0;
    PSU ra8;
    PSU rb0;
    volatile PSU sr;
    volatile PSU sc0;
    volatile PSU sc8;
    volatile PSU sd0;
    volatile PSU sd8;
    __ps_t zp;
    __ps_t q23in;
    __ps_t acc;
    __ps_t acc2;
    __ps_t q01ld;
    __ps_t mnv;
    __ps_t rr;
    __ps_t t0;
    __ps_t t1;
    __ps_t t2;
    __ps_t t3;
    __ps_t t4;
    __ps_t t5;
    __ps_t t6;
    __ps_t t7;
    f32 kz;
    f32 ko;
    f32 kl;
    f32 bz;
    f32 ny;
    f32 vz;
    f32 one94;
    s32 i;
    s32 n;
    s32 off;
    Unk_C1F9F519 *pb;
    Unk_C1F9F519 *mp;
    char *up;
    Unk_C1F9F519 *walker;
    register __ps_t p30 __asm__("fr30");
    register __ps_t p31 __asm__("fr31");
    s32 jj;

    q23in = quat->unk0x8;
    i = idxp[0];
    zp = *(volatile __ps_t *)lbl_802AE430;
    kz = lbl_802AE484;
    acc = __builtin_ps_mul(q23in, q23in);
    off = i << 4;
    acc = __builtin_ps_merge00(acc, zp);
    mm.p = *(__ps_t *)(base + off);
    mp = (char *)&mm;
    q01ld = *(__ps_t *)((char *)quat);
    pb = base + off;
    mnv = pb->unk0x8;
    acc = __builtin_ps_madd(q01ld, q01ld, acc);
    ko = lbl_802AE488;
    mp->unk0x8 = mnv;
    acc = __builtin_ps_sum0(acc, acc, acc);
    up = (char *)&ua;
    ua.w[0] = kz;
    ub.w[0] = kz;
    ua.w[1] = ko;
    ub.w[1] = ko;
    q01.p = *(__ps_t *)((char *)quat);
    q23.p = quat->unk0x8;
    acc2 = acc;
    kl = lbl_802AE48C;
    bz = (f32)q23.p;
    if (bz > kz) {
        acc2 = rr;
        q23.p = t1;
        t1 = __builtin_ps_mul(q23.p, sr.p);
        sr.w[1] = ko;
        q01.p = t0;
        t0 = __builtin_ps_muls0(q01.p, rr);
        sr.p = rr;
        rr = __builtin_ps_rsqrte(acc);
    }
    ny = q01.w[1];
    if (__builtin_fabsf(ny) > kl) {
        na.w[0] = kz;
        na.w[1] = kz;
        nb.w[0] = ko;
        nb.w[1] = ko;
    } else {
        t0 = __builtin_ps_merge10(ua.p, ub.p);
        zp = *(volatile __ps_t *)lbl_802AE430;
        t1 = __builtin_ps_merge10(q01.p, q23.p);
        t0 = __builtin_ps_mul(t0, q01.p);
        t1 = __builtin_ps_mul(t1, t1);
        t2 = __builtin_ps_merge00(ub.p, ua.p);
        t1 = __builtin_ps_sub(t1, t0);
        t3 = __builtin_ps_merge00(q01.p, q23.p);
        t4 = __builtin_ps_merge00(t1, t1);
        t2 = __builtin_ps_mul(t2, t3);
        sc0.w[0] = (f32)t4;
        sc0.w[1] = ko;
        t5 = __builtin_ps_merge10(t2, t2);
        t4 = sc0.p;
        t2 = __builtin_ps_sub(t2, t4);
        t2 = __builtin_ps_merge10(t1, t2);
        pc.p = t2;
        t0 = __builtin_ps_mul(ua.p, ua.p);
        pd.w[0] = ua.w[0];
        nb.w[0] = ua.w[0];
        t6 = __builtin_ps_merge00(t0, zp);
        t7 = pc.p;
        pc.p = t7;
        t3 = __builtin_ps_madd(t7, t7, t6);
        t3 = __builtin_ps_sum0(t3, t3, t3);
        vz = (f32)t5;
        if (vz > kz) {
            rr = __builtin_ps_rsqrte(t3);
            sc8.p = t1;
            t0 = __builtin_ps_muls0(pc.p, rr);
            sc8.w[1] = ko;
            na.p = t0;
            t1 = sc8.p;
            t2 = __builtin_ps_mul(ua.p, t1);
            nb.p = t2;
        }
    }
    t1 = q01.p;
    t3 = na.p;
    t0 = q23.p;
    t2 = nb.p;
    t4 = __builtin_ps_merge10(t0, t1);
    zp = *(volatile __ps_t *)lbl_802AE430;
    t5 = __builtin_ps_merge10(t3, t2);
    kz = lbl_802AE484;
    t4 = __builtin_ps_mul(t4, t3);
    t5 = __builtin_ps_mul(t5, t5);
    t5 = __builtin_ps_sub(t5, t4);
    t6 = __builtin_ps_merge00(t5, t5);
    sd0.w[0] = (f32)t6;
    t1 = __builtin_ps_merge00(t0, t1);
    ko = lbl_802AE488;
    t2 = __builtin_ps_merge00(t3, t2);
    t1 = __builtin_ps_mul(t1, t2);
    sd0.w[1] = ko;
    t6 = sd0.p;
    t2 = __builtin_ps_merge10(t1, t1);
    t1 = __builtin_ps_sub(t1, t6);
    t0 = __builtin_ps_mul(q01.p, q01.p);
    pd.p = q01.p;
    t5 = __builtin_ps_merge10(t5, t1);
    t0 = __builtin_ps_merge00(t0, zp);
    pc.p = t5;
    t0 = __builtin_ps_madd(t5, t5, t0);
    t0 = __builtin_ps_sum0(t0, t0, t0);
    vz = (f32)t2;
    if (vz > kz) {
        rr = __builtin_ps_rsqrte(t0);
        ko = lbl_802AE488;
        sd8.p = t1;
        t0 = __builtin_ps_muls0(t5, rr);
        sd8.w[1] = ko;
        pc.p = t0;
        t1 = sd8.p;
        t5 = __builtin_ps_mul(q01.p, t1);
        pd.p = t5;
    }
    for (i = 0; i < 4; i++) {
    }
    c58.p = q01.p;
    c60.p = q23.p;
    one94 = ko;
    p30 = mm.p;
    p31 = q01.p;
    if (count > 0) {
        n = count;
        do {
            jj = idxp[0];
            t4 = mp->unk0x8;
            idxp += 1;
            off = jj << 4;
            t5 = vtx->unk0x8;
            t6 = *(__ps_t *)(base + off);
            walker = base + off;
            t7 = walker->unk0x8;
            t6 = __builtin_ps_sub(t6, p30);
            t3 = *(__ps_t *)((char *)vtx);
            t0 = __builtin_ps_muls0(p31, t6);
            t1 = __builtin_ps_muls0(c60.p, t6);
            t0 = __builtin_ps_madds1(pc.p, t6, t0);
            t7 = __builtin_ps_sub(t7, t4);
            t1 = __builtin_ps_madds1(pd.p, t6, t1);
            t0 = __builtin_ps_madds0(na.p, t7, t0);
            t1 = __builtin_ps_madds0(nb.p, t7, t1);
            t0 = __builtin_ps_madds1(e88.w[0], t7, t0);
            t1 = __builtin_ps_madds1(e90.w[0], t7, t1);
            r98.p = t0;
            ra0.p = t1;
            t0 = __builtin_ps_add(t0, t3);
            *(__ps_t *)(base + off) = t0;
            rb0.p = t1;
            ra8.p = t0;
            walker->unk0x8 = t1;
            t1 = __builtin_ps_add(t1, t5);
        } while (--n != 0);
    }
}
