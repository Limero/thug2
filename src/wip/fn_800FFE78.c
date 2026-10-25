// WIP DRAFT - hand-rebuild v3 from disasm (2026-10-07): union Pair slots,
// PARKED 2026-10-07: frame is 0x40 short (want stwu -0x1170, got -0x1130);
//   the shortfall is entirely in the tail — want's c1058..c10E8 pair run plus
//   sp10F0/sp10F4/sp10F8 and c1100/c1108/sp1110 occupy 0x1058..0x1118 (0xc0) while
//   got occupies 0x80, i.e. ngccc keeps ~5 tail `Pair` locals in FPRs.  A
//   `volatile s32 sp10F8` experiment measured 3.34% vs 4.37%, so it was reverted.
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 3.0848% -> 4.3702% `volatile` keyword(s) removed from the body
// volatile pair reloads + volatile base reads, (off+base) addressing,
// split slwi/add, fetch3 prologue inline per path with shared zero tail,
// scalar const temps, ucmp-union fcmpu idiom.
//
// family=m2c range=0x800FFE78-0x8010048C size=1556B
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

void fn_800063B4(void *);
void fn_800FD81C(void *, void *, void *);
void fn_8000723C(__ps_t *, __ps_t *);
void fn_8000728C(f32 *, f32 *);
u16 *fn_8010391C(void *, void *, u32 *, void *, s32);
s32 fn_800F6DE0(void *, void *, void *, void *, void *, void *);
void fn_8008757C(void *, void *, void *, void *, void *, void *);
s32 fn_800F6AD0(void *, void *, void *, s32, f32);
extern f32 lbl_8029C1D0;
extern f32 lbl_8029C1D4;
extern __ps_t lbl_8029C060[];

typedef union {
    __ps_t ps;
    f32 f[2];
} Pair;

