// WIP DRAFT — hand-rebuilt from retail disasm.
// family=m2c range=0x80017700-0x800179D0 size=720B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// WHAT IT IS: video-mode / widescreen prompt (sibling of fn_800179D0 and of
// the PROMOTED twin fn_80019B90 — same ScreenDesc 0x110-byte local at r1+8,
// s32 sp118 at r1+0x118).
//
// STATUS: 91.67% (15 diffs, exact 720B). Remaining diffs are register-only
// (bits/opcodes/branches all mask-equal). Two walls:
//   1. loop_optimize move order (solved): the early `pmax` address makes the
//      max high a movable *before* the pad high in scan order, so it moves
//      first (threshold 73 -> 70), pad then fails desirability at
//      70*1*1 < 71 and is hoisted in loop #2 with zero. That is why pad is
//      r26/max r25/zero r27 now; dropping `pmax` regresses to 17 diffs.
//      Residual: sched1 keeps the two pre-loop `lis` in emission order
//      (max,inc), the want has inc,max (two diffs).
//   2. psp (&sp118) allocates last: 5 refs / 73 live -> priority 1369,
//      behind inc high (9/130 -> 2076) and clamp high (9/136 -> 1985).
//      The want order is psp,inc,clamp (psp r31, inc r29, clamp r28);
//      here it is inc,clamp,psp (r31,r29,r28) - a 3-cycle. psp needs
//      refs>=8 at this live length (or live<48 at 5 refs); the two stores
//      are direct frame-pointer stores, so they add no refs. Making them
//      go through a pointer (shared or store-only) breaks codegen: stores
//      become 0(reg), and the +=/-= RMW pointer form breaks the frame
//      (0x138) and block layout.
// DO NOT lose the `t = *var_r9; flags = t | flags;` two-step: it is what
// emits `or r30,r0,r30` (plain `flags |= *p` gives the operands swapped).
// Dead temporaries are removed before loop_optimize #1 (cse1 -> DCE), so
// they cannot raise the loop's insn count.
//
// Semantics (all from want): the extracted bit is PAD_BUTTON_B; skip-loop iff
// (prog && reset==0x80000000 && !(bit)); else loop iff !(flags & PAD_BUTTON_A);
// 0x8026626C is OSSetProgressiveMode (symbols.txt).
#include "types.h"
#include "qb_constants.h"

// From dolphin/pad.h
#define PAD_MAX_CONTROLLERS     4
#define PAD_BUTTON_DOWN  (1 << 2)   // 0x0004
#define PAD_BUTTON_UP    (1 << 3)   // 0x0008
#define PAD_BUTTON_A     (1 << 8)   // 0x0100
#define PAD_BUTTON_B     (1 << 9)   // 0x0200

typedef struct ScreenDesc {
    char pad0[0x30];
    f32 sub0[3];
    f32 sub1[3];
    char pad48[0x60];
    void *unk0xA8;
    char padAC[0x64];
} ScreenDesc;

extern u8 lbl_8033B5E8[];
extern f32 lbl_80290CF4;
extern f32 lbl_80290CF8;
extern char lbl_80290CE4[];
extern u16 lbl_80312434[];
extern s32 lbl_80300138;
extern s32 lbl_8030013C;
extern s32 lbl_80300125;
extern s32 lbl_80300120;

void fn_80017DA4(void);
void fn_8001B8D0(void);
void fn_8001B9C8(void);
void fn_80017E20(s32);
void fn_8001B8B0(void);
void fn_8001B8C0(void);
void queue_front(ScreenDesc *);
void Camera_orthographic(ScreenDesc *, s32, s32, s32, s32);
void fn_8001737C(ScreenDesc *);
void fn_800173CC(ScreenDesc *);
void GX_SetZMode(s32, s32, s32);
void set_blend_mode(s32, s32, u8);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_80018064(s32 *);
s32 fn_800176B8(void);
void fn_80016A88(ScreenDesc *, s32);
s32 OSGetProgressiveMode(void);
s32 OSGetResetCode(void);
void OSSetProgressiveMode(s32);
u32 VIGetDTVStatus(void);
void CStruct_new(s32);
s32 CStruct_ctor(void);
void AddInteger(s32, s32, s32);
s32 sprintf(char *, const char *, ...);
void fn_80131154(ScreenDesc *, s32, s32, s32);
void CStruct_delete(s32, s32);
void fn_80018E2C(void);

