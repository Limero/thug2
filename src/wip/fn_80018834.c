// WIP DRAFT (non-matching) — hand reconstruction of the HUD/debug draw loop
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 2.8721% -> 4.3011% per-object flags: -fno-rerun-cse-after-loop -> -O1
// FLAG: -O1
// family=hand range=0x80018834-0x80018DEC size=1464B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// REWRITTEN 2026-10-06: replaced the m2c transcription with a structural
// reconstruction — the two `count < denom` guards are two separate `if`s in
// the source (ngccc CSEs the comparison into one cr0 and reuses it for both
// branches, which the m2c body modelled as a bogus `temp_cr0_lt` local), the
// Z-mode call takes 3 args (the old body passed 8), and the packed colour /
// rectangle coordinates are typed as u32/s32 instead of cast soup.
#include "types.h"
/* Every callee except fn_8001F2D8 is declared: the WANT has exactly one
 * `crclr cr1eq` (the unprototyped-call marker) and it sits right before the
 * fn_8001F2D8 `bl`, so that one call must stay unprototyped. */
s32 fn_80018178(void);
s32 fn_80019E0C(void);
void fn_80017DA4(void);
void fn_8001B8D0(void);
void fn_8001B8B0(void);
void queue_front(void *);
void Camera_orthographic(void *, s32, s32, s32, s32);
void fn_8001737C(void *);
void fn_800173CC(void *);
void GX_SetZMode(s32, s32, s32);
void fn_8001FAA4(s32, s32, s32, s32, s32);
void fn_8001E3CC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void fn_8001E4E8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void fn_8001E2FC(s32, s32, s32, s32, s32, s32, s32);
void fn_8001EEE0(s32, s32, s32, s32, s32);
void fn_8001FA54(s32, s32, s32, s32, s32);
void SetBlendMode(s32, s32, s32, s32, s32, s32, s32);
void fn_8001EFBC(s32, s32 *);
void fn_8001E248(s32, s32, s32, s32, s32, s32, s32);
void fn_8001F0A0(s32, s32, s32);
void fn_8001F1D4(u32);
f32 fn_8001F0F8(f32, f32, f32);
void fn_8001F0F4(void);
void fn_8001B8C0(void);
void fn_8001B9C8(void);
void fn_80017E20(s32);
void fn_80016A88(void *, s32);
void OSSuspendThread(void *);
extern char lbl_80290D28[];
extern char lbl_80290D30[];
extern char lbl_80301758[];
extern char lbl_80301760[];
extern char lbl_80301764[];
extern char lbl_80301768[];
extern char lbl_8030176C[];
extern char lbl_80301770[];
extern char lbl_80301780[];
extern char lbl_80301790[];
extern char lbl_80301794[];
extern char lbl_80301798[];
extern char lbl_8031FB28[];
extern char lbl_80377678[];
extern char lbl_8037767C[];
extern char lbl_8037B5E8[];

typedef struct {
    u8 pad[0x110];
} Cam;

/* one rectangle corner */
#define VERT(x, y, col)                        \
    do {                                       \
        fn_8001F0F8((f32)(x), (f32)(y),        \
                    *(f32 *)lbl_80290D30);     \
        fn_8001F1D4(col);                      \
    } while (0)

