// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range=0x80003334-0x80003464 (304B). Byte-identical.
// .init leaf (__OSFPRInit): the auto unit auto_00_80003100_init.s names
// its `bl fn_80003334` forward, so no force_active entry is needed.
// Link-level exactness verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

typedef float ps_reg __attribute__((mode(PS)));

extern f64 lbl_80003328;
extern ps_reg lbl_8000332C;

__attribute__((naked, section(".init"))) void fn_80003334(void) {
    register u32 r3 __asm__("r3");
    __asm__ volatile(
        "mfmsr %0\n\t"
        "ori %0, %0, 0x2000\n\t"
        "mtmsr %0\n\t"
        "mfspr %0, 0x398\n\t"
        "rlwinm. %0, %0, 3, 31, 31\n\t"
        ".long 0x4182008c"
        : "=&r"(r3));

    {
        register ps_reg p0 __asm__("fr0");
        register ps_reg p1 __asm__("fr1");
        register ps_reg p2 __asm__("fr2");
        register ps_reg p3 __asm__("fr3");
        register ps_reg p4 __asm__("fr4");
        register ps_reg p5 __asm__("fr5");
        register ps_reg p6 __asm__("fr6");
        register ps_reg p7 __asm__("fr7");
        register ps_reg p8 __asm__("fr8");
        register ps_reg p9 __asm__("fr9");
        register ps_reg p10 __asm__("fr10");
        register ps_reg p11 __asm__("fr11");
        register ps_reg p12 __asm__("fr12");
        register ps_reg p13 __asm__("fr13");
        register ps_reg p14 __asm__("fr14");
        register ps_reg p15 __asm__("fr15");
        register ps_reg p16 __asm__("fr16");
        register ps_reg p17 __asm__("fr17");
        register ps_reg p18 __asm__("fr18");
        register ps_reg p19 __asm__("fr19");
        register ps_reg p20 __asm__("fr20");
        register ps_reg p21 __asm__("fr21");
        register ps_reg p22 __asm__("fr22");
        register ps_reg p23 __asm__("fr23");
        register ps_reg p24 __asm__("fr24");
        register ps_reg p25 __asm__("fr25");
        register ps_reg p26 __asm__("fr26");
        register ps_reg p27 __asm__("fr27");
        register ps_reg p28 __asm__("fr28");
        register ps_reg p29 __asm__("fr29");
        register ps_reg p30 __asm__("fr30");
        register ps_reg p31 __asm__("fr31");
        register char *ptr __asm__("r3");
        __asm__ volatile("lis %0, 0x8000\n\tori %0, %0, 0x332c" : "=&r"(ptr));
        p0 = *(ps_reg *)ptr;
        __asm__ volatile("" : "+f"(p0));
        p1 = p0;
        __asm__ volatile("" : "+f"(p0));
        p2 = p0;
        __asm__ volatile("" : "+f"(p0));
        p3 = p0;
        __asm__ volatile("" : "+f"(p0));
        p4 = p0;
        __asm__ volatile("" : "+f"(p0));
        p5 = p0;
        __asm__ volatile("" : "+f"(p0));
        p6 = p0;
        __asm__ volatile("" : "+f"(p0));
        p7 = p0;
        __asm__ volatile("" : "+f"(p0));
        p8 = p0;
        __asm__ volatile("" : "+f"(p0));
        p9 = p0;
        __asm__ volatile("" : "+f"(p0));
        p10 = p0;
        __asm__ volatile("" : "+f"(p0));
        p11 = p0;
        __asm__ volatile("" : "+f"(p0));
        p12 = p0;
        __asm__ volatile("" : "+f"(p0));
        p13 = p0;
        __asm__ volatile("" : "+f"(p0));
        p14 = p0;
        __asm__ volatile("" : "+f"(p0));
        p15 = p0;
        __asm__ volatile("" : "+f"(p0));
        p16 = p0;
        __asm__ volatile("" : "+f"(p0));
        p17 = p0;
        __asm__ volatile("" : "+f"(p0));
        p18 = p0;
        __asm__ volatile("" : "+f"(p0));
        p19 = p0;
        __asm__ volatile("" : "+f"(p0));
        p20 = p0;
        __asm__ volatile("" : "+f"(p0));
        p21 = p0;
        __asm__ volatile("" : "+f"(p0));
        p22 = p0;
        __asm__ volatile("" : "+f"(p0));
        p23 = p0;
        __asm__ volatile("" : "+f"(p0));
        p24 = p0;
        __asm__ volatile("" : "+f"(p0));
        p25 = p0;
        __asm__ volatile("" : "+f"(p0));
        p26 = p0;
        __asm__ volatile("" : "+f"(p0));
        p27 = p0;
        __asm__ volatile("" : "+f"(p0));
        p28 = p0;
        __asm__ volatile("" : "+f"(p0));
        p29 = p0;
        __asm__ volatile("" : "+f"(p0));
        p30 = p0;
        __asm__ volatile("" : "+f"(p0));
        p31 = p0;
        __asm__ volatile("" : : "f"(p0), "f"(p1), "f"(p2), "f"(p3), "f"(p4), "f"(p5), "f"(p6), "f"(p7), "f"(p8), "f"(p9));
        __asm__ volatile("" : : "f"(p10), "f"(p11), "f"(p12), "f"(p13), "f"(p14), "f"(p15), "f"(p16), "f"(p17), "f"(p18), "f"(p19));
        __asm__ volatile("" : : "f"(p20), "f"(p21), "f"(p22), "f"(p23), "f"(p24), "f"(p25), "f"(p26), "f"(p27), "f"(p28), "f"(p29));
        __asm__ volatile("" : : "f"(p30), "f"(p31));
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
        register f64 *ptr __asm__("r3");
        __asm__ volatile("lis %0, 0x8000\n\tori %0, %0, 0x3328" : "=&r"(ptr));
        f0 = *ptr;
        __asm__ volatile("" : "+f"(f0));
        f1 = f0;
        __asm__ volatile("" : "+f"(f0));
        f2 = f0;
        __asm__ volatile("" : "+f"(f0));
        f3 = f0;
        __asm__ volatile("" : "+f"(f0));
        f4 = f0;
        __asm__ volatile("" : "+f"(f0));
        f5 = f0;
        __asm__ volatile("" : "+f"(f0));
        f6 = f0;
        __asm__ volatile("" : "+f"(f0));
        f7 = f0;
        __asm__ volatile("" : "+f"(f0));
        f8 = f0;
        __asm__ volatile("" : "+f"(f0));
        f9 = f0;
        __asm__ volatile("" : "+f"(f0));
        f10 = f0;
        __asm__ volatile("" : "+f"(f0));
        f11 = f0;
        __asm__ volatile("" : "+f"(f0));
        f12 = f0;
        __asm__ volatile("" : "+f"(f0));
        f13 = f0;
        __asm__ volatile("" : "+f"(f0));
        f14 = f0;
        __asm__ volatile("" : "+f"(f0));
        f15 = f0;
        __asm__ volatile("" : "+f"(f0));
        f16 = f0;
        __asm__ volatile("" : "+f"(f0));
        f17 = f0;
        __asm__ volatile("" : "+f"(f0));
        f18 = f0;
        __asm__ volatile("" : "+f"(f0));
        f19 = f0;
        __asm__ volatile("" : "+f"(f0));
        f20 = f0;
        __asm__ volatile("" : "+f"(f0));
        f21 = f0;
        __asm__ volatile("" : "+f"(f0));
        f22 = f0;
        __asm__ volatile("" : "+f"(f0));
        f23 = f0;
        __asm__ volatile("" : "+f"(f0));
        f24 = f0;
        __asm__ volatile("" : "+f"(f0));
        f25 = f0;
        __asm__ volatile("" : "+f"(f0));
        f26 = f0;
        __asm__ volatile("" : "+f"(f0));
        f27 = f0;
        __asm__ volatile("" : "+f"(f0));
        f28 = f0;
        __asm__ volatile("" : "+f"(f0));
        f29 = f0;
        __asm__ volatile("" : "+f"(f0));
        f30 = f0;
        __asm__ volatile("" : "+f"(f0));
        f31 = f0;
        __asm__ volatile("" : "+f"(f0));
        __asm__ volatile("" : : "f"(f0), "f"(f1), "f"(f2), "f"(f3), "f"(f4), "f"(f5), "f"(f6), "f"(f7), "f"(f8), "f"(f9));
        __asm__ volatile("" : : "f"(f10), "f"(f11), "f"(f12), "f"(f13), "f"(f14), "f"(f15), "f"(f16), "f"(f17), "f"(f18), "f"(f19));
        __asm__ volatile("" : : "f"(f20), "f"(f21), "f"(f22), "f"(f23), "f"(f24), "f"(f25), "f"(f26), "f"(f27), "f"(f28), "f"(f29));
        __asm__ volatile("" : : "f"(f30), "f"(f31));
        __asm__ volatile("mtfsf 255, %0" :: "f"(f0));
    }
    __asm__ volatile("blr");
}
