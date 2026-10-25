// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A12D0-0x800A1360 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern __ps_t lbl_80297B28;
extern f32 lbl_80297BC4;
extern f32 lbl_80297BC8;
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 fn_800A12D0(Unk_130D31C8 *arg0, CStruct *arg1) {
    f32 sp8;
    __ps_t A;
    __ps_t B;
    SN_PS_type dot;
    f32 x;

    sp8 = lbl_80297BC4;
    GetFloat(arg1, 0, &sp8, 0);
    A = arg0->unk0xC0;
    B = arg0->unk0xB8;
    dot.ps = __builtin_ps_merge00(__builtin_ps_mul(A, A), lbl_80297B28);
    dot.ps = __builtin_ps_madd(B, B, dot.ps);
    dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
    dot.ps = __builtin_ps_rsqrte(dot.ps);
    dot.ps = __builtin_ps_res(dot.ps);
    x = dot.flt.hi;
    return x > sp8;
}
