// WIP DRAFT (non-matching) — hand-rewritten from the want disassembly
// family=m2c range=0x8012CD84-0x8012D0D8 size=852B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Codegen disclosures (0 emitted instructions, 1 pin + 2 zero-code barriers):
//   register s32 op __asm__("r28")   — pins the opcode byte to r28 (want's reg)
//   __asm__("" : "+r"(op));           — zero-code barrier at the top of case 0x40
//   __asm__("" : "+r"(op));           — zero-code barrier at the top of case 0x41
//     (both barriers exist ONLY to stop reload's eqelim from turning the
//      `li r4,0x40` / `li r4,0x41` lookup-tag argument into `mr r4,r28`;
//      without them the constant load is replaced by a copy of op.)
//
// === PARKED (2026-10-01) ===
// score: NEAR 93.0% (198/213 words), object .text 0x354 = 852B == symbols.txt
// size == the `size=852B` range marker.  No private .rodata.
//
// Structure is 100% reproduced: every instruction shape, the switch decision
// tree, block order, the `crclr cr1eq` sites, the mfcr/mtcrf CR save, the
// cr4 live-range, and the 0x8/0xc/0xe/0x10../0x28 local slots all match.
//
// Residual: 15 words, ALL inside the 0x2f/0x37 case, all a 3-cycle rotation of
// one register-allocation choice.  want {n:r28, i:r29, c1:r31}; GOT
// {c1:r28, n:r29, i:r31} — r28 is the register `op` was pinned to and op is dead
// on this path, so r28 is free and local-alloc hands it to whichever of the
// three it likes best (here the copy `c1 = var_r30`, in want the load `n`).
// The blocker is purely ngccc local-alloc priority, not semantics: the post-
// front-end RTL differs only in which pseudo gets r28.
//
// 2026-10-22 (role-count audit): `n` and `o` are reused by three switch cases.
// Splitting them per case (n37/n40/n41, o40/o41, and both) is byte-identical
// at 92.96% — the rotation is not a merged-role artefact.
//
// Untried: pinning `n` to r28 as well (fails — two pins on the same reg break
// the cr4 liveness and collapse the mfcr save, frame 0x58 -> 0x50); pinning
// `c1`/`c2`/`i` (also collapses the CR save); `-fno-schedule-insns*`,
// `-fno-thread-jumps`, `-fno-sched-interblock/spec`,
// `-fno-strength-reduce`, `-fno-branch-count-reg` (all inert or worse).
#include "types.h"

typedef struct {
    char pad0[4];
    s32 f4;
    u8 *f8;
    u16 fC;
    s32 f10;
    u16 f14;
    u8 f16[0x42];
    s32 f58;
} Unk_8012CD84;

void *fn_8012C9F0(s32, s32, s32);
void *fn_8012CA80(void);
void fn_8012CB2C(); /* deliberately unprototyped: want keeps crclr cr1eq */
void fn_8012CB60(); /* deliberately unprototyped: want keeps crclr cr1eq */
void fn_8012CC9C(void *);
void fn_8012CCCC(void *, s32);
s32 fn_8012ED70(void);
s32 Mth_Rnd(s32);
s32 Mth_Rnd2(s32);

u8 *fn_8012CD84(u8 *arg0) {
    typedef struct {
        u32 n8;
        s16 nC;
        s16 nE;
        u32 n10;
        u32 n14;
        u32 n18;
        u32 n1C;
        u32 n20;
        u32 n24;
        u16 n28;
        u8 pad2A[2];
    } F;
    F sp;
    s32 var_r24;
    u8 *var_r30;
    register s32 op __asm__("r28");
    u32 n;
    u32 sum;
    u32 i;
    s32 v;
    s32 v40;
    s32 k;
    s32 cnt;
    s32 idx;
    u8 *c1;
    u8 *c2;
    Unk_8012CD84 *o;

    var_r30 = arg0;
    do {
        op = *var_r30;
        var_r24 = 0;
        switch (op) {
        case 0x2f:
        case 0x37:
            var_r30++;
            fn_8012CB2C(&sp.n8, var_r30);
            var_r30 += 4;
            n = sp.n8;
            c1 = var_r30;
            sum = 0;
            i = 0;
            while (i < n) {
                fn_8012CB60(&sp.nC, c1);
                i++;
                c1 += 2;
                sum += sp.nC;
            }
            if (op == 0x2f) {
                v = Mth_Rnd(sum);
            } else {
                v = Mth_Rnd2(sum);
            }
            k = 0;
            c2 = var_r30;
            for (;;) {
                fn_8012CB60(&sp.nE, c2);
                v -= sp.nE;
                if (v < 0) {
                    break;
                }
                c2 += 2;
                k++;
            }
            var_r30 += n * 2;
            var_r30 += k * 4;
            fn_8012CB2C(&sp.n10, var_r30);
            var_r30 += 4;
            var_r30 += sp.n10;
            break;
        case 0x40:
            __asm__("" : "+r"(op));
            var_r30++;
            fn_8012CB2C(&sp.n14, var_r30);
            var_r30 += 4;
            n = sp.n14;
            var_r30 += n * 2;
            o = fn_8012C9F0((s32)var_r30, 0x40, n);
            if (o == NULL) {
                o = fn_8012CA80();
                o->f10 = op;
                o->f8 = var_r30;
                o->fC = n;
                o->f58 = Mth_Rnd(n);
            }
            o->f4 = fn_8012ED70();
            v40 = Mth_Rnd(n) & 0xffff;
            if (v40 == o->f58) {
                cnt = 1;
                do {
                    v40 = Mth_Rnd(n) & 0xffff;
                    if (v40 != o->f58) {
                        break;
                    }
                    cnt++;
                } while (cnt <= 0x64);
            }
            o->f58 = v40;
            var_r30 += v40 * 4;
            fn_8012CB2C(&sp.n18, var_r30);
            var_r30 += 4;
            var_r30 += sp.n18;
            break;
        case 0x41:
            __asm__("" : "+r"(op));
            var_r30++;
            fn_8012CB2C(&sp.n1C, var_r30);
            var_r30 += 4;
            n = sp.n1C;
            var_r30 += n * 2;
            o = fn_8012C9F0((s32)var_r30, 0x41, n);
            if (o == NULL) {
                o = fn_8012CA80();
                o->f10 = op;
                o->fC = n;
                o->f8 = var_r30;
                o->f14 = 0;
                fn_8012CC9C(o);
                fn_8012CCCC(o, 0);
            }
            o->f4 = fn_8012ED70();
            idx = o->f14 + 1;
            o->f14 = idx;
            if ((u16)idx >= o->fC) {
                fn_8012CCCC(o, 1);
                o->f14 = 0;
            }
            var_r30 += o->f16[o->f14] * 4;
            fn_8012CB2C(&sp.n20, var_r30);
            var_r30 += 4;
            var_r30 += sp.n20;
            break;
        case 0x2e:
            var_r30++;
            fn_8012CB2C(&sp.n24, var_r30);
            var_r30 += 4;
            var_r30 += sp.n24;
            break;
        case 0x49:
            var_r30++;
            fn_8012CB60(&sp.n28, var_r30);
            var_r30 += sp.n28;
            break;
        default:
            var_r24 = 1;
            break;
        }
    } while (var_r24 == 0);
    return var_r30;
}
