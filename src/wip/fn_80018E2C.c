// PARKED at NEAR 97.9%: 94 of 96 words match, object .text 384B == symbol size.
//
// WHAT THE FUNCTION IS: the QB_NGC_LICENSE startup path — "pick a video mode,
// run the frame loop 2 or 10 times, tear down". Display_flush(); n = flag ? 2 :
// 10; then per iteration either copy the 1.0f constant at lbl_80290D34 into the
// progress float or compute i/n, then the standard GX FIFO draw sequence
// (fn_80017DA4 / fn_8001B8D0 / queue_front / Camera_orthographic(0,0,640,448) /
// fn_8001B8B0 / fn_8001737C / GX_SetZMode(0,7,0) / set_blend_mode(0,5,0) /
// Script_RunScript(QB_NGC_LICENSE,0,0,0,0) / fn_80018064(&state) / fn_800173CC /
// fn_8001B8C0 / fn_8001B9C8 / fn_80017E20(1) / fn_80016A88(desc,2)) — the same
// tail the promoted siblings src/fn_80019800.c and src/fn_80019B90.c carry.
//
// THE FOUR LOAD-BEARING FINDINGS (each measured; all four are needed for 97.9%):
//  1. `extern CONST f32 lbl_80290D34[1]`.  The const qualifier is what lets
//     ngccc hoist the loop-invariant load into the PREHEADER into f30.
//     Without const the load stays inside the loop in f0, only f31 is
//     callee-saved, and the frame is 0x158 (8 short).  With const: f30+f31
//     saved, frame 0x160, LR 0x164 — exact.
//  2. THE SCREEN-DESCRIPTOR LOCAL MUST BE 0x128 BYTES, not the 0x110 the
//     siblings use, and the s32 handed to fn_80018064 is its +0x110 MEMBER
//     (= r1+0x118).  Measured frame rule for this function shape:
//       DF-temp slot      = align8(end of declared locals)   (the two int->float
//                            expansions share ONE slot at r1+0x130)
//       GPR saves (r26..r31) start right after it        = 0x138
//       FPR area starts at align16(that + 24)            = 0x150
//       frame = end of FPR area = 0x160, LR at frame+4    = 0x164
//     With the 0x110 sibling struct (locals end 0x11C) the DF slot lands at
//     0x120 and the frame is 0x150 — 16 bytes out, whole tail shifted.  With
//     0x114 the frame is 0x158.  So the real descriptor here is 0x128 bytes.
//  3. The progress store must be a STRUCT MEMBER of the base symbol
//     (`lbl_8037B5E8.progress`), not `*(f32 *)(lbl_8037B5E8 + 0x184)` on a char
//     array.  The array form makes ngccc fold +0x184 into the symbol's HA/LO
//     addend and drop the want's separate base materialisation — ONE word, and
//     every later word shifts.  Member form reproduces the want's three-step
//     page-anchor, base-add and displaced store.
//  4. `(f32)var_r31 / (f32)var_r30` on **s32** counters.  The want's
//     xoris/stw/stw/lfd/`fsub f31`/`frsp` pair is ngccc's own SIGNED int->float
//     expansion (the pool magic is 0x4330000080000000 = lbl_80290D38); the
//     `fsub` is NOT a source-level subtraction — do not "fix" it.
//     The object's only .rodata entry is those 8 bytes, so tools/fix_fp_pool.py
//     retargets it to lbl_80290D38, which is what the want's `lfd f31,0xd38(r10)`
//     references.  Bonus: because lbl_80290D34 and that pool double share the
//     0x8029xxxx page, the pool's loop-invariant page register CSEs into
//     `mr r11, r9` at +0x80 for free — that word is not hand-written.
//
// REMAINING DIFF (2 words, the ONLY ones): at +0x100/+0x104 the want loads
// immediates in r3, r5, r4 order (0, 0, 5) before the set_blend_mode call, while
// this build loads them in r3, r4, r5 order.
//  Same bug the two promoted siblings parked: retail emits the three constant
//  args as r3,r5,r4; ngccc normalises two independent constant births to
//  ASCENDING register order in every plain-C spelling (they measured plain
//  call, temp var, s32/u8 param flip and expression-valued arg — all identical
//  with r4/r5 swapped).  fn_80019800.c / fn_80019B90.c closed it with an asm
//  window that emits the three loads itself; that is out of scope here, so it
//  is left open.  Swapping the prototype and the argument list together does
//  NOT help (the registers are chosen by the prototype, the emission order by
//  the call site).
//
// RULED OUT (don't redo):
//  * m2c's `*(s32 *)((char *)0x8037B5E8 + (s32)0x184) = ...` literal-address
//    form — literal addresses compile to `lis; ori` (see finding 3 above).
//  * `fn_80018064(&lbl_80300125)` — the want stores the global into a local
//    first (`lwz r0,0x125(r27); addi r3,r1,0x118; stw r0,0x118(r1)`), so the
//    arg is a stack slot, not the global.
//  * `queue_front` returning `Obj*` (fn_800169FC.c) — irrelevant here, the
//    return is unused; the 0x110 layout in that file is just that file's guess.
//  * A 4-arg `Script_RunScript` (m2c's proto): the want sets r3..r7, so it takes
//    FIVE args here, same as the siblings.
//
//  * The siblings' asm window does NOT transfer here: the volatile+memory
//    barrier de-schedules cross-call arg interleaving across the whole loop
//    body (97.9% -> 71.9%).  The window only works where calls are already
//    isolated; here arg setups interleave across neighbouring calls.
//  * Chained zero-arg barriers: a cascade — chaining set_blend_mode's args
//    fixes its window but flips GX_SetZMode's window upstream; chaining ZMode
//    flips Camera_orthographic's; chaining Camera breaks the base-add
//    interleaving (94.8%).  Each chain perturbs the previous call's expansion
//    order, so single-window fixes cannot all hold; do not retry without a
//    whole-region ordering theory.
//  * Single-instruction arg births for the three constants: even clobber-free
//    volatile asm blocks the cross-call arg interleaving this region needs
//    (79.2%).
//  * Proto (s32,s32,u8) with plain (0,5,0) args: identical 97.9% with the same
//    r4/r5 swap, so the u8 third parameter alone does not birth the constants
//    in retail order.  Body keeps (s32,s32,s32) + (0,5,(u8)0).
//
// family=m2c range=0x80018E2C-0x80018FAC size=384B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.

