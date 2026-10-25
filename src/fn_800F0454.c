// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F0454-0x800F054C (248B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"

extern f32 lbl_8029B300;
extern f32 lbl_8029B2C0[];

typedef struct { f32 w, x, y, z; } WV;
typedef struct { u16 cnt; char pad[6]; f32 sp[10]; } FR;

s32 fn_800F03A0(s32, void *, s32);
s32 fn_800F0F84(s32, s32);
s32 GetVector(s32, s32, WV *, s32);

s32 fn_800F0454(s32 arg0, WV *arg1) {
    FR fr;
    s32 *walker;
    s32 obj;
    s32 best_obj;
    f32 best;
    __ps_t p, q;
    register f32 t13 __asm__("fr13");
    register f32 t0 __asm__("fr0");

    best_obj = 0;
    best = lbl_8029B300;
    fr.cnt = 0;
    walker = (s32 *)fn_800F03A0(arg0, &fr.cnt, 1);
    if (fr.cnt == 0) goto done;
    do {
        obj = fn_800F0F84(*walker, 1);
        GetVector(obj, QB_POS, (WV *)&fr.sp[0], 0);
        q = __builtin_ps_sub(*(__ps_t *)&fr.sp[2], *(__ps_t *)((char *)arg1 + 8));
        p = __builtin_ps_sub(*(__ps_t *)&fr.sp[0], *(__ps_t *)arg1);
        *(__ps_t *)&fr.sp[6] = q;
        *(__ps_t *)&fr.sp[4] = p;
        q = __builtin_ps_merge00(__builtin_ps_mul(q, q), *(const __ps_t *)lbl_8029B2C0);
        p = __builtin_ps_madd(p, p, q);
        p = __builtin_ps_sum0(p, p, p);
        *(__ps_t *)&fr.sp[8] = p;
        t13 = fr.sp[8];
        __asm__("fmr %0,%1" : "=f"(t0) : "f"(t13));
        if (t0 < best) {
            best = t0;
            best_obj = obj;
        }
        walker += 1;
    } while (--fr.cnt);
done:
    return best_obj;
}
