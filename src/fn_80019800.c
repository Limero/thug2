// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80019800-0x80019958 (344B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

/* The 0x110-byte screen/viewport descriptor every ScriptNgc_Set* passes to
 * queue_front / Camera_orthographic / fn_8001737C / fn_800173CC / fn_80016A88.
 * Layout provable from queue_front (0x800169FC, promoted, byte-exact):
 * stfs 0x30,0x34,0x38 / 0x3C,0x40,0x44 and stw 0xA8; and all siblings use a
 * 0x110-byte local (frame 0x130, locals r1+8..r1+0x11C). */
typedef struct ScreenDesc {
    char pad0[0x30];
    f32 sub0[3];
    f32 sub1[3];
    char pad48[0x60];
    void *unk0xA8;
    char padAC[0x64];
} ScreenDesc;

extern s32 lbl_80300125;   /* lwz 0x125(r28) with r28 = lis -0x7fd0 */
extern bool lbl_8037B790;   /* stw -0x4870(r9) with r9 = lis -0x7fc8 */

void OSSetProgressiveMode(s32);
void fn_8001CC70(s32);
s32 GetInteger(void *, s32, s32 *, s32);
s32 fn_8001E17C(s32);
void queue_front(ScreenDesc *);
void Camera_orthographic(ScreenDesc *, s32, s32, s32, s32);
void fn_8001737C(ScreenDesc *);
void fn_800173CC(ScreenDesc *);
void GX_SetZMode(s32, s32, s32);
void set_blend_mode(s32, s32, u8);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_80018064(s32 *);
void fn_80017DA4(void);
void fn_80017E20(s32);
void fn_8001B8B0(void);
void fn_8001B8C0(void);
void fn_8001B8D0(void);
void fn_8001B9C8(void);
void fn_80016A88(ScreenDesc *, s32);

bool ScriptNgc_Set480P(void *arg0) {
    ScreenDesc sp8;
    /* Slot layout is LOAD-BEARING (worth 6 points, 91.9% -> 97.7%): want puts
     * &sp118 (the fn_80018064 arg, address-taken and r29-hoisted) at r1+0x118
     * and the GetInteger out-param at r1+0x11C.  ngccc assigns these two
     * scalar slots by FIRST REFERENCE, and GetInteger is reached first, so
     * plain `s32 sp11C; s32 sp118;` yields the swapped layout (0x118/0x11C).
     * DECLARATION ORDER IS NOT THE LEVER — both orders were measured and are
     * byte-identical (91.9% each), as are one-element-array and struct/union
     * spellings.  `volatile` on sp118 alone IS: it keeps that slot's store and
     * its address remat from folding into the loop-carried web, which changes
     * the allocation order.  Mirrors the identical finding in fn_80019B90 /
     * fn_80019958 (both promoted EXACT with the same shapes). */
    s32 sp11C;
    volatile s32 sp118;
    s32 var_r31;
    s32 temp_r30;

    var_r31 = 0;
    OSSetProgressiveMode(1);
    lbl_8037B790 = 1;
    fn_8001CC70(0);
    sp11C = -1;
    GetInteger(arg0, QB_SHOWMESSAGE, &sp11C, 0);
    temp_r30 = fn_8001E17C(0);
    do {
        fn_80017DA4();
        fn_8001B8D0();
        queue_front(&sp8);
        Camera_orthographic(&sp8, 0, 0, 0x280, 0x1C0);
        fn_8001B8B0();
        fn_8001737C(&sp8);
        GX_SetZMode(0, 7, 1);
        {
            /* 4 emitted insns of 86 words (4.7%).  See the header: retail emits
             * the three constant args as r3,r5,r4 and ngccc normalises two
             * independent constant births to ascending register order in every
             * C spelling (measured: plain call, temp var, s32/u8 param flips,
             * expression-valued arg — all 97.7% with r4/r5 swapped).  The `bl`
             * must live inside the asm window, hence `volatile` + "lr". */
            register s32 arg0 __asm__("r3");
            register s32 arg1 __asm__("r4");
            register s32 arg2 __asm__("r5");
            __asm__ volatile("li %0,0\n\tli %1,0\n\tli %2,5\n\tbl set_blend_mode"
                             : "=r"(arg0), "=r"(arg2), "=r"(arg1)
                             :
                             : "lr", "memory");
        }
        if ((sp11C != 0) && (var_r31 > 0x3C)) {
            Script_RunScript(QB_NGC_PROGRESSIVE, 0, 0, 0, 0);
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
    fn_8001E17C(temp_r30 != 0);
    return true;
}
