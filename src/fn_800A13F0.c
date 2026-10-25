// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A13F0-0x800A14A8 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "dolphin/SN_PS.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_80297BCC;
f32 fn_80005C28(void *, void *, s32, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
typedef struct P58 { char _0[0x58]; __ps_t unk0x58; __ps_t unk0x60; } P58;

P58 *fn_800A16B8(void *, s32);
s32 fn_800A13F0(void *arg0, CStruct *arg1) {
    f32 sp18;
    __ps_t sp8[2];
    f32 transformed;
    __ps_t f11;
    __ps_t f12;
    __ps_t f0;
    __ps_t f13;
    P58 *ok;

    ok = fn_800A16B8(arg0, QB_OBJECT_TYPE_SKATER);
    if (ok == NULL) {
        return 0;
    }
    {
        GetFloat(arg1, 0, &sp18, 1);
        f11 = ((P58 *)arg0)->unk0x58;
        f12 = ((P58 *)arg0)->unk0x60;
        sp18 *= lbl_80297BCC;
        f13 = ok->unk0x58;
        f0 = ok->unk0x60;
        f0 = __builtin_ps_sub(f0, f12);
        f13 = __builtin_ps_sub(f13, f11);
        sp8[1] = f0;
        sp8[0] = f13;
        transformed = fn_80005C28((char *)arg0 + 0x78, sp8, 2, 1);
        return fabs(transformed) > sp18;
    }
}