s32 fn_800FFE78(Unk_A9157FE7 *arg0, void *arg1, s32 arg2, s32 arg3) {
    __ps_t b8[2];
    __ps_t b18[2];
    __ps_t b28[2];
    __ps_t b38[4];
    u8 qbuf[0x800];
    u8 pad0858[0x800];
    Pair c1058;
    Pair c1060;
    Pair c1068;
    Pair c1070;
    Pair c1078;
    Pair c1080;
    Pair c1088;
    Pair c1090;
    Pair c1098;
    Pair c10A0;
    s32 sp10A8;
    Pair c10B0;
    Pair c10B8;
    Pair c10C0;
    Pair c10C8;
    Pair c10D0;
    Pair c10D8;
    Pair e10;
    Pair e11;
    u32 sp10F0;
    f32 sp10F4;
    s32 sp10F8;
    Pair c1100;
    Pair c1108;
    void *sp1110;
    s32 var_r15;
    u32 var_r16;
    u16 *var_r22;
    f32 c;
    f32 sconst;
    __ps_t t0;
    __ps_t t8;
    __ps_t t9;
    __ps_t t10;
    __ps_t t11;
    __ps_t t12;
    __ps_t t13;
    Pair ucmp;
    char *r23;
    char *e7;
    s32 off;
    s32 bz;
    s32 qoff;
    f32 v;
    s32 node;
    s32 node3;
    s32 tab;
    s32 bx;
    u16 sel3;

    sp10F8 = arg3;
    fn_800063B4(&b8);
    var_r15 = 0;
    fn_800FD81C(arg0, arg1, &b8);
    var_r16 = 0;
    t13 = b18[0];
    t12 = b8[1];
    t11 = b8[0];
    t0 = b18[1];
    t13 = __builtin_ps_sub(t13, t11);
    t0 = __builtin_ps_sub(t0, t12);
    b28[0] = t13;
    b28[1] = t0;
    fn_8000723C(b38, b8);
    fn_8000728C((f32 *)b38, (f32 *)b18);
    var_r22 = fn_8010391C((void *)arg0->unk0x8, b38, &sp10F0, qbuf, 0x800);
    if ((u32)var_r15 < sp10F0) {
        c = lbl_8029C1D0;
        sp1110 = &e11.f[0];
        r23 = (char *)arg0 + 0x20;
        do {
            node = *(s32 *)&arg0->unk0x8;
            if (*(u8 *)((char *)node + 0xA) != 0) {
                u16 qi = var_r22[0];
                tab = *(s32 *)((char *)node + 0xC);
                qoff = (s32)(qi << 3);
                bx = *(s32 *)((char *)node + 0x3C);
                e7 = (char *)tab + qoff;
                off = (s32)*(u8 *)(e7 + 4) * 12;
                if (bx != 0) {
                    v = *(f32 *)(off + bx);
                    c1058.f[0] = v;
                    bx = *(s32 *)((char *)node + 0x3C);
                    v = *(f32 *)(off + bx + 4);
                    c1058.f[1] = v;
                    bz = *(s32 *)((char *)node + 0x3C);
                } else {
                    bx = *(s32 *)((char *)node + 0x30);
                    v = *(f32 *)(off + bx);
                    c1058.f[0] = v;
                    bx = *(s32 *)((char *)node + 0x30);
                    v = *(f32 *)(off + bx + 4);
                    c1058.f[1] = v;
                    bz = *(s32 *)((char *)node + 0x30);
                }
                v = *(f32 *)(off + bz + 8);
                c1060.f[1] = c;
                c1060.f[0] = v;
                node = *(s32 *)&arg0->unk0x8;
                bx = *(s32 *)((char *)node + 0x3C);
                off = (s32)*(u8 *)(e7 + 5) * 12;
                if (bx != 0) {
                    v = *(f32 *)(off + bx);
                    c1068.f[0] = v;
                    bx = *(s32 *)((char *)node + 0x3C);
                    v = *(f32 *)(off + bx + 4);
                    c1068.f[1] = v;
                    bz = *(s32 *)((char *)node + 0x3C);
                } else {
                    bx = *(s32 *)((char *)node + 0x30);
                    v = *(f32 *)(off + bx);
                    c1068.f[0] = v;
                    bx = *(s32 *)((char *)node + 0x30);
                    v = *(f32 *)(off + bx + 4);
                    c1068.f[1] = v;
                    bz = *(s32 *)((char *)node + 0x30);
                }
                v = *(f32 *)(off + bz + 8);
                c1070.f[1] = c;
                c1070.f[0] = v;
                node3 = *(s32 *)&arg0->unk0x8;
                sel3 = *(u8 *)(e7 + 6);
                bx = *(s32 *)((char *)node3 + 0x3C);
                if (bx != 0) {
                    off = (s32)sel3 * 12;
                    v = *(f32 *)(off + bx);
                    c1078.f[0] = v;
                    bx = *(s32 *)((char *)node3 + 0x3C);
                    v = *(f32 *)(off + bx + 4);
                    c1078.f[1] = v;
                    bz = *(s32 *)((char *)node3 + 0x3C);
                    goto join;
                } else {
                    goto tail3;
                }
            } else {
                u16 qi = var_r22[0];
                tab = *(s32 *)((char *)node + 0xC);
                qoff = (s32)(qi * 10);
                bx = *(s32 *)((char *)node + 0x3C);
                e7 = (char *)tab + qoff;
                off = (s32)*(u16 *)(e7 + 4) * 12;
                if (bx != 0) {
                    v = *(f32 *)(off + bx);
                    c1058.f[0] = v;
                    bx = *(s32 *)((char *)node + 0x3C);
                    v = *(f32 *)(off + bx + 4);
                    c1058.f[1] = v;
                    bz = *(s32 *)((char *)node + 0x3C);
                } else {
                    bx = *(s32 *)((char *)node + 0x30);
                    v = *(f32 *)(off + bx);
                    c1058.f[0] = v;
                    bx = *(s32 *)((char *)node + 0x30);
                    v = *(f32 *)(off + bx + 4);
                    c1058.f[1] = v;
                    bz = *(s32 *)((char *)node + 0x30);
                }
                v = *(f32 *)(off + bz + 8);
                c1060.f[1] = c;
                c1060.f[0] = v;
                node = *(s32 *)&arg0->unk0x8;
                bx = *(s32 *)((char *)node + 0x3C);
                off = (s32)*(u16 *)(e7 + 6) * 12;
                if (bx != 0) {
                    v = *(f32 *)(off + bx);
                    c1068.f[0] = v;
                    bx = *(s32 *)((char *)node + 0x3C);
                    v = *(f32 *)(off + bx + 4);
                    c1068.f[1] = v;
                    bz = *(s32 *)((char *)node + 0x3C);
                } else {
                    bx = *(s32 *)((char *)node + 0x30);
                    v = *(f32 *)(off + bx);
                    c1068.f[0] = v;
                    bx = *(s32 *)((char *)node + 0x30);
                    v = *(f32 *)(off + bx + 4);
                    c1068.f[1] = v;
                    bz = *(s32 *)((char *)node + 0x30);
                }
                v = *(f32 *)(off + bz + 8);
                c1070.f[1] = c;
                c1070.f[0] = v;
                node3 = *(s32 *)&arg0->unk0x8;
                sel3 = *(u16 *)(e7 + 8);
                bx = *(s32 *)((char *)node3 + 0x3C);
                if (bx != 0) {
                    off = (s32)sel3 * 12;
                    v = *(f32 *)(off + bx);
                    c1078.f[0] = v;
                    bx = *(s32 *)((char *)node3 + 0x3C);
                    v = *(f32 *)(off + bx + 4);
                    c1078.f[1] = v;
                    bz = *(s32 *)((char *)node3 + 0x3C);
                    goto join;
                } else {
                    goto tail3;
                }
            }
        tail3:
            off = (s32)sel3 * 12;
            bx = *(s32 *)((char *)node3 + 0x30);
            v = *(f32 *)(off + bx);
            c1078.f[0] = v;
            bx = *(s32 *)((char *)node3 + 0x30);
            v = *(f32 *)(off + bx + 4);
            c1078.f[1] = v;
            bz = *(s32 *)((char *)node3 + 0x30);
        join:
            v = *(f32 *)(off + bz + 8);
            c1080.f[1] = c;
            c1080.f[0] = v;
            if (fn_800F6DE0(&b8, &b28, (void *)&c1058, (void *)&c1068, (void *)&c1078, &sp10F4) != 0) {
                t0 = c1058.ps;
                c1098.ps = t0;
                t11 = c1060.ps;
                c10A0.ps = t11;
                sp10A8 = var_r22[0];
                t11 = c1058.ps;
                t0 = c1068.ps;
                t12 = c1060.ps;
                t13 = c1070.ps;
                t0 = __builtin_ps_sub(t0, t11);
                c10B0.ps = t0;
                t13 = __builtin_ps_sub(t13, t12);
                t8 = lbl_8029C060[0];
                c10B8.ps = t13;
                t13 = c1058.ps;
                t0 = c1078.ps;
                t12 = c1060.ps;
                t9 = c1080.ps;
                t0 = __builtin_ps_sub(t0, t13);
                c10C0.ps = t0;
                t9 = __builtin_ps_sub(t9, t12);
                c10C8.ps = t9;
                t10 = c10B0.ps;
                t12 = c10C0.ps;
                t0 = c10B8.ps;
                t13 = __builtin_ps_merge10(t12, t9);
                t11 = __builtin_ps_merge10(t10, t0);
                t11 = __builtin_ps_mul(t11, t12);
                t13 = __builtin_ps_mul(t10, t13);
                t12 = __builtin_ps_merge00(t12, t9);
                t13 = __builtin_ps_sub(t13, t11);
                t0 = __builtin_ps_merge00(t0, t10);
                t11 = __builtin_ps_merge00(t13, t13);
                t0 = __builtin_ps_mul(t0, t12);
                c1100.ps = t11;
                sconst = lbl_8029C1D4;
                t12 = __builtin_ps_merge10(t0, t0);
                t0 = __builtin_ps_sub(t0, t12);
                c1100.f[1] = sconst;
                t13 = __builtin_ps_merge10(t13, t0);
                c10D0.ps = t13;
                t0 = c1100.ps;
                c10D8.ps = t0;
                t12 = c10D0.ps;
                c1088.ps = t12;
                t13 = c10D8.ps;
                c1090.ps = t13;
                t0 = t13;
                t12 = c1088.ps;
                t0 = __builtin_ps_mul(t0, t0);
                t0 = __builtin_ps_merge00(t0, t8);
                t0 = __builtin_ps_madd(t12, t12, t0);
                t0 = __builtin_ps_sum0(t0, t0, t0);
                t11 = t0;
                ucmp.ps = t11;
                if (ucmp.f[0] > c) {
                    t13 = __builtin_ps_rsqrte(t0);
                    t0 = __builtin_ps_muls0(t12, t13);
                    c1088.ps = t0;
                    c1108.ps = t13;
                    sconst = lbl_8029C1D4;
                    c1108.f[1] = sconst;
                    t0 = c1090.ps;
                    t11 = c1108.ps;
                    t0 = __builtin_ps_mul(t0, t11);
                    c1090.ps = t0;
                }
                {
                    f32 f3;
                    f32 f4;
                    f32 f5;
                    f32 f6;
                    f32 f7;
                    f32 f8s;
                    f32 f9s;
                    f32 f11s;
                    f32 f0s;
                    f32 f10s;
                    f32 f12s;
                    f32 f13s;
                    t0 = c1098.ps;
                    c1098.ps = t0;
                    t13 = *((__ps_t *)((char *)arg0 + 16));
                    t12 = *((__ps_t *)((char *)arg0 + 24));
                    t0 = __builtin_ps_mul(t0, t13);
                    f11s = *(f32 *)((char *)arg0 + 0x30);
                    f9s = *(f32 *)((char *)arg0 + 0x20);
                    c1098.ps = t0;
                    t0 = c10A0.ps;
                    f4 = *(f32 *)((char *)arg0 + 0x50);
                    t0 = __builtin_ps_mul(t0, t12);
                    f3 = *(f32 *)((char *)arg0 + 0x54);
                    f7 = *(f32 *)((char *)arg0 + 0x34);
                    f6 = *(f32 *)((char *)arg0 + 0x24);
                    c10A0.ps = t0;
                    f13s = c1098.f[1];
                    f10s = c1098.f[0];
                    f12s = c10A0.f[0];
                    f11s = f13s * f11s;
                    f0s = *(f32 *)(r23 + 0x20);
                    f9s = f10s * f9s + f11s;
                    f5 = *(f32 *)((char *)arg0 + 0x58);
                    f7 = f13s * f7;
                    f0s = f12s * f0s + f9s;
                    f8s = *(f32 *)((char *)arg0 + 0x38);
                    f9s = *(f32 *)((char *)arg0 + 0x3C);
                    f0s = f0s + f4;
                    f11s = *(f32 *)((char *)arg0 + 0x28);
                    f6 = f10s * f6 + f7;
                    e10.f[0] = f0s;
                    f8s = f13s * f8s;
                    f11s = f10s * f11s + f8s;
                    f0s = *(f32 *)(r23 + 0x24);
                    f13s = f13s * f9s;
                    f7 = *(f32 *)((char *)arg0 + 0x2C);
                    f0s = f12s * f0s + f6;
                    f8s = *(f32 *)((char *)arg0 + 0x5C);
                    f0s = f0s + f3;
                    e10.f[1] = f0s;
                    f10s = f10s * f7 + f13s;
                    f0s = *(f32 *)(r23 + 0x28);
                    f0s = f12s * f0s + f11s;
                    f0s = f0s + f5;
                    e11.f[0] = f0s;
                    f13s = *(f32 *)(r23 + 0x2C);
                    f12s = f12s * f13s + f10s;
                    f12s = f12s + f8s;
                    e11.f[1] = f12s;
                }
                t12 = e10.ps;
                c10D0.ps = t12;
                t0 = ((Pair *)sp1110)->ps;
                c10D8.ps = t0;
                t11 = c10D0.ps;
                c1098.ps = t11;
                t12 = c10D8.ps;
                c10A0.ps = t12;
                fn_8008757C((void *)&c10D0, r23, (void *)&c1088, (void *)&c10A0, (void *)&c1098, (void *)&c10C8);
                t0 = c10D0.ps;
                c1088.ps = t0;
                t11 = c10D8.ps;
                c1090.ps = t11;
                if (fn_800F6AD0(arg1, arg0, (void *)&c1088, sp10F8, sp10F4) != 0) {
                    var_r15 = 1;
                }
            }
            var_r16 += 1;
            var_r22 += 1;
        } while (var_r16 < sp10F0);
    }
    return var_r15;
}
