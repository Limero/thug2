// WIP DRAFT — hand-rebuilt C (2026-10-11 round). NOT matching.
// family=m2c range=0x800FF030-0x800FF478 size=1096B
// STATUS: 19.41% (v18), 1092B (1 word SHORT). Best-known body below.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// BREAKTHROUGH (this round): "vpkuhum" park reason is INVALID —
// ps_disasm proves 0x800FF3F8 is plain `psq_stx` (M5.0t xo5=6/7 mislabel).
// Whole function is plain C + PS (no VMX). See docs/parkings/29 CORRECTION.
// CONFIRMED MATCHING PIECES (byte-exact regions): frame/layout (Frame_F030
// struct gives exact r1+offsets), prologue+call setup+loop entry (thru bge),
// helper-call arg sets, ret/count checks, PS copy block (set/order),
// fcmpu/fixup, count++/0x624-check, latch, tail (return count>0).
// LOAD-BEARING DEVICES: extern f32 lbl_8029C1B8 (rodata2 const -> f31);
// volatile tp load (forces path t-reload); register f32 f618v fr1 (f1);
// register u32 raw r8 (forces top-mr, but adds pressure elsewhere);
// explicit goto latch/loop + goto v2else/zjoin2 (preheader + sharing);
// z-before-w store order (v?z before v?w); c2-destroy+reload for count++.
// WALLS (all measured, see <scratch> for variant log):
//  1. v2-then cross-jump over-merge (SAME class as FE42C doc-29 wall):
//     want keeps v2A-then AND v2B-then duplicated (byte-identical incl.
//     regs) + shares only v2-else/v2-zjoin. ngccc merges identical thens
//     (or tails). x-first source merges; y-first source (this body) stays
//     separate but emits y-first+f13 (want: x-first+f0). No per-object flag
//     disables cross-jump (-fno-crossjumping/-fno-jump-optimize rejected;
//     -fno-thread-jumps accepted but irrelevant). ProDG 3.5/3.7/3.8.1 give
//     byte-identical output (version lever dead).
//  2. Head schedule [lis][lfs][lwz-t] vs got [lwz-t][lis]...[lfs late]:
//     f31c-init will not LICM-hoist (slot stores block); guard-shape fixes
//     placement but costs a saved reg (stmw r24, frame 0x1090). For-loop kept.
//  3. Coloring: and.-operand swap, vertex/copy reg homes, call-arg addi
//     order (r5,r6 first in want), stb placement, top-mr/nodemask roles.
// NEXT (untried): revisit head + homes after any v2 breakthrough; FF478 is
// the twin (same lessons apply; different arg layout/helpers).
#include "types.h"

s32 fn_800FABC0(void *a0, void *a1, void *a2, void *a3, void *a4, void *a5);
s32 fn_800FA000(void *a0, void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7);
u16 *fn_8010391C(void *a0, s32 a1, void *a2, void *a3, s32 a4);

extern f32 lbl_8029C1B8;

typedef struct Frame_F030 {
    u8 sp8[0x1000];     /* +0x0000 -> r1+0x08 */
    f32 v0x, v0y, v0z, v0w; /* +0x1000 -> r1+0x1008 */
    f32 v1x, v1y, v1z, v1w; /* +0x1010 -> r1+0x1018 */
    f32 v2x, v2y, v2z, v2w; /* +0x1020 -> r1+0x1028 */
    __ps_t o1a;         /* +0x1030 -> r1+0x1038 */
    __ps_t o1b;         /* +0x1038 -> r1+0x1040 */
    __ps_t o2a;         /* +0x1040 -> r1+0x1048 */
    __ps_t o2b;         /* +0x1048 -> r1+0x1050 */
    u32 cnt1058;        /* +0x1050 -> r1+0x1058 */
    f32 tmp105C;        /* +0x1054 -> r1+0x105C */
} Frame_F030;

