// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80019958-0x80019A6C (276B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

typedef struct {
    char pad0[0x30];
    f32 subA[3];
    f32 subB[3];
    char pad48[0x60];
    void *unk0xA8;
    char padAC[0x64];
} Obj;

s32 queue_front(s32);
extern s32 lbl_80300125;
void OSSetProgressiveMode(void *);
s32 fn_8001E17C(s32 arg0);
void fn_80017DA4(void);
void fn_8001B8D0(void);
void fn_8001B8B0(void);
void fn_8001B8C0(void);
void fn_8001B9C8(void);
void Camera_orthographic(Obj *, s32, s32, s32, s32);
void fn_8001737C(Obj *);
void GX_SetZMode(s32 arg0, s32 arg1, s32 arg2);
void set_blend_mode(s32 arg0, s32 arg1, u8 arg2);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_80018064(s32 *arg0);
void fn_80017E20(s32);
void fn_80016A88(Obj *, s32);
void fn_800173CC(Obj *);

bool ScriptNgc_Set480I(void) {
    Obj sp8;
    s32 sp118;
    s32 var_r31;
    s32 temp_r29;
    var_r31 = 0;
    OSSetProgressiveMode(0);
    temp_r29 = fn_8001E17C(0);
    do {
        fn_80017DA4();
        fn_8001B8D0();
        queue_front((s32)&sp8);
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
        if (var_r31 > 0x3C) {
            Script_RunScript(QB_UNKNOWN_0x6D5E3565, 0, 0, 0, 0);
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
    fn_8001E17C(temp_r29 != 0);
    return true;
}
