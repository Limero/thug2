// WIP DRAFT - hand-rebuilt paired-single reconstruction; BEST-MATCH 52.2%
// (-mps-float -fno-schedule-insns, ps_diff.py 70/134). PARKED - see below.
//
// RE-AUDIT 2026-08-25: old park ("AltiVec vmsumshm/vmhaddshs/vsel + f31 frame
// quirk", docs/parkings/29) was WRONG. All 18 opcode-4 words decode as standard
// Gekko PS under the M5.0q two-form discipline (capstone mislabels A-form words
// because frC@21-25 collides with VMX VC):
//   The block holds two subtracts of f0 (words 118C0028 on f12 and 116B0028
//   on f11), two squares (112C0332 on f12 into f9 and 114B02F2 on f11 into
//   f10), two subtracts of f8 (10004028 on f0 and 11AD4028 on f13), two
//   merges with f7 (11293C20 on f9 and 114A3C20 on f10), and two
//   multiply-adds (1000483A of f0 with f9 and 11AD537A of f13 with f10). It
//   closes with the pair-sum (words 10000014 and 11AD6B54), the reciprocal
//   square-root estimate (10000034 and 11A06834), the reciprocal estimate
//   (10000030 and 11A06830), and the pair add (1000682A and 118C582A).
// Every opcode is emitted by this draft via __builtin_ps_* / __ps_t arithmetic.
//
// What matches byte-exactly here: prologue/frame (frame-template struct at sp8,
// -mps-float issue-01 +8 gives stfd f31 + want's 0xE8), all four setup calls,
// the six-way float bounds guard (frozen verbatim as inline asm - every C form
// of the boolean threads an early `li r0,0` GCC 2.95 never emits; r0-pin output
// works), fn_800073B0 gate, block-2/3 pair adds/copies, final fn_800F6AD0 call
// shape (r3=arg1,r4=arg0,r5=&sp88,r6=arg3-passthrough,f1=scale).
//
// PARKED (52.2%) - residual is doc06 M5.0r scheduler/allocator walls, not
// emission: (a) block-1 FPR color rotation - want recycles f0 across p10/p48
// (load, dies at subs, reborn) and colors sq1/sq2 as f9/f10; pins hold on five
// loads but the p10->f0->p48 recycling chain is unreachable (recipe 169 pins
// block inter-web reuse, double-pin poisons allocation); (b) want scatters the
// fn_8008757C arg setups (mr r5/mr r4/addi r3) mid-block between float ops -
// sched2 behavior that survives no flag combo tried (plain/-fno-schedule-insns/
// insns2/sched-spec/interblock/thread-jumps/O1); (c) stmw spans r25..r31 (one
// hole reg) vs want r26..r31 - same extra-web pressure. ~12 guard shapes +
// pin/volatile/comma-init/roundtrip variants exhausted. Retry when a lever for
// cross-web FPR recycling or per-site arg-setup scatter exists.
// family=m2c range=0x800FDE38-0x800FE058 size=544B
// extra_cflags: -mps-float -fno-schedule-insns
#include "types.h"
#include "structs.h"
void fn_800063B4(void *);
void fn_800FD198(Unk_BE223D5D *, Unk_EA529D06 *, Unk_EA529D06 *);
void fn_8000723C(void *, void *);
void fn_8000728C(Unk_DB0E2BAB *, CStruct *);
s32 fn_800073B0(void *, void *, void *, void *);
void fn_8008757C(void *, Unk_DB0E2BAB *, CStruct *);
s32 fn_800F6AD0(s32, void *, void *, void *, f32);

extern char lbl_8029C060[];

#define argf(o) (*(f32 *)((char *)arg0 + (o)))

typedef union { __ps_t p; f32 w[2]; } S;

typedef struct {
    __ps_t buf1[4];     /* 0x08-0x27 */
    f32 bbox[8];        /* 0x28-0x47 */
    __ps_t r29buf[2];   /* 0x48-0x57 */
    __ps_t r28buf[2];   /* 0x58-0x67 */
    volatile __ps_t tmp68[4]; /* 0x68-0x87 (0x68=d3,0x70=d1,0x80=d2) */
    __ps_t out88[2];    /* 0x88-0x97 */
    __ps_t sum98[2];    /* 0x98-0xA7 */
    __ps_t padA8;       /* 0xA8 */
    S vb0;              /* 0xB0 */
    S vb8;              /* 0xB8 */
} FrameT;

