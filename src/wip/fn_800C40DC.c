// PARKED 2026-10-06: PS/FPR-colouring wall (see VERDICT below) — retail's
//   hand-tuned f0/f3..f13 assignment cannot be selected from C source, and the
//   +4-word symbol-page-anchor difference (retail folds the constant into the
//   load displacement, ngccc materialises the address first) plus the
//   ps_madd/ps_sum0 lane semantics are unreachable without register pins and
//   inline-asm ps_* templates, which this task forbids.  Best hand-rebuilt body
//   retained unchanged (1.3% masked = 3/225 words); no better body is known.
// WIP DRAFT (non-matching) — hand-rebuilt from tools/ps_disasm.py output
// family=m2c range=0x800C40DC-0x800C4414 size=824B
// FLAG: -mps-float
// VERDICT 2026-09-27: compiles under -mps-float; object 900B vs retail 824B
//   (206 vs 225 insns), masked 3/225 words = 1.3%.  NO FLAG-less build: cc1
//   ICEs at expr.c:2802 on `__ps_t` without the flag, so the FLAG line is
//   load-bearing (promote_wip reads it; the plain sweep ignores it — §6w-105).
// WHAT IS SOLVED: signature `(Obj *)`; the 0x1E0-stride element array at
//   self+0x2F0 walked BACKWARD from cnt-1; all three loop guards; the frame
//   (0xB0 = 8 + 21 paired-single slots at 0x8..0xA7 + V[20] pair at 0xA8, and
//   the four +0x100..+0x11F pair copies land at 0x8/0x10/0x18/0x20 in the
//   right order with retail's own displacement folding); every field offset
//   and width; the two rsqrte/res and merge00/merge10/merge10/merge00 chains.
// PRECISE RESIDUAL (why C cannot reach it yet):
//   1. FPR COLOURING.  retail assigns f0,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13
//      in a hand-tuned order (f5/f6/f7 hold the two muls0 falloff terms, f4
//      carries the clamped length, f3/f11/f13 the div chain).  cc1's allocator
//      picks a different permutation from the same dataflow; nothing in the
//      source shape selects retail's, and the promoted siblings
//      (src/fn_801B19DC.c) needed ~40 `register __ps_t x __asm__("frN")` pins
//      PLUS inline-asm `ps_*` templates to hold theirs.
//   2. SYMBOL PAGE ANCHORS (+4 words).  retail folds each constant into the
//      load's displacement (`lis r9,0x802A; lfd f2,-0x6f30(r9)` = 2 words);
//      ngccc materialises the address first (`lis`+`addi`+`lfd 0(rX)` = 3).
//      Copying the extern into a local to hoist it out of the loop (which is
//      what retail's preheader does) is what triggers the extra `addi`; using
//      the extern inline re-materialises it every iteration instead.
//   3. ps_madd / ps_sum0 OPERAND MEANING.  Verified field positions, but the
//      lane semantics of the 46-deep `ps_madd`/`ps_sum0` dot-product chain
//      (does fD.hi use the high or low product lane?) could not be pinned down
//      without an emitter probe, so the *values* in V[6..V[11]/V[13] are a
//      best guess.  Byte-matching the register names without the right lane
//      semantics would still not match.
//   4. cc1 FRAGILITY: optabs.c:3515 ICEs as soon as ~3 more `ps_madd`/
//      `ps_sum0`/`ps_muls0` are live at once in one basic block (§7c-163
//      family) — the reason the intermediates had to be spilled through the
//      V[] array instead of held in registers.
// INERT: not registered in splits.txt/configure.py — never compiled by the
// build, not counted in objdiff progress.  activate via tools/wip.py.
// STRUCT TYPES: file-local Obj/Elem typedefs with the TRUE offsets+types
// (0x18/0x20/0x100..0x118 on the element and 0x110..0x150 on self are PAIRS,
//  0x08/0x38/0x78/0xA0/0xA4/0xC8/0xCC/0x158 are f32).  The shared Unk_*
//  classes mis-type several of those slots, which is why this is a local
//  typedef rather than a header edit (AGENTS M6.89d-note).
// BLOCKER SUMMARY (why parked, not promoted): (1) FPR colouring,
//  (2) +4 words from symbol page anchors (lis+addi+lfd vs lis+lfd(-disp)),
//  (3) ps_madd/ps_sum0 lane semantics unverified, (4) cc1 optabs ICE with
//  >~3 live ps_* ops per block.  None are reachable from plain C here.
// LOOP / GUARDS (fully resolved, see below):
//   * element array is `*(Elem **)(self+0x2F0)`, stride 0x1E0, walked BACKWARD
//     from index cnt-1 (retail: rlwinm r0,r8,4 / subf / rlwinm r7,r0,5 = i*0x1E0,
//     then `addi r7,r7,-0x1E0` at the latch).
//   * `e->f04 == 1` -> skip the node (cmpwi/beq to the latch).
//   * node skipped when `V[15].w[0] < 1e-6f` (fcmpu cr0,f0,f2 ; blt latch) and
//     lbl_802990D0 (the f64 1e-06) is what f2 holds.
//   * divide-by-len guard is `ble` after `fcmpu cr0,len,0.0f`.
//   * tail is `if (i == 0) break;` (cmpwi r8,0 / bne loop head).
// PARKED 2026-10-06 (same-day reconfirm): reviewed the body line-by-line
//   against the WANT again — loop shape (backward walk over the 0x1E0-stride
//   array at self+0x2F0, arr reloaded inside the loop head at 0x800C4110),
//   both skip guards, the V[14]/V[15] falloff->rsqrte/ps_res chain, the
//   clamp branch at 0x800C42D8 and the scalar tail all agree with the body.
//   Nothing further is safely changeable without a compiler; body left as-is.
// PS ENCODING (established by compiling probes with ngccc 3.9.3 + ngcas —
// the classic VMX A-form field order is WRONG for opcode 4 here):
//   opcode 4 : D = bits 21-25, 2nd op = 16-20, 3rd op = 11-15, 4th op = 6-10,
//              xo5 = 26-30.  merge00/01/10/11 all use xo5=16 with the SELECTOR
//              in bits 6-10 (16/17/18/19); xo5=8 with selector 0/2 is ps_mr,
//              1/4/8 is ps_neg/ps_nabs/ps_abs.
//   psq_l/st (opcode 56/60): D = bits 21-25, base = 16-20, 12-bit signed disp
//              in bits 0-11, W = bit 15, I = bits 12-14.
#include "types.h"
#include "structs.h"

