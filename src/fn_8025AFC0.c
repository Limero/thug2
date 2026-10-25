// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025AFC0-0x8025B180 (448B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

typedef float sn_ps __attribute__((mode(PS)));

typedef struct {
    char pad0[0x100];
    f64 fpr[32];
    f64 fpscr;
    struct {
        u32 value;
        u32 pad;
    } gqr[8];
    sn_ps psf[32];
} trk_fp_context;

register s32 ctx_r31 __asm__("r31");

extern void lbl_8025BC14(s32 context);
extern void lbl_8025BD3C(s32 context);

__attribute__((naked)) void fn_8025AFC0(void) {
    register s32 r3v __asm__("r3");
    register s32 r4v __asm__("r4");
    register s32 r5v __asm__("r5");
    register s32 r29v __asm__("r29");
    register s32 r30v __asm__("r30");
    register f64 fpscr __asm__("fr0");

    __asm__ volatile(
        "mfmsr %0\n\t"
        "ori %0, %0, 0x900\n\t"
        "xori %0, %0, 0x900\n\t"
        "ori %0, %0, 0x2000\n\t"
        "mtmsr %0\n\t"
        "isync"
        : "=&r"(r5v));

    fpscr = ((trk_fp_context *)ctx_r31)->fpscr;
    __asm__ volatile("mtfsf 0xff, %0" :: "f"(fpscr));

    __asm__ volatile(
        "mfspr %0, 0x398\n\t"
        "isync\n\t"
        "rlwinm. %0, %0, 3, 31, 31\n\t"
        "beq 8f"
        : "=&r"(r5v));

    r5v = 0;
    __asm__ volatile("mtspr 0x390, %0\n\tisync" :: "r"(r5v));

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

        p0 = ((trk_fp_context *)ctx_r31)->psf[0];
        __asm__ volatile("" : "+f"(p0));
        p1 = ((trk_fp_context *)ctx_r31)->psf[1];
        __asm__ volatile("" : "+f"(p1));
        p2 = ((trk_fp_context *)ctx_r31)->psf[2];
        __asm__ volatile("" : "+f"(p2));
        p3 = ((trk_fp_context *)ctx_r31)->psf[3];
        __asm__ volatile("" : "+f"(p3));
        p4 = ((trk_fp_context *)ctx_r31)->psf[4];
        __asm__ volatile("" : "+f"(p4));
        p5 = ((trk_fp_context *)ctx_r31)->psf[5];
        __asm__ volatile("" : "+f"(p5));
        p6 = ((trk_fp_context *)ctx_r31)->psf[6];
        __asm__ volatile("" : "+f"(p6));
        p7 = ((trk_fp_context *)ctx_r31)->psf[7];
        __asm__ volatile("" : "+f"(p7));
        p8 = ((trk_fp_context *)ctx_r31)->psf[8];
        __asm__ volatile("" : "+f"(p8));
        p9 = ((trk_fp_context *)ctx_r31)->psf[9];
        __asm__ volatile("" : "+f"(p9));
        p10 = ((trk_fp_context *)ctx_r31)->psf[10];
        __asm__ volatile("" : "+f"(p10));
        p11 = ((trk_fp_context *)ctx_r31)->psf[11];
        __asm__ volatile("" : "+f"(p11));
        p12 = ((trk_fp_context *)ctx_r31)->psf[12];
        __asm__ volatile("" : "+f"(p12));
        p13 = ((trk_fp_context *)ctx_r31)->psf[13];
        __asm__ volatile("" : "+f"(p13));
        p14 = ((trk_fp_context *)ctx_r31)->psf[14];
        __asm__ volatile("" : "+f"(p14));
        p15 = ((trk_fp_context *)ctx_r31)->psf[15];
        __asm__ volatile("" : "+f"(p15));
        p16 = ((trk_fp_context *)ctx_r31)->psf[16];
        __asm__ volatile("" : "+f"(p16));
        p17 = ((trk_fp_context *)ctx_r31)->psf[17];
        __asm__ volatile("" : "+f"(p17));
        p18 = ((trk_fp_context *)ctx_r31)->psf[18];
        __asm__ volatile("" : "+f"(p18));
        p19 = ((trk_fp_context *)ctx_r31)->psf[19];
        __asm__ volatile("" : "+f"(p19));
        p20 = ((trk_fp_context *)ctx_r31)->psf[20];
        __asm__ volatile("" : "+f"(p20));
        p21 = ((trk_fp_context *)ctx_r31)->psf[21];
        __asm__ volatile("" : "+f"(p21));
        p22 = ((trk_fp_context *)ctx_r31)->psf[22];
        __asm__ volatile("" : "+f"(p22));
        p23 = ((trk_fp_context *)ctx_r31)->psf[23];
        __asm__ volatile("" : "+f"(p23));
        p24 = ((trk_fp_context *)ctx_r31)->psf[24];
        __asm__ volatile("" : "+f"(p24));
        p25 = ((trk_fp_context *)ctx_r31)->psf[25];
        __asm__ volatile("" : "+f"(p25));
        p26 = ((trk_fp_context *)ctx_r31)->psf[26];
        __asm__ volatile("" : "+f"(p26));
        p27 = ((trk_fp_context *)ctx_r31)->psf[27];
        __asm__ volatile("" : "+f"(p27));
        p28 = ((trk_fp_context *)ctx_r31)->psf[28];
        __asm__ volatile("" : "+f"(p28));
        p29 = ((trk_fp_context *)ctx_r31)->psf[29];
        __asm__ volatile("" : "+f"(p29));
        p30 = ((trk_fp_context *)ctx_r31)->psf[30];
        __asm__ volatile("" : "+f"(p30));
        p31 = ((trk_fp_context *)ctx_r31)->psf[31];
        __asm__ volatile("" : "+f"(p31));
    }

    r5v = ((trk_fp_context *)ctx_r31)->gqr[0].value;
    __asm__ volatile("mtspr 0x390, %0" :: "r"(r5v));
    r5v = ((trk_fp_context *)ctx_r31)->gqr[1].value;
    __asm__ volatile("mtspr 0x391, %0" :: "r"(r5v));
    r5v = ((trk_fp_context *)ctx_r31)->gqr[2].value;
    __asm__ volatile("mtspr 0x392, %0" :: "r"(r5v));
    r5v = ((trk_fp_context *)ctx_r31)->gqr[3].value;
    __asm__ volatile("mtspr 0x393, %0" :: "r"(r5v));
    r5v = ((trk_fp_context *)ctx_r31)->gqr[4].value;
    __asm__ volatile("mtspr 0x394, %0" :: "r"(r5v));
    r5v = ((trk_fp_context *)ctx_r31)->gqr[5].value;
    __asm__ volatile("mtspr 0x395, %0" :: "r"(r5v));
    r5v = ((trk_fp_context *)ctx_r31)->gqr[6].value;
    __asm__ volatile("mtspr 0x396, %0" :: "r"(r5v));
    r5v = ((trk_fp_context *)ctx_r31)->gqr[7].value;
    __asm__ volatile("mtspr 0x397, %0" :: "r"(r5v));

    __asm__ volatile("8:");

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

        f0 = ((trk_fp_context *)ctx_r31)->fpr[0];
        __asm__ volatile("" : "+f"(f0));
        f1 = ((trk_fp_context *)ctx_r31)->fpr[1];
        __asm__ volatile("" : "+f"(f1));
        f2 = ((trk_fp_context *)ctx_r31)->fpr[2];
        __asm__ volatile("" : "+f"(f2));
        f3 = ((trk_fp_context *)ctx_r31)->fpr[3];
        __asm__ volatile("" : "+f"(f3));
        f4 = ((trk_fp_context *)ctx_r31)->fpr[4];
        __asm__ volatile("" : "+f"(f4));
        f5 = ((trk_fp_context *)ctx_r31)->fpr[5];
        __asm__ volatile("" : "+f"(f5));
        f6 = ((trk_fp_context *)ctx_r31)->fpr[6];
        __asm__ volatile("" : "+f"(f6));
        f7 = ((trk_fp_context *)ctx_r31)->fpr[7];
        __asm__ volatile("" : "+f"(f7));
        f8 = ((trk_fp_context *)ctx_r31)->fpr[8];
        __asm__ volatile("" : "+f"(f8));
        f9 = ((trk_fp_context *)ctx_r31)->fpr[9];
        __asm__ volatile("" : "+f"(f9));
        f10 = ((trk_fp_context *)ctx_r31)->fpr[10];
        __asm__ volatile("" : "+f"(f10));
        f11 = ((trk_fp_context *)ctx_r31)->fpr[11];
        __asm__ volatile("" : "+f"(f11));
        f12 = ((trk_fp_context *)ctx_r31)->fpr[12];
        __asm__ volatile("" : "+f"(f12));
        f13 = ((trk_fp_context *)ctx_r31)->fpr[13];
        __asm__ volatile("" : "+f"(f13));
        f14 = ((trk_fp_context *)ctx_r31)->fpr[14];
        __asm__ volatile("" : "+f"(f14));
        f15 = ((trk_fp_context *)ctx_r31)->fpr[15];
        __asm__ volatile("" : "+f"(f15));
        f16 = ((trk_fp_context *)ctx_r31)->fpr[16];
        __asm__ volatile("" : "+f"(f16));
        f17 = ((trk_fp_context *)ctx_r31)->fpr[17];
        __asm__ volatile("" : "+f"(f17));
        f18 = ((trk_fp_context *)ctx_r31)->fpr[18];
        __asm__ volatile("" : "+f"(f18));
        f19 = ((trk_fp_context *)ctx_r31)->fpr[19];
        __asm__ volatile("" : "+f"(f19));
        f20 = ((trk_fp_context *)ctx_r31)->fpr[20];
        __asm__ volatile("" : "+f"(f20));
        f21 = ((trk_fp_context *)ctx_r31)->fpr[21];
        __asm__ volatile("" : "+f"(f21));
        f22 = ((trk_fp_context *)ctx_r31)->fpr[22];
        __asm__ volatile("" : "+f"(f22));
        f23 = ((trk_fp_context *)ctx_r31)->fpr[23];
        __asm__ volatile("" : "+f"(f23));
        f24 = ((trk_fp_context *)ctx_r31)->fpr[24];
        __asm__ volatile("" : "+f"(f24));
        f25 = ((trk_fp_context *)ctx_r31)->fpr[25];
        __asm__ volatile("" : "+f"(f25));
        f26 = ((trk_fp_context *)ctx_r31)->fpr[26];
        __asm__ volatile("" : "+f"(f26));
        f27 = ((trk_fp_context *)ctx_r31)->fpr[27];
        __asm__ volatile("" : "+f"(f27));
        f28 = ((trk_fp_context *)ctx_r31)->fpr[28];
        __asm__ volatile("" : "+f"(f28));
        f29 = ((trk_fp_context *)ctx_r31)->fpr[29];
        __asm__ volatile("" : "+f"(f29));
        f30 = ((trk_fp_context *)ctx_r31)->fpr[30];
        __asm__ volatile("" : "+f"(f30));
        f31 = ((trk_fp_context *)ctx_r31)->fpr[31];
        __asm__ volatile("" : "+f"(f31));
    }

    r5v = (s32)0x80000000;
    r3v = *(volatile u32 *)((char *)r5v + 0xD4);
    r30v = *(volatile u32 *)((char *)r5v + 0xD8);
    if (r3v != r30v) {
        __asm__ volatile("mflr %0" : "=r"(r29v));
        lbl_8025BD3C(r3v);
        if (r30v != 0) {
            r3v = r30v;
            r30v = *(volatile u16 *)((char *)r3v + 0x1A2);
            r4v = r30v | 1;
            *(volatile u16 *)((char *)r3v + 0x1A2) = r4v;
            lbl_8025BC14(r3v);
            *(volatile u16 *)((char *)r3v + 0x1A2) = r30v;
        }
        __asm__ volatile("mtlr %0" :: "r"(r29v));
    }

    __asm__ volatile("blr");
}
