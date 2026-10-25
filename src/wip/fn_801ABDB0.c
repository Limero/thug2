// WIP DRAFT (non-matching) — hand-rebuilt from disasm (entity collision resolver).
// family=hand range=0x801ABDB0-0x801AC39C size=1516B
// PARKED (full note): 1.3% masked (-mps-float), got=1504B vs want=1516B.
// Semantically complete reconstruction: outer rotated for-loop over
// arg0+0x50 entities (count reloaded per test), ent->ptr(+0x48) null-guard,
// AABB inflate by lbl_802ABBCC(16.0) around ent+8..+24, inner j-walk gated
// by fn_800E9D30(ent,2), six-float overlap test in want's exact order, five
// SNAPS paired-single dances as raw asm (ps_sub / ps_mul /
// ps_merge00-with-{0,0}-pair / ps_madd / ps_sum0 for dist2; ps_rsqrte
// WITHOUT refinement then ps_muls0/ps_mul normalize; dot product vs
// lbl_802ABBD0(-0.99)/lbl_802ABBD4(0.99)), fn_80005854(&spA8,&sp98), rsqrte
// length gate vs lbl_802ABBD8(6.0), x/z spread min-max tests + two 3-term
// fabs equality chains scoring cnt1/cnt2, pick by +0x2C key into
// fn_801AECA4(pick,2).
// Root causes (allocator/scheduling class — same family as A2D4 park):
// 1) want homes 15 GPRs (stmw r17, matched here via the pinned page anchor)
//    but only f31; this shape keeps f27-f31 live across asm dance blocks.
// 2) want REMATERIALIZES the rodata page anchor per constant site (lis r9 /
//    lis r21 / lis r18 ... all 0x802B0000); pinned-anchor + opaque-asm wedge
//    reproduced one (r17) but GCC still CSEs/reuses for later sites.
// 3) want's PS-dance spill points (inv pair at 184/192/208(r1)) sit at exact
//    pressure positions not reachable without (1)+(2).
// Tried: scalar-only body, named __ps_t temps, mem-routed dance temps,
// file/local register pins (r17 anchor), opaque "+r"/"=r" wedges,
// blk-array sizing, volatile count reads. ~8 structural variants.
// extra_cflags: -mps-float
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 3.2% ([3]rev->2.9% [2]rev->3.2%).
#include "types.h"
#include "structs.h"
extern f32 lbl_802ABB78[];
extern f32 lbl_802ABBC4;
extern f32 lbl_802ABBC8;
extern f32 lbl_802ABBCC;
extern f32 lbl_802ABBD0;
extern f32 lbl_802ABBD4;
extern f32 lbl_802ABBD8;
s32 fn_800E9D30(Unk_C7387A53 *, s32);
void fn_80005854(void *, void *);
void fn_801AECA4(Unk_C7387A53 *, s32);

typedef struct __ps_t_ { f32 lo, hi; } ps2;

