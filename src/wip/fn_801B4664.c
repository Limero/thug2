// WIP DRAFT (non-matching) — hand-rebuilt from disasm. NEAR ~35% masked
// (-mps-float), up from m2c draft 7%. Full control flow + all 20 callees
// prototyped + PS chains via SNAPS builtins.
// PARKED on three stacked walls (see docs/parkings/06 + 15 + 28):
//  1. doc-28 CR liveness: want keeps the (bit!=0) compare in cr0 ACROSS
//     ~10 calls via single [cmpwi r30,0][mfcr r30] / [mtcrf 0x80,r30]
//     save/restore pairs; plain-C || conditions reproduce the SHAPE but
//     GCC re-tests registers instead of saving cr0 at every site here.
//  2. allocator-order wall (doc-15 family): want homes arg0->r31,
//     hash-ref->r29, bit->r30, p08->r27 with stmw r27 span; every source
//     arrangement reaches stmw r25 with shifted roles (pins collapse
//     allocation catastrophically on bodies this size).
//  3. PS tail rotation: pathB normalize chain (rsqrte/muls0/add/vsel
//     region @0x497C-4A38) interleaves dead pair spills in an order tied
//     to the intermediate-SN-compiler scheduler (cf. doc06 M5.0j).
// NOTE for retry: all opcode-4 words in WANT are cc1-builtin encodings —
// probe map verified on 3.9.3: __builtin_ps_mul=xo5-25, _muls0=12,
// _muls1=13, _madds0=14, _madds1=15, _sum0=10, _sum1=11, mergeNN=c-field
// 16-19 under xo5-16, neg/abs/nabs=xo5-8 forms, sel=23, res=24, rsqrte=26.
// doc06's 'XO5=6/7 hard wall' was a mislabeled table (sum0 is 10 not 6);
// retest any doc-06 member parked on sum/madds encodings with these.
// family=hand range=0x801B4664-0x801B4BD0 size=1388B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -mps-float
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 10.9% ([3]rev->8.0% [6]rev->10.9%).
#include "types.h"
#include "structs.h"
#include "dolphin/SN_PS.h"
extern char lbl_802ABFB8[];

extern f32 lbl_802AC068;
extern char lbl_802AC078[];
extern s32 lbl_80305EAC;

void fn_800D80F8(Unk_2A3EDACE * a);
s32 GetChecksum_3(Unk_6A70655D * a, s32 h);
s32 fn_801745B4(s32 a);
f32 fn_8012570C(s32 h, s32 f);
s32 Script_GetInteger(s32 h, s32 f);
void fn_801B91DC(Unk_A9157FE7 * a);
void fn_801B6310(Unk_A9157FE7 * a);
void fn_801B3220(Unk_C7387A53 * a, s32 * h, s32 * v, Unk_C8FEE62D * f);
s32 fn_801B7FF0(CScript * a);
s32 fn_801B56C8(Unk_61ECF642 * a);
void fn_801B52D0(Unk_0EAAF5DE * a);
void fn_801B5A54(void *a);
void fn_801B7A48(void *a);
void fn_801B7C80(void *a, s32 h);
void fn_801B7484(Unk_0EAAF5DE * a, Unk_EA529D06 * out);
void fn_801B6F8C(Unk_2124B462 * a);
void fn_801B5BBC(Unk_C7387A53 * a);
void fn_801B8DE0(Unk_073F5245 * a);
void fn_801B7ED4(Unk_C7387A53 * a, s32 k);
void fn_801C1A9C(f32 v);

#define TBL (*(SN_PS_type *)lbl_802ABFB8)

