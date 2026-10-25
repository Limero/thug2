// WIP DRAFT — hand rebuild (doc-06 M5.0t unpark attempt, follow-up)
// family=hand range=0x801F7B04-0x801F7FEC size=1256B
// STATUS: PARKED at 29.8% ps_diff / 28.98% sweep masked (-mps-float).
// Prior 98.4% figure belonged to the reverted asm-transcription attempt
// (recipe-180 incident class); this rebuild is honest plain C.
//
// WIN 1 — former "XO5=6/7 hard wall" is DEAD (M5.0t decode artifact):
//   all five words decode as X-form indexed pair ops and EMIT from plain C:
//     D48 1009E80C psq_lx  f0,r9+r29   <- ((__ps_t*)buf1)[o1*2] element form
//     D58 101E000E psq_stx f0,r30+r0   <- ((__ps_t*)buf2)[o2*2] = v
//     E68 101F000C psq_lx  f0,r31+r0   <- ((__ps_t*)buf4)[i*2]
//     ED4 119F000E psq_stx f12,r31+r0  <- match-path store, off-first web
//     F50 117F000E psq_stx f11,r31+r0  <- search-2 store
//   They assemble byte-correct in this build; residual is stream POSITION.
//
// WIN 2 — doc-28 long-range CR machinery reproduced from PLAIN C (no asm):
//   mfcr r12 prologue + stw r12,0xb0 + mtcrf 8,r12 epilogue (arg6 test
//   hoisted into call-saved cr4 across ~15 bls — arg6 has no saved GPR
//   home, its only use is the early compare) AND mfcr r31/mtcrf 0x80,r31
//   volatile-cr0 spill around the arg5 test. All four words OK-masked.
//
// RESIDUAL (214 insns, doc-15/scheduler class): interlocked ready-list
// tie-breaks shift streams. Biggest windows:
//   - block1 PS weave @0180-01F8 (59): want emits [lfs f12 E0][li r7,0xa
//     @pos2!][lfs f0][mr r4][psq_l a8 BEFORE fdivs]...; got sinks divs,
//     reorders six pair loads (+0s first), ratio-pair reload hoists early
//     (want reloads f11 mid-block after add1 -> forces ps_mr f12,f11;
//     got keeps reload in f12, no mr). LUID-order artifact.
//   - search loops @038C-F98 (64): found-flag homes r7-saved (want) vs
//     r0-scratch (got); sap/sbp walker roles r11/r9 swapped; guards use
//     found-reg-as-zero correctly in both (cmpw r_found, cnt emerged!).
//   - blocks 2/3 store rotations @0270 (34); big-section prologue @0328
//     (23, arg1/arg2 homes +1 slot, dbaseB/ob swap).
// Levers that WORKED (kept): serialized single-temp table copies (r0 chain),
// dA->r30 / dbaseA->r19 solo pins, "+r" barrier splitting ba web (mr r7,r19
// copy), goto-web duplicated-header loops (search guards!), x2 record index
// for psq_lx element form, inline &fr.ob[0] (GCSE cache = want r24).
// Levers that FAILED: 5-arg fn_800546A0 proto (worse), full param pin set
// (cascade), removing param copies (catastrophic), ratio named-local,
// "+f" barrier on ratio, stmt reorder of block1 loads.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -mps-float
#include "types.h"
#include "structs.h"

typedef union { __ps_t p; f32 w[2]; } PSU;

extern char lbl_802AE490[];
extern char lbl_802AE4B8[];
extern f32 lbl_802AE4E0;
extern f32 lbl_802AE4E4;

