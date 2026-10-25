// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015896C-0x80158A00 (148B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern __ps_t lbl_802A8048;
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern s32 fn_801745B4(s32);

s32 ScriptSkaterSpeedGreaterThan(CStruct *pParams, CScript *pScript) {
    f32 sp8;
    s32 var_r3;
    Unk_073F5245 *obj;
    f32 mag;
    __ps_t A;
    __ps_t B;
    SN_PS_type dot;

    if (GetFloat((s32)pParams, 0, &sp8, 0) == 0) {
        goto block_5;
    }
    obj = (void *)fn_801745B4(lbl_80305EAC);
    if (obj == NULL) {
        goto block_5;
    }
    var_r3 = 1;
    __asm__("" : "+r"(var_r3));
    A = obj->unk0xC0;
    B = obj->unk0xB8;
    dot.ps = __builtin_ps_merge00(__builtin_ps_mul(A, A), lbl_802A8048);
    dot.ps = __builtin_ps_madd(B, B, dot.ps);
    dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
    dot.ps = __builtin_ps_rsqrte(dot.ps);
    dot.ps = __builtin_ps_res(dot.ps);
    mag = dot.flt.hi;
    if (!(mag > sp8)) {
block_5:
        var_r3 = 0;
    }
    return var_r3;
}
