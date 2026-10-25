// WIP DRAFT (non-matching) — hand rewrite from disasm (group H)
// family=m2c range=0x801E1D30-0x801E2624 size=2292B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// RE-TRIAGED 2026-10-13: still SIZE MISMATCH (got ~492B vs 2292B
// want; skeleton). Unrolled matrix-muls + bdnz windows + FPR staging per header.
// No body change; out of round scope.
// PARKED: 1.6% (2/123 words, got 492B vs 2292B) - skeleton only;
// ran out of budget before writing the full unrolled body. What is known:
// - ALL opcode-4 words decode clean via tools/ps_diff.py two-form tables:
//   ps_mul x3 / ps_merge00 x3 / ps_madd x3 / ps_sum0 x3 (@0x801E1E1C-6C,
//   the doc06 canonical dot-product idiom x4 over the matrix at arg0+0x520)
//   - NO XO5=6/7 hard-wall encodings; emittable via __builtin_ps_mul/
//   madd/sum0/merge00 under -mps-float.
// - Structure: guard *(arg0->0x15BC)->0xAC != 0; THREE empty bdnz$ spin
//   windows (0x801E1D70 w/ 10 setup insns inside incl. r3/r31/r28/r26/r29/r27
//   address precomputes, 0x801E1DEC post-call, 0x801E1F20 w/ 2 stw inside);
//   clamp var=0x508/0x50C vs lbl_802AD78C; bl fn_800086B0(arg0+0x470,&sp8,f)
//   (r3/r4/f1 only, no crclr -> proto void(void*,void*,f32)); dot block;
//   transpose/negate copies; TWO fully-unrolled 16-out scalar matrix muls
//   (flat left-assoc fmadd trees, seed product = SECOND product of each sum);
//   MM#2 reads its 16 M-constants through SAVED FPRs f26-f31 loaded once from
//   sp98..spD4 (that's why the prologue saves 6 FPRs); copybacks are psq pair
//   stores incl. negative-offset (-728(r30)) forms.
// Tried: m2c draft (all float math rendered as *(s32*) integer ops - wrong
// opcodes everywhere), this partial rewrite (compiles, 1.6%).
// Retry hints: doc-30 solved recipe for the three bdnz$ windows (pinned
// outputs); hand-unroll both MMs in want's exact load order; stage MM#2's 16
// constants as named locals BEFORE it so they claim f26-f31; frame-template
// struct (6q-86) to pin sp48..sp130 slot layout.
// FLAG: -mps-float
#include "types.h"
#include "structs.h"

extern s32 lbl_80303150;
extern f32 lbl_802AD78C;
extern f32 lbl_802AD790;
extern f32 lbl_802AD794;
extern u8 lbl_802AD278[];

void fn_800086B0(Unk_C7387A53 *, Unk_DB0E2BAB *, f32);

typedef union { __ps_t ps; f32 f[2]; } PSQ;

void fn_801E1D30(Unk_E1A7D3A0 *arg0) {
    PSQ sp8;
    f32 sp48;
    f32 sp4C;
    f32 sp50;
    f32 sp58;
    f32 sp60;
    f32 sp68;
    f32 sp6C;
    f32 sp78;
    f32 sp7C;
    f32 sp80;
    PSQ m[8];
    f32 mm[16];
    f32 v[16];
    f32 t[16];
    char *p;
    char *q;
    Unk_C1F9F519 *mat;
    char *r11p;
    char *r9p;
    s32 ctr;

    if (*(s32 *)(arg0->unk0x15BC + 0xAC) != 0) {
        arg0->unk0x508 = arg0->unk0x508 + arg0->unk0x94;
        for (ctr = 0; ctr < 4; ctr++) {
        }
        mat = (char *)arg0 + 0x520;
        p = (char *)&sp48;
        q = (char *)&sp8;
        if (arg0->unk0x508 / arg0->unk0x50C > lbl_802AD78C) {
            arg0->unk0x508 /= 1.0f;
        }
        {
            f32 var_f13;
            var_f13 = arg0->unk0x508 / arg0->unk0x50C;
            if (var_f13 > lbl_802AD78C) {
                var_f13 = lbl_802AD78C;
            }
            fn_800086B0((char *)arg0 + 0x470, q,
                        ((var_f13 * lbl_802AD790) * var_f13) * (var_f13 - lbl_802AD794));
        }
        for (ctr = 0; ctr < 4; ctr++) {
        }

        /* dot-product normalize block over the matrix at arg0+0x520 */
        m[0].ps = mat->unk0x0;
        m[1].ps = mat->unk0x8;
        m[2].ps = mat->unk0x10;
        m[3].ps = mat->unk0x18;
        m[4].ps = mat->unk0x20;
        m[5].ps = mat->unk0x28;
        m[6].ps = mat->unk0x30;
        m[7].ps = mat->unk0x38;
        {
            PSQ k;
            PSQ a;
            PSQ b;
            PSQ c;
            PSQ d;
            k.ps = *(__ps_t *)&lbl_802AD278[0];
            a.ps = __builtin_ps_mul(m[7].ps, m[1].ps);
            b.ps = __builtin_ps_merge00(m[5].ps, k.ps);
            c.f[0] = m[6].f[0];
            c.f[1] = m[4].f[0];
            c.ps = __builtin_ps_add(c.ps, b.ps);
            b.f[0] = m[7].f[0];
            b.f[1] = k.f[0];
            d.f[0] = m[0].f[0];
            d.f[1] = a.f[0];
            d.ps = __builtin_ps_madd(c.ps, d.ps, b.ps);
            d.ps = __builtin_ps_sum0(d.ps, d.ps, d.ps);
            m[7].ps = d.ps;
            (void)m[7];
        }
        /* transposed row copies + negated column tail */
        sp78 = -mm[8];
        sp7C = -mm[9];
        sp80 = -mm[10];
        sp4C = mm[1];
        sp58 = sp4C;
        sp50 = mm[4];
        sp68 = sp50;
        sp60 = mm[5];
        sp6C = sp60;
        /* matrix multiply #1: rows of arg0+0x20-based vec vs matrix rows */
        {
            char *pp = p;
            char *qq = q;
            int i;
            for (i = 0; i < 16; i++) {
                mm[i] = *(f32 *)(pp + (i & 3) * 4) * *(f32 *)(qq + (i >> 2) * 0x10) +
                        *(f32 *)(pp + ((i + 1) & 3) * 4) * *(f32 *)(qq + (i >> 2) * 0x10 + 4) +
                        *(f32 *)(pp + ((i + 2) & 3) * 4) * *(f32 *)(qq + (i >> 2) * 0x10 + 8) +
                        *(f32 *)(pp + ((i + 3) & 3) * 4) * *(f32 *)(qq + (i >> 2) * 0x10 + 0xC);
            }
        }
    }
}
