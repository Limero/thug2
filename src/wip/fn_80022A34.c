// WIP DRAFT (non-matching) — PARKED 2026-10-04. Body fully re-derived from the
// disassembly (the previous m2c bulk-fill was semantically wrong: it had dead
// `0;` statements, f32-typed byte loads and no loop). This body is a faithful
// decompilation: same calls, same argument vectors, same control flow, object
// 1892 B vs want 1936 B (was 1404 B).
// family=m2c range=0x80022A34-0x800231C4 size=1936B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// SCORE: DIFF, masked 2.48% (12/484 insns), object 44 B short.  The masked
// score is index-aligned, so it stays ~2% until the *prologue* matches; the
// old m2c body scored 2.9% only because it was a different length.
//
// WHY PARKED (remaining blockers, in order of cost):
//  (1) FRAME LAYOUT (hard blocker).  The want has five 4-byte locals at
//      0x18(sp18=u32) 0x1c(c1c colour) 0x20(sp20 colour) 0x24(sp24=arg0)
//      0x28(sp28=arg4), then a 28-byte dead hole 0x2c-0x47, then the int->f32
//      union at 0x48 and the CR slot at 0x54; frame 0xb0.  This draft only has
//      four locals (arg0 stays in r15 instead of being spilled to 0x24) and an
//      8-byte hole, frame 0x80.  The 28 bytes are *dead pseudos* in the original
//      (allocated then deleted before local-alloc) and cannot be recovered from
//      the binary — every single (r1) offset in the function depends on it.
//      NGCCC orders stack slots by pseudo-creation order, not by declaration
//      order, so the locals cannot even be permuted into place (measured).
//  (2) CR0 save/restore.  The want has `mfcr r12` + `stw r12,0x54` in the
//      prologue and `mtcrf 8,r12` before `addi r1`.  Probed: ngccc emits that
//      pair when an integer comparison is live ACROSS a call *and* the body uses
//      FP registers (verified with a 10-line probe).  This draft reproduces the
//      `mfcr`/`mtcrf 0x80` comparison-CSE pattern but not the CR0 save.
//  (3) `lfs f30, 0x1220(r10)` (the 1/256 scale) is loop-invariant-hoisted in the
//      want but stays inside the loop here; writing the hoist by hand puts the
//      load *before* the loop test instead of in the loop header.
//  (4) The two switch dispatch trees differ in shape (the want's first switch
//      tests 7 explicitly, the second switch needs `case 0:` as a real case for
//      its balanced tree).  Adding `case 0:` here already moved the tree closer.
//  (5) `lha r0, 0x10(r28)` vs `lhz`: the want sign-extends the halfword and then
//      `xori 0x8000`; every spelling of `(f32)(u16)x` measured gives `lhz`
//      (GCC narrows the load to HImode), so this single insn is unreachable from
//      plain C as written.
//
// TECHNIQUES FOUND (worth keeping — they generalise):
//  * `*(u32 *)&struct_colour` is what forces ngccc to keep a byte-wise-built
//    colour in MEMORY.  Without it (plain field assignment, or a union `.u`
//    read) GCC merges the four `stb` into `rlwimi` chains and keeps the colour in
//    a register.  With it the shape is exactly 4x stb -> lwz -> stw, which is
//    what the want does in both colour sites.
//  * `(f32)(u16)x * *(f32*)0x80291220` is the u16->f32 idiom here: lbl_80291218
//    is exactly 2^52 (the double bias GCC subtracts), 0x80291220 = 0.00390625.
//  * The order of the bit-test locals (`b7`, then `b5`, then `b6`) selects the
//    xor/rotate-mask emission order and matches the want exactly: the 0x40
//    xor comes first, then the 0x19 rotate-mask, then the 0x20 xor, then the
//    0x1a and 0x1b rotate-masks in that order.
//  * `!(flags & 0x20)` / `!(flags & 0x40)` / `(flags >> 7) & 1` give the
//    xor-then-extract forms; `(flags & 0x20) ? 1 : 0` gives a bare rlwinm.
//  * arg1[] element: a u16 flag word at +0x04 that OVERLAPS the byte at +0x05
//    (unk6/unk7 at +6/+7) — not expressible as plain fields, hence the union.
//  * Callee arities audited from the prologues: fn_800211D8 = 13 (args 9/10 are
//    floats in f1/f2, args 11-13 on the stack), fn_8001E3CC = 12,
//    fn_8001E4E8 = 10, SetBlendMode = 7, fn_8001E66C = 2, fn_80020834 = 4,
//    fn_8002062C = 2, fn_800224B8 = 8.
#include "types.h"

/* 4-byte RGBA colour: the game builds it byte-wise and then hands a *word* to
 * fn_800211D8 / fn_8001E66C, so the local is read back through `.u`. */
