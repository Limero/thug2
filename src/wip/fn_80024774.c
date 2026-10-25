// WIP DRAFT — hand reconstruction; range marker added 2026-10-03.
// REFRESHED 2026-10-07 (FPR-pin RETARGET sweep): 21.4286% -> 26.4286%
//   the `v11` pin was retargeted fr11 -> fr0 (nothing else touched).  fr-pin REMOVAL
//   had been swept; retargeting had not.  Checked NOT size-exact before or after.  §6hk.
// family=m2c range=0x80024774-0x800249A4 size=560B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-03 — PS/paired-single body (`__ps_t` everywhere, FPR-bound
// `register __ps_t v0 __asm__("fr0")` pins).  NOT scored by my harness because
// it needs the per-object `-mps-float` flag, which the single-variant runner
// omits; tools/test_wip_drafts.py adds it automatically for `__ps_t` bodies.
// FPR/VMX wall — do not attempt as GPR-only work.  Best-known body retained
// unchanged; no source edit was made beyond the marker.
//
// PARKED 2026-10-03 — range marker missing (added).
#include "types.h"
#include "structs.h"

extern char lbl_802913D4[];
extern char lbl_802913D8[];
extern char lbl_802913F8[];
extern __ps_t lbl_80291398;

typedef union {
    __ps_t ps;
    struct { f32 hi; f32 lo; } flt;
} PSValue;

void fn_80024724(CStruct *arg0);
s32 fn_80055018(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void fn_80055038(CStruct *arg0, CStruct *arg1, s32 arg2);
s32 Mem_NewZero(s32 arg0);
s32 fn_8002439C(s32 arg0);
void fn_80062594(CStruct *arg0, s32 arg1);

void *fn_80024774(CStruct *arg0, CStruct *arg1, __ps_t *arg2, f32 farg0) {
    PSValue sp8[11];
    register __ps_t v0 __asm__("fr0");
    register __ps_t v1 __asm__("fr9");
    register __ps_t v12 __asm__("fr12");
    register __ps_t v11 __asm__("fr0");
    __ps_t zero, t, f9, f13, tmp;
    PSValue r, one;
    f32 f_one;
    s32 var_ctr;
    __ps_t *p;

    fn_80024724(arg0);
    arg0->unk0x8 = (s32)lbl_802913F8;
    arg0->unk0x4 = 1;
    arg0->unk0x10 = fn_80055018(0x100, 0x100, 0x10, 0x10);
    fn_80055038(arg0, arg1, 0);
    *(f32 *)((char *)arg0 + 0x28) = farg0;

    v0 = arg2[0];
    *(__ps_t *)((char *)arg0 + 0x18) = v0;
    v1 = arg2[1];
    v12 = v0;
    *(__ps_t *)((char *)arg0 + 0x20) = v1;
    v11 = v1;
    zero = lbl_80291398;
    f_one = *(f32 *)&lbl_802913D4;

    t = __builtin_ps_sum1(v11, v11, v0);
    t = __builtin_ps_merge00(t, zero);
    r.ps = __builtin_ps_muls0(v12, t);
    r.ps = __builtin_ps_sum0(r.ps, r.ps, r.ps);
    if (r.flt.lo > f_one) {
        f13 = __builtin_ps_sum0(r.ps, r.ps, r.ps);
        tmp = __builtin_ps_muls1(v12, r.ps);
        *(__ps_t *)((char *)arg0 + 0x18) = tmp;
        sp8[10].ps = f13;
        sp8[10].flt.hi = 1.0f;
        f9 = sp8[10].ps;
        one.flt.lo = *(f32 *)&lbl_802913D8;
        tmp = __builtin_ps_muls0(v11, one.ps);
        *(__ps_t *)((char *)arg0 + 0x20) = tmp;
    }

    arg0->unk0xC = fn_8002439C(Mem_NewZero(0xD0));

    sp8[0].flt.lo = 1.0f;
    sp8[0].flt.hi = 1.0f;
    sp8[1].flt.lo = 1.0f;
    fn_8002464C((__ps_t *)sp8);

    p = &sp8[2];
    for (var_ctr = 4; var_ctr != 0; var_ctr--) {
    }

    v11 = *(__ps_t *)((char *)arg0 + 0x20);
    v12 = *(__ps_t *)((char *)arg0 + 0x18);
    zero = lbl_80291398;
    t = __builtin_ps_sum1(v11, v11, v0);
    t = __builtin_ps_merge00(t, zero);
    r.ps = __builtin_ps_muls0(v12, t);
    r.ps = __builtin_ps_sum0(r.ps, r.ps, r.ps);
    f9 = r.ps;

    sp8[7].flt.lo = 1.0f;
    sp8[6].flt.lo = 1.0f;
    sp8[6].flt.hi = 1.0f;
    sp8[7].flt.hi = 1.0f;
    sp8[2].flt.lo = 1.0f;
    sp8[6].ps = v12;
    sp8[2].flt.hi = 1.0f;
    sp8[7].ps = v11;
    sp8[3].flt.lo = 1.0f;
    sp8[3].flt.hi = 1.0f;
    sp8[4].flt.lo = 1.0f;
    sp8[4].flt.hi = 1.0f;
    sp8[5].flt.lo = 1.0f;
    sp8[5].flt.hi = 1.0f;
    sp8[8].flt.lo = 1.0f;
    sp8[8].flt.hi = 1.0f;
    sp8[9].flt.lo = 1.0f;
    sp8[9].flt.hi = 1.0f;

    if (r.flt.lo > f_one) {
        f13 = __builtin_ps_sum0(r.ps, r.ps, r.ps);
        sp8[10].ps = f13;
        tmp = __builtin_ps_muls1(v12, r.ps);
        sp8[10].flt.hi = 1.0f;
        sp8[6].ps = tmp;
        f9 = sp8[10].ps;
        f13 = __builtin_ps_madd(v11, f9, tmp);
        sp8[7].ps = f13;
    }

    {
        f32 x = sp8[7].flt.lo;
        f32 y = sp8[6].flt.hi;
        f32 z = sp8[6].flt.lo;
        sp8[2].flt.lo = x;
        sp8[2].flt.hi = -z;
        sp8[3].flt.lo = -y;
        sp8[4].flt.lo = y;
        sp8[4].flt.hi = -x;
        sp8[5].flt.lo = -z;
    }
    fn_80024668(arg0->unk0xC, p);
    fn_80062594(arg1, 1);
    return arg0;
}
// RE-TRIAGE 2026-10-12: re-verified 26.4% size-exact; FPR-pin wall stands; no body change.