extern s32 fn_800546A0(s32);
extern s32 fn_80057CA0(CStruct *);
extern s32 fn_8005F550(s32);
extern s32 Mem_Alloc_3(s32);
extern s32 fn_8005F584(s32, s32);
extern s32 fn_8005F410(Unk_9994C3F5 *);
extern s32 fn_8005F70C(s32, s32);
extern void Mem_Free_3(s32);
extern void fn_801040FC(s32, s32);
extern void fn_8000634C(s32);
extern void fn_8005812C(s32, s32);
extern s32 fn_80238964(void);
extern void fn_8022D4C4(Unk_DB0E2BAB *);
extern void fn_801F77B8(Unk_EA529D06 *, Unk_EA529D06 *, char *, s32 *, s32);

void fn_801F7B04(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    struct {
        s32 bufA[10];
        s32 bufB[10];
        PSU ob[10];
        f32 ratio;
    } fr;

    PSU *obp;
    u32 *sa;
    u32 *sb;
    u32 *d;
    u32 *db;
    s32 n;
    s32 nb;
    u32 w0;
    Unk_EA529D06 *a0h;
    Unk_EA529D06 *a1h;
    Unk_EA529D06 *a2h;
    s32 a3h;
    s32 a5h;
    s32 h1;
    s32 cnt;
    s32 buf1;
    register s32 dbaseA __asm__("r19");
    u32 *dAp;
    u32 *dbaseB;
    PSU a0p, a8p, b0p, b8p, c0p, c8p, rp, m13, m0, mrb;
    PSU e_b0p, e_b8p, e_c0p, e_c8p;
    PSU t_b8p, t_b0p, t_c0p, t_c8p;
    s32 h2;
    s32 cnt2;
    s32 buf2;
    u32 *ba;
    u32 *bb;
    s32 k;
    u32 o1;
    u32 o2;
    __ps_t v;
    Unk_C1F9F519 *a1p;
    Unk_C1F9F519 *a2p;
    s32 buf3;
    Unk_897A0ACF *src3;
    u16 nObj;
    s32 buf4;
    s32 i;
    s32 found;
    s32 j;
    s32 k2;
    s32 off;
    Unk_59D80CBF *ea;
    Unk_C1F9F519 *eacopy;
    char *sap;
    char *sbp;
    PSU p0;
    PSU p1;
    PSU q0;
    f32 fdiff;

    /* ---- static table copies (0x28 bytes each) ---- */
    sa = (u32 *)lbl_802AE490;
    dAp = (s32)fr.bufA;
    d = (u32 *)dAp;
    a0h = arg0;
    dbaseA = dAp;
    a2h = arg2;
    a1h = arg1;
    a3h = arg3;
    a5h = arg5;
    n = 0x18;
    dbaseB = (u32 *)fr.bufB;
    do {
        n -= 0x18;
        w0 = sa[0];
        d[0] = w0;
        w0 = sa[1];
        d[1] = w0;
        w0 = sa[2];
        d[2] = w0;
        w0 = sa[3];
        d[3] = w0;
        w0 = sa[4];
        d[4] = w0;
        w0 = sa[5];
        d[5] = w0;
        sa += 6;
        d += 6;
    } while (n != 0);
    w0 = sa[0];
    d[0] = w0;
    w0 = sa[1];
    d[1] = w0;
    w0 = sa[2];
    d[2] = w0;
    w0 = sa[3];
    d[3] = w0;

    sb = (u32 *)lbl_802AE4B8;
    db = (u32 *)dbaseB;
    nb = 0x18;
    do {
        nb -= 0x18;
        w0 = sb[0];
        db[0] = w0;
        w0 = sb[1];
        db[1] = w0;
        w0 = sb[2];
        db[2] = w0;
        w0 = sb[3];
        db[3] = w0;
        w0 = sb[4];
        db[4] = w0;
        w0 = sb[5];
        db[5] = w0;
        sb += 6;
        db += 6;
    } while (nb != 0);
    w0 = sb[0];
    db[0] = w0;
    w0 = sb[1];
    db[1] = w0;
    w0 = sb[2];
    db[2] = w0;
    w0 = sb[3];
    db[3] = w0;

    /* ---- setup calls (chained r3) ---- */
    cnt = fn_8005F550(h1 = fn_80057CA0(fn_800546A0(arg4)));
    buf1 = Mem_Alloc_3(cnt * 16);
    fn_8005F584(h1, buf1);

    if (a5h != 0) {
        /* ---- block 1: scaled direction vectors ---- */
        fr.ratio = lbl_802AE4E4 / lbl_802AE4E0;
        a8p.p = a0h->unk0x8;
        b8p.p = a1h->unk0x8;
        c8p.p = a2h->unk0x8;
        b0p.p = *(__ps_t *)((char *)a1h);
        c0p.p = *(__ps_t *)((char *)a2h);
        a0p.p = *(__ps_t *)((char *)a0h);
        c8p.p = __builtin_ps_sub(c8p.p, b8p.p);
        b8p.p = __builtin_ps_sub(b8p.p, a8p.p);
        fr.ob[7].p = b8p.p;
        c0p.p = __builtin_ps_sub(c0p.p, b0p.p);
        b0p.p = __builtin_ps_sub(b0p.p, a0p.p);
        fr.ob[9].p = c8p.p;
        b8p.p = __builtin_ps_add(b8p.p, c8p.p);
        fr.ob[6].p = c0p.p;
        rp.p = *(__ps_t *)((char *)&fr.ratio);
        b0p.p = __builtin_ps_add(b0p.p, c0p.p);
        fr.ob[8].p = c0p.p;
        mrb = rp;
        fr.ob[4].p = b0p.p;
        fr.ob[5].p = b8p.p;
        m13.p = __builtin_ps_muls0(b0p.p, mrb.p);
        m0.p = __builtin_ps_muls0(b8p.p, mrb.p);
        fr.ob[0].p = m13.p;
        fr.ob[2].p = m13.p;
        fr.ob[1].p = m0.p;
        fr.ob[3].p = m0.p;
        fn_801F77B8(a1h, (s32)&fr.ob[0], buf1, (s32)dbaseA, 0xA);

        /* ---- second buffer alloc + pair copy loop ---- */
        h2 = fn_80057CA0(a5h);
        cnt2 = fn_8005F550(h2);
        buf2 = Mem_Alloc_3(cnt2 * 16);
        fn_8005F584(h2, buf2);
        ba = dbaseA;
        __asm__("" : "+r"(ba));
        bb = dbaseB;
        k = 0;
        do {
            o1 = ba[k];
            o2 = bb[k];
            v = ((__ps_t *)buf1)[o1 * 2];
            k++;
            ((__ps_t *)buf2)[o2 * 2] = v;
            a1p = (char *)buf1 + (o1 << 4);
            a2p = (char *)buf2 + (o2 << 4);
            a2p->unk0x8 = a1p->unk0x8;
        } while (k < 10);
        fn_8005F70C(h2, buf2);
        Mem_Free_3(buf2);
    } else {
        /* ---- block 2: unscaled ---- */
        e_b0p.p = *(__ps_t *)((char *)a2h);
        e_b8p.p = *(__ps_t *)((char *)a1h);
        e_c0p.p = a1h->unk0x8;
        e_c8p.p = a2h->unk0x8;
        e_b0p.p = __builtin_ps_sub(e_b0p.p, e_b8p.p);
        fr.ob[6].p = e_b0p.p;
        e_c0p.p = __builtin_ps_sub(e_c0p.p, e_c8p.p);
        fr.ob[2].p = e_b0p.p;
        fr.ob[1].p = e_c0p.p;
        fr.ob[3].p = e_c0p.p;
        fn_801F77B8(a1h, (s32)&fr.ob[0], buf1, (s32)dbaseA, 0xA);
    }

    /* ---- block 3 (always) ---- */
    t_b8p.p = a1h->unk0x8;
    t_b0p.p = *(__ps_t *)((char *)a1h);
    t_c0p.p = *(__ps_t *)((char *)a2h);
    t_c8p.p = a2h->unk0x8;
    t_c0p.p = __builtin_ps_sub(t_c0p.p, t_b0p.p);
    t_c8p.p = __builtin_ps_sub(t_c8p.p, t_b8p.p);
    fr.ob[6].p = t_c0p.p;
    fr.ob[1].p = t_c8p.p;
    fr.ob[2].p = t_c0p.p;
    fr.ob[3].p = t_c8p.p;
    fn_801F77B8(a2h, (s32)&fr.ob[0], buf1, (s32)dbaseB, 0xA);
    fn_8005F70C(fn_80057CA0(a3h), buf1);

    if (arg6 != 0) {
        /* ---- big object section ---- */
        s32 inext;
        s32 offcopy;
        f32 facc;
        buf3 = Mem_Alloc_3(cnt * 16);
        fn_8005F584(h1, buf3);
        src3 = fn_8005F410(h1);
        nObj = src3->unk0x6;
        buf4 = Mem_Alloc_3(nObj * 16);
        fn_801040FC(src3, buf4);
        inext = 0;
        i = 0;
        if (i >= (s32)nObj) goto after_objs;
    loop_objs:
        off = i * 16;
        p0.p = ((__ps_t *)buf4)[i * 2];
        ea = (char *)buf4 + off;
        offcopy = off;
        inext = i + 1;
        fr.ob[2].p = p0.p;
        found = 0;
        j = 0;
        p1.p = ea->unk0x8;
        fr.ob[3].p = p1.p;
        eacopy = ea;
        sap = (char *)buf1;
        sbp = (char *)buf3;
        if (j >= (s32)cnt) goto chk_found;
    loop_s1:
        if (((Unk_59AB5482_2 *)sbp)->unk0x0 == fr.ob[2].w[0] &&
            ((Unk_59AB5482_2 *)sbp)->unk0x4 == fr.ob[2].w[1] &&
            ((Unk_5EF41E38 *)sbp)->unk0x8 == fr.ob[3].w[0]) {
            found = 1;
            ((__ps_t *)buf4)[i * 2] = *(__ps_t *)(sap);
            eacopy->unk0x8 = ((Unk_C1F9F519 *)sap)->unk0x8;
            goto chk_found;
        }
        sap += 16;
        sbp += 16;
        j++;
        if (j < (s32)cnt) goto loop_s1;
    chk_found:
        if (found != 0) goto next_obj;
        sap = (char *)buf1;
        sbp = (char *)buf3;
        k2 = 0;
        if (k2 >= (s32)cnt) goto call_634c;
    loop_s2:
        if (((Unk_59AB5482_2 *)sbp)->unk0x0 == fr.ob[2].w[0] &&
            ((Unk_5EF41E38 *)sbp)->unk0x8 == fr.ob[3].w[0]) {
            found = 1;
            ((__ps_t *)buf4)[i * 2] = *(__ps_t *)(sap);
            fdiff = fr.ob[2].w[1] - ((Unk_59AB5482_2 *)sbp)->unk0x4;
            facc = ea->unk0x4;
            q0.p = ((Unk_C1F9F519 *)sap)->unk0x8;
            facc = facc + fdiff;
            ea->unk0x8 = q0.p;
            ea->unk0x4 = facc;
            goto next_obj;
        }
        sap += 16;
        sbp += 16;
        k2++;
        if (k2 < (s32)cnt) goto loop_s2;
    call_634c:
        if (found == 0) {
            fn_8000634C(&fr.ob[2]);
        }
    next_obj:
        i = inext;
        if (i < (s32)nObj) goto loop_objs;
    after_objs:
        fn_8005812C(a3h, buf4);
        Mem_Free_3(buf4);
        Mem_Free_3(buf3);
        fn_8022D4C4(fn_80238964());
    }
    Mem_Free_3(buf1);
}
