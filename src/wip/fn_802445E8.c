// WIP DRAFT (non-matching) — hand-rebuilt from disasm (was m2c FAIL)
// family=m2c range=0x802445E8-0x80244858 size=624B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED 51.9% (81/156 words): body is semantically complete and compiles
// clean under -mps-float. Structure proven: frame 0xB0 exact (stfd f27-f31
// @0x88+, stmw r28 @0x78, lr @0xb4), got==want size 624B, all six
// int->float conversions are PLAIN CASTS (f32)(f64)(int-expr) — ngccc's own
// expander emits want's anonymous 0x70 cvt slot + single GCSE-hoisted pool
// load (f28, callee-saved). DO NOT convert to the manual union dance
// (lbl_802B1330): the volatile read SERIALIZES the four dances and kills
// the interleave (proven: 52% -> ~20%). DOC-14 caveat: because the source
// uses plain casts, a promote would synthesize the private pool double into
// module .rodata instead of the game's .rodata2 lbl_802B1330 — any future
// EXACT-masked verdict on this shape must check the pool before promoting.
// Residual 75 insns (doc-15 class): (a) want interleaves dance1/dance2
// tightly ([subf d1][mr r7,r11][xoris][subf d2][stw lo1]...) while got
// completes each dance statement first — the three dead "mr rX, r11" in
// want are NATURAL regalloc copies (caller never sets r11; no wedges needed,
// got reproduces its own set at slightly different slots/colors);
// (b) ps_add #1/#2 order + arg4 pair-load batching (got batches both
// psq_l early and issues add#2 first); (c) rotation-store timing (rot2/sp20
// store lands after add#1 in want); (d) scratch FPR colors f11/f12/f13.
// Flags tried under -mps-float: -fno-sched-spec/-fno-gcse/
// -fno-rerun-cse-after-loop neutral, -fno-schedule-insns2 hurts (41%),
// -fno-schedule-insns hurts (20%). PS ops decoded by hand: both opcode-4
// words @0x80244788/@0x802447B8 are ps_add (xo10=21) — reproduced via
// __builtin_ps_add. Callee arities audited: fn_80238964 = genuine 0-arg
// s32 getter (lis/lwz/blr, returns *(0x80306004)); fn_80236FE4 = 3-arg
// (saves r3/r4/r5) returning heap ptr, arg0 CHAINED from fn_80238964;
// fn_80271170 = sin-like f32(f32), fn_80271070 = cos-like f32(f32)
// (§6j-5 reconfirmed — m2c sinf/cosf names wrong in arity); fn_80241F00 =
// (ptr,out-ptr@&sp38,f32) ret discarded.
#include "types.h"
#include "structs.h"

s32 fn_80238964(void);
void *fn_80236FE4(CStruct *, CStruct *, s32);
f32 sinf(f32);
f32 cosf(f32);
void fn_80241F00(void *, void *, f32);

extern f32 lbl_802B0544;
extern f32 lbl_802B0548;
extern f32 lbl_802B054C[];
extern f32 lbl_802B1338;
extern f32 lbl_802B133C;
extern f32 lbl_802B1340;
extern f32 lbl_802B1344;
extern f32 lbl_802B1348;
extern f32 lbl_802B134C;

union psv { __ps_t ps; f32 f[2]; };

struct frame45 {
    f32 v0;
    f32 v1;
    f32 v2;
    f32 v3;
    f32 rot0;
    f32 rot1;
    f32 rot2;
    char _p24[4];
    __ps_t q0;
    __ps_t q1;
    __ps_t s0;
    __ps_t s1;
};

void fn_802445E8(Unk_6E48A312 *arg0, s32 arg1, s32 arg2, s32 arg3, Unk_EA529D06 *arg4, f32 farg0) {
    struct frame45 fr;
    struct frame45 *fp;
    Unk_9994C3F5 *temp_r3;
    f32 ang;
    f32 fill;
    f32 sc;
    f32 sn;
    f32 t1;
    f32 t2;
    f32 t3;
    f32 t4;

    if (arg0->unk0x4 != 0) {
        fp = &fr;
        t1 = (f32)(f64)(arg0->unk0x8 - arg1);
        t2 = (f32)(f64)(arg0->unk0xA - arg3);
        t3 = (f32)(f64)(arg0->unk0x10 - 1U);
        t4 = (f32)(f64)(arg0->unk0x11 - 1U);
        ang = (farg0 * lbl_802B1344) / lbl_802B1348;
        fill = lbl_802B1338;
        fp->v0 = fill;
        fp->v3 = lbl_802B133C;
        fp->v2 = fill;
        fp->v1 = fill;
        fp->v0 = t1 * lbl_802B0544 + t3 * lbl_802B0544 * lbl_802B1340;
        fp->v2 = t2 * lbl_802B054C[0] + t4 * lbl_802B054C[0] * lbl_802B1340;
        sn = sinf(ang);
        sc = cosf(ang);
        fp->rot0 = sc * fp->v0 + sn * fp->v2;
        fp->rot1 = fill;
        fp->rot2 = sc * fp->v2 - sn * fp->v0;
        fp->q0 = __builtin_ps_add(arg4->unk0x0, *(__ps_t *)&fp->rot0);
        ((union psv *)&fp->q0)->f[1] = (f32)(f64)(s32)(s8) * (u8 *)((char *)arg0 + (s32)0x9) * lbl_802B0548 + ((union psv *)&fp->q0)->f[1];
        fp->q1 = __builtin_ps_add(arg4->unk0x8, *(__ps_t *)&fp->rot2);
        if (arg0->unk0x14 == NULL) {
            temp_r3 = fn_80236FE4((void *)fn_80238964(), arg0->unk0x4, 0x204);
            arg0->unk0x14 = (s32)temp_r3;
            temp_r3->unk0x8 |= 0x200;
        }
        fp->s0 = *(__ps_t *)&fp->q0;
        fp->s1 = *(__ps_t *)&fp->q1;
        fn_80241F00(*((void * *)&arg0->unk0x14), &fp->s0,
                    (f32)(f64) arg0->unk0xC * lbl_802B134C + farg0);
    }
}
