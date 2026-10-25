// WIP draft - PARKED.
// TRIAGED 2026-10-18: stwu -0x1190 with stfd f30/f31 + stmw r14 (FPR-saving
// giant frame, known +8B quirk blocker per AGENTS.md). Full rebuild material
// after the FPR-quirk breakthrough; do not grind scheduling on the m2c husk.
// family=m2c range=0x8010048C-0x80100F08 size=2684B
// extra_cflags: -mps-float
//
// The opcode-4 stream is Gekko paired-single, not AltiVec: the previous VMX
// parking note was a disassembly-label artifact. This reconstruction models
// the bbox setup, query loop, vertex extraction, hit-record test, and PS
// normalization/intersection path in C.
//
// Current masked score: DIFF 1.0% with
// tools/score_body.py 0x8010048C <file> -mps-float.
// Remaining blocker: ngccc assigns a different GPR/FPR save map and frame
// homes, and the scalar/PS hit-record tail and branch scheduling are not yet
// reproduced byte-for-byte. No inline assembly is used.
#include "types.h"

typedef union {
    __ps_t p;
    f32 f[2];
} Pair;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

typedef struct {
    volatile char data[0x1110];
    volatile f32 scratch[6];
} Frame;

#define FP(fr, off) (*(__ps_t *)((char *)(fr) + (off)))
#define FV(fr, off) (*(volatile f32 *)((char *)(fr) + (off)))
#define FI(fr, off) (*(volatile s32 *)((char *)(fr) + (off)))

extern f32 lbl_8029C1D8;
extern f32 lbl_8029C1DC;
extern __ps_t lbl_8029C060;
extern void fn_80006C60(void *);
extern void fn_800FD9A8(void *, f32 *, f32 *);
extern void fn_8000723C(__ps_t *, __ps_t *);
extern void fn_8000728C(f32 *, f32 *);
extern u16 *fn_8010391C(void *, void *, u32 *, void *, s32);
extern s32 fn_800F8858(void *, f32 *, f32 *, f32 *, f32 *, void *);
extern void fn_8008757C(void *, f32 *, f32 *);

#define NORMALIZE(a, b, dst) do { \
    __ps_t qa = (a); \
    __ps_t qb = (b); \
    __ps_t qzero = lbl_8029C060; \
    __ps_t qd = __builtin_ps_mul(qa, qa); \
    __ps_t qs; \
    Pair qv; \
    f32 dot; \
    qd = __builtin_ps_merge00(qd, qzero); \
    qd = __builtin_ps_madd(qb, qb, qd); \
    qs = __builtin_ps_sum0(qd, qd, qd); \
    qv.p = qs; \
    dot = qv.f[0]; \
    if (dot > 0.0f) { \
        __ps_t qr = __builtin_ps_rsqrte(qs); \
        __ps_t qn = __builtin_ps_muls0(qb, qr); \
        (dst)[0] = qn; \
        (dst)[1] = __builtin_ps_mul(qa, qn); \
    } \
} while (0)

