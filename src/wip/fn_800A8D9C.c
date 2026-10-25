// WIP DRAFT (non-matching) — hand-rebuilt from the WANT disassembly.
// family=m2c range=0x800A8D9C-0x800A9200 size=1124B
// PARKED 2026-10-06. Semantics now match the WANT:
//   scale store  arg0[0xF0] = arg0[0xE0] * (farg0 / arg0[0xE4]);
//   mp = fn_80003EB0(m, farg0);            // builds the 16-float matrix at m
//   result = mp * M  (M = the 4x4 at arg0+0x20), stored element-by-element;
//   8 psq_l/psq_st row copies of result back into arg0+0x20..0x5C;
//   if (M[5] > lbl_80298210) arg0[0xF0] = -arg0[0xF0];
//   PS tail: pairs at arg0+0x8/0x10 = arg0+0x20/0x28 * -arg0[0xE8] + arg0+0xC0/0xC8.
// FIXED THIS PASS: the conditional negate was INVERTED in the previous body
//   (WANT is `fcmpu f0,f13 ; ble` -> negate when the lo half is GREATER than the
//   threshold, not less); and the 16 products are now written straight into
//   result[] one at a time (WANT `stfs f0,0x48+4i(r1)`) instead of into 16 named
//   f32 locals held live together — the latter is what forced the allocator to
//   spill into callee-saved FPRs.
// BLOCKER (unchanged in kind): codegen, not structure.  The WANT frame is
//   0xa8 with `stmw r28` and NO FPR saves; `-mps-float` (required for the
//   psq_l/psq_st + ps_muls0 tail) makes ngccc home the dot-product temporaries in
//   callee-saved FPRs and inflates the frame.  Two WANT regions have no plain-C
//   spelling: the 4-iteration `li r0,4; mtctr r0; bdnz`-self stall at 0x800A8DD8
//   (kept as an intentionally empty loop, DCE'd) and the 5 undecoded op-4 PS
//   words (0x800A91B0/B4/B8, 0x800A91D8, 0x800A91E4) in the PS tail.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

extern f32 lbl_80298210;
s32 fn_80003EB0(void *arg0, f32 farg0);

typedef struct {
    char pad0x0[0x8];
    __ps_t unk0x8;
    __ps_t unk0x10;
    char pad0x18[0x8];
    f32 unk0x20, unk0x24, unk0x28, unk0x2C;
    f32 unk0x30, unk0x34, unk0x38, unk0x3C;
    f32 unk0x40, unk0x44, unk0x48, unk0x4C;
    f32 unk0x50, unk0x54, unk0x58, unk0x5C;
    char pad0x60[0x60];
    __ps_t unk0xC0;
    __ps_t unk0xC8;
    char pad0xD0[0x10];
    f32 unk0xE0;
    f32 unk0xE4;
    f32 unk0xE8;
    f32 unk0xEC;
    f32 unk0xF0;
    f32 unk0xF4;
    s32 unk0xF8;
} Arg0;

typedef struct { s32 unk0x0; s32 unk0x4; } Sp88;