void fn_801ABDB0(Unk_C7387A53 *arg0) {
    f32 blk[54];
    register char *pg __asm__("r17");
    char *pgv;
    Unk_08077989 *ent;
    Unk_6A666056 *oth;
    Unk_C1F9F519 *op;
    char *base;
    s32 i;
    s32 j;
    s32 n;
    s32 cnt1;
    s32 cnt2;
    s32 hit;
    __ps_t cpair;
    __ps_t d1;
    __ps_t d2;
    __ps_t t;
    __ps_t inv;
    __ps_t inv2;
    f32 dv;
    f32 thr;
    f32 pad;
    f32 dotmin;
    f32 dotmax;
    f32 thr2;
    f32 ax;
    f32 bx;
    f32 az2;
    f32 bz;
    f32 mn;
    f32 mx;

    __asm__("" : "=r"(pg) : "r"((char *)0x802B0000));
    pgv = pg;
    base = *((char * *)&arg0->unk0x48);
    pad = *(f32 *)(pgv - 0x4434);
    thr = *(f32 *)(pgv - 0x443C);
    cpair = *(__ps_t *)(pgv - 0x4488);
    for (i = 0; i < arg0->unk0x50; i++) {
        ent = base + i * 0x60;
        if (ent->unk0x48 == 0) {
            continue;
        }
        op = ((Unk_DBB368F3 *)ent)->unk0x48;
        /* ---- PS dance 1: normalize (ptr-ent) delta pair ---- */
        *((__ps_t *)&((Unk_5F85C510 *)blk)->unk0x8) = ent->unk0x28;
        ((Unk_5F85C510 *)blk)->unk0x10 = ent->unk0x30;
        *((__ps_t *)&((Unk_5F85C510 *)blk)->unk0x18) = op->unk0x28;
        *((__ps_t *)&((Unk_5F85C510 *)blk)->unk0x20) = op->unk0x30;
#define DANCE1(BASEP, BASEE, OUTD) \
        __asm__ volatile("ps_sub %0, %1, %2" \
                         : "=f"(blk[0]) \
                         : "f"(*(BASEP)), "f"(*(BASEE))); \
        *(__ps_t *)(OUTD) = *(__ps_t *)&blk[0];
        __asm__ volatile("ps_sub %0, %1, %2"
                         : "=f"(blk[0])
                         : "f"(*((__ps_t *)&((Unk_5F85C510 *)blk)->unk0x20)),
                           "f"(((Unk_5F85C510 *)blk)->unk0x10));
        ((Unk_130D31C8 *)blk)->unk0x30 = *(__ps_t *)&blk[0];
        __asm__ volatile("ps_mul %0, %1, %1" : "=f"(blk[2]) : "f"(((Unk_130D31C8 *)blk)->unk0x30));
        __asm__ volatile("ps_merge00 %0, %1, %2" : "=f"(blk[2]) : "f"(*(__ps_t *)&blk[2]), "f"(cpair));
        __asm__ volatile("ps_madd %0, %1, %1, %2" : "=f"(blk[2]) : "f"(((Unk_130D31C8 *)blk)->unk0x28), "f"(*(__ps_t *)&blk[2]));
        __asm__ volatile("ps_sum0 %0, %1, %1, %1" : "=f"(blk[0]) : "f"(*(__ps_t *)&blk[2]));
        __asm__("" : "=f"(dv) : "f"(*(__ps_t *)&blk[0]));
        if (thr < dv) {
            __asm__ volatile("ps_rsqrte %0, %1" : "=f"(blk[0]) : "f"(*(__ps_t *)&blk[0]));
            ((Unk_130D31C8 *)blk)->unk0xB8 = *(__ps_t *)&blk[0];
            __asm__ volatile("ps_muls0 %0, %1, %2" : "=f"(blk[2]) : "f"(((Unk_130D31C8 *)blk)->unk0x28), "f"(*(__ps_t *)&blk[0]));
            ((Unk_5F85C510 *)blk)->unk0xBC = lbl_802ABBC8;
            ((Unk_130D31C8 *)blk)->unk0x28 = *(__ps_t *)&blk[2];
            __asm__ volatile("ps_mul %0, %1, %2" : "=f"(blk[2]) : "f"(((Unk_130D31C8 *)blk)->unk0x30), "f"(((Unk_130D31C8 *)blk)->unk0xB8));
            ((Unk_130D31C8 *)blk)->unk0x30 = *(__ps_t *)&blk[2];
        }
        /* ---- AABB inflate ---- */
        *((__ps_t *)&((Unk_5F85C510 *)blk)->unk0x38) = ent->unk0x8;
        *((__ps_t *)&((Unk_5F85C510 *)blk)->unk0x40) = ent->unk0x10;
        ((Unk_5F85C510 *)blk)->unk0x38 -= pad;
        ((Unk_130D31C8 *)blk)->unk0x3C -= pad;
        ((Unk_5F85C510 *)blk)->unk0x40 -= pad;
        *((__ps_t *)&((Unk_5F85C510 *)blk)->unk0x48) = ent->unk0x18;
        ((Unk_5F85C510 *)blk)->unk0x50 = ent->unk0x20;
        ((Unk_130D31C8 *)blk)->unk0x4C += pad;
        ((Unk_5F85C510 *)blk)->unk0x48 += pad;
        *((f32 *)&((Unk_5F85C510 *)blk)->unk0x50) += pad;
        for (j = i + 1; j < arg0->unk0x50 &&
                        fn_800E9D30(ent, 2) != 0;
             j++) {
            oth = base + j * 0x60;
            if (oth->unk0x48 == 0) {
                continue;
            }
            if (oth->unk0x8 > ((Unk_5F85C510 *)blk)->unk0x48) {
                continue;
            }
            if (oth->unk0x18 < ((Unk_5F85C510 *)blk)->unk0x38) {
                continue;
            }
            if (oth->unk0x10 > *((f32 *)&((Unk_5F85C510 *)blk)->unk0x50)) {
                continue;
            }
            if (oth->unk0x20 < ((Unk_5F85C510 *)blk)->unk0x40) {
                continue;
            }
            if (oth->unk0xC > ((Unk_130D31C8 *)blk)->unk0x4C) {
                continue;
            }
            if (oth->unk0x1C < ((Unk_130D31C8 *)blk)->unk0x3C) {
                continue;
            }
            op = ((Unk_DBB368F3 *)oth)->unk0x48;
            /* ---- PS dance 2: normalize (op-oth) delta pair ---- */
            ((Unk_5F85C510 *)blk)->unk0x58 = oth->unk0x28;
            ((Unk_5F85C510 *)blk)->unk0x60 = oth->unk0x30;
            *((__ps_t *)&((Unk_5F85C510 *)blk)->unk0x68) = op->unk0x28;
            *((__ps_t *)&((Unk_5F85C510 *)blk)->unk0x70) = op->unk0x30;
            __asm__ volatile("ps_sub %0, %1, %2"
                             : "=f"(d1)
                             : "f"(*((__ps_t *)&((Unk_5F85C510 *)blk)->unk0x68)),
                               "f"(((Unk_5F85C510 *)blk)->unk0x58));
            __asm__ volatile("ps_sub %0, %1, %2"
                             : "=f"(d2)
                             : "f"(*((__ps_t *)&((Unk_5F85C510 *)blk)->unk0x70)),
                               "f"(((Unk_5F85C510 *)blk)->unk0x60));
            ((Unk_130D31C8 *)blk)->unk0x78 = d1;
            ((Unk_130D31C8 *)blk)->unk0x80 = d2;
            __asm__ volatile("ps_mul %0, %1, %1" : "=f"(t) : "f"(d2));
            __asm__ volatile("ps_merge00 %0, %1, %2" : "=f"(t) : "f"(t), "f"(cpair));
            __asm__ volatile("ps_madd %0, %1, %1, %2" : "=f"(t) : "f"(d1), "f"(t));
            __asm__ volatile("ps_sum0 %0, %1, %1, %1" : "=f"(d2) : "f"(t));
            __asm__("" : "=f"(dv) : "f"(d2));
            if (thr < dv) {
                __asm__ volatile("ps_rsqrte %0, %1" : "=f"(inv) : "f"(d2));
                ((Unk_130D31C8 *)blk)->unk0xC0 = inv;
                __asm__ volatile("ps_muls0 %0, %1, %2" : "=f"(t) : "f"(d1), "f"(inv));
                ((Unk_5F85C510 *)blk)->unk0xC4 = lbl_802ABBC8;
                ((Unk_130D31C8 *)blk)->unk0x78 = t;
                inv = ((Unk_130D31C8 *)blk)->unk0xC0;
                __asm__ volatile("ps_mul %0, %1, %2" : "=f"(d2) : "f"(d2), "f"(inv));
                ((Unk_130D31C8 *)blk)->unk0x80 = d2;
            }
            /* ---- dot of normalized dirs ---- */
            __asm__ volatile("ps_mul %0, %1, %2"
                             : "=f"(t)
                             : "f"(((Unk_130D31C8 *)blk)->unk0x30),
                               "f"(((Unk_130D31C8 *)blk)->unk0x80));
            __asm__ volatile("ps_merge00 %0, %1, %2"
                             : "=f"(t)
                             : "f"(t), "f"(cpair));
            __asm__ volatile("ps_madd %0, %1, %2, %3"
                             : "=f"(t)
                             : "f"(((Unk_130D31C8 *)blk)->unk0x28),
                               "f"(((Unk_130D31C8 *)blk)->unk0x78),
                               "f"(t));
            __asm__ volatile("ps_sum0 %0, %1, %1, %1" : "=f"(d2) : "f"(t));
            ((Unk_130D31C8 *)blk)->unk0xC8 = d2;
            __asm__("" : "=f"(dv) : "f"(d2));
            dotmin = *(f32 *)(pgv - 0x4430);
            if (!(dv < dotmin)) {
                dotmax = *(f32 *)(pgv - 0x442C);
                if (dv <= dotmax) {
                    continue;
                }
            }
            /* ---- G/H deltas + normalize dances ---- */
            cnt1 = 0;
            cnt2 = 0;
            ((Unk_130D31C8 *)blk)->unk0x88 =
                ((Unk_5F85C510 *)blk)->unk0x58 - *((__ps_t *)&((Unk_5F85C510 *)blk)->unk0x8);
            ((Unk_130D31C8 *)blk)->unk0x90 =
                ((Unk_5F85C510 *)blk)->unk0x60 - *((__ps_t *)&((Unk_5F85C510 *)blk)->unk0x8);
            ((Unk_130D31C8 *)blk)->unk0x98 =
                *((__ps_t *)&((Unk_5F85C510 *)blk)->unk0x18) - *((__ps_t *)&((Unk_5F85C510 *)blk)->unk0x8);
            ((Unk_130D31C8 *)blk)->unk0xA0 =
                *((__ps_t *)&((Unk_5F85C510 *)blk)->unk0x20) - *((__ps_t *)&((Unk_5F85C510 *)blk)->unk0x8);
            __asm__ volatile("ps_mul %0, %1, %1"
                             : "=f"(t)
                             : "f"(((Unk_130D31C8 *)blk)->unk0xA0));
            __asm__ volatile("ps_merge00 %0, %1, %2"
                             : "=f"(t)
                             : "f"(t), "f"(cpair));
            __asm__ volatile("ps_madd %0, %1, %1, %2"
                             : "=f"(t)
                             : "f"(((Unk_130D31C8 *)blk)->unk0x98), "f"(t));
            __asm__ volatile("ps_sum0 %0, %1, %1, %1" : "=f"(d2) : "f"(t));
            __asm__("" : "=f"(dv) : "f"(d2));
            if (thr < dv) {
                __asm__ volatile("ps_rsqrte %0, %1" : "=f"(inv) : "f"(d2));
                ((Unk_130D31C8 *)blk)->unk0xD0 = inv;
                __asm__ volatile("ps_muls0 %0, %1, %2"
                                 : "=f"(t)
                                 : "f"(((Unk_130D31C8 *)blk)->unk0x98), "f"(inv));
                ((Unk_5F85C510 *)blk)->unk0xD4 = lbl_802ABBC8;
                ((Unk_130D31C8 *)blk)->unk0x98 = t;
                inv2 = ((Unk_130D31C8 *)blk)->unk0xD0;
                __asm__ volatile("ps_mul %0, %1, %2"
                                 : "=f"(t)
                                 : "f"(((Unk_130D31C8 *)blk)->unk0xA0), "f"(inv2));
                ((Unk_130D31C8 *)blk)->unk0xA0 = t;
            }
            ((Unk_130D31C8 *)blk)->unk0xA8 = ((Unk_130D31C8 *)blk)->unk0x88;
            ((Unk_130D31C8 *)blk)->unk0xB0 = ((Unk_130D31C8 *)blk)->unk0x90;
            fn_80005854((char *)blk + 0xA8, (char *)blk + 0x98);
            __asm__ volatile("ps_mul %0, %1, %1"
                             : "=f"(t)
                             : "f"(((Unk_130D31C8 *)blk)->unk0xB0));
            __asm__ volatile("ps_merge00 %0, %1, %2"
                             : "=f"(t)
                             : "f"(t), "f"(cpair));
            __asm__ volatile("ps_madd %0, %1, %1, %2"
                             : "=f"(t)
                             : "f"(((Unk_130D31C8 *)blk)->unk0xA8), "f"(t));
            __asm__ volatile("ps_sum0 %0, %1, %1, %1" : "=f"(d2) : "f"(t));
            __asm__ volatile("ps_rsqrte %0, %1" : "=f"(inv) : "f"(d2));
            ((Unk_130D31C8 *)blk)->unk0xD8 = inv;
            __asm__("" : "=f"(dv) : "f"(inv));
            thr2 = *(f32 *)(pgv - 0x4428);
            if (dv < thr2) {
                /* x-axis spread */
                mx = mn;
                mn = *((f32 *)&((Unk_5F85C510 *)blk)->unk0x8);
                bx = ((Unk_5F85C510 *)blk)->unk0x68 - *((f32 *)&((Unk_5F85C510 *)blk)->unk0x58);
                ax = *((f32 *)&((Unk_5F85C510 *)blk)->unk0x18) - *((f32 *)&((Unk_5F85C510 *)blk)->unk0x8);
                if (*((f32 *)&((Unk_5F85C510 *)blk)->unk0x18) < mn) {
                    mn = *((f32 *)&((Unk_5F85C510 *)blk)->unk0x18);
                }
                if (*((f32 *)&((Unk_5F85C510 *)blk)->unk0x58) < mn) {
                    mn = *((f32 *)&((Unk_5F85C510 *)blk)->unk0x58);
                }
                if (((Unk_5F85C510 *)blk)->unk0x68 < mn) {
                    mn = ((Unk_5F85C510 *)blk)->unk0x68;
                }
                if (*((f32 *)&((Unk_5F85C510 *)blk)->unk0x18) > mx) {
                    mx = *((f32 *)&((Unk_5F85C510 *)blk)->unk0x18);
                }
                if (*((f32 *)&((Unk_5F85C510 *)blk)->unk0x58) > mx) {
                    mx = *((f32 *)&((Unk_5F85C510 *)blk)->unk0x58);
                }
                if (((Unk_5F85C510 *)blk)->unk0x68 > mx) {
                    mx = ((Unk_5F85C510 *)blk)->unk0x68;
                }
                if (((__builtin_fabs(ax) + __builtin_fabs(bx)) - (mx - mn)) > thr2) {
                    cnt1 = 1;
                }
                /* z-axis spread */
                mx = mn;
                mn = *((f32 *)&((Unk_5F85C510 *)blk)->unk0x8);
                bz = ((Unk_5F85C510 *)blk)->unk0x20 - *((f32 *)&((Unk_5F85C510 *)blk)->unk0x8);
                az2 = ((Unk_5F85C510 *)blk)->unk0x70 - *((f32 *)&((Unk_5F85C510 *)blk)->unk0x60);
                if (((Unk_5F85C510 *)blk)->unk0x20 < mn) {
                    mn = ((Unk_5F85C510 *)blk)->unk0x20;
                }
                if (*((f32 *)&((Unk_5F85C510 *)blk)->unk0x60) < mn) {
                    mn = *((f32 *)&((Unk_5F85C510 *)blk)->unk0x60);
                }
                if (((Unk_5F85C510 *)blk)->unk0x70 < mn) {
                    mn = ((Unk_5F85C510 *)blk)->unk0x70;
                }
                if (((Unk_5F85C510 *)blk)->unk0x20 > mx) {
                    mx = ((Unk_5F85C510 *)blk)->unk0x20;
                }
                if (*((f32 *)&((Unk_5F85C510 *)blk)->unk0x60) > mx) {
                    mx = *((f32 *)&((Unk_5F85C510 *)blk)->unk0x60);
                }
                if (((Unk_5F85C510 *)blk)->unk0x70 > mx) {
                    mx = ((Unk_5F85C510 *)blk)->unk0x70;
                }
                if (((__builtin_fabs(az2) + __builtin_fabs(bz)) - (mx - mn)) > thr2) {
                    cnt1 += 1;
                }
                /* equality chains (x axis, then z axis) */
                hit = 0;
                if ((dv = __builtin_fabs(*((f32 *)&((Unk_5F85C510 *)blk)->unk0x8) - *((f32 *)&((Unk_5F85C510 *)blk)->unk0x18))) < thr2 &&
                    (dv = __builtin_fabs(*((f32 *)&((Unk_5F85C510 *)blk)->unk0x18) - *((f32 *)&((Unk_5F85C510 *)blk)->unk0x58))) < thr2 &&
                    (dv = __builtin_fabs(*((f32 *)&((Unk_5F85C510 *)blk)->unk0x58) - ((Unk_5F85C510 *)blk)->unk0x68)) < thr2) {
                    hit = 1;
                }
                if (hit != 0) {
                    cnt2 = 1;
                }
                hit = 0;
                if ((__builtin_fabs(*((f32 *)&((Unk_5F85C510 *)blk)->unk0x10) - ((Unk_5F85C510 *)blk)->unk0x20) < thr2) &&
                    (__builtin_fabs(((Unk_5F85C510 *)blk)->unk0x20 - *((f32 *)&((Unk_5F85C510 *)blk)->unk0x60)) < thr2) &&
                    (__builtin_fabs(*((f32 *)&((Unk_5F85C510 *)blk)->unk0x60) - ((Unk_5F85C510 *)blk)->unk0x70) < thr2)) {
                    hit = 1;
                }
                if (hit != 0) {
                    cnt2 += 1;
                }
                if (cnt1 + cnt2 > 1) {
                    if (((Unk_DBB368F3 *)ent)->unk0x2C < ((Unk_DBB368F3 *)oth)->unk0x2C) {
                        fn_801AECA4(ent, 2);
                    } else {
                        fn_801AECA4(oth, 2);
                    }
                }
            }
        }
    }
}
