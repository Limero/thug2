// WIP DRAFT (non-matching) — family=hand range=0x800EC22C-0x800EC324 size=248B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
//
// === PARKED 2026-10-06 — 21.2% (was 1.6% m2c husk) ===============
//
// SEMANTICS (fully decoded from tools/ps_disasm.py; the m2c husk was a shell):
//   void *fn_800EC22C(__ps_t *arg0, u8 *arg1) {
//       PV sp8;                        // r1+8,  16 B
//       Blk64 sp18;                    // r1+18, 64 B (8 pairs)
//       PV sp58;                       // r1+58, 16 B
//       sp8 = *(PV *)(arg1 + 0x20);                    // psq copies
//       if (arg1->unk0x70 != NULL) {
//           <4-iteration empty loop -> li/mtctr/bdnz>
//           sp18 = *(Blk64 *)(arg1->unk0x70 + 0x78);   // 8 psq pairs
//           fn_8008757C(&sp58, &sp18, &sp8);           // bl 0x8008757c
//           sp8 = sp58;
//           sp8.p[0] = ps_add(sp8.p[0], *(__ps_t*)(arg1->unk0x70 + 0x58));
//           sp8.p[1] = ps_add(sp8.p[1], *(__ps_t*)(arg1->unk0x70 + 0x60));
//       }
//       arg0->p[1] = sp8.p[1]; arg0->p[0] = sp8.p[0];  // note p[1] FIRST
//       return arg0;                                   // r3 = arg0
//   }
//
// --- FINDINGS THIS ROUND (all confirmed against the raw words) --------------
// 1) The tail pair ops are ps_add (xo=0x15), NOT ps_sub.  want word 0x47 is
//    0x1000682A = `ps_add f0, f13, f0` (FRA=f13 = arg[0x58], FRB=f0 = sp8.p[0]);
//    the m2c husk's `__builtin_ps_sub` produced 0x11AD0028 (xo=0x14, dest f13)
//    which is a DIFFERENT operation AND different operand slots.  Fixing this
//    alone moved the draft from 3.7% to 9.7% and is the single biggest lever.
//    NOTE: `__builtin_ps_add(X, Y)` emits FRT=X, FRA=Y, FRB=X — i.e. write the
//    destination/left operand first.
// 2) `arg1->unk0x70` is re-read AFTER the fn_8008757C call (`lwz r9,0x70(r31)`
//    at 0x800EC2CC) — arg1 must therefore stay live across the call in a
//    callee-saved reg (r31).  Keeping a stale `t` in a local instead pins arg1
//    out of the loop and breaks the whole allocation.
// 3) The `li r0,4; mtctr r0; bdnz .` at 0x800EC268 is a real 4-iteration empty
//    counted loop; a literal `for (i=0;i<4;i++){}` reproduces it (GCC 2.95's
//    doloop conversion keeps it as mtctr/bdnz).
// 4) sp8's epilogue copies p[1] to arg0+8 BEFORE p[0] to arg0+0.
//
// --- WHY PARKED: size / copy idiom ------------------------------------------
// Best measured 21.2% (tools/score_addrs.py) but the object is 264B, 16B OVER
// the 248B function.  The residual is the idiom for `sp8 = sp58`:
//   * `sp8 = sp58;` as a struct assignment -> 264B/21.2% : GCC lowers it to
//     WORD moves (lwz/stw) and materialises &sp8/&sp58 into two extra
//     callee-saved regs, which inflates the frame.
//   * element-wise `sp8.p[0]=sp58.p[0]; sp8.p[1]=sp58.p[1];` -> 240B/9.7% :
//     GCC FUSES each copy with the following ps_add (`sp8.p[0] = ps_add(
//     sp58.p[0], ...)`), deleting want's store/reload pair.
// want does neither: it emits 2 psq_l + 2 psq_st for the copy (psq pair moves,
// not word moves) and does NOT fuse the add.  A 16-byte struct of `__ps_t`
// (typedef double, structs.h) is copied with SImode word moves; the psq
// pair copy in retail must come from a PS-mode aggregate type (see
// include/dolphin/SN_PS.h `sn_ps __attribute__((mode(PS)))`, which the PS
// builtins do not accept as an operand).  Reproducing want byte-for-byte needs
// that aggregate type sorted out — that is the one open item, everything else
// in this function is decoded and correct.
//
// A size-EXACT variant exists (248B, 3.7%): use `sp8 = *(PV*)(arg1+0x20)` and
// `sp18 = *(Blk64*)(... + 0x78)` struct copies with `sp8 = sp58` and no
// element-wise writes; it is correct but the word-move copies score lower.
// The body below is the highest-measuring one (21.2%).
#include "types.h"

typedef struct { __ps_t p[2]; } PV;
typedef struct { __ps_t p[8]; } Blk64;

void fn_8008757C(PV *out, void *in, PV *pv);

void *fn_800EC22C(PV *arg0, u8 *arg1) {
    PV sp8;
    Blk64 sp18;
    PV sp58;

    sp8.p[0] = *(__ps_t *)(arg1 + 0x20);
    sp8.p[1] = *(__ps_t *)(arg1 + 0x28);
    if (*(u8 **)(arg1 + 0x70) != NULL) {
        s32 i;
        for (i = 0; i < 4; i++) {
        }
        sp18.p[0] = *(__ps_t *)(*(u8 **)(arg1 + 0x70) + 0x78);
        sp18.p[1] = *(__ps_t *)(*(u8 **)(arg1 + 0x70) + 0x80);
        sp18.p[2] = *(__ps_t *)(*(u8 **)(arg1 + 0x70) + 0x88);
        sp18.p[3] = *(__ps_t *)(*(u8 **)(arg1 + 0x70) + 0x90);
        sp18.p[4] = *(__ps_t *)(*(u8 **)(arg1 + 0x70) + 0x98);
        sp18.p[5] = *(__ps_t *)(*(u8 **)(arg1 + 0x70) + 0xA0);
        sp18.p[6] = *(__ps_t *)(*(u8 **)(arg1 + 0x70) + 0xA8);
        sp18.p[7] = *(__ps_t *)(*(u8 **)(arg1 + 0x70) + 0xB0);
        fn_8008757C(&sp58, &sp18, &sp8);
        sp8 = sp58;
        sp8.p[0] = __builtin_ps_add(sp8.p[0], *(__ps_t *)(*(u8 **)(arg1 + 0x70) + 0x58));
        sp8.p[1] = __builtin_ps_add(sp8.p[1], *(__ps_t *)(*(u8 **)(arg1 + 0x70) + 0x60));
    }
    arg0->p[1] = sp8.p[1];
    arg0->p[0] = sp8.p[0];
    return arg0;
}