s32 fn_8010048C(void *arg0, f32 *arg1, void *arg2, void *arg3) {
    Frame fr;
    char *sp8;
    char *bbox;
    char *p58;
    char *node;
    char *index;
    char *verts;
    char *entry;
    char *hit;
    char *rec;
    f32 *a0;
    f32 *hf;
    f32 f30;
    f32 f31;
    f32 one;
    u32 count;
    u32 iter;
    u32 state;
    u32 mask0;
    u32 mask1;
    u32 code;
    u32 hit_count;
    u16 node_index;
    u16 *cursor;
    __ps_t p0;
    __ps_t p1;
    __ps_t p2;
    __ps_t p3;
    __ps_t p4;
    __ps_t p5;
    Vec4 *v0;
    Vec4 *v1;
    Vec4 *v2;
    s32 i;
    s32 spin;

    sp8 = (char *)&fr;
    bbox = sp8 + 0x30;
    p58 = sp8 + 0x50;
    a0 = (f32 *)arg0;
    f30 = lbl_8029C1D8;
    one = lbl_8029C1DC;

    fn_80006C60(sp8);
    fn_800FD9A8(arg0, arg1, (f32 *)sp8);
    fn_8000723C((__ps_t *)bbox, (__ps_t *)sp8);

    p0 = FP(&fr, 0x18);
    p1 = FP(&fr, 0x20);
    p2 = FP(&fr, 0x00);
    p3 = FP(&fr, 0x08);
    FP(&fr, 0x50) = __builtin_ps_add(p2, p0);
    FP(&fr, 0x58) = __builtin_ps_add(p3, p1);
    FI(&fr, 0x10E4) = 0;
    fn_8000728C((f32 *)bbox, (f32 *)p58);

    p0 = FP(&fr, 0x28);
    p1 = FP(&fr, 0x30);
    p2 = FP(&fr, 0x00);
    p3 = FP(&fr, 0x08);
    FP(&fr, 0x50) = __builtin_ps_add(p2, p0);
    FP(&fr, 0x58) = __builtin_ps_add(p3, p1);
    fn_8000728C((f32 *)bbox, (f32 *)p58);

    p0 = FP(&fr, 0x08);
    p1 = FP(&fr, 0x00);
    p2 = FP(&fr, 0x18);
    p3 = FP(&fr, 0x20);
    p4 = FP(&fr, 0x28);
    p5 = FP(&fr, 0x30);
    p0 = __builtin_ps_add(p1, p2);
    p1 = __builtin_ps_add(p0, p3);
    p2 = __builtin_ps_add(p1, p4);
    p3 = __builtin_ps_add(p0, p5);
    FP(&fr, 0x60) = p2;
    FP(&fr, 0x50) = p1;
    FP(&fr, 0x58) = p3;
    FP(&fr, 0x68) = p0;
    fn_8000728C((f32 *)bbox, (f32 *)p58);

    node = *(char **)(sp8 + 0x8);
    cursor = fn_8010391C(node, sp8 + 0x30, (u32 *)(sp8 + 0x10D0),
                         sp8 + 0x70, 0x800);
    count = FI(&fr, 0x10D0);
    iter = 0;
    *(volatile void **)(sp8 + 0x10E8) = (void *)(sp8 + 0x10C0);
    if (iter < count) {
        FV(&fr, 0x10D0) = f30;
        do {
            node = *(char **)((char *)arg0 + 0x8);
            node_index = *cursor;
            if (*(u8 *)(node + 0xA) != 0) {
                index = *(char **)(node + 0xC);
                state = *(u16 *)(index + node_index * 8);
                entry = index + node_index * 8;
            } else {
                index = *(char **)(node + 0xC);
                state = *(u16 *)(index + node_index * 10);
                entry = index + node_index * 10;
            }
            mask0 = *(u16 *)((char *)arg3 + 0xD04);
            mask1 = *(u16 *)((char *)arg3 + 0xD06);
            if ((state & mask0) == 0 && (mask1 & ~state) == 0) {
                if (*(u8 *)(node + 0xA) != 0) {
                    verts = *(char **)(node + 0x3C);
                    if (verts == 0) {
                        verts = *(char **)(node + 0x30);
                    }
                    v0 = (Vec4 *)(sp8 + 0x50);
                    v1 = (Vec4 *)(sp8 + 0x60);
                    v2 = (Vec4 *)(sp8 + 0x70);
                    hf = (f32 *)(verts + *(u8 *)(entry + 4) * 12);
                    v0->x = hf[0];
                    v0->y = hf[1];
                    v0->z = hf[2];
                    v0->w = f30;
                    hf = (f32 *)(verts + *(u8 *)(entry + 5) * 12);
                    v1->x = hf[0];
                    v1->y = hf[1];
                    v1->z = hf[2];
                    v1->w = f30;
                    hf = (f32 *)(verts + *(u8 *)(entry + 6) * 12);
                    v2->x = hf[0];
                    v2->y = hf[1];
                    v2->z = hf[2];
                    v2->w = f30;
                } else {
                    verts = *(char **)(node + 0x3C);
                    if (verts == 0) {
                        verts = *(char **)(node + 0x30);
                    }
                    v0 = (Vec4 *)(sp8 + 0x50);
                    v1 = (Vec4 *)(sp8 + 0x60);
                    v2 = (Vec4 *)(sp8 + 0x70);
                    hf = (f32 *)(verts + *(u16 *)(entry + 4) * 12);
                    v0->x = hf[0];
                    v0->y = hf[1];
                    v0->z = hf[2];
                    v0->w = f30;
                    hf = (f32 *)(verts + *(u16 *)(entry + 6) * 12);
                    v1->x = hf[0];
                    v1->y = hf[1];
                    v1->z = hf[2];
                    v1->w = f30;
                    hf = (f32 *)(verts + *(u16 *)(entry + 8) * 12);
                    v2->x = hf[0];
                    v2->y = hf[1];
                    v2->z = hf[2];
                    v2->w = f30;
                }
                spin = 1;
                do {
                    spin--;
                } while (spin != 0);
                if (fn_800F8858(sp8, (f32 *)p58,
                                (f32 *)(sp8 + 0x60),
                                (f32 *)(sp8 + 0x1070),
                                (f32 *)(sp8 + 0x1080),
                                (void *)(sp8 + 0x10D8)) != 0) {
                    hit_count = *(u32 *)((char *)arg3 + 0xD00);
                    if (hit_count == 0x20) {
                        return 1;
                    }
                    hit = (char *)arg3 + hit_count * 0x68;
                    *(volatile u8 *)(hit + 0x64) = (u8)((state >> 25) & 1);
                    *(volatile u32 *)(hit + 0x60) = *(u32 *)arg0;

                    {
                    __ps_t p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13;
                    __ps_t zero;
                    Pair qv;
                    zero = lbl_8029C060;
                    p0 = FP(&fr, 0x80);
                    p1 = FP(&fr, 0x60);
                    p2 = FP(&fr, 0x58);
                    p3 = FP(&fr, 0x68);
                    p4 = __builtin_ps_sub(p1, p0);
                    p5 = __builtin_ps_sub(p3, p2);
                    FP(&fr, 0x10B0) = p4;
                    FP(&fr, 0x10B8) = p5;
                    p6 = FP(&fr, 0x1078);
                    p7 = FP(&fr, 0x1070);
                    p8 = FP(&fr, 0x80);
                    p9 = __builtin_ps_sub(p7, p8);
                    FP(&fr, 0x10C0) = p9;
                    p10 = __builtin_ps_sub(p6, FP(&fr, 0x58));
                    FP(&fr, 0x10C8) = p10;
                    p11 = __builtin_ps_merge10(FP(&fr, 0x10C0), FP(&fr, 0x10D0));
                    p12 = __builtin_ps_merge10(FP(&fr, 0x10B0), FP(&fr, 0x10B8));
                    p11 = __builtin_ps_mul(p12, FP(&fr, 0x10C0));
                    p12 = __builtin_ps_mul(FP(&fr, 0x10B0), p11);
                    p13 = __builtin_ps_merge00(FP(&fr, 0x10C0), FP(&fr, 0x10D0));
                    p11 = __builtin_ps_sub(p12, p11);
                    p12 = __builtin_ps_merge00(FP(&fr, 0x10B8), FP(&fr, 0x10B0));
                    p12 = __builtin_ps_mul(p12, p13);
                    FP(&fr, 0x10F0) = __builtin_ps_merge00(p11, p11);
                    FV(&fr, 0x10F4) = one;
                    p13 = __builtin_ps_merge10(p11, __builtin_ps_sub(p12,
                             __builtin_ps_merge10(p12, p12)));
                    FP(&fr, 0x10A0) = p13;
                    p0 = FP(&fr, 0x10F0);
                    FP(&fr, 0x10A8) = p0;
                    p0 = __builtin_ps_mul(p0, p0);
                    p0 = __builtin_ps_merge00(p0, zero);
                    p0 = __builtin_ps_madd(p13, p13, p0);
                    p0 = __builtin_ps_sum0(p0, p0, p0);
                    qv.p = p0; if (qv.f[0] > f30) {
                        p1 = FP(&fr, 0x10A8);
                        p2 = __builtin_ps_rsqrte(p0);
                        FP(&fr, 0x1100) = p2;
                        p2 = __builtin_ps_muls0(p13, p2);
                        FP(&fr, 0x10A0) = p2;
                        p1 = __builtin_ps_mul(p1, p2);
                        FP(&fr, 0x10A8) = p1;
                    }
                    FP(&fr, 0x10B0) = FP(&fr, 0x10A0);
                    FP(&fr, 0x10B8) = FP(&fr, 0x10A8);
                    FP(&fr, 0x10C0) = FP(&fr, 0x10A0);
                    FP(&fr, 0x10C8) = FP(&fr, 0x10A8);
                    fr.scratch[0] = *(volatile f32 *)(hit + 4);
                    fr.scratch[1] = *(volatile f32 *)(hit + 8);
                    fr.scratch[2] = *(volatile f32 *)((char *)arg3 + hit_count * 0x68);
                    fr.scratch[3] = fr.scratch[0] * a0[12];
                    fr.scratch[4] = fr.scratch[2] * a0[8] + fr.scratch[3];
                    fr.scratch[5] = fr.scratch[1] * a0[8] + fr.scratch[4];
                    fr.scratch[5] += a0[20];
                    FV(&fr, 0x10B0) = fr.scratch[5];
                    fr.scratch[3] = fr.scratch[0] * a0[13];
                    fr.scratch[4] = fr.scratch[2] * a0[9] + fr.scratch[3];
                    fr.scratch[5] = fr.scratch[1] * a0[9] + fr.scratch[4];
                    fr.scratch[5] += a0[21];
                    FV(&fr, 0x10B4) = fr.scratch[5];
                    fr.scratch[3] = fr.scratch[0] * a0[14];
                    fr.scratch[4] = fr.scratch[2] * a0[10] + fr.scratch[3];
                    fr.scratch[5] = fr.scratch[1] * a0[10] + fr.scratch[4];
                    fr.scratch[5] += a0[22];
                    FV(&fr, 0x10B8) = fr.scratch[5];
                    fr.scratch[3] = fr.scratch[0] * a0[15];
                    fr.scratch[4] = fr.scratch[2] * a0[11] + fr.scratch[3];
                    fr.scratch[5] = fr.scratch[1] * a0[11] + fr.scratch[4];
                    fr.scratch[5] += a0[23];
                    FV(&fr, 0x10BC) = fr.scratch[5];
                    fn_8008757C(sp8 + 0x10A8, (f32 *)a0 + 8,
                                 (f32 *)(sp8 + 0x60));
                    f31 = f30;
                    rec = hit + 0x28;
                    for (i = 0; i < 4; i++) {
                        code = FI(&fr, 0x10DC - i * 4);
                        *(volatile u8 *)(rec + 0x20) = (u8)(code != 0);
                        if (code == 1) {
                            NORMALIZE(FP((char *)hit, 0x50), FP((char *)hit, 0x58),
                                      (volatile __ps_t *)(rec + 0x10));
                        } else if (code == 2) {
                            NORMALIZE(FP((char *)hit, 0x38), FP((char *)hit, 0x40),
                                      (volatile __ps_t *)(rec + 0x10));
                        } else if (code == 3) {
                            NORMALIZE(FP((char *)hit, 0x20), FP((char *)hit, 0x28),
                                      (volatile __ps_t *)(rec + 0x10));
                        }
                        rec -= 0x28;
                    }
                    *(volatile u32 *)((char *)arg3 + 0xD00) = hit_count + 1;
                }
            }
            }
            iter++;
            cursor += 2;
        } while (iter < count);
    }
    return *(u32 *)((char *)arg3 + 0xD00) > 0;
}
