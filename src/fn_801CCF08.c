// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CCF08-0x801CCF64 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern f64 fn_800144EC(s32);
s32 fn_801CCF08(s32 arg0, Unk_C7387A53 *arg1) {
    register __ps_t *dst __asm__("r29");
    register __ps_t *src __asm__("r30");
    register __ps_t t __asm__("fr11");
    register __ps_t m __asm__("fr12");
    __ps_t a;
    __ps_t b;
    volatile f32 sp8;
    f64 res;

    __asm__("" : "=r"(dst) : "0"(arg0));
    src = *((__ps_t * *)&arg1->unk0xC);
    res = fn_800144EC(arg0);
    a = src[24];
    sp8 = (f32)res;
    {
        register s32 r3c __asm__("r3");
        __asm__ volatile("mr %0,%1" : "=r"(r3c) : "r"(dst));
        __asm__ volatile("" :: "r"(r3c));
    }
    t = *(__ps_t *)&sp8;
    __asm__ volatile("" ::: "memory");
    b = src[23];
    __asm__ volatile("ps_mr %0,%1" : "=f"(m) : "f"(t));
    dst[0] = __builtin_ps_muls0(b, m);
    dst[1] = __builtin_ps_muls0(a, m);
}