typedef union {
    struct { u8 r, g, b, a; } c;
    u32 u;
} Unk_Color;

typedef struct {
    u8 _pad[0xA];
    u16 unkA;
} Unk_8037Obj;

typedef struct {
    u8 _pad[0x148];
    Unk_Color color;
    s32 c14C;
} Unk_8037B5E8_t;
extern Unk_8037B5E8_t lbl_8037B5E8;

/* arg1[] element: 0x20 bytes; `f` is a u16 flag word overlapping the byte at +5. */
typedef struct {
    Unk_8037Obj *unk0;
    union { u16 flags; struct { u8 lo, hi; } b; } f;
    u8 unk6, unk7;
    u8 _pad0[4];
    Unk_Color unkC;
    s16 unk10;
    u8 _pad1[14];
} Unk_Elem;

typedef struct {
    u8 _pad[4];
    u8 unk4, unk5, unk6;
} Unk_Arg0;

extern f64 lbl_80291218;
extern f32 lbl_80291220;
extern f32 lbl_80291224;
extern s32 lbl_803001D0;
extern s32 lbl_80300348;
extern s32 lbl_8030034C;
extern s32 lbl_8030035C;
extern s32 lbl_80362AD0[];
extern s32 lbl_80362B10[];
extern s32 lbl_80362B50[];
extern s32 lbl_80362B90[];
extern s32 lbl_80362BD0[];
extern s32 lbl_80362C10[];
extern s32 lbl_80362C50[];
extern bool lbl_80362CB0;

void fn_800211D8(s32, u32 *, s32, s32, u8, u8, u8, s32, f32, f32, s32, s32, s32);
void fn_8001E3CC(s32, s32, s32, s32, s32, s32, s32, s32, u8, s32, s32, s32);
void fn_8001E4E8(s32, s32, s32, s32, s32, s32, s32, s32, u8, s32);
void SetBlendMode(s32, s32, s32, s32, s32, s32, s32);
void fn_8001E66C(s32, u32 *);
void fn_8002062C(s32, s32);
void fn_80020834(s32, s32, s32, s32);
void fn_800224B8(s32, s32, s32, s32, s32, s32, s32, s32);

