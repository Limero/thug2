// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B6EB8-0x801B6F48 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "structs.h"
void GetFloat(CStruct *, u32, volatile f32 *, s32);
s32 Mth_Rnd(s32);
extern f32 lbl_802AC1CC;
extern char lbl_802AC1D0[];
extern char lbl_802AC1D8[];

#define PG_D0 (-0x3E30)
#define PG_D8 (-0x3E28)

s32 ShouldExecuteAction(Unk_C7387A53 *arg0, CStruct *arg1, u32 arg2) {
    volatile f32 sp8;
    volatile union {
        u32 w[2];
        f64 d;
    } cvt;
    register s32 pg_d0 __asm__("r11");
    register s32 pg_d8 __asm__("r10");
    u32 lo;
    s32 var_r3;

    GetFloat(arg1, arg2, &sp8, 1);
    var_r3 = 1;
    if (!(sp8 > lbl_802AC1CC)) {
        cvt.w[1] = (u32)Mth_Rnd(0x3E8) ^ 0x80000000U;
        __asm__ volatile("lis %0,0x4330" : "=r"(lo));
        __asm__ volatile("lis %0,%1@ha" : "=r"(pg_d0) : "s"(lbl_802AC1D0));
        __asm__ volatile("lis %0,%1@ha" : "=r"(pg_d8) : "s"(lbl_802AC1D8));
        cvt.w[0] = lo;
        var_r3 = (f32)(cvt.d - *(f64 *)(pg_d0 + PG_D0)) < sp8 * *(f32 *)(pg_d8 + PG_D8);
    }
    return var_r3;
}