void fn_80017700(void) {
    ScreenDesc sp8;
    s32 sp118;
    u8 *base;
    u16 *tbl;
    s32 flags;
    s32 i;
    s32 bit;
    s32 prog;
    s32 is_reset;
    s32 temp2;

    base = lbl_8033B5E8;
    *(s32 *)(base + 0x1BC) = 0;
    *(f32 *)(base + 0x184) = lbl_80290CF4;
    flags = 0;
    tbl = lbl_80312434;
    for (i = 0; i <= 3; i++) {
        s32 var_ctr;
        u16 *var_r9;

        fn_80017DA4();
        fn_8001B8D0();
        fn_8001B9C8();
        fn_80017E20(1);

        for (var_ctr = PAD_MAX_CONTROLLERS, var_r9 = tbl; var_ctr != 0; var_ctr -= 1) {
            s32 t = *var_r9;
            s32 u = t | flags;
            flags = u;
            var_r9 += 6;
        }
    }

    bit = flags & PAD_BUTTON_B;
    *(f32 *)(lbl_8033B5E8 + 0x184) = lbl_80290CF8;
    prog = OSGetProgressiveMode();
    is_reset = (OSGetResetCode() == 0x80000000);

    if (VIGetDTVStatus() != 0) {
        if (bit || prog) {
            if (prog == 0 || !is_reset || bit) {
                if (!(flags & PAD_BUTTON_A)) {
                    while (!(flags & PAD_BUTTON_A)) {
                        s32 *pmax;
                        fn_80017DA4();
                        fn_8001B8D0();
                        queue_front(&sp8);
                        Camera_orthographic(&sp8, 0, 0, 0x280, 0x1C0);
                        fn_8001B8B0();
                        fn_8001737C(&sp8);
                        GX_SetZMode(0, 7, 1);
                        {
                            register s32 arg0 __asm__("r3");
                            register s32 arg1 __asm__("r4");
                            register s32 arg2 __asm__("r5");
                            __asm__ volatile("li %0,0\n\tli %1,0\n\tli %2,5\n\tbl set_blend_mode"
                                             : "=r"(arg0), "=r"(arg2), "=r"(arg1)
                                             :
                                             : "lr", "memory");
                        }
                        Script_RunScript(QB_NGC_WIDESCREEN, 0, 0, 0, 0);
                        pmax = &lbl_8030013C;
                        sp118 = lbl_80300125;
                        fn_80018064(&sp118);
                        fn_800173CC(&sp8);
                        fn_8001B8C0();
                        fn_8001B9C8();
                        fn_80017E20(1);
                        flags = fn_800176B8();
                        if (flags & PAD_BUTTON_DOWN) {
                            lbl_80300138 += 1;
                        }
                        if (flags & PAD_BUTTON_UP) {
                            lbl_80300138 -= 1;
                        }
                        if (lbl_80300138 < 0) {
                            lbl_80300138 = 0;
                        }
                        if (lbl_80300138 >= *pmax) {
                            lbl_80300138 = *pmax - 1;
                        }
                        fn_80016A88(&sp8, 2);
                    }
                }
            }
            sp118 = 0;
            fn_80018064(&sp118);
            fn_80017DA4();
            fn_80017E20(1);
            fn_80017DA4();
            fn_80017E20(1);
            CStruct_new(8);
            temp2 = CStruct_ctor();
            AddInteger(temp2, QB_SHOWMESSAGE,
                       (OSGetResetCode() == 0x80000000) ? 0 : 1);
            sprintf((char *)&sp8, lbl_80290CE4, lbl_80300138);
            fn_80131154(&sp8, temp2, 0, 0);
            if (temp2 != 0) {
                CStruct_delete(temp2, 3);
            }
        }
    } else {
        OSSetProgressiveMode(0);
    }
    fn_80018E2C();
    lbl_80300120 = 1;
}