void fn_80022A34(Unk_Arg0 *arg0, Unk_Elem *arg1, s32 arg2, s32 arg3, s32 arg4) {
    Unk_Color c1c;
    u32 sp18;
    Unk_Color sp20;
    Unk_Arg0 *sp24 = arg0;
    s32 sp28 = arg4;
    s32 n;
    s32 i;
    s32 lim;

    fn_8002062C(arg2, arg3);
    n = sp24->unk4;
    lim = lbl_803001D0;
    if ((lim < n) && (lim > 0)) {
        n = lim;
    }
    for (i = 0; i < n; i++, arg1++) {
        Unk_Elem *p = arg1;
        s32 b7 = (p->f.flags >> 7) & 1;
        s32 b5 = !(p->f.flags & 0x20);
        s32 b6 = !(p->f.flags & 0x40);

        if (p->unk0 != 0) {
            if (lbl_8037B5E8.c14C != 0) {
                c1c.c.r = lbl_8037B5E8.color.c.r;
                c1c.c.g = lbl_8037B5E8.color.c.g;
                c1c.c.b = lbl_8037B5E8.color.c.b;
                c1c.c.a = lbl_8037B5E8.color.c.a;
                sp18 = *(u32 *)&c1c;
                fn_800211D8(p->unk0, &sp18, b5, b6, p->unk6, p->unk7, p->f.b.hi, i,
                            (f32)(u16)p->unk10 * lbl_80291220, lbl_80291224, b7, arg2, arg3);
            } else {
                sp18 = p->unkC.u;
                fn_800211D8(p->unk0, &sp18, b5, b6, p->unk6, p->unk7, p->f.b.hi, i,
                            (f32)(u16)p->unk10 * lbl_80291220, lbl_80291224, b7, arg2, arg3);
            }
        } else {
            s32 six = p->unk6;
            s32 seven = p->unk7;
            s32 idx = lbl_80300348;

            if (six == 10) {
                sp20.c.r = seven;
                sp20.c.g = seven;
                sp20.c.b = seven;
            } else {
                sp20.c.r = p->unkC.c.r;
                sp20.c.g = p->unkC.c.g;
                sp20.c.b = p->unkC.c.b;
            }
            sp20.c.a = seven;
            if ((arg3 != 0) && (lbl_80362CB0 != 0)) {
                sp18 = *(u32 *)&sp20;
                fn_8001E66C(lbl_8030034C, &sp18);
            }
            if (arg2 != 0) {
                if (lbl_80362CB0 != 0) {
                    lbl_80362BD0[idx] = lbl_8030035C + 0x1C;
                    lbl_80362C50[idx] = 1;
                    lbl_80362C10[idx] = lbl_8030035C + 0xC;
                }
                if (lbl_80362CB0 != 0) {
                    lbl_80362B10[idx] = 0x100;
                    lbl_80362B50[idx] = 4;
                    lbl_80362B90[idx] = 1;
                    lbl_80362AD0[idx] = 0;
                }
            }
            switch (six) {
            case 10:
                if (arg2 != 0) {
                    if (lbl_80362CB0 != 0) {
                        fn_8001E3CC(idx, 7, 6, 5, 7, 0, 0, 0, 1, lbl_8030034C, 0, 0);
                    }
                    if (lbl_80362CB0 != 0) {
                        fn_8001E4E8(idx, 15, 14, 11, 15, 0, 0, 1, 1, lbl_8030034C);
                    }
                }
                break;
            case 9:
                if (arg2 != 0) {
                    if (lbl_80362CB0 != 0) {
                        fn_8001E3CC(idx, 7, 7, 7, 7, 0, 1, 1, 1, lbl_8030034C, 0, 0);
                    }
                }
                if (b7 != 0) {
                    if (arg2 != 0) {
                        if (lbl_80362CB0 != 0) {
                            fn_8001E4E8(idx, 15, 15, 15, 15, 0, 0, 1, 1, lbl_8030034C);
                        }
                    }
                } else {
                    if (arg2 != 0) {
                        if (lbl_80362CB0 != 0) {
                            fn_8001E4E8(idx, 11, 15, 15, 15, 0, 0, 1, 1, lbl_8030034C);
                        }
                    }
                }
                break;
            case 2:
            case 4:
            case 6:
            case 8:
                if (arg2 != 0) {
                    if (lbl_80362CB0 != 0) {
                        fn_8001E3CC(idx, 6, 7, 7, 7, 0, 0, 0, 1, lbl_8030034C, 0, 0);
                    }
                    if (lbl_80362CB0 != 0) {
                        fn_8001E4E8(idx, 15, 10, 14, 15, 0, 0, 1, 1, lbl_8030034C);
                    }
                }
                break;
            case 7:
            default:
                if (b7 != 0) {
                    if (arg2 != 0) {
                        if (lbl_80362CB0 != 0) {
                            fn_8001E3CC(idx, 7, 7, 7, 7, 0, 1, 1, 1, lbl_8030034C, 0, 0);
                        }
                    }
                } else {
                    if (arg2 != 0) {
                        if (lbl_80362CB0 != 0) {
                            fn_8001E3CC(idx, 5, 7, 7, 7, 0, 0, 1, 1, lbl_8030034C, b7, b7);
                        }
                    }
                }
                if (arg2 != 0) {
                    if (lbl_80362CB0 != 0) {
                        fn_8001E4E8(idx, 15, 10, 14, 15, 0, 0, 1, 1, lbl_8030034C);
                    }
                }
                break;
            }
            lbl_80300348++;
            if (lbl_8030034C > 0) {
                fn_80020834(six, seven, arg2, arg3);
            } else {
                switch (six) {
                case 0:
                case 1:
                case 2:
                    if (arg2 != 0) {
                        if (lbl_80362CB0 != 0) {
                            SetBlendMode(1, 4, 1, 0, 1, 0, 1);
                        }
                    }
                    break;
                case 3:
                case 4:
                    if (arg2 != 0) {
                        if (lbl_80362CB0 != 0) {
                            SetBlendMode(3, 0, 0, 0, 1, 0, 1);
                        }
                    }
                    break;
                case 5:
                case 6:
                    if (arg2 != 0) {
                        if (lbl_80362CB0 != 0) {
                            SetBlendMode(1, 4, 5, 0, 1, 0, 1);
                        }
                    }
                    break;
                case 7:
                case 8:
                    if (arg2 != 0) {
                        if (lbl_80362CB0 != 0) {
                            SetBlendMode(1, 0, 4, 0, 1, 0, 1);
                        }
                    }
                    break;
                case 9:
                case 10:
                    if (arg2 != 0) {
                        if (lbl_80362CB0 != 0) {
                            SetBlendMode(1, 2, 1, 0, 1, 0, 1);
                        }
                    }
                    break;
                default:
                    if (arg2 != 0) {
                        if (lbl_80362CB0 != 0) {
                            SetBlendMode(0, 1, 1, 0, 1, 0, 1);
                        }
                    }
                    break;
                }
            }
            lbl_8030034C++;
            lbl_8030035C++;
        }
    }
    {
        s32 f = 0;
        if (arg1->unk0 != 0) {
            if (arg1->unk0->unkA & 1) {
                f = 1;
            }
        }
        fn_800224B8(arg1->unk6, arg1->f.b.hi, f, sp24->unk5, sp24->unk6, arg2, arg3, sp28);
    }
}