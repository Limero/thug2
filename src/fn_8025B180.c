// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025B180-0x8025B340 (448B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "dolphin/SN_PS.h"

register s32 *ctx_r31 __asm__("r31");

extern void lbl_8025BD3C(s32);
extern void lbl_8025BC14(s32, s32);

#define SAVE_F64(offset, value) \
    (*(f64 *)((char *)ctx_r31 + (offset)) = (value))
#define SAVE_PS(offset, value) \
    ps_st((void *)((char *)ctx_r31 + (offset)), (value), 0, 0)
#define SAVE_GQR(index) do { \
    v5 = 0; \
    __asm__ volatile("mfspr %0, %1" : "=r"(v5) : "i"(912 + (index))); \
    *(u32 *)((char *)ctx_r31 + 0x208 + (index) * 8) = v5; \
} while (0)

__attribute__((naked)) void fn_8025B180(void) {
    {
        register s32 v5 __asm__("r5");

        __asm__ volatile(
            "mfmsr %0\n\t"
            "ori %0, %0, 0x900\n\t"
            "xori %0, %0, 0x900\n\t"
            "ori %0, %0, 0x2000\n\t"
            "mtmsr %0\n\t"
            "isync"
            : "=r"(v5));
    }

    {
        register s32 v5 __asm__("r5");
        register s32 v30 __asm__("r30");
        register s32 active __asm__("r3");

        v5 = (s32)0x80000000;
        v30 = *(u32 *)((s32)v5 + 0xD4);
        __asm__ volatile("" : "+r"(v30));
        active = *(u32 *)((s32)v5 + 0xD8);
        if (active != v30) {
            register s32 v29 __asm__("r29");
            register s32 v4 __asm__("r4");

            __asm__ volatile("mflr %0" : "=r"(v29));
            if (active != 0) {
                lbl_8025BD3C(active);
            }
            active = v30;
            v30 = *(u16 *)((char *)active + 0x1A2);
            v4 = v30 | 1;
            *(u16 *)((char *)active + 0x1A2) = (u16)v4;
            lbl_8025BC14(active, v4);
            *(u16 *)((char *)active + 0x1A2) = (u16)v30;
            __asm__ volatile("mtlr %0" :: "r"(v29));
        }
    }

    {
        register f64 f0 __asm__("fr0");
        register f64 f1 __asm__("fr1");
        register f64 f2 __asm__("fr2");
        register f64 f3 __asm__("fr3");
        register f64 f4 __asm__("fr4");
        register f64 f5 __asm__("fr5");
        register f64 f6 __asm__("fr6");
        register f64 f7 __asm__("fr7");
        register f64 f8 __asm__("fr8");
        register f64 f9 __asm__("fr9");
        register f64 f10 __asm__("fr10");
        register f64 f11 __asm__("fr11");
        register f64 f12 __asm__("fr12");
        register f64 f13 __asm__("fr13");
        register f64 f14 __asm__("fr14");
        register f64 f15 __asm__("fr15");
        register f64 f16 __asm__("fr16");
        register f64 f17 __asm__("fr17");
        register f64 f18 __asm__("fr18");
        register f64 f19 __asm__("fr19");
        register f64 f20 __asm__("fr20");
        register f64 f21 __asm__("fr21");
        register f64 f22 __asm__("fr22");
        register f64 f23 __asm__("fr23");
        register f64 f24 __asm__("fr24");
        register f64 f25 __asm__("fr25");
        register f64 f26 __asm__("fr26");
        register f64 f27 __asm__("fr27");
        register f64 f28 __asm__("fr28");
        register f64 f29 __asm__("fr29");
        register f64 f30 __asm__("fr30");
        register f64 f31 __asm__("fr31");

        SAVE_F64(0x100, f0);
        SAVE_F64(0x108, f1);
        SAVE_F64(0x110, f2);
        SAVE_F64(0x118, f3);
        SAVE_F64(0x120, f4);
        SAVE_F64(0x128, f5);
        SAVE_F64(0x130, f6);
        SAVE_F64(0x138, f7);
        SAVE_F64(0x140, f8);
        SAVE_F64(0x148, f9);
        SAVE_F64(0x150, f10);
        SAVE_F64(0x158, f11);
        SAVE_F64(0x160, f12);
        SAVE_F64(0x168, f13);
        SAVE_F64(0x170, f14);
        SAVE_F64(0x178, f15);
        SAVE_F64(0x180, f16);
        SAVE_F64(0x188, f17);
        SAVE_F64(0x190, f18);
        SAVE_F64(0x198, f19);
        SAVE_F64(0x1A0, f20);
        SAVE_F64(0x1A8, f21);
        SAVE_F64(0x1B0, f22);
        SAVE_F64(0x1B8, f23);
        SAVE_F64(0x1C0, f24);
        SAVE_F64(0x1C8, f25);
        SAVE_F64(0x1D0, f26);
        SAVE_F64(0x1D8, f27);
        SAVE_F64(0x1E0, f28);
        SAVE_F64(0x1E8, f29);
        SAVE_F64(0x1F0, f30);
        SAVE_F64(0x1F8, f31);
    }

    __asm__ volatile(
        "mfspr 5, 0x398\n\t"
        "isync\n\t"
        ".long 0x54A51FFF\n\t"
        ".long 0x418200D0");

    {
        register s32 v5 __asm__("r5");

        SAVE_GQR(0);
        SAVE_GQR(1);
        SAVE_GQR(2);
        SAVE_GQR(3);
        SAVE_GQR(4);
        SAVE_GQR(5);
        SAVE_GQR(6);
        SAVE_GQR(7);
        v5 = 0;
        __asm__ volatile("mtspr 0x390, %0\n\tisync" :: "r"(v5));

        {
            register sn_ps p0 __asm__("fr0");
            register sn_ps p1 __asm__("fr1");
            register sn_ps p2 __asm__("fr2");
            register sn_ps p3 __asm__("fr3");
            register sn_ps p4 __asm__("fr4");
            register sn_ps p5 __asm__("fr5");
            register sn_ps p6 __asm__("fr6");
            register sn_ps p7 __asm__("fr7");
            register sn_ps p8 __asm__("fr8");
            register sn_ps p9 __asm__("fr9");
            register sn_ps p10 __asm__("fr10");
            register sn_ps p11 __asm__("fr11");
            register sn_ps p12 __asm__("fr12");
            register sn_ps p13 __asm__("fr13");
            register sn_ps p14 __asm__("fr14");
            register sn_ps p15 __asm__("fr15");
            register sn_ps p16 __asm__("fr16");
            register sn_ps p17 __asm__("fr17");
            register sn_ps p18 __asm__("fr18");
            register sn_ps p19 __asm__("fr19");
            register sn_ps p20 __asm__("fr20");
            register sn_ps p21 __asm__("fr21");
            register sn_ps p22 __asm__("fr22");
            register sn_ps p23 __asm__("fr23");
            register sn_ps p24 __asm__("fr24");
            register sn_ps p25 __asm__("fr25");
            register sn_ps p26 __asm__("fr26");
            register sn_ps p27 __asm__("fr27");
            register sn_ps p28 __asm__("fr28");
            register sn_ps p29 __asm__("fr29");
            register sn_ps p30 __asm__("fr30");
            register sn_ps p31 __asm__("fr31");

            SAVE_PS(0x248, p0);
            SAVE_PS(0x250, p1);
            SAVE_PS(0x258, p2);
            SAVE_PS(0x260, p3);
            SAVE_PS(0x268, p4);
            SAVE_PS(0x270, p5);
            SAVE_PS(0x278, p6);
            SAVE_PS(0x280, p7);
            SAVE_PS(0x288, p8);
            SAVE_PS(0x290, p9);
            SAVE_PS(0x298, p10);
            SAVE_PS(0x2A0, p11);
            SAVE_PS(0x2A8, p12);
            SAVE_PS(0x2B0, p13);
            SAVE_PS(0x2B8, p14);
            SAVE_PS(0x2C0, p15);
            SAVE_PS(0x2C8, p16);
            SAVE_PS(0x2D0, p17);
            SAVE_PS(0x2D8, p18);
            SAVE_PS(0x2E0, p19);
            SAVE_PS(0x2E8, p20);
            SAVE_PS(0x2F0, p21);
            SAVE_PS(0x2F8, p22);
            SAVE_PS(0x300, p23);
            SAVE_PS(0x308, p24);
            SAVE_PS(0x310, p25);
            SAVE_PS(0x318, p26);
            SAVE_PS(0x320, p27);
            SAVE_PS(0x328, p28);
            SAVE_PS(0x330, p29);
            SAVE_PS(0x338, p30);
            SAVE_PS(0x340, p31);
        }
    }

    {
        register f64 fpscr __asm__("fr0");

        __asm__ volatile("mffs %0" : "=f"(fpscr));
        SAVE_F64(0x200, fpscr);
    }
    __asm__ volatile("blr");
}