extern f64 lbl_802990D0;
extern f32 lbl_802990D8;
extern f32 lbl_802990DC;
extern __ps_t lbl_80298F18;

typedef struct Elem {
    char pad00[0x4];
    s32 f04;
    f32 f08;
    char pad0C[0xC];
    __ps_t p18;
    __ps_t p20;
    char pad28[0x10];
    f32 f38;
    char pad3C[0x3C];
    f32 f78;
    char pad7C[0x24];
    f32 fA0;
    f32 fA4;
    char padA8[0x20];
    f32 fC8;
    f32 fCC;
    char padD0[0x30];
    __ps_t p100;
    __ps_t p108;
    __ps_t p110;
    __ps_t p118;
} Elem;

typedef struct Obj {
    char pad000[0x110];
    __ps_t p110;
    __ps_t p118;
    char pad120[0x18];
    __ps_t p138;
    __ps_t p140;
    __ps_t p148;
    __ps_t p150;
    f32 f158;
    char pad15C[0x50];
    s32 cnt;
    char pad1B0[0x140];
    Elem *arr;
} Obj;

void fn_800C40DC(Obj *arg0) {
    volatile __ps_t V[21];
    s32 i;
    s32 off;
    Elem *e;
    __ps_t t;
    volatile f32 *L;
    f32 f0, f1, f2, f3, f4;
    f64 cEps;
    f32 cZero;
    f32 cOne;
    __ps_t cVZero;

    cEps = lbl_802990D0;
    cZero = lbl_802990D8;
    cOne = lbl_802990DC;
    cVZero = lbl_80298F18;
    i = arg0->cnt;
    if (i == 0) {
        return;
    }
    i = i - 1;
    off = (i * 0x10 - i) * 0x20;
    for (;;) {
        e = (Elem *)((char *)arg0->arr + off);
        if (e->f04 != 1) {
            /* --- V[0..3] = element +0x100..+0x11F (4 pair copies) --- */
            V[0] = e->p100;
            V[1] = e->p108;
            V[2] = e->p110;
            V[3] = e->p118;

            /* --- normalise: V[14].lo = e[0x08]*e[0xC8], then cross products --- */
            f4 = e->f08 * e->fC8;
            *((volatile f32 *)&V[14]) = f4;
            t = V[14];
            V[5] = __builtin_ps_muls0(V[1], t);
            V[3] = __builtin_ps_sub(V[3], V[5]);
            V[4] = __builtin_ps_muls0(V[0], t);
            V[2] = __builtin_ps_sub(V[2], V[4]);
            t = __builtin_ps_madd(V[2], t, V[3]);
            t = __builtin_ps_sum0(t, t, t);
            t = __builtin_ps_rsqrte(t);
            t = __builtin_ps_res(t);
            V[15] = t;
            f4 = *((volatile f32 *)&V[15]);
            e->fA0 = f4;

            f0 = e->fA0;
            if (!(f0 < cEps)) {
                /* --- 1/length --- */
                V[4] = V[2];
                t = __builtin_ps_mul(V[3], V[3]);
                t = __builtin_ps_merge00(t, cVZero);
                t = __builtin_ps_madd(t, t, V[2]);
                t = __builtin_ps_sum0(t, t, t);
                V[16] = t;
                f4 = *((volatile f32 *)&V[16]);
                if (f4 > cZero) {
                    V[16] = __builtin_ps_rsqrte(t);
                    *(((volatile f32 *)&V[16]) + 1) = cOne;
                    V[4] = __builtin_ps_muls0(V[2], V[16]);
                    V[5] = __builtin_ps_mul(V[3], V[4]);
                }

                /* --- falloff and its two dot products --- */
                f4 = -e->f78 * e->f38;
                *((volatile f32 *)&V[17]) = f4;
                V[7] = __builtin_ps_muls0(V[5], V[17]);
                V[6] = __builtin_ps_muls0(V[4], V[17]);
                f2 = arg0->f158 * e->fCC;
                f4 = e->fC8;
                t = __builtin_ps_mul(V[3], V[3]);
                t = __builtin_ps_merge00(t, cVZero);
                t = __builtin_ps_madd(V[2], t, V[0]);
                t = __builtin_ps_sum0(t, t, t);
                V[18] = t;
                f3 = *((volatile f32 *)&V[18]);
                f3 = f3 / f4;
                f3 = -f3;
                f1 = f3 / f2;
                t = __builtin_ps_mul(V[7], f3);
                t = __builtin_ps_merge00(t, cVZero);
                t = __builtin_ps_madd(V[6], t, V[0]);
                t = __builtin_ps_sum0(t, t, t);
                f0 = *((volatile f32 *)&V[13]);
                f2 = f0;
                f0 = f3 * (-f4);
                f1 = -f1;
                if (!(__builtin_fabsf(f0) < __builtin_fabsf(f1))) {
                    V[8] = V[6];
                    f4 = f0;
                    V[9] = V[7];
                } else {
                    f0 = f1 / f4;
                    f0 = f0 - f2;
                    *((volatile f32 *)&V[17]) = f0;
                    f4 = f1;
                    V[13] = __builtin_ps_muls0(V[1], V[17]);
                    V[12] = __builtin_ps_muls0(V[0], V[17]);
                    V[8] = __builtin_ps_add(V[6], V[12]);
                    V[9] = __builtin_ps_add(V[7], V[13]);
                }
                V[10] = V[8];
                V[11] = V[9];

                /* --- accumulate the four momentum pairs --- */
                arg0->p138 = __builtin_ps_add(arg0->p138, V[8]);
                arg0->p140 = __builtin_ps_add(arg0->p140, V[9]);
                t = __builtin_ps_merge10(V[8], V[9]);
                V[12] = __builtin_ps_sub(e->p18, arg0->p110);
                V[13] = __builtin_ps_sub(e->p20, arg0->p118);
                t = __builtin_ps_merge10(V[12], V[13]);
                V[12] = __builtin_ps_mul(V[12], V[12]);
                V[13] = __builtin_ps_mul(t, V[12]);
                t = __builtin_ps_sub(V[12], V[13]);
                V[12] = __builtin_ps_merge00(V[13], V[12]);
                t = __builtin_ps_merge00(t, t);
                V[20] = t;
                *(((volatile f32 *)&V[20]) + 1) = cOne;
                t = __builtin_ps_mul(V[12], t);
                t = __builtin_ps_merge10(t, t);
                t = __builtin_ps_sub(t, t);
                arg0->p148 = __builtin_ps_add(arg0->p148, __builtin_ps_merge10(V[12], t));
                arg0->p150 = __builtin_ps_add(arg0->p150, V[20]);
                V[10] = arg0->p148;
                V[11] = arg0->p150;

                /* --- scalar tail --- */
                f0 = e->fCC * f4;
                f1 = f0 * arg0->f158 + e->f08;
                f2 = e->fA4 + f0;
                e->f08 = f1;
                e->fA4 = f2;
            }
        }
        if (i == 0) {
            break;
        }
        off = off - 0x1E0;
        i = i - 1;
    }
}
