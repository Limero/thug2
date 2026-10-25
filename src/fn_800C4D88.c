// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C4D88-0x800C4E78 (240B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float -fno-schedule-insns
#include "types.h"
#include "dolphin/SN_PS.h"

/* The six out-param pairs. `&b.s10` is passed to fn_8003EF4C, so the
   otherwise-dead s00/s08/s18/s20/s28 stores survive DCE (this struct MUST
   escape — with separate locals they are all removed and the object shrinks
   by 32 bytes). */
typedef struct {
    sn_ps s00, s08, s10, s18, s20, s28;
} Blk;

/* r1+0x40. MUST be 8 bytes wide: ngccc's local-slot assignment orders a
   4-byte f32 local ahead of an 8-byte SN_PS_type local regardless of
   declaration order, which would put the union at 0x40 instead of 0x38 and
   lose both tail copies (see header). */
typedef struct { f32 v; char pad[4]; } F8;

typedef struct {
    char _p[0x20];
    sn_ps o20, o28;
    char _q[0x1350 - 0x30];
    s32 f1350;
} Obj;

typedef struct {
    sn_ps p0, p1, p2, p3;
} Quad;

extern char lbl_80298F18[];
extern f32 lbl_80299128;
extern f32 lbl_8029912C;

s32 fn_8003EF4C(void *, void *, s32, s32, s32);

s32 fn_800C4D88(Obj *arg0, Quad *arg1) {
    Blk b;
    /* r1+0x38. A STANDALONE union, never a member of Blk: only that shape
       leaves the lane reload in a scratch FPR and yields retail's
       `lfs f0`+`fmr f13,f0` and `psq_l f13`+`ps_mr f0,f13`. */
    SN_PS_type res;
    F8 s38;
    sn_ps o1, o0;
    sn_ps p1, p0, p3, p2, k;
    f32 c1;
    /* the &lbl_80298F18 page anchor must be r9 so the 0.0f anchor gets r11 */
    register char *kp __asm__("r9");
    s32 fl, bo;
    f32 hi;

    p1 = arg1->p1;
    o1 = arg0->o28;
    kp = lbl_80298F18;
    p0 = arg1->p0;
    c1 = lbl_80299128;
    p3 = arg1->p3;
    o1 = p1 - o1;
    p2 = arg1->p2;
    k = *(sn_ps *)kp;
    o0 = arg0->o20;
    b.s08 = o1;
    o1 = o1 * p3;
    fl = arg0->f1350;
    o0 = p0 - o0;
    o1 = __builtin_ps_merge00(o1, k);
    b.s00 = o0;
    o0 = o0 * p2 + o1;
    res.ps = __builtin_ps_sum0(o0, o0, o0);
    hi = res.flt.hi;
    bo = (hi >= c1);
    if (fl != 0 && bo != 0) {
        sn_ps vv, u, m3, m2, a2, a3;
        s38.v = lbl_8029912C;
        vv = *(sn_ps *)&s38;
        u = vv;
        m3 = __builtin_ps_muls0(p3, u);
        m2 = __builtin_ps_muls0(p2, u);
        b.s28 = m3;
        a2 = p0 + m2;
        b.s20 = m2;
        a3 = p1 + m3;
        b.s10 = a2;
        b.s18 = a3;
        fn_8003EF4C(arg1, &b.s10, 0xFF, 0xFF, 1);
    }
    return bo;
}