void fn_80018834(void) {
    Cam cam;
    s32 sp128;
    s32 sp12C;
    s32 sp130;
    s32 sp134;
    s32 sp138;
    s32 count;
    s32 denom;
    s32 span;
    s32 x0;
    s32 x1;
    s32 y0;
    s32 y1;
    u32 colA;
    u32 colB;
    u32 colC;

    for (;;) {
        if (fn_80018178() == 0 && fn_80019E0C() == 0) {
            *(s32 *)lbl_8037767C += 1;
        }
        if (*(s32 *)lbl_80301758 != 0 &&
            *(s32 *)(lbl_8037B5E8 + 0x18C) == 0 &&
            fn_80018178() == 0) {
            fn_80017DA4();
            fn_8001B8D0();
            fn_8001B8B0();
            queue_front(&cam);
            Camera_orthographic(&cam, 0, 0, 0x280, 0x1C0);
            fn_8001737C(&cam);

            count = *(s32 *)lbl_8037767C;
            denom = *(s32 *)lbl_80377678;
            span = *(s32 *)lbl_80301768 - 1;
            if (count < denom) {
                span = span * count / denom;
            }
            y0 = *(s32 *)lbl_80301760;
            x0 = *(s32 *)lbl_80301764;
            y1 = y0 + span;
            x1 = x0 - 1 + *(s32 *)lbl_8030176C;

            if (count < denom) {
                sp134 = *(s32 *)(lbl_80301770 + 0xC) +
                        (*(s32 *)(lbl_80301780 + 0xC) * count) / denom;
                sp128 = *(s32 *)(lbl_80301770 + 0) +
                        (*(s32 *)(lbl_80301780 + 0) * count) / denom;
                sp12C = *(s32 *)(lbl_80301770 + 4) +
                        (*(s32 *)(lbl_80301780 + 4) * count) / denom;
                sp130 = *(s32 *)(lbl_80301770 + 8) +
                        (*(s32 *)(lbl_80301780 + 8) * count) / denom;
            } else {
                sp128 = *(s32 *)(lbl_80301770 + 0) + *(s32 *)(lbl_80301780 + 0);
                sp12C = *(s32 *)(lbl_80301770 + 4) + *(s32 *)(lbl_80301780 + 4);
                sp130 = *(s32 *)(lbl_80301770 + 8) + *(s32 *)(lbl_80301780 + 8);
                sp134 = *(s32 *)(lbl_80301770 + 0xC) + *(s32 *)(lbl_80301780 + 0xC);
            }

            /* ARGB byte packing: +0xC is the low byte */
            colC = (u32)*(s32 *)(lbl_80301798 + 0xC) |
                   ((u32)*(s32 *)(lbl_80301798 + 8) << 8) |
                   ((u32)*(s32 *)(lbl_80301798 + 4) << 16) |
                   ((u32)*(s32 *)(lbl_80301798 + 0) << 24);
            colA = (u32)*(s32 *)(lbl_80301770 + 0xC) |
                   ((u32)*(s32 *)(lbl_80301770 + 8) << 8) |
                   ((u32)*(s32 *)(lbl_80301770 + 4) << 16) |
                   ((u32)*(s32 *)(lbl_80301770 + 0) << 24);
            colB = (u32)sp134 | ((u32)sp130 << 8) | ((u32)sp12C << 16) |
                   ((u32)sp128 << 24);

            x1 = x1 + *(s32 *)lbl_80301794;
            y1 = y1 + *(s32 *)lbl_80301790;
            x0 = x0 - *(s32 *)lbl_80301794;
            y0 = y0 - *(s32 *)lbl_80301790;

            GX_SetZMode(0, 7, 0);
            fn_8001FAA4(0, 0x3C, 0x3C, 0x3C, 0x3C);
            fn_8001E3CC(0, 5, 7, 7, 7, 0, 0, 1, 1, 0, 0, 0);
            fn_8001E4E8(0, 0xA, 0xF, 0xF, 0xF, 0, 0, 1, 1, 0);
            fn_8001E2FC(0, 0xFF, 0xFF, 4, 0xFF, 0xFF, 4);
            fn_8001EEE0(0, 1, 1, 0, 0);
            fn_8001FA54(4, 0, 0, 4, 0);
            SetBlendMode(0, 1, 1, 0, 1, 0, 0);
            fn_8001F2D8(2, 9, 1, 0xB, 1);
            sp138 = -1;
            fn_8001EFBC(4, &sp138);
            fn_8001E248(4, 1, 1, 0, 0, 0, 2);
            fn_8001F0A0(0x80, 0, 4);

            VERT(y0, x0, colA);
            VERT(y0, x1, colA);
            VERT(y1, x1, colA);
            VERT(y1, x0, colA);
            fn_8001F0F4();
            fn_8001F0A0(0x80, 0, 4);

            VERT(*(s32 *)lbl_80301760, *(s32 *)lbl_80301764, colB);
            VERT(*(s32 *)lbl_80301760, x1,
                 colB);
            VERT(y1, x1, colB);
            VERT(y1, *(s32 *)lbl_80301764, colB);
            fn_8001F0F4();

            fn_800173CC(&cam);
            fn_8001B8C0();
            fn_8001B9C8();
            fn_80017E20(0);
            fn_80016A88(&cam, 2);
        }
        OSSuspendThread(lbl_8031FB28);
    }
}

// NOTE 2026-10-06: structural reconstruction only. The shape
// above matches the WANT control flow (single infinite loop, invariant bases
// r23/r19/r17/r20 hoisted before 0x80018878, two CSE'd `count < denom`
// guards, the 4-corner VERT runs with a re-done (f32) conversion per call).
// PARKED: byte-exactness is blocked by
//   (a) the int->float pools: WANT keeps ONE 8-byte slot pair at 0x158/0x15c
//       and re-materialises `xoris rX,rX,0x8000; stw; lfd f31/f30` per
//       argument, with f31/f30 alternating across the four VERTs — the source
//       shape that produces that alternation is not yet pinned;
//   (b) tail call-setup scheduling of the GX block: the stack-arg stores for
//       fn_8001E3CC / fn_8001E4E8 are interleaved with the li's and are
//       reused from the same 8(r1)..0x14(r1) slots that the m2c body's sp8/
//       spC/sp10/sp14 modelled (ngccc here sinks/reorders them around the
//       crclr cr1eq of fn_8001F2D8, so a real arg list may still differ);
//   (c) the register file: WANT uses r14..r31 continuously and the greedy
//       allocator is driven by the *declaration order* of the locals above,
//       which is a guess.