s32 fn_800FF030(void *arg0, void *arg1, s32 arg2, void *arg3) {
    Frame_F030 fr;
    f32 f31c;
    register f32 f618v __asm__("fr1");
    u32 i;
    u8 *cur;
    u8 *t;
    u8 *tp;
    u8 *t1;
    u8 *t2;
    s32 o;
    u8 *cb;
    u32 node;
    register u32 raw __asm__("r8");
    u16 state;
    u16 st;
    s32 ret;
    s32 c2;
    s32 off;
    u8 *slot;

    i = 0;
    cur = (u8 *)fn_8010391C(*(void **)((u8 *)arg0 + 8), arg2, &fr.cnt1058, fr.sp8, 0x800);
    for (; i < fr.cnt1058; i++, cur += 2) {
        f31c = lbl_8029C1B8;
        t = *(u8 **)((u8 *)arg0 + 8);
        node = *(u16 *)cur;
        raw = node;
        node &= 0xFFFF;
        if (*(u8 *)(t + 0xA)) {
            st = ((u16 *)(*(void **)(t + 0xC)))[node * 4];
        } else {
            st = *(u16 *)((u8 *)(*(void **)(t + 0xC)) + node * 10);
        }
        state = st;
        if ((state & *(u16 *)((u8 *)arg3 + 0x620)) != 0) {
            continue;
        }
        if ((*(u16 *)((u8 *)arg3 + 0x622) & ~state) != 0) {
            continue;
        }
        tp = *(u8 * volatile *)((u8 *)arg0 + 8);
        if (*(u8 *)(tp + 0xA)) {
            u8 *row = (u8 *)(*(void **)(tp + 0xC)) + (raw << 3);
            u8 idx;
            u8 *c;
            idx = row[4];
            c = *(u8 **)(tp + 0x3C);
            if (c != 0) {
                o = idx * 12;
                fr.v0x = *(f32 *)(c + o);
                fr.v0y = *(f32 *)(*(u8 **)(tp + 0x3C) + o + 4);
                cb = *(u8 **)(tp + 0x3C);
            } else {
                u8 *c30 = *(u8 **)(tp + 0x30);
                o = idx * 12;
                fr.v0x = *(f32 *)(c30 + o);
                fr.v0y = *(f32 *)(*(u8 **)(tp + 0x30) + o + 4);
                cb = *(u8 **)(tp + 0x30);
            }
            fr.v0z = *(f32 *)(cb + o + 8);
            fr.v0w = f31c;
            t1 = *(u8 **)((u8 *)arg0 + 8);
            idx = row[5];
            c = *(u8 **)(t1 + 0x3C);
            if (c != 0) {
                o = idx * 12;
                fr.v1x = *(f32 *)(c + o);
                fr.v1y = *(f32 *)(*(u8 **)(t1 + 0x3C) + o + 4);
                cb = *(u8 **)(t1 + 0x3C);
            } else {
                u8 *c30 = *(u8 **)(t1 + 0x30);
                o = idx * 12;
                fr.v1x = *(f32 *)(c30 + o);
                fr.v1y = *(f32 *)(*(u8 **)(t1 + 0x30) + o + 4);
                cb = *(u8 **)(t1 + 0x30);
            }
            fr.v1z = *(f32 *)(cb + o + 8);
            fr.v1w = f31c;
            t2 = *(u8 **)((u8 *)arg0 + 8);
            idx = row[6];
            c = *(u8 **)(t2 + 0x3C);
            if (c != 0) {
                o = idx * 12;
                fr.v2y = *(f32 *)(*(u8 **)(t2 + 0x3C) + o + 4);
                fr.v2x = *(f32 *)(c + o);
                cb = *(u8 **)(t2 + 0x3C);
                goto zjoin2;
            } else {
                goto v2else;
            }
        } else {
            u8 *row = (u8 *)(*(void **)(tp + 0xC)) + (raw & 0xFFFF) * 10;
            u16 idx;
            u8 *c;
            idx = *(u16 *)(row + 4);
            c = *(u8 **)(tp + 0x3C);
            if (c != 0) {
                o = idx * 12;
                fr.v0x = *(f32 *)(c + o);
                fr.v0y = *(f32 *)(*(u8 **)(tp + 0x3C) + o + 4);
                cb = *(u8 **)(tp + 0x3C);
            } else {
                u8 *c30 = *(u8 **)(tp + 0x30);
                o = idx * 12;
                fr.v0x = *(f32 *)(c30 + o);
                fr.v0y = *(f32 *)(*(u8 **)(tp + 0x30) + o + 4);
                cb = *(u8 **)(tp + 0x30);
            }
            fr.v0z = *(f32 *)(cb + o + 8);
            fr.v0w = f31c;
            t1 = *(u8 **)((u8 *)arg0 + 8);
            idx = *(u16 *)(row + 6);
            c = *(u8 **)(t1 + 0x3C);
            if (c != 0) {
                o = idx * 12;
                fr.v1x = *(f32 *)(c + o);
                fr.v1y = *(f32 *)(*(u8 **)(t1 + 0x3C) + o + 4);
                cb = *(u8 **)(t1 + 0x3C);
            } else {
                u8 *c30 = *(u8 **)(t1 + 0x30);
                o = idx * 12;
                fr.v1x = *(f32 *)(c30 + o);
                fr.v1y = *(f32 *)(*(u8 **)(t1 + 0x30) + o + 4);
                cb = *(u8 **)(t1 + 0x30);
            }
            fr.v1z = *(f32 *)(cb + o + 8);
            fr.v1w = f31c;
            t2 = *(u8 **)((u8 *)arg0 + 8);
            idx = *(u16 *)(row + 8);
            c = *(u8 **)(t2 + 0x3C);
            if (c != 0) {
                o = idx * 12;
                fr.v2x = *(f32 *)(c + o);
                fr.v2y = *(f32 *)(*(u8 **)(t2 + 0x3C) + o + 4);
                cb = *(u8 **)(t2 + 0x3C);
                goto zjoin2;
            } else {
            v2else:
                o = idx * 12;
                {
                    u8 *c30 = *(u8 **)(t2 + 0x30);
                    fr.v2x = *(f32 *)(c30 + o);
                    fr.v2y = *(f32 *)(*(u8 **)(t2 + 0x30) + o + 4);
                    cb = *(u8 **)(t2 + 0x30);
                }
            }
        }
zjoin2:
            fr.v2z = *(f32 *)(cb + o + 8);
            fr.v2w = f31c;
        f618v = *(f32 *)((u8 *)arg3 + 0x618);
        fr.tmp105C = f31c;
        if (f618v == f31c) {
            ret = fn_800FABC0(arg1, &fr.v0x, &fr.v1x, &fr.v2x, &fr.o1a, &fr.o2a);
        } else {
            ret = fn_800FA000(arg1, &fr.v0x, &fr.v1x, &fr.v2x, &fr.tmp105C, (u8 *)arg3 + 0x608, &fr.o1a, &fr.o2a);
        }
        if (ret != 0) {
            c2 = *(s32 *)((u8 *)arg3 + 0x61C);
            if (c2 != 0x20) {
                off = c2 * 0x30 + 8;
                slot = (u8 *)arg3 + off;
                *(__ps_t *)(slot + 24) = fr.o2a;
                *(__ps_t *)(slot + 32) = fr.o2b;
                slot[0x2C] = (u8)(state & 0x40);
                *(u32 *)(slot + 0x28) = *(u32 *)arg0;
                *(__ps_t *)((u8 *)arg3 + off) = fr.o1a;
                *(__ps_t *)(slot + 8) = fr.o1b;
                if (*(f32 *)((u8 *)arg3 + 0x618) > f31c) {
                    *(f32 *)(slot + 0x10) = fr.tmp105C;
                }
                *(s32 *)((u8 *)arg3 + 0x61C) = *(s32 *)((u8 *)arg3 + 0x61C) + 1;
                if (*(s32 *)((u8 *)arg3 + 0x624) == 2) {
                    return 1;
                }
            } else {
                return 1;
            }
        }
    }
    return *(s32 *)((u8 *)arg3 + 0x61C) > 0;
}
