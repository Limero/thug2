// UPDATED 2026-08-29: WA-split sweep (call-result store delay) — major gain.
// WIP DRAFT - PARKED at ~31% best-match (2026-08-24). Hand-rebuilt from
// full PS-aware decode (m2c draft was statics-DCE corrupt: float fields
// typed s32, body stripped to dead stubs). Every pair-single word IS decoded
// and emittable (pair multiply/add ops via builtins + SN asm;
// assembler-verified encodings). The empty counter/loop window and all five
// volatile asm (doc-30 recipe, cf. EXACT twin fn_801B5A54); inter-block
// values flow through r1 slots exactly like want.
// REMAINING WALLS (do not re-grind without a new lever):
// 1. Prologue condition-register save: the original computes ONE float
//    compare with a combined unordered/equal/less-than test, keeps that
//    condition LIVE across the GetChecksum_3 call and re-tests it later
//    (doc-28 class). No C shape reproduced the single-compare reuse:
//    duplicate `if` forms emit two compares, bool-value forms fold to
//    branchy materialise/compare forms.
// 2. Copy-loop/hash-arg interleave: want interleaves the hash constant
//    arg setup inside the 8-pair copy shadow; solved only by freezing the
//    whole sequence incl. two bl targets in asm (works, but blocks further
//    scheduler-driven matches downstream).
// 3. Loop-body allocator order: want homes entity/cursor/base reads in
//    fresh temporaries per read (five reloads of the same struct field)
//    and recycles float registers across sections; every pin permutation
//    shifts allocation elsewhere (allocator-order wall, class).
// 4. Conversion dance slot: want shares ONE stack pair slot for the
//    int->float conversion; the compiler gives anonymous temps private
//    slots.
// Best verified masked score during iteration: ~30.5% (prologue byte-exact
// through 0xEC incl. frame 0x160/condition-register save at one config).
// Current build: frame/save area exact except the condition-save pair; positional masked
// score reads low (~4%) because that 2-word shift desynchronizes naive
// word-diff alignment - the frozen blocks and call sequence themselves are
// exact. Recovering the cr4 reuse is wall #1 above.
// family=m2c range=0x801B4E84-0x801B52D0 size=1100B
// INERT: not registered in splits.txt/configure.py -- never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_800A7DB4(CStruct *);
extern f32 fn_8012570C(s32, s32);
extern void *GetChecksum_3(Unk_6A70655D *, s32);
extern f32 acosf(f32);
extern void fn_801B5DC4(s32, f32, f32, f32, f32);
extern char lbl_802ACFB8[];
extern f32 lbl_802AC08C;
extern f32 lbl_802AC090;
extern f32 lbl_802AC094;
extern f32 lbl_802AC098;
extern f64 lbl_802AC0A0;
extern f32 lbl_802AC0A8;