void fn_800A8D9C(Arg0 *arg0, f32 farg0) {
    f32 m[16];
    f32 result[16];
    Sp88 sp88;
    f32 *M = (f32 *)((char *)arg0 + 0x20);
    f32 *mp;
    s32 i;

    /* Scale factor: WANT loads 0xE4 first, then 0xE0 (fdivs then fmuls). */
    arg0->unk0xF0 = arg0->unk0xE0 * (farg0 / arg0->unk0xE4);

    /* WANT: `li r0,4 ; mtctr r0 ; bdnz`-self — a 4-iteration stall with no C
       spelling.  Left as an intentionally empty loop; ngccc deletes it. */
    for (i = 0; i < 4; i++) { }

    sp88.unk0x0 = fn_80003EB0(m, farg0);
    sp88.unk0x4 = (s32)M;
    mp = (f32 *)sp88.unk0x0;

    /* result = mp * M, i.e. result[i*4+j] = sum_k mp[i*4+k]*M[k*4+j], written
       element-by-element in WANT's order (each `stfs` lands at r1+0x48+4i). */
    result[0]  = mp[0]*M[0]  + mp[1]*M[4]  + mp[2]*M[8]   + mp[3]*M[12];
    result[1]  = mp[0]*M[1]  + mp[1]*M[5]  + mp[2]*M[9]   + mp[3]*M[13];
    result[2]  = mp[0]*M[2]  + mp[1]*M[6]  + mp[2]*M[10]  + mp[3]*M[14];
    result[3]  = mp[0]*M[3]  + mp[1]*M[7]  + mp[2]*M[11]  + mp[3]*M[15];
    result[4]  = mp[4]*M[0]  + mp[5]*M[4]  + mp[6]*M[8]   + mp[7]*M[12];
    result[5]  = mp[4]*M[1]  + mp[5]*M[5]  + mp[6]*M[9]   + mp[7]*M[13];
    result[6]  = mp[4]*M[2]  + mp[5]*M[6]  + mp[6]*M[10]  + mp[7]*M[14];
    result[7]  = mp[4]*M[3]  + mp[5]*M[7]  + mp[6]*M[11]  + mp[7]*M[15];
    result[8]  = mp[8]*M[0]  + mp[9]*M[4]  + mp[10]*M[8]  + mp[11]*M[12];
    result[9]  = mp[8]*M[1]  + mp[9]*M[5]  + mp[10]*M[9]  + mp[11]*M[13];
    result[10] = mp[8]*M[2]  + mp[9]*M[6]  + mp[10]*M[10] + mp[11]*M[14];
    result[11] = mp[8]*M[3]  + mp[9]*M[7]  + mp[10]*M[11] + mp[11]*M[15];
    result[12] = mp[12]*M[0] + mp[13]*M[4] + mp[14]*M[8]  + mp[15]*M[12];
    result[13] = mp[12]*M[1] + mp[13]*M[5] + mp[14]*M[9]  + mp[15]*M[13];
    result[14] = mp[12]*M[2] + mp[13]*M[6] + mp[14]*M[10] + mp[15]*M[14];
    result[15] = mp[12]*M[3] + mp[13]*M[7] + mp[14]*M[11] + mp[15]*M[15];

    /* 8 paired-single row copies result[] -> arg0+0x20..0x5C. */
    *(__ps_t *)&M[0]  = *(__ps_t *)&result[0];
    *(__ps_t *)&M[2]  = *(__ps_t *)&result[2];
    *(__ps_t *)&M[4]  = *(__ps_t *)&result[4];
    *(__ps_t *)&M[6]  = *(__ps_t *)&result[6];
    *(__ps_t *)&M[8]  = *(__ps_t *)&result[8];
    *(__ps_t *)&M[10] = *(__ps_t *)&result[10];
    *(__ps_t *)&M[12] = *(__ps_t *)&result[12];
    *(__ps_t *)&M[14] = *(__ps_t *)&result[14];

    /* WANT spills the updated M[4..5] to r1+8 and M[6..7] to r1+0x10, then tests
       the lo half of M[4..5] (loaded as `lfs 0xc(r1)`): negate +0xF0 when the
       value is GREATER than the threshold (`ble` skips the negate). */
    {
        __ps_t sp8 = *(__ps_t *)&M[4];
        __ps_t sp10 = *(__ps_t *)&M[6];
        f32 lo = ((f32 *)&sp8)[1];
        if (lo > lbl_80298210) {
            arg0->unk0xF0 = -arg0->unk0xF0;
        }
    }

    /* PS tail: scale the pairs at arg0+0x20/0x28 by -arg0[0xE8] and add the
       offset pairs at arg0+0xC0/0xC8 into arg0+0x8/0x10. */
    {
        f32 sp90 = -arg0->unk0xE8;
        *(__ps_t *)&arg0->unk0x8 = __builtin_ps_muls0(*(__ps_t *)&M[0], *(__ps_t *)&sp90);
        *(__ps_t *)&arg0->unk0x10 = __builtin_ps_muls0(*(__ps_t *)&M[2], *(__ps_t *)&sp90);
        *(__ps_t *)&arg0->unk0x8 = __builtin_ps_add(*(__ps_t *)&arg0->unk0x8, *(__ps_t *)&arg0->unk0xC0);
        *(__ps_t *)&arg0->unk0x10 = __builtin_ps_add(*(__ps_t *)&arg0->unk0x10, *(__ps_t *)&arg0->unk0xC8);
    }
}
