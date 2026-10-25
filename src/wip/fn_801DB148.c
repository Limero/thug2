// PARKED 2026-09-27 (ag18): best 80.6% (was 80.6%). Residual: single instruction
// placement — want `lfs f9, -0x2a04(r11)` at 0x8C (after ps_mul, before ps_merge00)
// vs got `lfs f9, 0(r11)` at 0x58 (right after the two lis anchors at 0x4C/0x50);
// all other 11 diffs are 2-word shifts from this one instruction. The rc3 load is
// independent of the PS math, so ngccc hoists it to the first available slot after
// its anchor; want defers it to 0x8C. Tried 12 distinct approaches: (1) move rc3
// assignment to use point, (2) move to between ps_mul and ps_merge00, (3) remove
// fr9 pin, (4) separate anchor variable, (5) volatile anchor, (6) memory clobber,
// (7) flags -fno-schedule-insns/-fno-schedule-insns2/-fno-sched-spec/-O2,
// (8) volatile asm with r11 pin, (9) volatile asm without pin, (10) load rc3 in
// last block, (11) asm output wedge, (12) volatile anchor load. All same or worse.
// Known family: doc-15 page-anchor scheduling (GCSE page-anchor class, same as
// fn_801B52D0). Future retry: find a C form giving two LIVE page anchors with
// deferred second load.
// WIP DRAFT — hand-rebuilt from disasm (m2c statics-DCE'd shell).
// Paired-single vector normalize/dot routine. Needs -mps-float.
// Semantics: normalize arg1 by len vs lbl_802AD5F4; scale by lbl_802AD5F8;
// dot vs *(arg0->0xC)+152/160 gated on lbl_802AD5FC; rescale by clamp sel.
// WIP DRAFT (non-matching) — hand-rebuilt from disasm (m2c statics-DCE'd shell).
// Paired-single vector normalize/dot routine. Needs -mps-float.
// family=m2c range=0x801DB148-0x801DB240 size=248B
// FLAG: -mps-float -Os
#include "types.h"
#include "structs.h"
extern f32 lbl_802AD5F4;
extern f32 lbl_802AD5F8;
extern f32 lbl_802AD5FC;
extern f32 lbl_802AD600;
extern char lbl_802AD278[];
void fn_801DB148(Unk_C7387A53 *arg0, Unk_EA529D06 *arg1) {
    volatile __ps_t spA;
    volatile __ps_t spB;
    volatile __ps_t spC;
    volatile __ps_t spD;
    register __ps_t ra8 __asm__("fr10");
    register __ps_t ra0 __asm__("fr11");
    register f32 rc1 __asm__("fr12");
    register f32 rc2 __asm__("fr7");
    register f32 rc3 __asm__("fr9");
    register f32 rlen __asm__("fr8");
    char *rtab;
    rtab = (char *)&lbl_802AD278;
    ra8 = arg1->unk0x8;
    ra0 = arg1->unk0x0;
    rc1 = lbl_802AD5F4;
    {
        register __ps_t wk __asm__("fr13");
        register __ps_t wt __asm__("fr0");
        wk = *(__ps_t *)rtab;
        wt = __builtin_ps_mul(ra8, ra8);
        wt = __builtin_ps_merge00(wt, wk);
        wt = __builtin_ps_madd(ra0, ra0, wt);
        wt = __builtin_ps_sum0(wt, wt, wt);
        wt = __builtin_ps_rsqrte(wt);
        wt = __builtin_ps_res(wt);
        spA = wt;
    }
    {
        register f32 wlen __asm__("fr0");
        wlen = *(f32 *)&spA;
        __asm__ volatile("fmr %0,%1" : "=f"(rlen) : "f"(wlen));
    }
    if (!(rlen > rc1)) {
        return;
    }
    rc2 = lbl_802AD5F8;
    rc3 = lbl_802AD5FC;
    {
        register f32 wsc __asm__("fr13");
        register __ps_t wb __asm__("fr13");
        register __ps_t wscc __asm__("fr0");
        wsc = rc2 / rlen;
        ((volatile f32 *)&spB)[0] = wsc;
        wb = *(__ps_t *)&spB;
        __asm__ volatile("ps_mr %0,%1" : "=f"(wscc) : "f"(wb));
        __asm__ volatile("ps_muls0 %0,%1,%2" : "=f"(wb) : "f"(ra8), "f"(wscc));
        __asm__ volatile("ps_muls0 %0,%1,%0" : "+f"(wscc) : "f"(ra0));
        arg1->unk0x0 = wscc;
        arg1->unk0x8 = wb;
        ra8 = *(__ps_t *)rtab;
        {
            void *p = *((void * *)&arg0->unk0xC);
            register __ps_t wb160 __asm__("fr12");
            register __ps_t wb152 __asm__("fr11");
            wb160 = ((Unk_130D31C8 *)p)->unk0xA0;
            wb152 = ((Unk_130D31C8 *)p)->unk0x98;
            __asm__ volatile("ps_mul %0,%0,%1" : "+f"(wb) : "f"(wb160));
            __asm__ volatile("ps_merge00 %0,%0,%1" : "+f"(wb) : "f"(ra8));
            __asm__ volatile("ps_madd %0,%0,%1,%2" : "+f"(wscc) : "f"(wb152), "f"(wb));
            __asm__ volatile("ps_sum0 %0,%0,%0,%0" : "+f"(wscc));
        }
        spC = wscc;
    }
    {
        register f32 wval __asm__("fr0");
        register f32 wv13 __asm__("fr13");
        register f32 wsel __asm__("fr0");
        wval = *(f32 *)&spC;
        __asm__ volatile("fmr %0,%1" : "=f"(wv13) : "f"(wval));
        if (wv13 < rc3) {
            wsel = lbl_802AD600;
        } else {
            wsel = rc2;
        }
        {
            void *p = *((void * *)&arg0->unk0xC);
            register __ps_t wv152 __asm__("fr0");
            register __ps_t ws __asm__("fr13");
            register __ps_t ws2 __asm__("fr12");
            rlen = rlen * wsel;
            ((volatile f32 *)&spD)[0] = rlen;
            wv152 = ((Unk_130D31C8 *)p)->unk0x98;
            ws = *(__ps_t *)&spD;
            arg1->unk0x0 = wv152;
            __asm__ volatile("ps_mr %0,%1" : "=f"(ws2) : "f"(ws));
            ws = ((Unk_130D31C8 *)p)->unk0xA0;
            wv152 = __builtin_ps_muls0(wv152, ws2);
            ws = __builtin_ps_muls0(ws, ws2);
            arg1->unk0x8 = ws;
            arg1->unk0x0 = wv152;
        }
    }
}