s32 fn_800FDE38(Unk_BE223D5D *arg0, void *arg1, void *arg2, void *arg3) {
    FrameT fr;
    register __ps_t p50 __asm__("fr12");
    register __ps_t p20 __asm__("fr11");
    register __ps_t p08 __asm__("fr8");
    register __ps_t k7 __asm__("fr7");
    register __ps_t p18 __asm__("fr13");
    register __ps_t p10 __asm__("fr0");
    __ps_t p48;
    __ps_t d1, d2, d3, d4, sq1, sq2, m1, m2, acc1, acc2, g1, g2, i1p, i2p;
    f32 i1, i2;
    register f32 scale __asm__("fr31");
    __ps_t a18, a10, t0, t1, s1, s2, rt0, rt1, x1, x2;
    register s32 ok __asm__("r0");
    register char *q48 __asm__("r29");
    register char *q58 __asm__("r28");
    register void *t68a __asm__("r3");
    register char *bp __asm__("r30");
    register void *a1 __asm__("r27");
    register void *a3 __asm__("r26");

    a1 = arg1;
    a3 = arg3;
    fn_800063B4(&fr.buf1[0]);
    bp = &fr.bbox[0];
    fn_800FD198(arg0, a1, &fr.buf1[0]);
    fn_8000723C(bp, &fr.buf1[0]);
    fn_8000728C(bp, &fr.buf1[2]);
    /* checks region frozen verbatim (recipe 170): arg0 homed r31 via pin,
       bbox slots are fixed r1 displacements; flag left in r0 like want */
    __asm__ __volatile__(
        "lfs 13, 0xa8(31)
	"
        "lfs 0, 0x38(1)
	"
        "fcmpu 0, 13, 0
	"
        "bgt 0f
	"
        "lfs 13, 0x28(1)
	"
        "lfs 0, 0xb8(31)
	"
        "fcmpu 0, 13, 0
	"
        "bgt 0f
	"
        "lfs 13, 0xb0(31)
	"
        "lfs 0, 0x40(1)
	"
        "fcmpu 0, 13, 0
	"
        "bgt 0f
	"
        "lfs 13, 0x30(1)
	"
        "lfs 0, 0xc0(31)
	"
        "fcmpu 0, 13, 0
	"
        "bgt 0f
	"
        "lfs 13, 0xac(31)
	"
        "lfs 0, 0x3c(1)
	"
        "fcmpu 0, 13, 0
	"
        "bgt 0f
	"
        "lfs 13, 0x2c(1)
	"
        "lfs 0, 0xbc(31)
	"
        "fcmpu 0, 13, 0
	"
        "ble 1f
	"
        "li 0, 0
	"
        "b 2f
	"
        "1:
	"
        "li 0, 1
	"
        "2:
	"
        : "=r"(ok)
        : : "fr0", "fr13", "cc");
    if (ok != 0
        && (q48 = &fr.r29buf[0], q58 = &fr.r28buf[0],
            fn_800073B0((char *)arg0 + 0xA8, &fr.buf1[0], q48,
                        q58) != 0)) {
    p10 = *(volatile __ps_t *)&fr.buf1[1];
    p50 = *(volatile __ps_t *)&fr.r29buf[1];
    p20 = *(volatile __ps_t *)&fr.buf1[3];
    bp = (char *)arg0 + 0x20;
    d1 = p50 - p10;
    p08 = *(volatile __ps_t *)&fr.buf1[0];
    d2 = p20 - p10;
    k7 = *(volatile __ps_t *)((char *)&lbl_8029C060[0]);
    p48 = *(volatile __ps_t *)((char *)&fr.r29buf[0]);
    sq1 = __builtin_ps_mul(d1, d1);
    p18 = *(volatile __ps_t *)&fr.buf1[2];
    t68a = (void *)&fr.tmp68[0];
    d3 = p48 - p08;
    fr.tmp68[1] = d1;
    sq2 = __builtin_ps_mul(d2, d2);
    fr.tmp68[0] = d3;
    fr.tmp68[2] = d2;
    d4 = p18 - p08;
    m1 = __builtin_ps_merge00(sq1, k7);
    m2 = __builtin_ps_merge00(sq2, k7);
    acc1 = __builtin_ps_madd(m1, d3, d3);
    acc2 = __builtin_ps_madd(m2, d4, d4);
    g1 = __builtin_ps_sum0(acc1, acc1, acc1);
    g2 = __builtin_ps_sum0(acc2, acc2, acc2);
    g1 = __builtin_ps_rsqrte(g1);
    i1p = __builtin_ps_res(g1);
    g2 = __builtin_ps_rsqrte(g2);
    fr.vb0.p = i1p;
    i2p = __builtin_ps_res(g2);
    i1 = fr.vb0.w[0];
    fr.vb8.p = i2p;
    i2 = fr.vb8.w[0];
    scale = i1 / i2;
    fn_8008757C(t68a, bp, q48);
    a18 = arg0->unk0x18;
    t1 = fr.tmp68[1];
    a10 = arg0->unk0x10;
    t68a = (void *)((s32)&fr.tmp68[2] - 8);
    t0 = fr.tmp68[0];
    s1 = t0 + a18;
    fr.sum98[1] = s1;
    s2 = t1 + a10;
    rt0 = fr.tmp68[0];
    rt1 = fr.tmp68[1];
    fr.r29buf[0] = rt0;
    fr.r29buf[1] = rt1;
    fr.sum98[0] = s2;
    fn_8008757C(t68a, bp, q58);
    x1 = fr.tmp68[0];
    x2 = fr.tmp68[1];
    fr.r28buf[0] = x1;
    fr.r28buf[1] = x2;
    fr.out88[0] = x1;
    fr.out88[1] = x2;
    return fn_800F6AD0(a1, arg0, &fr.out88[0], a3, scale);
    }
    return 0;
}