s32 fn_801B4E84(s32 arg0) {
s32 fs_t;
    volatile struct {
        __ps_t T[8];
        __ps_t s72;
        __ps_t s80;
        __ps_t s88;
        __ps_t s96;
        __ps_t s104;
        __ps_t s112;
        __ps_t s120;
        __ps_t s128;
        f32 f132;
        char pad[96];
    } fr;
    register char *a0 __asm__("r29");
    register s32 res __asm__("r25");
    register char **walker __asm__("r26");
    register s32 ctr __asm__("r27");
    register f32 c_a8 __asm__("fr22");
    register f32 h2v __asm__("fr23");
    register f64 c_a0 __asm__("fr24");
    register f32 h1v __asm__("fr25");
    register f32 limit __asm__("fr26");
    register f32 dist __asm__("fr27");
    register f32 c_90 __asm__("fr28");
    register f32 c_94 __asm__("fr29");
    register f32 ang __asm__("fr30");
    register f32 b1sum __asm__("fr31");
    register __ps_t pf8 __asm__("fr8");
    register __ps_t pf9 __asm__("fr9");
    register __ps_t pf10 __asm__("fr10");
    register __ps_t *spp __asm__("r9");
    register __ps_t *dpp __asm__("r11");
    register __ps_t *rpp __asm__("r8");
    register f32 p68 __asm__("fr13");
    register f32 p70 __asm__("fr0");
    register char *tw __asm__("r31");
    register char *ent30 __asm__("r30");
    register char *e31 __asm__("r31");
    char *cv;
    char *tbl;
    char *base;
    Unk_90ACC040 *b11;
    char *b12;
    Unk_C4D756ED *comp2;
    register void *comp __asm__("r24");
    s32 count;
    union { u32 w[2]; f64 d; } cvt;
    f32 prod;
    f32 t1;
    f32 t2;

    a0 = (char *)arg0;
    res = 0;
    if (((Unk_43B2646B *)a0)->unk0xA0 == NULL) {
        goto EXIT;
    }
    tbl = (char *)fn_800A7DB4(((Unk_43B2646B *)a0)->unk0xA0);
    __asm__ volatile(
        "li 0, 4\n\t"
        "lwz 9, 0xc(29)\n\t"
        "mtctr 0\n\t"
        "mr 31, 3\n\t"
        "addi 11, 1, 8\n\t"
        "addi 9, 9, 0xd0\n\t"
        "bdnz $\n\t"
        "psq_l 0, 0(9), 0, 0\n\t"
        "lis 3, 0x7a78\n\t"
        "ori 3, 3, 0xf471\n\t"
        "li 4, 0\n\t"
        "psq_st 0, 0(11), 0, 0\n\t"
        "psq_l 12, 8(9), 0, 0\n\t"
        "psq_st 12, 8(11), 0, 0\n\t"
        "psq_l 13, 16(9), 0, 0\n\t"
        "psq_st 13, 16(11), 0, 0\n\t"
        "psq_l 0, 24(9), 0, 0\n\t"
        "psq_st 0, 24(11), 0, 0\n\t"
        "psq_l 12, 32(9), 0, 0\n\t"
        "psq_st 12, 32(11), 0, 0\n\t"
        "psq_l 13, 40(9), 0, 0\n\t"
        "psq_st 13, 40(11), 0, 0\n\t"
        "psq_l 0, 48(9), 0, 0\n\t"
        "psq_st 0, 48(11), 0, 0\n\t"
        "psq_l 12, 56(9), 0, 0\n\t"
        "psq_st 12, 56(11), 0, 0\n\t"
        "bl fn_8012570C\n\t"
        "lis 3, -0x2e1a\n\t"
        "li 4, 0\n\t"
        "ori 3, 3, 0x177b\n\t"
        "fmr 25, 1\n\t"
        "bl fn_8012570C\n\t"
        "lwz 3, 0xc(29)\n\t"
        "lis 4, 0xa01\n\t"
        "fmr 23, 1\n\t"
        "ori 4, 4, 0x5e17\n\t"
        "bl GetChecksum_3\n\t"
        "lwz 9, 0xa0(29)\n\t"
        "mr 24, 3\n\t"
        "lwz 27, 4(9)"
        : "=f"(h1v), "=f"(h2v), "=r"(comp), "=r"(ctr)
        : "r"(a0), "r"(tw), "m"(fr.s88), "m"(fr.s128)
        : "r0", "r3", "r4", "r9", "r11", "fr0", "fr12", "fr13", "lr", "ctr",
          "cr0", "memory");
    if (ctr > 0) {
    __asm__ volatile(
        "lis 9, -0x7fd5\n\t"
        "lis 11, -0x7fd5\n\t"
        "lfd 24, -0x3f60(9)\n\t"
        "mr 26, 31\n\t"
        "lfs 22, -0x3f58(11)"
        : "=f"(c_a0), "=r"(walker), "=f"(c_a8));
    for (;;) {
        ent30 = (char *)*walker;
        if (ent30 == NULL) {
            goto NEXT;
        }
        base = ((Unk_43B2646B *)a0)->unk0xC;
        e31 = ent30;
        if (e31 == base) {
            goto NEXT;
        }
        fs_t = fn_8012570C(QB_PED_MAX_Y_DISTANCE_TO_IGNORE, 1);
        b11 = ((Unk_43B2646B *)a0)->unk0xC;
        t1 = fs_t;
        if (fabsf(b11->unk0x5C - ((Unk_90ACC040 *)e31)->unk0x5C) > t1) {
            goto NEXT;
        }
        /* ---- block 1 (also loads limit + buf pairs used downstream) ---- */
        __asm__ volatile(
            "lis 9, -0x7fd5\n\t"
            "psq_l 13, 248(%0), 0, 0\n\t"
            "psq_l 8, 48(1), 0, 0\n\t"
            "addi 28, 9, -0x4048\n\t"
            "psq_l 9, 0(28), 0, 0\n\t"
            "lis 9, -0x7fd5\n\t"
            "ps_muls0 13, 8, 13\n\t"
            "psq_l 0, 240(%0), 0, 0\n\t"
            "psq_l 10, 40(1), 0, 0\n\t"
            "ps_merge00 13, 13, 9\n\t"
            "lfs 26, -0x3f74(9)\n\t"
            "ps_madd 0, 10, 13, 0\n\t"
            "ps_sum0 0, 0, 0, 0\n\t"
            "psq_st 0, 88(1), 0, 0\n\t"
            "lfs 31, 88(1)"
            : "=f"(pf8), "=f"(pf9), "=f"(pf10), "=f"(limit), "=f"(b1sum)
            : "r"(e31)
            : "fr13", "fr0", "fr28", "r9", "r28", "memory");
        if (!(b1sum > limit)) {
            /* ---- block A ---- */
            __asm__ volatile(
                "psq_l 12, 96(%0), 0, 0\n\t"
                "psq_l 13, 96(%1), 0, 0\n\t"
                "psq_l 0, 88(%0), 0, 0\n\t"
                "psq_l 11, 88(%1), 0, 0\n\t"
                "ps_sub 13, 13, 12\n\t"
                "ps_muls0 12, 8, 13\n\t"
                "psq_st 13, 80(1), 0, 0\n\t"
                "ps_sub 0, 0, 11\n\t"
                "ps_merge00 12, 12, 9\n\t"
                "psq_st 0, 72(1), 0, 0\n\t"
                "ps_madd 0, 10, 12, 0\n\t"
                "ps_sum0 0, 0, 0, 0\n\t"
                "psq_st 0, 96(1), 0, 0"
                :
                : "r"(e31), "r"(b11), "f"(pf8), "f"(pf9), "f"(pf10)
                : "fr11", "fr12", "fr13", "fr0", "memory");
        }
        comp2 = GetChecksum_3(e31, QB_MOTION);
        if (!(b1sum > limit)) {
            if (!(!(comp2->unk0x30 < ((Unk_C4D756ED *)comp)->unk0x30))) {
                goto NEXT;
            }
            b12 = ((Unk_43B2646B *)a0)->unk0xC;
        /* ---- block 3: distance (rsqrte/res) ---- */
            __asm__ volatile(
                "psq_l 13, 88(%0), 0, 0\n\t"
                "psq_l 12, 88(%1), 0, 0\n\t"
                "psq_l 11, 96(%1), 0, 0\n\t"
                "psq_l 0, 96(%0), 0, 0\n\t"
                "ps_sub 13, 13, 12\n\t"
                "psq_l 10, 0(%2), 0, 0\n\t"
                "ps_mul 13, 13, 13\n\t"
                "ps_sub 0, 0, 11\n\t"
                "ps_merge00 0, 0, 10\n\t"
                "ps_madds0 0, 0, 13, 0\n\t"
                "ps_sum0 0, 0, 0, 0\n\t"
                "ps_rsqrte 0, 0\n\t"
                "ps_res 0, 0\n\t"
                "psq_st 0, 104(1), 0, 0\n\t"
                "lfs 27, 104(1)"
                : "=f"(dist)
                : "r"(e31), "r"(b12)
                : "fr8", "fr9", "fr10", "fr11", "fr12", "fr13", "fr0", "r9", "memory");
            if (dist > h1v) {
                goto NEXT;
            }
            /* ---- block 4 ---- */
            __asm__ volatile(
                "psq_l 11, 48(1), 0, 0\n\t"
                "lis 11, -0x7fd5\n\t"
                "psq_l 12, 248(%0), 0, 0\n\t"
                "lis 9, -0x7fd5\n\t"
                "ps_muls0 11, 11, 11\n\t"
                "psq_l 0, 40(1), 0, 0\n\t"
                "psq_l 13, 240(%0), 0, 0\n\t"
                "ps_merge00 11, 11, 10\n\t"
                "lfs 29, -0x3f6c(11)\n\t"
                "ps_muls0 12, 12, 12\n\t"
                "lfs 28, -0x3f70(9)\n\t"
                "ps_madd 0, 0, 11, 0\n\t"
                "ps_merge00 12, 12, 10\n\t"
                "ps_sum0 0, 0, 0, 0\n\t"
                "ps_madd 13, 13, 12, 13\n\t"
                "ps_rsqrte 0, 0\n\t"
                "ps_res 0, 0\n\t"
                "psq_st 0, 112(1), 0, 0\n\t"
                "ps_sum0 13, 13, 13, 13\n\t"
                "ps_rsqrte 13, 13\n\t"
                "ps_res 13, 13\n\t"
                "psq_st 13, 120(1), 0, 0"
                : "=f"(c_94), "=f"(c_90)
                : "r"(e31), "f"(pf10)
                : "fr9", "fr11", "fr12", "fr13", "fr0", "fr28", "fr29", "memory");
            /* ---- clamp chain + angle fn ---- */
            __asm__ volatile(
                "lfs 0, 112(1)\n\t"
                "lfs 13, 120(1)\n\t"
                "fmuls 0, 0, 13\n\t"
                "fdivs 0, %1, 0\n\t"
                "fmr 13, 0\n\t"
                "fcmpu cr0, 0, %2\n\t"
                "ble 0f\n\t"
                "fmr 13, %2\n\t"
                "0:\n\t"
                "fmr 1, 13\n\t"
                "fcmpu cr0, 13, %3\n\t"
                "bge 1f\n\t"
                "fmr 1, %3\n\t"
                "1:"
                : "=f"(ang)
                : "f"(b1sum), "f"(c_94), "f"(c_90)
                : "fr0", "fr13", "memory");
            ang = acosf(ang);
            /* ---- angle wrap via manual int->float dance ---- */
            __asm__ volatile(
                "lis 9, -0x7fd5\n\t"
                "lfs 12, -0x3f68(9)\n\t"
                "fcmpu cr0, %0, 12\n\t"
                "ble 2f\n\t"
                "fdivs 0, %0, 12\n\t"
                "mr 11, 9\n\t"
                "lis 0, 0x4330\n\t"
                "fctiwz 13, 0\n\t"
                "stfd 13, 224(1)\n\t"
                "lwz 9, 228(1)\n\t"
                "xoris 9, 9, 0x8000\n\t"
                "stw 9, 228(1)\n\t"
                "stw 0, 224(1)\n\t"
                "lfd 0, 224(1)\n\t"
                "fsub 0, 0, %1\n\t"
                "frsp 0, 0\n\t"
                "fmuls 0, 0, 12\n\t"
                "fsubs %0, %0, 0\n\t"
                "2:"
                : "+f"(ang)
                : "f"(c_a0)
                : "r9", "r11", "r0", "fr12", "fr13", "fr0", "memory");
            b1sum = ang - c_a8;
            b1sum = __builtin_fabsf(b1sum);
            t2 = fn_8012570C(QB_PED_HEAD_ON_RANGE, 1);
            if (!(b1sum < t2)) {
                goto FINAL;
            }
            /* ---- block 5 ---- */
            __asm__ volatile(
                "psq_l 10, 240(%0), 0, 0\n\t"
                "psq_l 11, 248(%0), 0, 0\n\t"
                "psq_l 12, 40(1), 0, 0\n\t"
                "psq_l 13, 48(1), 0, 0\n\t"
                "ps_merge00 9, 10, 11\n\t"
                "ps_merge10 11, 10, 11\n\t"
                "lfs 30, -0x3f54(9)\n\t"
                "ps_merge00 0, 12, 13\n\t"
                "ps_muls0 0, 0, 9\n\t"
                "ps_merge10 12, 13, 12\n\t"
                "ps_muls0 13, 13, 11\n\t"
                "ps_muls0 12, 12, 10\n\t"
                "ps_merge10 11, 0, 0\n\t"
                "ps_sub 13, 13, 12\n\t"
                "ps_sub 0, 0, 11\n\t"
                "ps_merge10 0, 13, 0\n\t"
                "ps_merge00 13, 13, 13\n\t"
                "psq_st 0, 72(1), 0, 0\n\t"
                "psq_st 13, 128(1), 0, 0\n\t"
                "stfs 29, 132(1)\n\t"
                "lfs 13, 76(1)\n\t"
                "psq_l 12, 128(1), 0, 0\n\t"
                "fcmpu cr0, 13, %1\n\t"
                "ps_mr 0, 12\n\t"
                "psq_st 0, 80(1), 0, 0\n\t"
                "bge 3f\n\t"
                "fmuls 30, %2, 30\n\t"
                "3:"
                :
                : "r"(e31), "f"(limit), "f"(c_90)
                : "fr0", "fr9", "fr10", "fr11", "fr12", "fr13", "fr30", "memory");
        }
FINAL:
        fn_801B5DC4(a0, ang, h2v, dist, h1v);
        res = 1;
        goto NEXTLOOP;
NEXT:
        ;
NEXTLOOP:
        walker += 3;
        ctr -= 1;
        if (ctr != 0) {
            continue;
        }
        break;
    }
    }
EXIT:
    return res;
}
