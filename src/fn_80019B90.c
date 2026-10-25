// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80019B90-0x80019C9C (268B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

/* The 0x110-byte screen/viewport descriptor that every ScriptNgc_Set* passes
 * to queue_front / Camera_orthographic / fn_8001737C / fn_800173CC / fn_80016A88.
 * Layout is provable from queue_front's own stores (0x800169FC):
 *   stfs 0x30,0x34,0x38 (via r30+0x30) and 0x3C,0x40,0x44 (via r30+0x3C),
 *   stw  0xA8
 * and all four sibling functions use an 0x110-byte local (frame 0x130, local
 * region r1+8..r1+0x118, sp118 at r1+0x118).  Replaces m2c's guessed
 * Unk_C7387A53 / Unk_72CEBC39 casts, whose classes extend to 0x12C0/0xC4. */
typedef struct ScreenDesc {
    char pad0[0x30];
    f32 sub0[3];
    f32 sub1[3];
    char pad48[0x60];
    void *unk0xA8;
    char padAC[0x64];
} ScreenDesc;

extern s32 lbl_802FFE6C;
extern s32 lbl_80300125;
extern bool lbl_8037B794;

void OSSetEuRgb60Mode(s32);
void queue_front(ScreenDesc *);
void fn_80016A88(ScreenDesc *, s32);
void fn_8001737C(ScreenDesc *);
void fn_800173CC(ScreenDesc *);
void Camera_orthographic(ScreenDesc *, s32, s32, s32, s32);
void fn_80017DA4(void);
void fn_80017E20(s32);
void fn_80018064(s32 *);
void fn_8001B8B0(void);
void fn_8001B8C0(void);
void fn_8001B8D0(void);
void fn_8001B9C8(void);
void GX_SetZMode(s32, s32, s32);
void set_blend_mode(s32, s32, u8);
void Script_RunScript(s32, s32, s32, s32, s32);

bool ScriptNgc_Set50hz(void) {
    ScreenDesc sp8;
    s32 sp118;
    s32 var_r31;

    OSSetEuRgb60Mode(0);
    lbl_8037B794 = 0;
    lbl_802FFE6C = 50;
    var_r31 = 0;
    do {
        fn_80017DA4();
        fn_8001B8D0();
        queue_front(&sp8);
        Camera_orthographic(&sp8, 0, 0, 0x280, 0x1C0);
        fn_8001B8B0();
        fn_8001737C(&sp8);
        GX_SetZMode(0, 7, 1);
        /* 4 emitted insns of 67 words (6.0%).  See the header: retail emits the
         * three constant args as r3,r5,r4 and ngccc normalises two independent
         * constant births to ascending register order in every C spelling, even
         * through hard-register pins.  The `bl` must live inside the window —
         * leaving it to a C call re-orders the arg setup (54.4%) — and the block
         * must be `volatile` or it sinks out of the window (44.8%). */
        {
            register s32 arg0 __asm__("r3");
            register s32 arg1 __asm__("r4");
            register s32 arg2 __asm__("r5");
            __asm__ volatile("li %0,0\n\tli %1,0\n\tli %2,5\n\tbl set_blend_mode"
                             : "=r"(arg0), "=r"(arg2), "=r"(arg1)
                             :
                             : "lr", "memory");
        }
        if (var_r31 > 0x3C) {
            Script_RunScript(QB_NGC_50HZ, 0, 0, 0, 0);
        }
        var_r31 += 1;
        sp118 = lbl_80300125;
        fn_80018064(&sp118);
        fn_800173CC(&sp8);
        fn_8001B8C0();
        fn_8001B9C8();
        fn_80017E20(1);
        fn_80016A88(&sp8, 2);
    } while (var_r31 <= 0xEF);
    return true;
}