#include "types.h"
#include "qb_constants.h"

// The screen/viewport descriptor every ScriptNgc_Set* passes to queue_front /
// Camera_orthographic / fn_8001737C / fn_800173CC / fn_80016A88.  Front part is
// provable from queue_front (0x800169FC, promoted, byte-exact: stfs 0x30..0x44,
// stw 0xA8); THIS function's copy is 0x128 bytes (see finding 2 above).
typedef struct ScreenDesc {
    char pad0[0x30];
    f32 sub0[3];
    f32 sub1[3];
    char pad48[0x60];
    void *unk0xA8;
    char padAC[0x64];
    s32 unk110;    /* +0x110 -> r1+0x118; fn_80018064's argument */
    char pad114[0x14];
} ScreenDesc;

extern u32 lbl_80300120;
extern s32 lbl_80300125;
extern const f32 lbl_80290D34[1];   /* 1.0f in .rodata2 (src/r2d_80290D0C.c) */
// The store target: base symbol 0x8037B5E8 + member offset 0x184, which is the
// float at 0x8037B76C.  See finding 3 in the PARKED note for why this has to be
// a member access and not a pointer arithmetic expression.
typedef struct {
    char pad[0x184];
    f32 progress;
} ProgressState;

extern ProgressState lbl_8037B5E8;

void Display_flush(void);
void fn_80017DA4(void);
void fn_8001B8D0(void);
void queue_front(ScreenDesc *);
void Camera_orthographic(ScreenDesc *, s32, s32, s32, s32);
void fn_8001B8B0(void);
void fn_8001737C(ScreenDesc *);
void GX_SetZMode(s32, s32, s32);
void set_blend_mode(s32, s32, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_80018064(void *);
void fn_800173CC(ScreenDesc *);
void fn_8001B8C0(void);
void fn_8001B9C8(void);
void fn_80017E20(s32);
void fn_80016A88(ScreenDesc *, s32);

void fn_80018E2C(void) {
    ScreenDesc sp8;
    s32 var_r30;
    s32 var_r31;

    Display_flush();

    var_r30 = 2;
    if (lbl_80300120 == 0) {
        var_r30 = 10;
    }

    for (var_r31 = 0; var_r31 < var_r30; var_r31++) {
        if (lbl_80300120 != 0) {
            lbl_8037B5E8.progress = lbl_80290D34[0];
        } else {
            lbl_8037B5E8.progress = (f32)var_r31 / (f32)var_r30;
        }

        fn_80017DA4();
        fn_8001B8D0();
        queue_front(&sp8);
        Camera_orthographic(&sp8, 0, 0, 0x280, 0x1C0);
        fn_8001B8B0();
        fn_8001737C(&sp8);
        GX_SetZMode(0, 7, 0);
        set_blend_mode(0, 5, (u8)0);
        Script_RunScript(QB_NGC_LICENSE, 0, 0, 0, 0);
        sp8.unk110 = lbl_80300125;
        fn_80018064(&sp8.unk110);
        fn_800173CC(&sp8);
        fn_8001B8C0();
        fn_8001B9C8();
        fn_80017E20(1);
        fn_80016A88(&sp8, 2);
    }
}