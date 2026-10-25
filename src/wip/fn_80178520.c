// WIP DRAFT (non-matching) — 94.78% (6 of 115 words differ), object 460B ==
// want 460B.
// family=m2c range=0x80178520-0x801786EC size=460B
// FLAG: -fno-gcse
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// RESIDUAL is one 6-insn window at 0x80178588: retail keeps the loop-invariant
// `fc = lbl_802A8FD4` load and the `&fr.a` address materialisation AFTER the
// fn_8021D454 call and after the loop-entry `beq`, i.e. in the loop's preheader
// block; this body emits them in the source position (before the call), so the
// `bl`/`addi r23` swap and the lis/lfs move ahead of `beq`.
//
// Moving both statements into the loop body reproduces the preheader block
// (the lis/addi/lfs do land after the beq) but the two webs that used to live
// across the whole loop no longer do, so the allocator re-colours the whole
// function: g r26->r25, entry r27->r26, descp r23->r27 and the loop-carried
// constant 2 takes r23 instead of r25 — 87.8%.  Pinning g/entry/descp to their
// retail colours (r26/r27/r23) restores the colours but makes GCC CSE the
// address into descp and emit `mr r3,r23` for the fn_80137CB4 argument where
// retail recomputes `addi r3,r1,0x18` (93.0%); pinning only g/entry leaves
// descp and the constant 2 swapped (93.9%).  Putting the two statements after
// the in-loop call is worse (86.9-87.8%).  The r24 `iter` pin and -fno-gcse
// remain load-bearing in the parked form.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80305F9C;
extern s32 lbl_80305EC0;
extern char lbl_802A83F8[];
extern f32 lbl_802A8FD4;

extern s32 fn_8021D2C4(s32 arg0, s32 arg1);
extern s32 fn_8021D454(s32 arg0, CStruct * arg1, s32 arg2);
extern s32 fn_8021D4E8(s32 arg0, CStruct * arg1, s32 arg2);
extern void fn_80137CB4(Unk_9F066EC1 * arg0);
extern s32 fn_8022A9B8(Unk_31DE137E * arg0);
extern void fn_8013CC84(void * arg0, s32 arg1, Unk_C71E6DE1 * arg2);
extern s32 fn_80198F7C(s32 arg0);
extern s32 fn_8013F74C(s32 arg0);

// frame template: pins the exact sp layout incl. holes (recipe 86)
struct enum_frame {
    s32 pad08;      /* +0x00 -> r1+0x08 */
    s32 count;      /* +0x04 */
    char *sentinel; /* +0x08 */
    s32 pad14;      /* +0x0C */
    u8 a;           /* +0x10 -> r1+0x18 */
    u8 pad19;       /* +0x11 */
    u16 b;          /* +0x12 */
    s32 c;          /* +0x14 */
    s32 hole20;     /* +0x18 */
    s32 e;          /* +0x1C */
    u8 f;           /* +0x20 */
    char tail[0x1b];
};

s32 fn_80178520(Unk_A2CA54F3 *arg0) {
    struct enum_frame fr;
    register s32 iter __asm__("r24");
    char *sp;
    s32 g;
    CScript *entry;
    s32 walker;
    s32 descp;
    Unk_B9F059B9 *obj;
    Unk_2DBBFAC5 *src;
    s32 val;
    f32 fc;

    g = lbl_80305F9C;
    sp = (char *)&fr;
    ((struct enum_frame *)sp)->count = 0;
    ((struct enum_frame *)sp)->sentinel = lbl_802A83F8;
    iter = (s32)sp;
    entry = fn_8021D2C4(g, arg0->unk0x10);
    if (entry == 0) {
        ((Unk_42076946_2 *)iter)->unk0x8 = lbl_802A83F8;
        return 4;
    }
    walker = fn_8021D454(g, iter, 1);
    fc = lbl_802A8FD4;
    descp = (s32)((char *)&fr.a);
    while (walker != 0) {
        fn_80137CB4((s32)((char *)&fr.a));
        if (walker != entry) {
            fr.c = arg0->unk0x0;
            fr.b = arg0->unk0xA;
            fr.a = arg0->unk0x4;
            if (arg0->unk0x4 == 0x3a ||
                arg0->unk0x4 == 0x4c ||
                arg0->unk0x4 == 0x89) {
                fr.e = 2;
                fr.f = 8;
            } else if (arg0->unk0x4 == 0x99) {
                fr.e = 2;
                fr.f = 0xa;
            } else if (arg0->unk0x4 == 0x83) {
                if (fn_80198F7C(lbl_80305EC0) == QB_FIREFIGHT ||
                    fn_80198F7C(lbl_80305EC0) == QB_NETFIREFIGHT) {
                    obj = arg0->unk0x0;
                    if (*((f32 *)&obj->unk0x34) <= fc) {
                        if (obj->unk0x30 <= 0xF0) {
                            *((u8 *)&obj->unk0x38) =
                                *(volatile s32 *)(entry->unk0x18 + (s32)0x18);
                            src = arg0->unk0x10;
                            *(s32 *)obj = (fn_8013F74C(src) == 0)
                                ? src->unk0x20B4
                                : 0;
                        }
                    }
                }
            }
            fn_8013CC84(arg0->unk0xC, fn_8022A9B8(walker), descp);
        }
        walker = fn_8021D4E8(g, (s32)&fr, 1);
    }
    ((Unk_42076946_2 *)iter)->unk0x8 = lbl_802A83F8;
    return 1;
}
