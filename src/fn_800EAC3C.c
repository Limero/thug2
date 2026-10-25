// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EAC3C-0x800EAD24 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_8029AC40;
extern f32 lbl_8029AC44;
extern f32 lbl_8029AC48;
extern char lbl_80303150[];
extern char lbl_8029AC94[];
CStruct *GetStructure(s32, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 fn_801EC3F0(s32, char *);
f32 cosf(f32);
void fn_800EAD24(void *);
void fn_800EAC3C(Unk_C4A686EC *arg0) {
    f32 sp8[4];
    f32 temp_f31;
    s32 temp_r30;
    CStruct *ctx;

    temp_r30 = arg0->unk0x20;
    if ((u32) ((*(s32 *)&lbl_80303150 + Tmr_GetTime()) - temp_r30) <= 0x18U) {
        fn_801EC3F0(arg0->unk0x1858, lbl_8029AC94);
    }
    arg0->unk0x1A3C = 0;
    temp_f31 = __builtin_fabsf(lbl_8029AC40 - __builtin_fabsf(*(f32 *)(*(s32 *)((char *)arg0 + 0x183C) + 0x290)));
    ctx = GetStructure(QB_WALK_PARAMETERS, 0);
    GetFloat(ctx, QB_LADDER_CONTROL_TOLERANCE, &sp8[0], 1);
    if (temp_f31 > cosf(sp8[0] * lbl_8029AC44)) {
        fn_800EAD24(arg0);
        return;
    }
    arg0->unk0x80 = QB_LADDER;
    arg0->unk0x7BC = lbl_8029AC48;
}
