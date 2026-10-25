// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A07F0-0x800A0858 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern __ps_t lbl_80297B28;
void fn_8012772C(s32, s32, f32);
bool fn_800A07F0(Unk_130D31C8 *arg0, s32 arg1, CScript *arg2) {
    __ps_t A;
    __ps_t D;
    __ps_t t;
    SN_PS_type dot;
    f32 x;

    D = arg0->unk0xC0;
    A = arg0->unk0xB8;
    t = __builtin_ps_merge00(__builtin_ps_mul(D, D), lbl_80297B28);
    dot.ps = __builtin_ps_madd(A, A, t);
    dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
    dot.ps = __builtin_ps_rsqrte(dot.ps);
    dot.ps = __builtin_ps_res(dot.ps);
    x = dot.flt.hi;
    fn_8012772C(arg2->unk0x18, QB_SPEED, x);
    return true;
}
