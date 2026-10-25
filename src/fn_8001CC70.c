// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001CC70-0x8001CEAC (572B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct ModeObj {
    s32 unk0x0;
    s32 unk0x4;
    u16 unk0x8;
    u16 unk0xA;
    u16 unk0xC;
    u16 unk0xE;
    u16 unk0x10;
    u16 unk0x12;
    s32 unk0x14;
} ModeObj;
typedef struct ScnObj {
    char pad0[0x110];
} ScnObj;
extern char lbl_803001D8[];
extern char lbl_803613E8[];
extern s32 lbl_803613E4;
extern s8 lbl_80300124;
extern bool lbl_8037B790;
extern bool lbl_8037B794;
extern char lbl_802910CC[];
extern char lbl_8029110C[];
extern s32 VIGetTvFormat(void);
extern void VIConfigure(void *);
extern void VIFlush(void);
extern void VIWaitForRetrace(void);
void GX_AdjustForOverscan(s32, s32, s32, s32);
void GX_SetZMode(s32, s32, s32);
void set_blend_mode(s32, u32, s32);
void fn_80017E20(s32);
void fn_80016A88(void *, s32);
void fn_80017DA4(void);
void fn_8001B8D0(void);
void *queue_front(void *);
void Camera_orthographic(void *, s32, s32, s32, u32);
void fn_8001B8B0(void);
void fn_8001737C(void *);
void fn_80018064(s32 *);
void fn_800173CC(s32);
void fn_8001B8C0(void);
void fn_8001B9C8(void);
void __hwInitVI(void);
s32 fn_8001E17C(s32);
void fn_8001CC70(void *arg0) {
    ScnObj sp8;
    s32 sp118;
    s32 var_r30;
    s32 zero;
    s32 *p118;
    register ModeObj *temp_r9 __asm__("r9");
    register s32 a0 __asm__("r3");
    register s32 a1 __asm__("r4");
    register s32 a2 __asm__("r5");
    register s32 hwA __asm__("r10");
    register ModeObj *temp_r11 __asm__("r11");
    s32 temp_r3;
    register s32 var_r0 __asm__("r0");

    if (arg0 != NULL) {
        lbl_803613E4 = (s32)arg0;
    } else {
        lbl_803613E4 = (s32)lbl_803001D8;
        lbl_80300124 = 4;
        GX_AdjustForOverscan((s32)lbl_803001D8, (s32)lbl_803613E8, 0, 0);
        lbl_803613E4 = (s32)lbl_803613E8;
        temp_r3 = VIGetTvFormat();
        switch ((u32)temp_r3) {
        case 0:
            if (lbl_8037B790 != 0) {
                temp_r9 = (ModeObj *)lbl_803613E4;
                temp_r9->unk0x0 = 2;
                temp_r9->unk0x14 = (s32)arg0;
            }
            break;
        case 1:
            temp_r11 = (ModeObj *)lbl_803613E4;
            if (temp_r11->unk0x0 == 0) {
                var_r0 = lbl_8037B794;
                if (var_r0 == 0) {
                    var_r0 = 4;
                } else {
                    var_r0 = 0x14;
                }
            } else {
                var_r0 = lbl_8037B794;
                if (var_r0 != 0) {
                    var_r0 = 0x15;
                } else {
                    var_r0 = 5;
                }
            }
            temp_r11->unk0x0 = var_r0;
            var_r0 = lbl_8037B794;
            if (var_r0 != 0) {
                hwA = 0x1C0;
                temp_r9 = (ModeObj *)lbl_803613E4;
                temp_r9->unk0x8 = hwA;
                temp_r9->unk0x10 = hwA;
                temp_r9->unk0xC = 0x10;
            } else {
                hwA = 0x1F4;
                temp_r9 = (ModeObj *)lbl_803613E4;
                temp_r9->unk0x10 = hwA;
                temp_r9->unk0x8 = hwA;
                temp_r9->unk0xC = 0x25;
            }
            break;
        case 2:
            temp_r9 = (ModeObj *)lbl_803613E4;
            temp_r9->unk0x0 = 8;
            break;
        default:
            OSPanic(lbl_802910CC, 0x79B, lbl_8029110C);
            break;
        }
        VIConfigure((void *)lbl_803613E4);
        __hwInitVI();
    }
    VIFlush();
    p118 = &sp118;
    zero = 0;
    var_r30 = 4;
    VIWaitForRetrace();
    fn_8001E17C(0);
    VIFlush();
    do {
        fn_80017DA4();
        fn_8001B8D0();
        queue_front(&sp8);
        Camera_orthographic(&sp8, 0, 0, 0x280, 0x1C0);
        fn_8001B8B0();
        fn_8001737C(&sp8);
        GX_SetZMode(0, 7, 1);
        __asm__("li %0,0\n\tli %1,0\n\tli %2,5" : "=r"(a0), "=r"(a2), "=r"(a1));
        set_blend_mode(a0, a1, a2);
        sp118 = zero;
        fn_80018064(p118);
        fn_800173CC(&sp8);
        fn_8001B8C0();
        fn_8001B9C8();
        fn_80017E20(1);
        fn_80016A88(&sp8, 2);
        var_r30 -= 1;
    } while (var_r30 != 0);
}
