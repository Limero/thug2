// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80019A6C-0x80019B90 (292B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

/* The stack object at r1+8 (0x110 = 272 bytes). Layout from the promoted
 * callees: queue_front (src/fn_800169FC.c) writes +0xA8 and two P3s at
 * 0x30/0x3C, fn_8001737C (src/fn_8001737C.c) reads +0xA8, and
 * Camera_orthographic (src/wip/fn_80017480.c) writes 12 f32 at +0x00..0x2C,
 * +0xBC, proj[4][4] at +0xC0 and reaches +0x10C via fn_800175CC. Together with
 * the separate s32 at r1+0x118 that is 8+272+4 = 0x11C bytes of locals, which
 * is exactly Gsave(0x124) - 8 for the 3-register stmw r29 / 0x130 frame. */
typedef struct {
    f32 vf[12];          /* 0x000 */
    char pad030[0x7C];   /* 0x030 */
    f32 fAC;             /* 0x0AC */
    f32 fB0;             /* 0x0B0 */
    f32 fB4;             /* 0x0B4 */
    f32 fB8;             /* 0x0B8 */
    s32 iBC;             /* 0x0BC */
    f32 proj[4][4];      /* 0x0C0 */
    s32 rect[4];         /* 0x100 */
} Cam_t;

/* fn_80018064() is handed the u32 at .data 0x80300125 (fn_80018064 copies
 * *arg0 and hands it to GX_SetCopyClear as a packed colour). */
extern bool lbl_8037B794;
extern s32 lbl_803613E4;
extern s32 lbl_802FFE6C;
extern s32 lbl_80300125;

void queue_front(Cam_t *);
void Camera_orthographic(Cam_t *, s32, s32, s32, s32);
void fn_80016A88(Cam_t *, s32);
void fn_8001737C(Cam_t *);
void fn_800173CC(Cam_t *);
void fn_80017DA4(void);
void fn_80017E20(s32);
void fn_80018064(s32 *);
void fn_8001B8B0(void);
void fn_8001B8C0(void);
void fn_8001B8D0(void);
void fn_8001B9C8(void);
void fn_8001CC70(s32);
void fn_8001CEAC(void);
void GX_SetZMode(s32, s32, s32);
void set_blend_mode(s32, s32, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void OSSetEuRgb60Mode(s32);
void VIConfigure(s32);

bool ScriptNgc_Set60hz(void) {
    Cam_t sp;
    s32 sp118;
    s32 i;

    i = 0;
    OSSetEuRgb60Mode(1);
    lbl_8037B794 = 1;
    fn_8001CC70(0);
    fn_8001CEAC();
    VIConfigure(lbl_803613E4);
    lbl_802FFE6C = 0x3C;
    do {
        fn_80017DA4();
        fn_8001B8D0();
        queue_front(&sp);
        Camera_orthographic(&sp, 0, 0, 0x280, 0x1C0);
        fn_8001B8B0();
        fn_8001737C(&sp);
        GX_SetZMode(0, 7, 1);
        /* Same 4-insn window as the promoted twin ScriptNgc_Set50hz
         * (src/fn_80019B90.c): retail emits the constant args r3,r5,r4 and
         * ngccc normalises them to ascending order from any C spelling. */
        {
            register s32 arg0 __asm__("r3");
            register s32 arg1 __asm__("r4");
            register s32 arg2 __asm__("r5");
            __asm__ volatile("li %0,0\n\tli %1,0\n\tli %2,5\n\tbl set_blend_mode"
                             : "=r"(arg0), "=r"(arg2), "=r"(arg1)
                             :
                             : "lr", "memory");
        }
        if (i > 0x3C) {
            Script_RunScript(QB_NGC_60HZ, 0, 0, 0, 0);
        }
        sp118 = lbl_80300125;
        fn_80018064(&sp118);
        i += 1;
        fn_800173CC(&sp);
        fn_8001B8C0();
        fn_8001B9C8();
        fn_80017E20(1);
        fn_80016A88(&sp, 2);
    } while (i <= 0xEF);
    return true;
}