void fn_801B4664(Unk_38B8A5C2 *arg0) {
    struct {
        __ps_t v08;
        __ps_t v10;
        __ps_t v18;
        __ps_t v20;
        __ps_t v28;
        __ps_t v30;
        __ps_t v38;
        __ps_t v40;
        __ps_t v48;
        __ps_t v50;
        __ps_t v58;
        __ps_t v60;
        SN_PS_type lane1C;
        f32 lane60;
    } fr;
    Unk_DF2324A8 *objp;
    Unk_C8FEE62D *ref;
    Unk_AF254F69 *cat;
    char *p08;
    s32 bit;
    s32 flags;
    s32 var_r28;
    f32 scale;
    SN_PS_type o88;
    SN_PS_type o96;
    SN_PS_type o120;
    SN_PS_type o128;
    SN_PS_type tA;
    SN_PS_type tB;
    SN_PS_type tC;
    SN_PS_type tD;
    SN_PS_type tv;

    ref = (void *)GetChecksum_3(*((s32 *)&arg0->unk0xC), (s32)0x0A015E17u);
    fn_800D80F8(arg0);
    bit = (ref->unk0x1C >> 8) & 1;
    scale = arg0->unk0xA4 * *((f32 *)&ref->unk0x34);

    flags = arg0->unk0x24;
    if ((flags & 4) != 0) {
        cat = (void *)fn_801745B4(lbl_80305EAC);
        if (cat != NULL) {
            tA.ps = cat->unk0x58;
            objp = *((void * *)&arg0->unk0xC);
            tv.ps = ((Unk_2D7DC1B6 *)&TBL)->unk0x0;
            tB.ps = objp->unk0x58;
            tD.ps = cat->unk0x60;
            tA.ps = __builtin_ps_sub(tA.ps, tB.ps);
            tB.ps = objp->unk0x60;
            tA.ps = __builtin_ps_mul(tA.ps, tv.ps);
            tB.ps = __builtin_ps_sub(tD.ps, tB.ps);
            tD.ps = __builtin_ps_merge00(tB.ps, tv.ps);
            tD.ps = __builtin_ps_madds0(tD.ps, tA.ps, tD.ps);
            tD.ps = __builtin_ps_sum0(tD.ps, tD.ps, tD.ps);
            fr.v48 = *(__ps_t *)&tD;
            if (*(f32 *)(char *)&fr.v48 < fn_8012570C(0xBC2E678Au, 1)) {
                fn_801B91DC(arg0);
                return;
            }
        }
    }

    flags = arg0->unk0x24;
    if (bit != 0 || (flags & 2) != 0) {
        p08 = (char *)&fr.v08;
        if ((flags & 8) != 0 || bit != 0) {
            /* path A */
            tB.ps = arg0->unk0x78;
            o88.ps = *(__ps_t *)(arg0->unk0xC + 88);
            o96.ps = *(__ps_t *)(arg0->unk0xC + 96);
            o128.ps = arg0->unk0x80;
            tA.ps = __builtin_ps_sub(o88.ps, tB.ps);
            tB.ps = __builtin_ps_sub(o96.ps, o128.ps);
            fr.v08 = *(__ps_t *)&tA;
            fr.v18 = *(__ps_t *)&tA;
            fr.v20 = *(__ps_t *)&tB;
        } else {
            /* path B */
            fr.v38 = *(__ps_t *)&tA;
            fr.v08 = *(__ps_t *)&tA;
            fr.v40 = *(__ps_t *)&tC;
            fr.v30 = *(__ps_t *)&tC;
            tA.ps = __builtin_ps_sub(o88.ps, tA.ps);
            fr.v28 = *(__ps_t *)&o88;
            tC.ps = __builtin_ps_sub(tB.ps, tD.ps);
            fr.v20 = *(__ps_t *)&tC;
            fr.v18 = *(__ps_t *)&tA;
            tB.ps = *(__ps_t *)(arg0->unk0xC + 96);
            fr.lane1C = tv;
            tD.ps = arg0->unk0x80;
            o120.ps = *(__ps_t *)&tB;
            o88.ps = *(__ps_t *)(arg0->unk0xC + 88);
            tC.ps = arg0->unk0x80;
            tv.flt.lo = lbl_802AC068;
            tB.ps = arg0->unk0x78;
        }

        /* mix join @0x47F0 */
        fr.v08 = *(__ps_t *)&tC;
        tA.ps = *(__ps_t *)&fr.v08;
        tv.ps = ((Unk_2D7DC1B6 *)&TBL)->unk0x0;
        tB.ps = __builtin_ps_mul(tA.ps, tv.ps);
        tB.ps = __builtin_ps_sum0(tB.ps, tB.ps, tB.ps);
        fr.v50 = *(__ps_t *)&tB;
        scale = *(f32 *)(char *)&fr.v50;

        if ((arg0->unk0x24 & 0x800) == 0) {
            tC.ps = *(__ps_t *)&scale;
            tD.ps = __builtin_ps_mul(tC.ps, tC.ps);
            if (scale < scale * scale) {
                fn_801B6310(arg0);
            } else if (!(scale < (f32)(f64)(s32)Script_GetInteger(0xFB5D106Fu, 1))) {
            } else {
                fn_801B6310(arg0);
            }
        }

        flags = arg0->unk0x24;
        if ((flags & 0x100) != 0) {
            if (scale < (f32)(f64)(s32)Script_GetInteger(0x52EC432Fu, 1)) {
                arg0->unk0x24 = flags & ~0x100;
                fn_801B3220(arg0, (s32)0xB32163E0u, (s32)0x46196541u, 0);
            }
        }
    } else {
        goto plain;
    }
    goto after_flags;

plain:
    /* @0x48FC: !(bit||flags&2) lands here when bit==0 */
    fn_801B5BBC(arg0);
    fn_801B7A48(arg0);
    if ((arg0->unk0x24 & 0x600) != 0) {
        fn_801B8DE0(arg0);
    }
    goto state_sel;

after_flags:
    if (((arg0->unk0x24 & 2) == 0)) {
        goto plain;
    }
    if (scale == lbl_802AC068) {
        goto plain;
    }
    /* main body @0x4918 */
    {
        fr.v10 = objp->unk0x60;
        fr.v08 = objp->unk0x58;
        var_r28 = 0;
        p08 = (char *)&fr.v08;
        objp = *((void * *)&arg0->unk0xC);

        if (fn_801B7FF0(arg0) != 0) {
            if (fn_801B56C8(arg0) == 0) {
                fn_801B52D0(arg0);
            }
            fn_801B5A54(arg0);
            if (bit != 0) {
                fn_801B7A48(arg0);
            }
        } else {
            /* pathB' @0x497C */
            tA.ps = arg0->unk0x80;
            tB.ps = objp->unk0x60;
            tC.ps = objp->unk0x58;
            tD.ps = __builtin_ps_sub(tA.ps, tB.ps);
            tv.ps = ((Unk_2D7DC1B6 *)&TBL)->unk0x0;
            tA.ps = arg0->unk0x78;
            tB.ps = __builtin_ps_mul(tD.ps, tD.ps);
            fr.v40 = *(__ps_t *)&tD;
            tA.ps = __builtin_ps_sub(tA.ps, tC.ps);
            tD.ps = __builtin_ps_merge00(tB.ps, tv.ps);
            fr.v38 = *(__ps_t *)&tv;
            tB.ps = __builtin_ps_madd(tA.ps, tD.ps, tA.ps);
            tB.ps = __builtin_ps_sum0(tB.ps, tB.ps, tB.ps);
            tC = tB;
            if (!(tC.flt.hi <= lbl_802AC068)) {
                tD.ps = __builtin_ps_rsqrte(tB.ps);
                tB.flt.lo = *((f32 *)&((Unk_7D81B2AB *)&lbl_802AC078)->unk0x0);
                fr.v58 = *(__ps_t *)&tD;
                fr.v30 = *(__ps_t *)&tv;
            }
            fr.lane60 = scale;
            var_r28 = 1;
            fn_801B52D0(arg0);
            fn_801B5A54(arg0);
            fn_801B7484(arg0, (char *)&fr + 0x28);
        }

        /* @0x4A74 */
        if ((arg0->unk0x24 & 0x84) == 0) {
            if (bit != 0) {
                fn_801B7C80(arg0, (s32)0x0A015E17u);
                if (var_r28 == 0) {
                    fr.v18 = fr.v08;
                    fn_801B7484(arg0, (char *)&fr + 0x18);
                }
                fn_801B6F8C(arg0);
            }
        }
    }

state_sel:
    /* @0x4AE4 */
    if (bit != 0) {
        fn_801B7ED4(arg0, 1);
    } else if ((arg0->unk0x24 & 4) != 0) {
        fn_801B7ED4(arg0, 4);
    } else if ((arg0->unk0x24 & 2) != 0) {
        fn_801B7ED4(arg0, 0);
    } else if ((arg0->unk0x24 & 0x2000) != 0) {
        fn_801B7ED4(arg0, 3);
    }

    /* tail @0x4B44 */
    if ((arg0->unk0x24 & 2) != 0) {
        tA.flt.hi = *((f32 *)&ref->unk0x30);
        if (tA.flt.hi != lbl_802AC068) {
            tA.flt.lo = *((f32 *)&ref->unk0x34) / tA.flt.hi;
        } else {
            tA.flt.lo = lbl_802AC068;
        }
    } else {
        tA.flt.lo = lbl_802AC068;
    }
    arg0->unk0xE8 = tA.flt.lo;

    cat = (void *)GetChecksum_3(*((s32 *)&arg0->unk0xC), (s32)0xB5F1E9D2u);
    if (cat != NULL) {
        s32 v9 = 1;
        if ((arg0->unk0x24 & 0xC0) == 0) {
            v9 = 0;
        }
        cat->unk0xE8 = v9;
        fn_801C1A9C(arg0->unk0xE8);
    }
}
