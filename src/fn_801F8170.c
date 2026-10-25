// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F8170-0x801F81E0 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

typedef float psf __attribute__((mode(PS)));

extern char lbl_802AE430[];
extern char lbl_802AE4F4[];

s32 fn_801F8170(Unk_9994C3F5 *arg0, Unk_9994C3F5 *arg1) {
    SN_PS_type s8;
    SN_PS_type s16;
    SN_PS_type t;
    register s32 kaddr __asm__("r9");
    register s32 ta __asm__("r11");
    register f32 tv __asm__("fr10");
    psf ahi;
    register psf bhi __asm__("fr12");
    psf alo;
    psf dh;
    psf sq;
    psf blo;
    psf dl;
    psf mg;
    register psf kv __asm__("fr11");

    __asm__("" : : "m"(s8.ps));
    ahi = *((psf *)&arg0->unk0x8);
    __asm__ volatile("lis %0,%1@ha" : "=r"(kaddr) : "s"(lbl_802AE430));
    bhi = *((psf *)&arg1->unk0x8);
    __asm__ volatile("addi %0,%0,%1@l" : "+r"(kaddr) : "s"(lbl_802AE430));
    alo = *(psf *)((char *)arg0);
    __asm__ volatile("lis %0,%1@ha" : "=r"(ta) : "s"(lbl_802AE4F4));
    kv = *(psf *)kaddr;

    dh = ahi - bhi;
    s16.ps = dh;
    __asm__("" : : "m"(s16.ps));
    blo = *(psf *)((char *)arg1);
    sq = dh * dh;
    __asm__ volatile("lfs %0,%1@l(%2)" : "=f"(tv) : "s"(lbl_802AE4F4), "r"(ta));
    dl = alo - blo;
    mg = __builtin_ps_merge00(sq, kv);
    s8.ps = dl;
    __asm__("" : : "m"(s8.ps));
    t.ps = dl * dl + mg;
    t.ps = __builtin_ps_sum0(t.ps, t.ps, t.ps);
    t.ps = __builtin_ps_rsqrte(t.ps);
    t.ps = __builtin_ps_res(t.ps);
    {
        f32 x = t.flt.hi;
        return x > tv;
    }
}
