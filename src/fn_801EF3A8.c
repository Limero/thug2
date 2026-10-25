// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EF3A8-0x801EF44C (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "dolphin/SN_PS.h"

typedef struct ObjEF {
    char pad0x0[0x18];
    s32 unk0x18;
    char pad0x1C[0x3C];
    __ps_t unk0x58;
    __ps_t unk0x60;
} ObjEF;

typedef struct {
    char pad0x0[0xC];
    ObjEF *unk0xC;
} ArgEF;

extern __ps_t lbl_802ADC38;
extern f32 lbl_802ADC84;
extern s32 lbl_80305EAC;

struct ObjEF *fn_801745B4(s32);

f32 fn_801EF3A8(ArgEF *arg0, s32 *arg1) {
    ObjEF *temp_r3;
    ObjEF *c;
    __ps_t v11;
    __ps_t v13;
    __ps_t v0;
    __ps_t v10;
    __ps_t v12;
    SN_PS_type res;
    f32 x;

    temp_r3 = fn_801745B4(lbl_80305EAC);
    if ((temp_r3 != NULL) && (temp_r3 != arg0->unk0xC)) {
        *arg1 = temp_r3->unk0x18;
        c = arg0->unk0xC;
        v11 = temp_r3->unk0x58;
        v13 = c->unk0x58;
        v0 = c->unk0x60;
        v10 = temp_r3->unk0x60;
        v13 = __builtin_ps_sub(v13, v11);
        v12 = lbl_802ADC38;
        v13 = __builtin_ps_mul(v13, v13);
        v0 = __builtin_ps_sub(v0, v10);
        v0 = __builtin_ps_merge00(v0, v12);
        v0 = __builtin_ps_madds0(v0, v0, v13);
        v0 = __builtin_ps_sum0(v0, v0, v0);
        res.ps = v0;
        x = res.flt.hi;
        return x;
    }
    return lbl_802ADC84;
}
