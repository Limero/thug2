// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A11D8-0x800A1230 (88B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern __ps_t lbl_80297B28;
extern f32 lbl_80297BB8;
s32 fn_800A11D8(Unk_130D31C8 *arg0) {
    __ps_t B;
    __ps_t A;
    __ps_t D;
    __ps_t C;
    __ps_t t;
    SN_PS_type dot;
    B = arg0->unk0x98;
    A = arg0->unk0xA0;
    D = arg0->unk0xB8;
    C = arg0->unk0xC0;
    t = __builtin_ps_mul(C, A);
    t = __builtin_ps_merge00(t, lbl_80297B28);
    dot.ps = __builtin_ps_madd(D, B, t);
    dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
    {
        f32 x = dot.flt.hi;
        return x < lbl_80297BB8;
    }
}
